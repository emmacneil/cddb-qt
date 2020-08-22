#include "addalbumdialog.h"
#include "addartistdialog.h"
#include "addgenredialog.h"
#include "editalbumdialog.h"
#include "editartistdialog.h"
#include "editgenredialog.h"
#include "mainwindow.h"

#include <QtSql/QtSql>
#include <QSplitter>
#include <QGroupBox>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    qDebug() << "Qt Version" << qVersion();
    createActions();
    createMenus();

    tabWidget = new QTabWidget();
    albumView = new AlbumView;
    artistView = new ArtistView;
    genreView = new GenreView;
    tabWidget->addTab(albumView, tr("&1: Albums"));
    tabWidget->addTab(artistView, tr("&2: Artists"));
    tabWidget->addTab(genreView, tr("&3: Genres"));
    setCentralWidget(tabWidget);

    showMaximized();
}

MainWindow::~MainWindow()
{
}

void MainWindow::addAlbum()
{
    AddAlbumDialog dialog(this);
    dialog.exec();
}

void MainWindow::addArtist()
{
    AddArtistDialog dialog(this);
    dialog.exec();
}

void MainWindow::addGenre()
{
    AddGenreDialog dialog(this);
    dialog.exec();
}

void MainWindow::createActions()
{
    // TODO: Do I need to delete this pointer later myself?
    quitAct = new QAction(tr("&Quit"));
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit CDDB-qt"));
    connect(quitAct, &QAction::triggered, this, &MainWindow::quit);

    editAlbumAct = new QAction(tr("Edit &Album..."));
    editAlbumAct->setStatusTip(tr("Edit an album in the database"));
    connect(editAlbumAct, &QAction::triggered, this, &MainWindow::editAlbum);

    editArtistAct = new QAction(tr("Edit A&rtist..."));
    editArtistAct->setStatusTip(tr("Edit an artist in the database"));
    connect(editArtistAct, &QAction::triggered, this, &MainWindow::editArtist);

    editGenreAct = new QAction(tr("Edit &Genre..."));
    editGenreAct->setStatusTip(tr("Edit a genre in the database"));
    connect(editGenreAct, &QAction::triggered, this, &MainWindow::editGenre);

    addAlbumAct = new QAction(tr("Add &Album..."));
    addAlbumAct->setStatusTip(tr("Add a new album to the database"));
    connect(addAlbumAct, &QAction::triggered, this, &MainWindow::addAlbum);

    addArtistAct = new QAction(tr("Add A&rtist..."));
    addArtistAct->setStatusTip(tr("Add a new artist to the database"));
    connect(addArtistAct, &QAction::triggered, this, &MainWindow::addArtist);

    addGenreAct = new QAction(tr("Add &Genre..."));
    addGenreAct->setStatusTip(tr("Add a new genre to the database"));
    connect(addGenreAct, &QAction::triggered, this, &MainWindow::addGenre);

    aboutAct = new QAction(tr("&About..."));
    aboutAct->setEnabled(false);
}

void MainWindow::createMenus()
{
    // Create the File, Edit, Help, etc. menus
    // TODO: Do I need to delete this pointer (fileMenu, editMenu, etc.) later myself?
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(quitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(editAlbumAct);
    editMenu->addAction(editArtistAct);
    editMenu->addAction(editGenreAct);

    addMenu = menuBar()->addMenu(tr("&Add"));
    addMenu->addAction(addAlbumAct);
    addMenu->addAction(addArtistAct);
    addMenu->addAction(addGenreAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

void MainWindow::editAlbum()
{
    EditAlbumDialog dialog(0, this);
    dialog.exec();
}

void MainWindow::editArtist()
{
    std::optional<int> artistID = artistView->getSelectedArtistID();
    if (artistID.has_value())
    {
        EditArtistDialog dialog(artistID.value(), this);
        dialog.exec();
    }
    else
    {
        qWarning() << "Attempted to edit artist when no artist was selected.";
    }
}

void MainWindow::editGenre()
{
    std::optional<int> genreID = genreView->getSelectedGenreID();
    if (genreID.has_value())
    {
        EditGenreDialog dialog(genreID.value(), this);
        dialog.exec();
    }
    else
    {
        qWarning() << "Attempted to edit genre when no genre was selected.";
    }
}

void MainWindow::quit()
{
    qApp->quit();
}
