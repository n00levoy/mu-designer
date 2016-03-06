#include "dtemplate.h"

dTemplate::dTemplate()
{
    titleTemplate = "%ARTIST_NAME% - %ALBUM% (%YEAR%)";

    shortTemplate = "[center][img]%SMALL_COVER%[/img]\n"
                    "[b]Стиль: [color=%TEXT_COLOR%]%GENRES%[/color]\n"
                    "Формат: [color=%TEXT_COLOR%]%SHORT_FORMAT%[/color]\n"
                    "Треклист:[/b]\n"
                    "%TRACKLIST%\n"
                    "\n"
                    "[b][color=#999999]%LISTENERS% слушателей на Last.fm[/color][/b]\n"
                    "[/center]";

    fullTemplate  = "<div style=\"background-color: %BACKGRND_COLOR%; text-align: center;\">\n"
                    "[URL=%FULLSIZE_COVER%][IMG]%BIG_COVER%[/IMG][/URL]\n"
                    " \n"
                    "[url=%FACEBOOK_LINK%][img]%FACEBOOK_ICON%[/img][/url] "
                    "[url=%LASTFM_LINK%][img]%LASTFM_ICON%[/img][/url] "
                    "[url=%YOUTUBE_LINK%][img]%YOUTUBE_ICON%[/img][/url] "
                    "[url=%STORE_LINK%][img]%STORE_ICON%[/img][/url] \n"
                    " \n"
                    "[b][color=%TEXT_COLOR%]Исполнитель:[/color][/b] [b]%ARTIST_NAME%[/b]\n"
                    "[b][color=%TEXT_COLOR%]Альбом:[/color][/b] [b]%ALBUM%[/b]\n"
                    "[b][color=%TEXT_COLOR%]Год:[/color][/b] [b]%YEAR%[/b]\n"
                    "[b][color=%TEXT_COLOR%]Страна:[/color][/b] [b]%COUNTRY%[/b]\n"
                    "[b][color=%TEXT_COLOR%]Стиль:[/color][/b] [b]%GENRES%[/b]\n"
                    "[b][color=%TEXT_COLOR%]Продолжительность:[/color][/b] [b]%FULL_LENGTH%[/b]\n"
                    "[b][color=%TEXT_COLOR%]Формат:[/color][/b] [b]%FORMAT%[/b]\n"
                    " \n"
                    "[b][color=%TEXT_COLOR%]Треклист:[/color][/b]\n"
                    "%TRACKLIST%\n"
                    " \n"
                    "<div style=\"background-color: %LINK_BCGRD_COLOR%; text-shadow: 1px 1px 1px black;\">\n"
                    "[size=2][b]%DOWNLOAD_LINKS%[/b][/size]\n"
                    "\n"
                    "</div>%PRELISTEN_OBJECT%</div>";

    linkTemplate = "[url=%LINK%][color=%LINK_COLOR%]%FORMAT% (%SITE%)[/color][/url]";

    QFile hosts("hostings.txt");
    if(hosts.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&hosts);
        QStringList text = stream.readAll().split(QRegExp(";\r\n"));
        foreach(QString k, text)
        {
            QStringList linkCont = k.split(" - ");
            siteNames.insert(linkCont.first().remove("\""), linkCont.last().remove("\""));
        }
        hosts.close();
    }
    else
    {
        siteNames.insert("zippyshare", "Zippyshare");
        siteNames.insert("yadi.sk",    "Yandex"    );
        siteNames.insert("solidfiles", "Solidfiles");
        siteNames.insert("rusfolder",  "Rusfolder" );
    }

    startParsing();
}

QString dTemplate::createDownloadLink(QString link, QString format, QString link_color)
{
    QString templ;
    if(linkTemplate != "")
         templ = linkTemplate;
    else
        return 0;

    QString site;
    foreach(QString k, siteNames.keys())
        if(link.contains(k))
            site = siteNames[k];

    return templ.replace("%LINK%", link).replace("%LINK_COLOR%", link_color).replace("%FORMAT%", format).replace("%SITE%", site);
}

void dTemplate::loadTemplate()
{
    QString fileName = QFileDialog::getOpenFileName(0, "Выбрать файл шаблона", "", "*.xml");
    if(fileName.isEmpty())
        return;

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly))
        return;

    QXmlStreamReader xmlData(file.readAll());
    file.close();

    do
    {
        xmlData.readNext();
        if(xmlData.name() == "full_template")
        {
            xmlData.readNext();
            fullTemplate = xmlData.text().toString();
            xmlData.readNext();
        }
        if(xmlData.name() == "short_template")
        {
            xmlData.readNext();
            shortTemplate = xmlData.text().toString();
            xmlData.readNext();
        }
        if(xmlData.name() == "title_template")
        {
            xmlData.readNext();
            titleTemplate = xmlData.text().toString();
            xmlData.readNext();
        }
        if(xmlData.name() == "link_template")
        {
            xmlData.readNext();
            linkTemplate = xmlData.text().toString();
            xmlData.readNext();
        }
    }
    while(!xmlData.atEnd());

    startParsing();
}

void dTemplate::parseTemplate(QString templateToParse, QSet<QString> packToSave)
{
    QStringList lst = templateToParse.split("%");
    int i = 0;
    foreach(QString k, lst)
    {
        if(i % 2)
            packToSave << k;
        i++;
    }
}

void dTemplate::startParsing()
{
    parseTemplate(titleTemplate, titlePack);
    parseTemplate(shortTemplate, shortPack);
    parseTemplate(fullTemplate,  fullPack);
}

