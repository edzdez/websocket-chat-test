#include "WsClient.h"

WsClient::WsClient(QObject *parent)
    : QObject(parent)
{
    connect(&m_webSocket, &QWebSocket::connected, this, &WsClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &WsClient::closed);
    connect(&m_webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &WsClient::error);
}

void WsClient::open(const QUrl &url, const QString &name)
{
    spdlog::info("attempting to connect to {}", url.toString().toStdString());
    QNetworkRequest request(url);
    request.setRawHeader("name", name.toUtf8());
    m_webSocket.open(request);
}

void WsClient::send(const QString &message)
{
    spdlog::info("sending message: {}", message.toStdString());
    m_webSocket.sendTextMessage(message);
}

void WsClient::onConnected()
{
    spdlog::info("websocket connected");
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &WsClient::onMessageReceived);
}

void WsClient::onMessageReceived(QString message)
{
    spdlog::info("received message: {}", message.toStdString());
    emit messageReceived(message);
}

