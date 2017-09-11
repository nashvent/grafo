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
    g->printStatic();
    g->print();

 /*   cout<<"inicio: ";
    g->nStatic[0]->printNode();
    cout<<"fin: ";
    g->nStatic[1]->printNode();
    cout<<endl;
    cout<<"A*"<<endl;
    g->aStar(g->nStatic[0]->coord,g->nStatic[1]->coord);
*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString x,y,a,b;
    x= ui->i_x->text();
    y= ui->i_y->text();
    a= ui->f_x->text();
    b= ui->f_y->text();
    int p1[2]={x.toInt(),y.toInt()};
    int p2[2]={a.toInt(),b.toInt()};
    g->searchBlind(p1,p2);
}
