#ifndef FOOD_H
#define FOOD_H

#include <QMainWindow>

class Food : public QMainWindow{
    Q_OBJECT
private:
    int foodx = 0;     //食物坐标
    int foody = 0;
    const int Margin=80;
    const int mysize=20;
public:
    explicit Food(QWidget *parent = nullptr);
    void randfood(QVector<int> sx,QVector<int> sy,bool isWall[][40]);    //随机产生食物坐标
    int getfoodX()const;     //返回食物坐标
    int getfoodY()const;
    void setfoodPos(int _x,int _y);
};
#endif // FOOD_H
