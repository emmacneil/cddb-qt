#include "genreview.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QTableView>

GenreView::GenreView() : QSplitter()
{
    // Genre tab is a QSplitter divided into two sections
    // Left-most section is a table displaying a list of genres
    // Right-most section displays more details about an genre selected from the left.
    queryModel = new QSqlQueryModel;

    initGenreListGroupBox();
    initDetailsGroupBox();

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
    QHBoxLayout *tableLayout = new QHBoxLayout;
    genreListGroupBox->setLayout(tableLayout);

    // Create a QTableView widget to show the genre list in a table
    QTableView *tableView = new QTableView;
    updateGenreList();
    tableView->setModel(queryModel);
    tableView->resizeColumnsToContents();
    tableView->show();
    tableLayout->addWidget(tableView);
}

void GenreView::updateGenreList()
{
    queryModel->setQuery("SELECT name FROM genre");
    queryModel->setHeaderData(0, Qt::Horizontal, tr("Genre"));
}

