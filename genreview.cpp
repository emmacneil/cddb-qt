#include "genreview.h"

#include <QGroupBox>
#include <QVBoxLayout>
#include <QTableView>

GenreView::GenreView() : QSplitter()
{
    // Genre tab is a QSplitter divided into two sections
    // Left-most section is a table displaying a list of genres
    // Right-most section displays more details about an genre selected from the left.
    queryModel = new QSqlQueryModel;

    initGenreListGroupBox();
    initDetailsGroupBox();
    updateGenreList();

    addWidget(genreListGroupBox);
    addWidget(detailsGroupBox);

    int w = width()/2;
    QList<int> sizes = {w, w};
    setSizes(sizes);
}

void GenreView::initDetailsGroupBox()
{
    detailsGroupBox = new QGroupBox(tr("Details"));
}

void GenreView::initGenreListGroupBox()
{
    // Create a QGroupBox to collect widgets related to search results
    genreListGroupBox  = new QGroupBox(tr("Genres"));

    // Add a layout to the QGroupBox
    QVBoxLayout *tableLayout = new QVBoxLayout;
    genreListGroupBox->setLayout(tableLayout);

    // Create a QTableView widget to show the genre list in a table
    tableView = new QTableView;
    tableLayout->addWidget(tableView);

    // Create a refresh button to update the genre list if new genres are added
    refreshButton = new QPushButton(tr("&Refresh"));
    connect(refreshButton, &QPushButton::clicked, this, &GenreView::updateGenreList);
    tableLayout->addWidget(refreshButton);
}

void GenreView::updateGenreList()
{
    queryModel->setQuery("SELECT name FROM genre");
    queryModel->setHeaderData(0, Qt::Horizontal, tr("Genre"));
    tableView->setModel(queryModel);
    tableView->resizeColumnsToContents();
    tableView->show();
}

