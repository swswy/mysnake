#include "food.h"
#include <ctime>

Food::Food(QWidget *parent) : QMainWindow(parent)
{
}

//随机产生食物坐标
void Food::randfood(QVector<int> sx,QVector<int> sy,bool isWall[][40]){
    srand((unsigned)time(NULL));
    bool needagain=true;
    while (needagain) {
        int tem1=rand()%40;
        int tem2=rand()%40;
        if(isWall[tem1][tem2]) continue;
        needagain=false;
        foodx = (tem1 + 1) * mysize+Margin;
        foody = (tem2 + 1)* mysize+Margin;

        for(int i=0;i<sx.size();++i){
            if(sx[i]==foodx&&sy[i]==foody){
                needagain=true;
                break;
            }
        }
    }
    return;

}

//获取食物的坐标
int Food::getfoodX() const{
    return foodx;
}

int Food::getfoodY() const{
    return foody;
}
void Food::setfoodPos(int _x, int _y){
    foodx=_x;
    foody=_y;
}
