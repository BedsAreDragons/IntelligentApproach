#include "stdafx.h"
#include "MUAC.h"
#include "CallsignLookup.h"

MUAC::MUAC()
    : CPlugIn(COMPATIBILITY_CODE,
              PLUGIN_NAME.c_str(),
              PLUGIN_VERSION.c_str(),
              PLUGIN_AUTHOR.c_str(),
              PLUGIN_COPY.c_str())
{
    srand((unsigned int)time(nullptr));
    RegisterPlugin();

    DisplayUserMessage(
        "Message",
        "MUAC PlugIn",
        ("Version " + PLUGIN_VERSION + " loaded").c_str(),
        false, false, false, false, false
    );

    char DllPathFile[_MAX_PATH];
    GetModuleFileNameA(HINSTANCE(&__ImageBase), DllPathFile, sizeof(DllPathFile));

    std::string DllPath = DllPathFile;
    DllPath.resize(DllPath.size() - strlen("MUAC.dll"));

    std::string FilePath = DllPath + "\\config.txt";

    if (!file_exist(FilePath))
    {
        CCallsignLookup::Available = false;

        DisplayUserMessage(
            "Message",
            "MUAC PlugIn",
            "Warning: config.txt not found. Using default values.",
            true, true, false, false, true
        );
    }
    else
    {
        CCallsignLookup::Lookup = new CCallsignLookup(FilePath);

        if (CCallsignLookup::Available)
        {
            DisplayUserMessage(
                "Message",
                "MUAC PlugIn",
                "config.txt loaded successfully.",
                false, false, false, false, false
            );
        }
    }
}


MUAC::~MUAC() {}

CRadarScreen * MUAC::OnRadarScreenCreated(const char * sDisplayName, bool NeedRadarContent, bool GeoReferenced, bool CanBeSaved, bool CanBeCreated)
{
	if (!strcmp(sDisplayName, MUAC_RADAR_SCREEN_VIEW))
		return new RadarScreen();

	return nullptr;
}

void MUAC::OnTimer(int Counter)
{
	if (Counter % 5 == 0) {

	}
}

void MUAC::RegisterPlugin() {
	RegisterDisplayType(MUAC_RADAR_SCREEN_VIEW, false, true, true, true);
}
