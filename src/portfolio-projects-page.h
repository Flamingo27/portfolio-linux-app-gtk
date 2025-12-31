#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_PROJECTS_PAGE \
  (portfolio_projects_page_get_type())

G_DECLARE_FINAL_TYPE (
  PortfolioProjectsPage,
  portfolio_projects_page,
  PORTFOLIO,
  PROJECTS_PAGE,
  AdwBin
)

PortfolioProjectsPage *
portfolio_projects_page_new (void);

G_END_DECLS
