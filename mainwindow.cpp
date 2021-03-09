#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "oEditingFunctions"
#include "oFilters.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    cv::Mat img = cv::imread("D://lena.jpg", false);

    //original image
    ui->originalImage->setPixmap(QPixmap("D://lena.jpg"));
    /*
    cv::Mat lowImg = thresholdOtsu(img);
    QImage qimgg((uchar*)lowImg.data, lowImg.cols, lowImg.rows, lowImg.step, QImage::Format_Indexed8);
    ui->originalImage->setPixmap(QPixmap::fromImage(qimgg));
    */
    uchar kdata[] = {0, 1, 0,1, 1, 1, 0, 1, 0};
    cv::Mat kernel(3,3,CV_8U, kdata);
    cv::Mat inversedImg = convolution(img, kernel);


    std::cout <<"blabla"<<std::endl;
    QImage qimg((uchar*)inversedImg.data, inversedImg.cols, inversedImg.rows, inversedImg.step, QImage::Format_Indexed8);
    ui->targetImage->setPixmap(QPixmap::fromImage(qimg));

}

MainWindow::~MainWindow()
{
    delete ui;
}

