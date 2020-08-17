#ifndef EDITGENREDIALOG_H
#define EDITGENREDIALOG_H

#include "genredialog.h"

class EditGenreDialog : public GenreDialog
{
public:
    EditGenreDialog(QWidget *parent = 0);

private slots:
    void editGenreInDatabase();
};

#endif // EDITGENREDIALOG_H
