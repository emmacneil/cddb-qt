#ifndef ADDARTISTDIALOG_H
#define ADDARTISTDIALOG_H

#include "artistdialog.h"

class AddArtistDialog : public ArtistDialog
{
public:
    AddArtistDialog(QWidget *parent = 0);

private:
    void addArtistToDatabase();
};

#endif // ADDARTISTDIALOG_H
