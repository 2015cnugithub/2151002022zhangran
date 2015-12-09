/*在visual studio2013可以运行。
小车可以再图形框中循环移动。
可以按着<+>键一直加速，但是当速度过大时，小车会停止移动，需要重新输入<S>键方可移动。*/

#include<graphics.h>
#include <conio.h>
#include <dos.h>
#include <iostream>
#include<stdio.h>
#include<Windows.h>
using namespace std;

enum TYPE { CIRCLE, RECTANGLE, TRIANGLE };//枚举TYPE

class FigureLink;//声明图形链表

class Figure
{
	friend class FigureLink;//友元类
protected:
	TYPE type;//type是Figure中的成员
	int center_x, center_y;//绘制图形的中心
	static Figure *p;//指向将要插入链表的图形绘制对象
	Figure *next;//指向链表中的下一个图形绘制对象
public:
	Figure(int x, int y, TYPE tp)//绘制图形，输入参数为坐标和图形类型
	{
		center_x = x;//横坐标
		center_y = y;//纵坐标
		type = tp;//图形类型
		next = 0;//指向下一个图形绘制对象
	}
	virtual void DrawPic() = 0;//图形绘制操作的接口规则,虚函数，继承以后由子类具体定义
	virtual void Insert() = 0;//图形绘制类对象插入链表的接口规则，虚函数，继承以后由子类具体定义
	void Hide();//隐藏图形
	void Move();//图形移动
};

Figure *Figure::p = 0;//将要插入链表的图形绘制对象指向0

void Figure::Hide()//隐藏图形
{
	unsigned int sc = getcolor();//颜色设置
	setcolor(BLACK);//设置为黑色即可隐藏图形
	DrawPic();//画图
	setcolor(sc);//设置颜色
}

void Figure::Move()//图形移动
{
	unsigned int sc = getcolor();
	setcolor(BLACK);//设置颜色为黑，然后画图
	DrawPic();
	setcolor(sc);
	center_x += 1;//x坐标+1即可实现移动
	center_x = center_x % 625;//使中心坐标模625，即可使图形回到原来的起始位置，从而循环移动
	DrawPic();
}

//圆形类，圆类Circle继承Figure
class Circle :public Figure	
{
private:
	int radius;//半径
public:
	Circle(int x, int y, int r) :Figure(x, y, CIRCLE)
	{
		radius = r;
	}
	void DrawPic();
	void Insert();
};

void Circle::DrawPic()
{
	circle(center_x, center_y, radius);//画圆
}

void Circle::Insert()
{
	Figure::p = new Circle(center_x, center_y, radius);//插入圆的对象
}

//矩形类Rect继承了Figure类
class Rect :public Figure
{
private:
	int width;
	int length;
public:
	Rect(int w, int l, int x, int y) :Figure(x, y, RECTANGLE)//构造函数
	{
		width = w;
		length = l;
	}
	void DrawPic();
	void Insert();
};

void Rect::DrawPic()
{
	rectangle(center_x - width / 2, center_y - length / 2, center_x + width / 2, center_y + length / 2);//画矩形
}

void Rect::Insert()//插入矩形对象
{
	Figure::p = new Rect(width, length, center_x, center_y);
}

//三角形Triangle类继承了Figure类
class Triangle :public Figure	
{
private:
	int RightAngleFlag;//角度
	int bottomSide;//底
	int height;//高
public:
	Triangle(int b, int h, int flag, int x, int y) :Figure(x, y, TRIANGLE)
	{
		bottomSide = b;
		height = h;
		RightAngleFlag = flag;
	}
	void DrawPic();
	void Insert();
};

//画三角形
void Triangle::DrawPic()
{
	if (RightAngleFlag == 1)
	{
		int points[8] = { center_x - bottomSide / 2, center_y + height / 2, center_x + bottomSide / 2, center_y + height / 2,
			center_x + bottomSide / 2, center_y - height / 2, center_x - bottomSide / 2, center_y + height / 2 };
		drawpoly(4, points);
	}
	else
	{
		int points[8] = { center_x - bottomSide / 2, center_y + height / 2, center_x + bottomSide / 2, center_y + height / 2,
			center_x - bottomSide / 2, center_y - height / 2, center_x - bottomSide / 2, center_y + height / 2 };
		drawpoly(4, points);
	}
}

void Triangle::Insert()//插入三角形对象
{
	Figure::p = new Triangle(bottomSide, height, RightAngleFlag, center_x, center_y);
}

class FigureLink//图形链表类
{
protected:
	Figure *head;//头指针
public:
	FigureLink(){ head = 0; }
	~FigureLink(){ Empty(); }
	void Empty();
	void Insert(Figure *figureNode);//插入图形节点
	void Draw();
	void Hide();
	void Move();
};

//清空链表
void FigureLink::Empty()
{
	Figure *current;
	Figure *next;
	current = head;
	while (current)
	{
		next = current->next;
		delete current;
		current = next;
	}
}

//插入图形类节点
void FigureLink::Insert(Figure *figureNode)
{
	figureNode->Insert();
	if (head)
	{
		figureNode->p->next = head;
		head = figureNode->p;
	}
	else head = figureNode->p;
}

//绘制图形
void FigureLink::Draw()
{
	Figure *current;
	current = head;
	while (current)
	{
		current->DrawPic();
		current = current->next;
	}
}

//隐藏图形
void FigureLink::Hide()
{
	Figure *current;
	current = head;
	while (current)
	{
		current->Hide();
		current = current->next;
	}
}

//移动图形
void FigureLink::Move()
{
	Figure *current;
	current = head;
	while (current)
	{
		current->Move();
		current = current->next;
	}
}

//顶一个基类车类Vehicle
class Vehicle
{
protected:
	FigureLink contents;//图形链表类
	int WheelSize;
	int x;
	int y;
public:
	void Draw();
	void Hide();
	void Move();
};

void Vehicle::Draw()
{
	contents.Draw();
}

void Vehicle::Hide()
{
	contents.Hide();
}

//车辆的移动
void Vehicle::Move()
{
	int seconds = 1000;
	int speed = 100;//移动速度为100
	int choice;
	while (1)
	{
		contents.Move();
		Sleep(seconds / speed);
		if (_kbhit())//在车辆移动过程中检测输入，有‘+’输入时，时间变短，加速，有‘-’输入时，时间变长，减速，输入‘E’，终止移动，输入‘P’，暂停或者继续移动
		{
			choice = _getch();
			if (choice == '+' || choice == '=') //seconds -= 10;
				if (seconds > 10) 
					seconds -= 10;
				else
				{
					outtextxy(25, 125, "车速过快！车辆停止移动！请再次按下<S>键！");
					return;//车速过快时，停止
				}
			else if (choice == '-' || choice == '_') seconds += 10;
			else if (choice == 'E' || choice == 'e') return;//输入‘E’，终止移动，推出Move函数，有’S‘输入时才继续移动
			else if (choice == 'P' || choice == 'p')
			{
				while (1)
				{
					choice = 0;
					if (_kbhit()) choice = _getch();//检查此时是否有键盘输入，若有，返回非零值
					if (choice == 'P' || choice == 'p') break;//若再次按P，继续运动
				}
			}
		}
	}

}

//Car类继承了Vehicle类
class Car :public Vehicle
{
public:
	Car(int d, int xstart, int ystart);
};

//构造Car
Car::Car(int d, int xstart, int ystart)
{
	WheelSize = d;
	x = xstart;
	y = ystart;
	Figure *f;
	f = new Triangle(d, d, 1, x + 1.75*d, y - 2.5*d);
	contents.Insert(f);
	f = new Rect(3.5*d, d, x + 4 * d, y - 2.5*d);
	contents.Insert(f);
	f = new Triangle(d, d, 2, x + 6.25*d, y - 2.5*d);
	contents.Insert(f);
	f = new Rect(8 * d, d, x + 4 * d, y - 1.5*d);
	contents.Insert(f);
	f = new Circle(x + 1.75*d, y - 0.5*d, 0.5*d);
	contents.Insert(f);
	f = new Circle(x + 6.25*d, y - 0.5*d, 0.5*d);
	contents.Insert(f);
}

//Truck 继承了Vehicle类
class Truck :public Vehicle
{
public:
	Truck(int d, int xstart, int ystart);
};

//构造Truck
Truck::Truck(int d, int xstart, int ystart)
{
	WheelSize = d;
	x = xstart;
	y = ystart;
	Figure *f;
	f = new Rect(9 * d, 4 * d, x + 4.5*d, y - 3 * d);
	contents.Insert(f);
	f = new Rect(2 * d, 3 * d, x + 2 + 10 * d, y - 2.5*d);
	contents.Insert(f);
	f = new Circle(x + d, y - 0.5*d, 0.5*d);
	contents.Insert(f);
	f = new Circle(x + 2.25*d, y - 0.5*d, 0.5*d);
	contents.Insert(f);
	f = new Circle(x + 6.75*d, y - 0.5*d, 0.5*d);
	contents.Insert(f);
	f = new Circle(x + 8 * d, y - 0.5*d, 0.5*d);
	contents.Insert(f);
}

//主函数
int main()
{
	Vehicle *v = 0;//定义一个机动车Vehicle类的指针
	Car car(10, 30, 350);
	Truck truck(10, 30, 350);
	int choice;

	initgraph(640, 450);//图像框大小
	outtextxy(10, 10, "1  Car  2  Truck  3  Exit");//选择图形类型
	rectangle(20, 30, 625, 430);//先画大矩形框轮廓
	outtextxy(25, 35, "Press <S> key to start moving");	//指令提示
	outtextxy(25, 50, "Press <P> key to pause/continue moving");
	outtextxy(25, 65, "Press <E> key to end moving");
	outtextxy(25, 80, "Press <+> key to speed up");
	outtextxy(25, 95, "Press <-> key to speed down");
	line(20, 351, 625, 354);

	choice = _getch();//不断循环，从输入获得指令，‘s'开始移动，1选择car，2选择truck，3退出程序
	while (choice != '3')
	{
		if (choice == '1')
		{
			outtextxy(25, 125, "                                                                                ");
			if (v) v->Hide();
			v = &car;
			v->Draw();
		}
		else if (choice == '2')
		{
			outtextxy(25, 125, "                                                                                 ");
			if (v) v->Hide();
			v = &truck;
			v->Draw();
		}
		else if (choice == 'S' || choice == 's')
		{
			outtextxy(25, 125, "                                                                                  ");
			if (v) v->Move();
		}
		choice = _getch();
	}
	closegraph();//关闭图形
	return 0;
}