portfolio_linux_app_gtk_sources = [
  'main.c',
  'portfolio-linux-app-gtk-application.c',
  'portfolio-linux-app-gtk-window.c',
]

portfolio_linux_app_gtk_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1', version: '>= 1.4'),
]

portfolio_linux_app_gtk_sources += gnome.compile_resources('portfolio-linux-app-gtk-resources',
  'portfolio-linux-app-gtk.gresource.xml',
  c_name: 'portfolio_linux_app_gtk'
)

executable('portfolio-linux-app-gtk', portfolio_linux_app_gtk_sources,
  dependencies: portfolio_linux_app_gtk_deps,
       install: true,
)
