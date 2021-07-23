#include <iostream>
#include <sstream>
#include <cstdlib>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

#include "world_time.h"

int main(int argc, char *argv[])
{
  if(argc != 2) {
    std::cerr << argv[0] << ": Wrong number of arguments" << std::endl 
	      << argv[0] << ": Usage: " << " url " 
	      << std::endl;
    return EXIT_FAILURE;
  }

  char *url = argv[1];
  
  try
  {
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
        std::cout << a.name << "-> " << a.region << '-' << a.location << '-' << a.area << '\n';
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
}