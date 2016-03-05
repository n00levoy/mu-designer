#include "dalbumsettings.h"

dAlbumSettings::dAlbumSettings(dTemplate* tmplt) : dSettings(tmplt)
{
    mainSets.albumModif     = 0;
    mainSets.listenersModif = 0;
}

void dAlbumSettings::setArtist    (QString str) { mainSets.artist      = str; sendParam("Artist",     mainSets.artist     ); }
void dAlbumSettings::setYear      (QString str) { mainSets.year        = str; sendParam("Year",       mainSets.year       ); }
void dAlbumSettings::setTracklist (QString str) { mainSets.tracklist   = str; sendParam("Tracklist",  mainSets.tracklist  ); }
void dAlbumSettings::setCountry   (QString str) { mainSets.country     = str; sendParam("Country",    mainSets.country    ); }
void dAlbumSettings::setFullLength(QString str) { mainSets.full_length = str; sendParam("FullLength", mainSets.full_length); }

void dAlbumSettings::setAlbum(QString str)
{
    mainSets.album = str;

    if (mainSets.albumModif)
        sendParam("Album", mainSets.album + " " + mainSets.albumModifText);
    else
        sendParam("Album", mainSets.album);
}

void dAlbumSettings::setAlbumModificatorText(QString str)
{
    mainSets.albumModifText = str;

    if(mainSets.albumModif)
        sendParam("Album", mainSets.album + " " + mainSets.albumModifText);
    else
        sendParam("Album", mainSets.album);
}

void dAlbumSettings::setAlbumModificator(int d)
{
    mainSets.albumModif = (d) ? 1 : 0;

    if(mainSets.albumModif)
        sendParam("Album", mainSets.album + " " + mainSets.albumModifText);
    else
        sendParam("Album", mainSets.album);
}

void dAlbumSettings::setGenres(QString str, int num)
{
    if(mainSets.genres.count() < num && mainSets.genres.at(num) == "")
        mainSets.genres.insert(num, str);
    else
        mainSets.genres.replace(num, str);

    sendParam("Genres", mainSets.genres.join(" / "));
}

void dAlbumSettings::setFormats(QString str, int num)
{
    if(mainSets.formats.count() < num && mainSets.formats.at(num) == "")
        mainSets.formats.insert(num, str);
    else
        mainSets.formats.replace(num, str);

    sendParam("Formats", mainSets.formats.join(" / "));
}

void dAlbumSettings::setDownloadAlbumLink(int num, QString str)
{
    if(downloadSets.dl.count() <= num)
        downloadSets.dl.append(str);
    else
        downloadSets.dl.replace(num, str);

    QString dlLinks;
    int i = 0;
    foreach(QString k, downloadSets.dl)
    {
        dlLinks += designTemplate->createDownloadLink(k, downloadSets.formats[i]);
        dlLinks += " - ";
        i++;
    }
    dlLinks = dlLinks.remove(dlLinks.size() - 3, 3);
}

void dAlbumSettings::setDownloadAlbumFormat(int num, QString str)
{
    if(downloadSets.formats.count() <= num)
        downloadSets.formats.append(str);
    else
        downloadSets.formats.replace(num, str);

    /* ДОПИСАТЬ ОТПРАВКУ В ШАБЛОН */
}

void dAlbumSettings::setListeners(QString str)
{
    mainSets.listeners   = str;

    if(mainSets.listenersModif)
        sendParam("Listeners", mainSets.listeners);
}

void dAlbumSettings::setListenersModificator(int d)
{
    mainSets.listenersModif = (d) ? 1 : 0;

    if(mainSets.listenersModif)
        sendParam("Listeners", mainSets.listeners);
}

void dAlbumSettings::setSmallCover   (QString str) { coverSets.small    = str; sendParam("smallCover",    coverSets.small);    }
void dAlbumSettings::setBigCover     (QString str) { coverSets.big      = str; sendParam("bigCover",      coverSets.big);      }
void dAlbumSettings::setFullsizeCover(QString str) { coverSets.fullsize = str; sendParam("fullsizeCover", coverSets.fullsize); }

void dAlbumSettings::setSocialLink(QString str) { bandSets.social = str; sendParam("socialLink", bandSets.social); }
void dAlbumSettings::setLastfmLink(QString str) { bandSets.lastfm = str; sendParam("lastfmLink", bandSets.lastfm); }
void dAlbumSettings::setListenLink(QString str) { bandSets.listen = str; sendParam("listenLink", bandSets.listen); }
void dAlbumSettings::setStoreLink (QString str) { bandSets.store  = str; sendParam("storeLink",  bandSets.store);  }

void dAlbumSettings::setPrelistenObject(QString str) { prelistenSets.pr = str; sendParam("prelistenObject", bandSets.store); }
