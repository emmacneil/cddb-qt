#ifndef ALBUMVIEW_H
#define ALBUMVIEW_H

#include <QGroupBox>
#include <QSplitter>

#include <QSqlQueryModel>

class AlbumView : public QSplitter
{
public:
    AlbumView();

private:
    QGroupBox *searchGroupBox;
    QGroupBox *resultsGroupBox;
    QGroupBox *detailsGroupBox;
    QSqlQueryModel *queryModel;

    void initSearchGroupBox();
    void initResultsGroupBox();
    void initDetailsGroupBox();
};

#endif // ALBUMVIEW_H
