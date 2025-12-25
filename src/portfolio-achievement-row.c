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
portfolio_achievement_row_class_init (PortfolioAchievementRowClass *klass)
{
}

static void
portfolio_achievement_row_init (PortfolioAchievementRow *self)
{
}

GtkWidget *
portfolio_achievement_row_new (const Achievement *a)
{
  PortfolioAchievementRow *row =
    g_object_new (PORTFOLIO_TYPE_ACHIEVEMENT_ROW, NULL);

  g_object_set (row,
                "title", a->title,
                "subtitle", a->event,
                NULL);

  return GTK_WIDGET (row);
}
