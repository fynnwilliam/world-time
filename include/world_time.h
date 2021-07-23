#include <vector>
#include <sstream>

struct location
{
    std::string name;
    std::string region;
    std::string area;
};

std::vector<location> locations;


void display_time(std::stringstream& ss)
{
    std::string sch;
    int count{};
    
    while (ss >> sch)
        if (count++ == 5)
            std::cout << "the time in ... is " << sch.substr(sch.find('T') + 1, 8) << '\n';
}