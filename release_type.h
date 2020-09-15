#ifndef RELEASETYPE_H
#define RELEASETYPE_H

#include  <QString>

namespace cddb
{
class ReleaseType
{
public:
    ReleaseType(int id);
    ReleaseType(const ReleaseType &other);

    int getID() const;
    float getMultiplier() const;
    QString getName() const;

    void setMultiplier(float val);
    void setName(QString str);
private:
    const int id;
    float multiplier;
    QString name;
};
} // namespace cddb
#endif // RELEASETYPE_H
