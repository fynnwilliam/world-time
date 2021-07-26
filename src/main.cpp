#include "timezn.h"

int main(int argc, char* argv[])
{
    try
    {   
        retrieve_time(argc, argv);
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
    
    catch (curlpp::RuntimeError& e)
    {
        std::cout << e.what()
                  << "\nplease check your internet connection or check for typos"
                  << std::endl;
    }
}