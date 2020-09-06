#include "addartistdialog.h"
#include "cddb.h"

#include <QDebug>

#include <QSqlQuery>

AddArtistDialog::AddArtistDialog(QWidget *parent) : ArtistDialog(parent)
{
    setWindowTitle(tr("Add Artist to Database"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AddArtistDialog::addArtistToDatabase);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AddArtistDialog::reject);
}

void AddArtistDialog::addArtistToDatabase()
{
    // Make sure a name was provided
    if (nameLineEdit->text() == "")
    {
        qWarning() << "Attempted to add unnamed artist to database";
        reject(); // TODO: This should make a warning dialog appear instead!
    }

    cddb::Artist artist(0);

    fillArtistDetails(artist);

    cddb::addArtist(artist);

    accept();
}
