#include "portfolio-publication-page.h"
#include "portfolio-publication-card.h"
#include "portfolio-data.h"

struct _PortfolioPublicationPage {
  AdwBin parent_instance;
  AdwPreferencesGroup *group;
};

G_DEFINE_FINAL_TYPE (
  PortfolioPublicationPage,
  portfolio_publication_page,
  ADW_TYPE_BIN
)

static void
portfolio_publication_page_class_init
  (PortfolioPublicationPageClass *klass)
{
  GtkWidgetClass *wc = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (
    wc,
    "/org/alokparna/portfolio/gtk/portfolio-publication-page.ui"
  );

  gtk_widget_class_bind_template_child (
    wc,
    PortfolioPublicationPage,
    group
  );
}

static void
portfolio_publication_page_init
  (PortfolioPublicationPage *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));

  g_assert (ADW_IS_PREFERENCES_GROUP (self->group));

  for (gsize i = 0; i < num_publications; i++) {
    GtkWidget *card =
      portfolio_publication_card_new (&publications[i]);

    adw_preferences_group_add (self->group, card);
  }
}

GtkWidget *
portfolio_publication_page_new (void)
{
  return g_object_new (
    PORTFOLIO_TYPE_PUBLICATION_PAGE,
    NULL
  );
}
