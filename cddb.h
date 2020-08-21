#ifndef CDDB_H
#define CDDB_H

#include "artist.h"
#include "genre.h"

#include <QString>

namespace cddb
{
std::optional<Artist> getArtist(int artistID);
std::optional<Genre> getGenre(int genreID);
void init(QString filename);
void seedDatabase();
} // namespace cddb
#endif // CDDB_H
