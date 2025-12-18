#include "about-page.h"

struct _AboutPage {
  AdwBin parent_instance;
};

G_DEFINE_FINAL_TYPE (AboutPage, about_page, ADW_TYPE_BIN)

static void
about_page_class_init (AboutPageClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (
    widget_class,
    "/org/alokparna/portfolio/gtk/about-page.ui"
  );
}

static void
about_page_init (AboutPage *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

AboutPage *
about_page_new (void)
{
  return g_object_new (ABOUT_TYPE_PAGE, NULL);
}


