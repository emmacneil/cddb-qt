#include "artist.h"
#include "cddb.h"
#include "editartistdialog.h"

#include <QDebug>
#include <QPushButton>

#include <QSqlError>
#include <QSqlQuery>

EditArtistDialog::EditArtistDialog(int artistID, QWidget *parent) : ArtistDialog(parent), artistID(artistID)
{
    setWindowTitle(tr("Edit Artist in Database"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &EditArtistDialog::editArtistInDatabase);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &EditArtistDialog::reject);

    std::optional<cddb::Artist> artist = cddb::getArtist(artistID);
    if (artist.has_value())
    {
        nameLineEdit->setText(artist.value().getName());
        sortNameLineEdit->setText(artist.value().getSortName());
        localizedNameLineEdit->setText(artist.value().getLocalizedName());
        countryLineEdit->setText(artist.value().getCountry());
        notesTextEdit->setText(artist.value().getNotes());
    }
    else
    {
        // Something has gone wrong and we don't have an artist to edit.
        // Seems we can't close the dialog from within the constructor (?)
        // For now, just make fields uneditable and disable OK button.
        qWarning() << QString("EditArtistDialog opened with invalid artistID(%1).").arg(artistID);
        nameLineEdit->setEnabled(false);
        sortNameLineEdit->setEnabled(false);
        localizedNameLineEdit->setEnabled(false);
        countryLineEdit->setEnabled(false);
        notesTextEdit->setEnabled(false);
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }

}

void EditArtistDialog::editArtistInDatabase()
{
    QSqlQuery query;
    query.prepare("UPDATE artist SET "
                  "name = ?, "
                  "sort_name = ?, "
                  "localized_name = ?, "
                  "country = ?, "
                  "notes = ? "
                  "WHERE id = ?");
    query.bindValue(0, nameLineEdit->text());
    query.bindValue(1, sortNameLineEdit->text());
    query.bindValue(2, localizedNameLineEdit->text());
    query.bindValue(3, countryLineEdit->text());
    query.bindValue(4, notesTextEdit->toPlainText());
    query.bindValue(5, artistID);
    if (!query.exec())
    {
        qWarning() << "Failed to update artist information.";
        qWarning() << query.lastError();
        reject();
    }

    accept();
}
