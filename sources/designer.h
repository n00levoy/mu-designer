#ifndef DESIGNER_H
#define DESIGNER_H

#include <QtWidgets>
#include <QtNetwork>
#include <QJsonDocument>
#include "coloredbutton.h"
#include "dtemplate.h"
#include "dalbumsettings.h"

namespace Ui {
class designer;
}

class designer : public QMainWindow
{
    Q_OBJECT

private:
    Ui::designer *ui;

    QMap<QString, QString>* settingsMap;
    QWidget*                gItL;

    void guiConnections();

    void setDefaultTemplates();
    void setDefaultSettings();

    void updateContent();
    void postProcessing();

    void getFiles(QStringList);

    void   inputIcons();

    QImage generateIconPic(QString);
    void   uploadIcon(QString);

    void uploadImages(QString link);

    void lastSearch();

public:
    designer(QWidget *parent = 0);
    ~designer();

private slots:
    void setSetting(QString);
    void addDownloadLink();
    void addGenre();
    void deleteGenre();
    void updateContentSlot() { updateContent(); }

    void getFilesFromList();
    void getFilesFromFolder();
    void loadTemplate();

    void uploadCover(QString);
    void uploadCoversDialog();
    void uploadFinished  (QNetworkReply*);
    void downloadFinished(QNetworkReply*);

    void itunesSearchAlbum();
    void itunesSearchFinished(QNetworkReply*);
    void getItunesLinks();
    void copyToStore();
    void uploadItunesCover();

    void lastSearchFinished(QNetworkReply*);

    void updateIcons();
    void uploadIcons();
    void iconUploadFinished(QNetworkReply*);

signals:

private:
    QString titleTemplate;
    QString shortTemplate;
    QString fullTemplate;
    QString linkTemplate;
};

#endif // DESIGNER_H
