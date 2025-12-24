#include "config.h"
#include <gio/gio.h>
#include <glib/gi18n.h>

#include "portfolio-skill-category-card.h"

struct _PortfolioSkillCategoryCard
{
  AdwBin parent_instance;

  const SkillCategory *skill_category;

  GtkImage *icon_image;
  GtkLabel *title_label;
  GtkBox   *skills_box;
};

G_DEFINE_FINAL_TYPE (PortfolioSkillCategoryCard, portfolio_skill_category_card, ADW_TYPE_BIN)

static const gchar *
get_icon_name_for_skill (const gchar *skill_icon_name)
{
    if (g_strcmp0(skill_icon_name, "Code") == 0) return "applications-development-symbolic"; // Code icon
    if (g_strcmp0(skill_icon_name, "Layout") == 0) return "web-browser-symbolic"; // Web icon
    if (g_strcmp0(skill_icon_name, "Database") == 0) return "drive-harddisk-symbolic"; // Database icon
    if (g_strcmp0(skill_icon_name, "Cpu") == 0) return "cpu-symbolic"; // CPU icon
    if (g_strcmp0(skill_icon_name, "GitBranch") == 0) return "folder-sync-symbolic"; // Git branch or sync folder
    if (g_strcmp0(skill_icon_name, "Globe") == 0) return "network-wireless-symbolic"; // Globe or network icon
    return "starred-symbolic"; // Default or info icon
}

static void
portfolio_skill_category_card_class_init (PortfolioSkillCategoryCardClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/alokparna/portfolio/gtk/portfolio-skill-category-card.ui");
  gtk_widget_class_bind_template_child (widget_class, PortfolioSkillCategoryCard, icon_image);
  gtk_widget_class_bind_template_child (widget_class, PortfolioSkillCategoryCard, title_label);
  gtk_widget_class_bind_template_child (widget_class, PortfolioSkillCategoryCard, skills_box);
}

static void
portfolio_skill_category_card_init (PortfolioSkillCategoryCard *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

PortfolioSkillCategoryCard *
portfolio_skill_category_card_new (const SkillCategory *skill_category)
{
  PortfolioSkillCategoryCard *self = g_object_new (PORTFOLIO_TYPE_SKILL_CATEGORY_CARD, NULL);
  gsize i;
  GtkWidget *skill_row_box;
  GtkWidget *bullet;
  GtkWidget *skill_label;

  self->skill_category = skill_category;

  // Set icon
  gtk_image_set_from_icon_name(self->icon_image, get_icon_name_for_skill(skill_category->icon));
  gtk_label_set_text (self->title_label, skill_category->title);

  // Populate skills
  if (skill_category->skills != NULL) {
      for (i = 0; i < skill_category->n_skills; i++) {
          skill_row_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 12);
          gtk_widget_set_valign (skill_row_box, GTK_ALIGN_START);

          bullet = gtk_image_new_from_icon_name ("media-record-symbolic");
          gtk_widget_add_css_class (bullet, "accent");
          gtk_widget_set_valign (bullet, GTK_ALIGN_START);

          skill_label = gtk_label_new(skill_category->skills[i]);
          gtk_label_set_xalign (GTK_LABEL (skill_label), 0.0);
          gtk_label_set_wrap (GTK_LABEL (skill_label), TRUE);
          gtk_widget_set_valign (skill_label, GTK_ALIGN_START);

          gtk_box_append(GTK_BOX(skill_row_box), bullet);
          gtk_box_append(GTK_BOX(skill_row_box), skill_label);
          gtk_box_append(self->skills_box, skill_row_box);
      }
  }

  return self;
}