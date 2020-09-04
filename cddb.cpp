#include "cddb.h"
#include "partialdate.h"

#include <QDebug>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

void cddb::addAlbum(cddb::Album &album)
{
    QSqlQuery query;

    // Make sure album ID is zero.
    // A non-zero ID may be an attempt to re-add an existing album to the database.
    if (album.getId() != 0)
        throw std::invalid_argument("Album must have ID = 0 to add to database");

    // Insert album into database
    query.prepare("INSERT INTO album (title, sort_title, localized_title, release_year, "
                  "release_month, release_day, release_type, rating, backlogged, owned, seeking, wishlisted, notes) VALUES "
                  "(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.bindValue(0, album.getTitle());
    query.bindValue(1, album.getSortTitle());
    query.bindValue(2, album.getLocalizedTitle());
    query.bindValue(3, album.getReleaseDate().getYear());
    query.bindValue(4, album.getReleaseDate().getMonth());
    query.bindValue(5, album.getReleaseDate().getDay());
    query.bindValue(6, album.getReleaseType());
    query.bindValue(7, album.getRating());
    query.bindValue(8, album.isBacklogged());
    query.bindValue(9, album.isOwned());
    query.bindValue(10, album.isSeeking());
    query.bindValue(11, album.isWishlisted());
    query.bindValue(12, album.getNotes());
    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());

    query.exec("SELECT last_insert_rowid();");
    query.next();
    int albumID = query.value(0).toInt();

    // Insert album rating into database
    if (album.getRating() != 0)
    {
        query.prepare("INSERT INTO album_rating_relation (album_id, rating_id) VALUES (?, ?)");
        query.bindValue(0, albumID);
        query.bindValue(1, album.getRating());
        if (!query.exec())
            throw std::runtime_error(query.lastError().text().toStdString());
    }

    // Insert album artists into database
    for (int artistID : album.getArtists())
    {
        query.prepare("INSERT INTO album_artist_relation(album_id, artist_id) VALUES (?, ?)");
        query.bindValue(0, albumID);
        query.bindValue(1, artistID);
        if (!query.exec())
            throw std::runtime_error(query.lastError().text().toStdString());
    }

    // Insert album featured artists into database
    for (int artistID : album.getFeaturedArtists())
    {
        query.prepare("INSERT INTO album_featured_artist_relation(album_id, artist_id) VALUES (?, ?)");
        query.bindValue(0, albumID);
        query.bindValue(1, artistID);
        if (!query.exec())
            throw std::runtime_error(query.lastError().text().toStdString());
    }

    // Insert album genres into database
    for (int genreID : album.getGenres())
    {
        query.prepare("INSERT INTO album_genre_relation(album_id, genre_id) VALUES (?, ?)");
        query.bindValue(0, albumID);
        query.bindValue(1, genreID);
        if (!query.exec())
            throw std::runtime_error(query.lastError().text().toStdString());
    }
}

void cddb::createTables()
{
    QSqlQuery q;
    q.exec("CREATE TABLE IF NOT EXISTS release_type ("
           "id   INTEGER PRIMARY KEY,"
           "type VARCHAR UNIQUE,"
           "multiplier INTEGER"
           ")");
    q.exec("CREATE TABLE IF NOT EXISTS rating ("
           "id     INTEGER PRIMARY KEY,"
           "letter VARCHAR NOT NULL UNIQUE,"
           "grade  REAL    NOT NULL"
           ")");

    q.exec("CREATE TABLE IF NOT EXISTS artist ("
           "id             INTEGER PRIMARY KEY,"
           "name           VARCHAR NOT NULL,"
           "sort_name      VARCHAR NOT NULL,"
           "localized_name VARCHAR,"
           "country        VARCHAR,"
           "notes          VARCHAR,"
           "score          INTEGER"
           ")");
    q.exec("CREATE TABLE IF NOT EXISTS album ("
           "id              INTEGER PRIMARY KEY,"
           "title           VARCHAR NOT NULL,"
           "sort_title      VARCHAR NOT NULL,"
           "localized_title VARCHAR,"
           "release_year    INTEGER,"
           "release_month   INTEGER,"
           "release_day     INTEGER,"
           "release_type    INTEGER NOT NULL,"
           "rating          INTEGER,"
           "backlogged      BOOLEAN DEFAULT 0,"
           "owned           BOOLEAN DEFAULT 0,"
           "seeking         BOOLEAN DEFAULT 0,"
           "wishlisted      BOOLEAN DEFAULT 0,"
           "notes           VARCHAR,"
           "FOREIGN KEY(release_type) REFERENCES release_type(id),"
           "FOREIGN KEY(rating)       REFERENCES rating(id)"
           ")");
    q.exec("CREATE TABLE IF NOT EXISTS genre ("
           "id    INTEGER PRIMARY KEY,"
           "name  VARCHAR NOT NULL UNIQUE,"
           "notes VARCHAR"
           ")");

    q.exec("CREATE TABLE IF NOT EXISTS album_artist_relation ("
           "album_id  INTEGER NOT NULL,"
           "artist_id INTEGER NOT NULL,"
           "FOREIGN KEY(album_id)  REFERENCES album(id),"
           "FOREIGN KEY(artist_id) REFERENCES artist(id)"
           ")");
    q.exec("CREATE TABLE IF NOT EXISTS album_featured_artist_relation ("
           "album_id  INTEGER NOT NULL,"
           "artist_id INTEGER NOT NULL,"
           "FOREIGN KEY(album_id)  REFERENCES album(id),"
           "FOREIGN KEY(artist_id) REFERENCES artist(id)"
           ")");
    q.exec("CREATE TABLE IF NOT EXISTS album_genre_relation ("
           "album_id  INTEGER NOT NULL,"
           "genre_id  INTEGER NOT NULL,"
           "FOREIGN KEY(album_id) REFERENCES album(id),"
           "FOREIGN KEY(genre_id) REFERENCES genre(id)"
           ")");
    q.exec("CREATE TABLE IF NOT EXISTS album_rating_relation ("
           "album_id  INTEGER NOT NULL UNIQUE,"
           "rating_id INTEGER NOT NULL,"
           "FOREIGN KEY(album_id)  REFERENCES album(id),"
           "FOREIGN KEY(rating_id) REFERENCES rating(id)"
           ")");
    q.exec("CREATE TABLE IF NOT EXISTS parent_genre_relation ("
           "parent INTEGER NOT NULL,"
           "child  INTEGER NOT NULL,"
           "FOREIGN KEY(parent) REFERENCES genre(id),"
           "FOREIGN KEY(child)  REFERENCES genre(id)"
           ")");
    q.exec("CREATE TABLE IF NOT EXISTS similar_genre_relation ("
           "genre1 INTEGER NOT NULL,"
           "genre2 INTEGER NOT NULL,"
           "FOREIGN KEY(genre1) REFERENCES genre(id),"
           "FOREIGN KEY(genre2) REFERENCES genre(id)"
           ")");
}

void cddb::dropTables()
{
    QSqlQuery q;
    q.exec("DROP TABLE IF EXISTS release_type");
    q.exec("DROP TABLE IF EXISTS rating");
    q.exec("DROP TABLE IF EXISTS artist");
    q.exec("DROP TABLE IF EXISTS album");
    q.exec("DROP TABLE IF EXISTS genre");
    q.exec("DROP TABLE IF EXISTS album_artist_relation");
    q.exec("DROP TABLE IF EXISTS album_featured_artist_relation");
    q.exec("DROP TABLE IF EXISTS album_genre_relation");
    q.exec("DROP TABLE IF EXISTS album_rating_relation");
    q.exec("DROP TABLE IF EXISTS parent_genre_relation");
    q.exec("DROP TABLE IF EXISTS similar_genre_relation");
}

std::optional<cddb::Album> cddb::getAlbum(int albumID)
{
    QSqlQuery query, innerQuery;
    query.prepare("SELECT * FROM album WHERE id = ?");
    query.bindValue(0, albumID);
    query.exec();
    if (query.next())
    {
        cddb::Album album(query.value("id").toInt());
        album.setTitle(query.value("title").toString());
        album.setSortTitle(query.value("sort_title").toString());
        if (!query.value("localized_title").toString().isEmpty())
            album.setLocalizedTitle(query.value("localized_title").toString());

        album.setReleaseDate(PartialDate(
                                 query.value("release_year").toInt(),
                                 query.value("release_month").toInt(),
                                 query.value("release_day").toInt()));

        std::optional<int> opt = getAlbumRatingID(albumID);
        album.setRating(opt.has_value() ? opt.value() : 0);
        album.setReleaseType(query.value("release_type").toInt());
        album.setRating(query.value("rating").toInt());

        std::vector<int> vec;
        vec = cddb::getAlbumArtistIDs(albumID);
        album.setArtistIDs(vec);
        vec = cddb::getAlbumFeaturedArtistIDs(albumID);
        album.setFeaturedArtistIDs(vec);
        vec = cddb::getAlbumGenreIDs(albumID);
        album.setGenreIDs(vec);

        album.setBacklogged(query.value("backlogged").toBool());
        album.setOwned(query.value("owned").toBool());
        album.setSeeking(query.value("seeking").toBool());
        album.setWishlisted(query.value("wishlisted").toBool());
        album.setNotes(query.value("notes").toString());
        return album;
    }

    return {};
}

std::vector<int> cddb::getAlbumArtistIDs(int albumID)
{
    std::vector<int> ret;
    QSqlQuery q;
    q.prepare("SELECT artist_id FROM album_artist_relation WHERE album_id = ?");
    q.bindValue(0, albumID);
    q.exec();
    while (q.next())
        ret.push_back(q.value("artist_id").toInt());
    return ret;
}

std::vector<int> cddb::getAlbumFeaturedArtistIDs(int albumID)
{
    std::vector<int> ret;
    QSqlQuery q;
    q.prepare("SELECT artist_id FROM album_featured_artist_relation WHERE album_id = ?");
    q.bindValue(0, albumID);
    q.exec();
    while (q.next())
        ret.push_back(q.value("artist_id").toInt());
    return ret;
}

std::vector<int> cddb::getAlbumGenreIDs(int albumID)
{
    std::vector<int> ret;
    QSqlQuery q;
    q.prepare("SELECT genre_id FROM album_genre_relation WHERE album_id = ?");
    q.bindValue(0, albumID);
    q.exec();
    while (q.next())
        ret.push_back(q.value("genre_id").toInt());
    return ret;
}

std::optional<int> cddb::getAlbumRatingID(int albumID)
{
    QSqlQuery q;
    q.prepare("SELECT rating_id FROM album_rating_relation WHERE album_id = ?");
    q.bindValue(0, albumID);
    q.exec();
    if (q.next())
        return q.value("rating_id").toInt();
    return {};
}

std::optional<cddb::Artist> cddb::getArtist(int artistID)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM artist WHERE id = ?");
    query.bindValue(0, artistID);
    query.exec();
    if (query.next())
    {
        cddb::Artist artist;
        artist.setID(query.value("id").toInt());
        artist.setName(query.value("name").toString());
        artist.setSortName(query.value("sort_name").toString());
        artist.setLocalizedName(query.value("localized_name").toString());
        artist.setCountry(query.value("country").toString());
        artist.setNotes(query.value("notes").toString());
        return artist;
    }

    return {};
}

std::vector<int> cddb::getArtistIDs(QString artistName)
{
    std::vector<int> ret;
    QSqlQuery q;
    q.prepare("SELECT id FROM artist WHERE name = ?");
    q.bindValue(0, artistName);
    q.exec();
    while (q.next())
        ret.push_back(q.value("id").toInt());
    return ret;
}

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
        return genre;
    }

    return {};
}

std::optional<int> cddb::getGenreID(QString genreName)
{
    QSqlQuery q;
    q.prepare("SELECT id FROM genre WHERE name = ?");
    q.bindValue(0, genreName);
    if (!q.exec())
        throw std::runtime_error(q.lastError().text().toStdString());
    if (q.next())
        return q.value("id").toInt();
    return {};
}

std::optional<QString> cddb::getRating(int id)
{
    QSqlQuery q;
    q.prepare("SELECT letter FROM rating WHERE id = ?");
    q.bindValue(0, id);
    if (!q.exec())
        throw std::runtime_error(q.lastError().text().toStdString());
    if (q.next())
        return q.value("letter").toString();
    return {};
}

std::optional<int> cddb::getRatingID(QString letter)
{
    QSqlQuery q;
    q.prepare("SELECT id FROM rating WHERE letter = ?");
    q.bindValue(0, letter);
    if (!q.exec())
        throw std::runtime_error(q.lastError().text().toStdString());
    if (q.next())
        return q.value("id").toInt();
    return {};
}

std::optional<QString> cddb::getReleaseType(int id)
{
    QSqlQuery q;
    q.prepare("SELECT type FROM release_type WHERE id = ?");
    q.bindValue(0, id);
    if (!q.exec())
        throw std::runtime_error(q.lastError().text().toStdString());
    if (q.next())
        return q.value("type").toString();
    return {};
}

std::optional<int> cddb::getReleaseTypeID(QString type)
{
    QSqlQuery q;
    q.prepare("SELECT id FROM release_type WHERE type = ?");
    q.bindValue(0, type);
    if (!q.exec())
        throw std::runtime_error(q.lastError().text().toStdString());
    if (q.next())
        return q.value("id").toInt();
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
    q.exec("INSERT INTO release_type (type, multiplier) VALUES"
           "('Album', 6),"
           "('Mini-album', 3),"
           "('EP', 3),"
           "('Single', 1),"
           "('Live Album', 3),"
           "('Compilation', 3),"
           "('V/A Compilation', 0),"
           "('Soundtrack', 6)");

    q.exec("INSERT INTO rating (letter, grade) VALUES"
           "('S+', 5.3),"
           "('S',  5.0),"
           "('S-', 4.7),"
           "('A+', 4.3),"
           "('A',  4.0),"
           "('A-', 3.7),"
           "('B+', 3.3),"
           "('B',  3.0),"
           "('B-', 2.7),"
           "('C+', 2.3),"
           "('C',  2.0),"
           "('C-', 1.7),"
           "('D+', 1.3),"
           "('D',  1.0),"
           "('D-', 0.7),"
           "('F',  0.0)");
    qDebug() << q.lastError();

    q.exec("INSERT INTO artist (name, sort_name, country) VALUES"
           "('Primal Scream', 'Primal Scream', 'United Kingdom'),"
           "('Hooverphonic', 'Hooverphonic', 'Belgium'),"
           "('sugar plant', 'sugar plant', 'Japan'),"
           "('Supercar', 'Supercar', 'Japan')");

    q.exec("INSERT INTO album (title, sort_title, release_year, release_month, release_day, release_type) VALUES"
           "('More Light', 'More Light', 2013, 5, 13, 1),"
           "('A New Stereophonic Sound Spectacular', 'A New Stereophonic Sound Spectacular', 1996, 7, 29, 1)");

    q.exec("INSERT INTO genre (name) VALUES"
           "('Dream Pop & Shoegaze'),"
           "('New Wave'),"
           "('Post-punk'),"
           "('Psychedelia')");

    q.exec("INSERT INTO album_artist_relation (album_id, artist_id) VALUES"
           "(1, 1),"
           "(2, 2)");
    q.exec("INSERT INTO parent_genre_relation (parent, child) VALUES"
           "(4, 1)");

    q.exec("INSERT INTO similar_genre_relation (genre1, genre2) VALUES"
           "(2, 3)");
}

void cddb::updateAlbum(cddb::Album &album)
{
    QSqlQuery query;

    // Make sure album ID is non-zero.
    // A non-zero ID may be an attempt to re-add an existing album to the database.
    if (album.getId() == 0)
        throw std::invalid_argument("Album must have non-zero ID to update database");

    // Insert album into database
    query.prepare("UPDATE album SET "
                  "title = ?, sort_title = ?, localized_title = ?, "
                  "release_year = ?, release_month = ?, release_day = ?, "
                  "backlogged = ?, owned = ?, seeking = ?, wishlisted = ?, "
                  "notes = ? WHERE id = ?");
    query.bindValue(0, album.getTitle());
    query.bindValue(1, album.getSortTitle());
    query.bindValue(2, album.getLocalizedTitle());
    query.bindValue(3, album.getReleaseDate().getYear());
    query.bindValue(4, album.getReleaseDate().getMonth());
    query.bindValue(5, album.getReleaseDate().getDay());
    query.bindValue(6, album.isBacklogged());
    query.bindValue(7, album.isOwned());
    query.bindValue(8, album.isSeeking());
    query.bindValue(9, album.isWishlisted());
    query.bindValue(10, album.getNotes());
    query.bindValue(11, album.getId());
    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());

    // Insert album rating into database
    query.prepare("DELETE FROM album_rating_relation WHERE album_id = ?");
    query.bindValue(0, album.getId());
    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());
    if (album.getRating() != 0)
    {
        query.prepare("INSERT INTO album_rating_relation (album_id, rating_id) VALUES (?, ?)");
        query.bindValue(0, album.getId());
        query.bindValue(1, album.getRating());
        if (!query.exec())
            throw std::runtime_error(query.lastError().text().toStdString());
    }

    // Insert album artists into database
    query.prepare("DELETE FROM album_artist_relation WHERE album_id = ?");
    query.bindValue(0, album.getId());
    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());
    for (int artistID : album.getArtists())
    {
        query.prepare("INSERT INTO album_artist_relation (album_id, artist_id) VALUES (?, ?)");
        query.bindValue(0, album.getId());
        query.bindValue(1, artistID);
        if (!query.exec())
            throw std::runtime_error(query.lastError().text().toStdString());
    }

    // Insert album featured artists into database
    query.prepare("DELETE FROM album_featured_artist_relation WHERE album_id = ?");
    query.bindValue(0, album.getId());
    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());
    for (int artistID : album.getFeaturedArtists())
    {
        query.prepare("INSERT INTO album_featured_artist_relation (album_id, artist_id) VALUES (?, ?)");
        query.bindValue(0, album.getId());
        query.bindValue(1, artistID);
        if (!query.exec())
            throw std::runtime_error(query.lastError().text().toStdString());
    }

    // Insert album genres into database
    query.prepare("DELETE FROM album_genre_relation WHERE album_id = ?");
    query.bindValue(0, album.getId());
    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());
    for (int genreID : album.getGenres())
    {
        query.prepare("INSERT INTO album_genre_relation (album_id, genre_id) VALUES (?, ?)");
        query.bindValue(0, album.getId());
        query.bindValue(1, genreID);
        if (!query.exec())
            throw std::runtime_error(query.lastError().text().toStdString());
    }
}
