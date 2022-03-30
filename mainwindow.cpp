#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),timer(new QTimer(this))
{
    ui->setupUi(this);
    setFixedSize(1200,950);

    //监听七个按钮
    connect(ui->btnStart,&QPushButton::clicked,[=](){
        food.randfood(snake.snakex(),snake.snakey(),isWall);
        update();
        gameStarted();
    });
    connect(ui->start,&QAction::triggered,[=](){
        food.randfood(snake.snakex(),snake.snakey(),isWall);
        update();
        gameStarted();
    });
    connect(ui->btnRestart,&QPushButton::clicked,[=](){
        notStarted();
        update();
    });
    connect(ui->restart,&QAction::triggered,[=]{
        notStarted();
        update();
    });
    connect(ui->btnPause,&QPushButton::clicked,this,&MainWindow::gamePaused);connect(ui->pause,&QAction::triggered,this,&MainWindow::gamePaused);
    connect(ui->btnCon,&QPushButton::clicked,this,&MainWindow::gameStarted); connect(ui->con,&QAction::triggered,this,&MainWindow::gameStarted);
    connect(ui->btnQuit,&QPushButton::clicked,this,&MainWindow::close);      connect(ui->quit,&QAction::triggered,this,&MainWindow::close);
    connect(ui->btnSave,&QPushButton::clicked,this,&MainWindow::writeData);  connect(ui->save,&QAction::triggered,this,&MainWindow::writeData);
    connect(ui->btnLoad,&QPushButton::clicked,this,&MainWindow::readData);   connect(ui->load,&QAction::triggered,this,&MainWindow::readData);

    //绑定计时器
    connect(timer,&QTimer::timeout,[=](){
        snake.Move(key);    //蛇移动函数
        dist++;
        //吃到食物的情况
        if(reward>0||(food.getfoodX() == snake.snakevec.at(0).x && food.getfoodY() == snake.snakevec.at(0).y)){
            //随机产生一个食物坐标
            if((food.getfoodX() == snake.snakevec.at(0).x && food.getfoodY() == snake.snakevec.at(0).y)){
                food.randfood(snake.snakex(),snake.snakey(),isWall);
                if(reward==0){
                    snake.snakevec.pop_back();
                    reward+=3;
                    ui->label->setText(QString::number(dist));
                    update();
                    return;
                }
                reward+=3;
            }
            if(reward>0){
                reward--;
            }
        }
        else{
            snake.snakevec.pop_back();   //删除蛇尾
        }
        GameOver();    //游戏失败的情况
        update();      //调用绘图函数
        //更新标签控件的文本内容
        ui->label->setText(QString::number(dist));
        return;
    });
        notStarted();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::notStarted(){
    reward=0;
    snake.Reset();      //重置蛇
    dist = 0;          //得分清0
    key = 'd';          //key值向右
    timer->stop();//重置定时器
    gameflag = false;   //重置游戏结束标志
    for(int i=0;i<40;++i)
        for(int j=0;j<40;++j)
           isWall[i][j]=false;
    gamestart=false;    //游戏是否是未开始状态
    bugflag=false;
    food.setfoodPos(0,0);
    ui->label->setText(QString::number(dist));

    this->ui->btnLoad->setEnabled(true); this->ui->load->setEnabled(true);
    this->ui->btnStart->setEnabled(true); this->ui->start->setEnabled(true);
    this->ui->btnQuit->setEnabled(true); this->ui->quit->setEnabled(true);
    this->ui->btnPause->setEnabled(false); this->ui->pause->setEnabled(false);
    this->ui->btnCon->setEnabled(false); this->ui->con->setEnabled(false);
    this->ui->btnRestart->setEnabled(false); this->ui->restart->setEnabled(false);
    this->ui->btnSave->setEnabled(false); this->ui->save->setEnabled(false);
}
void MainWindow::gameStarted(){

    timer->start(timerspeed);
    gamestart=true;

    this->ui->btnLoad->setEnabled(false);  this->ui->load->setEnabled(false);
    this->ui->btnStart->setEnabled(false); this->ui->start->setEnabled(false);
    this->ui->btnQuit->setEnabled(true);   this->ui->quit->setEnabled(true);
    this->ui->btnPause->setEnabled(true);  this->ui->pause->setEnabled(true);
    this->ui->btnCon->setEnabled(false);   this->ui->con->setEnabled(false);
    this->ui->btnRestart->setEnabled(false);this->ui->restart->setEnabled(false);
    this->ui->btnSave->setEnabled(false);  this->ui->save->setEnabled(false);
}
void MainWindow::gamePaused(){
    timer->stop();
    ui->label->setText(QString::number(dist));

    this->ui->btnLoad->setEnabled(false); this->ui->load->setEnabled(false);
    this->ui->btnStart->setEnabled(false); this->ui->start->setEnabled(false);
    this->ui->btnQuit->setEnabled(true);   this->ui->quit->setEnabled(true);
    this->ui->btnPause->setEnabled(false); this->ui->pause->setEnabled(false);
    this->ui->btnCon->setEnabled(true);    this->ui->con->setEnabled(true);
    this->ui->btnRestart->setEnabled(true);this->ui->restart->setEnabled(true);
    this->ui->btnSave->setEnabled(true);   this->ui->save->setEnabled(true);
}
void MainWindow::gameTermination(){
    gameflag=true;
    timer->stop();  //暂停定时器

    this->ui->btnLoad->setEnabled(false);  this->ui->load->setEnabled(false);
    this->ui->btnStart->setEnabled(false); this->ui->start->setEnabled(false);
    this->ui->btnQuit->setEnabled(true);   this->ui->quit->setEnabled(true);
    this->ui->btnPause->setEnabled(false); this->ui->pause->setEnabled(false);
    this->ui->btnCon->setEnabled(false);   this->ui->con->setEnabled(false);
    this->ui->btnRestart->setEnabled(true);this->ui->restart->setEnabled(true);
    this->ui->btnSave->setEnabled(false);  this->ui->save->setEnabled(false);
}
void MainWindow::GameOver(){
    //撞墙失败
    if(snake.snakevec.at(0).x >= 41 * mysize+Margin || snake.snakevec.at(0).x <= Margin ||
       snake.snakevec.at(0).y <= Margin || snake.snakevec.at(0).y >= 41 * mysize+Margin){    
        gameTermination();
        return;
    }

    //撞自己失败
    for(int i = 1; i < snake.snakevec.size(); i++){
        if(snake.snakevec.at(0).x == snake.snakevec.at(i).x &&
           snake.snakevec.at(0).y == snake.snakevec.at(i).y){
            gameTermination();
            return;
        }
    }
    //撞着障碍物失败
    //可以这样，遍历所有，如果有的地方的节点的值是true的话，就失败了
    for(int i = 0;i<snake.snakevec.size();++i){
        int x=(snake.snakevec[i].x-Margin)/mysize-1;
        int y=(snake.snakevec[i].y-Margin)/mysize-1;
        if(isWall[x][y]){
            gameTermination();
            return;
        }
    }
}
void MainWindow::paintEvent(QPaintEvent *event){

      QPainter wallPainter(this);
      QBrush wallBrush(QColor(128,64,0));
      wallPainter.setBrush(wallBrush);

      for (int i=0;i<41;++i){
           wallPainter.drawRect(Margin,Margin+i*mysize,mysize,mysize);
           wallPainter.drawRect(Margin+i*mysize,Margin+41*mysize,mysize,mysize);
           wallPainter.drawRect(Margin+41*mysize,Margin+(41-i)*mysize,mysize,mysize);
           wallPainter.drawRect(Margin+(41-i)*mysize,Margin,mysize,mysize);
      }
      for (int i=0;i<40;++i){
           for(int j=0;j<40;++j){
               if(isWall[i][j]){
                   wallPainter.drawRect(Margin+(i+1)*mysize,Margin+(j+1)*mysize,mysize,mysize);
               }
           }
      }
      //创建画家对象，指定绘图设备为this主窗口
      QPainter painter(this);
      //设置画刷为红色
      QBrush brush1(QColor(214,194,121));
      painter.setBrush(brush1);
      //画食物
      if(food.getfoodX()!=0){
          painter.drawRect(QRect(food.getfoodX(),food.getfoodY(),mysize,mysize));
        }
      //设置画刷为黑色
      QBrush brush2(QColor(150,185,125));
      painter.setBrush(brush2);

      //遍历蛇坐标容器，画出代表蛇身的矩形
      for(auto snakenodei : snake.snakevec)
          (snakenodei.x == snake.snakevec.at(0).x &&
           snakenodei.y == snake.snakevec.at(0).y) ?
          //蛇头画圆形
          painter.setRenderHint(QPainter::Antialiasing),  //用抗锯齿画圆
          painter.drawEllipse(QPoint(snakenodei.x + 10,snakenodei.y + 10),10,10):
          //蛇身画矩形
          painter.drawRect(QRect(snakenodei.x,snakenodei.y,mysize,mysize));

      bugflag = false;    //在画出蛇之后将标志设为假
      if(gameflag){   //设置文字属性
          QFont font("楷体", 80, QFont::Bold, false);
          painter.setFont(font);      //使用字体
          painter.drawText(QRect(350, 350, 1000, 500), "游戏结束");   //画出游戏结束文字
      }
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(bugflag)     //bug标志为真直接返回
        return;
    switch (event->key())
    {
    case Qt::Key_I:
        if(key != 's'){   //按下与当前方向相反按键时break
        key = 'w';
        bugflag = true;   //按键之后将标志设为真
        }
        break;
    case Qt::Key_K:
        if(key != 'w'){
        key = 's';
        bugflag = true;
        }
        break;
    case Qt::Key_J:
        if(key != 'd'){
        key = 'a';
        bugflag = true;
        }
        break;
    case Qt::Key_L:
        if(key != 'a'){
        key = 'd';
        bugflag = true;
        }
        break;
    default:
        break;
    }
    return;
}
void MainWindow::mousePressEvent(QMouseEvent *event){
    if(gamestart) return;
    if(event->button()!=Qt::LeftButton){
        return;
    }
    int x=(event->x()-Margin)/mysize-1;
    int y=(event->y()-Margin)/mysize-1;
    if(x>=0&&x<40&&y>=0&&y<40){
        isWall[x][y]^=true;
        update();
    }
    return;
}
void MainWindow::readData(){
    QString path=QFileDialog::getOpenFileName(this,"open","../","MDAT(*.mdat)");
    if(path.isEmpty()==false){
        QFile file(path);
        //只读方式打开
        bool isOK=file.open(QIODevice::ReadOnly);
        if(isOK){
            //读文件
            QByteArray array;
            //读食物位置
            array=file.readLine();
            QString str(array.data());
            if(str!="FOOD\n"){
                QMessageBox::warning(this,"Error","please open mdat file",QMessageBox::Ok,QMessageBox::Cancel);
            }
            int a[2];
            for (int i=0;i<2;++i) {
                array=file.readLine();
                a[i]=array.toInt();
            }
            food.setfoodPos(a[0],a[1]);

            //读用户自定义的墙的数据
            array=file.readLine();
            while(1){
                array=file.readLine();
                str=array;
                if(str=="SNAKE\n") break;
                QStringList templist=str.split(" ", QString::SkipEmptyParts);
                int t[2];
                for (int i = 0; i < templist.size(); ++i)
                      t[i]=templist.at(i).toInt();
                isWall[t[0]][t[1]]=true;

            }
            //读蛇的位置
            QVector<int> tx,ty;
            array=file.readLine();
            str=array;
            QStringList tempx=str.split(" ",QString::SkipEmptyParts);
            for (int i=0;i<tempx.size();++i) {
                tx.push_back(tempx.at(i).toInt());
            }
            array=file.readLine();
            str=array;
            QStringList tempy=str.split(" ",QString::SkipEmptyParts);
            for (int i=0;i<tempy.size();++i) {
                ty.push_back(tempy.at(i).toInt());
            }
            snake.setData(tx,ty);
            //读取时间
            array=file.readLine();
            dist=array.toInt();
            //读取reward
            array=file.readLine();
            reward=array.toInt();
            //读取前行的方向
            array=file.readLine();
            key=*array.data();
        }
        file.close();
        gamePaused();
    }

    update();
    return;
}
void MainWindow::writeData(){
    QString path=QFileDialog::getSaveFileName(this,"save","../","MDAT(*.mdat)");
    if(path.isEmpty()==false){
        QFile file(path);
        bool isOK=file.open(QIODevice::WriteOnly);
        if(isOK){
            QString str;
            str=str+"FOOD"+"\n"+QString::number(food.getfoodX())+"\n"+QString::number(food.getfoodY())+"\n";
            str+="ISWALL\n";
            QString temp;
            for(int i=0;i<40;++i){
                for(int j=0;j<40;++j){
                    if(isWall[i][j]){
                        temp+=(QString::number(i)+" "+QString::number(j)+"\n");
                    }
                }
            }
            QVector<int> tempx(snake.snakex()),tempy(snake.snakey());
            QString temp1,temp2;
            for(auto x:tempx)
                temp1+=(QString::number(x)+" ");
            for(auto y:tempy)
                temp2+=(QString::number(y)+" ");
            temp1.remove(temp1.size()-1,1);
            temp2.remove(temp2.size()-1,1);
            str=str+temp+"SNAKE\n"+temp1+"\n"+temp2+"\n"+ui->label->text()+"\n"+QString::number(reward)+"\n"+key;
            file.write(str.toUtf8());
        }
        file.close();
    }
}
