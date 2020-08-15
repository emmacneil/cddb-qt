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
    void quit();

private:
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QAction *quitAct;
    QAction *addAlbumAct;
    QAction *addArtistAct;
    QAction *addGenreAct;
    QAction *aboutAct;
    QTabWidget *tabWidget;
    void addSqlConnection();
    void createActions();
    void createDatabase();
    void createMenus();
};

#endif // MAINWINDOW_H
