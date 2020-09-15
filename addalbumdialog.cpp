#include "addalbumdialog.h"
#include "cddb.h"

#include <QDebug>
#include <QSqlQuery>

AddAlbumDialog::AddAlbumDialog(QWidget *parent) : AlbumDialog(parent)
{
    setWindowTitle(tr("Add Album to Database"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AddAlbumDialog::addAlbumToDatabase);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AddAlbumDialog::reject);
}

void AddAlbumDialog::addAlbumToDatabase()
{
    cddb::Album album;

    fillAlbumDetails(album);

    qDebug() << "in addAlbumToDatabase: release type ID" << album.getReleaseTypeID();
    cddb::addAlbum(album);

    accept();
}
