#pragma once
#include <adwaita.h>

G_BEGIN_DECLS

#define HERO_TYPE_PAGE (hero_page_get_type())
G_DECLARE_FINAL_TYPE (HeroPage, hero_page, HERO, PAGE, AdwBin)

HeroPage *hero_page_new (void);

G_END_DECLS

