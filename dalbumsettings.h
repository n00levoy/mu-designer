#ifndef DALBUMSETTINGS_H
#define DALBUMSETTINGS_H

#include "dsettings.h"

struct mainAlbumSets
{
    QString artist;
    QString album;
    QString albumModifText;
    QString year;
    QString tracklist;
    QString country;
    QString full_length;
    QString listeners;

    QStringList genres;
    QStringList formats;

    int albumModif;
    int listenersModif;
};

struct coverAlbumSets
{
    QString small;
    QString big;
    QString fullsize;
};

struct bandLinksAlbumSets
{
    QString social;
    QString lastfm;
    QString listen;
    QString store;
};

struct downloadAlbumSets
{
    QStringList dl;
    QStringList formats;
};

struct prelistenAlbumSets
{
    QString pr;
};

class dAlbumSettings : public dSettings
{
    Q_OBJECT

public:
    dAlbumSettings(dTemplate* );

private:
    mainAlbumSets      mainSets;
    coverAlbumSets     coverSets;
    bandLinksAlbumSets bandSets;
    downloadAlbumSets  downloadSets;
    prelistenAlbumSets prelistenSets;

public slots:
    void setArtist              (QString);
    void setAlbum               (QString);
    void setAlbumModificatorText(QString);
    void setYear                (QString);
    void setTracklist           (QString);
    void setCountry             (QString);
    void setFullLength          (QString);
    void setListeners           (QString);

    void setGenres    (QString, int);
    void setFormats   (QString, int);

    void setAlbumModificator    (int);
    void setListenersModificator(int);

    void setSmallCover   (QString);
    void setBigCover     (QString);
    void setFullsizeCover(QString);

    void setSocialLink(QString);
    void setLastfmLink(QString);
    void setListenLink(QString);
    void setStoreLink (QString);

    void setDownloadAlbumLink  (int, QString);
    void setDownloadAlbumFormat(int, QString);

    void setPrelistenObject(QString);

signals:
    void sendParam(QString, QString);
};

#endif // DALBUMSETTINGS_H
