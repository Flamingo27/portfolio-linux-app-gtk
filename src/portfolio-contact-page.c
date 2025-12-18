/* portfolio-contact-page.c
 *
 * Contact page widget for the portfolio app.
 */

#include "config.h"

#include "portfolio-contact-page.h"

struct _PortfolioContactPage
{
	AdwBin parent_instance;
};

G_DEFINE_FINAL_TYPE (PortfolioContactPage, portfolio_contact_page, ADW_TYPE_BIN)

static void
portfolio_contact_page_class_init (PortfolioContactPageClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/com/alokparna/portfolio/gtk/portfolio-contact-page.ui");
}

static void
portfolio_contact_page_init (PortfolioContactPage *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));
}



