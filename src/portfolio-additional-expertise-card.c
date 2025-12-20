#include "config.h"

#include <gio/gio.h>
#include <glib/gi18n.h>

#include "portfolio-additional-expertise-card.h"

struct _PortfolioAdditionalExpertiseCard
{
  AdwBin parent_instance;

};

G_DEFINE_FINAL_TYPE (PortfolioAdditionalExpertiseCard, portfolio_additional_expertise_card, ADW_TYPE_BIN)

static void
portfolio_additional_expertise_card_class_init (PortfolioAdditionalExpertiseCardClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/alokparna/portfolio/gtk/portfolio-additional-expertise-card.ui");
}

static void
portfolio_additional_expertise_card_init (PortfolioAdditionalExpertiseCard *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

PortfolioAdditionalExpertiseCard *
portfolio_additional_expertise_card_new (void)
{
  return g_object_new (PORTFOLIO_TYPE_ADDITIONAL_EXPERTISE_CARD, NULL);
}
