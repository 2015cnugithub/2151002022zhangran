/*��visual studio2013�������С�
С��������ͼ�ο���ѭ���ƶ���
���԰���<+>��һֱ���٣����ǵ��ٶȹ���ʱ��С����ֹͣ�ƶ�����Ҫ��������<S>�������ƶ���*/

#include<graphics.h>
#include <conio.h>
#include <dos.h>
#include <iostream>
#include<stdio.h>
#include<Windows.h>
using namespace std;

enum TYPE { CIRCLE, RECTANGLE, TRIANGLE };//ö��TYPE

class FigureLink;//����ͼ������

class Figure
{
	friend class FigureLink;//��Ԫ��
protected:
	TYPE type;//type��Figure�еĳ�Ա
	int center_x, center_y;//����ͼ�ε�����
	static Figure *p;//ָ��Ҫ���������ͼ�λ��ƶ���
	Figure *next;//ָ�������е���һ��ͼ�λ��ƶ���
public:
	Figure(int x, int y, TYPE tp)//����ͼ�Σ��������Ϊ�����ͼ������
	{
		center_x = x;//������
		center_y = y;//������
		type = tp;//ͼ������
		next = 0;//ָ����һ��ͼ�λ��ƶ���
	}
	virtual void DrawPic() = 0;//ͼ�λ��Ʋ����Ľӿڹ���,�麯�����̳��Ժ���������嶨��
	virtual void Insert() = 0;//ͼ�λ���������������Ľӿڹ����麯�����̳��Ժ���������嶨��
	void Hide();//����ͼ��
	void Move();//ͼ���ƶ�
};

Figure *Figure::p = 0;//��Ҫ���������ͼ�λ��ƶ���ָ��0

void Figure::Hide()//����ͼ��
{
	unsigned int sc = getcolor();//��ɫ����
	setcolor(BLACK);//����Ϊ��ɫ��������ͼ��
	DrawPic();//��ͼ
	setcolor(sc);//������ɫ
}

void Figure::Move()//ͼ���ƶ�
{
	unsigned int sc = getcolor();
	setcolor(BLACK);//������ɫΪ�ڣ�Ȼ��ͼ
	DrawPic();
	setcolor(sc);
	center_x += 1;//x����+1����ʵ���ƶ�
	center_x = center_x % 625;//ʹ��������ģ625������ʹͼ�λص�ԭ������ʼλ�ã��Ӷ�ѭ���ƶ�
	DrawPic();
}

//Բ���࣬Բ��Circle�̳�Figure
class Circle :public Figure	
{
private:
	int radius;//�뾶
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
	circle(center_x, center_y, radius);//��Բ
}

void Circle::Insert()
{
	Figure::p = new Circle(center_x, center_y, radius);//����Բ�Ķ���
}

//������Rect�̳���Figure��
class Rect :public Figure
{
private:
	int width;
	int length;
public:
	Rect(int w, int l, int x, int y) :Figure(x, y, RECTANGLE)//���캯��
	{
		width = w;
		length = l;
	}
	void DrawPic();
	void Insert();
};

void Rect::DrawPic()
{
	rectangle(center_x - width / 2, center_y - length / 2, center_x + width / 2, center_y + length / 2);//������
}

void Rect::Insert()//������ζ���
{
	Figure::p = new Rect(width, length, center_x, center_y);
}

//������Triangle��̳���Figure��
class Triangle :public Figure	
{
private:
	int RightAngleFlag;//�Ƕ�
	int bottomSide;//��
	int height;//��
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

//��������
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

void Triangle::Insert()//���������ζ���
{
	Figure::p = new Triangle(bottomSide, height, RightAngleFlag, center_x, center_y);
}

class FigureLink//ͼ��������
{
protected:
	Figure *head;//ͷָ��
public:
	FigureLink(){ head = 0; }
	~FigureLink(){ Empty(); }
	void Empty();
	void Insert(Figure *figureNode);//����ͼ�νڵ�
	void Draw();
	void Hide();
	void Move();
};

//�������
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

//����ͼ����ڵ�
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

//����ͼ��
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

//����ͼ��
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

//�ƶ�ͼ��
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

//��һ�����೵��Vehicle
class Vehicle
{
protected:
	FigureLink contents;//ͼ��������
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

//�������ƶ�
void Vehicle::Move()
{
	int seconds = 1000;
	int speed = 100;//�ƶ��ٶ�Ϊ100
	int choice;
	while (1)
	{
		contents.Move();
		Sleep(seconds / speed);
		if (_kbhit())//�ڳ����ƶ������м�����룬�С�+������ʱ��ʱ���̣����٣��С�-������ʱ��ʱ��䳤�����٣����롮E������ֹ�ƶ������롮P������ͣ���߼����ƶ�
		{
			choice = _getch();
			if (choice == '+' || choice == '=') //seconds -= 10;
				if (seconds > 10) 
					seconds -= 10;
				else
				{
					outtextxy(25, 125, "���ٹ��죡����ֹͣ�ƶ������ٴΰ���<S>����");
					return;//���ٹ���ʱ��ֹͣ
				}
			else if (choice == '-' || choice == '_') seconds += 10;
			else if (choice == 'E' || choice == 'e') return;//���롮E������ֹ�ƶ����Ƴ�Move�������С�S������ʱ�ż����ƶ�
			else if (choice == 'P' || choice == 'p')
			{
				while (1)
				{
					choice = 0;
					if (_kbhit()) choice = _getch();//����ʱ�Ƿ��м������룬���У����ط���ֵ
					if (choice == 'P' || choice == 'p') break;//���ٴΰ�P�������˶�
				}
			}
		}
	}

}

//Car��̳���Vehicle��
class Car :public Vehicle
{
public:
	Car(int d, int xstart, int ystart);
};

//����Car
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

//Truck �̳���Vehicle��
class Truck :public Vehicle
{
public:
	Truck(int d, int xstart, int ystart);
};

//����Truck
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

//������
int main()
{
	Vehicle *v = 0;//����һ��������Vehicle���ָ��
	Car car(10, 30, 350);
	Truck truck(10, 30, 350);
	int choice;

	initgraph(640, 450);//ͼ����С
	outtextxy(10, 10, "1  Car  2  Truck  3  Exit");//ѡ��ͼ������
	rectangle(20, 30, 625, 430);//�Ȼ�����ο�����
	outtextxy(25, 35, "Press <S> key to start moving");	//ָ����ʾ
	outtextxy(25, 50, "Press <P> key to pause/continue moving");
	outtextxy(25, 65, "Press <E> key to end moving");
	outtextxy(25, 80, "Press <+> key to speed up");
	outtextxy(25, 95, "Press <-> key to speed down");
	line(20, 351, 625, 354);

	choice = _getch();//����ѭ������������ָ���s'��ʼ�ƶ���1ѡ��car��2ѡ��truck��3�˳�����
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
	closegraph();//�ر�ͼ��
	return 0;
}