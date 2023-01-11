#ifndef BATTLESHIPS_H
#define BATTLESHIPS_H

#include <QMainWindow>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <QTcpSocket>
#include <QtcpServer>



QT_BEGIN_NAMESPACE
namespace Ui { class BattleShips; }
QT_END_NAMESPACE



// × • O

struct Cell {
    int row;
    char column;
};



class Field {
private:
    char field[10][10];
    int oneCell;
    int twoCell;
    int threeCell;
    int fourCell;
public:
    Field() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                field[i][j] = '*';
            }
        }
        oneCell=0;
        twoCell=0;
        threeCell=0;
        fourCell=0;
    }
    int getOne(){return oneCell;}
    int getTwo(){return twoCell;}
    int getThree(){return threeCell;}
    int getFour(){return fourCell;}

    char placeShip1(char column, int row) {
        //returns 'P' if other ship placed too close,
        //returns 'O' if ship already placed there,
        //returns 'Y' if ship placed,
        //returns 'D' if incorrect data
        if(oneCell==4) return 'D';
        if (column - 'A' < 0 || column - 'A' > 9 || row < 1 || row>10) return 'D';
        row--;
        if (field[column - 'A'][row] != '*') return 'O';
        if (column == 'A' && row == 0) {
            if (field[column + 1 - 'A'][row] == '*' && field[column + 1 - 'A'][row + 1] == '*' && field[column - 'A'][row + 1] == '*') field[column - 'A'][row] = 'O';
            else return 'P';
        }
        else if (column == 'J' && row == 0) {
            if (field[column - 1 - 'A'][row] == '*' && field[column - 1 - 'A'][row + 1] == '*' && field[column - 'A'][row + 1] == '*') field[column - 'A'][row] = 'O';
            else return 'P';
        }
        else if (column == 'A' && row == 9) {
            if (field[column + 1 - 'A'][row] == '*' && field[column + 1 - 'A'][row - 1] == '*' && field[column - 'A'][row - 1] == '*') field[column - 'A'][row] = 'O';
            else return 'P';
        }
        else if (column == 'J' && row == 9) {
            if (field[column - 1 - 'A'][row] == '*' && field[column - 1 - 'A'][row - 1] == '*' && field[column - 'A'][row - 1] == '*') field[column - 'A'][row] = 'O';
            else return 'P';
        }
        else if (column == 'A') {
            //**
            //O*
            //**
            if (field[column + 1 - 'A'][row] == '*' && field[column + 1 - 'A'][row + 1] == '*' && field[column - 'A'][row + 1] == '*' && field[column - 'A'][row - 1] == '*' && field[column + 1 - 'A'][row - 1] == '*') field[column - 'A'][row] = 'O';
            else return 'P';
        }
        else if (column == 'J') {
            //**
            //*O
            //**
            if (field[column - 1 - 'A'][row] == '*' && field[column - 1 - 'A'][row + 1] == '*' && field[column - 'A'][row + 1] == '*' && field[column - 'A'][row - 1] == '*' && field[column - 1 - 'A'][row - 1] == '*') field[column - 'A'][row] = 'O';
            else return 'P';
        }
        else if (row == 0) {
            //*0*
            //***
            if (field[column - 1 - 'A'][row] == '*' && field[column - 1 - 'A'][row + 1] == '*' && field[column - 'A'][row + 1] == '*' && field[column + 1 - 'A'][row + 1] == '*' && field[column + 1 - 'A'][row] == '*') field[column - 'A'][row] = 'O';
            else return 'P';
        }
        else if (row == 9) {
            //***
            //*0*
            if (field[column - 1 - 'A'][row] == '*' && field[column - 1 - 'A'][row - 1] == '*' && field[column - 'A'][row - 1] == '*' && field[column + 1 - 'A'][row - 1] == '*' && field[column + 1 - 'A'][row] == '*') field[column - 'A'][row] = 'O';
            else return 'P';
        }
        //***
        //*0*
        //***
        else {
            if (field[column - 1 - 'A'][row] == '*' && field[column - 1 - 'A'][row - 1] == '*' && field[column - 'A'][row - 1] == '*' && field[column + 1 - 'A'][row - 1] == '*' && field[column + 1 - 'A'][row] == '*' && field[column + 1 - 'A'][row + 1] == '*' && field[column - 'A'][row + 1] == '*' && field[column - 1 - 'A'][row + 1] == '*') field[column - 'A'][row] = 'O';
            else return 'P';
        }
        oneCell++;
        return 'Y';
    }
    char placeShip(int size, char column, int row, char column2, int row2) {
        //returns 'P' if other ship placed too close,
        //returns 'O' if ship already placed there,
        //returns 'Y' if ship placed successfully,
        //returns 'D' if incorrect data
        column = column - 'A';
        column2 = column2 - 'A';
        row--;
        row2--;
        if(size==4&&fourCell==1) return'D';
        if(size==3&&threeCell==2)return'D';
        if(size==2&&twoCell==3)return 'D';
        if (column != column2 && row != row2) return 'D';
        if (column == column2 && row == row2) return 'D';
        if (column > 9 || column < 0) return 'D';
        if (column2 > 9 || column2 < 0)return'D';
        if (row > 9 || row < 0 || row2>9 || row2 < 0)return'D';
        if (column == column2) {
            if (row < row2) {
                int temp = row;
                row = row2;
                row2 = temp;
            }
            if (row - row2 + 1 != size) return 'D';
            for (int i = row2; i<=row; i++) {
                if (field[column][i] != '*') return 'O';
                if (column != 0 && field[column-1][i] != '*') return 'P';
                if (column != 9 && field[column+1][i] != '*') return 'P';
            }
            if (column == 0) {
                if (row2 != 0 && (field[column][row2 - 1] != '*' || field[column + 1][row2 - 1] != '*')) return 'P';
                if (row != 9 && (field[column][row + 1] != '*' || field[column + 1][row + 1] != '*')) return 'P';
            }else if (column == 9) {
                if (row2 != 0 && (field[column][row2 - 1] != '*' || field[column - 1][row2 - 1] != '*')) return 'P';
                if (row != 9 && (field[column][row + 1] != '*' || field[column - 1][row + 1] != '*')) return 'P';
            }
            else {
                if (row2 != 0 && (field[column][row2 - 1] != '*' || field[column - 1][row2 - 1] != '*' || field[column + 1][row2 - 1] != '*')) return 'P';
                if (row != 9 && (field[column][row + 1] != '*' || field[column - 1][row + 1] != '*' || field[column + 1][row + 1] != '*')) return 'P';
            }
            for (int i = row2; i <= row; i++) {
                field[column][i] = 'O';
            }
        }
        if (row == row2) {
            if (column < column2) {
                int temp = column;
                column = column2;
                column2 = temp;
            }
            if (column - column2 + 1 != size) return 'D';
            for (int i = column2; i <= column; i++) {
                if (field[i][row] != '*') return 'O';
                if (row != 0 && field[i][row-1] != '*') return 'P';
                if (row != 9 && field[i][row+1] != '*') return 'P';
            }
            if (row == 0) {
                if (column2 != 0 && (field[column2-1][row] != '*' || field[column2 - 1][row + 1] != '*')) return 'P';
                if (column != 9 && (field[column+1][row] != '*' || field[column + 1][row + 1] != '*')) return 'P';
            }
            else if (row == 9) {
                if (column2 != 0 && (field[column2-1][row] != '*' || field[column2 - 1][row - 1] != '*')) return 'P';
                if (column != 9 && (field[column+1][row - 1] != '*' || field[column + 1][row] != '*')) return 'P';
            }
            else {
                if (column2 != 0 && (field[column2-1][row - 1] != '*' || field[column2 - 1][row] != '*' || field[column2 - 1][row + 1] != '*')) return 'P';
                if (column != 9 && (field[column+1][row + 1] != '*' || field[column + 1][row] != '*' || field[column + 1][row - 1] != '*')) return 'P';
            }
            for (int i = column2; i <= column; i++) {
                field[i][row] = 'O';
            }
        }
        if(size==2) twoCell++;
        if(size==3)threeCell++;
        if(size==4)fourCell++;
        return 'Y';
    }

    bool killed(char column, int row) {
            if (column - 'A' < 0 || column - 'A' > 9 || row < 1 || row>10) return false;
            row--;
            if (field[column - 'A'][row] != 'O') return false;
            if (column == 'A' && row == 0) {
                if (field[column + 1 - 'A'][row] == 'O' ||  field[column - 'A'][row + 1] == 'O') return false;
            }
            else if (column == 'J' && row == 0) {
                if (field[column - 1 - 'A'][row] == 'O' || field[column - 'A'][row + 1] == 'O') return false;
            }
            else if (column == 'A' && row == 9) {
                if (field[column + 1 - 'A'][row] == 'O' || field[column - 'A'][row - 1] == 'O') return false;
            }
            else if (column == 'J' && row == 9) {
                if (field[column - 1 - 'A'][row] == 'O' || field[column - 'A'][row - 1] == 'O') return false;
            }
            else if (column == 'A') {
                //*
                //O*
                //*
                if (field[column + 1 - 'A'][row] == 'O' || field[column - 'A'][row + 1] == 'O' || field[column - 'A'][row - 1] == 'O') return false;
            }
            else if (column == 'J') {
                // *
                //*O
                // *
                if (field[column - 1 - 'A'][row] == 'O' || field[column - 'A'][row + 1] == 'O' || field[column - 'A'][row - 1] == 'O') return false;
            }
            else if (row == 0) {
                //*0*
                // *
                if (field[column - 1 - 'A'][row] == 'O' || field[column - 'A'][row + 1] == 'O' || field[column + 1 - 'A'][row] == 'O') return false;
            }
            else if (row == 9) {
                // *
                //*0*
                if (field[column - 1 - 'A'][row] == 'O' || field[column - 'A'][row - 1] == 'O' || field[column + 1 - 'A'][row] == 'O') return false;
            }
            // *
            //*0*
            // *
            else {
                if (field[column - 1 - 'A'][row] == 'O' || field[column - 'A'][row - 1] == 'O' || field[column + 1 - 'A'][row] == 'O' || field[column - 'A'][row + 1] == 'O') return false;
            }
            return true;
        }
    void drawDestroyedShip1(char column, int row) {
           setCell(column, row, 'X');
           if (row != 1 && getCell(column, row - 1) == 'x')drawDestroyedShip1(column, row - 1);
           if (row != 10 && getCell(column, row + 1) == 'x')drawDestroyedShip1(column, row + 1);
           if (column != 'A' && getCell(column-1, row) == 'x')drawDestroyedShip1(column-1, row);
           if (column != 'J' && getCell(column+1, row) == 'x')drawDestroyedShip1(column+1, row);
       }

       void drawDestroyedShip2() {
           for (int i = 0; i < 10; i++) {
               for (int j = 0; j < 10; j++) {
                   if (field[j][i] == 'X') {
                       if (j == 0 && i == 0) {
                           if (field[j + 1][i] != 'X')field[j + 1][i] = '.';
                           if (field[j + 1][i + 1] != 'X')field[j + 1][i + 1] = '.';
                           if (field[j][i+1] != 'X')field[j][i+1] = '.';
                       }
                       else if (j == 9 && i == 0) {
                           if (field[j - 1][i] != 'X')field[j - 1][i] = '.';
                           if (field[j - 1][i + 1] != 'X')field[j - 1][i + 1] = '.';
                           if (field[j][i + 1] != 'X')field[j][i + 1] = '.';
                       }
                       else if (j == 0 && i == 9) {
                           if (field[j + 1][i-1] != 'X')field[j +1][i-1] = '.';
                           if (field[j][i - 1] != 'X')field[j][i - 1] = '.';
                           if (field[j+1][i] != 'X')field[j+1][i] = '.';
                       }
                       else if (j == 9 && i == 9) {
                           if (field[j - 1][i - 1] != 'X')field[j - 1][i - 1] = '.';
                           if (field[j][i - 1] != 'X')field[j][i - 1] = '.';
                           if (field[j-1][i] != 'X')field[j - 1][i] = '.';
                       }
                       else if (j == 0) {
                           if (field[j + 1][i] != 'X')field[j + 1][i] = '.';
                           if (field[j + 1][i + 1] != 'X')field[j + 1][i + 1] = '.';
                           if (field[j][i + 1] != 'X')field[j][i + 1] = '.';
                           if (field[j][i - 1] != 'X')field[j][i - 1] = '.';
                           if (field[j+1][i - 1] != 'X')field[j+1][i - 1] = '.';
                       }
                       else if (i == 0) {
                           if (field[j + 1][i] != 'X')field[j + 1][i] = '.';
                           if (field[j + 1][i + 1] != 'X')field[j + 1][i + 1] = '.';
                           if (field[j][i + 1] != 'X')field[j][i + 1] = '.';
                           if (field[j - 1][i] != 'X')field[j - 1][i] = '.';
                           if (field[j - 1][i + 1] != 'X')field[j - 1][i + 1] = '.';

                       }
                       else if (j == 9) {
                           if (field[j - 1][i-1] != 'X')field[j - 1][i-1] = '.';
                           if (field[j ][i - 1] != 'X')field[j ][i - 1] = '.';
                           if (field[j][i + 1] != 'X')field[j][i + 1] = '.';
                           if (field[j - 1][i] != 'X')field[j - 1][i] = '.';
                           if (field[j - 1][i + 1] != 'X')field[j - 1][i + 1] = '.';
                       }
                       else if (i == 9) {
                           if (field[j + 1][i - 1] != 'X')field[j + 1][i - 1] = '.';
                           if (field[j][i - 1] != 'X')field[j][i - 1] = '.';
                           if (field[j + 1][i] != 'X')field[j + 1][i] = '.';
                           if (field[j - 1][i] != 'X')field[j - 1][i] = '.';
                           if (field[j - 1][i-1] != 'X')field[j - 1][i-1] = '.';
                       }
                       else {
                           if (field[j + 1][i] != 'X')field[j + 1][i] = '.';
                           if (field[j + 1][i + 1] != 'X')field[j + 1][i + 1] = '.';
                           if (field[j][i + 1] != 'X')field[j][i + 1] = '.';
                           if (field[j - 1][i] != 'X')field[j - 1][i] = '.';
                           if (field[j - 1][i + 1] != 'X')field[j - 1][i + 1] = '.';
                           if (field[j + 1][i - 1] != 'X')field[j + 1][i - 1] = '.';
                           if (field[j][i - 1] != 'X')field[j][i - 1] = '.';
                           if (field[j - 1][i - 1] != 'X')field[j - 1][i - 1] = '.';
                       }
                  }
               }
           }
       }
    void setCell(char column, int row, char newSign) {
        if (column-'A' > 9 || column-'A' < 0 || row>10 || row < 0) return;
        field[column-'A'][row - 1] = newSign;
    }
    char getCell(char column, int row) {
        if (column - 'A' > 9 || column - 'A' < 0 || row > 10 || row < 0) return 'E';
        return field[column-'A'][row - 1];
    }
    bool finished(){
        for (int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                if(field[i][j]=='O') return false;
            }
        }
        return true;
    }
};


class AIBot {
private:
    Field botField;
public:
    AIBot() {}
    void setField() {
        srand(time(NULL));
        int row, column, row2, column2;
        for (int i = 0; i < 4; i++) {
            row = rand() % 10 + 1;
            column = rand() % 10 + 'A';
            while (botField.placeShip1(column, row) != 'Y') {
                row = rand() % 10 + 1;
                column = rand() % 10 + 'A';
            }
        }
        for (int i = 0; i < 3; i++) {
            row = rand() % 10 + 1;
            column = rand() % 10 + 'A';
            row2 = rand() % 10 + 1;
            column2 = rand() % 10 + 'A';
            while (botField.placeShip(2,column, row,column2,row2) != 'Y') {
                row = rand() % 10 + 1;
                column = rand() % 10 + 'A';
                row2 = rand() % 10 + 1;
                column2 = rand() % 10 + 'A';
            }
        }
        for (int i = 0; i < 2; i++) {
            row = rand() % 10 + 1;
            column = rand() % 10 + 'A';
            row2 = rand() % 10 + 1;
            column2 = rand() % 10 + 'A';
            while (botField.placeShip(3, column, row, column2, row2) != 'Y') {
                row = rand() % 10 + 1;
                column = rand() % 10 + 'A';
                row2 = rand() % 10 + 1;
                column2 = rand() % 10 + 'A';
            }
        }
        row = rand() % 10 + 1;
        column = rand() % 10 + 'A';
        row2 = rand() % 10 + 1;
        column2 = rand() % 10 + 'A';
        while (botField.placeShip(4, column, row, column2, row2) != 'Y') {
            row = rand() % 10 + 1;
            column = rand() % 10 + 'A';
            row2 = rand() % 10 + 1;
            column2 = rand() % 10 + 'A';
        }
    }
    Cell shoot(Field enemyField) {
        srand(time(NULL));
        Cell result;
        result.row = rand() % 10 + 1;
        result.column = rand() % 10 + 'A';
        while (enemyField.getCell(result.column, result.row) != '*'&& enemyField.getCell(result.column,result.row)!='O') {
            result.row = rand() % 10 + 1;
            result.column = rand() % 10 + 'A';
        }
        return result;
    }
    void setBotCell(char column,int row,char sign){
        botField.setCell(column,row,sign);
    }

    Field getBotField() {
        return botField;
    }
};


class MyServer:public QObject
{
    Q_OBJECT
public:
        void Connect();
        void CreateServer();

    signals:


    public slots:
        void newConnection();

private:
    QTcpSocket *socket;
    QTcpServer *server;
};


class BattleShips : public QMainWindow
{
    Q_OBJECT

private:
    Field playersField,shootField;
    AIBot bot;
public:
    BattleShips(QWidget *parent = nullptr);
    ~BattleShips();

private slots:


    void on_table1_cellActivated(int row, int column);

    void on_pushButton_clicked();

    void on_oneCellButton_clicked();

    void on_severalCellsButton_clicked();

    void on_shootButton_clicked();

    void on_hostButton_clicked();



    void on_connectButton_clicked();

private:
    Ui::BattleShips *ui;


};



#endif // BATTLESHIPS_H
