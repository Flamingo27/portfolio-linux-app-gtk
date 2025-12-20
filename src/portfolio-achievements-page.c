#include "config.h"

#include "portfolio-achievements-page.h"
#include "portfolio-data.h"
#include "portfolio-achievement-card.h" // For AchievementCard widgets

// Achievement Data
static Achievement achievements_data[] = {
  {
    .title = "Top 5 Finalist",
    .event = "GDG HackBuild",
    .description = "UNICRED project recognized among top finalists at VIT Mumbai hackathon",
    .icon = "Trophy",
  },
  {
    .title = "Winner",
    .event = "Eureka Startup Pitch",
    .description = "Cura Horizon won first place in competitive startup pitch competition",
    .icon = "Award",
  },
  {
    .title = "Winner",
    .event = "IEMHEALS 2024",
    .description = "Selected among 289 international teams for healthcare innovation",
    .icon = "Star",
  }
};

static Portfolio portfolio = {
  .experience = NULL, // Handled in experience page
  .n_experience = 0,
  .projects = NULL, // Handled in projects page
  .n_projects = 0,
  .skills = NULL, // Handled in skills page
  .n_skills = 0,
  .interests = NULL, // Handled in skills page
  .n_interests = 0,
  .achievements = achievements_data,
  .n_achievements = G_N_ELEMENTS (achievements_data)
};


struct _PortfolioAchievementsPage
{
	AdwBin parent_instance;

    GtkFlowBox *achievements_flowbox;
};

G_DEFINE_FINAL_TYPE (PortfolioAchievementsPage, portfolio_achievements_page, ADW_TYPE_BIN)

static void
portfolio_achievements_page_class_init (PortfolioAchievementsPageClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	gtk_widget_class_set_template_from_resource (widget_class, "/org/alokparna/portfolio/gtk/portfolio-achievements-page.ui");
    gtk_widget_class_bind_template_child (widget_class, PortfolioAchievementsPage, achievements_flowbox);
}

static void
portfolio_achievements_page_init (PortfolioAchievementsPage *self)
{
	gtk_widget_init_template (GTK_WIDGET (self));

    for (gsize i = 0; i < portfolio.n_achievements; i++)
    {
        GtkWidget *card = GTK_WIDGET (portfolio_achievement_card_new (&portfolio.achievements[i]));
        gtk_flow_box_append (self->achievements_flowbox, card);
    }
}
