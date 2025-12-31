#include "config.h"

#include "portfolio-linux-app-gtk-window.h"
#include "portfolio-hero-page.h"
#include "portfolio-about-page.h"
#include "portfolio-experience-page.h"
#include "portfolio-projects-page.h"
#include "portfolio-skills-page.h"
#include "portfolio-achievements-page.h"
#include "portfolio-publication-page.h"
#include "portfolio-contact-page.h"

#include <gtk/gtk.h>
#include <adwaita.h>

struct _PortfolioLinuxAppGtkWindow
{
  AdwApplicationWindow parent_instance;

  AdwNavigationView *nav_view;
  AdwNavigationPage *hero_page;
  AdwNavigationPage *main_page;

  GtkListBox   *nav_list;
  AdwViewStack *view_stack;
};

G_DEFINE_FINAL_TYPE (
  PortfolioLinuxAppGtkWindow,
  portfolio_linux_app_gtk_window,
  ADW_TYPE_APPLICATION_WINDOW
)

/* Sidebar → content switching */
static void
on_nav_row_selected (GtkListBox    *box,
                     GtkListBoxRow *row,
                     gpointer       user_data)
{
  PortfolioLinuxAppGtkWindow *self = user_data;
  AdwViewStackPage *page;
  GtkWidget *child;
  GListModel *pages;
  int index;

  if (!row)
    return;

  index = gtk_list_box_row_get_index (row);
  pages = G_LIST_MODEL (adw_view_stack_get_pages (self->view_stack));
  page = g_list_model_get_item (pages, index);

  if (!page)
    return;

  child = adw_view_stack_page_get_child (page);
  adw_view_stack_set_visible_child (self->view_stack, child);

  g_object_unref (page);
}

/* Hero → Main */
static void
on_hero_show_work (PortfolioHeroPage *hero,
                   gpointer           user_data)
{
  PortfolioLinuxAppGtkWindow *self = user_data;
  adw_navigation_view_push (self->nav_view, self->main_page);
}

/* Class init */
static void
portfolio_linux_app_gtk_window_class_init (PortfolioLinuxAppGtkWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  portfolio_hero_page_get_type ();
  portfolio_about_page_get_type ();
  portfolio_experience_page_get_type ();
  portfolio_projects_page_get_type ();
  portfolio_skills_page_get_type ();
  portfolio_achievements_page_get_type ();
  portfolio_publication_page_get_type ();
  portfolio_contact_page_get_type ();

  gtk_widget_class_set_template_from_resource (
    widget_class,
    "/org/alokparna/portfolio/gtk/portfolio-linux-app-gtk-window.ui");

  gtk_widget_class_bind_template_child (widget_class, PortfolioLinuxAppGtkWindow, nav_view);
  gtk_widget_class_bind_template_child (widget_class, PortfolioLinuxAppGtkWindow, hero_page);
  gtk_widget_class_bind_template_child (widget_class, PortfolioLinuxAppGtkWindow, main_page);
  gtk_widget_class_bind_template_child (widget_class, PortfolioLinuxAppGtkWindow, nav_list);
  gtk_widget_class_bind_template_child (widget_class, PortfolioLinuxAppGtkWindow, view_stack);
}

/* Instance init */
static void
portfolio_linux_app_gtk_window_init (PortfolioLinuxAppGtkWindow *self)
{
  GtkWidget *hero_child;
  GtkIconTheme *icon_theme;
  GdkDisplay *display;

  /* Ensure icon theme is set up (fallback in case app startup didn't work) */
  display = gtk_widget_get_display (GTK_WIDGET (self));
  if (display != NULL)
  {
    icon_theme = gtk_icon_theme_get_for_display (display);
    gtk_icon_theme_add_resource_path (icon_theme, "/org/alokparna/portfolio/gtk/icons");
  }

  gtk_widget_init_template (GTK_WIDGET (self));

  g_signal_connect (
    self->nav_list,
    "row-selected",
    G_CALLBACK (on_nav_row_selected),
    self);

  gtk_list_box_select_row (
    self->nav_list,
    gtk_list_box_get_row_at_index (self->nav_list, 0));

  hero_child = adw_navigation_page_get_child (self->hero_page);

  g_signal_connect (
    hero_child,
    "show-work",
    G_CALLBACK (on_hero_show_work),
    self);
}