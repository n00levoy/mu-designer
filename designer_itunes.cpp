#include "designer.h"
#include "ui_designer.h"

void designer::getItunesLinks()
{
    gItL                       = new QWidget;
    QGridLayout* gItLlayout    = new QGridLayout;
    QLineEdit*   albumNameLine = new QLineEdit;
    QLineEdit*   itLinkLine    = new QLineEdit;
    QLineEdit*   itPicLinkLine = new QLineEdit;
    QPushButton* startSearchButton = new QPushButton("Поиск");
    QPushButton* uploadCoverButton = new QPushButton("Загрузить обложку");
    QPushButton* copyToStoreButton = new QPushButton("Одобрить ссылку");
    QPushButton* okButton          = new QPushButton("Ok");

    itLinkLine   ->setReadOnly(true);
    itPicLinkLine->setReadOnly(true);

    itLinkLine->setObjectName("itLinkLine");
    itPicLinkLine->setObjectName("itPicLinkLine");

    gItLlayout->addWidget(new QLabel("Название альбома"), 0, 0);
    gItLlayout->addWidget(albumNameLine, 0, 1);
    gItLlayout->addWidget(startSearchButton, 0, 2);
    gItLlayout->addWidget(new QLabel("Ссылка на альбом в Itunes"), 2, 0);
    gItLlayout->addWidget(itLinkLine, 2, 1);
    gItLlayout->addWidget(copyToStoreButton);
    gItLlayout->addWidget(new QLabel("Ссылка на обложку"), 3, 0);
    gItLlayout->addWidget(itPicLinkLine, 3, 1);
    gItLlayout->addWidget(uploadCoverButton, 3, 2);
    gItLlayout->addWidget(okButton, 4, 2);
    gItL->setLayout(gItLlayout);

    gItL->show();

    QString albumName = settingsMap->value("artist") + " " + settingsMap->value("album");
    albumNameLine->setText(albumName);
    albumNameLine->setObjectName("albumNameLine");

    connect(startSearchButton, SIGNAL(clicked(bool)), SLOT(itunesSearchAlbum()));
    connect(okButton, SIGNAL(clicked(bool)), gItL, SLOT(close()));
    connect(copyToStoreButton, SIGNAL(clicked(bool)), SLOT(copyToStore()));
    connect(uploadCoverButton, SIGNAL(clicked(bool)), SLOT(uploadItunesCover()));
}

void designer::copyToStore()
{
    ui->storeLinkLine->setText(gItL->findChild<QLineEdit*>("itLinkLine")->text());
}

void designer::uploadItunesCover()
{
    uploadImages(gItL->findChild<QLineEdit*>("itPicLinkLine")->text());
}

void designer::itunesSearchAlbum()
{
    QString whatSearch = gItL->findChild<QLineEdit*>("albumNameLine")->text();
    whatSearch = whatSearch.replace(" ", "+");
    QNetworkAccessManager* itManager = new QNetworkAccessManager(this);
    QNetworkRequest itRequest;
    itRequest.setUrl(QUrl("https://itunes.apple.com/search?term=" + whatSearch + "&entity=album"));
    itManager->get(itRequest);

    connect(itManager, SIGNAL(finished(QNetworkReply*)), SLOT(itunesSearchFinished(QNetworkReply*)));
}

void designer::itunesSearchFinished(QNetworkReply* reply)
{
    QString answ = reply->readAll();

    QJsonDocument doc = QJsonDocument::fromJson(answ.toUtf8());
    QJsonObject jsonObj = doc.object();
    QJsonArray jsonArObj = jsonObj["results"].toArray();
    QJsonObject jsonFirObj = jsonArObj.first().toObject();

    gItL->findChild<QLineEdit*>("itLinkLine")->setText(jsonFirObj.value("collectionViewUrl").toString());
    gItL->findChild<QLineEdit*>("itPicLinkLine")->setText(jsonFirObj.value("artworkUrl100").toString().replace("100x100bb", "1400x1400bb"));

    reply->deleteLater();
}
