#include "config.h"

#include "portfolio-skills-page.h"
#include "portfolio-data.h"
#include "portfolio-skill-category-card.h"
#include "portfolio-additional-expertise-card.h"

// Skill Data
static const gchar *languages_skills[] = {"JavaScript", "Python", "Java", "C/C++", "HTML/CSS", NULL};
static const gchar *frontend_skills[] = {"React", "Responsive Design", "UI/UX", "Tailwind CSS", NULL};
static const gchar *backend_skills[] = {"Node.js", "REST APIs", "MySQL", "MongoDB", "PostgreSQL", NULL};
static const gchar *hardware_skills[] = {"Arduino", "Raspberry Pi", "MicroPython", "IoT Systems", NULL};
static const gchar *version_control_skills[] = {"Git", "GitHub", "Collaboration", NULL};
static const gchar *blockchain_skills[] = {"Solidity", "Smart Contracts", "Web3", NULL};

static SkillCategory skill_categories[] = {
  {
    .title = "Languages",
    .icon = "Code",
    .skills = languages_skills,
    .n_skills = G_N_ELEMENTS(languages_skills) - 1,
  },
  {
    .title = "Frontend",
    .icon = "Layout",
    .skills = frontend_skills,
    .n_skills = G_N_ELEMENTS(frontend_skills) - 1,
  },
  {
    .title = "Backend",
    .icon = "Database",
    .skills = backend_skills,
    .n_skills = G_N_ELEMENTS(backend_skills) - 1,
  },
  {
    .title = "Hardware/IoT",
    .icon = "Cpu",
    .skills = hardware_skills,
    .n_skills = G_N_ELEMENTS(hardware_skills) - 1,
  },
  {
    .title = "Version Control",
    .icon = "GitBranch",
    .skills = version_control_skills,
    .n_skills = G_N_ELEMENTS(version_control_skills) - 1,
  },
  {
    .title = "Blockchain",
    .icon = "Globe",
    .skills = blockchain_skills,
    .n_skills = G_N_ELEMENTS(blockchain_skills) - 1,
  }
};

static const gchar *interests_data[] = {"Full-Stack Development", "UI/UX", "Open-source Contributions", NULL};

static Portfolio portfolio = {
  .experience = NULL, // Handled in experience page
  .n_experience = 0,
  .projects = NULL, // Handled in projects page
  .n_projects = 0,
  .skills = skill_categories,
  .n_skills = G_N_ELEMENTS (skill_categories),
  .interests = interests_data,
  .n_interests = G_N_ELEMENTS (interests_data) - 1,
};


struct _PortfolioSkillsPage
{
	AdwBin parent_instance;

    GtkFlowBox *skills_flowbox;
};

G_DEFINE_FINAL_TYPE (PortfolioSkillsPage, portfolio_skills_page, ADW_TYPE_BIN)

static void
portfolio_skills_page_class_init (PortfolioSkillsPageClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/org/alokparna/portfolio/gtk/portfolio-skills-page.ui");
    gtk_widget_class_bind_template_child (widget_class, PortfolioSkillsPage, skills_flowbox);
}

static void
portfolio_skills_page_init (PortfolioSkillsPage *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));

    for (gsize i = 0; i < portfolio.n_skills; i++)
    {
        GtkWidget *card = GTK_WIDGET (portfolio_skill_category_card_new (&portfolio.skills[i]));
        gtk_flow_box_append (self->skills_flowbox, card);
    }
    
    // Add Additional Expertise Card
    GtkWidget *additional_expertise_card = GTK_WIDGET (portfolio_additional_expertise_card_new ());
    gtk_flow_box_append (self->skills_flowbox, additional_expertise_card);
}