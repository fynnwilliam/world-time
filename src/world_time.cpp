#include "world_time.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

int main(int argc, char *argv[])
{ 
    try
    {
        std::string input = arguments(argc, argv);
        std::string url{"http://worldtimeapi.org/api"};
        
        read_timezones();
        
        curlpp::Cleanup cleaner;
        curlpp::Easy request;
        
        std::string zone = find_timezone(input);
        zone.empty() ? throw not_avaliable() : url.append(zone).append(".txt");

        std::stringstream fetched;
        fetched << curlpp::options::Url(url);
    
        display_time(fetched, input);
    }
  
    catch (std::invalid_argument& e)
    {
        std::cout << e.what()
                  << "\nplease call with a specific location, region or IP"
                  << "\neg.1: " << argv[0] << " Los Angeles"
                  << "\neg.2: " << argv[0] << " Salta"
                  << "\neg.3: " << argv[0] << " GMT+2"
                  << "\neg.4: " << argv[0] << " 8.8.8.8"
                  << std::endl;
    }
    
    catch (std::out_of_range& e)
    {
        std::cout << e.what() << std::endl;
    }

    catch (std::range_error& e)
    {
        std::cout << e.what() << std::endl;
    }
    
    catch (curlpp::LogicError& e)
    {
        std::cout << e.what() << std::endl;
    }
  
    catch (curlpp::RuntimeError& e)
    {
        std::cout << e.what()
                  << "\nplease check your internet connection or check for typos"
                  << std::endl;
    }
}