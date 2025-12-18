#include "hero-page.h"

struct _HeroPage {
    AdwBin parent_instance;
};

G_DEFINE_FINAL_TYPE (HeroPage, hero_page, ADW_TYPE_BIN)

static void
hero_page_class_init (HeroPageClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (
    widget_class,
    "/org/alokparna/portfolio/gtk/hero-page.ui"
  );
}

static void
hero_page_init (HeroPage *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

HeroPage *
hero_page_new (void)
{
    return g_object_new (HERO_TYPE_PAGE, NULL);
}

