#include "addartistdialog.h"

#include <QSqlQuery>

AddArtistDialog::AddArtistDialog(QWidget *parent) : ArtistDialog(parent)
{
    setWindowTitle(tr("Add Artist to Database"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AddArtistDialog::addArtistToDatabase);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AddArtistDialog::reject);
}

void AddArtistDialog::addArtistToDatabase()
{
    QSqlQuery query;
    query.prepare("INSERT INTO artist (name, sort_name, localized_name, country, notes) values (?, ?, ?, ?, ?)");
    query.bindValue(0, nameLineEdit->text());
    query.bindValue(1, sortNameLineEdit->text());
    query.bindValue(2, localizedNameLineEdit->text());
    query.bindValue(3, countryLineEdit->text());
    query.bindValue(4, notesTextEdit->toPlainText());
    query.exec();

    accept();
}
