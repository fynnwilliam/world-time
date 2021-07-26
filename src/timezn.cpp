#include "timezn.h"
#include "timezones.h"

std::vector<timezn> timezns;

timezn timezn::values(std::string& timezone)
{
    std::replace(timezone.begin(), timezone.end(), '/', ' ');
    std::stringstream temp(timezone);
    temp >> region_ >> location_ >> area_;

    name_ = area_ == location_ ? region_ : area_.size() == 0 ? location_ : area_;

    return *this;
}

std::string timezn::sub_link() const
{
    return std::string{"/timezone"} + insert_slash(region()) + insert_slash(location()) + insert_slash(area());
}

void retrieve_time(int const& argc, char** argv)
{
    std::string usr_input{arguments(argc, argv)};

    read_timezones();

    std::string url{::url(usr_input)};

    std::stringstream fetched;
    fetched << curlpp::options::Url(url);

    display_time(fetched, usr_input);
}

auto invalid_argc()
{
    return std::invalid_argument("invalid number of arguments");
}

auto not_avaliable()
{
    return std::range_error("timezone not found");
}

std::string arguments(int const& argc, char** argv)
{
    if (argc > 3 || argc == 1) { throw invalid_argc(); }

    return ip_address(argv[1]) ? ip(argc, argv) : location(argv);
}

void read_timezones()
{
    std::stringstream timezones(::timezones);
    std::string timezone;

    while (timezones >> timezone)
    {
        timezns.push_back(timezn().values(timezone));
    }
}

std::string url(std::string const& usr_input)
{
    std::string url{"http://worldtimeapi.org/api"};
    
    std::string zone{find_timezone(usr_input)};
    zone.empty() ? throw not_avaliable() : url.append(zone).append(".txt");
    
    return url;
}

std::string time(std::stringstream& ss, std::string const& usr_input)
{
    std::string sch;
    int count{};

    while (ss >> sch)
    {
        if (count++ == 5)
        {
            return std::string{"It is "}
                + sch.substr(sch.find('T') + 1, 8)
                + (ip_address(usr_input) ? " at " : " in ")
                + usr_input;
        }
    }
    
    return std::string{"please update the app"};
}

void display_time(std::stringstream& ss, std::string const& usr_input)
{
    std::cout << time(ss, usr_input) << std::endl;
}

std::string to_lower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c)
        { return std::tolower(c); });
    return s;
}

std::string ip(int const& argc, char** argv)
{
    if (argc > 2) { throw invalid_argc(); }

    std::string ip{argv[1]};

    if (public_ip(ip)) { return ip; }
    throw std::out_of_range("\"" + ip + "\" is not a public IP");
}

std::string location(char** argv)
{
    std::string first = argv[1];
    std::string second = !argv[2] ? std::string{} : argv[2];

    return second.empty() ? first : first.append('_' + second);
}

std::string insert_slash(std::string item)
{
    return item.empty() ? item : '/' + item;
}

std::string find_timezone(std::string const& usr_input)
{
    if (ip_address(usr_input)) { return std::string{"/ip/"}.append(usr_input); }

    for (timezn const& a : timezns)
    {
        if (to_lower(a.name()) == to_lower(usr_input))
        {
            return a.sub_link();
        }
    }

    return std::string{};
}

bool private_a(std::string const& ip)
{
    std::regex pattern("([1][0])(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){3}");
    return std::regex_match(ip, pattern);
}

bool private_b(std::string const& ip)
{
    std::regex pattern("([1][7][2])(\\.(1[6-9]|2[0-9]|3[01]))(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){2}");
    return std::regex_match(ip, pattern);
}

bool private_c(std::string const& ip)
{
    std::regex pattern("([1][9][2])(\\.([1][6][8]))(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){2}");
    return std::regex_match(ip, pattern);
}

bool private_ip(std::string const& ip)
{
    return private_a(ip) || private_b(ip) || private_c(ip);
}

bool public_ip(std::string const& ip)
{
    return !private_ip(ip);
}

bool ip_address(std::string const& item)
{
    std::regex pattern("([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){3}");
    return std::regex_match(item, pattern);
}