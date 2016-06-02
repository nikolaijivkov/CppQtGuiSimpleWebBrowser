#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QUrl>
#include <QProgressBar>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QThread>
#include <QBasicTimer>
#include <QTimerEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void setUrl();
    void setIconUrl(const QUrl &iconUrl);
    void finishedIconRequest(QNetworkReply* reply);
private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *nam;
    QUrl currentIconUrl;
};


//ReplyTimer helper
class ReplyTimeout : public QObject {
  Q_OBJECT
  QBasicTimer m_timer;
public:
  ReplyTimeout(QNetworkReply* reply, const int timeout) : QObject(reply) {
    Q_ASSERT(reply);
    if (reply && reply->isRunning())
        m_timer.start(timeout, this);
  }
  static void set(QNetworkReply* reply, const int timeout) {
    new ReplyTimeout(reply, timeout);
  }
protected:
  void timerEvent(QTimerEvent * ev) {
    if (!m_timer.isActive() || ev->timerId() != m_timer.timerId())
        return;
    auto reply = static_cast<QNetworkReply*>(parent());
    if (reply->isRunning())
        reply->close();
    m_timer.stop();
  }
};

#endif // MAINWINDOW_H
