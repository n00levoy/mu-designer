#include "coloredbutton.h"

coloredButton::coloredButton(QWidget* parent) : QPushButton(parent)
{
    connect(this, SIGNAL(clicked(bool)), SLOT(chooseColor()));
}

void coloredButton::setLineForRead(QLineEdit* line)
{
    buttonBuddy = line;
    connect(line, SIGNAL(textChanged(QString)), SLOT(changeColor(QString)));
}

void coloredButton::changeColor(QString col)
{
    setStyleSheet("*{background-color: " + col + ";}");
}

void coloredButton::chooseColor()
{
    QStringList customCols;
    customCols << "#000000" << "#ffffff" << "#f44336" << "#ff8a80" << "#e91e63" << "#ff80ab";
    customCols << "#9c27b0" << "#ea80fc" << "#673ab7" << "#b388ff" << "#3f51b5" << "#8c9eff";
    customCols << "#2196f3" << "#82b1ff" << "#0091ea" << "#03a9f4" << "#0097a7" << "#00b8d4";
    customCols << "#009688" << "#00bfa5" << "#43a047" << "#00e676" << "#689f38" << "#76ff03";
    customCols << "#827717" << "#c6ff00" << "#f57f17" << "#ffea00" << "#ff6f00" << "#ffc400";
    customCols << "#ef6c00" << "#ff9100" << "#ff5722" << "#ff6e40" << "#795548" << "#bcaaa4";
    customCols << "#616161" << "#bdbdbd" << "#607d8b" << "#b0bec5";

    int i = 0;
    foreach(QString k, customCols)
    {
        QColorDialog::setStandardColor(i, QColor(k));
        i++;
    }

    QString color = QColorDialog::getColor(buttonBuddy->text(), 0, "Выбрать цвет").name();
    changeColor(color);
    buttonBuddy->setText(color);
}
