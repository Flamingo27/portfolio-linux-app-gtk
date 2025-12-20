#include "config.h"

#include <gio/gio.h>
#include <glib/gi18n.h>

#include "portfolio-achievement-card.h"

struct _PortfolioAchievementCard
{
  AdwBin parent_instance;

  const Achievement *achievement;

  GtkImage *icon_image;
  GtkLabel *title_label;
  GtkLabel *event_label;
  GtkLabel *description_label;
};

G_DEFINE_FINAL_TYPE (PortfolioAchievementCard, portfolio_achievement_card, ADW_TYPE_BIN)

static const gchar *
get_icon_name_for_achievement (const gchar *achievement_icon_name)
{
    if (g_strcmp0(achievement_icon_name, "Trophy") == 0) return "award-trophy-symbolic"; // Custom icon name, assuming it exists
    if (g_strcmp0(achievement_icon_name, "Award") == 0) return "award-award-symbolic"; // Custom icon name, assuming it exists
    if (g_strcmp0(achievement_icon_name, "Star") == 0) return "starred-symbolic"; // Standard Gtk icon
    return "starred-symbolic"; // Default or info icon
}

static void
portfolio_achievement_card_class_init (PortfolioAchievementCardClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/alokparna/portfolio/gtk/portfolio-achievement-card.ui");
  gtk_widget_class_bind_template_child (widget_class, PortfolioAchievementCard, icon_image);
  gtk_widget_class_bind_template_child (widget_class, PortfolioAchievementCard, title_label);
  gtk_widget_class_bind_template_child (widget_class, PortfolioAchievementCard, event_label);
  gtk_widget_class_bind_template_child (widget_class, PortfolioAchievementCard, description_label);
}

static void
portfolio_achievement_card_init (PortfolioAchievementCard *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

PortfolioAchievementCard *
portfolio_achievement_card_new (const Achievement *achievement)
{
  PortfolioAchievementCard *self = g_object_new (PORTFOLIO_TYPE_ACHIEVEMENT_CARD, NULL);

  self->achievement = achievement;

  // Set icon
  gtk_image_set_from_icon_name(self->icon_image, get_icon_name_for_achievement(achievement->icon));
  
  gtk_label_set_text (self->title_label, achievement->title);
  gtk_label_set_text (self->event_label, achievement->event);
  gtk_label_set_text (self->description_label, achievement->description);

  return self;
}
