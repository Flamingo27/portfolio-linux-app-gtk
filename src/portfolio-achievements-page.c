#include "portfolio-achievements-page.h"
#include "portfolio-achievement-row.h"
#include "portfolio-data.h"

struct _PortfolioAchievementsPage {
  AdwBin parent_instance;
  GtkListBox *rows_box;
};

/* 🔴 THIS WAS MISSING */
G_DEFINE_FINAL_TYPE (
  PortfolioAchievementsPage,
  portfolio_achievements_page,
  ADW_TYPE_BIN
)

/* 🔴 THIS WAS MISSING */
static void
portfolio_achievements_page_class_init (PortfolioAchievementsPageClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (
    widget_class,
    "/org/alokparna/portfolio/gtk/portfolio-achievements-page.ui");

  gtk_widget_class_bind_template_child (
    widget_class,
    PortfolioAchievementsPage,
    rows_box);
}

static void
portfolio_achievements_page_init (PortfolioAchievementsPage *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  for (gsize i = 0; i < num_achievements; i++) {
    GtkWidget *row =
      portfolio_achievement_row_new (&achievements[i]);
    gtk_list_box_append (self->rows_box, row);
  }
}
