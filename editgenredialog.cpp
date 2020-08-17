#include "editgenredialog.h"

EditGenreDialog::EditGenreDialog(QWidget *parent) : GenreDialog(parent)
{
    setWindowTitle(tr("Edit Genre in Database"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &EditGenreDialog::editGenreInDatabase);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &EditGenreDialog::reject);
}

void EditGenreDialog::editGenreInDatabase()
{
    accept();
}
