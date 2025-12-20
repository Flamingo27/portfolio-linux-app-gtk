/* portfolio-experience-page.c
 *
 * Experience page widget for the portfolio app.
 */

#include "config.h"

#include "portfolio-experience-page.h"
#include "portfolio-data.h"
#include "portfolio-experience-card.h"


struct _PortfolioExperiencePage
{
	AdwBin parent_instance;

  GtkListBox *experience_list_box;
};

G_DEFINE_FINAL_TYPE (PortfolioExperiencePage, portfolio_experience_page, ADW_TYPE_BIN)

static void
portfolio_experience_page_class_init (PortfolioExperiencePageClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/org/alokparna/portfolio/gtk/portfolio-experience-page.ui");
  gtk_widget_class_bind_template_child (widget_class, PortfolioExperiencePage, experience_list_box);
}

static void
portfolio_experience_page_init (PortfolioExperiencePage *self)
{
  GtkListBoxRow *row; // Moved declaration to the beginning

	gtk_widget_init_template (GTK_WIDGET (self));

  for (gsize i = 0; i < num_experiences; i++)
    {
      GtkWidget *card = GTK_WIDGET (portfolio_experience_card_new (&experiences[i]));
      gtk_list_box_append (self->experience_list_box, card);
      row = GTK_LIST_BOX_ROW (gtk_widget_get_parent (card));
      gtk_list_box_row_set_activatable (row, FALSE);
    }
}