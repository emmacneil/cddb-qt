#include "addgenredialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>
#include <QGroupBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDialogButtonBox>

#include <QDebug>

AddGenreDialog::AddGenreDialog(QWidget *parent) : QDialog(parent)
{
    populateGenreList();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *dataLayout = new QHBoxLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QVBoxLayout *rightLayout = new QVBoxLayout;

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AddGenreDialog::addGenreToDatabase);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
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
    QPushButton *parentAddButton = new QPushButton(tr("Add"));
    QPushButton *parentRemoveButton = new QPushButton(tr("Remove"));
    parentComboBox->addItems(genreList);
    parentGroupBoxLayout->addWidget(parentComboBox, 0, 0);
    parentGroupBoxLayout->addWidget(parentAddButton, 0, 1);
    parentGroupBoxLayout->addWidget(parentListWidget, 1, 0);
    parentGroupBoxLayout->addWidget(parentRemoveButton, 1, 1, Qt::AlignTop);
    parentGroupBox->setLayout(parentGroupBoxLayout);
    leftLayout->addWidget(parentGroupBox);
    connect(parentAddButton, &QPushButton::clicked, this, &AddGenreDialog::addParentGenre);
    connect(parentRemoveButton, &QPushButton::clicked, this, &AddGenreDialog::removeParentGenre);

    QGroupBox *similarGroupBox = new QGroupBox(tr("Similar Genres"));
    QGridLayout *similarGroupBoxLayout = new QGridLayout;
    similarComboBox = new QComboBox;
    similarListWidget = new QListWidget;
    QPushButton *similarAddButton = new QPushButton(tr("Add"));
    QPushButton *similarRemoveButton = new QPushButton(tr("Remove"));
    similarComboBox->addItems(genreList);
    similarGroupBoxLayout->addWidget(similarComboBox, 0, 0);
    similarGroupBoxLayout->addWidget(similarAddButton, 0, 1);
    similarGroupBoxLayout->addWidget(similarListWidget, 1, 0);
    similarGroupBoxLayout->addWidget(similarRemoveButton, 1, 1, Qt::AlignTop);
    similarGroupBox->setLayout(similarGroupBoxLayout);
    leftLayout->addWidget(similarGroupBox);
    connect(similarAddButton, &QPushButton::clicked, this, &AddGenreDialog::addSimilarGenre);
    connect(similarRemoveButton, &QPushButton::clicked, this, &AddGenreDialog::removeSimilarGenre);

    QGroupBox *notesGroupBox = new QGroupBox(tr("Notes"));
    QVBoxLayout *notesGroupBoxLayout = new QVBoxLayout;
    notesTextEdit = new QTextEdit();
    notesGroupBoxLayout->addWidget(notesTextEdit);
    notesGroupBox->setLayout(notesGroupBoxLayout);
    rightLayout->addWidget(notesGroupBox);
}

AddGenreDialog::~AddGenreDialog()
{

}

void AddGenreDialog::addGenre(QListWidget *listWidget, QComboBox *comboBox)
{
    // Get the genre currently showing in the QComboBox
    QString genreName = comboBox->currentText();

    // Check if the genre is already in the QListWidget. If not, add it.
    QList<QListWidgetItem*> results = listWidget->findItems(genreName, Qt::MatchExactly);
    if (results.isEmpty())
        listWidget->addItem(genreName);
}

void AddGenreDialog::addGenreToDatabase()
{
    // Get data from dialog box's widgets
    QString genreName = nameLineEdit->text();
    QStringList parentGenres;
    QStringList similarGenres;
    QString notes = notesTextEdit->toPlainText();
    QListWidgetItem *result = nullptr;

    while (result = parentListWidget->takeItem(0))
        parentGenres.append(result->text());
    while (result = similarListWidget->takeItem(0))
        similarGenres.append(result->text());

    // Add a genre into database
    QSqlQuery query;
    query.prepare("INSERT INTO genre (name, notes) values (?, ?)");
    query.bindValue(0, genreName);
    query.bindValue(1, notes);
    query.exec();
    
    // Get ID of newly added genre
    query.prepare("SELECT id FROM genre WHERE name = ?");
    query.bindValue(0, genreName);
    query.exec();
    query.next();
    int genreID = query.value(0).toInt();

    // For each parent genre, create a relation in the database
    for (QString s : parentGenres)
    {
        query.prepare("SELECT id FROM genre WHERE name = ?");
        query.bindValue(0, s);
        query.exec();
        query.next();
        int parentID = query.value(0).toInt();

        query.prepare("INSERT INTO parent_genre_relation (parent, child) VALUES (?, ?)");
        query.bindValue(0, parentID);
        query.bindValue(1, genreID);
        query.exec();
    }

    // For each similargenre, create a relation in the database
    for (QString s : similarGenres)
    {
        query.prepare("SELECT id FROM genre WHERE name = ?");
        query.bindValue(0, s);
        query.exec();
        query.next();
        int similarID = query.value(0).toInt();

        query.prepare("INSERT INTO similar_genre_relation (genre1, genre2) VALUES (?, ?)");
        query.bindValue(0, genreID);
        query.bindValue(1, similarID);
        query.exec();
    }

    accept();
}

void AddGenreDialog::addParentGenre()
{
    addGenre(parentListWidget, parentComboBox);
}

void AddGenreDialog::addSimilarGenre()
{
    addGenre(similarListWidget, similarComboBox);
}

void AddGenreDialog::populateGenreList()
{
    QSqlQuery query("SELECT name FROM genre");
    while (query.next())
    {
        QSqlRecord record = query.record();
        int n = record.indexOf("name");
        genreList.append(record.value(n).toString());
    }
}

void AddGenreDialog::removeGenre(QListWidget *listWidget)
{
    listWidget->takeItem(listWidget->currentRow());
}

void AddGenreDialog::removeParentGenre()
{
    removeGenre(parentListWidget);
}

void AddGenreDialog::removeSimilarGenre()
{
    removeGenre(similarListWidget);
}
