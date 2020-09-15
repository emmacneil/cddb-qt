#ifndef ALBUM_H
#define ALBUM_H

#include "partialdate.h"
#include "release_type.h"

#include <vector>

#include <QString>

namespace cddb
{

class Album
{
public:
    Album(const int id = 0);
    Album(const Album &other);
    ~Album();

    void addArtist(int artistID);
    void addFeaturedArtist(int artistID);
    void addGenre(int genreID);

    std::vector<int> getArtistIDs() const;
    std::vector<int> getFeaturedArtistIDs() const;
    std::vector<int> getGenreIDs() const;
    int getID() const;
    QString getLocalizedTitle() const;
    QString getNotes() const;
    int getRatingID() const;
    PartialDate getReleaseDate() const;
    int getReleaseTypeID() const;
    QString getSortTitle() const;
    QString getTitle() const;

    bool isBacklogged() const;
    bool isOwned() const;
    bool isSeeking() const;
    bool isWishlisted() const;

    void removeArtist(int artistID);
    void removeFeaturedArtist(int artistID);
    void removeGenre(int artistID);

    void setArtistIDs(std::vector<int> &artistIDs);
    void setBacklogged(bool value);
    void setFeaturedArtistIDs(std::vector<int> &artistIDs);
    void setGenreIDs(std::vector<int> &genreIDs);
    void setLocalizedTitle(const QString &value);
    void setNotes(const QString &value);
    void setOwned(bool value);
    void setRatingID(int value);
    void setReleaseDate(const PartialDate &value);
    void setReleaseTypeID(int value);
    void setSeeking(bool value);
    void setSortTitle(const QString &value);
    void setTitle(const QString &value);
    void setWishlisted(bool value);

private:
    const int id;           // Unique identifier for the album, for looking it up in SQLite
    int releaseTypeID; // Album, EP, Single, etc.
    int ratingID;
    bool backlog;  // True if the album is in the user's backlog
    bool owned;    // True if the user owns a copy of this album, whether physically or digitally
    bool seeking;  // True if the user would like to hear or buy the album, but cannot find it
    bool wishlist; // True if the album is on the user's wishlist
    PartialDate * releaseDate;
    QString title;
    QString sortTitle;
    QString localizedTitle;
    QString notes;
    std::vector<int> artistIDs;
    std::vector<int> featuredArtistIDs;
    std::vector<int> genreIDs;
};

} // namespace cddb

#endif // ALBUM_H
