#include "artist.h"
#include "cddb.h"

#include <math.h>

#include <QDebug>

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
    albumIDs.assign(other.albumIDs.begin(), other.albumIDs.end());
}

void Artist::addAlbumID(int albumID)
{
    albumIDs.push_back(albumID);
}

int Artist::computeScore()
{
    float fScore = 0.0f;
    for (int albumID : albumIDs)
    {
        std::optional<Album> album = getAlbum(albumID);
        if (!album.has_value())
        {
            qDebug() << "No album found with ID " << albumID;
            continue;
        }
        qDebug() << "Adding score for album" << albumID;

        // Get release type
        std::optional<ReleaseType> releaseType = cddb::getReleaseType(album->getReleaseTypeID());
        if (!releaseType.has_value())
        {
            qDebug() << "No release type found with ID " << album->getReleaseTypeID();
            continue;
        }

        // Get rating
        std::optional<Rating> rating = cddb::getRating(album->getRatingID());
        if (!rating.has_value())
        {
            qDebug() << "No rating found with ID " << album->getRatingID();
            continue;
        }

        float multiplier = releaseType->getMultiplier();
        float grade = rating->getScore();
        fScore += multiplier * pow(2.0f, grade);
        qDebug() << "Multiplier: " << multiplier;
        qDebug() << "Grade: " << grade;
        qDebug() << "Score: " << fScore;
    }
    score = (int)fScore;
    return score;
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
