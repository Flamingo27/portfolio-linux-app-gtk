#pragma once

#include <adwaita.h>
#include "portfolio-data.h"

G_BEGIN_DECLS

#define PORTFOLIO_LINUX_APP_GTK_TYPE_EDUCATION_ROW (portfolio_education_row_get_type())

G_DECLARE_FINAL_TYPE (PortfolioEducationRow, portfolio_education_row, PORTFOLIO_LINUX_APP_GTK, EDUCATION_ROW, AdwBin)

PortfolioEducationRow *
portfolio_education_row_new (const Education *education_data);

G_END_DECLS
