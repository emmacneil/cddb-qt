#include "artistview.h"

#include <QHBoxLayout>
#include <QList>
#include <QTableView>

ArtistView::ArtistView() : QSplitter()
{
    // Artist tab is a QSplitter divided into three sections
    // Left-most section has a number of editable fields for search queries
    // Middle section is a table displaying a list of search results
    // Right-most section displays more details about an item selected from the middle table.
    queryModel = new QSqlQueryModel;

    initSearchGroupBox();
    initResultsGroupBox();
    initDetailsGroupBox();

    addWidget(searchGroupBox);
    addWidget(resultsGroupBox);
    addWidget(detailsGroupBox);

    int w = width()/3;
    QList<int> sizes = {w, w, w};
    setSizes(sizes);
}

void ArtistView::initDetailsGroupBox()
{
    detailsGroupBox = new QGroupBox(tr("Details"));
}

void ArtistView::initResultsGroupBox()
{
    // Create a QGroupBox to collect widgets related to search results
    resultsGroupBox = new QGroupBox(tr("Results"));

    // Add a layout to the QGroupBox
    QHBoxLayout *tableLayout = new QHBoxLayout;
    resultsGroupBox->setLayout(tableLayout);

    // Create a QTableView widget to show the search results in a table
    QTableView *tableView = new QTableView;
    tableView->setModel(queryModel);
    tableView->resizeColumnsToContents();
    tableView->show();
    tableLayout->addWidget(tableView);
}

void ArtistView::initSearchGroupBox()
{
    searchGroupBox  = new QGroupBox(tr("Search"));

    // TODO: This code bit probably makes more sense in another method
    queryModel->setQuery("SELECT name, country FROM artist");
    queryModel->setHeaderData(0, Qt::Horizontal, tr("Artist"));
    queryModel->setHeaderData(1, Qt::Horizontal, tr("Country"));
}
