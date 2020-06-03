#include "downloader.h"

#include <QNetworkAccessManager>
#include <QString>
#include <QtAndroid>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QUrl>

Downloader::Downloader(QObject *parent) : QObject(parent)
{
    qDebug() << "SSL_VERSION: " << QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "SSL_STATUS: " << QSslSocket::supportsSsl();
    getNetworkAccess();
    // Инициализирую менеджер ...
    manager = new QNetworkAccessManager();
    // ... и подключаю сигнал о завершении получения данных к обработчику полученного ответа
    connect(manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);
    //connect(manager, &QNetworkAccessManager::finished, manager, &QNetworkAccessManager::deleteLater);//во избежание утечки памяти
}

void Downloader::getData()
{
    QUrl url("https://reqres.in/api/users?page=2"); // URL по которому буду получать данные
    QNetworkRequest request;                        // Объект запроса
    request.setUrl(url);                            // Устанавлвиваю URL в запрос
    manager->get(request);                          // Выполняю запрос
}
void Downloader::onResult(QNetworkReply *reply)
{
    // Если в процесе получения данных произошла ошибка
    if(reply->error()){
        // Сообщаю об этом и показываю информацию об ошибках
        qDebug() << "onResult(): "+reply->errorString();
    }
    else
    {
        arr = reply->readAll();
        setter2 = new QSettings("dat", "response");
        setter2->beginGroup("test");
        setter2->setValue("data1", arr);
        setter2->endGroup();

        QJsonDocument doc = QJsonDocument::fromJson(arr);
        QJsonObject root = doc.object();
        QJsonValue jv = root.value("data");
        setter = new QSettings("dat", "json");
        setter->beginGroup("test");
        qDebug() << "1";
        if(jv.isArray()){
            qDebug() << "2";
            // забираю массив из данного свойства
            QJsonArray ja = jv.toArray();
            setter->setValue("COUNT", ja.count());
            // Перебирая все элементы массива ...
            for(int i = 0; i < ja.count(); i++){
                qDebug() << "i = " << i;
                QJsonObject subtree = ja.at(i).toObject();
                // Забираю значения свойств имени и фамилии
                for(int j = 0; j < 3; j++){
                    qDebug() << "j = " << j;
                    if(j == 0) setter->setValue(QString("NAME1_%1").arg(i), subtree.value("first_name").toString());
                    if(j == 1) setter->setValue(QString("NAME2_%1").arg(i), subtree.value("last_name").toString());
                    if(j == 2) setter->setValue(QString("MAIL_%1").arg(i), subtree.value("email").toString());
                    if(j == 2) setter->setValue(QString("AVATAR_%1").arg(i), subtree.value("avatar").toString());
                }
            }
            qDebug() << arr;
        }
        setter->endGroup();
        qDebug() << "onResult(): Downloading is completed";
        emit onReady(); // Посылаю сигнал о завершении получения файла
    }
}
QString Downloader::getResponse(){
    setter = new QSettings("dat", "response");
    setter->beginGroup("test");
    str = setter->value("data1", "ERROR_DATA").toString();
    setter->endGroup();

    return str;
}
int Downloader::getCount(){
    setter = new QSettings("dat", "json");
    setter->beginGroup("test");
    tmpint = setter->value("COUNT", 0).toInt(&ok);
    setter->endGroup();

    return tmpint;
}
QString Downloader::getName1(int a){
    setter = new QSettings("dat", "json");
    setter->beginGroup("test");
    str = setter->value(QString("NAME1_%1").arg(a), 0).toString();
    setter->endGroup();

    return str;
}
QString Downloader::getName2(int a){
    setter = new QSettings("dat", "json");
    setter->beginGroup("test");
    str = setter->value(QString("NAME2_%1").arg(a), 0).toString();
    setter->endGroup();

    return str;
}
QString Downloader::getMail(int a){
    setter = new QSettings("dat", "json");
    setter->beginGroup("test");
    str = setter->value(QString("MAIL_%1").arg(a), 0).toString();
    setter->endGroup();

    return str;
}
QString Downloader::getAvatar(int a){
    setter = new QSettings("dat", "json");
    setter->beginGroup("test");
    str = setter->value(QString("AVATAR_%1").arg(a), 0).toString();
    setter->endGroup();

    return str;
}
bool Downloader::getNetworkAccess()
{
    qDebug() << "getNetworkAccess";
    #ifdef Q_OS_ANDROID
    QtAndroid::PermissionResult r = QtAndroid::checkPermission("android.permission.ACCESS_NETWORK_STATE");//создаю переменную хранящую название запроса
    qDebug() << "requestNetworkPermissions";
    if(r == QtAndroid::PermissionResult::Denied) {              //если состояние разрешения нудовлетворительное
        QtAndroid::requestPermissionsSync(QStringList() << "android.permission.ACCESS_NETWORK_STATE" );    //запрашиваю разрешение(далее действия юзера)
        r = QtAndroid::checkPermission("android.permission.ACCESS_NETWORK_STATE");     //проверяю состояние разрешения(после действий юзера)
        if(r == QtAndroid::PermissionResult::Denied) {              //если оно неудовлетворительное...
            qDebug() << "requestNetworkPermission: DENIED";
            return false;
        }
    }
    #endif
    qDebug() << "requestNetworkPermission: ALLOWED";
    return true;
}
