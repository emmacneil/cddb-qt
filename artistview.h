#ifndef ARTISTVIEW_H
#define ARTISTVIEW_H

#include "markdownview.h"

#include <QGroupBox>
#include <QSplitter>
#include <QTableView>

#include <QSqlQueryModel>

class ArtistView : public QSplitter
{
public:
    ArtistView();

private:
    QGroupBox *searchGroupBox;
    QGroupBox *resultsGroupBox;
    QGroupBox *detailsGroupBox;
    QTableView *tableView;
    QSqlQueryModel *queryModel;
    MarkdownView *markdownView;

    void initSearchGroupBox();
    void initResultsGroupBox();
    void initDetailsGroupBox();

private slots:
    void updateArtistList();
    void updateMarkdownView();
};

#endif // ARTISTVIEW_H
