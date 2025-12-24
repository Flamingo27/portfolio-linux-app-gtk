#include "config.h"
#include <glib/gi18n.h>

#include "portfolio-linux-app-gtk-application.h"
#include <adwaita.h>
#include "portfolio-data.h" // Added include

int
main (int   argc,
      char *argv[])
{
	g_autoptr(PortfolioLinuxAppGtkApplication) app = NULL;
	int ret;

	adw_init ();
	portfolio_data_init(); // Added initialization call

	bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);

	app = portfolio_linux_app_gtk_application_new ("org.alokparna.portfolio.gtk", G_APPLICATION_DEFAULT_FLAGS);
	ret = g_application_run (G_APPLICATION (app), argc, argv);

	portfolio_data_cleanup(); // Added cleanup call
	return ret;
}