#include "app.h"
#include "day.h"
#include "month.h"

namespace world_time {
void app::tell(int argc, char **argv) {
  assign_input(argc, argv) && fetch_time() && display_time();
}

auto app::fetch(std::string const &url) {
  try {
    fetched_ << curlpp::options::Url(url);
  } catch (curlpp::RuntimeError const &e) {
    using namespace std::string_literals;
    return status{1, e.what() + "\nplease check your internet connection\n"s};
  }

  return status{};
}

auto app::invalid(char **argv) const noexcept {
  using namespace std::string_literals;

  auto program = argv[0];
  auto message = "invalid number of arguments"
                 "\nplease call with a specific location, region or IP"s
                     .append("\neg.1: "s + program + " Los Angeles")
                     .append("\neg.2: "s + program + " Salta")
                     .append("\neg.3: "s + program + " GMT+2")
                     .append("\neg.4: "s + program + " 8.8.8.8\n");

  return status{1, std::move(message)};
}

auto app::zone_unavailable() const noexcept {
  return status{1, "timezone not found\n"};
}

status app::fetch_time() {
  std::string url{_url()};
  return url.empty() ? zone_unavailable() : fetch(url);
}

status app::ip(char **argv) {
  return ip::public_ip(usr_input_ = argv[1])
             ? status{}
             : status{1, "\"" + usr_input_ + "\" is not a public IP\n"};
}

auto app::location(char **argv) noexcept {
  auto first = capitalize(argv[1]);
  auto last = argv[2] == nullptr ? std::string{} : capitalize(argv[2]);

  usr_input_ = last.empty() ? first : first.append('_' + last);

  return status{};
}

status app::assign_input(int argc, char **argv) {
  return argc > 3 || argc == 1    ? invalid(argv)
         : !ip::valid_ip(argv[1]) ? location(argv)
         : argc > 2               ? invalid(argv)
                                  : ip(argv);
}

std::string app::_url() {
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
  return ip::valid_ip(usr_input_) ? " at " : " in ";
}

std::string app::usr_input() const {
  std::string s{usr_input_};
  std::replace(begin(s), end(s), '_', ' ');
  return s;
}

std::string app::datetime() {
  std::string temp;
  std::string t;
  std::string abbr;
  std::string d;

  int count{};

  while (fetched_ >> temp) {
    switch (count) {
    case 1:
      abbr = abbreviation(temp);
      break;
    case 5:
      d = date(temp);
      t = time(temp);
      break;
    case 7:
      return t + abbr + day{}[std::stoi(temp)] + d + preposition() +
             usr_input().append({'\n'});
    }
    count++;
  }

  return {};
}

status app::display_time() {
  auto result = datetime();
  return result.empty() ? status{1, "please update the app\n"}
                        : status{std::move(result)};
}

void app::_transform(std::string &s, int index) {
  std::transform(s.begin(), s.begin() + index, s.begin(),
                 [](unsigned char c) { return std::toupper(c); });
}

std::string &app::to_lower(std::string &s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  return s;
}

std::string app::capitalize(std::string s) {
  _transform(to_lower(s), 1);

  return s;
}

std::string app::find_timezone() {
  return ip::valid_ip(usr_input_) ? std::string{"/ip/"}.append(usr_input_)
                                  : timezns_.find(usr_input_);
}

namespace ip {
bool private_a(std::string const &ip) noexcept {
  std::regex pattern("([1][0])(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){3}");
  return std::regex_match(ip, pattern);
}

bool private_b(std::string const &ip) noexcept {
  std::regex pattern("([1][7][2])(\\.(1[6-9]|2[0-9]|3[01]))(\\.([01]?[0-9][0-9]"
                     "?|2[0-4][0-9]|25[0-5])){2}");
  return std::regex_match(ip, pattern);
}

bool private_c(std::string const &ip) noexcept {
  std::regex pattern("([1][9][2])(\\.([1][6][8]))(\\.([01]?[0-9][0-9]?|2[0-4]["
                     "0-9]|25[0-5])){2}");
  return std::regex_match(ip, pattern);
}

bool private_ip(std::string const &ip) noexcept {
  return private_a(ip) || private_b(ip) || private_c(ip);
}

bool public_ip(std::string const &ip) noexcept { return !private_ip(ip); }

bool valid_ip(std::string const &item) noexcept {
  std::regex pattern("([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])(\\.([01]?[0-9][0-"
                     "9]?|2[0-4][0-9]|25[0-5])){3}");
  return std::regex_match(item, pattern);
}
} // namespace ip
} // namespace world_time
