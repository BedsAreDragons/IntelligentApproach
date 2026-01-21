#pragma once
#include <map>
#include <string>

class CCallsignLookup
{
private:
    std::map<std::string, int> configValues;

public:
    explicit CCallsignLookup(const std::string& fileName);

    int getValue(const std::string& key) const;

    int getLineupTime() const;
    int getDepartTime() const;
    int getLandTime() const;
    int getMovementPerHour() const;

    static bool Available;
    static CCallsignLookup* Lookup;

    ~CCallsignLookup();
};
