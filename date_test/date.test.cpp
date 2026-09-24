//
// Created by George Hinckley on 9/21/26.
//

#include <gtest/gtest.h>
#include <sstream>
#include "date.h"

using util::Date;

// test default constructor
TEST(DefaultCtor, HasCorrectDefaultValue) {
    Date d;
    EXPECT_EQ(d.day(), 1);
    EXPECT_EQ(d.month(), 1);
    EXPECT_EQ(d.year(), 1970);
}

// test value constructor
TEST(ValueCtor, ValidDateInitilization) {
    Date d { 20, 6, 2005 };
    EXPECT_EQ(d.day(), 20);
    EXPECT_EQ(d.month(), 6);
    EXPECT_EQ(d.year(), 2005);
}
TEST(ValueCtor, ThrowsInvalidDate) {
    EXPECT_THROW(Date(29, 2, 2001), Date::Invalid);
}

// test setters
TEST(Setters, ValidSettersWork) {
    Date d;
    d.day(20);
    d.month(6);
    d.year(2005);

    EXPECT_EQ(d.day(), 20);
    EXPECT_EQ(d.month(), 6);
    EXPECT_EQ(d.year(), 2005);
}

TEST(Setters, ThrowsInvalidSet) {
    Date d{20, 6, 2005};
    EXPECT_THROW(d.day(31), Date::Invalid);
    EXPECT_EQ(d.day(), 20);
}

TEST(Props, MonthAndDayNames) {
    Date d{20, 6, 2005};

    EXPECT_EQ(d.monthName(), "June");
    EXPECT_EQ(d.dayName(), "Monday");
}

// test advance function with pos and neg
TEST(Advance, MoveFowardAndBackward) {
    Date d{20, 6, 2005};
    d.advance(1);
    EXPECT_EQ(d.day(), 21);
    EXPECT_EQ(d.month(), 6);
    EXPECT_EQ(d.year(), 2005);

    d.advance(-22);
    EXPECT_EQ(d.day(), 30);
    EXPECT_EQ(d.month(), 5);
    EXPECT_EQ(d.year(), 2005);
}

// test print and formatting
TEST(Print, FormatCorrectly) {
    Date::order = Date::Order::MonthDayYear;
    Date::separator = '/';
    Date d{20, 6, 2005};
    std::ostringstream output1;
    d.print(output1);
    EXPECT_EQ(output1.str(), "6/20/2005");

    Date::order = Date::Order::DayMonthYear;
    Date::separator = '-';

    std::ostringstream output2;
    d.print(output2);
    EXPECT_EQ(output2.str(), "20-6-2005");
}

// test now method returning a date that makes sense to be the current date
TEST(Now, ReturnsCurrentDate) {
    Date today = Date::now();
    EXPECT_EQ(today.year(), 2026);
    EXPECT_EQ(today.month(), 9);
    EXPECT_GE(today.day(), 23);
    EXPECT_LE(today.day(), 30);
}