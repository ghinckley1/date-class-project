#define _CRT_SECURE_NO_WARNINGS
#include "date.hpp"
#include <ctime>

namespace util {

    // initialization
    Date::Order Date::order = Date::Order::MonthDayYear;
    char Date::separator = '/';

    bool Date::isValidDate(int day, int month, int year) {
        std::tm timeInfo = {};
        timeInfo.tm_mday = day;
        timeInfo.tm_mon = month - 1;
        timeInfo.tm_year = year - 1900;
        //lets mktime auto-detect daylight savings, otherwise dates shift unexpectedly
        timeInfo.tm_isdst = -1;

        // make the copy
        std::tm temp = timeInfo;
        std::time_t result = std::mktime(&temp);

        if (result == -1) {
            return false; }

        // if any of the values were changed, then that date was invalid
        if (temp.tm_mday != timeInfo.tm_mday || temp.tm_mon != timeInfo.tm_mon || temp.tm_year != timeInfo.tm_year) {
            return false;
        }
        return true;
    }

    Date::Date() {
        std::time_t zeroTime = 0;
        std::tm* localTimeInfo = std::localtime(&zeroTime);

        day_ = localTimeInfo->tm_mday;
        month_ = localTimeInfo->tm_mon + 1;
        year_ = localTimeInfo->tm_year + 1900;
    }

    Date::Date(int day, int month, int year) {
        if (!isValidDate(day, month, year)) {
            throw Date::Invalid{ day, month, year };
        }
        day_ = day;
        month_ = month;
        year_ = year;
    }

    int Date::day() const { return day_; }
    int Date::month() const { return month_; }
    int Date::year() const { return year_; }

    void Date::day(int day) {
        if (!isValidDate(day, month_, year_)) {
            throw Date::Invalid{ day, month_, year_ };
        }
        day_ = day;
    }

    void Date::month(int month) {
        if (!isValidDate(day_, month, year_)) {
            throw Date::Invalid{ day_, month, year_ };
        }
        month_ = month;
    }

    void Date::year(int year) {
        if (!isValidDate(day_, month_, year)) {
            throw Date::Invalid{ day_, month_, year };
        }
        year_ = year;
    }

    // read only properties
    std::string Date::monthName() const {
        static const std::string months[] = {
                "", "January", "February", "March", "April", "May", "June",
                "July", "August", "September", "October", "November", "December"
        };
        if (month_ >= 1 && month_ <= 12) {
            return months[month_];
        }
        return "";
    }

    std::string Date::dayName() const {
        std::tm timeInfo = {};
        timeInfo.tm_mday = day_;
        timeInfo.tm_mon = month_ - 1;
        timeInfo.tm_year = year_ - 1900;
        timeInfo.tm_isdst = -1;
        std::mktime(&timeInfo);

        static const std::string days[] = {
                "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
        };

        if (timeInfo.tm_wday >= 0 && timeInfo.tm_wday <= 6) {
            return days[timeInfo.tm_wday];
        }
        return "";
    }

    void Date::advance(int days) {
        std::tm timeInfo = {};
        timeInfo.tm_mday = day_;
        timeInfo.tm_mon = month_ - 1;
        timeInfo.tm_year = year_ - 1900;
        timeInfo.tm_isdst = -1;

        std::time_t seconds = std::mktime(&timeInfo);
        seconds += (static_cast<std::time_t>(days) * 24 * 60 * 60);

        std::tm* newTime = std::localtime(&seconds);
        day_ = newTime->tm_mday;
        month_ = newTime->tm_mon + 1;
        year_ = newTime->tm_year + 1900;
    }

    void Date::print(std::ostream& os) const {
        if (order == Order::MonthDayYear) {
            os << month_ << separator << day_ << separator << year_;
        }
        else if (order == Order::DayMonthYear) {
            os << day_ << separator << month_ << separator << year_;
        }
        else if (order == Order::YearMonthDay) {
            os << year_ << separator << month_ << separator << day_;
        }
    }

    Date Date::now() {
        std::time_t currentTime = std::time(nullptr);
        std::tm* localTimeInfo = std::localtime(&currentTime);
        Date d;
        d.day_ = localTimeInfo->tm_mday;
        d.month_ = localTimeInfo->tm_mon + 1;
        d.year_ = localTimeInfo->tm_year + 1900;
        return d;


    }
}
