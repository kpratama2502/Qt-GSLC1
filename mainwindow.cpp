#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mNetManager = new QNetworkAccessManager(this);
    connect(mNetManager, &QNetworkAccessManager::finished,
            this, &MainWindow::handleNetFinished);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openUrl(const QString &url) {
    mNetManager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::testJson(QByteArray data) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    QString Anime = obj["anime"].toString();
    QString Character = obj["character"].toString();
    QString Quote = obj["quote"].toString();

    qDebug() << Anime;
    qDebug() << Character;
    qDebug() << Quote;

    ui->Anime->setText(Anime);
    ui->Character->setText(Character);
    ui->Quote->setText(Quote);

    //Website API: https://animechan.vercel.app/api/random
}

void MainWindow::handleNetFinished(QNetworkReply *reply) {
    if (reply->error()==QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        testJson(data);
    }
    else
        qDebug("Network error");
}

void MainWindow::on_pushButtonGetUrl_clicked() {
    openUrl(ui->lineEditUrl->text());
}
