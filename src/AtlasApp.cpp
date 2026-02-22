#include "AtlasApp/AtlasSetupLayers/AtlasConfigTasks/AtlasCreateApplicationDirectory/AtlasCreateApplicationDirectory.h"
#include "AtlasApp/AtlasSetupLayers/AtlasDataTasks/AtlasDownloadCatalogs/AtlasDownloadCatalogs.h"
#include "AtlasApp/AtlasSetupLayers/AtlasDataTasks/AtlasImportDefaultCatalog/AtlasImportDefaultCatalog.h"
#include "AtlasApp/AtlasSetupLayers/AtlasDataTasks/AtlasLoadCurl/AtlasLoadCurl.h"
#include "AtlasApp/AtlasSetupLayers/AtlasDatabaseTasks/AtlasExecuteDatabaseSchema/AtlasExecuteDatabaseSchema.h"
#include "AtlasCore/AtlasConfig/AtlasConfig.h"
#include "AtlasGUI/AtlasFrame/AtlasFrame.h"
#include <expected>
#include <string>
#include <wx/app.h>
#include <wx/cmdline.h>
#include <wx/defs.h>
#include <wx/msgdlg.h>

class AtlasApp : public wxApp
{
public:
	virtual bool OnInit();
	virtual void OnInitCmdLine(wxCmdLineParser& parser);
	virtual bool OnCmdLineParsed(wxCmdLineParser& parser);

private:
	AtlasFrame* frame = nullptr;
	AtlasConfig& config = AtlasConfig::getInstance();
};

/*
*
*         .o.           .   oooo                          oooooooooo.                          .   oooo
*        .888.        .o8   `888                          `888'   `Y8b                       .o8   `888
*       .8"888.     .o888oo  888   .oooo.    .oooo.o       888     888  .ooooo.   .ooooo.  .o888oo  888   .ooooo.
*      .8' `888.      888    888  `P  )88b  d88(  "8       888oooo888' d88' `88b d88' `88b   888    888  d88' `88b
*     .88ooo8888.     888    888   .oP"888  `"Y88b.        888    `88b 888ooo888 888ooo888   888    888  888ooo888
*    .8'     `888.    888 .  888  d8(  888  o.  )88b       888    .88P 888    .o 888    .o   888 .  888  888    .o
*   o88o     o8888o   "888" o888o `Y888""8o 8""888P'      o888bood8P'  `Y8bod8P' `Y8bod8P'   "888" o888o `Y8bod8P'
*
*   Project: Atlas Beetle
*
*   Author: Sean Maloney (Astrosaur Projects)
*
*	Date: October 18, 2025
*
*   Description: A home-brewed, planetarium software with plugin extensibility; built for amateur astronomers, budding computer scientists, and do-it-yourself enthusiasts.
*
*	License: MIT License
*
*	Technologies:
*	 - https://cplusplus.com/
*	 - https://www.opengl.org/
*	 - https://wxwidgets.org/
*	 - https://curl.se/
*	 - https://cmake.org/
*	 - https://sqlite.org/
*	 - https://heasarc.gsfc.nasa.gov/docs/software/fitsio/fitsio.html
*/
wxIMPLEMENT_APP(AtlasApp);

bool AtlasApp::OnInit()
{
	if (!wxApp::OnInit()) {
		return false;
	}

	std::expected<bool, std::string> initAppResult = true;

	initAppResult = initAppResult
		.and_then([](bool) { return AtlasLoadCurl::load(); })
		.and_then([](bool) { return AtlasCreateApplicationDirectory::initialize(); })
		.and_then([](bool) { return AtlasExecuteDatabaseSchema::initialize(); })
		.and_then([](bool) { return AtlasDownloadCatalogs::download(); })
		.and_then([](bool) { return AtlasImportDefaultCatalog::load(); });

	if (!initAppResult.has_value()) {
		wxMessageBox(initAppResult.error(), "Error", wxOK | wxICON_ERROR);
		return false;
	}

	frame = new AtlasFrame();

	frame->Show(true);

	return true;
}

void AtlasApp::OnInitCmdLine(wxCmdLineParser& parser)
{
	wxApp::OnInitCmdLine(parser);

	static const wxCmdLineEntryDesc description[] = {
		{ wxCMD_LINE_SWITCH, "V", "version", "display software version and exit" },
		{ wxCMD_LINE_SWITCH, nullptr, "reset", "reset to default" },
		{ wxCMD_LINE_NONE }
	};

	parser.SetDesc(description);
}

bool AtlasApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
	if (!wxApp::OnCmdLineParsed(parser)) {
		return false;
	}

	if (parser.Found("version")) {
		return false;
	}

	config.reset = parser.Found("reset");

	return true;
}