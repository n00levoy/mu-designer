#include "designer.h"
#include "ui_designer.h"

void designer::lastSearch()
{
    QNetworkAccessManager* lmanager = new QNetworkAccessManager(this);
    QString str = settingsMap->value("artist");
    str = str.replace(" ", "+");
    QNetworkRequest lrequest(QUrl("http://ws.audioscrobbler.com/2.0/?method=artist.getInfo"
                                  "&api_key=0eba4e8b2e234125dcc44868d43e89a5&artist=" + str));
    lmanager->get(lrequest);

    connect(lmanager, SIGNAL(finished(QNetworkReply*)), SLOT(lastSearchFinished(QNetworkReply*)));
}

void designer::lastSearchFinished(QNetworkReply* reply)
{
    QXmlStreamReader rd(reply->readAll());
    QString listnrs;
    do
    {
        rd.readNext();
        if(rd.name() == "listeners")
        {
            rd.readNext();
            listnrs = rd.text().toString();
            rd.readNext();
        }
    }
    while(!rd.atEnd());

    ui->listenersLine->setText(listnrs);
}
