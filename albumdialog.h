#ifndef ALBUMDIALOG_H
#define ALBUMDIALOG_H

/* AlbumDialog
 *
 * A dialog box containing fields for entering data related albums and other releases. This dialog
 * box has no functionality. It is subclassed by AddAlbumDialog and EditAlbumDialog, which use
 * the entered data to insert into or update the database.
 *
 * Title
 * Sort Title
 * Localized Title
 * Release Type (One of Album, EP, Single, etc.)
 * Release Date (YYYY, YYYY-MM, or YYYY-MM-DD)
 * Artists (One or more)
 * Featured Artists (Zero or more)
 * Genres (Zero or more)
 * Rating
 * Owned
 * Wishlisted
 * Backlogged
 * Looking for
 * Notes
 */

#include "partialdateedit.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>

class AlbumDialog : public QDialog
{
public:
    AlbumDialog(QWidget *parent = 0);

protected:
    QCheckBox *backlogCheckBox;
    QCheckBox *ownedCheckBox;
    QCheckBox *seekingCheckBox;
    QCheckBox *wishlistCheckBox;
    QComboBox *artistComboBox;
    QComboBox *featuredArtistComboBox;
    QComboBox *genreComboBox;
    QComboBox *ratingComboBox;
    PartialDateEdit *releaseDateComboBox; // This is temporary... we actually need three combo boxes (year, month, and date)
    QComboBox *releaseTypeComboBox;
    QDialogButtonBox *buttonBox;
    QLineEdit *localizedTitleLineEdit;
    QLineEdit *sortTitleLineEdit;
    QLineEdit *titleLineEdit;
    QListWidget *artistListWidget;
    QListWidget *featuredArtistListWidget;
    QListWidget *genreListWidget;
    QPushButton *artistAddButton;
    QPushButton *artistRemoveButton;
    QPushButton *featuredArtistAddButton;
    QPushButton *featuredArtistRemoveButton;
    QPushButton *genreAddButton;
    QPushButton *genreRemoveButton;
    QTextEdit *notesTextEdit;

protected slots:
    void addArtist();
    void addFeaturedArtist();
    void addGenre();
    void removeArtist();
    void removeFeaturedArtist();
    void removeGenre();
};

#endif // ALBUMDIALOG_H
