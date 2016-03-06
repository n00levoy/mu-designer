#include "designer.h"
#include "ui_designer.h"

void designer::inputIcons()
{
    QDir dir("icons");
    QStringList filter("*.png");
    QStringList icons = dir.entryList(filter, QDir::Files);
    foreach(QString k, icons)
    {
        QPixmap iconPic = QPixmap::fromImage(generateIconPic("icons/" + k));
        QIcon icon(iconPic);
        if(k.contains("facebook") || k.contains("twitter"))
            ui->facebookIconBox->addItem(icon, k.remove(".png"));
        if(k.contains("lastfm"))
            ui->lastfmIconBox->addItem(icon, k.remove(".png"));
        if(k.contains("youtube") || k.contains("soundcloud"))
            ui->youtubeIconBox->addItem(icon, k.remove(".png"));
        if(k.contains("bandcamp") || k.contains("itunes") || k.contains("gplay"))
            ui->storeIconBox->addItem(icon, k.remove(".png"));
    }

    int size = settingsMap->value("icon_size").toInt();
    ui->facebookIconBox->setIconSize(QSize(size, size));
    ui->lastfmIconBox  ->setIconSize(QSize(size, size));
    ui->youtubeIconBox ->setIconSize(QSize(size, size));
    ui->storeIconBox   ->setIconSize(QSize(size, size));
}

void designer::updateIcons()
{
    ui->facebookIconBox->clear();
    ui->lastfmIconBox  ->clear();
    ui->youtubeIconBox ->clear();
    ui->storeIconBox   ->clear();

    inputIcons();
}

QImage designer::generateIconPic(QString iconFilename)
{
    int rad      = settingsMap->value("icon_radius")  .toInt();
    int picSize  = settingsMap->value("icon_pic_size").toInt();
    int iconType = settingsMap->value("icon_type")    .toInt();
    int shadow   = ui->iconShadowCheckBox->isChecked() ? 1 : 0;

    QPixmap icon(iconFilename);
    QPainter pntIcon(&icon);
    pntIcon.setCompositionMode(QPainter::CompositionMode_SourceIn);
    pntIcon.fillRect(icon.rect(), QColor(settingsMap->value("icon_text_color")));
    pntIcon.end();
    icon = icon.scaled(256 - picSize * 2, 256 - picSize * 2, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    int alphaMatrix[256][256], opacityDecrMatrix[256][256] = { 0 };
    if(shadow)
    {
        QImage imgr(256, 256, QImage::Format_ARGB32);
        QPainter pntr(&imgr);
        pntr.setRenderHint(QPainter::Antialiasing);

        pntr.setCompositionMode(QPainter::CompositionMode_Source);
        pntr.fillRect(imgr.rect(), QColor(Qt::transparent));
        pntr.setCompositionMode(QPainter::CompositionMode_SourceOver);

        pntr.setBrush(QColor("#FFFFFF"));
        pntr.drawPixmap(picSize, picSize, icon);

        pntr.end();

        for(int i = 0; i < imgr.height(); i++)
        {
            QRgb* rowData = (QRgb*)imgr.scanLine(i);
            for(int j = 0; j < imgr.width(); j++)
                alphaMatrix[i][j] = qAlpha(rowData[j]);
        }
        for(int i = 0; i < 256; i++)
        {
            for(int j = i, k = 0, flag = 0; j < 256 && k < 256; j++, k++)
            {
                if(alphaMatrix[j][k])
                    flag = 1;
                if(flag)
                    opacityDecrMatrix[j][k] = 1;
                else
                    opacityDecrMatrix[j][k] = 0;
            }
            for(int j = i, k = 0, flag = 0; j < 256 && k < 256; j++, k++)
            {
                if(alphaMatrix[k][j])
                    flag = 1;
                if (flag)
                    opacityDecrMatrix[k][j] = 1;
                else
                    opacityDecrMatrix[k][j] = 0;
            }
        }
    }

    QImage img(256, 256, QImage::Format_ARGB32);
    QPainter pnt(&img);
    pnt.setRenderHint(QPainter::Antialiasing);
    pnt.setBrush(QColor(settingsMap->value("icon_back_color")));

    pnt.setCompositionMode(QPainter::CompositionMode_Source);
    pnt.fillRect(img.rect(), QColor(Qt::transparent));
    pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);

    switch(iconType)
    {
    case 1:                                 // Empty Circle
        pnt.drawEllipse(0, 0, 256, 256);
        pnt.setBrush(QColor(1, 1, 1, 0));
        pnt.setCompositionMode(QPainter::CompositionMode_Source);
        pnt.drawEllipse(rad, rad, 256 - rad * 2, 256 - rad * 2);
        pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);
        break;

    case 2:                                 // Filled Circle
        pnt.drawEllipse(0, 0, 256, 256);
        break;

    case 3:                                 // Rectangle
        pnt.drawRoundedRect(0, 0, 256, 256, rad, rad, Qt::RelativeSize);
        break;

    case 4:                                 // Hexagon
    {
        QVector<QPoint> vec;
        vec << QPoint(256 / 2, 0) << QPoint(0, 74) << QPoint(0, 182) << QPoint(256 / 2, 256)
            << QPoint(256, 182) << QPoint(256, 74);
        QPolygon pol(vec);
        pnt.drawPolygon(pol);
        break;
    }

    default:
        break;
    }

    if(iconType > 1 && shadow)
    {
        for(int i = 0; i < 256; i++)
        {
            QRgb* rowData = (QRgb*)img.scanLine(i);
            for(int j = 0; j < 256; j++)
            {
                if(opacityDecrMatrix[i][j] && qAlpha(rowData[j]) != 0)
                    img.setPixel(j, i, QColor(rowData[j]).darker(180).rgba());
            }
        }
    }

    pnt.drawPixmap(picSize, picSize, icon);
    pnt.end();

    int size = settingsMap->value("icon_size").toInt();
    img = img.scaled(size, size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    return img;
}

void designer::uploadIcons()
{
    if(!QDir("designer_temp").exists())
        QDir().mkdir("designer_temp");

    uploadIcon("icons/" + ui->facebookIconBox->currentText() + ".png");
    uploadIcon("icons/" + ui->lastfmIconBox  ->currentText() + ".png");
    uploadIcon("icons/" + ui->youtubeIconBox ->currentText() + ".png");
    uploadIcon("icons/" + ui->storeIconBox   ->currentText() + ".png");
}

void designer::uploadIcon(QString filename)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(iconUploadFinished(QNetworkReply*)));

    QString type;
    if(filename.contains("facebook") || filename.contains("twitter"))
        type = "facebook";
    else if(filename.contains("lastfm"))
        type = "lastfm";
    else if(filename.contains("youtube") || filename.contains("soundcloud"))
        type = "youtube";
    else
        type = "store";

    QNetworkRequest request;
    request.setUrl(QUrl("https://api.imgur.com/3/upload?image=&title=" + type));
    request.setRawHeader(QString("Authorization").toUtf8(), QString("Client-ID 272a620ab69316a").toUtf8());

    QImage img = generateIconPic(filename);
    img.save("designer_temp/" + filename.remove("icons/"), "PNG", 100);

    QByteArray bytes;

    QFile image("designer_temp/" + filename);
    if(image.open(QIODevice::ReadOnly))
        bytes = image.readAll();
    image.close();

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\"")); //filename=\"facebook_1.png\""));
    imagePart.setBody(bytes);
    multiPart->append(imagePart);
    multiPart->setParent(this);

    manager->post(request, multiPart);
}

void designer::iconUploadFinished(QNetworkReply* reply)
{
    QString answ = reply->readAll();

    QJsonDocument doc = QJsonDocument::fromJson(answ.toUtf8());
    QJsonObject jsonObj = doc.object();
    QJsonObject jsonData = jsonObj["data"].toObject();
    if(jsonData["title"].toString() == "facebook")
        ui->facebookIconLine->setText(jsonData["link"].toString());
    else if (jsonData["title"].toString() == "lastfm")
        ui->lastfmIconLine->setText(jsonData["link"].toString());
    else if (jsonData["title"].toString() == "youtube")
        ui->youtubeIconLine->setText(jsonData["link"].toString());
    else
        ui->storeIconLine->setText(jsonData["link"].toString());

    reply->deleteLater();
}
