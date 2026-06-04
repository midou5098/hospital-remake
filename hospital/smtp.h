#ifndef SMTP_H
#define SMTP_H
#include "libraries.h"
#include <QtNetwork/QSslSocket>
#include <QByteArray>
class smtp{
public:
    QSslSocket socket;
    const QString password="uzxciblcvimzemkr";
    const QString user="midouamdouni4@gmail.com";
    bool connect(const QString& host,int port);
    bool auth(const QString* user,const QString* password);
    bool send(const QString& to,const QString& obj,const QString& body);
    void disconnect();
    QString sendcommand(QSslSocket* socket,   const QString& cmd);
    int resp(QString response);
};

#endif // SMTP_H
