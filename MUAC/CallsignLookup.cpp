#include "stdafx.h"
#include "CallsignLookup.h"

bool CCallsignLookup::Available = false;
CCallsignLookup* CCallsignLookup::Lookup = nullptr;

CCallsignLookup::CCallsignLookup(string fileName)
{
    ifstream myfile(fileName);
    string line;

    if (!myfile.is_open())
        return;

    while (getline(myfile, line))
    {
        // Ignore empty lines
        if (line.empty())
            continue;

        // Must start with #
        if (line[0] != '#')
            continue;

        // Remove #
        line.erase(0, 1);

        istringstream iss(line);
        string key;
        int value;

        if (iss >> key >> value)
        {
            configValues[key] = value;
        }
    }

    myfile.close();
    Available = true;
}

int CCallsignLookup::getValue(const string& key) const
{
    auto it = configValues.find(key);
    if (it == configValues.end())
        return 0; // or -1 if you prefer error signalling

    return it->second;
}

// Convenience getters
int CCallsignLookup::getLineupTime() const
{
    return getValue("LINEUPTIME");
}

int CCallsignLookup::getDepartTime() const
{
    return getValue("DEPARTTIME");
}

int CCallsignLookup::getLandTime() const
{
    return getValue("LANDTIME");
}

int CCallsignLookup::getMovementPerHour() const
{
    return getValue("MOVEMENTPERHOUR");
}

CCallsignLookup::~CCallsignLookup()
{
}
