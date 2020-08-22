#ifndef EDITALBUMDIALOG_H
#define EDITALBUMDIALOG_H

#include "albumdialog.h"

class EditAlbumDialog : public AlbumDialog
{
public:
    EditAlbumDialog(int artistID, QWidget *parent = 0);

private:
    int albumID;
};

#endif // EDITALBUMDIALOG_H
