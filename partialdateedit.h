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

private:
    QSpinBox yearComboBox;
    MonthSpinBox monthComboBox;
    QSpinBox dayComboBox;
    QHBoxLayout layout;
};

#endif // PARTIALDATEEDIT_H
