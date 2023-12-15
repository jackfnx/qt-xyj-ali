#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setFocus();

    QPalette p = ui->plainTextEdit->palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::gray);
    ui->plainTextEdit->setPalette(p);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_returnPressed()
{
    QTextCharFormat fmt0 = ui->plainTextEdit->currentCharFormat();

    QString line = ui->lineEdit->text();
    QTextCharFormat fmt;
    fmt.setForeground(QBrush(Qt::yellow));
    ui->plainTextEdit->mergeCurrentCharFormat(fmt);
    ui->plainTextEdit->appendPlainText(line);
    ui->plainTextEdit->setCurrentCharFormat(fmt0);


    QNetworkAccessManager *manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished,
                     this, [manager, this, fmt0](QNetworkReply *reply){
        qDebug() << reply->error();
        ui->plainTextEdit->appendPlainText(reply->readAll());
    });
    QNetworkRequest request;
    request.setUrl(QUrl("http://127.0.0.1:7013/" + line));
    manager->get(request);

    ui->lineEdit->selectAll();
}
