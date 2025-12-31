#pragma once

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

typedef struct _Experience Experience;
typedef struct _ProjectLink ProjectLink;
typedef struct _Project Project;
typedef struct _SkillCategory SkillCategory;
typedef struct _Achievement Achievement;
typedef struct _Education Education;

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

/* ───────── Publications ───────── */

typedef struct _Publication Publication;

struct _Publication {
  const gchar *title;
  const gchar *type;
  const gchar *icon;
  const gchar *description;
  const gchar *url;
};

extern const Publication publications[];
extern const gsize num_publications;

/* ───────── Education ───────── */

struct _Education {
  const gchar *institution;
  const gchar *degree;
  const gchar *score;
  const gchar *duration;
  const gchar *logo; // Will be used for icon name
  const gchar *location;
  gboolean highlight;
};

extern const Education education[];
extern const gsize num_education;

/* ───────── Lifecycle ───────── */

void portfolio_data_init (void);
void portfolio_data_cleanup (void);

G_END_DECLS
