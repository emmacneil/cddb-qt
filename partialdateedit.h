#ifndef PARTIALDATEEDIT_H
#define PARTIALDATEEDIT_H

#include "partialdate.h"

#include <QSpinBox>
#include <QFrame>
#include <QHBoxLayout>

class MonthSpinBox : public QSpinBox
{
public:
    MonthSpinBox(QWidget *parent = nullptr);

    QString textFromValue(int val) const override;
};

class PartialDateEdit : public QFrame
{
public:
    PartialDateEdit();
    cddb::PartialDate getPartialDate();
    void setPartialDate(const uint16_t year, const uint8_t month, const uint8_t day);
    void setPartialDate(const cddb::PartialDate &date);

private:
    QSpinBox yearComboBox;
    MonthSpinBox monthComboBox;
    QSpinBox dayComboBox;
    QHBoxLayout layout;
};

#endif // PARTIALDATEEDIT_H
