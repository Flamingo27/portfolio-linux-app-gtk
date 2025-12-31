#include "config.h"
#include "portfolio-education-row.h"
#include "portfolio-data.h"

struct _PortfolioEducationRow
{
  AdwBin parent_instance;

  GtkImage *education_logo;
  GtkLabel *education_degree;
  GtkLabel *education_institution;
  GtkLabel *education_location;
  GtkLabel *education_duration;
  GtkLabel *education_score;
};

G_DEFINE_FINAL_TYPE (PortfolioEducationRow, portfolio_education_row, ADW_TYPE_BIN)

static void
portfolio_education_row_class_init (PortfolioEducationRowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (
    widget_class,
    "/org/alokparna/portfolio/gtk/portfolio-education-row.ui"
  );

  gtk_widget_class_bind_template_child (
    widget_class,
    PortfolioEducationRow,
    education_logo
  );
  gtk_widget_class_bind_template_child (
    widget_class,
    PortfolioEducationRow,
    education_degree
  );
  gtk_widget_class_bind_template_child (
    widget_class,
    PortfolioEducationRow,
    education_institution
  );
  gtk_widget_class_bind_template_child (
    widget_class,
    PortfolioEducationRow,
    education_location
  );
  gtk_widget_class_bind_template_child (
    widget_class,
    PortfolioEducationRow,
    education_duration
  );
  gtk_widget_class_bind_template_child (
    widget_class,
    PortfolioEducationRow,
    education_score
  );
}

static void
portfolio_education_row_init (PortfolioEducationRow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

PortfolioEducationRow *
portfolio_education_row_new (const Education *education_data)
{
  PortfolioEducationRow *row = g_object_new (PORTFOLIO_LINUX_APP_GTK_TYPE_EDUCATION_ROW, NULL);

  if (education_data->logo != NULL) {
    gtk_image_set_from_icon_name (row->education_logo, education_data->logo);
  }
  if (education_data->degree != NULL) {
    gtk_label_set_text (row->education_degree, education_data->degree);
  }
  if (education_data->institution != NULL) {
    gtk_label_set_text (row->education_institution, education_data->institution);
  }
  if (education_data->location != NULL) {
    gtk_label_set_text (row->education_location, education_data->location);
  }
  if (education_data->duration != NULL) {
    gtk_label_set_text (row->education_duration, education_data->duration);
  }
  if (education_data->score != NULL) {
    gtk_label_set_text (row->education_score, education_data->score);
  }

  // Apply highlight style if needed
  if (education_data->highlight) {
    GtkStyleContext *context = gtk_widget_get_style_context (GTK_WIDGET (row));
    gtk_style_context_add_class (context, "highlight"); // Assuming a 'highlight' CSS class exists
  }

  return row;
}