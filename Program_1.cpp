/************************************************************

	֪ʶ�㣺�������캯��
	��  �ţ�1
	Ŀ  �ģ����һ���ຬ��ָ�����͵����ݳ�Ա��δ���ж��忽��
			���캯��������Ķ���ֱ�Ӹ�ֵʱ����ִ��󡣱�ʾ
			��ּ��˵����һ���⡣
	ע  �⣺��ʾ����һ�����ڴ���ĳ���

************************************************************/

#include <iostream>
using namespace std;
#include <cstring>							//�����������ַ�������

class MyClass
{
	char *name;								//˽�����ݳ�Ա��ָ������
public:
	MyClass(char *);						//�������캯��
	~MyClass();								//������������
	MyClass(const MyClass& other);
	void print();							//�������ܺ������ṩ��ӡ����
};

MyClass::MyClass(char *s)					//���幹�캯��
{
	cout<<"ִ�й��캯��;"<<endl;
	name = new char[strlen(s)+1];			//�����ڴ�ռ�
	strcpy(name,s);							//�������
}

MyClass::MyClass(const MyClass& other)
{
	cout << "ִ��������캯��;" << endl;
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
}


MyClass::~MyClass()							//������������
{
	cout<<"ִ����������;"<<endl;
	delete []name;							//�ͷ��ڴ�ռ�
}

void MyClass::print()						//�����ӡ����
{
	cout<<"ѧ�������ǣ�"<<name<<endl;		//�����Աname
}

int main()									//������
{
	char *p = new char[20];					//����ɴ�20��char���ڴ�ռ�
	cout<<"����������������";
	cin>>p;									//���û���������
	MyClass Obj_A(p);						//����MyClass�Ĺ��캯������������obj_A
	MyClass Obj_B=Obj_A;					//����Ĭ���ṩ����ν��ǳ�������캯������������obj_A�ġ����ݡ�ֱ�Ӹ�������obj_B
/*ע�⣺ִ����һ������ʱû�е���MyClass�Ĺ��캯�������ǵ��������صġ�Ĭ�Ͽ������캯������ͬʱobj_A�е�ָ��name��ָ����ڴ�
	��ַ��ֱ�Ӹ�����obj_B�е�ָ��name��Ҳ����˵����nameָ��ָ����ͬһƬ�ڴ�ռ�*/
	Obj_A.print();
	Obj_B.print();
}