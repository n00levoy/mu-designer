#ifndef COLOREDBUTTON_H
#define COLOREDBUTTON_H

#include <QtWidgets>

class coloredButton : public QPushButton
{
    Q_OBJECT

public:
    coloredButton(QWidget* parent = 0);

    void setLineForRead(QLineEdit* );

private:
    QLineEdit* buttonBuddy;

public slots:
    void changeColor(QString);
    void chooseColor();
};

#endif // COLOREDBUTTON_H
