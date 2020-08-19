#ifndef GENREVIEW_H
#define GENREVIEW_H

#include "markdownview.h"

#include <QGroupBox>
#include <QPushButton>
#include <QSplitter>
#include <QTableView>

#include <QSqlQueryModel>

class GenreView : public QSplitter
{
public:
    GenreView();
    std::optional<int> getSelectedGenreID();

private:
    QGroupBox *genreListGroupBox;
    QGroupBox *detailsGroupBox;
    QPushButton *refreshButton;
    QTableView *tableView;
    QSqlQueryModel *queryModel;
    MarkdownView *markdownView;

    void initGenreListGroupBox();
    void initDetailsGroupBox();

private slots:
    void updateGenreList();
    void updateMarkdownView();
};

#endif // GENREVIEW_H
