#include "designer.h"
#include "ui_designer.h"

void designer::uploadCoversDialog()
{
    QString coverlink = QInputDialog::getText(0, "Ссылка на изображение", "Укажите ссылку на изображение для загрузки");
    if(QUrl(coverlink).isValid())
        uploadImages(coverlink);
}

void designer::uploadImages(QString link)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinished(QNetworkReply*)));
    QNetworkRequest request;
    request.setUrl(QUrl(link));
    manager->get(request);
}

void designer::downloadFinished(QNetworkReply* reply)
{
    if(!QDir("designer_temp").exists())
        QDir().mkdir("designer_temp");

    QFile cover("designer_temp/cover.jpeg");
    if(cover.open(QIODevice::WriteOnly))
        cover.write(reply->readAll());
    cover.close();

    QImage fullsize_pic("designer_temp/cover.jpeg");
    QImage big_pic = fullsize_pic.scaled(500, 500, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    big_pic.save("designer_temp/cover500x500.jpeg");
    QImage small_pic = fullsize_pic.scaled(300, 300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    small_pic.save("designer_temp/cover300x300.jpeg");

    uploadCover("cover.jpeg");
    uploadCover("cover500x500.jpeg");
    uploadCover("cover300x300.jpeg");

    reply->deleteLater();
}

void designer::uploadCover(QString filename)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(uploadFinished(QNetworkReply*)));

    QNetworkRequest request;
    request.setUrl(QUrl("https://api.imgur.com/3/upload?image="));
    request.setRawHeader(QString("Authorization").toUtf8(), QString("Client-ID 272a620ab69316a").toUtf8());

    QByteArray byte;

    QFile image("designer_temp/" + filename);
    if(image.open(QIODevice::ReadOnly))
        byte = image.readAll();
    image.close();

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\"")); //filename=\"" + filename + "\""));
    imagePart.setBody(byte);
    multiPart->append(imagePart);
    multiPart->setParent(this);

    manager->post(request, multiPart);
}

void designer::uploadFinished(QNetworkReply* reply)
{
    QString answ = reply->readAll();

    QJsonDocument doc = QJsonDocument::fromJson(answ.toUtf8());
    QJsonObject jsonObj = doc.object();
    QJsonObject jsonData = jsonObj["data"].toObject();
    if(jsonData["width"].toDouble() == 500)
        ui->bigCoverLine->setText(jsonData["link"].toString());
    else if (jsonData["width"].toDouble() == 300)
        ui->smallCoverLine->setText(jsonData["link"].toString());
    else
        ui->fullsizeCoverLine->setText(jsonData["link"].toString());

    reply->deleteLater();
}
