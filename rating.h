#ifndef RATING_H
#define RATING_H

#include <QString>

namespace cddb
{
class Rating
{
public:
    Rating(int id = 0);
    bool operator<(Rating &other);
    bool operator==(Rating &other);

    int getID() const;
    QString getLetter() const;
    float getScore() const;

    void setLetter(QString str);
    void setScore(float val);

private:
    const int id;
    QString letter;
    float score;
};
} // namespace cddb
#endif // RATING_H
