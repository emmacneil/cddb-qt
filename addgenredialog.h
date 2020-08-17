#ifndef ADDGENREDIALOG_H
#define ADDGENREDIALOG_H

#include "genredialog.h"

class AddGenreDialog : public GenreDialog
{
    Q_OBJECT
public:
    explicit AddGenreDialog(QWidget *parent = 0);

private slots:
    void addGenreToDatabase();
};

#endif // ADDGENREDIALOG_H
