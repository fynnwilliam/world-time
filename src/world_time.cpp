#include <iostream>
#include <sstream>
#include <algorithm>

#include <cstdlib>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

int main(int argc, char *argv[])
{
  if(argc != 2) {
    std::cerr << argv[0] << ": Wrong number of arguments" << std::endl 
	      << argv[0] << ": Usage: " << " url " 
	      << std::endl;
    return EXIT_FAILURE;
  }

  char *url = argv[1];
  
  try {
    curlpp::Cleanup cleaner;
    curlpp::Easy request;

    std::stringstream fetched;

    fetched << curlpp::options::Url(url);
    std::string edit;
    fetched >> edit;
    //edit.erase(0, 1);
    //edit.pop_back();
    //std::replace(edit.begin(), edit.end(), ':', ' ');
    //std::replace(edit.begin(), edit.end(), ' ', '_');
    //std::replace(edit.begin(), edit.end(), ',', ' ');
    /*
    std::istringstream long_line(edit);
    std::string first;
    std::string second;
    
    while (long_line >> first)
    {
        if (first.substr(1, 8) == "datetime")
        {
            
            std::cout << "the time in ... is " << first.substr(first.find('T') + 1, 8)<< '\n';
        }
    }
    */
    
    std::cout << "the time in ... is " << edit.substr(edit.find('T') + 1, 8)<< '\n';
    
    //std::cout << edit << '\n';

    return EXIT_SUCCESS;
  }
  catch ( curlpp::LogicError & e ) {
    std::cout << e.what() << std::endl;
  }
  catch ( curlpp::RuntimeError & e ) {
    std::cout << e.what() << std::endl;
  }

  return EXIT_FAILURE;
}