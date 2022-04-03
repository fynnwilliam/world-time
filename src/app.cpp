#include "app.h"

void app::tell() {
  check_arguments();
  update_url();
  fetch_time();
  display_time();
}

void app::fetch_time() { fetched_ << curlpp::options::Url(url_); }

auto app::invalid_argc() const {
  return std::invalid_argument("invalid number of arguments");
}

auto app::not_avaliable() const {
  return std::range_error("timezone not found");
}

void app::check_arguments() {
  if (argc_ > 3 || argc_ == 1) {
    throw invalid_argc();
  }

  usr_input_ = ip_address(argv_[1]) ? ip() : location();
}

void app::update_url() {
  std::string zone{find_timezone()};
  zone.empty() ? throw not_avaliable() : url_.append(zone).append(".txt");
}

void app::time(std::string const &t) {
  time_ = std::string{"It is "} + t.substr(t.find('T') + 1, 8);
}

void app::abbreviation(std::string const &a) {
  abbreviation_ = std::string{" "}.append(a);
}

void app::day(std::string const &d) {
  day_ = std::string{", "} + _day(std::stoi(d));
}

std::string app::month(std::string const &m) const {
  return std::string{", "} + _month(std::stoi(m));
}

void app::date(std::string const &d) {
  std::string year{d.substr(0, 4)};
  std::string m{d.substr(5, 2)};
  int day{std::stoi(d.substr(8, 2))};

  date_ = month(m) + ' ' + std::to_string(day) + ", " + year;
}

std::string app::preposition() const {
  return ip_address(usr_input_) ? " at " : " in ";
}

std::string app::usr_input() const {
  std::string s{usr_input_};
  std::replace(begin(s), end(s), '_', ' ');
  return s;
}

std::string app::_datetime() const {
  return time_ + abbreviation_ + day_ + date_ + preposition() + usr_input();
}

std::string app::datetime() {
  std::string temp;
  int count{};

  while (fetched_ >> temp) {
    if (count == 1) {
      abbreviation(temp);
    }
    if (count == 5) {
      date(temp);
      time(temp);
    }
    if (count == 7) {
      day(temp);
      return _datetime();
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

std::string app::ip() const {
  if (argc_ > 2) {
    throw invalid_argc();
  }

  std::string ip{argv_[1]};

  if (public_ip(ip)) {
    return ip;
  }
  throw std::out_of_range("\"" + ip + "\" is not a public IP");
}

std::string app::location() {
  std::string first = capitalize(argv_[1]);
  std::string second = !argv_[2] ? std::string{} : capitalize(argv_[2]);

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
