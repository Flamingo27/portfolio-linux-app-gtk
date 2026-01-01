#pragma once
#include <adwaita.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_EDUCATION_PAGE (portfolio_education_page_get_type())
G_DECLARE_FINAL_TYPE (
  PortfolioEducationPage,
  portfolio_education_page,
  PORTFOLIO,
  EDUCATION_PAGE,
  AdwBin
)

G_END_DECLS

