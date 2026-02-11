#ifndef ATLAS_MENU_OPTION_ENUMS_H
#define ATLAS_MENU_OPTION_ENUMS_H

#include <wx/defs.h>
/*
* The AtlasMenuBar has several "menus", including: AtlasMenuFile, AtlasMenuHelp, etc... Each menu has multiple options that can be selected (E.g., About, License, GitHub, etc...).
* Each option within these menus must be represented by a unique integer ID such that their events can be appropriately bound to expected behaviors.
*/
enum class AtlasMenuOptionEnums : int
{
	ID_CATALOG_MANAGER = wxID_HIGHEST + 1,
	ID_PLUGIN_MANAGER
};

#endif