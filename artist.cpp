#include "artist.h"

namespace cddb {

Artist::Artist(int id)
    : id(id), name(""), sortName(""), localizedName(""), country(""), notes(""), score(0)
{
    // ...
}

Artist::Artist(const Artist &other)
    : id(other.id)
{
    name = other.name;
    sortName = other.sortName;
    localizedName = other.localizedName;
    country = other.country;
    notes = other.notes;
    score = other.score;
}

QString Artist::getCountry() const
{
    return country;
}

int Artist::getID() const
{
    return id;
}

QString Artist::getLocalizedName() const
{
    return localizedName;
}

QString Artist::getName() const
{
    return name;
}

QString Artist::getNotes() const
{
    return notes;
}

int Artist::getScore() const
{
    return score;
}

QString Artist::getSortName() const
{
    return sortName;
}

void Artist::setCountry(const QString &value)
{
    country = value;
}

void Artist::setLocalizedName(const QString &value)
{
    localizedName = value;
}

void Artist::setName(const QString &value)
{
    name = value;
}

void Artist::setNotes(const QString &value)
{
    notes = value;
}

void Artist::setScore(int value)
{
    score = value;
}

void Artist::setSortName(const QString &value)
{
    sortName = value;
}
}
