#include "genreview.h"

#include <QDebug>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QTextEdit>

#include <QSqlQuery>
#include <QSqlResult>

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

    connect(tableView, &QTableView::clicked, this, &GenreView::updateMarkdownView);
}

void GenreView::initDetailsGroupBox()
{
    detailsGroupBox = new QGroupBox(tr("Details"));

    QVBoxLayout *detailsLayout = new QVBoxLayout;
    detailsGroupBox->setLayout(detailsLayout);

    markdownView = new MarkdownView;
    detailsLayout->addWidget(markdownView);
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
    tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableLayout->addWidget(tableView);

    // Create a refresh button to update the genre list if new genres are added
    refreshButton = new QPushButton(tr("&Refresh"));
    connect(refreshButton, &QPushButton::clicked, this, &GenreView::updateGenreList);
    tableLayout->addWidget(refreshButton);
}

void GenreView::updateGenreList()
{
    queryModel->setQuery("SELECT id, name FROM genre");
    queryModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    queryModel->setHeaderData(1, Qt::Horizontal, tr("Genre"));
    tableView->setModel(queryModel);
    tableView->hideColumn(0);
    tableView->resizeColumnsToContents();
    tableView->show();
}

void GenreView::updateMarkdownView()
{
    QItemSelectionModel *selectionModel = tableView->selectionModel();
    QList<QModelIndex> selectedRows = selectionModel->selectedRows();
    if (selectedRows.size() == 1)
    {
        QModelIndex i = selectedRows[0];
        int genreID = tableView->model()->data(i).toInt(); // TODO : Why does this select the ID and not the name column?
        // Find notes for the selected genre
        QSqlQuery query;
        query.prepare("SELECT notes FROM genre WHERE id = ?");
        query.bindValue(0, genreID);
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
