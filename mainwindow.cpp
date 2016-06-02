#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui {new Ui::MainWindow},
    nam {new QNetworkAccessManager(this)}
{
    ui->setupUi(this);

    ui->progressBar->hide();
    ui->webEngineView->load(QUrl("http://www.google.com"));
                          //QUrl("https://embed.gog.com"));  // it looks nice, and it's gameing site, so... win win

    //navigation buttons connections
    connect(ui->goBackBtn, &QPushButton::clicked, ui->webEngineView, &QWebEngineView::back);
    connect(ui->goForwBtn, &QPushButton::clicked, ui->webEngineView, &QWebEngineView::forward);
    connect(ui->reloadBtn, &QPushButton::clicked, ui->webEngineView, &QWebEngineView::reload);
    connect(ui->goBtn, &QPushButton::clicked, this, &MainWindow::setUrl);
    connect(ui->urlLine, &QLineEdit::returnPressed, this, &MainWindow::setUrl);

    //webEngine related connections - show/hide progress bar on loading, setValue of progress bar, update urlLine on urlChanged
    connect(ui->webEngineView, &QWebEngineView::loadStarted,  ui->progressBar, &QWidget::show);
    connect(ui->webEngineView, &QWebEngineView::loadProgress, ui->progressBar, &QProgressBar::setValue);
    connect(ui->webEngineView, &QWebEngineView::loadFinished, ui->progressBar, &QWidget::hide);
    connect(ui->webEngineView, &QWebEngineView::titleChanged, this, &QWidget::setWindowTitle);
    connect(ui->webEngineView, &QWebEngineView::urlChanged, [&](const QUrl& url){ui->urlLine->setText(url.toString());});

    //webEngine icon related connections - detect iconUrlChanged, download and set new icon to MainWindow
    connect(ui->webEngineView, &QWebEngineView::iconUrlChanged, this, &MainWindow::setIconUrl);
    connect(nam, &QNetworkAccessManager::finished, this, &MainWindow::finishedIconRequest);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUrl()
{
    QString url_str = ui->urlLine->text();
    if (!url_str.isEmpty())
    {
        ui->webEngineView->setUrl(QUrl::fromUserInput(url_str));
    }
}

void MainWindow::setIconUrl(const QUrl &iconUrl)
{
    if (!iconUrl.isEmpty() && currentIconUrl!=iconUrl){
        currentIconUrl = iconUrl;
        nam->get(QNetworkRequest(iconUrl));
    }
}

void MainWindow::finishedIconRequest(QNetworkReply* reply)
{
    QPixmap pixmap;
    pixmap.loadFromData(reply->readAll());
    setWindowIcon(QIcon(pixmap));
}
