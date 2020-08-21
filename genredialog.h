#ifndef GENREDIALOG_H
#define GENREDIALOG_H

#include <QDialog>

#include <QComboBox>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>

class GenreDialog : public QDialog
{
    Q_OBJECT
public:
    GenreDialog(QWidget *parent = 0);

protected:
    QStringList genreList;
    QComboBox *parentComboBox;
    QComboBox *similarComboBox;
    QDialogButtonBox *buttonBox;
    QLineEdit *nameLineEdit;
    QListWidget *parentListWidget;
    QListWidget *similarListWidget;
    QPushButton *parentAddButton;
    QPushButton *parentRemoveButton;
    QPushButton *similarAddButton;
    QPushButton *similarRemoveButton;
    QTextEdit *notesTextEdit;

    void addGenre(QListWidget *listWidget, QComboBox *comboBox);
    void addParentGenre();
    void addSimilarGenre();
    void populateGenreList();
    void removeGenre(QListWidget *listWidget);
    void removeParentGenre();
    void removeSimilarGenre();
};

#endif // GENREDIALOG_H
