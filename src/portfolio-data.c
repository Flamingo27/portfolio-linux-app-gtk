#include "portfolio-data.h"
#include <glib.h>

/* Experience Data */

// Cura Horizon Links
static GHashTable *cura_horizon_links;
static void
init_cura_horizon_links (void)
{
  cura_horizon_links = g_hash_table_new_full (g_str_hash, g_str_equal,
                                              (GDestroyNotify)g_free,
                                              (GDestroyNotify)g_free);
  g_hash_table_insert (cura_horizon_links, g_strdup ("demo"), g_strdup ("https://cura-horizon-healthai.netlify.app/"));
  g_hash_table_insert (cura_horizon_links, g_strdup ("report"), g_strdup ("https://drive.google.com/file/d/1jGCZQ3055R2RPwNjKay2eU8RVlV4QWUS/view?usp=drive_open"));
}

static const gchar *cura_horizon_highlights[] = {
  "Built the core web UI, logic flow, and early-stage AI-assisted modules.",
  "Designed and prototyped IoT-based emergency response features.",
  "Created pitch materials, documentation, and technical explanations for presentations.",
  "Launched the functional prototype — view the Live Demo.",
  "Published implementation details — refer to the TechMag Report for deeper insights.",
  NULL
};

// IIC, IIFR Highlights
static const gchar *iic_iifr_highlights[] = {
  "Developed solutions using Raspberry Pi and Arduino.",
  "Implemented MicroPython-based logic for IoT applications.",
  "Built early-stage healthcare device prototypes.",
  NULL
};

// IETE IEM Students' Forum Highlights
static const gchar *iete_highlights[] = {
  "Managed LinkedIn, Instagram, and Facebook brand accounts.",
  "Designed content strategy to boost engagement.",
  "Increased forum visibility and community reach.",
  NULL
};


Experience experiences[] = {
  {
    .role = "Co-Founder",
    .company = "Cura Horizon",
    .duration = "2024 – Present",
    .description = "Developing an AI-integrated healthcare platform with hospital finder, emergency medicine assistance, and IoT device integration.",
    .location = "Remote",
    .highlights = (const gchar **)cura_horizon_highlights,
    .links = NULL // Will be initialized dynamically via init_cura_horizon_links
  },
  {
    .role = "Lab Intern",
    .company = "IIC, IIFR",
    .duration = "2024 – Present",
    .description = "Prototyped healthcare-focused hardware-software solutions using embedded systems and IoT development tools.",
    .location = "Kolkata, WB",
    .highlights = (const gchar **)iic_iifr_highlights,
    .links = NULL
  },
  {
    .role = "Social Media Manager",
    .company = "IETE IEM Students' Forum",
    .duration = "2025 – Present",
    .description = "Managing digital presence and improving engagement across multiple social platforms.",
    .location = "Kolkata, WB",
    .highlights = (const gchar **)iete_highlights,
    .links = NULL
  }
};

const gsize num_experiences = G_N_ELEMENTS(experiences);

/* Project Data */

// UNICRED Project Links
static const ProjectLink unicred_links[] = {
  {
    .label = "Live Demo",
    .url = "https://unicred-portal.debarghaya.in",
    .type = "demo"
  },
  {
    .label = "Project Drive Folder",
    .url = "https://drive.google.com/drive/folders/1K-i6kuuBj0G23VyYOGL7jthsgrd2gHMd",
    .type = "drive"
  }
};
static const gsize num_unicred_links = G_N_ELEMENTS(unicred_links);

// Assistive Healthcare Devices Project Links
static const ProjectLink assistive_links[] = {
  {
    .label = "Live Demo",
    .url = "https://dem-sim.netlify.app",
    .type = "demo"
  }
};
static const gsize num_assistive_links = G_N_ELEMENTS(assistive_links);


// Project Technologies
static const gchar *unicred_tech[] = {"React", "Node.js", "Kotlin", "PostgreSQL", "Solidity", NULL};
static const gchar *irrigation_tech[] = {"Arduino UNO", "Soil Moisture Sensor", "Embedded C", "IoT Logic", NULL};
static const gchar *stocks_tech[] = {"React", "Node.js", "MySQL", "REST APIs", NULL};
static const gchar *assistive_tech[] = {"Raspberry Pi", "Python", "IoT", "UI/UX", NULL};


const Project projects[] = {
  {
    .title = "UNICRED",
    .subtitle = "Blockchain Credential Verification System",
    .description = "Developed secure credential verification portal with frontend workflows and integration pipelines using blockchain technology.",
    .tech = unicred_tech,
    .n_tech = G_N_ELEMENTS(unicred_tech) - 1, // Exclude NULL terminator
    .achievement = "Top 5 Finalist at GDG HackBuild, VIT Mumbai",
    .links = unicred_links,
    .n_links = num_unicred_links,
    .image = "project_unicred.jpg",
  },
  {
    .title = "Smart Irrigation System",
    .subtitle = "Arduino UNO Based Automated Irrigation",
    .description = "Designed a sensor-based irrigation automation system using soil moisture sensing and microcontroller logic. The system intelligently controls water flow to optimize plant hydration and reduce water waste.",
    .tech = irrigation_tech,
    .n_tech = G_N_ELEMENTS(irrigation_tech) - 1,
    .achievement = "",
    .links = NULL, // No links
    .n_links = 0,
    .image = "project_irrigation.jpg",
  },
  {
    .title = "Smart Stocks",
    .subtitle = "Automated Inventory Management",
    .description = "Built responsive inventory automation system with product listing, search, and stock updates to reduce manual errors.",
    .tech = stocks_tech,
    .n_tech = G_N_ELEMENTS(stocks_tech) - 1,
    .achievement = "",
    .links = NULL, // No links
    .n_links = 0,
    .image = "project_stocks.jpg",
  },
  {
    .title = "Assistive Healthcare Devices",
    .subtitle = "Alzheimer's Glass & Accu-Pressure Glove",
    .description = "Created innovative healthcare devices with audio/video assistance and accessible UI/UX using Raspberry Pi.",
    .tech = assistive_tech,
    .n_tech = G_N_ELEMENTS(assistive_tech) - 1,
    .achievement = "",
    .links = assistive_links,
    .n_links = num_assistive_links,
    .image = "project_assistive.jpeg",
  }
};

const gsize num_projects = G_N_ELEMENTS(projects);

/* Skill Category Data */

static const gchar *languages_skills[] = {"JavaScript", "Python", "Java", "C/C++", "HTML/CSS", NULL};
static const gchar *frontend_skills[] = {"React", "Responsive Design", "UI/UX", "Tailwind CSS", NULL};
static const gchar *backend_skills[] = {"Node.js", "REST APIs", "MySQL", "MongoDB", "PostgreSQL", NULL};
static const gchar *hardware_skills[] = {"Arduino", "Raspberry Pi", "MicroPython", "IoT Systems", NULL};
static const gchar *version_control_skills[] = {"Git", "GitHub", "Collaboration", NULL};
static const gchar *blockchain_skills[] = {"Solidity", "Smart Contracts", "Web3", NULL};

const SkillCategory skill_categories[] = {
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

const gsize num_skill_categories = G_N_ELEMENTS(skill_categories);

/* Interests Data */
const gchar *interests_data[] = {"Full-Stack Development", "UI/UX", "Open-source Contributions", NULL};
const gsize num_interests = G_N_ELEMENTS(interests_data) - 1;


// Function to initialize all data (especially hash tables)
void
portfolio_data_init (void)
{
  init_cura_horizon_links ();

  // Assign dynamically allocated hash table after initialization
  ((Experience *)experiences)[0].links = cura_horizon_links;
}

// Function to free all dynamically allocated data
void
portfolio_data_cleanup (void)
{
  g_hash_table_unref (cura_horizon_links);
}

