#ifndef DTEMPLATE_H
#define DTEMPLATE_H

#include <QtWidgets>

class dTemplate : public QObject
{
public:
    dTemplate();

    QString createDownloadLink(QString link, QString format, QString link_color = "%LINK_COLOR%");

private:
    QString linkTemplate;
    QString shortTemplate;
    QString fullTemplate;
    QString titleTemplate;

    QMap<QString, QString> siteNames;

    QString currentTitle;
    QString currentShort;
    QString currentFull;

    QSet<QString> titlePack;
    QSet<QString> shortPack;
    QSet<QString> fullPack;

    void parseTemplate(QString templateToParse, QSet<QString> packToSave);
    void startParsing ();

private slots:
    void loadTemplate();

signals:

};

#endif // DTEMPLATE_H
