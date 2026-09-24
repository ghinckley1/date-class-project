#ifndef DATE_DATE_HPP
#define DATE_DATE_HPP

#include <iostream>
#include <string>

namespace util {

    class Date {
    public:
        // struct thrown on invalid dates
        struct Invalid {
            int day;
            int month;                
            int year;
        };

        // options
        enum class Order {
            MonthDayYear, DayMonthYear, YearMonthDay
        };
        static Order order;
        static char separator;

        // constructors
        Date();
        Date(int day, int month, int year);

        // getters            
        int day() const;
        int month() const;
        int year() const;

        // setters
        void day(int day);
        void month(int month);
        void year(int year);
        // read-only properties
        std::string monthName() const;
        std::string dayName() const;
        // operations
        void advance(int days = 1);
        void print(std::ostream& os) const;
        
        static Date now();

    private:
        int day_;
        int month_;
        int year_;

        static bool isValidDate(int day, int month, int year);
    };
}

#endif //DATE_DATE_HPP
