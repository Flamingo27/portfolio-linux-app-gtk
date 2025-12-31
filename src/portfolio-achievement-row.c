#include "portfolio-achievement-row.h"

struct _PortfolioAchievementRow {
  AdwActionRow parent_instance;
};

G_DEFINE_FINAL_TYPE (
  PortfolioAchievementRow,
  portfolio_achievement_row,
  ADW_TYPE_ACTION_ROW
)

static void
portfolio_achievement_row_class_init
  (PortfolioAchievementRowClass *klass)
{
}

static void
portfolio_achievement_row_init
  (PortfolioAchievementRow *self)
{
  /* Keep activatable for hover animation */
  g_object_set (self, "activatable", TRUE, NULL);
}

GtkWidget *
portfolio_achievement_row_new (const Achievement *a)
{
  PortfolioAchievementRow *self;
  GtkWidget *content;
  GtkWidget *title;
  GtkWidget *event;
  GtkWidget *description;

  self = g_object_new (
    PORTFOLIO_TYPE_ACHIEVEMENT_ROW,
    NULL
  );

  /* Content container with spacing + padding */
  content = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);
  gtk_widget_set_margin_top (content, 6);
  gtk_widget_set_margin_bottom (content, 6);
  gtk_widget_set_margin_start (content, 12);
  gtk_widget_set_margin_end (content, 12);

  /* Title */
  title = gtk_label_new (a->title);
  gtk_label_set_xalign (GTK_LABEL (title), 0.0);
  gtk_widget_add_css_class (title, "heading");

  /* Event */
  event = gtk_label_new (a->event);
  gtk_label_set_xalign (GTK_LABEL (event), 0.0);
  gtk_widget_add_css_class (event, "achievement-event");

  /* Description */
  description = gtk_label_new (a->description);
  gtk_label_set_wrap (GTK_LABEL (description), TRUE);
  gtk_label_set_xalign (GTK_LABEL (description), 0.0);
  gtk_widget_add_css_class (description, "dim-label");

  gtk_box_append (GTK_BOX (content), title);
  gtk_box_append (GTK_BOX (content), event);
  gtk_box_append (GTK_BOX (content), description);

  /* Attach content to row */
  adw_action_row_add_suffix (
    ADW_ACTION_ROW (self),
    content
  );

  return GTK_WIDGET (self);
}
