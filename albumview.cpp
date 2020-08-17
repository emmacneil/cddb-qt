#include "albumview.h"

#include <QHBoxLayout>
#include <QList>

#include <QSqlQuery>

AlbumView::AlbumView() : QSplitter()
{
    // Album tab is a QSplitter divided into three sections
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

    connect(tableView, &QTableView::clicked, this, &AlbumView::updateMarkdownView);
}

void AlbumView::initDetailsGroupBox()
{
    detailsGroupBox = new QGroupBox(tr("Details"));

    QVBoxLayout *detailsLayout = new QVBoxLayout;
    detailsGroupBox->setLayout(detailsLayout);

    markdownView = new MarkdownView;
    detailsLayout->addWidget(markdownView);
}

void AlbumView::initResultsGroupBox()
{
    // Create a QGroupBox to collect widgets related to search results
    resultsGroupBox = new QGroupBox(tr("Results"));

    // Add a layout to the QGroupBox
    QHBoxLayout *tableLayout = new QHBoxLayout;
    resultsGroupBox->setLayout(tableLayout);

    // Create a QTableView widget to show the search results in a table
    tableView = new QTableView;
    tableView->setModel(queryModel);
    tableView->resizeColumnsToContents();
    tableView->show();
    tableLayout->addWidget(tableView);
}

void AlbumView::initSearchGroupBox()
{
    searchGroupBox  = new QGroupBox(tr("Search"));

    // TODO: This code bit probably makes more sense in another method
    queryModel->setQuery("SELECT title, release_year FROM album");
    queryModel->setHeaderData(0, Qt::Horizontal, tr("Title"));
    queryModel->setHeaderData(1, Qt::Horizontal, tr("Year"));
}

void AlbumView::updateMarkdownView()
{
    QItemSelectionModel *selectionModel = tableView->selectionModel();
    QList<QModelIndex> selectedRows = selectionModel->selectedRows();
    if (selectedRows.size() == 1)
    {
        QModelIndex i = selectedRows[0];
        int albumID = tableView->model()->data(i).toInt(); // TODO : Why does this select the ID and not the name column?
        // Find notes for the selected album
        QSqlQuery query;
        query.prepare("SELECT notes FROM album WHERE id = ?");
        query.bindValue(0, albumID);
        query.exec();
        query.next();
        QString md = query.value(0).toString();

        // Set notes in markdown
        markdownView->setMarkdown(md);
    }
    else
    {
        markdownView->setMarkdown("");
    }
}
