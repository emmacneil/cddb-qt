#ifndef EDITARTISTDIALOG_H
#define EDITARTISTDIALOG_H

#include "artistdialog.h"

class EditArtistDialog : public ArtistDialog
{
public:
    EditArtistDialog(int artistID, QWidget *parent);

private:
    int artistID;

private slots:
    void editArtistInDatabase();
};

#endif // EDITARTISTDIALOG_H
