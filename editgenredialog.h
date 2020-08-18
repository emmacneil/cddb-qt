#ifndef EDITGENREDIALOG_H
#define EDITGENREDIALOG_H

#include "genredialog.h"

class EditGenreDialog : public GenreDialog
{
public:
    EditGenreDialog(int genreID, QWidget *parent = 0);

private:
    int genreID;

private slots:
    void editGenreInDatabase();
};

#endif // EDITGENREDIALOG_H
