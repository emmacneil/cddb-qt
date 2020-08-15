#ifndef ADDGENREDIALOG_H
#define ADDGENREDIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QTextEdit>

namespace Ui {
class AddGenreDialog;
}

class AddGenreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddGenreDialog(QWidget *parent = 0);
    ~AddGenreDialog();

private:
    //Ui::MainWindow *ui;
    QStringList genreList;
    QComboBox *parentComboBox;
    QComboBox *similarComboBox;
    QListWidget *parentListWidget;
    QListWidget *similarListWidget;
    QLineEdit *nameLineEdit;
    QTextEdit *notesTextEdit;

    void populateGenreList();
    void addGenre(QListWidget *listWidget, QComboBox *comboBox);
    void removeGenre(QListWidget *listWidget);

private slots:
    void addGenreToDatabase();
    void addParentGenre();
    void addSimilarGenre();
    void removeParentGenre();
    void removeSimilarGenre();
};

#endif // ADDGENREDIALOG_H
