#include "partialdateedit.h"

#include <QDate>

MonthSpinBox::MonthSpinBox(QWidget *parent)
 : QSpinBox(parent)
{
}

QString MonthSpinBox::textFromValue(int val) const
{
    static const QStringList months({"N/A", "Jan", "Feb", "Mar", "Apr",
                                     "May", "Jun", "Jul", "Aug",
                                     "Sep", "Oct", "Nov", "Dec"});
    return (val >= 0) && (val <= 12) ? months[val] : "";
}

PartialDateEdit::PartialDateEdit()
 : yearComboBox(this), monthComboBox(this), dayComboBox(this), layout(this)
{
    yearComboBox.setRange(1900, 2100);
    yearComboBox.setValue(QDate::currentDate().year());

    monthComboBox.setRange(0, 12);

    dayComboBox.setRange(0, 31);
    dayComboBox.setSpecialValueText("N/A");

    layout.addWidget(&yearComboBox);
    layout.addWidget(&monthComboBox);
    layout.addWidget(&dayComboBox);
}

cddb::PartialDate PartialDateEdit::getPartialDate()
{
    // This can throw an error if the date is invalid (e.g. Feb 30th)
    return cddb::PartialDate(yearComboBox.value(), monthComboBox.value(), dayComboBox.value());
}
