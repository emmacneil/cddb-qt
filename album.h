#ifndef ALBUM_H
#define ALBUM_H

#include "partialdate.h"

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

    std::vector<int> getArtists() const;
    std::vector<int> getFeaturedArtists() const;
    std::vector<int> getGenres() const;
    int getId() const;
    QString getLocalizedTitle() const;
    QString getNotes() const;
    int getRating() const;
    PartialDate getReleaseDate() const;
    int getReleaseType() const;
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
    void setRating(int value);
    void setReleaseDate(const PartialDate &value);
    void setReleaseType(int value);
    void setSeeking(bool value);
    void setSortTitle(const QString &value);
    void setTitle(const QString &value);
    void setWishlisted(bool value);

private:
    const int id;           // Unique identifier for the album, for looking it up in SQLite
    int releaseType;  // Album, EP, Single, etc.
    int rating;
    bool backlog;  // True if the album is in the user's backlog
    bool owned;    // True if the user owns a copy of this album, whether physically or digitally
    bool seeking;  // True if the user would like to hear or buy the album, but cannot find it
    bool wishlist; // True if the album is on the user's wishlist
    PartialDate * releaseDate;
    QString title;
    QString sortTitle;
    QString localizedTitle;
    QString notes;
    std::vector<int> artists;
    std::vector<int> featuredArtists;
    std::vector<int> genres;
};

} // namespace cddb

#endif // ALBUM_H
