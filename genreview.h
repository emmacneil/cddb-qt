#ifndef GENREVIEW_H
#define GENREVIEW_H

#include <QGroupBox>
#include <QPushButton>
#include <QSplitter>
#include <QTableView>

#include <QSqlQueryModel>

class GenreView : public QSplitter
{
public:
    GenreView();

private:
    QGroupBox *genreListGroupBox;
    QGroupBox *detailsGroupBox;
    QPushButton *refreshButton;
    QSqlQueryModel *queryModel;
    QTableView *tableView;

    void initGenreListGroupBox();
    void initDetailsGroupBox();

private slots:
    void updateGenreList();
};

#endif // GENREVIEW_H
