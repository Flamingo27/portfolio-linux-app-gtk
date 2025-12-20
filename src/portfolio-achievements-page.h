#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_ACHIEVEMENTS_PAGE (portfolio_achievements_page_get_type ())
G_DECLARE_FINAL_TYPE (PortfolioAchievementsPage, portfolio_achievements_page, PORTFOLIO, ACHIEVEMENTS_PAGE, AdwBin)

PortfolioAchievementsPage *
portfolio_achievements_page_new (void);

G_END_DECLS
