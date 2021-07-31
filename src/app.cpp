#include "app.h"
#include "timezones.h"

void app::tell()
{
    check_arguments();
    read_timezones();
    update_url();
    api_call();
    display_time();
}

void app::api_call()
{
    fetched_ << curlpp::options::Url(url_);
}

auto app::invalid_argc() const
{
    return std::invalid_argument("invalid number of arguments");
}

auto app::not_avaliable() const
{
    return std::range_error("timezone not found");
}

void app::check_arguments()
{
    if (argc_ > 3 || argc_ == 1) { throw invalid_argc(); }

    usr_input_ = ip_address(argv_[1]) ? ip() : location();
}

void app::read_timezones()
{
    std::stringstream timezones(::timezones);
    std::string timezone;

    while (timezones >> timezone)
    {
        timezns_.push_back(timezn().values(timezone));
    }
}

void app::update_url()
{   
    std::string zone{find_timezone()};
    zone.empty() ? throw not_avaliable() : url_.append(zone).append(".txt");
}

std::string app::time(std::string const& t) const
{
    return std::string{"It is "} + t.substr(t.find('T') + 1, 8);
}

std::string app::abbreviation(std::string const& a) const
{
    return std::string{" "} + a.substr(1, 3);
}

std::string app::day(std::string const& d) const
{   
    return std::string{", "} + _day(std::stoi(d));
}

std::string app::month(std::string const& m) const
{
    return _month(std::stoi(m));
}

std::string app::date(std::string const& d) const
{
    std::string year{ d.substr(1, 4) };
    std::string m{ d.substr(6, 2) };
    std::string day{ d.substr(9, 2) };
    
    return month(m) + day + ", " + year;
}

std::string app::datetime()
{
    std::string datetime;
    std::string abbr;
    std::string sch;
    int count{};

    while (fetched_ >> sch)
    {
        if (count++ == 1) { abbr = sch; }
        if (count++ == 5) { datetime = sch; }
        if (count++ == 7)
        {
            return time(datetime)
                 + abbreviation(abbr)
                 + day(sch)
                 + date(datetime)
                 + (ip_address(usr_input_) ? " at " : " in ")
                 + usr_input_;
        }
    }
    
    return std::string{"please update the app"};
}

void app::display_time()
{
    std::cout << datetime() << std::endl;
}

std::string app::to_lower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c)
                  { return std::tolower(c); });
    return s;
}

std::string app::ip() const
{
    if (argc_ > 2) { throw invalid_argc(); }

    std::string ip{argv_[1]};

    if (public_ip(ip)) { return ip; }
    throw std::out_of_range("\"" + ip + "\" is not a public IP");
}

std::string app::location() const
{
    std::string first = argv_[1];
    std::string second = !argv_[2] ? std::string{} : argv_[2];

    return second.empty() ? first : first.append('_' + second);
}

std::string app::find_timezone()
{
    if (ip_address(usr_input_)) { return std::string{"/ip/"}.append(usr_input_); }

    for (timezn const& a : timezns_)
    {
        if (to_lower(a.name()) == to_lower(usr_input_))
        {
            return a.sub_link();
        }
    }

    return std::string{};
}

bool app::private_a(std::string const& ip) const
{
    std::regex pattern("([1][0])(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){3}");
    return std::regex_match(ip, pattern);
}

bool app::private_b(std::string const& ip) const
{
    std::regex pattern("([1][7][2])(\\.(1[6-9]|2[0-9]|3[01]))(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){2}");
    return std::regex_match(ip, pattern);
}

bool app::private_c(std::string const& ip) const
{
    std::regex pattern("([1][9][2])(\\.([1][6][8]))(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){2}");
    return std::regex_match(ip, pattern);
}

bool app::private_ip(std::string const& ip) const
{
    return private_a(ip) || private_b(ip) || private_c(ip);
}

bool app::public_ip(std::string const& ip) const
{
    return !private_ip(ip);
}

bool app::ip_address(std::string const& item) const
{
    std::regex pattern("([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){3}");
    return std::regex_match(item, pattern);
}