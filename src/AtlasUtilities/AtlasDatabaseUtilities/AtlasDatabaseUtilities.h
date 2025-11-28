#ifndef ATLAS_DATABASE_UTILS_H
#define ATLAS_DATABASE_UTILS_H

#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <sqlite3.h>

namespace AtlasDatabaseUtilities
{
	wxString getPath();
	bool isInitialized();
};

#endif