#include "genredialog.h"

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QSqlQuery>
#include <QSqlRecord>

GenreDialog::GenreDialog(QWidget *parent) : QDialog(parent)
{
    populateGenreList();

    // mainLayout consists of an area for data-entry related widgets (dataLayout)
    // and OK/Cancel buttons at the bottom.
    // The data entry area is split into left and right.
    // The left has widgets for entering the genre name and related genres
    // The right has a widget for typing notes about the genre.
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *dataLayout = new QHBoxLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QVBoxLayout *rightLayout = new QVBoxLayout;

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    setLayout(mainLayout);
    mainLayout->addLayout(dataLayout);
    mainLayout->addWidget(buttonBox);
    dataLayout->addLayout(leftLayout);
    dataLayout->addLayout(rightLayout);

    QFormLayout *nameLayout = new QFormLayout;
    nameLineEdit = new QLineEdit;
    nameLayout->addRow(tr("Genre Name"), nameLineEdit);
    leftLayout->addLayout(nameLayout);

    QGroupBox *parentGroupBox = new QGroupBox(tr("Parent Genres"));
    QGridLayout *parentGroupBoxLayout = new QGridLayout;
    parentComboBox = new QComboBox;
    parentListWidget = new QListWidget;
    parentAddButton = new QPushButton(tr("Add"));
    parentRemoveButton = new QPushButton(tr("Remove"));
    parentComboBox->addItems(genreList);
    parentGroupBoxLayout->addWidget(parentComboBox, 0, 0);
    parentGroupBoxLayout->addWidget(parentAddButton, 0, 1);
    parentGroupBoxLayout->addWidget(parentListWidget, 1, 0);
    parentGroupBoxLayout->addWidget(parentRemoveButton, 1, 1, Qt::AlignTop);
    parentGroupBox->setLayout(parentGroupBoxLayout);
    leftLayout->addWidget(parentGroupBox);
    connect(parentAddButton, &QPushButton::clicked, this, &GenreDialog::addParentGenre);
    connect(parentRemoveButton, &QPushButton::clicked, this, &GenreDialog::removeParentGenre);

    QGroupBox *similarGroupBox = new QGroupBox(tr("Similar Genres"));
    QGridLayout *similarGroupBoxLayout = new QGridLayout;
    similarComboBox = new QComboBox;
    similarListWidget = new QListWidget;
    similarAddButton = new QPushButton(tr("Add"));
    similarRemoveButton = new QPushButton(tr("Remove"));
    similarComboBox->addItems(genreList);
    similarGroupBoxLayout->addWidget(similarComboBox, 0, 0);
    similarGroupBoxLayout->addWidget(similarAddButton, 0, 1);
    similarGroupBoxLayout->addWidget(similarListWidget, 1, 0);
    similarGroupBoxLayout->addWidget(similarRemoveButton, 1, 1, Qt::AlignTop);
    similarGroupBox->setLayout(similarGroupBoxLayout);
    leftLayout->addWidget(similarGroupBox);
    connect(similarAddButton, &QPushButton::clicked, this, &GenreDialog::addSimilarGenre);
    connect(similarRemoveButton, &QPushButton::clicked, this, &GenreDialog::removeSimilarGenre);

    QGroupBox *notesGroupBox = new QGroupBox(tr("Notes"));
    QVBoxLayout *notesGroupBoxLayout = new QVBoxLayout;
    notesTextEdit = new QTextEdit();
    notesGroupBoxLayout->addWidget(notesTextEdit);
    notesGroupBox->setLayout(notesGroupBoxLayout);
    rightLayout->addWidget(notesGroupBox);
}

void GenreDialog::addGenre(QListWidget *listWidget, QComboBox *comboBox)
{
    // Get the genre currently showing in the QComboBox
    QString genreName = comboBox->currentText();

    // Check if the genre is already in the QListWidget. If not, add it.
    QList<QListWidgetItem*> results = listWidget->findItems(genreName, Qt::MatchExactly);
    if (results.isEmpty())
        listWidget->addItem(genreName);
}

void GenreDialog::addParentGenre()
{
    addGenre(parentListWidget, parentComboBox);
}

void GenreDialog::addSimilarGenre()
{
    addGenre(similarListWidget, similarComboBox);
}

void GenreDialog::populateGenreList()
{
    QSqlQuery query("SELECT name FROM genre");
    while (query.next())
    {
        QSqlRecord record = query.record();
        int n = record.indexOf("name");
        genreList.append(record.value(n).toString());
    }
}

void GenreDialog::removeGenre(QListWidget *listWidget)
{
    listWidget->takeItem(listWidget->currentRow());
}

void GenreDialog::removeParentGenre()
{
    removeGenre(parentListWidget);
}

void GenreDialog::removeSimilarGenre()
{
    removeGenre(similarListWidget);
}
