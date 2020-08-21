#include "artistdialog.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

ArtistDialog::ArtistDialog(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *dataLayout = new QHBoxLayout;
    QFormLayout *leftLayout = new QFormLayout;
    QVBoxLayout *rightLayout = new QVBoxLayout;

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    setLayout(mainLayout);
    mainLayout->addLayout(dataLayout);
    mainLayout->addWidget(buttonBox);
    dataLayout->addLayout(leftLayout);
    dataLayout->addLayout(rightLayout);

    nameLineEdit = new QLineEdit;
    nameLineEdit->setToolTip(tr("The name by which the artist will appear in the database. E.g. \"The Beatles\", \"大貫妙子\"."));
    sortNameLineEdit = new QLineEdit;
    sortNameLineEdit->setToolTip(tr("The name by which the artist will appear in the database. E.g. \"Beatles, The\", \"おおぬきたえこ\"."));
    localizedNameLineEdit = new QLineEdit;
    localizedNameLineEdit->setToolTip(tr("The artist's name in another language. E.g. \"ビートルズ\", \"Taeko Ohnuki\"."));
    countryLineEdit = new QLineEdit;
    leftLayout->addRow(tr("Artist Name"), nameLineEdit);
    leftLayout->addRow(tr("Sort By"), sortNameLineEdit);
    leftLayout->addRow(tr("Localized Name"), localizedNameLineEdit);
    leftLayout->addRow(tr("Country of Origin"), countryLineEdit);

    QGroupBox *notesGroupBox = new QGroupBox(tr("Notes"));
    QVBoxLayout *notesGroupBoxLayout = new QVBoxLayout;
    notesTextEdit = new QTextEdit();
    notesTextEdit->setToolTip(tr("Personal notes on the artist. May be written in Markdown format."));
    notesGroupBoxLayout->addWidget(notesTextEdit);
    notesGroupBox->setLayout(notesGroupBoxLayout);
    rightLayout->addWidget(notesGroupBox);
}
