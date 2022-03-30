#ifndef SNAKE_H
#define SNAKE_H

#include <QMainWindow>

class Snake : public QMainWindow{
    Q_OBJECT
private:
    struct  SnakeNode{  //蛇坐标结构
        int x;
        int y;
    };
    const int Margin=80;
    const int mysize=20;
public:
    explicit Snake(QWidget *parent = nullptr);
    QVector<SnakeNode> snakevec;    //蛇坐标容器
    void Move(char key);    //蛇移动主要函数
    void DeteDirMove(char key, SnakeNode &nexthead);    //根据key值确定蛇的移动方向
    void Reset();//重置蛇
    void setData(QVector<int>& tx,QVector<int>& ty);
    QVector<int> snakex();
    QVector<int> snakey();
};

#endif // SNAKE_H
