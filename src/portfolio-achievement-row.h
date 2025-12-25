#pragma once

#include <adwaita.h>
#include "portfolio-data.h"

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_ACHIEVEMENT_ROW \
  (portfolio_achievement_row_get_type())

G_DECLARE_FINAL_TYPE (
  PortfolioAchievementRow,
  portfolio_achievement_row,
  PORTFOLIO,
  ACHIEVEMENT_ROW,
  AdwActionRow
)

GtkWidget *
portfolio_achievement_row_new (const Achievement *achievement);

G_END_DECLS
