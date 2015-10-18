/*1.设计一个抽象基类Worker，并从该基类中派生出计时工人类HourlyWorker和计薪工
人类SalariedWorker。每名工人都具有姓名name、年龄age、性别sex和小时工资
额pay_per_hour等属性；周薪计算成员函数void Compute_pay(double hours)，
（其中参数hours为每周的实际工作时数）和用于显示工人的基本信息的标准输出运
算符友元函数ostream& operator<<(ostream& out, Worker& worker)。
工人的薪金等级以小时工资额划分：
计时工人的薪金等级分为10、20和40 US$/hour三个等级；
计薪工人的薪金等级，分为30和50 US$/hour两个等级。
不同类别和等级工人的周薪计算方法不同，计时工人周薪的计算方法是：
如果每周的工作时数（hours）在40以内，则周薪 = 小时工资额 × 实际工作时数；
如果每周的工作时数（hours）超过40，则周薪 = 小时工资额 × 40 + 1.5 × 小时
工资额 ×（实际工作时数 – 40）。
而计薪工周薪的计算方法是：
如果每周的实际工作时数不少于35小时，则按40小时计周薪（允许有半个工作日的
事/病假），超出40小时部分不计薪，即周薪 = 小时工资额 × 40；
如果每周的实际工作时数少于35小时（不含35小时），则周薪 = 小时工资额  实
际工作时数 + 0.5 × 小时工资额 × (35 - 实际工作时数)。

要求：
1. 定义Worker、HourlyWorker和SalariedWorker类，并实现它们的不同周薪计算
方法。
2. 在主函数main()中使用HourlyWorker和SalariedWorker类完成如下操作：
① 通过控制台输入、输出操作顺序完成对5个不同工人的基本信息（姓名、年龄、
性别、类别和薪金等级）的注册。注意，5个工人应分属于两类工人的5个等级。
② 通过一个菜单结构实现在5个工人中可以任意选择一个工人，显示该工人的基
本信息，根据每周的实际工作时数（通过控制台输入）计算并显示该工人的周薪。
直至选择退出操作。

提示：
1. 可以定义一个Worker类的指针数组Worker* workers[5];用于指向5个动态创建的
HourlyWorker或SalariedWorker类对象。注意，程序结束前，应撤消这些动态
创建的对象。
2. 可以为Worker类增加一个成员函数void Name();用于在菜单结构中显示每个工人
的姓名作为用户选择的菜单项。*/

#include <iostream>
#include <string>
using namespace::std;

class Worker{
protected:
	string name;
	int age;
	string sex;
	double pay_per_hour;
public:
	void set(string n, int a, string s, double pay){
		name = n;
		age = a;
		sex = s;
		pay_per_hour = pay;
	}
	virtual void Comput_pay(double hours){
	}
	friend ostream& operator<<(ostream& out, Worker& worker){
		return out << "Name:" << worker.name << " Age:" << worker.age <<
			" Sex:" << worker.sex <<  " Pay per hour:" << worker.pay_per_hour << endl;
	}
	void Name(){
		cout << name << endl;
	}
};

class HourlyWorker : public Worker{
public:
	void Comput_pay(double hours){
		double pay;
		if (hours < 40) pay = pay_per_hour*hours;
		else pay = pay_per_hour * 40 + 1.5*pay_per_hour*(hours - 40);
		cout << "The pay of a week is " << pay << endl;
	}
};

class SalariedWorker : public Worker{
public:
	void Comput_pay(double hours){
		double pay;
		if (hours < 35) pay = pay_per_hour*hours + 0.5*pay_per_hour*(35 - hours);
		else pay = pay_per_hour * 40;
		cout << "The pay of a week is " << pay << endl;
	}
};

void main(){
	Worker* workers[5];
	for (int i = 0; i < 5; i++){
		string name;
		int age;
		string sex;
		double pay;
		cout << "Please enter the name,age,sex,pay per hour:";
		cin >> name >> age >> sex >> pay;
		if (pay == 10 || pay == 20 || pay == 40) workers[i] = new HourlyWorker;
		else if(pay==30||pay==50) workers[i] = new SalariedWorker;
		else {
			cout << "Erro: Pay is wrong!";
			return;
		}
		workers[i]->set(name, age, sex, pay);
	}
	cout << "Name" << endl;
	for (int i = 0; i < 5; i++){
		cout << i + 1 << " ";
		workers[i]->Name();
	}
	cout << "Please choose a name using the number given before it:";
	int number;
	cin >> number;
	cout << *workers[number];
	cout << "Please enter the working hours per week:";
	double h;
	cin >> h;
	workers[number]->Comput_pay(h);
	system("pause");
}
