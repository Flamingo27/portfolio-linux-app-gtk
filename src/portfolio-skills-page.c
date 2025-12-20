#include "config.h"

#include "portfolio-skills-page.h"
#include "portfolio-data.h"
#include "portfolio-skill-category-card.h"
#include "portfolio-additional-expertise-card.h"


struct _PortfolioSkillsPage
{
	AdwBin parent_instance;

    GtkFlowBox *skills_flowbox;
};

G_DEFINE_FINAL_TYPE (PortfolioSkillsPage, portfolio_skills_page, ADW_TYPE_BIN)

static void
portfolio_skills_page_class_init (PortfolioSkillsPageClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/org/alokparna/portfolio/gtk/portfolio-skills-page.ui");
    gtk_widget_class_bind_template_child (widget_class, PortfolioSkillsPage, skills_flowbox);
}

static void
portfolio_skills_page_init (PortfolioSkillsPage *self)
{
    GtkWidget *additional_expertise_card; // Moved declaration to the beginning
	gtk_widget_init_template (GTK_WIDGET (self));

    for (gsize i = 0; i < num_skill_categories; i++)
    {
        GtkWidget *card = GTK_WIDGET (portfolio_skill_category_card_new (&skill_categories[i]));
        gtk_flow_box_append (self->skills_flowbox, card);
    }
    
    // Add Additional Expertise Card
    additional_expertise_card = GTK_WIDGET (portfolio_additional_expertise_card_new ());
    gtk_flow_box_append (self->skills_flowbox, additional_expertise_card);
}