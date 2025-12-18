/* portfolio-projects-page.c
 *
 * Projects page widget for the portfolio app.
 */

#include "config.h"

#include "portfolio-projects-page.h"

struct _PortfolioProjectsPage
{
	AdwBin parent_instance;
};

G_DEFINE_FINAL_TYPE (PortfolioProjectsPage, portfolio_projects_page, ADW_TYPE_BIN)

static void
portfolio_projects_page_class_init (PortfolioProjectsPageClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/com/alokparna/portfolio/gtk/portfolio-projects-page.ui");
}

static void
portfolio_projects_page_init (PortfolioProjectsPage *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));
}



