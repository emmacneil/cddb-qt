#include "cddb.h"
#include "editgenredialog.h"

#include <QDebug>
#include <QPushButton>

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

        for (int id : genre.value().getParentIDs())
        {
            std::optional<cddb::Genre> parentGenre = cddb::getGenre(id);
            if (parentGenre.has_value())
                parentListWidget->addItem(parentGenre.value().getName());
        }

        for (int id : genre.value().getSimilarIDs())
        {
            std::optional<cddb::Genre> similarGenre = cddb::getGenre(id);
            if (similarGenre.has_value())
                similarListWidget->addItem(similarGenre.value().getName());
        }
    }
    else
    {
        // Something has gone wrong and we don't have a genre to edit.
        // Seems we can't close the dialog from within the constructor (?)
        // For now, just make fields uneditable and disable OK button.
        qWarning() << "EditGenreDialog opened with invalid genreID.";
        nameLineEdit->setEnabled(false);
        parentListWidget->setEnabled(false);
        parentAddButton->setEnabled(false);
        parentRemoveButton->setEnabled(false);
        similarListWidget->setEnabled(false);
        similarAddButton->setEnabled(false);
        similarRemoveButton->setEnabled(false);
        notesTextEdit->setEnabled(false);
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

void EditGenreDialog::editGenreInDatabase()
{
    // Get new data from dialog box's widgets
    QString genreName = nameLineEdit->text();
    QStringList parentGenres;
    QStringList similarGenres;
    QString notes = notesTextEdit->toPlainText();
    QListWidgetItem *result = nullptr;

    while (result = parentListWidget->takeItem(0))
        parentGenres.append(result->text());
    while (result = similarListWidget->takeItem(0))
        similarGenres.append(result->text());

    // Edit genre in database
    QSqlQuery query;
    query.prepare("UPDATE genre SET name = ?, notes = ? WHERE id = ?");
    query.bindValue(0, genreName);
    query.bindValue(1, notes);
    query.bindValue(2, genreID);
    query.exec();

    // If there was a parent-child genre relationship in the database before, remove it
    query.prepare("DELETE FROM parent_genre_relation WHERE child = ?");
    query.bindValue(0, genreID);
    query.exec();
    // For each parent genre, create a relation in the database
    for (QString s : parentGenres)
    {
        query.prepare("SELECT id FROM genre WHERE name = ?");
        query.bindValue(0, s);
        query.exec();
        query.next();
        int parentID = query.value(0).toInt();

        query.prepare("INSERT INTO parent_genre_relation (parent, child) VALUES (?, ?)");
        query.bindValue(0, parentID);
        query.bindValue(1, genreID);
        query.exec();
    }

    // If there were genres similar to this, delete those relations fom the database.
    query.prepare("DELETE FROM similar_genre_relation WHERE genre1 = ? OR genre2 = ?");
    query.bindValue(0, genreID);
    query.bindValue(1, genreID);
    query.exec();
    // For each similar genre, create a relation in the database
    for (QString s : similarGenres)
    {
        query.prepare("SELECT id FROM genre WHERE name = ?");
        query.bindValue(0, s);
        query.exec();
        query.next();
        int similarID = query.value(0).toInt();

        query.prepare("INSERT INTO similar_genre_relation (genre1, genre2) VALUES (?, ?)");
        query.bindValue(0, genreID);
        query.bindValue(1, similarID);
        query.exec();
    }

    accept();
}
