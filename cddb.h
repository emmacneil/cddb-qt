#ifndef CDDB_H
#define CDDB_H

#include "album.h"
#include "artist.h"
#include "genre.h"

#include <QString>

namespace cddb
{
void createTables();
void dropTables();
void addAlbum(Album &album);
std::optional<Album> getAlbum(int albumID);
std::vector<int> getAlbumArtistIDs(int albumID);
std::vector<int> getAlbumFeaturedArtistIDs(int albumID);
std::vector<int> getAlbumGenreIDs(int albumID);
std::optional<int> getAlbumRatingID(int albumID);
std::optional<Artist> getArtist(int artistID);
std::vector<int> getArtistIDs(QString artistName);
std::optional<Genre> getGenre(int genreID);
std::optional<int> getGenreID(QString genreName);
std::optional<int> getReleaseTypeID(QString type);
std::optional<int> getRatingID(QString letter);
void init(QString filename);
void seedDatabase();
} // namespace cddb
#endif // CDDB_H
