/* portfolio-linux-app-gtk-window.c
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "config.h"

#include "portfolio-linux-app-gtk-window.h"
#include "portfolio-hero-page.h"
#include "portfolio-about-page.h"
#include "portfolio-experience-page.h"
#include "portfolio-projects-page.h"
#include "portfolio-skills-page.h"
#include "portfolio-achievements-page.h"
#include "portfolio-contact-page.h"

#include <gtk/gtk.h>
#include <adwaita.h>

/* ─────────────────────────────────────────────── */

struct _PortfolioLinuxAppGtkWindow
{
  AdwApplicationWindow parent_instance;
};

G_DEFINE_FINAL_TYPE (
  PortfolioLinuxAppGtkWindow,
  portfolio_linux_app_gtk_window,
  ADW_TYPE_APPLICATION_WINDOW
)

/* ───────────────── Class Init ───────────────── */

static void
portfolio_linux_app_gtk_window_class_init (PortfolioLinuxAppGtkWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  /* Register all custom widgets BEFORE loading template */
  portfolio_hero_page_get_type ();
  portfolio_about_page_get_type ();
  portfolio_experience_page_get_type ();
  portfolio_projects_page_get_type ();
  portfolio_skills_page_get_type ();
  portfolio_achievements_page_get_type ();
  portfolio_contact_page_get_type ();

  gtk_widget_class_set_template_from_resource (
    widget_class,
    "/org/alokparna/portfolio/gtk/portfolio-linux-app-gtk-window.ui");
}

/* ───────────────── Instance Init ───────────────── */

static void
portfolio_linux_app_gtk_window_init (PortfolioLinuxAppGtkWindow *self)
{
  GtkCssProvider *provider;

  gtk_widget_init_template (GTK_WIDGET (self));

  /* Load application CSS */
  provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_resource (
    provider,
    "/org/alokparna/portfolio/gtk/style.css");

  gtk_style_context_add_provider_for_display (
    gdk_display_get_default (),
    GTK_STYLE_PROVIDER (provider),
    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  g_object_unref (provider);
}
