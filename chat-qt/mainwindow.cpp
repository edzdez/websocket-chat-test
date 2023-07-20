// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
    , m_pConnectDialog(new ConnectDialog(this))
    , m_pWsClient(new WsClient(this))
{
    ui->setupUi(this);

    connect(ui->SubmitButton, &QPushButton::clicked, this, &MainWindow::onSendButtonPressed);
    connect(m_pConnectDialog, &ConnectDialog::rejected, this, &MainWindow::onQuit);
    connect(m_pConnectDialog, &ConnectDialog::submitted, this, &MainWindow::onDialogSubmit);
    connect(m_pWsClient, &WsClient::error, this, &MainWindow::onWsError);
    connect(m_pWsClient, &WsClient::messageReceived, this, &MainWindow::onWsMessageReceived);

    m_pConnectDialog->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::attemptConnection(const QUrl &url, const QString &name)
{
    m_pWsClient->open(url, name);
}

void MainWindow::onDialogSubmit(QString url, QString name)
{
    spdlog::info("Url: {}", url.toStdString());
    spdlog::info("Name: {}", name.toStdString());

    ui->InfoLabel->setText("Connected to \"" + url + "\" as \"" + name + "\"");
    attemptConnection(QUrl("ws://" + url), name);
}

void MainWindow::onQuit()
{
    spdlog::info("quitting");
    close();
}

void MainWindow::onWsError(QAbstractSocket::SocketError error)
{
    spdlog::error("failed to connect to socket: {}", error);
    close();
}

void MainWindow::onWsMessageReceived(const QString message)
{
    ui->MessageView->appendPlainText(message);
}

void MainWindow::onSendButtonPressed()
{
    spdlog::info("send button pressed!");
    if (auto msg = ui->MessageEnter->toPlainText().trimmed(); msg.isEmpty())
        spdlog::error("can't send an empty message!");
    else
        m_pWsClient->send(msg);
    ui->MessageEnter->clear();
}
