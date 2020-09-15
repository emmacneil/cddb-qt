#include "rating.h"

namespace cddb
{
Rating::Rating(int id)
    : id(id)
{

}

bool Rating::operator<(Rating &other)
{
    return score < other.score;
}

bool Rating::operator==(Rating &other)
{
    return score == other.score;
}

int Rating::getID() const
{
    return id;
}

QString Rating::getLetter() const
{
    return letter;
}

float Rating::getScore() const
{
    return score;
}

void Rating::setLetter(QString str)
{
    letter = str;
}

void Rating::setScore(float val)
{
    score = val;
}

} // namespace cddb
