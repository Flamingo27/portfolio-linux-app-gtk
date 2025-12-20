#pragma once

#include <adwaita.h>
#include "portfolio-data.h"

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_EXPERIENCE_CARD (portfolio_experience_card_get_type())

G_DECLARE_FINAL_TYPE (PortfolioExperienceCard, portfolio_experience_card, PORTFOLIO, EXPERIENCE_CARD, AdwBin)

PortfolioExperienceCard *
portfolio_experience_card_new (const Experience *experience);

G_END_DECLS
