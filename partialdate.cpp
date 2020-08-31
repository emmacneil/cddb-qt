#include "partialdate.h"

#include <stdexcept>

namespace cddb
{
PartialDate::PartialDate(int16_t y, uint8_t m, uint8_t d) : year(y), month(m), day(d)
{
    // Make sure the date is valid
    if (!isValid())
        throw std::invalid_argument("Invalid date");
}

PartialDate::PartialDate(const PartialDate &other) : year(other.year), month(other.month), day(other.day)
{
    // ...
}

bool PartialDate::isLeapYear() const
{
    if (year % 4) // If year is not divisible by 4
        return false;
    if (year % 100) // If year is not divisible by 100
        return true;
    if (year % 400) // If year is not divisible by 400
        return false;
    return true;
}

bool PartialDate::isValid() const
{
    if (day > 31)
        return false;
    if (month > 12)
        return false;
    if ((month == 0) && (day > 0))
        return false;
    if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
    {
        if (day > 30)
            return false;
    }
    if (month == 2)
    {
        if (day > 29)
            return false;
        else if ((day == 29) && !isLeapYear())
            return false;
    }
    return true;
}

std::string PartialDate::toString() const
{
    std::string ret = std::to_string(year);
    if (month != 0)
        ret = ret + "-" + std::to_string(month);
    if (day != 0)
        ret = ret + "-" + std::to_string(day);
    return ret;
}

uint16_t PartialDate::getDay()
{
    return day;
}

uint8_t PartialDate::getMonth()
{
    return month;
}

uint8_t PartialDate::getYear()
{
    return year;
}

bool operator< (const PartialDate &lhs, const PartialDate &rhs)
{
    if (lhs.year < rhs.year)
        return true;
    if (lhs.year == rhs.year)
    {
        if (lhs.month == 0)
            return rhs.month != 0;
        if (rhs.month == 0)
            return lhs.month != 0;
        if (lhs.month < rhs.month)
            return true;
        if (lhs.month == rhs.month)
        {
            if (lhs.day == 0)
                return rhs.day != 0;
            if (rhs.day == 0)
                return lhs.day != 0;
            if (lhs.day < rhs.day)
                return true;
        }
    }
    return false;
}

bool operator> (const PartialDate &lhs, const PartialDate &rhs)
{
    return rhs < lhs;
}

bool operator<= (const PartialDate &lhs, const PartialDate &rhs)
{
    return !(rhs < lhs);
}

bool operator>= (const PartialDate &lhs, const PartialDate &rhs)
{
    return !(lhs < rhs);
}

bool operator== (const PartialDate &lhs, const PartialDate &rhs)
{
    return ((lhs.year == rhs.year) && (lhs.month == rhs.month) && (lhs.day == rhs.day));
}
}
