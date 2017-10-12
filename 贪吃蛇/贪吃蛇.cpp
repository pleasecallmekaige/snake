#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>//kbhit()������Ӧ
#include<windows.h>//pos����

using namespace std;
#define W 30 //��Ϸ����Ŀ��
#define H 25 //��Ϸ����ĸ߶�

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
//���ع��
void hidden()
{
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO cci;
GetConsoleCursorInfo(hOut,&cci);
cci.bVisible=0;//��1Ϊ��ʾ����0Ϊ����
SetConsoleCursorInfo(hOut,&cci);
}
char GetKeybutton()//��ȡ����
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
   cout<<"��"<<endl;
}
void earse_point(int32 x,int32 y)
{
   gotoxy(2*x, y);
   cout<<" "<<endl;
}

class myPoint
{
public:
    myPoint()//���캯��
    {
        X=0;Y=0;
    }
    myPoint(int32 x,int32 y)//���캯��
    {
        X=x;Y=y;
        dis_point(X,Y);
    }
    void Moveto(int32 x=0,int32 y=0)//����ƶ�
    {
        earse_point(X,Y);
        X=x;Y=y;
        dis_point(X,Y);
    }
    void Erase()//��Ĳ���
    {
        earse_point(X,Y);
    }
    int32 GetX()//��ȡx������
    {
        return X;
    }
    int32 GetY()//��ȡy������
    {
        return Y;
    }
    void operator=(const myPoint &p);
    friend void dis_point(int32 x,int32 y);
private:
    int32 X,Y;
};
void myPoint::operator=(const myPoint &p)
{
    this->X=p.X;
    this->Y=p.Y;
}
class Snake
{
public:
    Snake();//���캯�� ��ʼ���ߵ�λ�ù̶�����
    Snake(int32 longg,char direction);//���캯�� ��ʼ�����Ⱥͷ���ɱ�
    int32 Get_long()//��ȡ�ߵĳ���
    {
        return Snake_long;
    }
    char Get_direction()//��ȡ�ߵ�ǰ������
    {
        return Snake_direction;
    }
    int32 Get_snakepoint_coordinate(int32 position,char axis);//��ȡ�����λ��position��λ��  axis�����꣨ȡֵֻ��Ϊ'x'��'y'�� ���� Get_snakepoint_coordinate(5,'x'),��5�����x����ֵ
    void  Turnaround();//ת��
    void  Moveforward();//��ǰ��
//    void  length()//������
//    {
//        Snake_long++;
//        Snake_headposition++;
//        Snake_point[Snake_headposition]=food;
//    }
    friend char GetKeybutton();//��Ԫ
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
Snake::Snake()//���캯�� ��ʼ���ߵ�λ�ù̶�����
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
Snake::Snake(int32 longg,char direction)//���캯�� ��ʼ�����Ⱥͷ���ɱ�
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
int32 Snake::Get_snakepoint_coordinate(int32 position,char axis)//��ȡ�����λ��position��λ��  axis�����꣨ȡֵֻ��Ϊ'x'��'y'�� ���� Get_snakepoint_coordinate(5,'x'),��5�����x����ֵ
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
void Snake::Turnaround()//ת��
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
//void  Snake::length()
//{
//
//}
void creatGameinterface()//������Ϸ����
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

int32 foodrand(char a)//����ʳ�������
{
    int32 b;
    if(a=='W')
    {
        return 1 + (int)(W-1) * rand() / (RAND_MAX + 1);;
    }
    else if(a=='H')
    {
        return 1 + (int)(H-1) * rand() / (RAND_MAX + 1);
    }
}
class Food:public myPoint
{
public:
    Food()
    {
        Moveto(20,20);
    }
    void creatnewfood()
    {
        food_X=foodrand('W');
        food_Y=foodrand('H');
        Moveto(food_X,food_Y);
    }
    int32 GetfoodX()
    {
        return food_X;
    }
    int32 GetfoodY()
    {
        return food_Y;
    }
    friend int32 foodrand(char a);
    friend class Snake;
private:
    int32 food_X,food_Y;
};




int main()
{
//    int i;
//    Food food;
//    srand((unsigned)time(0));
//    while(1)
//    {
//        food.creatnewfood();
//        Sleep(600);
//        gotoxy(0, 28);
//        cout<<food.GetX()<<","<<food.GetY()<<endl;
//        cout<<food.GetfoodX()<<","<<food.GetfoodY()<<endl;
//    }
    myPoint point(8,244);
    return   0;
}
//int main()
//{
////    char now_direction;
//    creatGameinterface();
//    Snake snake(8,'d');
////    cout<<snake.Get_long()<<endl;
////    cout<<snake.Get_direction()<<endl;
////    cout<<snake.Get_snakepoint_coordinate(3,'y')<<endl;
////    now_direction=GetKeybutton();
////    cout<<now_direction<<endl;
////    snake.Moveforward_R();
////    snake.Moveforward_R();
////    snake.Moveforward_R();
////    snake.Moveforward_U();
////    snake.Moveforward_U();
////    snake.Moveforward_L();
//    while(1)
//    {
//        snake.Moveforward();
//
//        Sleep(600);
//    }
//
//    gotoxy(0, 28);
//    system("PAUSE");
//
//    return 0;
//}
