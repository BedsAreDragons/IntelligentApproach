#include "stdafx.h"
#include "CallsignLookup.h"
#include <fstream>
#include <sstream>

bool CCallsignLookup::Available = false;
CCallsignLookup* CCallsignLookup::Lookup = nullptr;

CCallsignLookup::CCallsignLookup(const std::string& fileName)
{
    std::ifstream myfile(fileName);
    if (!myfile.is_open())
    {
        Available = false;
        return;
    }

    std::string line;
    while (std::getline(myfile, line))
    {
        if (line.empty() || line[0] != '#')
            continue;

        line.erase(0, 1);

        std::istringstream iss(line);
        std::string key;
        int value;

        if (iss >> key >> value)
            configValues[key] = value;
    }

    Available = false;
}

int CCallsignLookup::getValue(const std::string& key) const
{
    auto it = configValues.find(key);
    return (it != configValues.end()) ? it->second : 0;
}

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

CCallsignLookup::~CCallsignLookup() {}
