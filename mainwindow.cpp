#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "oEditingFunctions"
#include "oFilters.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cv::Mat img = cv::imread("D://0-WORK/0-Programming/QT/Image-Processing/Ressources/lena.jpg", false);

    //original image
    ui->originalImage->setPixmap(QPixmap("D://0-WORK/0-Programming/QT/Image-Processing/Ressources/lena.jpg"));



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

