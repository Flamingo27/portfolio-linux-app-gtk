#pragma once

#include <adwaita.h>
#include "portfolio-data.h"

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_PUBLICATION_CARD (portfolio_publication_card_get_type())

G_DECLARE_FINAL_TYPE (
  PortfolioPublicationCard,
  portfolio_publication_card,
  PORTFOLIO,
  PUBLICATION_CARD,
  AdwActionRow
)

GtkWidget *
portfolio_publication_card_new (const Publication *publication);

G_END_DECLS
