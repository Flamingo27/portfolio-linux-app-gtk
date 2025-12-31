#include "config.h"

#include "portfolio-projects-page.h"
#include "portfolio-data.h"
#include "portfolio-project-card.h"

struct _PortfolioProjectsPage
{
  AdwBin parent_instance;
  AdwPreferencesGroup *projects_list_box;
};

G_DEFINE_FINAL_TYPE (
  PortfolioProjectsPage,
  portfolio_projects_page,
  ADW_TYPE_BIN
)

static void
portfolio_projects_page_class_init
  (PortfolioProjectsPageClass *klass)
{
  GtkWidgetClass *wc = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (
    wc,
    "/org/alokparna/portfolio/gtk/portfolio-projects-page.ui"
  );

  gtk_widget_class_bind_template_child (
    wc,
    PortfolioProjectsPage,
    projects_list_box
  );
}

static void
portfolio_projects_page_init
  (PortfolioProjectsPage *self)
{
  gsize i;

  gtk_widget_init_template (GTK_WIDGET (self));

  for (i = 0; i < num_projects; i++) {
    GtkWidget *card =
      GTK_WIDGET (portfolio_project_card_new (&projects[i]));

    adw_preferences_group_add (self->projects_list_box, card);
  }
}

PortfolioProjectsPage *
portfolio_projects_page_new (void)
{
  return g_object_new (
    PORTFOLIO_TYPE_PROJECTS_PAGE,
    NULL
  );
}
