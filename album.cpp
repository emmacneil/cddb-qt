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
    releaseType = other.releaseType;
    rating = other.rating;
    backlog = other.backlog;
    owned = other.owned;
    seeking = other.seeking;
    wishlist = other.wishlist;
    releaseDate = new PartialDate(*(other.releaseDate));
    title = other.title;
    sortTitle = other.sortTitle;
    localizedTitle = other.localizedTitle;
    notes = other.notes;
    artists = other.artists;
    featuredArtists = other.featuredArtists;
    genres = other.genres;
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
    for (int id : artists)
        if (id == artistID)
            alreadyIn = true;
    if (!alreadyIn)
        artists.push_back(artistID);
}

void Album::addFeaturedArtist(int artistID)
{
    // Check if artist is already in the list
    // If not, add it
    bool alreadyIn = false;
    for (int id : featuredArtists)
        if (id == artistID)
            alreadyIn = true;
    if (!alreadyIn)
        featuredArtists.push_back(artistID);
}

void Album::addGenre(int genreID)
{
    // Check if genreis already in the list
    // If not, add it
    bool alreadyIn = false;
    for (int id : genres)
        if (id == genreID)
            alreadyIn = true;
    if (!alreadyIn)
        genres.push_back(genreID);
}

std::vector<int> Album::getArtists() const
{
    return artists;
}

std::vector<int> Album::getFeaturedArtists() const
{
    return featuredArtists;
}

std::vector<int> Album::getGenres() const
{
    return genres;
}

int Album::getId() const
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

int Album::getRating() const
{
    return rating;
}

PartialDate Album::getReleaseDate() const
{
    return *releaseDate;
}

int Album::getReleaseType() const
{
    return releaseType;
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
    artists = vec;
}

void Album::setBacklogged(bool value)
{
    backlog = value;
}

void Album::setFeaturedArtistIDs(std::vector<int> &vec)
{
    featuredArtists = vec;
}

void Album::setGenreIDs(std::vector<int> &vec)
{
    genres = vec;
}

void Album::setLocalizedTitle(const QString &value)
{
    localizedTitle = value;
}

void Album::setOwned(bool value)
{
    owned = value;
}

void Album::setRating(int value)
{
    rating = value;
}

void Album::setReleaseDate(const PartialDate &value)
{
    if (releaseDate)
        delete releaseDate;
    releaseDate = new PartialDate(value);
}

void Album::setReleaseType(int value)
{
    releaseType = value;
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
