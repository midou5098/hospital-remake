#ifndef SMTP_H
#define SMTP_H
#include "libraries.h"

class smtp{
public:
    QSslSocket socket;
    const QString password="uzxciblcvimzemkr";
    const QString user="midouamdouni4@gmail.com";
    bool send (const QString command);
    bool connect(const QString& host,int port);
    bool auth(const QString* user,const QString* password);
    bool send(const QString* to,const QString* obj,const QString* body);
    void disconnect();
    QString sendcommand(QSslSocket* socket,   const QString& cmd);
};

#endif // SMTP_H
