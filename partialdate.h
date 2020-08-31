#ifndef PARTIALDATE_H
#define PARTIALDATE_H

/* cddb::PartialDate
 *
 * A class that can hold a date to a varying level of precision. A date may be given in the form
 * YYYY-MM-DD, YYYY-MM, or YYYY. In fact, the year does not have to be four digits. It may be
 * anywhere from 32768 BC to 32767 AD.
 *
 * Dates are immutable
 */

#include <stdint.h>
#include <string>

namespace cddb
{
class PartialDate
{
public:
    PartialDate(int16_t y = 0, uint8_t m = 0, uint8_t d = 0);
    PartialDate(const PartialDate &other);

    std::string toString() const;
    uint16_t getDay();
    uint8_t getMonth();
    uint8_t getYear();

    friend bool operator< (const PartialDate &lhs, const PartialDate &rhs);
    friend bool operator> (const PartialDate &lhs, const PartialDate &rhs);
    friend bool operator<= (const PartialDate &lhs, const PartialDate &rhs);
    friend bool operator>= (const PartialDate &lhs, const PartialDate &rhs);
    friend bool operator== (const PartialDate &lhs, const PartialDate &rhs);

private:
    const uint16_t year;
    const uint8_t month;
    const uint8_t day;

    bool isLeapYear() const;
    bool isValid() const;
};
} // namespace cddb
#endif // PARTIALDATE_H
