#pragma once

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

typedef struct _Experience Experience;
typedef struct _ProjectLink ProjectLink;
typedef struct _Project Project;
typedef struct _SkillCategory SkillCategory;
typedef struct _Achievement Achievement;

/* ───────── Experience ───────── */

struct _Experience {
  const gchar *role;
  const gchar *company;
  const gchar *duration;
  const gchar *description;
  const gchar *location;
  const gchar **highlights;
  GHashTable *links;
};

extern Experience experiences[];
extern const gsize num_experiences;

/* ───────── Projects ───────── */

struct _ProjectLink {
  const gchar *label;
  const gchar *url;
  const gchar *type;
};

struct _Project {
  const gchar *title;
  const gchar *subtitle;
  const gchar *description;
  const gchar **tech;
  gsize n_tech;
  const gchar *achievement;
  const ProjectLink *links;
  gsize n_links;
  const gchar *image;
};

extern const Project projects[];
extern const gsize num_projects;

/* ───────── Skills ───────── */

struct _SkillCategory {
  const gchar *title;
  const gchar *icon;
  const gchar **skills;
  gsize n_skills;
};

extern const SkillCategory skill_categories[];
extern const gsize num_skill_categories;

/* ───────── Interests ───────── */

extern const gchar *interests_data[];
extern const gsize num_interests;

/* ───────── Achievements ───────── */

struct _Achievement {
  const gchar *title;
  const gchar *event;
  const gchar *description;
  const gchar *icon;
  const gchar *color[2];
};

extern const Achievement achievements[];
extern const gsize num_achievements;

/* ───────── Lifecycle ───────── */

void portfolio_data_init (void);
void portfolio_data_cleanup (void);

G_END_DECLS
