/* portfolio-hero-page.c
 *
 * Hero page widget for the portfolio app.
 */

#include "config.h"

#include <gio/gio.h>
#include <glib/gi18n.h>

#include "portfolio-hero-page.h"

struct _PortfolioHeroPage
{
	AdwBin parent_instance;

	/* Template widgets */
	GtkButton *github_button;
	GtkButton *linkedin_button;
	GtkButton *view_work_button;
};

G_DEFINE_FINAL_TYPE (PortfolioHeroPage, portfolio_hero_page, ADW_TYPE_BIN)

enum {
	SHOW_WORK_SIGNAL,
	N_SIGNALS
};

static guint signals[N_SIGNALS];

static void
on_uri_launched (GObject      *source_object,
                 GAsyncResult *result,
                 gpointer      user_data)
{
	GtkUriLauncher *launcher = GTK_URI_LAUNCHER (source_object);
	GError *error = NULL;

	if (!gtk_uri_launcher_launch_finish (launcher, result, &error))
	{
		g_warning ("Failed to launch URI: %s", error->message);
		g_error_free (error);
	}

	g_object_unref (launcher);
}

static void
on_github_button_clicked (GtkButton *button,
                          gpointer   user_data)
{
	GtkRoot *root = gtk_widget_get_root (GTK_WIDGET (button));
	GtkUriLauncher *launcher = gtk_uri_launcher_new ("https://github.com/Flamingo27");
	gtk_uri_launcher_launch (launcher, GTK_WINDOW (root), NULL, on_uri_launched, NULL);
}

static void
on_linkedin_button_clicked (GtkButton *button,
                            gpointer   user_data)
{
	GtkRoot *root = gtk_widget_get_root (GTK_WIDGET (button));
	GtkUriLauncher *launcher = gtk_uri_launcher_new ("https://www.linkedin.com/in/alokparna-mitra/");
	gtk_uri_launcher_launch (launcher, GTK_WINDOW (root), NULL, on_uri_launched, NULL);
}

static void
on_view_work_button_clicked (PortfolioHeroPage *self,
                             GtkButton         *button)
{
	g_signal_emit (self, signals[SHOW_WORK_SIGNAL], 0);
}

static void
on_email_activated (AdwActionRow *row,
                    gpointer      user_data)
{
	GtkRoot *root = gtk_widget_get_root (GTK_WIDGET (row));
	GtkUriLauncher *launcher = gtk_uri_launcher_new ("mailto:k.19.alokparnamitra@gmail.com");
	gtk_uri_launcher_launch (launcher, GTK_WINDOW (root), NULL, on_uri_launched, NULL);
}

static void
on_phone_activated (AdwActionRow *row,
                    gpointer      user_data)
{
	GtkRoot *root = gtk_widget_get_root (GTK_WIDGET (row));
	GtkUriLauncher *launcher = gtk_uri_launcher_new ("tel:+919647325707");
	gtk_uri_launcher_launch (launcher, GTK_WINDOW (root), NULL, on_uri_launched, NULL);
}

static void
on_location_activated (AdwActionRow *row,
                       gpointer      user_data)
{
	GtkRoot *root = gtk_widget_get_root (GTK_WIDGET (row));
	GtkUriLauncher *launcher = gtk_uri_launcher_new ("geo:0,0?q=Kolkata,WB");
	gtk_uri_launcher_launch (launcher, GTK_WINDOW (root), NULL, on_uri_launched, NULL);
}

static void
portfolio_hero_page_class_init (PortfolioHeroPageClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/com/alokparna/portfolio/gtk/portfolio-hero-page.ui");
	gtk_widget_class_bind_template_callback (widget_class, on_github_button_clicked);
	gtk_widget_class_bind_template_callback (widget_class, on_linkedin_button_clicked);
	gtk_widget_class_bind_template_callback (widget_class, on_view_work_button_clicked);
	gtk_widget_class_bind_template_callback (widget_class, on_email_activated);
	gtk_widget_class_bind_template_callback (widget_class, on_phone_activated);
	gtk_widget_class_bind_template_callback (widget_class, on_location_activated);

	gtk_widget_class_bind_template_child (widget_class, PortfolioHeroPage, github_button);
	gtk_widget_class_bind_template_child (widget_class, PortfolioHeroPage, linkedin_button);
	gtk_widget_class_bind_template_child (widget_class, PortfolioHeroPage, view_work_button);

	signals[SHOW_WORK_SIGNAL] = g_signal_new ("show-work",
	                                          G_TYPE_FROM_CLASS (klass),
	                                          G_SIGNAL_RUN_LAST | G_SIGNAL_ACTION,
	                                          0,
	                                          NULL, NULL,
	                                          NULL,
	                                          G_TYPE_NONE, 0);
}

static void
portfolio_hero_page_init (PortfolioHeroPage *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));
}


