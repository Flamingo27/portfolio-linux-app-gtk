/* portfolio-experience-page.c
 *
 * Experience page widget for the portfolio app.
 */

#include "config.h"

#include "portfolio-experience-page.h"
#include "portfolio-data.h"
#include "portfolio-experience-card.h"

static const gchar *cura_highlights[] = {
  "Built the core web UI, logic flow, and early-stage AI-assisted modules.",
  "Designed and prototyped IoT-based emergency response features.",
  "Created pitch materials, documentation, and technical explanations for presentations.",
  "Launched the functional prototype — view the Live Demo.",
  "Published implementation details — refer to the TechMag Report for deeper insights.",
  NULL
};

static const gchar *iic_highlights[] = {
  "Developed solutions using Raspberry Pi and Arduino.",
  "Implemented MicroPython-based logic for IoT applications.",
  "Built early-stage healthcare device prototypes.",
  NULL
};

static const gchar *iete_highlights[] = {
  "Managed LinkedIn, Instagram, and Facebook brand accounts.",
  "Designed content strategy to boost engagement.",
  "Increased forum visibility and community reach.",
  NULL
};

static Experience experiences[] = {
  {
    .role = "Co-Founder",
    .company = "Cura Horizon",
    .duration = "2024 – Present",
    .description = "Developing an AI-integrated healthcare platform with hospital finder, emergency medicine assistance, and IoT device integration.",
    .highlights = cura_highlights,
    .links = NULL,
  },
  {
    .role = "Lab Intern",
    .company = "IIC, IIFR",
    .duration = "2024 – Present",
    .description = "Prototyped healthcare-focused hardware-software solutions using embedded systems and IoT development tools.",
    .highlights = iic_highlights,
    .links = NULL,
  },
  {
    .role = "Social Media Manager",
    .company = "IETE IEM Students' Forum",
    .duration = "2025 – Present",
    .description = "Managing digital presence and improving engagement across multiple social platforms.",
    .highlights = iete_highlights,
    .links = NULL,
  }
};

static Portfolio portfolio = {
  .experience = experiences,
  .n_experience = G_N_ELEMENTS (experiences)
};

struct _PortfolioExperiencePage
{
	AdwBin parent_instance;

  GtkListBox *experience_list_box;
};

G_DEFINE_FINAL_TYPE (PortfolioExperiencePage, portfolio_experience_page, ADW_TYPE_BIN)

static void
portfolio_experience_page_class_init (PortfolioExperiencePageClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/org/alokparna/portfolio/gtk/portfolio-experience-page.ui");
  gtk_widget_class_bind_template_child (widget_class, PortfolioExperiencePage, experience_list_box);
}

static void
portfolio_experience_page_init (PortfolioExperiencePage *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));

  experiences[0].links = g_hash_table_new (g_str_hash, g_str_equal);
  g_hash_table_insert (experiences[0].links, (gpointer)"demo", (gpointer)"https://cura-horizon-healthai.netlify.app/");
  g_hash_table_insert (experiences[0].links, (gpointer)"report", (gpointer)"https://drive.google.com/file/d/1jGCZQ3055R2RPwNjKay2eU8RVlV4QWUS/view?usp=drive_open");

  for (gsize i = 0; i < portfolio.n_experience; i++)
    {
      GtkWidget *card = GTK_WIDGET (portfolio_experience_card_new (&portfolio.experience[i]));
      gtk_list_box_append (self->experience_list_box, card);
      GtkListBoxRow *row = GTK_LIST_BOX_ROW (gtk_widget_get_parent (card));
      gtk_list_box_row_set_activatable (row, FALSE);
    }
}