#include "config.h"
#include <glib/gi18n.h>
#include <adwaita.h>

#include "portfolio-linux-app-gtk-application.h"
#include "portfolio-linux-app-gtk-window.h"

struct _PortfolioLinuxAppGtkApplication
{
	AdwApplication parent_instance;
};

G_DEFINE_FINAL_TYPE (PortfolioLinuxAppGtkApplication, portfolio_linux_app_gtk_application, ADW_TYPE_APPLICATION)

PortfolioLinuxAppGtkApplication *
portfolio_linux_app_gtk_application_new (const char        *application_id,
                                         GApplicationFlags  flags)
{
	g_return_val_if_fail (application_id != NULL, NULL);

	return g_object_new (PORTFOLIO_LINUX_APP_GTK_TYPE_APPLICATION,
	                     "application-id", application_id,
	                     "flags", flags,
	                     "resource-base-path", "/com/alokparna/portfolio/gtk",
	                     NULL);
}

static void
portfolio_linux_app_gtk_application_activate (GApplication *app)
{
	GtkWindow *window;

	g_assert (PORTFOLIO_LINUX_APP_GTK_IS_APPLICATION (app));

	window = gtk_application_get_active_window (GTK_APPLICATION (app));

	if (window == NULL)
		window = g_object_new (PORTFOLIO_LINUX_APP_GTK_TYPE_WINDOW,
		                       "application", app,
		                       NULL);

	gtk_window_present (window);
}

static void
portfolio_linux_app_gtk_application_class_init (PortfolioLinuxAppGtkApplicationClass *klass)
{
	GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

	app_class->activate = portfolio_linux_app_gtk_application_activate;
}

static void
portfolio_linux_app_gtk_application_about_action (GSimpleAction *action,
                                                  GVariant      *parameter,
                                                  gpointer       user_data)
{
	static const char *developers[] = {"Alokparna Mitra", NULL};
	PortfolioLinuxAppGtkApplication *self = user_data;
	GtkWindow *window = NULL;

	g_assert (PORTFOLIO_LINUX_APP_GTK_IS_APPLICATION (self));

	window = gtk_application_get_active_window (GTK_APPLICATION (self));

	adw_show_about_dialog (GTK_WIDGET (window),
	                       "application-name", "Alokparna Portfolio",
	                       "application-icon", "com.alokparna.portfolio.gtk",
	                       "developer-name", "Alokparna Mitra",
	                       "translator-credits", _("translator-credits"),
	                       "version", "0.1.0",
	                       "developers", developers,
	                       "copyright", "© 2025 Alokparna Mitra",
	                       NULL);
}

static void
portfolio_linux_app_gtk_application_quit_action (GSimpleAction *action,
                                                 GVariant      *parameter,
                                                 gpointer       user_data)
{
	PortfolioLinuxAppGtkApplication *self = user_data;

	g_assert (PORTFOLIO_LINUX_APP_GTK_IS_APPLICATION (self));

	g_application_quit (G_APPLICATION (self));
}

static const GActionEntry app_actions[] = {
	{ "quit", portfolio_linux_app_gtk_application_quit_action },
	{ "about", portfolio_linux_app_gtk_application_about_action },
};

static void
portfolio_linux_app_gtk_application_init (PortfolioLinuxAppGtkApplication *self)
{
    AdwStyleManager *style_manager;

	g_action_map_add_action_entries (G_ACTION_MAP (self),
	                                 app_actions,
	                                 G_N_ELEMENTS (app_actions),
	                                 self);
	gtk_application_set_accels_for_action (GTK_APPLICATION (self),
	                                       "app.quit",
	                                       (const char *[]) { "<control>q", NULL });

    style_manager = adw_style_manager_get_default ();
    adw_style_manager_set_color_scheme (style_manager, ADW_COLOR_SCHEME_PREFER_DARK);
}
