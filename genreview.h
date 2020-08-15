#ifndef GENREVIEW_H
#define GENREVIEW_H

#include <QGroupBox>
#include <QSplitter>

#include <QSqlQueryModel>

class GenreView : public QSplitter
{
public:
    GenreView();
    void updateGenreList();
private:
    QGroupBox *genreListGroupBox;
    QGroupBox *detailsGroupBox;
    QSqlQueryModel *queryModel;

    void initGenreListGroupBox();
    void initDetailsGroupBox();
};

#endif // GENREVIEW_H
