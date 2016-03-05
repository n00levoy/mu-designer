#include "designer.h"
#include "ui_designer.h"
#include "textedit.h"

designer::designer(QWidget *parent) : QMainWindow(parent), ui(new Ui::designer)
{
    ui->setupUi(this);
    guiConnections();

    settingsMap  = new QMap<QString, QString>;

    setDefaultTemplates();

    ui->titleLine    ->setText     (titleTemplate);
    ui->shortCodeText->setPlainText(shortTemplate);
    ui->fullCodeText ->setPlainText(fullTemplate );

    ui->settingsTab->setMinimumWidth(ui->otherSetsTab->width() + 20);

    setWindowTitle("Оформляшка");
    ui->modComboBox->adjustSize();

    setDefaultSettings();

    settingsMap->insert("icon_type", "0");
    ui->iconPicSizeBox->setValue(50);
    ui->iconSizeBox   ->setValue(50);
    ui->iconRadiusSpinbox->setValue(10);

    dTemplate tmplt;
    dAlbumSettings alSets(&tmplt);
    //alSets.setDownloadAlbumFormat(0, "MP3");
    //alSets.setDownloadAlbumLink(0, "https://yadi.sk/d/nY3DXClTpEB5M");
    //alSets.setDownloadAlbumFormat(1, "FLAC");
    //alSets.setDownloadAlbumLink(1, "https://cloud.mail.ru/public/EJFJ/u2pqQLexo");
}

designer::~designer()
{
    delete settingsMap;
    delete gItL;
    if(QDir("designer_temp").exists())
        QDir("designer_temp").removeRecursively();
}

void designer::setSetting(QString str)
{
    QString object = sender()->objectName();
    if(object != "")
    {
        if(object == "artistLine")
        {
            settingsMap->insert("artist", str);
            str.replace(" ", "+");
            ui->lastfmLinkLine->setText("http://www.last.fm/ru/music/" + str);
            lastSearch();
        }
        if(object == "albumLine")
            settingsMap->insert("album",       str);
        if(object == "yearSpinBox")
            settingsMap->insert("year",        str);
        if(object == "tracklistText")
            settingsMap->insert("tracklist",   str);
        if(object == "countryLine")
            settingsMap->insert("country",     str);
        if(object == "listenersLine")
            settingsMap->insert("listeners",   str);
        if(object == "lengthLine")
            settingsMap->insert("full_length", str);

        if(object == "smallCoverLine")
            settingsMap->insert("small_cover",    str);
        if(object == "bigCoverLine")
            settingsMap->insert("big_cover",      str);
        if(object == "fullsizeCoverLine")
            settingsMap->insert("fullsize_cover", str);

        if(object == "facebookLinkLine")
            settingsMap->insert("facebook_link", str);
        if(object == "lastfmLinkLine")
            settingsMap->insert("lastfm_link", str);
        if(object == "youtubeLinkLine")
            settingsMap->insert("youtube_link", str);
        if(object == "storeLinkLine")
            settingsMap->insert("store_link", str);

        if(object == "prelistenObjectText")
            settingsMap->insert("prelisten_object", str);

        if(object == "textColorLine")
            settingsMap->insert("text_color", str);
        if(object == "linkColorLine")
            settingsMap->insert("link_color", str);
        if(object == "backgrndColorLine")
            settingsMap->insert("backgrnd_color", str);
        if(object == "linkBcgrdColorLine")
            settingsMap->insert("link_bcgrd_color", str);

        if(object == "facebookIconLine")
            settingsMap->insert("facebook_icon", str);
        if(object == "lastfmIconLine")
            settingsMap->insert("lastfm_icon", str);
        if(object == "youtubeIconLine")
            settingsMap->insert("youtube_icon", str);
        if(object == "storeIconLine")
            settingsMap->insert("store_icon", str);

        if(object == "iconTextColorLine")
            settingsMap->insert("icon_text_color", str);
        if(object == "iconBackColorLine")
            settingsMap->insert("icon_back_color", str);
        if(object == "iconRadiusSpinbox")
            settingsMap->insert("icon_radius", str);
        if(object == "iconSizeBox")
            settingsMap->insert("icon_size", str);
        if(object == "iconPicSizeBox")
            settingsMap->insert("icon_pic_size", str);
        if(object == "iconBackTypeBox")
        {
            if(str == "Без фона")
                settingsMap->insert("icon_type", "0");
            if(str == "Окружность")
                settingsMap->insert("icon_type", "1");
            if(str == "Круг")
                settingsMap->insert("icon_type", "2");
            if(str == "Квадрат")
                settingsMap->insert("icon_type", "3");
            if(str == "Шестиугольник")
                settingsMap->insert("icon_type", "4");
        }

        if(object.contains("genreLine"))
            settingsMap->insert(QString("genre") + object[object.length() - 1], str);
        if(object.contains("formatComboBox"))
            settingsMap->insert(QString("format") + object[object.length() - 1], str);
        if(object.contains("dl_linkLine"))
            settingsMap->insert(QString("dl_link") + object[object.length() - 1], str);
        if(object.contains("dl_forlinkComboBox"))
            settingsMap->insert(QString("dl_forlink") + object[object.length() - 1], str);
    }

    updateContent();
}

void designer::updateContent()
{
    QString shortFiller = shortTemplate,
            fullFiller  = fullTemplate,
            titleFiller = titleTemplate;

    QString genreString = "%GENRES%";
    QString shortFormat = "%SHORT_FORMAT%", fullFormat = "%FORMAT%";
    QString downloadLinks = "%DOWNLOAD_LINKS%";

    QStringList keys = settingsMap->keys();
    foreach(QString k, keys)
    {
        if(settingsMap->value(k) != "")
        {
            if(k == "artist")
            {
                titleFiller.replace("%ARTIST_NAME%", settingsMap->value(k));
                fullFiller .replace("%ARTIST_NAME%", settingsMap->value(k));
            }
            if(k == "album")
            {
                QString album = settingsMap->value(k);
                if(ui->modComboBox->isEnabled() && ui->modComboBox->currentText() != "-")
                    album += " " + ui->modComboBox->currentText();
                titleFiller.replace("%ALBUM%", album);
                fullFiller .replace("%ALBUM%", album);
            }
            if(k == "year")
            {
                titleFiller.replace("%YEAR%", settingsMap->value(k));
                fullFiller .replace("%YEAR%", settingsMap->value(k));
            }
            if(k == "tracklist")
            {
                shortFiller.replace("%TRACKLIST%", settingsMap->value(k));
                fullFiller .replace("%TRACKLIST%", settingsMap->value(k));
            }
            if(k == "country")
                fullFiller .replace("%COUNTRY%", settingsMap->value(k));
            if(k == "listeners")
            {
                if(ui->listenersCheckBox->isChecked())
                    shortFiller.replace("%LISTENERS%", settingsMap->value(k));
                else
                    shortFiller.replace("%LISTENERS%", "%LISTENERS%");
            }
            if(k == "full_length")
                fullFiller .replace("%FULL_LENGTH%", settingsMap->value(k));

            if(k == "small_cover")
                shortFiller.replace("%SMALL_COVER%", settingsMap->value(k));
            if(k == "big_cover")
                fullFiller .replace("%BIG_COVER%", settingsMap->value(k));
            if(k == "fullsize_cover")
                fullFiller .replace("%FULLSIZE_COVER%", settingsMap->value(k));

            if(k == "facebook_link")
                fullFiller .replace("%FACEBOOK_LINK%", settingsMap->value(k));
            if(k == "lastfm_link")
                fullFiller .replace("%LASTFM_LINK%", settingsMap->value(k));
            if(k == "youtube_link")
                fullFiller .replace("%YOUTUBE_LINK%", settingsMap->value(k));
            if(k == "store_link")
                fullFiller .replace("%STORE_LINK%", settingsMap->value(k));

            if(k == "prelisten_object")
                fullFiller .replace("%PRELISTEN_OBJECT%", settingsMap->value(k));

            if(k == "text_color")
            {
                shortFiller.replace("%TEXT_COLOR%", settingsMap->value(k));
                fullFiller .replace("%TEXT_COLOR%", settingsMap->value(k));
            }
            if(k == "link_color")
                fullFiller .replace("%LINK_COLOR%", settingsMap->value(k));
            if(k == "backgrnd_color")
                fullFiller .replace("%BACKGRND_COLOR%", settingsMap->value(k));
            if(k == "link_bcgrd_color")
                fullFiller .replace("%LINK_BCGRD_COLOR%", settingsMap->value(k));

            if(k == "facebook_icon")
                fullFiller .replace("%FACEBOOK_ICON%", settingsMap->value(k));
            if(k == "lastfm_icon")
                fullFiller .replace("%LASTFM_ICON%", settingsMap->value(k));
            if(k == "youtube_icon")
                fullFiller .replace("%YOUTUBE_ICON%", settingsMap->value(k));
            if(k == "store_icon")
                fullFiller .replace("%STORE_ICON%", settingsMap->value(k));

            if(k.contains("genre"))
            {
                if(k[k.length() - 1] != '1')
                {
                    if(genreString == "%GENRES%")
                        genreString = settingsMap->value(k);
                    else
                        genreString += " / " + settingsMap->value(k);
                }
                else
                    genreString = settingsMap->value(k);
            }

            if(k.contains("format"))
            {
                if(k == "format1")
                {
                    if(settingsMap->value(k) != "-")
                    {
                        shortFormat = "FLAC";
                        fullFormat = settingsMap->value(k);
                    }
                }
                else
                {
                    if(settingsMap->value(k) != "-")
                    {
                        if(settingsMap->value("format1") != "-")
                        {
                            shortFormat += " / ";
                            shortFormat += (k == "format2") ? "MP3" : "M4A";
                        }

                        if(fullFormat == "%FORMAT%")
                            fullFormat = settingsMap->value(k);
                        else
                            fullFormat += " / " + settingsMap->value(k);
                    }
                }
            }

            if(k.contains("dl_link"))
            {
                QString temp = linkTemplate, site;
                temp.replace("%LINK%", settingsMap->value(k));
                temp.replace("%LINK_COLOR%", settingsMap->value("link_color"));

                site = ui->dl_forlinkComboBox1->parent()->findChild<QComboBox*>("dl_forlinkComboBox" + k[k.length() - 1])->currentText();
                if(settingsMap->value(k).contains("zippyshare"))
                    site += " (zippyshare)";
                if(settingsMap->value(k).contains("rusfolder"))
                    site += " (rusfolder)";
                if(settingsMap->value(k).contains("solidfiles"))
                    site += " (solidfiles)";
                if(settingsMap->value(k).contains("files.fm"))
                    site += " (files.fm)";
                if(settingsMap->value(k).contains("mail.ru"))
                    site += " (mail)";
                if(settingsMap->value(k).contains("yadi.sk"))
                    site += " (yandex)";
                temp.replace("%SITE%", site);

                if(k[k.length() - 1] != '1')
                {
                    if(downloadLinks == "%DOWNLOAD_LINKS%")
                        downloadLinks = temp;
                    else
                        downloadLinks += " - " + temp;
                }
                else
                    downloadLinks = temp;
            }
            if(k.contains("icon_"))
                updateIcons();
        }
    }

    shortFiller.replace("%GENRES%", genreString);
    fullFiller .replace("%GENRES%", genreString);

    shortFiller.replace("%SHORT_FORMAT%", shortFormat);
    fullFiller .replace("%FORMAT%",       fullFormat);

    fullFiller .replace("%DOWNLOAD_LINKS%", downloadLinks);

    ui->titleLine    ->setText     (titleFiller);
    ui->shortCodeText->setPlainText(shortFiller);
    ui->fullCodeText ->setPlainText(fullFiller );

    postProcessing();
}

void designer::postProcessing()
{
    QString shortCode = ui->shortCodeText->toPlainText();
    QString fullCode  = ui->fullCodeText ->toPlainText();

    foreach(QString k, shortCode.split("\n"))
        if(k.contains(QRegExp("(SHORT|LISTENERS)")))
            shortCode.remove(k + "\n");

    foreach(QString k, fullCode.split(" "))
        if(k.contains("LINK%"))
            fullCode. remove(k);

    ui->shortCodeText->setPlainText(shortCode);
    ui->fullCodeText ->setPlainText(fullCode );
}

void designer::setDefaultSettings()
{
    ui->textColorLine     ->setText("#64B5F6");
    ui->linkColorLine     ->setText("#FFFFFF");
    ui->backgrndColorLine ->setText("#000000");
    ui->linkBcgrdColorLine->setText("#2196F3");

    ui->facebookIconLine->setText("http://i70.fastpic.ru/big/2015/0917/70/c972dc4adfbf805c13f522c437883a70.png");
    ui->lastfmIconLine  ->setText("http://i70.fastpic.ru/big/2015/0917/24/289aae4964f0a937ae117d768a0d7d24.png");
    ui->youtubeIconLine ->setText("http://i70.fastpic.ru/big/2015/0917/78/a9fd6652f40dd02d1c92e4e502446f78.png");
    ui->storeIconLine   ->setText("http://i70.fastpic.ru/big/2015/0917/6f/76eb9acc3dceb4e5fa72093c44c2c56f.png");

    ui->iconBackColorLine->setText("#2196F3");
    ui->iconTextColorLine->setText("#FFFFFF");
    ui->iconRadiusSpinbox->setValue(10);
    ui->iconSizeBox      ->setValue(50);
}
