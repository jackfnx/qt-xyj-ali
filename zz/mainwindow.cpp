#include "mainwindow.h"
#include "./ui_mainwindow.h"
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
    ui->plainTextEdit->appendPlainText("什么\n");
    ui->lineEdit->selectAll();
}

