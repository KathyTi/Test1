#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QSettings>
#include <QNetworkReply>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = nullptr);
    QString str;
    QSettings *setter;
    QSettings *setter2;
    bool ok;
    int tmpint;
    QByteArray arr;
signals:
    void onReady();
    void sigSendPath(QString path);
    //void strChanged();
public slots:
    //void openGallery();
    void getData();     // Метод инициализации запроса на получение данных
    void onResult(QNetworkReply *reply);    // Слот обработки ответа о полученных данных
    QString getResponse();
    bool getNetworkAccess();
    int getCount();
    QString getName1(int a);
    QString getName2(int a);
    QString getMail(int a);
    QString getAvatar(int a);
    //void callJava();
    //Q_INVOKABLE
   // void setStr(QString s);
private:
    QNetworkAccessManager *manager; // менеджер сетевого доступа
};

#endif // DOWNLOADER_H
