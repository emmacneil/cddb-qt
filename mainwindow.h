#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "albumview.h"
#include "artistview.h"
#include "genreview.h"

#include <QMenu>
#include <QMenuBar>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void addAlbum();
    void addArtist();
    void addGenre();
    void editAlbum();
    void editArtist();
    void editGenre();
    void quit();

private:
    AlbumView *albumView;
    ArtistView *artistView;
    GenreView *genreView;

    QAction *aboutAct;
    QAction *addAlbumAct;
    QAction *addArtistAct;
    QAction *addGenreAct;
    QAction *editAlbumAct;
    QAction *editArtistAct;
    QAction *editGenreAct;
    QAction *quitAct;
    QMenu *fileMenu;
    QMenu *addMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QTabWidget *tabWidget;
    void createActions();
    void createMenus();
};

#endif // MAINWINDOW_H
