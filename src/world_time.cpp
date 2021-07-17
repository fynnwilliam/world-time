
#include <sstream>

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

    // Setting the URL to retrive.
    request.setOpt(new curlpp::options::Url(url));

    std::cout << request << std::endl;

    // Even easier version. It does the same thing 
    // but if you need to download only an url,
    // this is the easiest way to do it.
    std::cout << curlpp::options::Url(url) << std::endl; // ---------------------------------------------------------------------------------

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