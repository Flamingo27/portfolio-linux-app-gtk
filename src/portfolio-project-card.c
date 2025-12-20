#include "config.h"

#include <gio/gio.h>
#include <glib/gi18n.h>

#include "portfolio-project-card.h"

struct _PortfolioProjectCard
{
  AdwBin parent_instance;

  const Project *project;

  GtkImage *project_image;
  GtkLabel *title_label;
  GtkLabel *subtitle_label;
  GtkLabel *description_label;
  GtkBox   *achievement_box;
  GtkLabel *achievement_label;
  GtkFlowBox *tech_flowbox;
  GtkBox   *links_box;
};

G_DEFINE_FINAL_TYPE (PortfolioProjectCard, portfolio_project_card, ADW_TYPE_BIN)

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
on_link_button_clicked (GtkButton *button,
                        gpointer   user_data)
{
  const gchar *url = user_data;
  if (url != NULL && strlen(url) > 0) {
      GtkRoot *root = gtk_widget_get_root (GTK_WIDGET (button));
      GtkUriLauncher *launcher = gtk_uri_launcher_new (url);
      gtk_uri_launcher_launch (launcher, GTK_WINDOW (root), NULL, on_uri_launched, NULL);
  } else {
      g_warning("Attempted to launch a NULL or empty URL.");
  }
}


static void
portfolio_project_card_class_init (PortfolioProjectCardClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/alokparna/portfolio/gtk/portfolio-project-card.ui");
  gtk_widget_class_bind_template_child (widget_class, PortfolioProjectCard, project_image);
  gtk_widget_class_bind_template_child (widget_class, PortfolioProjectCard, title_label);
  gtk_widget_class_bind_template_child (widget_class, PortfolioProjectCard, subtitle_label);
  gtk_widget_class_bind_template_child (widget_class, PortfolioProjectCard, description_label);
  gtk_widget_class_bind_template_child (widget_class, PortfolioProjectCard, achievement_box);
  gtk_widget_class_bind_template_child (widget_class, PortfolioProjectCard, achievement_label);
  gtk_widget_class_bind_template_child (widget_class, PortfolioProjectCard, tech_flowbox);
  gtk_widget_class_bind_template_child (widget_class, PortfolioProjectCard, links_box);
}

static void
portfolio_project_card_init (PortfolioProjectCard *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

PortfolioProjectCard *
portfolio_project_card_new (const Project *project)
{
  PortfolioProjectCard *self = g_object_new (PORTFOLIO_TYPE_PROJECT_CARD, NULL);

  self->project = project;

  // Set project image
  if (project->image != NULL) {
      gchar *image_path = g_strdup_printf("/org/alokparna/portfolio/gtk/%s.png", project->image); // Assuming .png for project images
      gtk_image_set_from_resource(self->project_image, image_path);
      g_free(image_path);
  }

  gtk_label_set_text (self->title_label, project->title);
  gtk_label_set_text (self->subtitle_label, project->subtitle);
  gtk_label_set_text (self->description_label, project->description);

  // Achievement
  if (project->achievement != NULL && strlen(project->achievement) > 0) {
      gtk_label_set_text (self->achievement_label, project->achievement);
      gtk_widget_set_visible(GTK_WIDGET(self->achievement_box), TRUE);
  } else {
      gtk_widget_set_visible(GTK_WIDGET(self->achievement_box), FALSE);
  }

  // Tech stack
  if (project->tech != NULL) {
      for (gsize i = 0; i < project->n_tech; i++) {
          GtkWidget *tech_label_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0); // Use GtkBox for padding/background
          gtk_widget_add_css_class(tech_label_box, "pill"); // Using a "pill" class for tech labels
          
          GtkWidget *tech_label = gtk_label_new(project->tech[i]);
          gtk_box_append(GTK_BOX(tech_label_box), tech_label);
          gtk_flow_box_append(self->tech_flowbox, tech_label_box);
      }
  }

  // Links
  if (project->links != NULL) {
      for (gsize i = 0; i < project->n_links; i++) {
          const ProjectLink *link = &project->links[i];
          GtkWidget *link_button = gtk_button_new();
          gtk_widget_set_tooltip_text(link_button, link->label);
          
          GtkWidget *icon_image = NULL;
          if (g_strcmp0(link->type, "demo") == 0) {
              icon_image = gtk_image_new_from_icon_name("go-next-symbolic"); // Equivalent to ArrowForward
          } else if (g_strcmp0(link->type, "drive") == 0) {
              icon_image = gtk_image_new_from_resource("/org/alokparna/portfolio/gtk/google_drive_logo.svg"); // Custom icon
          } else {
              icon_image = gtk_image_new_from_icon_name("dialog-information-symbolic"); // Equivalent to Info
          }
          gtk_image_set_pixel_size(GTK_IMAGE(icon_image), 24); // Size of 24.dp in Kotlin
          gtk_button_set_child(GTK_BUTTON(link_button), icon_image);

          g_signal_connect(link_button, "clicked", G_CALLBACK(on_link_button_clicked), (gpointer)link->url);
          gtk_box_append(self->links_box, link_button);
      }
  }

  return self;
}
