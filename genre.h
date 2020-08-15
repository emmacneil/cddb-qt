#ifndef GENRE_H
#define GENRE_H

#include <optional>
#include <string>
#include <vector>

namespace Cddb {
class Genre
{
public:
    Genre();
private:
    // TODO: Change string to something with unicode support --- ICU?
    std::string name; // Name of genre
    std::optional<int> parentID; // ID number of parent genre
    std::vector<int> relatedGenreIDs; // ID numbers of related genres
    std::string notes; // Notes about the genre
};
}
#endif // GENRE_H
