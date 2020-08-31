#include "addalbumdialog.h"
#include "cddb.h"

#include <QDebug>
#include <QSqlQuery>

AddAlbumDialog::AddAlbumDialog(QWidget *parent) : AlbumDialog(parent)
{
    setWindowTitle(tr("Add Album to Database"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AddAlbumDialog::addAlbumToDatabase);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AddAlbumDialog::reject);
}

void AddAlbumDialog::addAlbumToDatabase()
{
    cddb::Album album;

    album.setTitle(titleLineEdit->text());
    album.setSortTitle(sortTitleLineEdit->text().isEmpty() ? titleLineEdit->text() : sortTitleLineEdit->text());
    album.setLocalizedTitle(localizedTitleLineEdit->text().isEmpty() ? QString("") : localizedTitleLineEdit->text());

    std::optional<int> releaseTypeID = cddb::getReleaseTypeID(releaseTypeComboBox->currentText());
    if (releaseTypeID.has_value())
        album.setRating(releaseTypeID.value());

    album.setReleaseDate(releaseDateComboBox->getPartialDate());

    std::optional<int> ratingID = cddb::getRatingID(ratingComboBox->currentText());
    if (ratingID.has_value())
        album.setRating(ratingID.value());

    album.setBacklogged(backlogCheckBox->isChecked());
    album.setOwned(ownedCheckBox->isChecked());
    album.setSeeking(seekingCheckBox->isChecked());
    album.setWishlisted(wishlistCheckBox->isChecked());

    // Artists
    for (int i = 0; i < artistListWidget->count(); i++)
    {
        QString artistName = artistListWidget->item(i)->text();
        std::vector<int> artistIDs = cddb::getArtistIDs(artistName);
        if (artistIDs.size() == 0)
            throw std::runtime_error("No artists found matching name");
        if (artistIDs.size() > 1)
            throw std::runtime_error("Multiple artists found with same name");
        album.addArtist(artistIDs[0]);
    }

    // Featured Artists
    for (int i = 0; i < featuredArtistListWidget->count(); i++)
    {
        QString artistName = featuredArtistListWidget->item(i)->text();
        std::vector<int> artistIDs = cddb::getArtistIDs(artistName);
        if (artistIDs.size() == 0)
            throw std::runtime_error("No artists found matching name");
        if (artistIDs.size() > 1)
            throw std::runtime_error("Multiple artists found with same name");
        album.addFeaturedArtist(artistIDs[0]);
    }

    // Genres
    for (int i = 0; i < genreListWidget->count(); i++)
    {
        QString genreName = genreListWidget->item(i)->text();
        std::optional<int> genreID = cddb::getGenreID(genreName);
        if (!genreID.has_value())
            throw std::runtime_error("No genre found matching name");
        album.addGenre(genreID.value());
    }

    album.setNotes(notesTextEdit->toMarkdown());

    cddb::addAlbum(album);

    accept();
}
