/* portfolio-experience-page.c
 *
 * Experience page widget for the portfolio app.
 */

#include "config.h"

#include "portfolio-experience-page.h"

struct _PortfolioExperiencePage
{
	AdwBin parent_instance;
};

G_DEFINE_FINAL_TYPE (PortfolioExperiencePage, portfolio_experience_page, ADW_TYPE_BIN)

static void
portfolio_experience_page_class_init (PortfolioExperiencePageClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/com/alokparna/portfolio/gtk/portfolio-experience-page.ui");
}

static void
portfolio_experience_page_init (PortfolioExperiencePage *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));
}



