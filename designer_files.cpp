#include "designer.h"
#include "ui_designer.h"

#include <fileref.h>
#include <tag.h>

void designer::getFilesFromList()
{
    QStringList files = QFileDialog::getOpenFileNames(0, "Выбрать файлы", "", "*.mp3 *.flac *.m4a");
    getFiles(files);
}

void designer::getFilesFromFolder()
{
    QString str = QFileDialog::getExistingDirectory(0, "Выбрать папку");
    if(str.isEmpty())
        return;

    QStringList filter, fileList;
    filter << "*.mp3" << "*.flac" << "*.m4a";
    QDirIterator it(str, filter, QDir::Files, QDirIterator::Subdirectories);
    while(it.hasNext())
        fileList << it.next();
    if(!fileList.isEmpty())
        getFiles(fileList);
}

void designer::getFiles(QStringList files)
{
    if (files.empty())
        return;

    QString filenames = "";
    int duration = 0;
    foreach(QString filepath, files)
    {
        TagLib::FileRef f(reinterpret_cast<const wchar_t*>(filepath.constData()));
        TagLib::AudioProperties* props = f.audioProperties();
        duration += props->lengthInSeconds();

        QString filename = filepath.split("/").last();
        filename.remove(QRegExp("\\.(mp3|flac|m4a)"));
        filenames += filename + "\n";
    }
    ui->lengthLine->setText(QTime(duration / 3600, (duration % 3600) / 60, ((duration % 3600) % 60)).toString("hh:mm:ss"));
    filenames.remove(QRegExp("\n$"));
    ui->tracklistText->setPlainText(filenames);

    QString tagfile = files.first();
    TagLib::FileRef f(reinterpret_cast<const wchar_t*>(tagfile.constData()));
    QString artist = f.tag()->artist().toCString(true);
    QString album  = f.tag()->album() .toCString(true);
    uint    year   = f.tag()->year();
    QString genre  = f.tag()->genre() .toCString(true);

    ui->artistLine ->setText(artist);
    ui->albumLine  ->setText(album);
    ui->yearSpinBox->setValue(year);

    QStringList genres = genre.split(" / ");
    if(genres.count() > 1)
    {
        int num = genres.count();
        for (int i = 1; i <= num; i++)
        {
            addGenre();
            ui->genreLayout->parent()->findChild<QLineEdit*>("genreLine" + QString::number(i))->setText(genres[i - 1]);
        }
    }
    else
        ui->genreLine1 ->setText(genre);
}
