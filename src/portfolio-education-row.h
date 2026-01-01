#pragma once

#include <adwaita.h>
#include "portfolio-data.h"

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_EDUCATION_ROW (portfolio_education_row_get_type())

G_DECLARE_FINAL_TYPE (
  PortfolioEducationRow,
  portfolio_education_row,
  PORTFOLIO,
  EDUCATION_ROW,
  AdwActionRow
)

PortfolioEducationRow *
portfolio_education_row_new (const Education *edu);

G_END_DECLS
