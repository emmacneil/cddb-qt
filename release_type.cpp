#include "release_type.h"

namespace cddb
{
ReleaseType::ReleaseType(int id)
    : id(id), multiplier(0.0f), name("")
{
}

ReleaseType::ReleaseType(const ReleaseType &other)
    : id(other.id), multiplier(other.multiplier), name(other.name)
{
}

int ReleaseType::getID() const
{
    return id;
}

float ReleaseType::getMultiplier() const
{
    return multiplier;
}

QString ReleaseType::getName() const
{
    return name;
}

void ReleaseType::setMultiplier(float val)
{
    multiplier = val;
}

void ReleaseType::setName(QString str)
{
    name = str;
}
} // namespace cddb
