#include "app.h"
#include "day.h"
#include "month.h"

void app::tell(int argc, char **argv) {
  check_arguments(argc, argv);
  fetch_time();
  display_time();
}

status_code app::fetch_time() {
  std::string url{update_url};
  return url.empty() ? zone_unavailable() : fetch(url);
}

auto app::fetch(std::string const &url) {
  try {
    fetched_ << curlpp::options::Url(url)
  } catch (curlpp::RuntimeError &e) {
    std::cout << e.what() << "\nplease check your internet connection\n";
    return status_code{1};
  }

  return status_code{};
}

auto app::invalid_argc() const {
  return std::invalid_argument("invalid number of arguments");
}

auto app::zone_unavailable() const noexcept {
  std::cout << "timezone not found\n";
  return status_code{1};
}

void app::check_arguments(int argc, char **argv) {
  if (argc > 3 || argc == 1) {
    throw invalid_argc();
  }

  usr_input_ = ip_address(argv[1]) ? ip(argc, argv) : location(argv);
}

std::string app::update_url() {
  std::string url{"http://worldtimeapi.org/api"};

  std::string zone{find_timezone()};
  return zone.empty() ? zone : url.append(zone).append(".txt");
}

auto app::time(std::string const &t) {
  return std::string{"It is "} + t.substr(t.find('T') + 1, 8);
}

auto app::abbreviation(std::string const &a) {
  return std::string{" "}.append(a);
}

auto app::date(std::string const &d) {
  std::string year{d.substr(0, 4)};
  std::string m{d.substr(5, 2)};
  int day{std::stoi(d.substr(8, 2))};

  return month{}[std::stoi(m)] + ' ' + std::to_string(day) + ", " + year;
}

std::string app::preposition() const {
  return ip_address(usr_input_) ? " at " : " in ";
}

std::string app::usr_input() const {
  std::string s{usr_input_};
  std::replace(begin(s), end(s), '_', ' ');
  return s;
}

std::string app::datetime() {
  std::string temp, t, abbr, d;
  int count{};

  while (fetched_ >> temp) {
    if (count == 1) {
      abbr = abbreviation(temp);
    }
    if (count == 5) {
      d = date(temp);
      t = time(temp);
    }
    if (count == 7) {
      return t + abbr + day{}[std::stoi(temp)] + d + preposition() +
             usr_input();
    }
    count++;
  }

  return std::string{"please update the app"};
}

void app::display_time() { std::cout << datetime() << std::endl; }

void app::_transform(std::string &s, int index) {
  std::transform(s.begin(), s.begin() + index, s.begin(),
                 [](unsigned char c) { return std::toupper(c); });
}

std::string app::to_lower(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  return s;
}

std::string app::capitalize(std::string s) {
  to_lower(s.substr(0, 3)) == "gmt" ? _transform(s, 3) : _transform(s, 1);

  return s;
}

std::string app::ip(int argc, char **argv) const {
  if (argc > 2) {
    throw invalid_argc();
  }

  std::string ip{argv[1]};

  if (public_ip(ip)) {
    return ip;
  }
  throw std::out_of_range("\"" + ip + "\" is not a public IP");
}

std::string app::location(char **argv) noexcept {
  std::string first = capitalize(argv[1]);
  std::string second = !argv[2] ? std::string{} : capitalize(argv[2]);

  return second.empty() ? first : first.append('_' + second);
}

std::string app::find_timezone() {
  return ip_address(usr_input_) ? std::string{"/ip/"}.append(usr_input_)
                                : timezns_.find(usr_input_);
}

bool app::private_a(std::string const &ip) const {
  std::regex pattern("([1][0])(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){3}");
  return std::regex_match(ip, pattern);
}

bool app::private_b(std::string const &ip) const {
  std::regex pattern("([1][7][2])(\\.(1[6-9]|2[0-9]|3[01]))(\\.([01]?[0-9][0-9]"
                     "?|2[0-4][0-9]|25[0-5])){2}");
  return std::regex_match(ip, pattern);
}

bool app::private_c(std::string const &ip) const {
  std::regex pattern("([1][9][2])(\\.([1][6][8]))(\\.([01]?[0-9][0-9]?|2[0-4]["
                     "0-9]|25[0-5])){2}");
  return std::regex_match(ip, pattern);
}

bool app::private_ip(std::string const &ip) const {
  return private_a(ip) || private_b(ip) || private_c(ip);
}

bool app::public_ip(std::string const &ip) const { return !private_ip(ip); }

bool app::ip_address(std::string const &item) const {
  std::regex pattern("([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])(\\.([01]?[0-9][0-"
                     "9]?|2[0-4][0-9]|25[0-5])){3}");
  return std::regex_match(item, pattern);
}
