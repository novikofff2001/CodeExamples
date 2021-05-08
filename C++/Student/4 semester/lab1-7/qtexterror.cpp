#include "qtexterror.h"

QTextError::QTextError(QWidget *parent) : QTextBrowser(parent)
{

}

void QTextError::appendRed(const QString & text)
{
    QColor c = textColor();
    setTextColor(QColor("red"));
    append(text);
    setTextColor(c);
}
