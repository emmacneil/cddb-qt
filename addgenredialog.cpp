#include "addgenredialog.h"

#include <QSqlQuery>

AddGenreDialog::AddGenreDialog(QWidget *parent) : GenreDialog(parent)
{
    setWindowTitle(tr("Add Genre to Database"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AddGenreDialog::addGenreToDatabase);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AddGenreDialog::reject);
}

void AddGenreDialog::addGenreToDatabase()
{
    // Get data from dialog box's widgets
    QString genreName = nameLineEdit->text();
    QStringList parentGenres;
    QStringList similarGenres;
    QString notes = notesTextEdit->toPlainText();
    QListWidgetItem *result = nullptr;

    while (result = parentListWidget->takeItem(0))
        parentGenres.append(result->text());
    while (result = similarListWidget->takeItem(0))
        similarGenres.append(result->text());

    // Add a genre into database
    QSqlQuery query;
    query.prepare("INSERT INTO genre (name, notes) values (?, ?)");
    query.bindValue(0, genreName);
    query.bindValue(1, notes);
    query.exec();
    
    // Get ID of newly added genre
    query.prepare("SELECT id FROM genre WHERE name = ?");
    query.bindValue(0, genreName);
    query.exec();
    query.next();
    int genreID = query.value(0).toInt();

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

    // For each similargenre, create a relation in the database
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

