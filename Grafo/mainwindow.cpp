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
    vector<int>predefinido={18,14,14,9,19,7,17,1,0,8};
    for(int x=0;x<predefinido.size()-1;x=x+2){
        int y[2];
        y[0]=predefinido[x];
        y[1]=predefinido[x+1];
        g->insertNode(y);
    }
    //g->randomInsert(scene,redBrush,outlinePen,tam);
    g->cuadricular(scene,outlinePen);
    g->printStatic();
    g->print();

    cout<<"inicio: ";
    g->nStatic[0]->printNode();
    cout<<"fin: ";
    g->nStatic[g->nStatic.size()-1]->printNode();
    cout<<endl;
    cout<<"A*"<<endl;
    g->aStar(g->nStatic[0]->coord,g->nStatic[1]->coord);

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

    QString x,y,a,b;
    x= ui->i_x->text();
    y= ui->i_y->text();
    a= ui->f_x->text();
    b= ui->f_y->text();
    int p1[2]={x.toInt(),y.toInt()};
    int p2[2]={a.toInt(),b.toInt()};
    g->colorNode(scene,outlinePen,ini,fin,p1,p2);
    string result=g->searchBlind(scene,outlinePen,p1,p2);
    QString qstr = QString::fromStdString(result);
    ui->lb_result->setText(qstr);
}

void MainWindow::on_pushButton_2_clicked()
{
    QPen outlinePen(Qt::red);
    QBrush ini(Qt::blue);
    QBrush fin(Qt::green);

    QString x,y,a,b;
    x= ui->i_x->text();
    y= ui->i_y->text();
    a= ui->f_x->text();
    b= ui->f_y->text();
    int p1[2]={x.toInt(),y.toInt()};
    int p2[2]={a.toInt(),b.toInt()};
    g->colorNode(scene,outlinePen,ini,fin,p1,p2);

    cout<<"click click clik"<<endl;
}
