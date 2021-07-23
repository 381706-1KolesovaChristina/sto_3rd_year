#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    
private:
    Ui::MainWindow *ui;
        QCustomPlot *customPlot;
        QVBoxLayout *vbox;
    //    QPushButton *res;
    //    QCPBars *fossil;
    //QCustomPlot *customPlot;    // Объявляем графическое полотно
    //QCPGraph *graphic;          // Объявляем график
};
#endif // MAINWINDOW_H
