#ifndef ADDALBUMDIALOG_H
#define ADDALBUMDIALOG_H

#include "albumdialog.h"

class AddAlbumDialog : public AlbumDialog
{
public:
    AddAlbumDialog(QWidget *parent = 0);

private:
    void addAlbumToDatabase();
};

#endif // ADDALBUMDIALOG_H
