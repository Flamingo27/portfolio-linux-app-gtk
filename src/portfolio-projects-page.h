/* portfolio-projects-page.h
 *
 * Projects page widget for the portfolio app.
 */

#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define PORTFOLIO_LINUX_APP_GTK_TYPE_PROJECTS_PAGE (portfolio_projects_page_get_type())

G_DECLARE_FINAL_TYPE (PortfolioProjectsPage, portfolio_projects_page, PORTFOLIO_LINUX_APP_GTK, PROJECTS_PAGE, AdwBin)

G_END_DECLS



