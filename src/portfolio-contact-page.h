#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_CONTACT_PAGE (portfolio_contact_page_get_type())

G_DECLARE_FINAL_TYPE (
  PortfolioContactPage,
  portfolio_contact_page,
  PORTFOLIO,
  CONTACT_PAGE,
  AdwBin
)

GtkWidget *
portfolio_contact_page_new (void);

G_END_DECLS
