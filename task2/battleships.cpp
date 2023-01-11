#include "battleships.h"
#include "./ui_battleships.h"

#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTcpSocket>
#include <QNetworkProxy>
BattleShips::BattleShips(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BattleShips)
{

    ui->setupUi(this);

    ui->shootButton->setVisible(false);
    ui->severalCellsButton->setVisible(false);
    ui->oneCellButton->setVisible(false);
    ui->labelInput->setVisible(false);
    ui->coordinatesInputBox->setVisible(false);
    ui->table1->setColumnCount(10);
    ui->table1->setRowCount(10);
    QStringList hLabels;
    hLabels<<"A"<<"B"<<"C"<<"D"<<"E"<<"F"<<"G"<<"H"<<"I"<<"J";
    ui->table1->setHorizontalHeaderLabels(hLabels);

    ui->table1->horizontalHeader()->setVisible(true);
    ui->table1->horizontalHeader()->setDefaultSectionSize(10);

    ui->table2->setColumnCount(10);
    ui->table2->setRowCount(10);

    ui->table2->setHorizontalHeaderLabels(hLabels);

    ui->table2->horizontalHeader()->setVisible(true);
    ui->table2->horizontalHeader()->setDefaultSectionSize(10);
}


BattleShips::~BattleShips()
{

    delete ui;
}


void BattleShips::on_pushButton_clicked()
{
   ui->oneCellButton->setVisible(true);
   ui->labelInput->setVisible(true);
   ui->pushButton->setVisible(false);
   ui->coordinatesInputBox->setVisible(true);
   return;
}


void BattleShips::on_table1_cellActivated(int row, int column)
{
   return;
}


void BattleShips::on_oneCellButton_clicked()
{
    QString coordinate=ui->coordinatesInputBox->toPlainText();
    if(coordinate.size()<2){
        ui->coordinatesInputBox->clear();
        return;
    }
    char column=coordinate[0].toLatin1();
    int row=coordinate[1].toLatin1()-'0';
    if(coordinate.size()>=3&&coordinate[2].toLatin1()=='0'&&coordinate[1].toLatin1()=='1') row=10;
    if(playersField.placeShip1(column,row)!='Y') {
        ui->coordinatesInputBox->clear();
        return;
    }
    QTableWidgetItem *item= new QTableWidgetItem;
    item->setText("O");
    ui->table1->setItem(row-1,column-'A',item);
    ui->coordinatesInputBox->clear();
    if(playersField.getOne()==4){
        ui->oneCellButton->setVisible(false);
        ui->labelInput->setText("Input coordinates of your 2x1 ship (example: A1B1)");
        ui->severalCellsButton->setVisible(true);
    }
}


void BattleShips::on_severalCellsButton_clicked()
{
    QString coordinate=ui->coordinatesInputBox->toPlainText();
    int k=0;
    if(coordinate.size()<4){
        ui->coordinatesInputBox->clear();
        return;
    }
    char column=coordinate[k++].toLatin1();
    int row=coordinate[k++].toLatin1()-'0';
    if(coordinate[k].toLatin1()=='0'&&coordinate[k-1].toLatin1()=='1') {
        row=10;
        k++;
    }
    char column2=coordinate[k++].toLatin1();
    int row2=coordinate[k++].toLatin1()-'0';
    if(row==10&&coordinate.size()>=6&&coordinate[k].toLatin1()=='0'&&coordinate[k-1].toLatin1()=='1')row2=10;
    if(row!=10&&coordinate.size()>=5&&coordinate[k].toLatin1()=='0'&&coordinate[k-1].toLatin1()=='1')row2=10;
    if(playersField.getTwo()!=3){
        if(playersField.placeShip(2,column,row,column2,row2)!='Y') {
            ui->coordinatesInputBox->clear();
            return;
        }
        QTableWidgetItem *item= new QTableWidgetItem;
        item->setText("O");
        if(column==column2){
            if(row<row2){
                int temp=row;
                row=row2;
                row2=temp;
            }

            ui->table1->setItem(row2,column-'A',item);
            item= new QTableWidgetItem;
            item->setText("O");
            ui->table1->setItem(row2-1,column-'A',item);
        }
        if(row==row2){
            if(column<column2){
                char temp=column;
                column=column2;
                column2=temp;
            }
            for(int i=column2;i<=column;i++){
                item= new QTableWidgetItem;
                item->setText("O");
                ui->table1->setItem(row-1,i-'A',item);
            }
        }
        ui->coordinatesInputBox->clear();
        if(playersField.getTwo()==3)ui->labelInput->setText("Input coordinates of your 3x1 ship (example: A1C1)");
        return;
    }
    if(playersField.getThree()!=2){
        if(playersField.placeShip(3,column,row,column2,row2)!='Y') {
            ui->coordinatesInputBox->clear();
            return;
        }
        QTableWidgetItem *item= new QTableWidgetItem;
        item->setText("O");
        if(column==column2){
            if(row<row2){
                int temp=row;
                row=row2;
                row2=temp;
            }
            for(int i=row2;i<=row;i++){
                item= new QTableWidgetItem;
                item->setText("O");
                ui->table1->setItem(i-1,column-'A',item);
            }
        }
        if(row==row2){
            if(column<column2){
                char temp=column;
                column=column2;
                column2=temp;
            }
            for(int i=column2;i<=column;i++){
                item= new QTableWidgetItem;
                item->setText("O");
                ui->table1->setItem(row-1,i-'A',item);
            }
        }
        ui->coordinatesInputBox->clear();
        if(playersField.getThree()==2)ui->labelInput->setText("Input coordinates of your 4x1 ship (example: A1D1)");
        return;
    }
    if(playersField.getFour()!=1){
        if(playersField.placeShip(4,column,row,column2,row2)!='Y') {
            ui->coordinatesInputBox->clear();
            return;
        }
        QTableWidgetItem *item= new QTableWidgetItem;
        item->setText("O");
        if(column==column2){
            if(row<row2){
                int temp=row;
                row=row2;
                row2=temp;
            }
            for(int i=row2;i<=row;i++){
                item= new QTableWidgetItem;
                item->setText("O");
                ui->table1->setItem(i-1,column-'A',item);
            }
        }
        if(row==row2){
            if(column<column2){
                char temp=column;
                column=column2;
                column2=temp;
            }
            for(int i=column2;i<=column;i++){
                item= new QTableWidgetItem;
                item->setText("O");
                ui->table1->setItem(row-1,i-'A',item);
            }
        }
        ui->coordinatesInputBox->clear();
        if(playersField.getFour()==1){
            ui->labelInput->setText("Enter coordinates to shoot");
            ui->severalCellsButton->setVisible(false);
            ui->coordinatesInputBox->clear();
            ui->shootButton->setVisible(true);
            bot.setField();
            for(int i=0;i<10;i++){
                for(int j=0;j<10;j++){
                    QTableWidgetItem *item = new QTableWidgetItem;
                    item->setText("*");
                    ui->table2->setItem(i,j,item);
                    shootField.setCell(j+'A',i,'*');
                }
            }
            Field botField=bot.getBotField();
            for(int i=0;i<10;i++){
                for(int j=0;j<10;j++){
                    QTableWidgetItem *item = new QTableWidgetItem;
                    char ch=botField.getCell(j+'A',i+1);
                    if(ch=='O') item->setText("O");
                    if(ch=='*') item->setText("*");
                    ui->table2->setItem(i,j,item);
                }
            }
        }
        return;
    }
}



void BattleShips::on_shootButton_clicked(){
    Field botField=bot.getBotField();
    QString coordinate=ui->coordinatesInputBox->toPlainText();
    if(coordinate.size()<2){
        ui->coordinatesInputBox->clear();
        return;
    }
    char column=coordinate[0].toLatin1();
    int row=coordinate[1].toLatin1()-'0';
    if(coordinate.size()>=3&&coordinate[2].toLatin1()=='0'&&coordinate[1].toLatin1()=='1') row=10;
    if(shootField.getCell(column,row)!='*'){
        ui->labelInput->setText("You already shooted there, try again");
        return;
    }

    if(botField.getCell(column,row)=='O'){
        QTableWidgetItem *item = new QTableWidgetItem;

        if(botField.killed(column,row)){
            bot.setBotCell(column,row,'X');
            shootField.setCell(column,row,'X');//'X' means destroyed an enemy ship shot
            item->setText("X");
            ui->table2->setItem(row,column-'A',item);
            shootField.drawDestroyedShip1(column,row);
            shootField.drawDestroyedShip2();
            ui->labelInput->setText("You destryed an enemy ship! You have an additional turn.");
            for(int i=0;i<10;i++){
                for(int j=0;j<10;j++){
                    QTableWidgetItem *item = new QTableWidgetItem;
                    char ch=shootField.getCell(j+'A',i+1);
                    if(ch=='*') item->setText("*");
                    if(ch=='x') item->setText("x");
                    if(ch=='X') item->setText("X");
                    if(ch=='.') item->setText(".");
                    ui->table2->setItem(i,j,item);
                }
            }

            if(botField.finished()){
                ui->labelInput->setText("You won");
                ui->shootButton->setVisible(false);
                ui->coordinatesInputBox->setVisible(false);
            }
            return;
        }else{
            bot.setBotCell(column,row,'x');
            shootField.setCell(column,row,'x');//'x' means got into a ship shot
            for(int i=0;i<10;i++){
                for(int j=0;j<10;j++){
                    QTableWidgetItem *item = new QTableWidgetItem;
                    char ch=shootField.getCell(j+'A',i+1);
                    if(ch=='*') item->setText("*");
                    if(ch=='x') item->setText("x");
                    if(ch=='X') item->setText("X");
                    if(ch=='.') item->setText(".");
                    ui->table2->setItem(i,j,item);
                }
            }
            ui->labelInput->setText("You got into a ship! You have an additional turn.");

            if(botField.finished()){
                ui->labelInput->setText("You won");
                ui->shootButton->setVisible(false);
                ui->coordinatesInputBox->setVisible(false);
            }
            return;
        }
    }


    if(botField.getCell(column,row)=='*'){
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(".");
        ui->table2->setItem(row-1,column-'A',item);
        ui->labelInput->setText("You missed, try again next turn.");

        bot.setBotCell(column,row,'.');
        shootField.setCell(column,row,'.');//'.' means nothing was on this spot
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                item = new QTableWidgetItem;
                char ch=shootField.getCell(j+'A',i+1);
                if(ch=='*') item->setText("*");
                if(ch=='x') item->setText("x");
                if(ch=='X') item->setText("X");
                if(ch=='.') item->setText(".");
                ui->table2->setItem(i,j,item);
            }
        }


        Cell botShot=bot.shoot(playersField);
        while(1){
            if(playersField.finished()){
                Field bots=bot.getBotField();
                for(int i=0;i<10;i++){
                    for(int j=0;j<10;j++){
                        QTableWidgetItem *item = new QTableWidgetItem;
                        item->setText(" ");
                        char ch=bots.getCell(j+'A',i+1);
                        char ch1=shootField.getCell(j+'A',i+1);
                        if(ch=='O') item->setText("O");
                        if(ch1=='x') item->setText("x");
                        if(ch1=='X') item->setText("X");
                        if(ch1=='.') item->setText(".");
                        ui->table2->setItem(i,j,item);
                    }
                }
                ui->labelInput->setText("Bot won");
                ui->shootButton->setVisible(false);
                ui->coordinatesInputBox->setVisible(false);
                return;
            }
            if(playersField.getCell(botShot.column,botShot.row)=='*'){
                QTableWidgetItem *item = new QTableWidgetItem;
                item->setText(".");
                ui->table1->setItem(botShot.row-1,botShot.column-'A',item);
                playersField.setCell(botShot.column,botShot.row,'.');
                break;
            }else{
                if(playersField.getCell(botShot.column,botShot.row)=='O'){
                    if(playersField.killed(botShot.column,botShot.row)){
                        playersField.setCell(botShot.column,botShot.row,'X');
                        item->setText("X");
                        ui->table1->setItem(botShot.row-1,botShot.column-'A',item);
                        playersField.drawDestroyedShip1(botShot.column,botShot.row);
                        playersField.drawDestroyedShip2();
                        for(int i=0;i<10;i++){
                            for(int j=0;j<10;j++){
                                QTableWidgetItem *item = new QTableWidgetItem;
                                char ch=playersField.getCell(j+'A',i+1);
                                if(ch=='x') item->setText("x");
                                if(ch=='X') item->setText("X");
                                if(ch=='.') item->setText(".");
                                if(ch=='O') item->setText("O");
                                ui->table1->setItem(i,j,item);
                            }
                        }
                    }else{
                        playersField.setCell(botShot.column,botShot.row,'x');
                        item->setText("x");
                        ui->table1->setItem(botShot.row-1,botShot.column-'A',item);
                        for(int i=0;i<10;i++){
                            for(int j=0;j<10;j++){
                                QTableWidgetItem *item = new QTableWidgetItem;
                                char ch=playersField.getCell(j+'A',i+1);
                                if(ch=='x') item->setText("x");
                                if(ch=='X') item->setText("X");
                                if(ch=='.') item->setText(".");
                                if(ch=='O') item->setText("O");
                                ui->table1->setItem(i,j,item);
                            }
                        }
                    }
                    botShot=bot.shoot(playersField);
                }

            }

        }
    }
}



void BattleShips::on_hostButton_clicked()
{
    MyServer asd;
    asd.CreateServer();
}



void MyServer::Connect()
{
    socket = new QTcpSocket(this);
   // socket->setProxy(QNetworkProxy::NoProxy);
    socket->connectToHost(QHostAddress("127.0.0.1"), 5555);

        if(socket->waitForConnected(3000))
        {
            qDebug() << "Connected!";
        }
        else
        {
            qDebug() << "Not connected!";
        }
}

void MyServer::CreateServer()
{
    server=new QTcpServer(this);
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
    if(!server->listen(QHostAddress("127.0.0.1"),5555)){
        qDebug()<<"Server could not start";
    }else{
        qDebug()<<"Server started";
    }
}

void MyServer::newConnection()
{
    QTcpSocket *socket1=server->nextPendingConnection();
    socket1->write("hello");
    socket1->flush();
    socket1->waitForBytesWritten(3000);
    socket->close();
}

void BattleShips::on_connectButton_clicked()
{
    MyServer asd;
    asd.Connect();
}

