#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_PUBLICATION_PAGE (portfolio_publication_page_get_type())

G_DECLARE_FINAL_TYPE (
  PortfolioPublicationPage,
  portfolio_publication_page,
  PORTFOLIO,
  PUBLICATION_PAGE,
  AdwBin
)

GtkWidget *portfolio_publication_page_new (void);

G_END_DECLS
