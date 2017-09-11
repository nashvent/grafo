#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::graphicsNode(int tam,int size)
{
    int matrix[2]={size,size};
    g =new Graph(matrix);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QBrush redBrush(Qt::yellow);
    QPen outlinePen(Qt::black);

    g->randomInsert(scene,redBrush,outlinePen,tam);
    g->cuadricular(scene,outlinePen);
    g->print();
    cout<<"\n aristas"<<endl;
    g->printStatic();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QPen outlinePen(Qt::red);
    QBrush ini(Qt::blue);
    QBrush fin(Qt::green);
    QPen arista(Qt::black);


    QString x,y,a,b;
    x= ui->i_x->text();
    y= ui->i_y->text();
    a= ui->f_x->text();
    b= ui->f_y->text();
    int p1[2]={x.toInt(),y.toInt()};
    int p2[2]={a.toInt(),b.toInt()};
    g->colorNode(scene,arista,ini,fin,p1,p2);
    string result=g->searchBlind(scene,outlinePen,p1,p2);
    QString qstr = QString::fromStdString(result);
    ui->lb_result->setText(qstr);
}
