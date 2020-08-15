#include "addgenredialog.h"
#include "albumview.h"
#include "artistview.h"
#include "genreview.h"
#include "mainwindow.h"
//#include "ui_mainwindow.h"


#include <QtSql/QtSql>
#include <QSplitter>
#include <QGroupBox>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    createActions();
    createMenus();

    // Open connection to database
    addSqlConnection();
    createDatabase();

    tabWidget = new QTabWidget();
    tabWidget->addTab(new AlbumView, tr("&1: Albums"));
    tabWidget->addTab(new ArtistView, tr("&2: Artists"));
    tabWidget->addTab(new GenreView, tr("&3: Genres"));
    setCentralWidget(tabWidget);

    showMaximized();
}

MainWindow::~MainWindow()
{
}

void MainWindow::addSqlConnection()
{
    // If database does not exist, create it.
    // Create connection
    QString filename = "./cddb.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    if (!db.open())
        qCritical() << "Could not open SQLite database!";
    qDebug() << "Connection name is '" << db.connectionName() << "'";
}

void MainWindow::addGenre()
{
    AddGenreDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        qDebug() << "Dialog accepted";
    }
    else
    {
        qDebug() << "Dialog rejected";
    }
}

void MainWindow::createActions()
{
    // TODO: Do I need to delete this pointer later myself?
    quitAct = new QAction(tr("&Quit"));
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit CDDB-qt"));
    connect(quitAct, &QAction::triggered, this, &MainWindow::quit);

    addAlbumAct = new QAction(tr("Add &Album..."));
    addAlbumAct->setEnabled(false);

    addArtistAct = new QAction(tr("Add A&rtist..."));
    addArtistAct->setEnabled(false);

    addGenreAct = new QAction(tr("Add &Genre..."));
    // addGenreAct->setEnabled(false);
    addGenreAct->setStatusTip(tr("Add a new genre to the database"));
    connect(addGenreAct, &QAction::triggered, this, &MainWindow::addGenre);

    aboutAct = new QAction(tr("&About..."));
    aboutAct->setEnabled(false);
}

void MainWindow::createDatabase()
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
           "(2, 3)");
}

void MainWindow::createMenus()
{
    // Create the File, Edit, Help, etc. menus
    // TODO: Do I need to delete this pointer (fileMenu, editMenu, etc.) later myself?
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(quitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(addArtistAct);
    editMenu->addAction(addAlbumAct);
    editMenu->addAction(addGenreAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

void MainWindow::quit()
{
    qApp->quit();
}
