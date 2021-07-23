#include <iostream>
#include <sstream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

#include "world_time.h"

int main(int argc, char *argv[])
{ 
    try
    {
        std::string input = arguments(argv);
        /*
        curlpp::Cleanup cleaner;
        curlpp::Easy request;

        std::stringstream fetched;

        fetched << curlpp::options::Url(url);
    
        display_time(fetched);
        */
   
        read_timezones();
   
        for (timezn a : timezns)
        {   
             if (to_lower(a.name()) == to_lower(input))
             {
                 std::cout << a.name() << "-> " << a.region() << '-' << a.location() << '-' << a.area() << '\n';
                 break;
             }
        }
   
    }
  
    catch (curlpp::LogicError& e)
    {
        std::cout << e.what() << std::endl;
    }
  
    catch (curlpp::RuntimeError& e)
    {
        std::cout << e.what()
                  << "\nplease check your internet connection or for typos"
                  << std::endl;
    }
    
    catch (std::runtime_error& e)
    {
        std::cout << e.what()
                  << "\nplease add a specific location or region"
                  << "\neg.1: " << argv[0] << " Los Angeles"
                  << "\neg.2: " << argv[0] << " Salta"
                  << "\neg.3: " << argv[0] << " GMT+2"
                  << '\n';
    }
}