#include "config.h"

#include "portfolio-projects-page.h"
#include "portfolio-data.h"
#include "portfolio-project-card.h" // For ProjectCard widgets

// Project Data
static const gchar *unicred_tech[] = {"React", "Node.js", "Kotlin", "PostgreSQL", "Solidity", NULL};
static const ProjectLink unicred_links[] = {
    {"Live Demo", "https://unicred-portal.debarghaya.in", "demo"},
    {"Project Drive Folder", "https://drive.google.com/drive/folders/1K-i6kuuBj0G23VyYOGL7jthsgrd2gHMd", "drive"}
};
static const gchar *irrigation_tech[] = {"Arduino UNO", "Soil Moisture Sensor", "Embedded C", "IoT Logic", NULL};
static const gchar *stocks_tech[] = {"React", "Node.js", "MySQL", "REST APIs", NULL};
static const gchar *assistive_tech[] = {"Raspberry Pi", "Python", "IoT", "UI/UX", NULL};
static const ProjectLink assistive_links[] = {
    {"Live Demo", "https://dem-sim.netlify.app", "demo"}
};


static Project projects[] = {
  {
    .title = "UNICRED",
    .subtitle = "Blockchain Credential Verification System",
    .description = "Developed secure credential verification portal with frontend workflows and integration pipelines using blockchain technology.",
    .tech = unicred_tech,
    .n_tech = G_N_ELEMENTS(unicred_tech) - 1, // Exclude NULL terminator
    .achievement = "Top 5 Finalist at GDG HackBuild, VIT Mumbai",
    .links = unicred_links,
    .n_links = G_N_ELEMENTS(unicred_links),
    .image = "project_unicred",
  },
  {
    .title = "Smart Irrigation System",
    .subtitle = "Arduino UNO Based Automated Irrigation",
    .description = "Designed a sensor-based irrigation automation system using soil moisture sensing and microcontroller logic. The system intelligently controls water flow to optimize plant hydration and reduce water waste.",
    .tech = irrigation_tech,
    .n_tech = G_N_ELEMENTS(irrigation_tech) - 1,
    .achievement = "", // Empty achievement
    .links = NULL, // No links
    .n_links = 0,
    .image = "project_irrigation",
  },
  {
    .title = "Smart Stocks",
    .subtitle = "Automated Inventory Management",
    .description = "Built responsive inventory automation system with product listing, search, and stock updates to reduce manual errors.",
    .tech = stocks_tech,
    .n_tech = G_N_ELEMENTS(stocks_tech) - 1,
    .achievement = "",
    .links = NULL,
    .n_links = 0,
    .image = "project_stocks",
  },
  {
    .title = "Assistive Healthcare Devices",
    .subtitle = "Alzheimer's Glass & Accu-Pressure Glove",
    .description = "Created innovative healthcare devices with audio/video assistance and accessible UI/UX using Raspberry Pi.",
    .tech = assistive_tech,
    .n_tech = G_N_ELEMENTS(assistive_tech) - 1,
    .achievement = "",
    .links = assistive_links,
    .n_links = G_N_ELEMENTS(assistive_links),
    .image = "project_assistive",
  }
};

static Portfolio portfolio = {
  .experience = NULL, // Experience data is in portfolio-experience-page.c
  .n_experience = 0,
  .projects = projects,
  .n_projects = G_N_ELEMENTS (projects)
};


struct _PortfolioProjectsPage
{
	AdwBin parent_instance;

    GtkListBox *projects_list_box;
};

G_DEFINE_FINAL_TYPE (PortfolioProjectsPage, portfolio_projects_page, ADW_TYPE_BIN)

static void
portfolio_projects_page_class_init (PortfolioProjectsPageClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/org/alokparna/portfolio/gtk/portfolio-projects-page.ui");
    gtk_widget_class_bind_template_child (widget_class, PortfolioProjectsPage, projects_list_box);
}

static void
portfolio_projects_page_init (PortfolioProjectsPage *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));

    for (gsize i = 0; i < portfolio.n_projects; i++)
    {
        GtkWidget *card = GTK_WIDGET (portfolio_project_card_new (&portfolio.projects[i]));
        gtk_list_box_append (self->projects_list_box, card);
        GtkListBoxRow *row = GTK_LIST_BOX_ROW (gtk_widget_get_parent (card));
        gtk_list_box_row_set_activatable (row, FALSE);
    }
}