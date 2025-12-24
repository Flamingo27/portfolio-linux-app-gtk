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

  /* Template widgets */
  AdwViewStack *view_stack;
  GtkListBox   *nav_list;
};

G_DEFINE_FINAL_TYPE (
  PortfolioLinuxAppGtkWindow,
  portfolio_linux_app_gtk_window,
  ADW_TYPE_APPLICATION_WINDOW
)

/* ───────────────── Sidebar → Page switch ───────────────── */

static void
on_nav_row_selected (GtkListBox    *box,
                     GtkListBoxRow *row,
                     gpointer       user_data)
{
  PortfolioLinuxAppGtkWindow *self = user_data;
  GtkSelectionModel *selection;
  GListModel *model;
  AdwViewStackPage *page;
  int index;

  if (!row)
    return;

  index = gtk_list_box_row_get_index (row);

  selection = adw_view_stack_get_pages (self->view_stack);
  model = G_LIST_MODEL (selection);

  page = g_list_model_get_item (model, index);
  if (!page)
    return;

  adw_view_stack_set_visible_child (
    self->view_stack,
    adw_view_stack_page_get_child (page));

  g_object_unref (page);
}

/* ───────────────── Class Init ───────────────── */

static void
portfolio_linux_app_gtk_window_class_init (PortfolioLinuxAppGtkWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  /* Register ALL custom widgets before template */
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

  gtk_widget_class_bind_template_child (
    widget_class,
    PortfolioLinuxAppGtkWindow,
    view_stack);

  gtk_widget_class_bind_template_child (
    widget_class,
    PortfolioLinuxAppGtkWindow,
    nav_list);
}

/* ───────────────── Instance Init ───────────────── */

static void
portfolio_linux_app_gtk_window_init (PortfolioLinuxAppGtkWindow *self)
{
  GtkCssProvider *provider;

  gtk_widget_init_template (GTK_WIDGET (self));

  /* Sidebar selection handler */
  g_signal_connect (
    self->nav_list,
    "row-selected",
    G_CALLBACK (on_nav_row_selected),
    self);

  /* Select first row by default */
  gtk_list_box_select_row (
    self->nav_list,
    gtk_list_box_get_row_at_index (self->nav_list, 0));

  /* Load app CSS */
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

