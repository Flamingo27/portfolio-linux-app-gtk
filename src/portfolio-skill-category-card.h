#pragma once

#include <adwaita.h>
#include "portfolio-data.h"

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_SKILL_CATEGORY_CARD (portfolio_skill_category_card_get_type ())
G_DECLARE_FINAL_TYPE (PortfolioSkillCategoryCard, portfolio_skill_category_card, PORTFOLIO, SKILL_CATEGORY_CARD, AdwBin)

PortfolioSkillCategoryCard *
portfolio_skill_category_card_new (const SkillCategory *skill_category);

G_END_DECLS
