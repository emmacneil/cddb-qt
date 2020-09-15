#include "album.h"
#include "cddb.h"
#include "editalbumdialog.h"

#include <QDebug>

EditAlbumDialog::EditAlbumDialog(int albumID, QWidget *parent) : AlbumDialog(parent), albumID(albumID)
{
    setWindowTitle(tr("Edit Album in Database"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &EditAlbumDialog::editAlbumInDatabase);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &EditAlbumDialog::reject);

    std::optional<cddb::Album> album = cddb::getAlbum(albumID);
    if (album.has_value())
    {
        titleLineEdit->setText(album->getTitle());
        sortTitleLineEdit->setText(album->getSortTitle());
        localizedTitleLineEdit->setText(album->getLocalizedTitle());

        releaseDateComboBox->setPartialDate(album->getReleaseDate());

        std::optional<cddb::ReleaseType> releaseType = cddb::getReleaseType(album->getReleaseTypeID());
        if (releaseType.has_value())
            releaseTypeComboBox->setCurrentText(releaseType->getName());

        releaseDateComboBox->setPartialDate(album->getReleaseDate());

        // Rating
        std::optional<cddb::Rating> rating = cddb::getRating(album->getRatingID());
        if (rating.has_value())
            ratingComboBox->setCurrentText(rating->getLetter());
        else
            ratingComboBox->setCurrentText(tr("None"));

        backlogCheckBox->setChecked(album->isBacklogged());
        ownedCheckBox->setChecked(album->isOwned());
        seekingCheckBox->setChecked(album->isSeeking());
        wishlistCheckBox->setChecked(album->isWishlisted());

        // Artists
        for (int artistID : album->getArtistIDs())
        {
            std::optional<cddb::Artist> artist = cddb::getArtist(artistID);
            if (!artist.has_value())
                continue;
            artistListWidget->addItem(artist->getName());
        }

        // Featured Artists
        for (int artistID : album->getFeaturedArtistIDs())
        {
            std::optional<cddb::Artist> artist = cddb::getArtist(artistID);
            if (!artist.has_value())
                continue;
            featuredArtistListWidget->addItem(artist->getName());
        }

        // Genre
        for (int genreID : album->getGenreIDs())
        {
            std::optional<cddb::Genre> genre= cddb::getGenre(genreID);
            if (!genre.has_value())
                continue;
            genreListWidget->addItem(genre->getName());
        }

        notesTextEdit->setText(album->getNotes());
    }
    else
    {
        // ...
    }
}

void EditAlbumDialog::editAlbumInDatabase()
{
    cddb::Album album(albumID);

    fillAlbumDetails(album);

    cddb::updateAlbum(album);

    accept();
}
