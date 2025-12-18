/* portfolio-skills-page.c
 *
 * Skills page widget for the portfolio app.
 */

#include "config.h"

#include "portfolio-skills-page.h"

struct _PortfolioSkillsPage
{
	AdwBin parent_instance;
};

G_DEFINE_FINAL_TYPE (PortfolioSkillsPage, portfolio_skills_page, ADW_TYPE_BIN)

static void
portfolio_skills_page_class_init (PortfolioSkillsPageClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/com/alokparna/portfolio/gtk/portfolio-skills-page.ui");
}

static void
portfolio_skills_page_init (PortfolioSkillsPage *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));
}



