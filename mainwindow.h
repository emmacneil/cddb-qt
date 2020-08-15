#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenu>
#include <QMainWindow>
#include <QTableView>

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
    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QAction *quitAct;
    QAction *addAlbumAct;
    QAction *addArtistAct;
    QAction *addGenreAct;
    QAction *aboutAct;
    QTableView *tableView;
    QTabWidget *tabWidget;
    void addSqlConnection();
    void createActions();
    void createAlbumTab();
    void createArtistTab();
    void createGenreTab();
    void createDatabase();
    void createMenus();
};

#endif // MAINWINDOW_H
