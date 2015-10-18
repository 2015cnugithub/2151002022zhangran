/*1.���һ���������Worker�����Ӹû�������������ʱ������HourlyWorker�ͼ�н��
����SalariedWorker��ÿ�����˶���������name������age���Ա�sex��Сʱ����
��pay_per_hour�����ԣ���н�����Ա����void Compute_pay(double hours)��
�����в���hoursΪÿ�ܵ�ʵ�ʹ���ʱ������������ʾ���˵Ļ�����Ϣ�ı�׼�����
�����Ԫ����ostream& operator<<(ostream& out, Worker& worker)��
���˵�н��ȼ���Сʱ���ʶ�֣�
��ʱ���˵�н��ȼ���Ϊ10��20��40 US$/hour�����ȼ���
��н���˵�н��ȼ�����Ϊ30��50 US$/hour�����ȼ���
��ͬ���͵ȼ����˵���н���㷽����ͬ����ʱ������н�ļ��㷽���ǣ�
���ÿ�ܵĹ���ʱ����hours����40���ڣ�����н = Сʱ���ʶ� �� ʵ�ʹ���ʱ����
���ÿ�ܵĹ���ʱ����hours������40������н = Сʱ���ʶ� �� 40 + 1.5 �� Сʱ
���ʶ� ����ʵ�ʹ���ʱ�� �C 40����
����н����н�ļ��㷽���ǣ�
���ÿ�ܵ�ʵ�ʹ���ʱ��������35Сʱ����40Сʱ����н�������а�������յ�
��/���٣�������40Сʱ���ֲ���н������н = Сʱ���ʶ� �� 40��
���ÿ�ܵ�ʵ�ʹ���ʱ������35Сʱ������35Сʱ��������н = Сʱ���ʶ�  ʵ
�ʹ���ʱ�� + 0.5 �� Сʱ���ʶ� �� (35 - ʵ�ʹ���ʱ��)��

Ҫ��
1. ����Worker��HourlyWorker��SalariedWorker�࣬��ʵ�����ǵĲ�ͬ��н����
������
2. ��������main()��ʹ��HourlyWorker��SalariedWorker��������²�����
�� ͨ������̨���롢�������˳����ɶ�5����ͬ���˵Ļ�����Ϣ�����������䡢
�Ա�����н��ȼ�����ע�ᡣע�⣬5������Ӧ���������๤�˵�5���ȼ���
�� ͨ��һ���˵��ṹʵ����5�������п�������ѡ��һ�����ˣ���ʾ�ù��˵Ļ�
����Ϣ������ÿ�ܵ�ʵ�ʹ���ʱ����ͨ������̨���룩���㲢��ʾ�ù��˵���н��
ֱ��ѡ���˳�������

��ʾ��
1. ���Զ���һ��Worker���ָ������Worker* workers[5];����ָ��5����̬������
HourlyWorker��SalariedWorker�����ע�⣬�������ǰ��Ӧ������Щ��̬
�����Ķ���
2. ����ΪWorker������һ����Ա����void Name();�����ڲ˵��ṹ����ʾÿ������
��������Ϊ�û�ѡ��Ĳ˵��*/

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
