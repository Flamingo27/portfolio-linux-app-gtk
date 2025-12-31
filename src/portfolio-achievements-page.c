#include "portfolio-achievements-page.h"
#include "portfolio-achievement-row.h"
#include "portfolio-data.h"

struct _PortfolioAchievementsPage {
  AdwBin parent_instance;
  AdwPreferencesGroup *group;
};

G_DEFINE_FINAL_TYPE (
  PortfolioAchievementsPage,
  portfolio_achievements_page,
  ADW_TYPE_BIN
)

static void
portfolio_achievements_page_class_init
  (PortfolioAchievementsPageClass *klass)
{
  GtkWidgetClass *wc = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (
    wc,
    "/org/alokparna/portfolio/gtk/portfolio-achievements-page.ui"
  );

  gtk_widget_class_bind_template_child (
    wc,
    PortfolioAchievementsPage,
    group
  );
}

static void
portfolio_achievements_page_init
  (PortfolioAchievementsPage *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  g_assert (ADW_IS_PREFERENCES_GROUP (self->group));

  for (gsize i = 0; i < num_achievements; i++) {
    GtkWidget *row =
      portfolio_achievement_row_new (&achievements[i]);

    /* ✅ CORRECT: pass GtkWidget* */
    adw_preferences_group_add (self->group, row);
  }
}

GtkWidget *
portfolio_achievements_page_new (void)
{
  return g_object_new (
    PORTFOLIO_TYPE_ACHIEVEMENTS_PAGE,
    NULL
  );
}
