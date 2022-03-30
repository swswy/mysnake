#include "snake.h"

Snake::Snake(QWidget *parent) : QMainWindow(parent){

    SnakeNode snakenode;            //临时结构变量用于创建蛇
    for (int i = 1; i >= 0; i--)	//从右向左创建5节蛇身，容器的第一个元素为蛇头
    {
        snakenode.x = mysize * 20 + i * mysize+Margin;//每个格子宽mysize像素
        snakenode.y = mysize * 20+Margin;
        snakevec.push_back(snakenode);//将蛇节点插入到数组中
    }
}
inline void Snake::DeteDirMove(char key, SnakeNode &nexthead)
{
    switch (key){
    case 'w':
        //新蛇头坐标根据旧蛇头坐标改变
        nexthead.x = snakevec.front().x;
        nexthead.y = snakevec.front().y - mysize;
        break;
    case 's':
        nexthead.x = snakevec.front().x;
        nexthead.y = snakevec.front().y + mysize;
        break;
    case 'a':
        nexthead.x = snakevec.front().x - mysize;
        nexthead.y = snakevec.front().y;
        break;
    case 'd':
        nexthead.x = snakevec.front().x + mysize;
        nexthead.y = snakevec.front().y;
    }
}

//蛇移动主要函数
void Snake::Move(char key){
    SnakeNode nexthead;  //创建一个新的蛇头

    DeteDirMove(key, nexthead);  //确定新蛇头的位置

    snakevec.insert(snakevec.begin(), nexthead);    //将新蛇头插入到容器头部
}

//重置蛇函数
void Snake::Reset(){
    snakevec.clear();   //清空容器

    //初始化蛇
    SnakeNode snakenode;
    for (int i = 1; i >= 0; i--){
        snakenode.x = mysize * 20 + i * mysize+Margin;
        snakenode.y = mysize * 20 + Margin;
        snakevec.push_back(snakenode);
    }
}
QVector<int> Snake::snakex(){
    QVector<int> temp;
    for(auto snakei:snakevec){
        temp.push_back(snakei.x);
    }
    return temp;
}
QVector<int> Snake::snakey(){
    QVector<int> temp;
    for(auto snakei:snakevec){
        temp.push_back(snakei.y);
    }
    return temp;
}
void Snake::setData(QVector<int> &tx, QVector<int> &ty){
    SnakeNode loadnode;
    snakevec.clear();
    for(int i=0;i<tx.size();++i){
        loadnode.x=tx[i];
        loadnode.y=ty[i];
        snakevec.push_back(loadnode);
    }
    return;

}
