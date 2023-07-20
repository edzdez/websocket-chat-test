#ifndef CHAT_QT_CONNECTUI_H
#define CHAT_QT_CONNECTUI_H

#include <QDialog>
#include <QPushButton>

#include <spdlog/spdlog.h>

QT_BEGIN_NAMESPACE

namespace Ui
{
class ConnectDialog;
}

QT_END_NAMESPACE

class ConnectDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit ConnectDialog(QWidget *parent = nullptr);
    ~ConnectDialog() override;

  private:
    Ui::ConnectDialog *ui;

  private slots:
    void accept() override;
    void reject() override;

  signals:
    void submitted(QString url, const QString name);
};


#endif // CHAT_QT_CONNECTUI_H
