#include "smtp.h"
#include "libraries.h"

QString smtp::sendcommand(QSslSocket* socket,   const QString& cmd){
    socket->write(cmd.toUtf8() + "\r\n");
    socket->waitForBytesWritten();
    socket->waitForReadyRead(5000);
    return QString::fromUtf8(socket->readAll());

}
int smtp::resp(QString response){
    return response.left(3).toInt();
}
bool smtp::connect(const QString& host,int port){
    socket.setProtocol(QSsl::TlsV1_2OrLater);
    socket.connectToHostEncrypted(host,port);
    if(!socket.waitForEncrypted(3000)){
        return false;
    }

    QString res=sendcommand(&socket,"EHLO localhost");
    if(resp(res)!=250){
        return false;
    }else{
        return true;
    }
}








bool smtp::auth(const QString* user,const QString* password){
    QString res=sendcommand(&socket,"AUTH LOGIN");
    if(resp(res)!=334){
        return false;

    }
    QString eu=user->toUtf8().toBase64();
    QString res1=sendcommand(&socket,eu);
    if(resp(res1)!=334){
        return false;
    }
}





















bool send(const QString* to,const QString* obj,const QString* body);
void disconnect();