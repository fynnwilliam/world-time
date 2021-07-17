#include <vector>
#include <sstream>

struct location
{
    std::string name;
    std::string region;
    std::string area;
};

std::vector<location> locations;

    curlpp::Cleanup cleaner;
    curlpp::Easy request;

    // Setting the URL to retrive.
    request.setOpt(new curlpp::options::Url(url));

    // std::cout << request << std::endl;
    
    
    
    std::istringstream fetched(request);
    fetched.erase(0, 1);
    fetched.pop_back();
    std::replace(fetched.begin(), fetched.end(), '"', '');
    std::replace(fetched.begin(), fetched.end(), ',', ' ');
    
    std::cout << fetched.str();