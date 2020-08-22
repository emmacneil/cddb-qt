#include "albumdialog.h"

#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

AlbumDialog::AlbumDialog(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QHBoxLayout *dataLayout = new QHBoxLayout;
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    mainLayout->addLayout(dataLayout);
    mainLayout->addWidget(buttonBox);

    QGroupBox *formGroupBox = new QGroupBox(tr("Release Data"));
    QVBoxLayout *listLayout = new QVBoxLayout;
    QGroupBox *notesGroupBox = new QGroupBox(tr("Notes"));
    dataLayout->addWidget(formGroupBox);
    dataLayout->addLayout(listLayout);
    dataLayout->addWidget(notesGroupBox);

    // Set up left-most part of dialog box
    QFormLayout *formLayout = new QFormLayout;
    formGroupBox->setLayout(formLayout);

    titleLineEdit = new QLineEdit;
    sortTitleLineEdit = new QLineEdit;
    localizedTitleLineEdit = new QLineEdit;
    releaseTypeComboBox = new QComboBox;
    releaseDateComboBox = new QComboBox;
    ratingComboBox = new QComboBox;
    backlogCheckBox = new QCheckBox;
    ownedCheckBox = new QCheckBox;
    seekingCheckBox = new QCheckBox;
    wishlistCheckBox = new QCheckBox;
    formLayout->addRow(tr("Title:"), titleLineEdit);
    formLayout->addRow(tr("Sort by:"), sortTitleLineEdit);
    formLayout->addRow(tr("Localized:"), localizedTitleLineEdit);
    formLayout->addRow(tr("Release Type:"), releaseTypeComboBox);
    formLayout->addRow(tr("Release Date:"), releaseDateComboBox);
    formLayout->addRow(tr("Rating:"), ratingComboBox);
    formLayout->addRow(tr("Backlog"), backlogCheckBox);
    formLayout->addRow(tr("Owned"), ownedCheckBox);
    formLayout->addRow(tr("Seeking"), seekingCheckBox);
    formLayout->addRow(tr("Wishlist"), wishlistCheckBox);

    // Set up middle area with list widgets
    QGroupBox *artistGroupBox = new QGroupBox(tr("Artist(s)"));
    QGridLayout *artistGroupBoxLayout = new QGridLayout;
    artistComboBox = new QComboBox;
    artistListWidget = new QListWidget;
    artistAddButton = new QPushButton(tr("Add"));
    artistRemoveButton = new QPushButton(tr("Remove"));
    //artistComboBox->addItems(...);
    artistGroupBoxLayout->addWidget(artistComboBox, 0, 0);
    artistGroupBoxLayout->addWidget(artistAddButton, 0, 1);
    artistGroupBoxLayout->addWidget(artistListWidget, 1, 0);
    artistGroupBoxLayout->addWidget(artistRemoveButton, 1, 1, Qt::AlignTop);
    artistGroupBox->setLayout(artistGroupBoxLayout);
    //connect(artistAddButton, &QPushButton::clicked, this, &AlbumDialog::addArtist);
    //connect(artistRemoveButton, &QPushButton::clicked, this, &AlbumDialog::removeArtist);

    QGroupBox *featuredArtistGroupBox = new QGroupBox(tr("Featured Artist(s)"));
    QGridLayout *featuredArtistGroupBoxLayout = new QGridLayout;
    featuredArtistComboBox = new QComboBox;
    featuredArtistListWidget = new QListWidget;
    featuredArtistAddButton = new QPushButton(tr("Add"));
    featuredArtistRemoveButton = new QPushButton(tr("Remove"));
    //featuredArtistComboBox->addItems(...);
    featuredArtistGroupBoxLayout->addWidget(featuredArtistComboBox, 0, 0);
    featuredArtistGroupBoxLayout->addWidget(featuredArtistAddButton, 0, 1);
    featuredArtistGroupBoxLayout->addWidget(featuredArtistListWidget, 1, 0);
    featuredArtistGroupBoxLayout->addWidget(featuredArtistRemoveButton, 1, 1, Qt::AlignTop);
    featuredArtistGroupBox->setLayout(featuredArtistGroupBoxLayout);
    //connect(featuredArtistAddButton, &QPushButton::clicked, this, &AlbumDialog::addFeaturedArtist);
    //connect(featuredArtistRemoveButton, &QPushButton::clicked, this, &AlbumDialog::removeFeaturedArtist);

    QGroupBox *genreGroupBox = new QGroupBox(tr("Genre(s)"));
    QGridLayout *genreGroupBoxLayout = new QGridLayout;
    genreComboBox = new QComboBox;
    genreListWidget = new QListWidget;
    genreAddButton = new QPushButton(tr("Add"));
    genreRemoveButton = new QPushButton(tr("Remove"));
    //genreComboBox->addItems(...);
    genreGroupBoxLayout->addWidget(genreComboBox, 0, 0);
    genreGroupBoxLayout->addWidget(genreAddButton, 0, 1);
    genreGroupBoxLayout->addWidget(genreListWidget, 1, 0);
    genreGroupBoxLayout->addWidget(genreRemoveButton, 1, 1, Qt::AlignTop);
    genreGroupBox->setLayout(genreGroupBoxLayout);
    //connect(genreAddButton, &QPushButton::clicked, this, &AlbumDialog::addGenre);
    //connect(genreRemoveButton, &QPushButton::clicked, this, &AlbumDialog::removeGenre);

    listLayout->addWidget(artistGroupBox);
    listLayout->addWidget(featuredArtistGroupBox);
    listLayout->addWidget(genreGroupBox);

    // Set up right-most area, with space to make markdown notes
    QVBoxLayout *notesLayout = new QVBoxLayout;
    notesGroupBox->setLayout(notesLayout);

    notesTextEdit = new QTextEdit;
    notesLayout->addWidget(notesTextEdit);
}
