#include "artist.h"

namespace cddb {

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

QString Artist::getSortName() const
{
    return sortName;
}

void Artist::setCountry(const QString &value)
{
    country = value;
}

void Artist::setID(int value)
{
    id = value;
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

void Artist::setSortName(const QString &value)
{
    sortName = value;
}
}
