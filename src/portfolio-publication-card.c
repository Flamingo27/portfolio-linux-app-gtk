#include "portfolio-publication-card.h"

struct _PortfolioPublicationCard {
  AdwActionRow parent_instance;
};

G_DEFINE_FINAL_TYPE (
  PortfolioPublicationCard,
  portfolio_publication_card,
  ADW_TYPE_ACTION_ROW
)

static void
on_open_url (GtkGestureClick *gesture,
             int              n_press,
             double           x,
             double           y,
             gpointer         user_data)
{
  const gchar *url = user_data;
  GtkUriLauncher *launcher = gtk_uri_launcher_new (url);

  gtk_uri_launcher_launch (launcher, NULL, NULL, NULL, NULL);
  g_object_unref(launcher);
}

static void
portfolio_publication_card_class_init (PortfolioPublicationCardClass *klass)
{
}

static void
portfolio_publication_card_init (PortfolioPublicationCard *self)
{
  g_object_set (self, "activatable", TRUE, NULL);
}

GtkWidget *
portfolio_publication_card_new (const Publication *publication)
{
  PortfolioPublicationCard *self;
  GtkWidget *content;
  GtkWidget *title;
  GtkWidget *type;
  GtkWidget *description;
  GtkGesture *click;
  GtkWidget *icon;

  self = g_object_new (PORTFOLIO_TYPE_PUBLICATION_CARD, NULL);

  content = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);
  gtk_widget_set_margin_top (content, 6);
  gtk_widget_set_margin_bottom (content, 6);
  gtk_widget_set_margin_start (content, 12);
  gtk_widget_set_margin_end (content, 12);

  title = gtk_label_new (publication->title);
  gtk_label_set_xalign (GTK_LABEL (title), 0.0);
  gtk_widget_add_css_class (title, "heading");

  type = gtk_label_new (publication->type);
  gtk_label_set_xalign (GTK_LABEL (type), 0.0);
  gtk_widget_add_css_class (type, "accent");

  description = gtk_label_new (publication->description);
  gtk_label_set_wrap (GTK_LABEL (description), TRUE);
  gtk_label_set_xalign (GTK_LABEL (description), 0.0);
  gtk_widget_add_css_class (description, "dim-label");

  gtk_box_append (GTK_BOX (content), title);
  gtk_box_append (GTK_BOX (content), type);
  gtk_box_append (GTK_BOX (content), description);

  adw_action_row_add_suffix (ADW_ACTION_ROW (self), content);
  
  icon = gtk_image_new_from_icon_name (publication->icon);
  gtk_widget_set_valign(icon, GTK_ALIGN_START);
  adw_action_row_add_prefix (ADW_ACTION_ROW (self), icon);


  click = gtk_gesture_click_new ();
  g_signal_connect (click, "released", G_CALLBACK (on_open_url), (gpointer)publication->url);
  gtk_widget_add_controller (GTK_WIDGET (self), GTK_EVENT_CONTROLLER (click));

  return GTK_WIDGET (self);
}