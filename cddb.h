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
void addArtist(Artist &artist);
std::optional<Album> getAlbum(int albumID);
std::vector<int> getAlbumArtistIDs(int albumID);
std::vector<int> getAlbumFeaturedArtistIDs(int albumID);
std::vector<int> getAlbumGenreIDs(int albumID);
std::optional<int> getAlbumRatingID(int albumID);
Artist getArtistNoOpt(int artistID);
std::optional<Artist> getArtist(int artistID);
std::vector<int> getArtistIDs(QString artistName);
std::optional<Genre> getGenre(int genreID);
std::optional<int> getGenreID(QString genreName);
std::optional<QString> getRating(int id);
std::optional<int> getRatingID(QString type);
std::optional<QString> getReleaseType(int id);
std::optional<int> getReleaseTypeID(QString type);
void init(QString filename);
void seedDatabase();
void updateAlbum(Album &album);
void updateArtist(Artist &artist);
} // namespace cddb
#endif // CDDB_H
