#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

struct timezn
{
    std::string name;
    std::string region;
    std::string location;
    std::string area;
};

std::vector<timezn> timezns;

void read_timezones()
{
    std::ifstream timezones("../timezones");
    std::string timezone;
    std::string region;
    std::string location;
    std::string area;

    while (timezones >> timezone)
    {
        int forward_slash = std::count(timezone.begin(), timezone.end(), '/');
        
        if (!forward_slash)
        {
            timezns.push_back(timezn(timezone, timezone, "", ""));
        }
        else if(forward_slash == 1)
        {
            std::replace(timezone.begin(), timezone.end(), '/', ' ');
            std::stringstream temp(timezone);
            temp >> region >> location;
            
            timezns.push_back(timezn(location, region, location, ""));
        }
        else
        {
            std::replace(timezone.begin(), timezone.end(), '/', ' ');
            std::stringstream temp(timezone);
            temp >> region >> location >> area;
            
            timezns.push_back(timezn(area, region, location, area));
        }
    }
}

void display_time(std::stringstream& ss)
{
    std::string sch;
    int count{};
    
    while (ss >> sch)
        if (count++ == 5)
            std::cout << "the time in ... is " << sch.substr(sch.find('T') + 1, 8) << '\n';
}

// http://worldtimeapi.org/api/timezone/