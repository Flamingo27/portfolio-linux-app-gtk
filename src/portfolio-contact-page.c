/* portfolio-contact-page.c
 * 
 * Contact page widget for the portfolio app. 
 */

#include "config.h"
#include "portfolio-contact-page.h"

#include <glib/gi18n.h>
#include <libsoup/soup.h>
#include <adwaita.h>
#include <adw-entry-row.h>

struct _PortfolioContactPage
{
	AdwBin parent_instance;

  AdwEntryRow *name_row;
  AdwEntryRow *email_row;
  AdwExpanderRow *message_row;
  GtkTextView *message_view;
  GtkButton *send_button;
  GtkSpinner *spinner;
  GtkLabel *status_label;
};

G_DEFINE_FINAL_TYPE (PortfolioContactPage, portfolio_contact_page, ADW_TYPE_BIN)

static void
portfolio_contact_page_class_init (PortfolioContactPageClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/org/alokparna/portfolio/gtk/portfolio-contact-page.ui");
  gtk_widget_class_bind_template_child_full (widget_class, "name_row", FALSE, G_STRUCT_OFFSET (PortfolioContactPage, name_row));
  gtk_widget_class_bind_template_child_full (widget_class, "email_row", FALSE, G_STRUCT_OFFSET (PortfolioContactPage, email_row));
  gtk_widget_class_bind_template_child_full (widget_class, "message_row", FALSE, G_STRUCT_OFFSET (PortfolioContactPage, message_row));
  gtk_widget_class_bind_template_child_full (widget_class, "message_view", FALSE, G_STRUCT_OFFSET (PortfolioContactPage, message_view));
  gtk_widget_class_bind_template_child_full (widget_class, "send_button", FALSE, G_STRUCT_OFFSET (PortfolioContactPage, send_button));
  gtk_widget_class_bind_template_child_full (widget_class, "spinner", FALSE, G_STRUCT_OFFSET (PortfolioContactPage, spinner));
  gtk_widget_class_bind_template_child_full (widget_class, "status_label", FALSE, G_STRUCT_OFFSET (PortfolioContactPage, status_label));
}

static void
reset_form (PortfolioContactPage *self)
{
  adw_entry_row_set_text (self->name_row, "");
  adw_entry_row_set_text (self->email_row, "");
  GtkTextBuffer *buffer = gtk_text_view_get_buffer (self->message_view);
  gtk_text_buffer_set_text (buffer, "", -1);
  gtk_widget_set_sensitive (GTK_WIDGET (self->send_button), TRUE);
  gtk_spinner_stop (self->spinner);
  gtk_widget_set_visible (GTK_WIDGET (self->spinner), FALSE);
  gtk_label_set_text (self->status_label, "");
}

static gboolean
reset_form_timeout (gpointer user_data)
{
  reset_form (user_data);
  return G_SOURCE_REMOVE;
}

static void
send_message_successful (PortfolioContactPage *self)
{
  gtk_spinner_stop(self->spinner);
  gtk_widget_set_visible(GTK_WIDGET(self->spinner), FALSE);
  gtk_label_set_text (self->status_label, "✅ Message sent! I'll get back to you soon.");
  g_timeout_add (3000, reset_form_timeout, self);
}

static void
send_message_failed (PortfolioContactPage *self)
{
  gtk_spinner_stop(self->spinner);
  gtk_widget_set_visible(GTK_WIDGET(self->spinner), FALSE);
  gtk_label_set_text (self->status_label, "❌ Something went wrong. Please try again later.");
  g_timeout_add (3000, reset_form_timeout, self);
}

static gboolean
is_email_valid (const char *email)
{
  // A simple email validation check. For a real world application,
  // a more robust validation is needed.
  return g_str_has_prefix (email, "") && g_strrstr(email, "@") && g_strrstr(email, ".");
}

static void
send_finish (GObject      *source_object,
             GAsyncResult *res,
             gpointer      user_data)
{
    PortfolioContactPage *self = PORTFOLIO_LINUX_APP_GTK_CONTACT_PAGE (user_data);
    GError *error = NULL;

    soup_session_send_finish (SOUP_SESSION (source_object), res, &error);

    if (error) {
        g_warning ("Failed to send message: %s", error->message);
        send_message_failed (self);
        g_error_free (error);
    } else {
        g_print ("Message sent successfully.\n");
        send_message_successful (self);
    }
}

static void
send_button_clicked (GtkButton *button, gpointer user_data)
{
  PortfolioContactPage *self = PORTFOLIO_LINUX_APP_GTK_CONTACT_PAGE (user_data);
  const char *name = adw_entry_row_get_text (self->name_row);
  const char *email = adw_entry_row_get_text (self->email_row);
  GtkTextBuffer *buffer = gtk_text_view_get_buffer (self->message_view);
  GtkTextIter start, end;
  gtk_text_buffer_get_start_iter (buffer, &start);
  gtk_text_buffer_get_end_iter (buffer, &end);
  char *message = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);

  if (g_str_equal (name, "") || g_str_equal (email, "") || g_str_equal (message, "")) {
    gtk_label_set_text (self->status_label, "Please fill all the fields.");
    g_free (message);
    return;
  }

  if (!is_email_valid(email)) {
    gtk_label_set_text (self->status_label, "Invalid email address.");
    g_free (message);
    return;
  }

  gtk_widget_set_sensitive (GTK_WIDGET (button), FALSE);
  gtk_widget_set_visible (GTK_WIDGET (self->spinner), TRUE);
  gtk_spinner_start (self->spinner);

  SoupSession *session = soup_session_new ();
  SoupMessage *soup_message = soup_message_new (SOUP_METHOD_POST, "https://portfolio-alokparna.pages.dev/contact");

  gchar *json_string = g_strdup_printf ("{\"name\":\"%s\",\"email\":\"%s\",\"message\":\"%s\"}", name, email, message);
  soup_message_set_request_body_from_bytes (soup_message, "application/json", g_bytes_new (json_string, strlen(json_string)));
  g_free (json_string);

  soup_session_send_async (session, soup_message, G_PRIORITY_DEFAULT, NULL, send_finish, self);
  g_free (message);
}

static void
portfolio_contact_page_init (PortfolioContactPage *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));
  g_signal_connect (self->send_button, "clicked", G_CALLBACK (send_button_clicked), self);
}
