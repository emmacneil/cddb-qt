#include "cddb.h"

#include <QDebug>

#include <QSqlDatabase>
#include <QSqlQuery>

std::optional<cddb::Genre> cddb::getGenre(int genreID)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM genre WHERE id = ?");
    query.bindValue(0, genreID);
    query.exec();
    if (query.next())
    {
        cddb::Genre genre(genreID, query.value("name").toString());
        genre.setNotes(query.value("notes").toString());

        // Find parent genre IDs
        query.prepare("SELECT parent FROM parent_genre_relation WHERE child = ?");
        query.bindValue(0, genreID);
        query.exec();
        while (query.next())
            genre.addParentID(query.value("parent").toInt());

        /*
        // Find similar genre IDs
        query.prepare("SELECT genre2 FROM similar_genre_relation WHERE genre1 = ?");
        query.bindValue(0, genreID);
        query.exec();
        while (query.next())
            genre.addSimilarID(query.value("genre2").toInt());
        query.prepare("SELECT genre1 FROM similar_genre_relation WHERE genre2 = ?");
        query.bindValue(0, genreID);
        query.exec();
        while (query.next())
            genre.addSimilarID(query.value("genre1").toInt());
        */
        return genre;
    }

    return {};
}

void cddb::init(QString filename)
{
    // Check if a database is already open
    QStringList connectionList = QSqlDatabase::connectionNames();
    if (!connectionList.isEmpty())
        throw std::runtime_error("A database connection is already open.");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    // At this point, we can do other initializations, if necessary, such as
    // setUserName(), setPassword(), setHostName(), setPort(), setConnectOptions()
    if (!db.open())
        throw std::runtime_error("Could not open SQLite database.");
}

void cddb::seedDatabase()
{
    QSqlQuery q("");
    q.exec("drop table if exists artist");
    q.exec("create table if not exists artist ("
           "id integer primary key,"
           "name varchar,"
           "country varchar,"
           "notes varchar"
           ")");
    q.exec("insert into artist (name, country) values"
           "('Primal Scream', 'United Kingdom'),"
           "('Hooverphonic', 'Belgium'),"
           "('sugar plant', 'Japan'),"
           "('Supercar', 'Japan')");

    q.exec("drop table if exists album");
    q.exec("create table if not exists album ("
           "id integer primary key,"
           "title varchar not null,"
           "release_year integer,"
           "release_month integer,"
           "release_day integer"
           ")");
    q.exec("insert into album (title, release_year) values"
           "('More Light', 2013),"
           "('A New Stereophonic Sound Spectacular', 1996)");

    q.exec("drop table if exists genre");
    q.exec("create table if not exists genre ("
           "id integer primary key,"
           "name varchar not null,"
           "notes varchar"
           ")");
    q.exec("insert into genre (name) values"
           "('Dream Pop & Shoegaze'),"
           "('New Wave'),"
           "('Post-punk'),"
           "('Psychedelia')");

    q.exec("drop table if exists parent_genre_relation");
    q.exec("create table if not exists parent_genre_relation ("
           "parent integer,"
           "child integer,"
           "foreign key(parent) references genre(id),"
           "foreign key(child) references genre(id)"
           ")");
    q.exec("insert into parent_genre_relation (parent, child) values"
           "(4, 1)");

    q.exec("drop table if exists similar_genre_relation");
    q.exec("create table if not exists similar_genre_relation ("
           "genre1 integer,"
           "genre2 integer,"
           "foreign key(genre1) references genre(id),"
           "foreign key(genre2) references genre(id)"
           ")");
    q.exec("insert into similar_genre_relation (genre1, genre2) values"
           "(2, 3)");}
