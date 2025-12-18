/* portfolio-contact-page.h
 *
 * Contact page widget for the portfolio app.
 */

#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define PORTFOLIO_LINUX_APP_GTK_TYPE_CONTACT_PAGE (portfolio_contact_page_get_type())

G_DECLARE_FINAL_TYPE (PortfolioContactPage, portfolio_contact_page, PORTFOLIO_LINUX_APP_GTK, CONTACT_PAGE, AdwBin)

G_END_DECLS



