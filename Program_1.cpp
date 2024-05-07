/************************************************************

	知识点：拷贝构造函数
	序  号：1
	目  的：如果一个类含有指针类型的数据成员而未自行定义拷贝
			构造函数，则当类的对象直接赋值时会出现错误。本示
			例旨在说明这一问题。
	注  意：本示例是一个存在错误的程序。

************************************************************/

#include <iostream>
using namespace std;
#include <cstring>							//定义了若干字符串函数

class MyClass
{
	char *name;								//私有数据成员，指针类型
public:
	MyClass(char *);						//声明构造函数
	~MyClass();								//声明析构函数
	MyClass(const MyClass& other);
	void print();							//声明功能函数，提供打印功能
};

MyClass::MyClass(char *s)					//定义构造函数
{
	cout<<"执行构造函数;"<<endl;
	name = new char[strlen(s)+1];			//申请内存空间
	strcpy(name,s);							//填充内容
}

MyClass::MyClass(const MyClass& other)
{
	cout << "执行深拷贝构造函数;" << endl;
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
}


MyClass::~MyClass()							//定义析构函数
{
	cout<<"执行析构函数;"<<endl;
	delete []name;							//释放内存空间
}

void MyClass::print()						//定义打印函数
{
	cout<<"学生姓名是："<<name<<endl;		//输出成员name
}

int main()									//主函数
{
	char *p = new char[20];					//申请可存20个char的内存空间
	cout<<"请输入您的姓名：";
	cin>>p;									//由用户输入姓名
	MyClass Obj_A(p);						//调用MyClass的构造函数，创建对象obj_A
	MyClass Obj_B=Obj_A;					//调用默认提供的所谓“浅拷贝构造函数”，将对象obj_A的“内容”直接赋给对象obj_B
/*注意：执行上一句命令时没有调用MyClass的构造函数，而是调用了隐藏的“默认拷贝构造函数”；同时obj_A中的指针name所指向的内存
	地址被直接赋给了obj_B中的指针name，也就是说两个name指针指向了同一片内存空间*/
	Obj_A.print();
	Obj_B.print();
}