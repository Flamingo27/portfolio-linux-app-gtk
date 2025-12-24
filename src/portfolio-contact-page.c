#include "portfolio-contact-page.h"

#include <gtk/gtk.h>
#include <libsoup/soup.h>
#include <json-glib/json-glib.h>

#define EMAIL_DEBOUNCE_MS 300

struct _PortfolioContactPage {
  AdwBin parent_instance;

  AdwEntryRow *name_entry;
  AdwEntryRow *email_entry;
  GtkTextView *message_view;

  GtkWidget   *email_suffix;
  guint        email_debounce_id;

  GtkButton   *send_button;
  GtkSpinner  *spinner;
  GtkLabel    *status_label;
  GtkRevealer *status_revealer;
};

G_DEFINE_TYPE (PortfolioContactPage, portfolio_contact_page, ADW_TYPE_BIN)

/* ───────── Email validation ───────── */

static gboolean
is_email_valid (const char *email)
{
  static GRegex *regex = NULL;

  if (!email || !*email)
    return FALSE;

  if (!regex)
    regex = g_regex_new (
      "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$",
      G_REGEX_CASELESS, 0, NULL);

  return g_regex_match (regex, email, 0, NULL);
}

/* ───────── Button state ───────── */

static void
update_button_state (PortfolioContactPage *self)
{
  GtkTextBuffer *buf;
  GtkTextIter s, e;
  char *msg;

  const char *name  = gtk_editable_get_text (GTK_EDITABLE (self->name_entry));
  const char *email = gtk_editable_get_text (GTK_EDITABLE (self->email_entry));

  buf = gtk_text_view_get_buffer (self->message_view);
  gtk_text_buffer_get_bounds (buf, &s, &e);
  msg = gtk_text_buffer_get_text (buf, &s, &e, FALSE);

  gtk_widget_set_sensitive (
    GTK_WIDGET (self->send_button),
    name && *name &&
    is_email_valid (email) &&
    msg && *msg
  );

  g_free (msg);
}

/* ───────── Debounced email validation ───────── */

static gboolean
email_validate_cb (gpointer data)
{
  PortfolioContactPage *self = data;
  const char *email = gtk_editable_get_text (GTK_EDITABLE (self->email_entry));

  self->email_debounce_id = 0;

  if (!email || !*email) {
    gtk_widget_set_visible (self->email_suffix, FALSE);
    gtk_widget_remove_css_class (GTK_WIDGET (self->email_entry), "error");
  }
  else if (is_email_valid (email)) {
    gtk_label_set_text (GTK_LABEL (self->email_suffix), "✓");
    gtk_widget_add_css_class (self->email_suffix, "success");
    gtk_widget_remove_css_class (self->email_suffix, "error");
    gtk_widget_set_visible (self->email_suffix, TRUE);
    gtk_widget_remove_css_class (GTK_WIDGET (self->email_entry), "error");
  }
  else {
    gtk_label_set_text (GTK_LABEL (self->email_suffix), "Invalid email");
    gtk_widget_add_css_class (self->email_suffix, "error");
    gtk_widget_remove_css_class (self->email_suffix, "success");
    gtk_widget_set_visible (self->email_suffix, TRUE);
    gtk_widget_add_css_class (GTK_WIDGET (self->email_entry), "error");
  }

  update_button_state (self);
  g_object_unref (self);
  return G_SOURCE_REMOVE;
}

/* ───────── Change handler ───────── */

static void
on_changed (GtkWidget *w, PortfolioContactPage *self)
{
  if (w == GTK_WIDGET (self->email_entry)) {
    if (self->email_debounce_id)
      g_source_remove (self->email_debounce_id);

    self->email_debounce_id =
      g_timeout_add_full (
        G_PRIORITY_DEFAULT,
        EMAIL_DEBOUNCE_MS,
        email_validate_cb,
        g_object_ref (self),
        NULL);
  }

  update_button_state (self);
}

/* ───────── Enter / Shift+Enter ───────── */

static gboolean
on_key_pressed (GtkEventControllerKey *c,
                guint keyval,
                guint keycode,
                GdkModifierType state,
                gpointer data)
{
  PortfolioContactPage *self = data;
  GtkWidget *w = gtk_event_controller_get_widget (GTK_EVENT_CONTROLLER (c));

  gboolean enter =
    keyval == GDK_KEY_Return || keyval == GDK_KEY_KP_Enter;
  gboolean shift = (state & GDK_SHIFT_MASK) != 0;

  if (!enter)
    return GDK_EVENT_PROPAGATE;

  if (GTK_IS_TEXT_VIEW (w) && !shift)
    return GDK_EVENT_PROPAGATE;

  if (gtk_widget_get_sensitive (GTK_WIDGET (self->send_button))) {
    g_signal_emit_by_name (self->send_button, "clicked");
    return GDK_EVENT_STOP;
  }

  return GDK_EVENT_PROPAGATE;
}

/* ───────── Status ───────── */

static gboolean
hide_status (gpointer r)
{
  gtk_revealer_set_reveal_child (GTK_REVEALER (r), FALSE);
  return G_SOURCE_REMOVE;
}

static void
show_status (PortfolioContactPage *self, const char *msg)
{
  gtk_label_set_text (self->status_label, msg);
  gtk_revealer_set_reveal_child (self->status_revealer, TRUE);
  g_timeout_add_seconds (3, hide_status, self->status_revealer);
}

/* ───────── Network ───────── */

static void
send_finished (GObject *src, GAsyncResult *res, gpointer data)
{
  PortfolioContactPage *self = data;

  if (!soup_session_send_finish (SOUP_SESSION (src), res, NULL))
    show_status (self, "❌ Something went wrong.");
  else {
    show_status (self, "✅ Message sent!");
    gtk_editable_set_text (GTK_EDITABLE (self->name_entry), "");
    gtk_editable_set_text (GTK_EDITABLE (self->email_entry), "");
    gtk_text_buffer_set_text (
      gtk_text_view_get_buffer (self->message_view), "", -1);
  }

  gtk_spinner_stop (self->spinner);
  gtk_widget_set_visible (GTK_WIDGET (self->spinner), FALSE);
  gtk_widget_set_sensitive (GTK_WIDGET (self->send_button), TRUE);
}

static void
on_send_clicked (GtkButton *b, PortfolioContactPage *self)
{
  GtkTextBuffer *buf;
  GtkTextIter s, e;
  char *msg;

  JsonBuilder *jb;
  JsonGenerator *jg;
  JsonNode *root;
  char *json;

  SoupSession *session;
  SoupMessage *req;

  buf = gtk_text_view_get_buffer (self->message_view);
  gtk_text_buffer_get_bounds (buf, &s, &e);
  msg = gtk_text_buffer_get_text (buf, &s, &e, FALSE);

  jb = json_builder_new ();
  json_builder_begin_object (jb);
  json_builder_set_member_name (jb, "name");
  json_builder_add_string_value (
    jb, gtk_editable_get_text (GTK_EDITABLE (self->name_entry)));
  json_builder_set_member_name (jb, "email");
  json_builder_add_string_value (
    jb, gtk_editable_get_text (GTK_EDITABLE (self->email_entry)));
  json_builder_set_member_name (jb, "message");
  json_builder_add_string_value (jb, msg);
  json_builder_end_object (jb);

  jg = json_generator_new ();
  root = json_builder_get_root (jb);
  json_generator_set_root (jg, root);
  json = json_generator_to_data (jg, NULL);

  session = soup_session_new ();
  req = soup_message_new (
    "POST", "https://portfolio-alokparna.pages.dev/contact");

  soup_message_set_request_body_from_bytes (
    req, "application/json",
    g_bytes_new_take (json, strlen (json)));

  gtk_widget_set_sensitive (GTK_WIDGET (b), FALSE);
  gtk_widget_set_visible (GTK_WIDGET (self->spinner), TRUE);
  gtk_spinner_start (self->spinner);

  soup_session_send_async (
    session, req, G_PRIORITY_DEFAULT,
    NULL, send_finished, self);

  json_node_free (root);
  g_object_unref (jg);
  g_object_unref (jb);
  g_free (msg);
}

/* ───────── Open links (GTK-4) ───────── */

static void
open_uri (GtkWidget *w, const char *uri)
{
  GtkUriLauncher *l = gtk_uri_launcher_new (uri);
  GtkRoot *r = gtk_widget_get_root (w);
  GtkWindow *win = GTK_IS_WINDOW (r) ? GTK_WINDOW (r) : NULL;

  gtk_uri_launcher_launch (l, win, NULL, NULL, NULL);
  g_object_unref (l);
}

static void on_open_email    (AdwActionRow *r, gpointer u) { open_uri (GTK_WIDGET (r), "mailto:k.19.alokparnamitra@gmail.com"); }
static void on_open_phone    (AdwActionRow *r, gpointer u) { open_uri (GTK_WIDGET (r), "tel:+919647325707"); }
static void on_open_location (AdwActionRow *r, gpointer u) { open_uri (GTK_WIDGET (r), "geo:0,0?q=Kolkata,West Bengal,India"); }
static void on_open_github   (AdwActionRow *r, gpointer u) { open_uri (GTK_WIDGET (r), "https://github.com/Flamingo27"); }
static void on_open_linkedin (AdwActionRow *r, gpointer u) { open_uri (GTK_WIDGET (r), "https://www.linkedin.com/in/alokparna-mitra/"); }

/* ───────── Init / Class ───────── */

static void
portfolio_contact_page_init (PortfolioContactPage *self)
{
  GtkEventController *c;

  gtk_widget_init_template (GTK_WIDGET (self));

  self->email_suffix = gtk_label_new ("");
  gtk_widget_add_css_class (self->email_suffix, "caption");
  gtk_widget_set_visible (self->email_suffix, FALSE);
  adw_entry_row_add_suffix (self->email_entry, self->email_suffix);

  c = gtk_event_controller_key_new ();
  g_signal_connect (c, "key-pressed", G_CALLBACK (on_key_pressed), self);
  gtk_widget_add_controller (GTK_WIDGET (self->name_entry), c);

  c = gtk_event_controller_key_new ();
  g_signal_connect (c, "key-pressed", G_CALLBACK (on_key_pressed), self);
  gtk_widget_add_controller (GTK_WIDGET (self->email_entry), c);

  c = gtk_event_controller_key_new ();
  g_signal_connect (c, "key-pressed", G_CALLBACK (on_key_pressed), self);
  gtk_widget_add_controller (GTK_WIDGET (self->message_view), c);

  update_button_state (self);
}

static void
portfolio_contact_page_class_init (PortfolioContactPageClass *klass)
{
  GtkWidgetClass *wc = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (
    wc, "/org/alokparna/portfolio/gtk/portfolio-contact-page.ui");

  gtk_widget_class_bind_template_child (wc, PortfolioContactPage, name_entry);
  gtk_widget_class_bind_template_child (wc, PortfolioContactPage, email_entry);
  gtk_widget_class_bind_template_child (wc, PortfolioContactPage, message_view);
  gtk_widget_class_bind_template_child (wc, PortfolioContactPage, send_button);
  gtk_widget_class_bind_template_child (wc, PortfolioContactPage, spinner);
  gtk_widget_class_bind_template_child (wc, PortfolioContactPage, status_label);
  gtk_widget_class_bind_template_child (wc, PortfolioContactPage, status_revealer);

  gtk_widget_class_bind_template_callback (wc, on_changed);
  gtk_widget_class_bind_template_callback (wc, on_send_clicked);
  gtk_widget_class_bind_template_callback (wc, on_open_email);
  gtk_widget_class_bind_template_callback (wc, on_open_phone);
  gtk_widget_class_bind_template_callback (wc, on_open_location);
  gtk_widget_class_bind_template_callback (wc, on_open_github);
  gtk_widget_class_bind_template_callback (wc, on_open_linkedin);
}

GtkWidget *
portfolio_contact_page_new (void)
{
  return g_object_new (PORTFOLIO_TYPE_CONTACT_PAGE, NULL);
}
