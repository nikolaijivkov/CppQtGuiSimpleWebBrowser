#pragma once
//#ifndef MAINWINDOW_H
//#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QUrl>
#include <QProgressBar>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QWebEngineView>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent  = nullptr);
    ~MainWindow();
public slots:
    void setUrl();
    void setIconUrl(const QUrl &iconUrl);
    void setIconFromNetworkReply(QNetworkReply* reply);  // used by setIconUrl
private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *nam;
    QUrl currentIconUrl;
};

//#endif // MAINWINDOW_H
