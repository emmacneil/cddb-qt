#include "cddb.h"
#include "editgenredialog.h"

#include <QSqlQuery>

EditGenreDialog::EditGenreDialog(int genreID, QWidget *parent) : GenreDialog(parent), genreID(genreID)
{
    setWindowTitle(tr("Edit Genre in Database"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &EditGenreDialog::editGenreInDatabase);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &EditGenreDialog::reject);

    std::optional<cddb::Genre> genre = cddb::getGenre(genreID);
    if (genre.has_value())
    {
        nameLineEdit->setText(genre.value().getName());
        notesTextEdit->setText(genre.value().getNotes());
    }
    // We are editing a genre, so we should populate the dialog box with the already-existing data on the genre.
    /*
    QString genreName;
    QString genreNotes;
    QList<QString> parentGenres;
    QList<QString> similarGenres;


    QSqlQuery query;
    query.prepare("SELECT * FROM genre WHERE id = ?");
    query.bindValue(0, genreID);
    query.exec();
    query.next();
    genreName = query.value("name").toString();
    genreNotes = query.value("notes").toString();

    nameLineEdit->setText(genreName);
    notesTextEdit->setText(genreNotes);

    query.prepare("SELECT * FROM similar_genre_relation WHERE genre1 = ? OR genre2 = ?");
    query.bindValue(0, genreID);
    query.bindValue(1, genreID);
    query.exec();
    */
}

void EditGenreDialog::editGenreInDatabase()
{
    accept();
}
