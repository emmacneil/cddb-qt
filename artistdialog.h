#ifndef ARTISTDIALOG_H
#define ARTISTDIALOG_H

#include "cddb.h"

#include <QDialog>

#include <QDialogButtonBox>
#include <QLineEdit>
#include <QTextEdit>

class ArtistDialog : public QDialog
{
public:
    ArtistDialog(QWidget *parent = 0);

protected:
    QDialogButtonBox *buttonBox;
    QLineEdit *nameLineEdit;
    QLineEdit *sortNameLineEdit;
    QLineEdit *localizedNameLineEdit;
    QLineEdit *countryLineEdit;
    QTextEdit *notesTextEdit;
    void fillArtistDetails(cddb::Artist &artist);
};

#endif // ARTISTDIALOG_H
