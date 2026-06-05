#include "smtp.h"
#include "libraries.h"
#include <QtNetwork/QSslSocket>
#include <QByteArray>
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
    socket.waitForReadyRead(3000);
    socket.readAll();

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
    QString ep=password->toUtf8().toBase64();
    QString res2=sendcommand(&socket,ep);
    if(resp(res2)!=235){
        return false;
    }
    return true;
}






bool smtp::send(const QString& to,const QString& obj,const QString& body){
    QString res=sendcommand(&socket,"MAIL FROM:<"+user+">");
    if(resp(res)!=250){
        return false;
    }
    QString res1=sendcommand(&socket,"RCPT To:<" + to+">");
    if(resp(res1)!=250){
        return false;
    }
    QString res3=sendcommand(&socket,"DATA");
    if(resp(res3)!=354){
        return false;
    }
    QString message;
    message += "From: "+ user+ "\r\n";
    message += "To: "+to      + "\r\n";
    message += "Subject: " + obj + "\r\n";
    message += "MIME-Version: 1.0\r\n";
    message += "Content-Type: text/plain; charset=UTF-8\r\n";
    message += "\r\n";
    message += body + "\r\n";
    message += ".\r\n";
    socket.write(message.toUtf8());
    socket.waitForBytesWritten();
    socket.waitForReadyRead(3000);
    QString res2=QString::fromUtf8(socket.readAll());
    if(resp(res2)!=250){
        return false;
    }
    return true;

}

















void disconnect();