#ifndef CHAT_QT_WSCLIENT_H
#define CHAT_QT_WSCLIENT_H

#include <QObject>
#include <QUrl>
#include <QWebSocket>

#include <spdlog/spdlog.h>

class WsClient : public QObject
{
    Q_OBJECT
  public:
    explicit WsClient(QObject *parent);
    void open(const QUrl &url, const QString &name);
    void send(const QString &message);

  signals:
    void closed();
    void error(QAbstractSocket::SocketError error);
    void messageReceived(const QString message);

  private slots:
    void onConnected();
    void onMessageReceived(QString message);

  private:
    QWebSocket m_webSocket;
};

#endif // CHAT_QT_WSCLIENT_H
