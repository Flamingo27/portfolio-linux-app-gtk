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

struct _PortfolioLinuxAppGtkWindow
{
	AdwApplicationWindow  parent_instance;

	/* Template widgets */
	GtkLabel            *label;
};

G_DEFINE_FINAL_TYPE (PortfolioLinuxAppGtkWindow, portfolio_linux_app_gtk_window, ADW_TYPE_APPLICATION_WINDOW)

static void
portfolio_linux_app_gtk_window_class_init (PortfolioLinuxAppGtkWindowClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/org/alokparna/portfolio/gtk/portfolio-linux-app-gtk-window.ui");
	gtk_widget_class_bind_template_child (widget_class, PortfolioLinuxAppGtkWindow, label);
}

static void
portfolio_linux_app_gtk_window_init (PortfolioLinuxAppGtkWindow *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));
}
