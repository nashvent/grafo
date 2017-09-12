#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lb_i->setStyleSheet("QLabel{ background-color : blue; color : white; }");
    ui->lb_i->setAlignment(Qt::AlignCenter);
    ui->lb_f->setStyleSheet("QLabel{ background-color : green; color : white; }");
    ui->lb_f->setAlignment(Qt::AlignCenter);
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
    g->printStatic();
/*
    cout<<"inicio: ";
    g->nStatic[0]->printNode();
    cout<<"fin: ";
    g->nStatic[g->nStatic.size()-1]->printNode();
    cout<<endl;
    cout<<"A*"<<endl;
    //g->aStar(g->nStatic[0]->coord,g->nStatic[1]->coord);
*/
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
    QBrush yellow(Qt::yellow);
    QPen arista(Qt::black);

    QString x,y,a,b;
    x= ui->i_x->text();
    y= ui->i_y->text();
    a= ui->f_x->text();
    b= ui->f_y->text();
    int p1[2]={x.toInt(),y.toInt()};
    int p2[2]={a.toInt(),b.toInt()};
    if(g->searchNode(p1) && g->searchNode(p2)){
        g->delColor(scene,yellow,arista);
        g->colorNode(scene,arista,ini,fin,p1,p2);
        string res=g->searchBlind(scene,outlinePen,p1,p2);
        Dialog *dialog= new Dialog();
        dialog->result(res);
        dialog->show();
    }
    else{
        QMessageBox reply;
        reply.question(this, "Alerta", "No existen estos puntos",
             QMessageBox::Ok);
    }
}

void MainWindow::on_pushButton_2_clicked()
{

    QPen outlinePen(Qt::red);
    QBrush ini(Qt::blue);
    QBrush fin(Qt::green);
    QBrush yellow(Qt::yellow);
    QPen arista(Qt::black);

    QString x,y,a,b;
    x= ui->i_x->text();
    y= ui->i_y->text();
    a= ui->f_x->text();
    b= ui->f_y->text();
    int p1[2]={x.toInt(),y.toInt()};
    int p2[2]={a.toInt(),b.toInt()};
    if(g->searchNode(p1) && g->searchNode(p2)){
        g->delColor(scene,yellow,arista);
        g->colorNode(scene,arista,ini,fin,p1,p2);
        string resA=g->aStar(scene,outlinePen,p1,p2);
        cout<<"resA"<<resA<<endl;
        Dialog *dialog= new Dialog();
        dialog->result(resA);
        dialog->show();
    }
    else{
        QMessageBox reply;
        reply.question(this, "Alerta", "No existen estos puntos",
             QMessageBox::Ok);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString n,tam;
    n=ui->n_nodes->text();
    tam=ui->n_tam->text();
    graphicsNode(n.toInt(),tam.toInt());
}
