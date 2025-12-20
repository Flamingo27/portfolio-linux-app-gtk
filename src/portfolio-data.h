#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

typedef struct _Experience Experience;
typedef struct _ProjectLink ProjectLink;
typedef struct _Project Project;
typedef struct _SkillCategory SkillCategory; // New
typedef struct _Portfolio Portfolio;

struct _Experience
{
  const gchar *role;
  const gchar *company;
  const gchar *duration;
  const gchar *description;
  const gchar **highlights;
  GHashTable *links;
};

// New struct for ProjectLink
struct _ProjectLink
{
  const gchar *label;
  const gchar *url;
  const gchar *type;
};

// New struct for Project
struct _Project
{
  const gchar *title;
  const gchar *subtitle;
  const gchar *description;
  const gchar **tech;
  gsize n_tech; // Add size for tech array
  const gchar *achievement;
  const ProjectLink *links;
  gsize n_links;
  const gchar *image;
};

// New struct for SkillCategory
struct _SkillCategory
{
  const gchar *title;
  const gchar *icon;
  const gchar **skills; // Array of strings
  gsize n_skills;
};

struct _Portfolio
{
  const Experience *experience;
  gsize n_experience;
  const Project *projects; // Add projects to Portfolio
  gsize n_projects;
  const SkillCategory *skills; // Add skills to Portfolio
  gsize n_skills;
  const gchar **interests; // Assuming interests is a list of strings
  gsize n_interests;
};

G_END_DECLS
