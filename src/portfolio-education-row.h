#pragma once
#include <adwaita.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_EDUCATION_ROW (portfolio_education_row_get_type())
G_DECLARE_FINAL_TYPE (
  PortfolioEducationRow,
  portfolio_education_row,
  PORTFOLIO,
  EDUCATION_ROW,
  AdwActionRow
)

PortfolioEducationRow *portfolio_education_row_new (
  const char *degree,
  const char *institute,
  const char *duration,
  const char *gpa
);

G_END_DECLS

