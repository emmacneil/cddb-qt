#ifndef GENRE_H
#define GENRE_H

#include <optional>
#include <string>
#include <vector>

#include <QString>

namespace cddb {
class Genre
{
public:
    Genre() : id(0), name(""), parentIDs(), similarIDs(), notes("") {}
    Genre(int id, QString name) : id(id), name(name), parentIDs(), similarIDs(), notes("") {}

    void addParentID(int parentID);
    void addSimilarID(int similarID);

    int getID() {return id;}
    QString getName() {return name;}
    QString getNotes() {return notes;}
    std::vector<int> getParentIDs() {return parentIDs;}
    std::vector<int> getSimilarIDs() {return similarIDs;}

    bool isParent(int parentID);
    bool isSimilar(int similarID);

    void removeParentID(int parentID);
    void removeSimilarID(int similarID);

    void setID(int newID) {id = newID;}
    void setName(QString newName) {name = newName;}
    void setNotes(QString newNotes) {notes= newNotes;}

private:
    int id;
    QString name; // Name of genre
    std::vector<int> parentIDs; // ID numbers of parent genres
    std::vector<int> similarIDs; // ID numbers of similar genres
    QString notes; // Notes about the genre

    int indexOfParentID(int parentID);
    int indexOfSimilarID(int similarID);
};
}
#endif // GENRE_H
