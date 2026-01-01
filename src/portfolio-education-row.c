#include "portfolio-education-row.h"

struct _PortfolioEducationRow {
  AdwActionRow parent_instance;

  GtkLabel *degree_label;
  GtkLabel *institute_label;
  GtkLabel *duration_label;
  GtkLabel *gpa_label;
};

G_DEFINE_TYPE (
  PortfolioEducationRow,
  portfolio_education_row,
  ADW_TYPE_ACTION_ROW
)

static void
portfolio_education_row_class_init (PortfolioEducationRowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (
    widget_class,
    "/org/alokparna/portfolio/gtk/portfolio-education-row.ui"
  );

  gtk_widget_class_bind_template_child (widget_class, PortfolioEducationRow, degree_label);
  gtk_widget_class_bind_template_child (widget_class, PortfolioEducationRow, institute_label);
  gtk_widget_class_bind_template_child (widget_class, PortfolioEducationRow, duration_label);
  gtk_widget_class_bind_template_child (widget_class, PortfolioEducationRow, gpa_label);
}

static void
portfolio_education_row_init (PortfolioEducationRow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

PortfolioEducationRow *
portfolio_education_row_new (
  const char *degree,
  const char *institute,
  const char *duration,
  const char *gpa
) {
  PortfolioEducationRow *row =
    g_object_new (PORTFOLIO_TYPE_EDUCATION_ROW, NULL);

  gtk_label_set_text (row->degree_label, degree);
  gtk_label_set_text (row->institute_label, institute);
  gtk_label_set_text (row->duration_label, duration);
  gtk_label_set_text (row->gpa_label, gpa);

  return row;
}

