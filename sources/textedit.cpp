#include "textedit.h"

TextEdit::TextEdit(QWidget *parent) : QPlainTextEdit(parent)
{
    connect(this, SIGNAL(textChanged()), SLOT(changingText()));
}
