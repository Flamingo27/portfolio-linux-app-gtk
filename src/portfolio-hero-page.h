/* portfolio-hero-page.h
 *
 * Hero page widget for the portfolio app.
 */

#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define PORTFOLIO_LINUX_APP_GTK_TYPE_HERO_PAGE (portfolio_hero_page_get_type())

G_DECLARE_FINAL_TYPE (PortfolioHeroPage, portfolio_hero_page, PORTFOLIO_LINUX_APP_GTK, HERO_PAGE, AdwBin)

G_END_DECLS



