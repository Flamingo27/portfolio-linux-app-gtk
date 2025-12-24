#pragma once

#include <glib-object.h>
#include <glib.h> // Required for GHashTable

G_BEGIN_DECLS

// Forward declarations for all structs
typedef struct _Experience Experience;
typedef struct _ProjectLink ProjectLink;
typedef struct _Project Project;
typedef struct _SkillCategory SkillCategory;
typedef struct _Achievement Achievement;
typedef struct _Portfolio Portfolio;

// Full definitions of structs
struct _Experience
{
  const gchar *role;
  const gchar *company;
  const gchar *duration;
  const gchar *description;
  const gchar *location; // Added
  const gchar **highlights;
  GHashTable *links; // Key: gchar*, Value: gchar* (URL)
};

struct _ProjectLink
{
  const gchar *label;
  const gchar *url;
  const gchar *type; // "demo", "drive", etc.
};

struct _Project
{
  const gchar *title;
  const gchar *subtitle;
  const gchar *description;
  const gchar **tech;
  gsize n_tech;
  const gchar *achievement;
  const ProjectLink *links;
  gsize n_links;
  const gchar *image; // Full filename, e.g., "project_unicred.png"
};

struct _SkillCategory
{
  const gchar *title;
  const gchar *icon; // Resource name for icon
  const gchar **skills;
  gsize n_skills;
};

struct _Achievement
{
  const gchar *title;
  const gchar *event;
  const gchar *description;
  const gchar *icon; // Resource name for icon
};

// Extern declarations for the data arrays and functions
extern Experience experiences[];
extern const gsize num_experiences;

extern const Project projects[];
extern const gsize num_projects;

extern const SkillCategory skill_categories[];
extern const gsize num_skill_categories;

extern const gchar *interests_data[];
extern const gsize num_interests;

// Function to initialize dynamically allocated data (e.g., hash tables)
void portfolio_data_init (void);

// Function to free dynamically allocated data
void portfolio_data_cleanup (void);

// Full definition of Portfolio (must come after all structs it contains)
struct _Portfolio
{
  const Experience *experience;
  gsize n_experience;
  const Project *projects;
  gsize n_projects;
  const SkillCategory *skills;
  gsize n_skills;
  const gchar **interests; // Not present in Kotlin example, keep for now
  gsize n_interests;
  const Achievement *achievements;
  gsize n_achievements;
};

G_END_DECLS
