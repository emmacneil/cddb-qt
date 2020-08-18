#ifndef CDDB_H
#define CDDB_H

#include "genre.h"

#include <QString>

namespace cddb
{
std::optional<Genre> getGenre(int genreID);
void init(QString filename);
void seedDatabase();
} // namespace cddb
#endif // CDDB_H
