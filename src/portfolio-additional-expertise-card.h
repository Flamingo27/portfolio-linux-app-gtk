#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_ADDITIONAL_EXPERTISE_CARD (portfolio_additional_expertise_card_get_type ())
G_DECLARE_FINAL_TYPE (PortfolioAdditionalExpertiseCard, portfolio_additional_expertise_card, PORTFOLIO, ADDITIONAL_EXPERTISE_CARD, AdwBin)

PortfolioAdditionalExpertiseCard *
portfolio_additional_expertise_card_new (void);

G_END_DECLS
