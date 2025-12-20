#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_SKILLS_PAGE (portfolio_skills_page_get_type ())
G_DECLARE_FINAL_TYPE (PortfolioSkillsPage, portfolio_skills_page, PORTFOLIO, SKILLS_PAGE, AdwBin)

PortfolioSkillsPage *
portfolio_skills_page_new (void);

G_END_DECLS