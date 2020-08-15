#ifndef ARTISTVIEW_H
#define ARTISTVIEW_H

#include <QGroupBox>
#include <QSplitter>

#include <QSqlQueryModel>

class ArtistView : public QSplitter
{
public:
    ArtistView();

private:
    QGroupBox *searchGroupBox;
    QGroupBox *resultsGroupBox;
    QGroupBox *detailsGroupBox;
    QSqlQueryModel *queryModel;

    void initSearchGroupBox();
    void initResultsGroupBox();
    void initDetailsGroupBox();
};

#endif // ARTISTVIEW_H
