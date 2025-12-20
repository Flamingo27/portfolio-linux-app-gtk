#include "config.h"

#include "portfolio-projects-page.h"
#include "portfolio-data.h"
#include "portfolio-project-card.h" // For ProjectCard widgets


struct _PortfolioProjectsPage
{
	AdwBin parent_instance;

    GtkListBox *projects_list_box;
};

G_DEFINE_FINAL_TYPE (PortfolioProjectsPage, portfolio_projects_page, ADW_TYPE_BIN)

static void
portfolio_projects_page_class_init (PortfolioProjectsPageClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/org/alokparna/portfolio/gtk/portfolio-projects-page.ui");
    gtk_widget_class_bind_template_child (widget_class, PortfolioProjectsPage, projects_list_box);
}

static void
portfolio_projects_page_init (PortfolioProjectsPage *self)
{
    GtkListBoxRow *row; // Moved declaration to the very beginning

	gtk_widget_init_template (GTK_WIDGET (self));

    for (gsize i = 0; i < num_projects; i++)
    {
        GtkWidget *card = GTK_WIDGET (portfolio_project_card_new (&projects[i]));
        gtk_list_box_append (self->projects_list_box, card);
        row = GTK_LIST_BOX_ROW (gtk_widget_get_parent (card));
        gtk_list_box_row_set_activatable (row, FALSE);
    }
}