#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QPlainTextEdit>

class TextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    TextEdit(QWidget *parent = 0);

public slots:
    void changingText() { emit textChanged(toPlainText()); }

signals:
    void textChanged(QString);
};

#endif // TEXTEDIT_H
