#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

class CCallsignLookup
{
private:
    map<string, int> configValues;

public:
    CCallsignLookup(string fileName);

    // Generic getter
    int getValue(const string& key) const;

    // Convenience getters (optional but practical)
    int getLineupTime() const;
    int getDepartTime() const;
    int getLandTime() const;
    int getMovementPerHour() const;

    static bool Available;
    static CCallsignLookup* Lookup;

    ~CCallsignLookup();
};
