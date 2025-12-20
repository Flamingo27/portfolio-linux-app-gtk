#include "config.h"

#include "portfolio-experience-card.h"

struct _PortfolioExperienceCard
{
  AdwBin parent_instance;

  const Experience *experience;

  GtkLabel *role_label;
  GtkLabel *company_label;
  GtkLabel *duration_label;
  GtkLabel *description_label;
  GtkBox *highlights_box;
};

G_DEFINE_FINAL_TYPE (PortfolioExperienceCard, portfolio_experience_card, ADW_TYPE_BIN)

static void
portfolio_experience_card_class_init (PortfolioExperienceCardClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/alokparna/portfolio/gtk/portfolio-experience-card.ui");
  gtk_widget_class_bind_template_child (widget_class, PortfolioExperienceCard, role_label);
  gtk_widget_class_bind_template_child (widget_class, PortfolioExperienceCard, company_label);
  gtk_widget_class_bind_template_child (widget_class, PortfolioExperienceCard, duration_label);
  gtk_widget_class_bind_template_child (widget_class, PortfolioExperienceCard, description_label);
  gtk_widget_class_bind_template_child (widget_class, PortfolioExperienceCard, highlights_box);
}

static void
portfolio_experience_card_init (PortfolioExperienceCard *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

static void
add_highlight (PortfolioExperienceCard *self,
               const gchar             *highlight_text)
{
  GtkWidget *box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 12);
  gtk_widget_set_valign (GTK_WIDGET (box), GTK_ALIGN_START);
  GtkWidget *bullet = gtk_image_new_from_icon_name ("media-record-symbolic");
  gtk_widget_add_css_class (bullet, "accent");
  gtk_widget_set_valign (bullet, GTK_ALIGN_START); // Align bullet to start

  GtkWidget *label = gtk_label_new (NULL);
  gtk_label_set_wrap (GTK_LABEL (label), TRUE);
  gtk_label_set_xalign (GTK_LABEL (label), 0.0);
  gtk_widget_set_valign (label, GTK_ALIGN_START); // Align label to start

  gchar *markup = g_strdup (highlight_text); // Start with a mutable copy

  // Handle "Live Demo" link
  const gchar *demo_phrase = "Live Demo";
  if (self->experience->links) {
    gchar *link_url = g_hash_table_lookup (self->experience->links, "demo");
    if (link_url) {
      gchar *found_demo = strstr (markup, demo_phrase);
      if (found_demo) {
        gchar *temp_markup = g_strdup_printf ("%.*s<a href=\"%s\">%s</a>%s",
                                             (int)(found_demo - markup), markup,
                                             link_url, demo_phrase,
                                             found_demo + strlen(demo_phrase));
        g_free (markup);
        markup = temp_markup;
      }
    }
  }

  // Handle "TechMag Report" link
  const gchar *report_phrase = "TechMag Report";
  if (self->experience->links) {
    gchar *link_url = g_hash_table_lookup (self->experience->links, "report");
    if (link_url) {
      gchar *found_report = strstr (markup, report_phrase);
      if (found_report) {
        gchar *temp_markup = g_strdup_printf ("%.*s<a href=\"%s\">%s</a>%s",
                                             (int)(found_report - markup), markup,
                                             link_url, report_phrase,
                                             found_report + strlen(report_phrase));
        g_free (markup);
        markup = temp_markup;
      }
    }
  }

  // Set markup or text
  if (strstr(markup, "<a href=")) { // Check if any link was actually embedded
    gtk_label_set_markup (GTK_LABEL (label), markup);
  } else {
    gtk_label_set_text (GTK_LABEL (label), markup);
  }
  g_free (markup);

  gtk_box_append (GTK_BOX (box), bullet);
  gtk_box_append (GTK_BOX (box), label);

  gtk_box_append (self->highlights_box, box);
}

PortfolioExperienceCard *
portfolio_experience_card_new (const Experience *experience)
{
  PortfolioExperienceCard *self = g_object_new (PORTFOLIO_TYPE_EXPERIENCE_CARD, NULL);

  self->experience = experience;

  gtk_label_set_text (self->role_label, experience->role);
  gtk_label_set_text (self->company_label, experience->company);
  gtk_label_set_text (self->duration_label, experience->duration);
  gtk_label_set_text (self->description_label, experience->description);

  if (experience->highlights)
    {
      for (int i = 0; experience->highlights[i]; i++)
        {
          add_highlight (self, experience->highlights[i]);
        }
    }

  return self;
}
