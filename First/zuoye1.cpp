// zuoye1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <iostream>
#include <string.h>
using namespace std;

/*1. ����һ����Ʒ��CGoods�����а�����Ʒ��(long no)����Ʒ��(char *p_name)����Ʒ�۸�(double price)�������ݳ�Ա��
  �Լ���Ӧ�Ĺ��캯�����������캯����������������ӡ���ݳ�Ա�ĳ�Ա������
2.ΪCGoods������һ����Ʒ����(int count)���ݳ�Ա��������һ����Ա����getCount()��ȡcount��ֵ��
  ��дһ����Ԫ����getName()��ȡ��Ʒ����p_name���������޸ĺ�����ʵ��CGoods��(���1����ͬ�Ĳ������ظ�)��
   ע�ͣ����ݹ���Ҫ����ϸ����countӦ�ö����ʲô��Ա��
3. ΪCGoods�ඨ��С�������(��<��)�Ͳ�С�������(��>=��)������������غ�����
   CGoods������С�ıȽ��Ǹ�������Ʒ�۸�(price)��ֵ�Ĵ�С��ʵ�ֵġ�(���2����ͬ�Ĳ������ظ�)
4. ��CGoods��Ϊ���࣬��������װ��CClothes��ʳƷ��CFood���������࣬�������������зֱ�����һ����ʾƷ�Ƶ�ָ�����ݳ�Ա(char *p_brand)��
  ��ʾ��;�ĳ�Ա����(void usedFor()�����ɷֱ����һ����ʾ��װ��ʳƷ��;����Ϣ)��
  д��CClothes���CFood�����������(�������졢������usedFor()��Ա������ʵ��)��
5.Ϊ���ܹ����ö�̬����ķ�ʽ�����������usedFor()��Ա������Ӧ����CGoods�༰��������CClothes��CFood�������θĶ��� */

////////////////////////////////////////////////////////////
class CGoods{
	static int count;//��̬���� 
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
int CGoods::count = 0;//��̬������ʼ�� 
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
	//��̬�������麯�� 
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

