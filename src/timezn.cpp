#include "timezn.h"

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
    return std::string{"/timezone"}
        + insert_slash(region())
        + insert_slash(location())
        + insert_slash(area());
}

std::string timezn::insert_slash(std::string const& item) const
{
    return item.empty() ? item : '/' + item;
}