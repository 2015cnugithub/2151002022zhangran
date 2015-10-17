// zuoye1.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include <string.h>
using namespace std;

/*1. 定义一个商品类CGoods，其中包含商品号(long no)、商品名(char *p_name)、商品价格(double price)三个数据成员，
  以及相应的构造函数、拷贝构造函数、析构函数、打印数据成员的成员函数。
2.为CGoods类增加一个商品总数(int count)数据成员，并增加一个成员函数getCount()获取count的值，
  编写一个友元函数getName()获取商品名称p_name。做如上修改后，重新实现CGoods类(与第1问相同的不用再重复)。
   注释：根据功能要求，仔细考虑count应该定义成什么成员！
3. 为CGoods类定义小于运算符(‘<’)和不小于运算符(‘>=’)两个运算符重载函数。
   CGoods类对象大小的比较是根据其商品价格(price)的值的大小来实现的。(与第2问相同的不用再重复)
4. 以CGoods类为基类，派生出服装类CClothes和食品类CFood两个派生类，并在这两个类中分别增加一个表示品牌的指针数据成员(char *p_brand)和
  表示用途的成员函数(void usedFor()——可分别输出一条表示服装和食品用途的信息)。
  写出CClothes类和CFood类的完整定义(包括构造、析构和usedFor()成员函数的实现)。
5.为了能够采用动态联编的方式调用派生类的usedFor()成员函数，应该在CGoods类及其派生类CClothes和CFood类中作何改动？ */

////////////////////////////////////////////////////////////
class CGoods{
	static int count;//静态变量 
	long no;
	char *p_name;
	double price;
public:
	CGoods(long n, double p, char* p_n = "noName");
	CGoods(const CGoods& s);
	~CGoods();
	friend char* getName(CGoods &s);
	bool operator<(const CGoods&a);
	bool operator>=(const CGoods&a);
	void print();
	int getCount();
	virtual void usedFor();
};
CGoods::CGoods(long n, double p, char* p_n){
		no = n;
		price = p;
		count++;
		p_name = new char[strlen(p_n) + 1];
		if (p_name) strcpy(p_name, p_n);
		cout << "Constructing " << p_n << "\n";
}
CGoods::CGoods(const CGoods& s){
		cout << "copy Constructing " << s.p_name << "\n";
		no = s.no;
		price = s.price;
		count++;
		p_name = new char[strlen(s.p_name) + 1];
		if (p_name) strcpy(p_name,s.p_name);
}
CGoods::~CGoods(){
		cout << "Destructing " << p_name<<"\n";
		delete[] p_name;
}
bool CGoods::operator<(const CGoods&a){
		if (price < a.price) return true;
		else return false;
}
bool CGoods::operator>=(const CGoods&a){
		if (price < a.price)return false;
		else return true;
}
void CGoods::print(){
		cout << "No. is " << no << endl <<
			"Price is " << price << endl <<
			"Name is " << p_name << endl <<
			"Count is " << count<<endl;
}
int CGoods::count = 0;//静态变量初始化 
int CGoods::getCount(){
		return count;
}
char* getName(CGoods &s){
	return s.p_name;
}
void CGoods::CGoods::usedFor(){
		cout<<"It is used for Goods."<<endl;
}
////////////////////////////////////////////////////////////////////
class CClothes : public CGoods{
private:
	char*p_brand;
public:
	CClothes(long n,double p,char* p_n,char* p_b):CGoods(n,p,p_n){
		p_brand = new char[strlen(p_b) + 1];
		if(p_brand)strcpy(p_brand, p_b);
	}
	~CClothes(){
		cout<<"Deconstructing "<<p_brand<<endl;
		delete[] p_brand;
	}
	void usedFor(){
		cout<<"It is used for clothes."<<endl;
	}
};
//////////////////////////////////////////////////////////////////////
class CFood:public CGoods{
	char* p_brand;
public:
	CFood(long n, double p, char* p_n, char* p_b):CGoods(n,p,p_n){
		p_brand=new char[strlen(p_b)+1];
		if(p_brand)strcpy(p_brand,p_b);
	}
	~CFood(){
		cout<<"Deconstructing "<<p_brand<<endl;
		delete[] p_brand;
	}
	void usedFor(){
		cout<<"It is used for food."<<endl;
	}
};
//////////////////////////////////////////////////////////////////////
int main()
{
	CGoods g1(1, 10, "Orange");
	g1.print();
	cout<<endl;
	CGoods g2(g1);
	g2.print();
	cout<<endl;
	CClothes cl(3,30,"Dress","ZARA");
	cl.print();
	cl.usedFor();
	cout<<endl;
	CFood fo(4,40,"Rice","Ripe");
	fo.print();
	fo.usedFor();
	cout<<endl;
	//动态编联，虚函数 
	CGoods *pg;
	CGoods &rg1=g1;
	pg=&g1;
	pg->usedFor();
	rg1.usedFor();
	pg=&cl;
	pg->usedFor();
	CGoods &rg2=cl;
	rg2.usedFor();
	pg=&fo;
	pg->usedFor();
	CGoods &rg3=fo;
	rg3.usedFor();
	cout<<endl;
	return 0; 
}

