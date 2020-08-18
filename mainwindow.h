#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void addGenre();
    void editGenre();
    void quit();

private:
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
