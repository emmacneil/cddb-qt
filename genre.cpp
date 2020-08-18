#include "genre.h"

void cddb::Genre::addParentID(int parentID)
{
    // If parentID is not already in the list of parentIDs, then add it.
    if (!isParent(parentID))
        parentIDs.push_back(parentID);
}

int cddb::Genre::indexOfParentID(int parentID)
{
    for (int i = 0; i < parentIDs.size(); i++) // Could cause an issue if there are more than 2^31 items in this vector?
        if (parentIDs[i] == parentID)
            return i;
    return -1;
}

bool cddb::Genre::isParent(int parentID)
{
    return indexOfParentID(parentID) >= 0;
}

void cddb::Genre::removeParentID(int parentID)
{
    int i = indexOfParentID(parentID);
    if (i >= 0)
        parentIDs.erase(parentIDs.begin() + i);
}

