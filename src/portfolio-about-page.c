#include "config.h"
#include "portfolio-about-page.h"

struct _PortfolioAboutPage
{
  AdwBin parent_instance;
  AdwAvatar *profile_avatar;
};

G_DEFINE_FINAL_TYPE (PortfolioAboutPage, portfolio_about_page, ADW_TYPE_BIN)

static void
portfolio_about_page_class_init (PortfolioAboutPageClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (
    widget_class,
    "/org/alokparna/portfolio/gtk/portfolio-about-page.ui"
  );

  gtk_widget_class_bind_template_child (
    widget_class,
    PortfolioAboutPage,
    profile_avatar
  );
}

static void
portfolio_about_page_init (PortfolioAboutPage *self)
{
  GdkTexture   *texture;
  GdkPaintable *paintable;

  gtk_widget_init_template (GTK_WIDGET (self));

  texture = gdk_texture_new_from_resource (
    "/org/alokparna/portfolio/gtk/alokparna_speaking.png"
  );

  paintable = GDK_PAINTABLE (texture);

  adw_avatar_set_custom_image (self->profile_avatar, paintable);
}


