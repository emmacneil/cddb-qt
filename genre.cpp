#include "genre.h"

void cddb::Genre::addParentID(int parentID)
{
    // If parentID is not already in the list of parentIDs, then add it.
    if (!isParent(parentID))
        parentIDs.push_back(parentID);
}

void cddb::Genre::addSimilarID(int similarID)
{
    // If similarID is not already in the list of parentIDs, then add it.
    if (!isSimilar(similarID))
        similarIDs.push_back(similarID);
}

int cddb::Genre::indexOfParentID(int parentID)
{
    for (int i = 0; i < parentIDs.size(); i++) // Could cause an issue if there are more than 2^31 items in this vector?
        if (parentIDs[i] == parentID)
            return i;
    return -1;
}

int cddb::Genre::indexOfSimilarID(int similarID)
{
    for (int i = 0; i < similarIDs.size(); i++) // Could cause an issue if there are more than 2^31 items in this vector?
        if (similarIDs[i] == similarID)
            return i;
    return -1;
}

bool cddb::Genre::isParent(int parentID)
{
    return indexOfParentID(parentID) >= 0;
}

bool cddb::Genre::isSimilar(int similarID)
{
    return indexOfSimilarID(similarID) >= 0;
}

void cddb::Genre::removeParentID(int parentID)
{
    int i = indexOfParentID(parentID);
    if (i >= 0)
        parentIDs.erase(parentIDs.begin() + i);
}

void cddb::Genre::removeSimilarID(int similarID)
{
    int i = indexOfSimilarID(similarID);
    if (i >= 0)
        similarIDs.erase(similarIDs.begin() + i);
}

