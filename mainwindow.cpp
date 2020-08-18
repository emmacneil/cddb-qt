#include "addgenredialog.h"
#include "albumview.h"
#include "artistview.h"
#include "editgenredialog.h"
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
    qDebug() << "Qt Version" << qVersion();
    createActions();
    createMenus();

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
    editAlbumAct->setEnabled(false);

    editArtistAct = new QAction(tr("Edit A&rtist..."));
    editArtistAct->setEnabled(false);

    editGenreAct = new QAction(tr("Edit &Genre..."));
    editGenreAct->setStatusTip(tr("Edit a new genre in the database"));
    connect(editGenreAct, &QAction::triggered, this, &MainWindow::editGenre);

    addAlbumAct = new QAction(tr("Add &Album..."));
    addAlbumAct->setEnabled(false);

    addArtistAct = new QAction(tr("Add A&rtist..."));
    addArtistAct->setEnabled(false);

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

void MainWindow::editGenre()
{
    EditGenreDialog dialog(1, this);
    dialog.exec();
}


void MainWindow::quit()
{
    qApp->quit();
}
