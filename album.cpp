#include "album.h"

#include <QDebug>

namespace cddb
{
Album::Album(const int id)
    : id(id)
{
    releaseDate = nullptr;
}

Album::Album(const Album &other)
    : id(other.id)
{
    releaseTypeID = other.releaseTypeID;
    ratingID = other.ratingID;
    backlog = other.backlog;
    owned = other.owned;
    seeking = other.seeking;
    wishlist = other.wishlist;
    releaseDate = new PartialDate(*(other.releaseDate));
    title = other.title;
    sortTitle = other.sortTitle;
    localizedTitle = other.localizedTitle;
    notes = other.notes;
    artistIDs = other.artistIDs;
    featuredArtistIDs = other.featuredArtistIDs;
    genreIDs = other.genreIDs;
}

Album::~Album()
{
    if (releaseDate)
        delete releaseDate;
}

void Album::addArtist(int artistID)
{
    // Check if artist is already in the list
    // If not, add it
    bool alreadyIn = false;
    for (int id : artistIDs)
        if (id == artistID)
            alreadyIn = true;
    if (!alreadyIn)
        artistIDs.push_back(artistID);
}

void Album::addFeaturedArtist(int artistID)
{
    // Check if artist is already in the list
    // If not, add it
    bool alreadyIn = false;
    for (int id : featuredArtistIDs)
        if (id == artistID)
            alreadyIn = true;
    if (!alreadyIn)
        featuredArtistIDs.push_back(artistID);
}

void Album::addGenre(int genreID)
{
    // Check if genreis already in the list
    // If not, add it
    bool alreadyIn = false;
    for (int id : genreIDs)
        if (id == genreID)
            alreadyIn = true;
    if (!alreadyIn)
        genreIDs.push_back(genreID);
}

std::vector<int> Album::getArtistIDs() const
{
    return artistIDs;
}

std::vector<int> Album::getFeaturedArtistIDs() const
{
    return featuredArtistIDs;
}

std::vector<int> Album::getGenreIDs() const
{
    return genreIDs;
}

int Album::getID() const
{
    return id;
}

QString Album::getLocalizedTitle() const
{
    return localizedTitle;
}

QString Album::getNotes() const
{
    return notes;
}

int Album::getRatingID() const
{
    return ratingID;
}

PartialDate Album::getReleaseDate() const
{
    return *releaseDate;
}

int Album::getReleaseTypeID() const
{
    return releaseTypeID;
}

QString Album::getSortTitle() const
{
    return sortTitle;
}

QString Album::getTitle() const
{
    return title;
}

bool Album::isBacklogged() const
{
    return backlog;
}

bool Album::isOwned() const
{
    return owned;
}

bool Album::isSeeking() const
{
    return seeking;
}

bool Album::isWishlisted() const
{
    return wishlist;
}

void Album::removeArtist(int artistID)
{

}

void Album::removeFeaturedArtist(int artistID)
{

}

void Album::removeGenre(int artistID)
{

}

void Album::setArtistIDs(std::vector<int> &vec)
{
    artistIDs = vec;
}

void Album::setBacklogged(bool value)
{
    backlog = value;
}

void Album::setFeaturedArtistIDs(std::vector<int> &vec)
{
    featuredArtistIDs = vec;
}

void Album::setGenreIDs(std::vector<int> &vec)
{
    genreIDs = vec;
}

void Album::setLocalizedTitle(const QString &value)
{
    localizedTitle = value;
}

void Album::setOwned(bool value)
{
    owned = value;
}

void Album::setRatingID(int value)
{
    ratingID = value;
}

void Album::setReleaseDate(const PartialDate &value)
{
    if (releaseDate)
        delete releaseDate;
    releaseDate = new PartialDate(value);
}

void Album::setReleaseTypeID(int value)
{
    releaseTypeID = value;
}

void Album::setSeeking(bool value)
{
    seeking = value;
}

void Album::setSortTitle(const QString &value)
{
    sortTitle = value;
}

void Album::setTitle(const QString &value)
{
    title = value;
}

void Album::setWishlisted(bool value)
{
    wishlist = value;
}

void Album::setNotes(const QString &value)
{
    notes = value;
}

} // namespace cddb
