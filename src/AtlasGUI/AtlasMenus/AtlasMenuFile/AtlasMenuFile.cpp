#include "AtlasGUI/AtlasMenus/AtlasMenuFile/AtlasMenuFile.h"
#include <wx/defs.h>
#include <wx/menu.h>

AtlasMenuFile::AtlasMenuFile() : wxMenu()
{
	AppendSeparator();

	Append(wxID_EXIT);
}

AtlasMenuFile::~AtlasMenuFile()
{
}