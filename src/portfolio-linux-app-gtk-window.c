/* portfolio-linux-app-gtk-window.c
 *
 * Copyright 2025 Unknown
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
#include "portfolio-contact-page.h"

struct _PortfolioLinuxAppGtkWindow
{
	AdwApplicationWindow  parent_instance;

	/* Template widgets */
	AdwViewStack *view_stack;
	PortfolioHeroPage *hero_page;
};

G_DEFINE_FINAL_TYPE (PortfolioLinuxAppGtkWindow, portfolio_linux_app_gtk_window, ADW_TYPE_APPLICATION_WINDOW)

static void
on_hero_page_show_work (PortfolioHeroPage *hero_page,
                        PortfolioLinuxAppGtkWindow *self)
{
	/* Switch to About page by name */
	GtkWidget *about_child = adw_view_stack_get_child_by_name (self->view_stack, "about");
	if (about_child != NULL)
	{
		adw_view_stack_set_visible_child (self->view_stack, about_child);
	}
}

static void
portfolio_linux_app_gtk_window_class_init (PortfolioLinuxAppGtkWindowClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	/* Register custom page types before loading template */
	portfolio_hero_page_get_type ();
	portfolio_about_page_get_type ();
	portfolio_experience_page_get_type ();
	portfolio_projects_page_get_type ();
	portfolio_skills_page_get_type ();
	portfolio_contact_page_get_type ();

	gtk_widget_class_set_template_from_resource (widget_class, "/com/alokparna/portfolio/gtk/portfolio-linux-app-gtk-window.ui");
	gtk_widget_class_bind_template_child (widget_class, PortfolioLinuxAppGtkWindow, view_stack);
	gtk_widget_class_bind_template_child (widget_class, PortfolioLinuxAppGtkWindow, hero_page);
	gtk_widget_class_bind_template_callback (widget_class, on_hero_page_show_work);
}

static void
portfolio_linux_app_gtk_window_init (PortfolioLinuxAppGtkWindow *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));

	g_signal_connect (self->hero_page, "show-work", G_CALLBACK (on_hero_page_show_work), self);
}
