#include "albumview.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QList>
#include <QPushButton>

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

std::optional<int> AlbumView::getSelectedAlbumID()
{
    QItemSelectionModel *selectionModel = tableView->selectionModel();
    QList<QModelIndex> selectedRows = selectionModel->selectedRows();
    if (selectedRows.size() == 1)
    {
        QModelIndex i = selectedRows[0];
        return tableView->model()->data(i).toInt();
    }
    return {};
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
    QVBoxLayout *tableLayout = new QVBoxLayout;
    resultsGroupBox->setLayout(tableLayout);

    // Create a QTableView widget to show the search results in a table
    tableView = new QTableView;
    tableView->setModel(queryModel);
    tableView->hideColumn(0);
    tableView->resizeColumnsToContents();
    tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->show();
    tableLayout->addWidget(tableView);

    QPushButton *refreshButton = new QPushButton(tr("&Refresh"));
    tableLayout->addWidget(refreshButton);
    connect(refreshButton, &QPushButton::clicked, this, &AlbumView::updateAlbumList);
}

void AlbumView::initSearchGroupBox()
{
    searchGroupBox  = new QGroupBox(tr("Search"));

    updateAlbumList();
}

void AlbumView::updateAlbumList()
{
    queryModel->setQuery("SELECT id, title, release_year FROM album");
    queryModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    queryModel->setHeaderData(1, Qt::Horizontal, tr("Title"));
    queryModel->setHeaderData(2, Qt::Horizontal, tr("Year"));
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
