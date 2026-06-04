#include "smtp.h"
#include "libraries.h"


bool smtp::connect(const QString& host,int port){
    socket.setProtocol(QSsl::TlsV1_2OrLater);
    socket.connectToHostEncrypted(host,port);
    if(!socket.waitForEncrypted(3000)){
        return false;
    }
    socket.waitForReadyRead(3000){
        sendcommand("EHLO localhost");
    }






}
bool auth(const QString* user,const QString* password);
bool send(const QString* to,const QString* obj,const QString* body);
void disconnect();