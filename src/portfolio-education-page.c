#include "config.h"
#include "portfolio-education-page.h"
#include "portfolio-education-row.h"
#include "portfolio-data.h"

struct _PortfolioEducationPage
{
  AdwBin parent_instance;

  GtkBox *education_rows_container;
};

G_DEFINE_FINAL_TYPE (PortfolioEducationPage, portfolio_education_page, ADW_TYPE_BIN)

static void
portfolio_education_page_class_init (PortfolioEducationPageClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (
    widget_class,
    "/org/alokparna/portfolio/gtk/portfolio-education-page.ui"
  );

  gtk_widget_class_bind_template_child (
    widget_class,
    PortfolioEducationPage,
    education_rows_container
  );
}

static void
portfolio_education_page_init (PortfolioEducationPage *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  for (gsize i = 0; i < num_education; i++) {
    PortfolioEducationRow *row = portfolio_education_row_new (&education[i]);
    gtk_box_append (self->education_rows_container, GTK_WIDGET (row));
  }
}
