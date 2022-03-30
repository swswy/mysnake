#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>     //画家类
#include "snake.h"      //蛇类
#include <QKeyEvent>    //键盘事件
#include "food.h"       //食物类
#include <QTimer>       //定时器类
#include <QBrush>
#include <QMouseEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *);
private:
    Ui::MainWindow *ui;
    const int Margin=80;
    const int mysize=20;

    Snake snake;        //蛇对象
    Food food;          //食物对象

    char key;     //接收键值，初始向右
    QTimer *timer;    //创建定时器
    bool gameflag;//游戏结束标记
    bool gamestart;
    bool bugflag; //用于解决操控过快导致撞死自己的bug的标志
    int dist;      //记录步数
    int timerspeed = 250; //定时器速度
    bool isWall[40][40];
    int reward;
    void GameOver();    //游戏结束的情况
    void readData();
    void writeData();
    void notStarted();
    void gameStarted();
    void gamePaused();
    void gameTermination();
};
#endif // MAINWINDOW_H
