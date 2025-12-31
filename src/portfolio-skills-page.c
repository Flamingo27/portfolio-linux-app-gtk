#include "portfolio-skills-page.h"
#include "portfolio-data.h"

static const char *
icon_for_skill_category (const char *name)
{
  if (g_strcmp0 (name, "Programming Languages") == 0)
    return "puzzle-piece-symbolic";
  if (g_strcmp0 (name, "Frameworks & Tools") == 0)
    return "pocket-knife-symbolic";
  if (g_strcmp0 (name, "Databases") == 0)
    return "harddisk-symbolic";
  if (g_strcmp0 (name, "Platforms") == 0)
    return "phonelink-symbolic";

  return "star-symbolic";
}

struct _PortfolioSkillsPage {
  AdwBin parent_instance;
  AdwPreferencesGroup *skills_group;
};

G_DEFINE_FINAL_TYPE (
  PortfolioSkillsPage,
  portfolio_skills_page,
  ADW_TYPE_BIN
)

static void
portfolio_skills_page_class_init (PortfolioSkillsPageClass *klass)
{
  GtkWidgetClass *wc = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (
    wc,
    "/org/alokparna/portfolio/gtk/portfolio-skills-page.ui"
  );

  gtk_widget_class_bind_template_child (
    wc,
    PortfolioSkillsPage,
    skills_group
  );
}

static void
portfolio_skills_page_init (PortfolioSkillsPage *self)
{
  gsize i, j;

  gtk_widget_init_template (GTK_WIDGET (self));
  g_assert (ADW_IS_PREFERENCES_GROUP (self->skills_group));

  for (i = 0; i < num_skill_categories; i++) {
    const SkillCategory *cat;

    GtkWidget *row;
    GtkWidget *vbox;
    GtkWidget *header;
    GtkWidget *icon;
    GtkWidget *title;

    cat = &skill_categories[i];

    /* Row */
    row = adw_action_row_new ();
    g_object_set (row, "activatable", TRUE, NULL);

    /* Vertical content */
    vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 8);

    /* Header: icon + title */
    header = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 12);

    icon = gtk_image_new_from_icon_name (
      icon_for_skill_category (cat->title));
    gtk_widget_set_valign (icon, GTK_ALIGN_START);

    title = gtk_label_new (cat->title);
    gtk_label_set_xalign (GTK_LABEL (title), 0.0);
    gtk_widget_add_css_class (title, "heading");

    gtk_box_append (GTK_BOX (header), icon);
    gtk_box_append (GTK_BOX (header), title);
    gtk_box_append (GTK_BOX (vbox), header);

    /* Bullets BELOW heading */
    for (j = 0; j < cat->n_skills; j++) {
      GtkWidget *line;
      GtkWidget *dot;
      GtkWidget *text;

      line = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 8);
      dot  = gtk_label_new ("•");
      text = gtk_label_new (cat->skills[j]);

      gtk_label_set_xalign (GTK_LABEL (text), 0.0);
      gtk_label_set_wrap (GTK_LABEL (text), TRUE);
      gtk_widget_add_css_class (text, "dim-label");

      gtk_box_append (GTK_BOX (line), dot);
      gtk_box_append (GTK_BOX (line), text);
      gtk_box_append (GTK_BOX (vbox), line);
    }

    /* Padding */
    gtk_widget_set_margin_top (vbox, 10);
    gtk_widget_set_margin_bottom (vbox, 10);
    gtk_widget_set_margin_start (vbox, 12);
    gtk_widget_set_margin_end (vbox, 12);

    /* Put content inside row */
    gtk_list_box_row_set_child (
      GTK_LIST_BOX_ROW (row),
      vbox
    );

    adw_preferences_group_add (
      self->skills_group,
      row
    );
  }
}

PortfolioSkillsPage *
portfolio_skills_page_new (void)
{
  return g_object_new (
    PORTFOLIO_TYPE_SKILLS_PAGE,
    NULL
  );
}
