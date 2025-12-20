#pragma once

#include <adwaita.h>
#include "portfolio-data.h"

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_PROJECT_CARD (portfolio_project_card_get_type ())
G_DECLARE_FINAL_TYPE (PortfolioProjectCard, portfolio_project_card, PORTFOLIO, PROJECT_CARD, AdwBin)

PortfolioProjectCard *
portfolio_project_card_new (const Project *project);

G_END_DECLS
