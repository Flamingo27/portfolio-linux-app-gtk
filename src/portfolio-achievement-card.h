#pragma once

#include <adwaita.h>
#include "portfolio-data.h"

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_ACHIEVEMENT_CARD (portfolio_achievement_card_get_type ())
G_DECLARE_FINAL_TYPE (PortfolioAchievementCard, portfolio_achievement_card, PORTFOLIO, ACHIEVEMENT_CARD, AdwBin)

PortfolioAchievementCard *
portfolio_achievement_card_new (const Achievement *achievement);

G_END_DECLS
