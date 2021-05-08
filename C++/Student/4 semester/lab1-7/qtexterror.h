#ifndef QTEXTERROR_H
#define QTEXTERROR_H

#include <QTextBrowser>

class QTextError : public QTextBrowser
{
    Q_OBJECT
public:
    explicit QTextError(QWidget *parent = nullptr);
signals:
    public slots:
        void appendRed(const QString & text);
};

#endif // QTEXTERROR_H
