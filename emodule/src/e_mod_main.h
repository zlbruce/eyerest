#ifndef E_MOD_MAIN_H
#define E_MOD_MAIN_H

#ifdef ENABLE_NLS
# include <libintl.h>
# define _(string) dgettext(PACKAGE, string)
#else
# define bindtextdomain(domain,dir)
# define bind_textdomain_codeset(domain, codeset)
# define _(string) (string)
#endif

EAPI extern E_Module_Api e_modapi;

EAPI void  *e_modapi_init       (E_Module *m);
EAPI int    e_modapi_shutdown   (E_Module *m);
EAPI int    e_modapi_save       (E_Module *m);

typedef struct _Config 		Config;
struct _Config
{
	E_Module *module;
	Eina_List *instances;
};

#endif
