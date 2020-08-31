#ifndef ALBUMVIEW_H
#define ALBUMVIEW_H

#include "markdownview.h"

#include <QGroupBox>
#include <QSplitter>
#include <QTableView>

#include <QSqlQueryModel>

class AlbumView : public QSplitter
{
public:
    AlbumView();

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
    void updateAlbumList();
    void updateMarkdownView();
};


#endif // ALBUMVIEW_H
