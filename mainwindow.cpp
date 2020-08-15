#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addgenredialog.h"

#include <QtSql/QtSql>
#include <QSplitter>
#include <QGroupBox>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenus();

    // Open connection to database
    addSqlConnection();
    createDatabase();

    tabWidget = new QTabWidget();
    setCentralWidget(tabWidget);
    //createTable();
    createAlbumTab();
    createArtistTab();
    createGenreTab();

    showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
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
    // Open a dialog box and allow user to enter information about the genre
    // Genre data
    //   Genre name (required)
    //   Parent genres, if all songs under this genre would also be considered of those.
    //   Other related genres
    //     These two should allow user to select from existing genres / type in genre and have it autocomplete from options.
    //     Fillable drop-down box?
    //   Notes
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

void MainWindow::createAlbumTab()
{
    // Album tab is a QSplitter divided into three sections
    // Left-most section has a number of editable fields for search queries
    // Middle section is a table displaying a list of search results
    // Right-most section displays more details about an item selected from the middle table.
    QSplitter *splitter = new QSplitter;
    QGroupBox *left = new QGroupBox(tr("Search"));
    QGroupBox *tableBox = new QGroupBox(tr("Results"));
    QGroupBox *right = new QGroupBox(tr("Details"));
    splitter->addWidget(left);
    splitter->addWidget(tableBox);
    splitter->addWidget(right);
    tabWidget->addTab(splitter, tr("&1: Albums"));
    int w = splitter->width()/3;
    QList<int> sizes = {w, w, w};
    splitter->setSizes(sizes);

    // Set up the search box
    
    // Set up the table view
    // Choose a layout for the interior of the GroupBox
    // It doesn't matter what layout we choose since we're only adding one widget
    QHBoxLayout *tableLayout = new QHBoxLayout;

    // Create the table and add it to the layout
    // By default, we will show a list of all artists
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT title, release_year FROM album");
    model->setHeaderData(0, Qt::Horizontal, tr("Title"));
    model->setHeaderData(1, Qt::Horizontal, tr("Year"));
    tableView = new QTableView;
    tableView->setModel(model);
    tableView->resizeColumnsToContents();
    tableView->show();

    tableBox->setLayout(tableLayout);
    tableLayout->addWidget(tableView);
}

void MainWindow::createArtistTab()
{
    // Artist tab is a QSplitter divided into three sections
    // Left-most section has a number of editable fields for search queries
    // Middle section is a table displaying a list of search results
    // Right-most section displays more details about an item selected from the middle table.
    QSplitter *splitter = new QSplitter;
    QGroupBox *left = new QGroupBox(tr("Search"));
    QGroupBox *tableBox = new QGroupBox(tr("Results"));
    QGroupBox *right = new QGroupBox(tr("Details"));
    splitter->addWidget(left);
    splitter->addWidget(tableBox);
    splitter->addWidget(right);
    tabWidget->addTab(splitter, tr("&2: Artists"));
    int w = splitter->width()/3;
    QList<int> sizes = {w, w, w};
    splitter->setSizes(sizes);

    // Set up the search box

    // Set up the table view
    // Choose a layout for the interior of the GroupBox
    // It doesn't matter what layout we choose since we're only adding one widget
    QHBoxLayout *tableLayout = new QHBoxLayout;

    // Create the table and add it to the layout
    // By default, we will show a list of all artists
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT name, country FROM artist");
    model->setHeaderData(0, Qt::Horizontal, tr("Artist"));
    model->setHeaderData(1, Qt::Horizontal, tr("Country"));
    tableView = new QTableView;
    tableView->setModel(model);
    tableView->resizeColumnsToContents();
    tableView->show();

    tableBox->setLayout(tableLayout);
    tableLayout->addWidget(tableView);
}

void MainWindow::createGenreTab()
{
    // Genre tab is a QSplitter divided into two sections
    // Left-most section is a table displaying a list of genres
    // Right-most section displays more details about an genre selected from the left.
    QSplitter *splitter = new QSplitter;
    QGroupBox *tableBox = new QGroupBox(tr("List"));
    QGroupBox *detailBox = new QGroupBox(tr("Details"));
    splitter->addWidget(tableBox);
    splitter->addWidget(detailBox);
    tabWidget->addTab(splitter, tr("&3: Genres"));
    int w = splitter->width()/2;
    QList<int> sizes = {w, w};
    splitter->setSizes(sizes);

    // Set up the table view
    // Choose a layout for the interior of the GroupBox
    // It doesn't matter what layout we choose since we're only adding one widget
    QHBoxLayout *tableLayout = new QHBoxLayout;

    // Create the table and add it to the layout
    // By default, we will show a list of all artists
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT name FROM genre");
    model->setHeaderData(0, Qt::Horizontal, tr("Genre"));
    tableView = new QTableView;
    tableView->setModel(model);
    tableView->resizeColumnsToContents();
    tableView->show();

    tableBox->setLayout(tableLayout);
    tableLayout->addWidget(tableView);
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
