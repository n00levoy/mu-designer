#include "designer.h"
#include "ui_designer.h"
#include "textedit.h"

void designer::addDownloadLink()
{
    int num = ui->dl_linksLayout->rowCount();
    QString strNum;
    strNum.setNum(num);

    QLineEdit* lineEdit = new QLineEdit;
    lineEdit->setObjectName("dl_linkLine" + strNum);

    QComboBox* comboBox = new QComboBox;
    comboBox->setObjectName("dl_forlinkComboBox" + strNum);

    QStringList list;
    list << "FLAC" << "MP3" << "M4A";
    comboBox->addItems   (list);
    comboBox->setEditable(true);

    ui->dl_linksLayout->removeWidget(ui->addDl_linkButton);
    ui->dl_linksLayout->addWidget(new QLabel("Ссылка " + strNum + ":"), num - 1, 0);
    ui->dl_linksLayout->addWidget(lineEdit, num - 1, 1);
    ui->dl_linksLayout->addWidget(comboBox, num - 1, 2);
    ui->dl_linksLayout->addWidget(ui->addDl_linkButton, num, 0, 1, 3);

    connect(lineEdit, SIGNAL(textChanged(QString)),     SLOT(setSetting(QString)));
    connect(comboBox, SIGNAL(activated(QString)),       SLOT(setSetting(QString)));
    connect(comboBox, SIGNAL(editTextChanged(QString)), SLOT(setSetting(QString)));
}

void designer::addGenre()
{
    int num = ui->genreLayout->count();
    QString strNum_1;
    strNum_1.setNum(num - 2);

    QLineEdit* lineEdit = new QLineEdit;
    lineEdit->setObjectName("genreLine" + strNum_1);

    ui->genreLayout->removeWidget(ui->addGenreButton);
    ui->genreLayout->removeWidget(ui->deleteGenreButton);
    ui->genreLayout->insertWidget(num - 2, lineEdit);
    ui->genreLayout->insertWidget(num - 1, ui->addGenreButton);
    ui->genreLayout->insertWidget(num, ui->deleteGenreButton);

    connect(lineEdit, SIGNAL(textChanged(QString)), SLOT(setSetting(QString)));
}

void designer::deleteGenre()
{
    int num = ui->genreLayout->count();
    if(num > 3)
    {
        QString strNum_1;
        strNum_1.setNum(num - 3);

        QLineEdit* child = ui->albumTab->findChild<QLineEdit*>("genreLine" + strNum_1);
        ui->genreLayout->removeWidget(ui->addGenreButton);
        ui->genreLayout->removeWidget(ui->deleteGenreButton);
        ui->genreLayout->removeWidget(child);
        ui->genreLayout->insertWidget(num - 2, ui->addGenreButton);
        ui->genreLayout->insertWidget(num - 1, ui->deleteGenreButton);

        child->setText("");

        disconnect(child, SIGNAL(textChanged(QString)), this, SLOT(setSetting(QString)));
        delete child;
    }
    else
        QMessageBox::critical(0, "НЕЛЬЗЯ!", "Нет полей для удаления", "k");
}

void designer::guiConnections()
{
    connect(ui->artistLine,     SIGNAL(textChanged(QString)),  SLOT(setSetting(QString)));
    connect(ui->albumLine,      SIGNAL(textChanged(QString)),  SLOT(setSetting(QString)));
    connect(ui->yearSpinBox,    SIGNAL(valueChanged(QString)), SLOT(setSetting(QString)));
    connect(ui->tracklistText,  SIGNAL(textChanged(QString)),  SLOT(setSetting(QString)));
    connect(ui->countryLine,    SIGNAL(textChanged(QString)),  SLOT(setSetting(QString)));
    connect(ui->listenersLine,  SIGNAL(textChanged(QString)),  SLOT(setSetting(QString)));
    connect(ui->lengthLine,     SIGNAL(textChanged(QString)),  SLOT(setSetting(QString)));

    connect(ui->modCheckBox,       SIGNAL(clicked(bool)),            SLOT(updateContentSlot()));
    connect(ui->modComboBox,       SIGNAL(activated(int)),           SLOT(updateContentSlot()));
    connect(ui->modComboBox,       SIGNAL(editTextChanged(QString)), SLOT(updateContentSlot()));
    connect(ui->listenersCheckBox, SIGNAL(clicked(bool)),            SLOT(updateContentSlot()));

    connect(ui->smallCoverLine,    SIGNAL(textChanged(QString)), SLOT(setSetting(QString)));
    connect(ui->bigCoverLine,      SIGNAL(textChanged(QString)), SLOT(setSetting(QString)));
    connect(ui->fullsizeCoverLine, SIGNAL(textChanged(QString)), SLOT(setSetting(QString)));

    connect(ui->facebookLinkLine, SIGNAL(textChanged(QString)), SLOT(setSetting(QString)));
    connect(ui->lastfmLinkLine,   SIGNAL(textChanged(QString)), SLOT(setSetting(QString)));
    connect(ui->youtubeLinkLine,  SIGNAL(textChanged(QString)), SLOT(setSetting(QString)));
    connect(ui->storeLinkLine,    SIGNAL(textChanged(QString)), SLOT(setSetting(QString)));

    connect(ui->prelistenObjectText, SIGNAL(textChanged(QString)), SLOT(setSetting(QString)));

    connect(ui->textColorLine,      SIGNAL(textChanged(QString)), SLOT(setSetting(QString)));
    connect(ui->linkColorLine,      SIGNAL(textChanged(QString)), SLOT(setSetting(QString)));
    connect(ui->backgrndColorLine,  SIGNAL(textChanged(QString)), SLOT(setSetting(QString)));
    connect(ui->linkBcgrdColorLine, SIGNAL(textChanged(QString)), SLOT(setSetting(QString)));

    connect(ui->facebookIconLine, SIGNAL(textChanged(QString)), SLOT(setSetting(QString)));
    connect(ui->lastfmIconLine,   SIGNAL(textChanged(QString)), SLOT(setSetting(QString)));
    connect(ui->youtubeIconLine,  SIGNAL(textChanged(QString)), SLOT(setSetting(QString)));
    connect(ui->storeIconLine,    SIGNAL(textChanged(QString)), SLOT(setSetting(QString)));

    connect(ui->iconBackColorLine,  SIGNAL(textChanged(QString)),  SLOT(setSetting(QString)));
    connect(ui->iconTextColorLine,  SIGNAL(textChanged(QString)),  SLOT(setSetting(QString)));
    connect(ui->iconShadowCheckBox, SIGNAL(toggled(bool)),         SLOT(updateIcons()));
    connect(ui->iconBackTypeBox,    SIGNAL(activated(QString)),    SLOT(setSetting(QString)));
    connect(ui->iconRadiusSpinbox,  SIGNAL(valueChanged(QString)), SLOT(setSetting(QString)));
    connect(ui->iconSizeBox,        SIGNAL(valueChanged(QString)), SLOT(setSetting(QString)));
    connect(ui->iconPicSizeBox,     SIGNAL(valueChanged(QString)), SLOT(setSetting(QString)));
    connect(ui->uploadIconsButton,  SIGNAL(clicked(bool)),         SLOT(uploadIcons()));

    connect(ui->formatComboBox1, SIGNAL(activated(QString)),   SLOT(setSetting(QString)));
    connect(ui->formatComboBox2, SIGNAL(activated(QString)),   SLOT(setSetting(QString)));
    connect(ui->formatComboBox3, SIGNAL(activated(QString)),   SLOT(setSetting(QString)));
    connect(ui->genreLine1,      SIGNAL(textChanged(QString)), SLOT(setSetting(QString)));

    connect(ui->dl_linkLine1,        SIGNAL(textChanged(QString)),     SLOT(setSetting(QString)));
    connect(ui->dl_forlinkComboBox1, SIGNAL(activated(QString)),       SLOT(setSetting(QString)));
    connect(ui->dl_forlinkComboBox1, SIGNAL(editTextChanged(QString)), SLOT(setSetting(QString)));
    connect(ui->dl_linkLine2,        SIGNAL(textChanged(QString)),     SLOT(setSetting(QString)));
    connect(ui->dl_forlinkComboBox2, SIGNAL(activated(QString)),       SLOT(setSetting(QString)));
    connect(ui->dl_forlinkComboBox2, SIGNAL(editTextChanged(QString)), SLOT(setSetting(QString)));

    connect(ui->listenersCheckBox, SIGNAL(clicked(bool)), ui->listenersLine, SLOT(setEnabled(bool)));

    connect(ui->addDl_linkButton,   SIGNAL(clicked(bool)), SLOT(addDownloadLink()));
    connect(ui->addGenreButton,     SIGNAL(clicked(bool)), SLOT(addGenre()));
    connect(ui->deleteGenreButton,  SIGNAL(clicked(bool)), SLOT(deleteGenre()));
    connect(ui->uploadCoversButton, SIGNAL(clicked(bool)), SLOT(uploadCoversDialog()));
    connect(ui->itunesSearchButton, SIGNAL(clicked(bool)), SLOT(getItunesLinks()));

    connect(ui->openFiles,    SIGNAL(triggered(bool)),       SLOT(getFilesFromList()));
    connect(ui->openFolder,   SIGNAL(triggered(bool)),       SLOT(getFilesFromFolder()));
    connect(ui->loadTemplate, SIGNAL(triggered(bool)),       SLOT(loadTemplate()));
    connect(ui->exitAction,   SIGNAL(triggered(bool)), qApp, SLOT(quit()));

    ui->textColorButton->     setLineForRead(ui->textColorLine);
    ui->linkColorButton->     setLineForRead(ui->linkColorLine);
    ui->backgrndColorButton-> setLineForRead(ui->backgrndColorLine);
    ui->linkBcgrdColorButton->setLineForRead(ui->linkBcgrdColorLine);

    ui->iconBackColorButton->setLineForRead(ui->iconBackColorLine);
    ui->iconTextColorButton->setLineForRead(ui->iconTextColorLine);
}
