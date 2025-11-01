#include <wx/wx.h>

/*
* The AtlasMenuBar has several "menus", including: AtlasMenuFile, AtlasMenuHelp, etc... Each menu has multiple options that can be selected (E.g., About, License, GitHub, etc...).
* Each option within these menus must be represented by a unique integer ID such that their events can be appropriately bound to expected behaviors.
*/
enum class AtlasMenuOptionEnums : int
{
	ID_HELLO = wxID_HIGHEST + 1,
	ID_PLUGIN_MANAGER
};
