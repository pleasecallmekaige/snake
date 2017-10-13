#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>//kbhit()键盘响应
#include<windows.h>//pos坐标

using namespace std;
#define W 30 //游戏界面的宽度
#define H 25 //游戏界面的高度

typedef char int8;
typedef short int int16;
typedef long int int32;   //int
typedef long long int64;
typedef float  f4;
typedef double d8;
//    cout<<"int      ="<<sizeof(int)<<endl;
//    cout<<"char     ="<<sizeof(char)<<endl;
//    cout<<"short int="<<sizeof(int16)<<endl;
//    cout<<"long int ="<<sizeof(int32)<<endl;
//    cout<<"long long="<<sizeof(int64)<<endl;
//    cout<<"float    ="<<sizeof(f4)<<endl;
//    cout<<"double   ="<<sizeof(d8)<<endl;

void gotoxy(int x, int y)
{
COORD pos = {x,y};
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleCursorPosition(hOut, pos);
}
//隐藏光标
void hidden()
{
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO cci;
GetConsoleCursorInfo(hOut,&cci);
cci.bVisible=0;//赋1为显示，赋0为隐藏
SetConsoleCursorInfo(hOut,&cci);
}
char GetKeybutton()//获取按键
{
    char direction;
    while(kbhit()!=0)
    {
        direction=getch();
    }
    return direction;
}

void dis_point(int32 x,int32 y)
{
   gotoxy(2*x, y);
   cout<<"■"<<endl;
}
void earse_point(int32 x,int32 y)
{
   gotoxy(2*x, y);
   cout<<" "<<endl;
}

int32 foodrand(char a)//生成食物随机数
{
    int32 b;
    if(a=='W')
    {
        return 1 + (int)(W-2) * rand() / (RAND_MAX + 1);;
    }
    else if(a=='H')
    {
        return 1 + (int)(H-2) * rand() / (RAND_MAX + 1);
    }
}
class Food;
class Snake;
/***************************myPoint 类**************************/
class myPoint
{
public:
    myPoint()//构造函数
    {
        X=0;Y=0;
    }
    myPoint(int32 x,int32 y)//构造函数
    {
        X=x;Y=y;
        dis_point(X,Y);
    }
    void Moveto(int32 x=0,int32 y=0)//点的移动
    {
        earse_point(X,Y);
        X=x;Y=y;
        dis_point(X,Y);
    }
    void Erase()//点的擦除
    {
        earse_point(X,Y);
    }
    int32 GetX()//获取x轴坐标
    {
        return X;
    }
    int32 GetY()//获取y轴坐标
    {
        return Y;
    }
    void operator=(const myPoint &p);
    int8 operator==(const myPoint &p);
    int8 operator==(const Food &p);
    int8 operator<(int32 x[]);
    //friend void dis_point(int32 x,int32 y);
    friend class Snake;
    friend class Food;
private:
    int32 X,Y;
};
/***************************Food 类**************************/
class Food:public myPoint
{
public:
    Food()
    {
        food_X=W/2;
        food_Y=H/2;
        num_count=0;
        Moveto(food_X,food_Y);
    }
    int8 creatnewfood(const Snake &snake);
    void Moveto(int32 x=0,int32 y=0)
    {
        food_X=x;food_Y=y;
        dis_point(food_X,food_Y);
    }
    int32 GetfoodX()
    {
        return food_X;
    }
    int32 GetfoodY()
    {
        return food_Y;
    }
    int32 Getcount()
    {
        return num_count;
    }
    int8 operator==(const myPoint &p);
    //friend int32 foodrand(char a);
    friend class Snake;
    friend class myPoint;
private:
    int32 food_X,food_Y,num_count;
};
/***************************Snake 类**************************/
class Snake
{
public:
    Snake();//构造函数 初始化蛇的位置固定不变
    Snake(int32 longg,char direction);//构造函数 初始化长度和方向可变
    int32 Get_long()//获取蛇的长度
    {
        return Snake_long;
    }
    char Get_direction()//获取蛇的前进方向
    {
        return Snake_direction;
    }
    int32 Get_snakepoint_coordinate(int32 position,char axis);//获取蛇身点位置position：位置  axis：坐标（取值只能为'x'和'y'） 例如 Get_snakepoint_coordinate(5,'x'),第5个点的x坐标值
    void  Turnaround();//转向
    void  Moveforward();//蛇前进
    int8  eatfood(const Food &food);//蛇吃食物生长
    friend int8 Impact_checking(const Snake &snake);
    //friend int8 Food::creatnewfood(const Snake &snake);
    //friend char GetKeybutton();//友元
    friend class Food;
private:
    void  Moveforward_R();
    void  Moveforward_L();
    void  Moveforward_U();
    void  Moveforward_D();
    myPoint Snake_point[W*H];
    int32 Snake_headposition,Snake_tailposition;
    char Snake_direction;
    int32 Snake_long;
};

/***************************myPoint 类的函数**************************/
void myPoint::operator=(const myPoint &p)
{
    this->X=p.X;
    this->Y=p.Y;
}
int8 myPoint::operator==(const myPoint &p)
{
    if( this->X==p.X&&this->Y==p.Y)
        return 1;
    else return 0;
}
int8 myPoint::operator==(const Food &p)
{
    if(this->X==p.food_X&&this->Y==p.food_Y)
        return 1;
    else return 0;
}
int8 myPoint::operator<(int32 x[])
{
    if(this->X>x[0]&&this->X<x[1]&&this->Y>x[2]&&this->Y<x[3])
        return 1;
    else return 0;
}
/***************************Snake 类的函数**************************/
Snake::Snake()//构造函数 初始化蛇的位置固定不变
{
    Snake_long=4;
    Snake_direction='d';
    for(int32 i=0;i<Snake_long;i++)
    {
        Snake_point[i].Moveto(1+i,5);
    }
    Snake_headposition=Snake_long-1;
    Snake_tailposition=0;
}
Snake::Snake(int32 longg,char direction)//构造函数 初始化长度和方向可变
{
    Snake_long=longg;
    Snake_direction=direction;
    for(int32 i=0;i<Snake_long;i++)
    {
        Snake_point[i].Moveto(1+i,5);
    }
    Snake_headposition=Snake_long-1;
    Snake_tailposition=0;
}
int32 Snake::Get_snakepoint_coordinate(int32 position,char axis)//获取蛇身点位置position：位置  axis：坐标（取值只能为'x'和'y'） 例如 Get_snakepoint_coordinate(5,'x'),第5个点的x坐标值
{
    if(position>Snake_long)
    {
        gotoxy(5, 3);
        cout<<"out of snake range"<<endl;
        return -1;
    }
    if(axis=='x')
        return Snake_point[position].GetX();
    else
        return Snake_point[position].GetY();
}
void Snake::Turnaround()//转向
{
    char d;
    d=GetKeybutton();
    if(Snake_direction=='a'&&(d=='s'|d=='w'))
        Snake_direction=GetKeybutton();
    else if(Snake_direction=='s'&&(d=='a'|d=='d'))
        Snake_direction=GetKeybutton();
    else if(Snake_direction=='d'&&(d=='s'|d=='w'))
        Snake_direction=GetKeybutton();
    else if(Snake_direction=='w'&&(d=='a'|d=='d'))
        Snake_direction=GetKeybutton();
}
void Snake::Moveforward_R()
{
    int32 last_head_x,last_head_y;
    myPoint *p=new myPoint;
//    gotoxy(0, 0);
//    for(int32 i=0;i<8;i++)
//    cout<<Get_snakepoint_coordinate(i,'x')<<endl;
    last_head_x=Get_snakepoint_coordinate(Snake_headposition,'x');
    last_head_y=Get_snakepoint_coordinate(Snake_headposition,'y');
    Snake_point[Snake_tailposition].Moveto(last_head_x+1,last_head_y);
    *p=Snake_point[Snake_tailposition];
    for(int32 i=Snake_tailposition;i<Snake_headposition;i++)
    {
        Snake_point[i]=Snake_point[i+1];
    }
    Snake_point[Snake_headposition]=*p;
    delete p;
//    gotoxy(0, 9);
//    for(int32 i=0;i<8;i++)
//    cout<<Get_snakepoint_coordinate(i,'x')<<endl;
}
void Snake::Moveforward_D()
{
    int32 last_head_x,last_head_y;
    myPoint *p=new myPoint;
    last_head_x=Get_snakepoint_coordinate(Snake_headposition,'x');
    last_head_y=Get_snakepoint_coordinate(Snake_headposition,'y');
    Snake_point[Snake_tailposition].Moveto(last_head_x,last_head_y+1);
    *p=Snake_point[Snake_tailposition];
    for(int32 i=Snake_tailposition;i<Snake_headposition;i++)
    {
        Snake_point[i]=Snake_point[i+1];
    }
    Snake_point[Snake_headposition]=*p;
    delete p;
}
void Snake::Moveforward_U()
{
    int32 last_head_x,last_head_y;
    myPoint *p=new myPoint;
    last_head_x=Get_snakepoint_coordinate(Snake_headposition,'x');
    last_head_y=Get_snakepoint_coordinate(Snake_headposition,'y');
    Snake_point[Snake_tailposition].Moveto(last_head_x,last_head_y-1);
    *p=Snake_point[Snake_tailposition];
    for(int32 i=Snake_tailposition;i<Snake_headposition;i++)
    {
        Snake_point[i]=Snake_point[i+1];
    }
    Snake_point[Snake_headposition]=*p;
    delete p;
}
void Snake::Moveforward_L()
{
    int32 last_head_x,last_head_y;
    myPoint *p=new myPoint;
    last_head_x=Get_snakepoint_coordinate(Snake_headposition,'x');
    last_head_y=Get_snakepoint_coordinate(Snake_headposition,'y');
    Snake_point[Snake_tailposition].Moveto(last_head_x-1,last_head_y);
    *p=Snake_point[Snake_tailposition];
    for(int32 i=Snake_tailposition;i<Snake_headposition;i++)
    {
        Snake_point[i]=Snake_point[i+1];
    }
    Snake_point[Snake_headposition]=*p;
    delete p;
}
void Snake::Moveforward()
{
    Turnaround();
    switch(Snake_direction)
    {
        case 'd':Moveforward_R();break;
        case 's':Moveforward_D();break;
        case 'w':Moveforward_U();break;
        case 'a':Moveforward_L();break;
        default:break;
    }
}
int8 Snake::eatfood(const Food &food)//蛇吃食物生长
{
//    gotoxy(0, 26);
//    cout<<food.food_X<<" , "<<food.food_Y<<"  "<<endl;
//    cout<<Snake_point[Snake_headposition].GetX()<<" , "<<Snake_point[Snake_headposition].GetY()<<"  "<<endl;
    int32 last_tail_x,last_tail_y,second_tail_x,second_tail_y;
    if(Snake_point[Snake_headposition]==food)
    {
//        gotoxy(0, 25);
//        cout<<"eat"<<endl;
        myPoint *p=new myPoint;
        last_tail_x=Get_snakepoint_coordinate(Snake_tailposition,'x');
        last_tail_y=Get_snakepoint_coordinate(Snake_tailposition,'y');
        second_tail_x=Get_snakepoint_coordinate(Snake_tailposition+1,'x');
        second_tail_y=Get_snakepoint_coordinate(Snake_tailposition+1,'y');
        Snake_long++;
        Snake_headposition++;
        Snake_point[Snake_headposition].Moveto(last_tail_x+(last_tail_x-second_tail_x),last_tail_y+(last_tail_y-second_tail_y));
        *p=Snake_point[Snake_headposition];
        for(int32 i=Snake_headposition;i>0;i--)
        {
            Snake_point[i]=Snake_point[i-1];
        }
        Snake_point[Snake_tailposition]=*p;
        delete p;
        return 1;
    }
    return 0;
}
/*********************************Food 类的函数****************************************/
int8 Food::creatnewfood(const Snake &snake)
{
    food_X=foodrand('W');
    food_Y=foodrand('H');
    Moveto(food_X,food_Y);
    for(int32 i=0;i<snake.Snake_headposition;i++)
    {
        if((*this)==snake.Snake_point[i])
        {
            return 1;
        }
    }
    num_count++;
    return 0;
}
int8 Food::operator==(const myPoint &p)
{
    if(this->food_X==p.X&&this->food_Y==p.Y)
        return 1;
    else return 0;
}

void creatGameinterface()//创建游戏界面
{
    int32 i,j;
    myPoint Boundary_point[W*2+H*2-4];
    for(i=0;i<W-1;i++)
       Boundary_point[i].Moveto(i,0);
    for(i=0;i<H-1;i++)
       Boundary_point[i+W-1].Moveto(W-1,i);
    for(i=0;i<W-1;i++)
       Boundary_point[i+W+H-2].Moveto(i+1,H-1);
    for(i=0;i<H-1;i++)
       Boundary_point[i+W*2+H-3].Moveto(0,i+1);
}

int8 Impact_checking(const Snake &snake)//检测蛇是否死亡
{
    myPoint *p=new myPoint;
    int32 x[4]={0,W-1,0,H-1};
    *p=snake.Snake_point[snake.Snake_headposition];
    for(int32 i=0;i<snake.Snake_headposition-2;i++)
    {
        if(*p==snake.Snake_point[i] || !(*p<x) )
        {
            delete p;
            return 1;
        }
    }
    delete p;
    return 0;
}
void Init()
{
    srand((unsigned)time(0));//随机种子
    gotoxy(0, 15);
    cout<<"         按任意键继续，记得把输入法调成英文，w:上  s:下  a:左  d:右            "<<endl;
    while(1)
    {
        if(kbhit()!=0)
            break;
    }
    gotoxy(0, 15);
    cout<<"                                                                               "<<endl;
    creatGameinterface();//创建游戏界面
}


int main()
{
    Init();
    Snake snake(4,'d');//生成一个长度为4，方向向右的蛇
    Food food;//生成一个食物
    while(1)
    {
        snake.Moveforward();//蛇的前进
        if(snake.eatfood(food))//蛇是否吃到食物 吃到返回1 否则返回0
            while(food.creatnewfood(snake));//吃到食物 生成下一个食物 食物不能生成到蛇的身上
        if(Impact_checking(snake))//检测蛇是否死亡
            break;//死亡则退出游戏
        Sleep(400);//延时
    }
    //GAME OVER界面
    gotoxy(0, 15);
    cout<<"                           GAME OVER                                  "<<endl;
    cout<<"                           你的得分是："<<food.Getcount()<<endl;
    cin.get();
    return   0;
}
