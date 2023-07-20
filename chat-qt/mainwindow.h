#ifndef CHAT_QT_MAINWINDOW_H
#define CHAT_QT_MAINWINDOW_H

#include <QWidget>

#include <spdlog/spdlog.h>

#include "WsClient.h"
#include "connectdialog.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

  private:
    void attemptConnection(const QUrl &url, const QString &name);

  private:
    Ui::MainWindow *ui;

    ConnectDialog *m_pConnectDialog;
    WsClient *m_pWsClient;

  public slots:
    void onDialogSubmit(QString url, QString name);
    void onQuit();
    void onWsError(QAbstractSocket::SocketError error);
    void onWsMessageReceived(const QString message);
    void onSendButtonPressed();
};

#endif // CHAT_QT_MAINWINDOW_H
