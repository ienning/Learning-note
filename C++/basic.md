​	

[TOC]



# 基础

## 关键字与操作符

### 关键字

- explicit：

### 操作符

- `&` ：取址操作符
- `*` ：引领操作符
- `->`：选员操作符
- `->*`：选员操作符，指向类成员的指针

### 运算符

#### 运算符顺序

1. 算术运算符
2. 移位运算符
3. 关系运算符，赋值运算符，条件运算符

#### 算术运算符



## 函数

### 值传递机制

- 形式参数在函数调用的时候才会创建存储空间，并接受实际参数的值；
- 实际参数可以为复杂的表达式，在函数调用前获得计算；
- 形式参数与实际参数可同名，也可不重名；
- 参数较多时候，实际参数值逐一赋值，它必须保持数目、类型、顺序一致；
- 值得赋值过程是单向不可逆的，函数内部对形式参数值的修改不会反映到实际参数中去；
- 函数参数一般为函数输入集的一部分，函数输出集一般使用返回值表示，只有使用特殊的手段才可以将函数参数作为函数输出集的一部分；

#### Task：

- [x] 编写函数IsPrime，判断某个大于2的正整数是否为素数；

- [x] 编写函数gcd与lcm，分别求两个正整数的最大公约数与最小公倍数；

### 引用传递机制



## 宏定义

```c++
#ifndef DEBUG
// code，using，if before not use #define DEBUG, will execute this code，else jump this code. 
#endif
```



## 指针

### 指针运算

指针运算操作是以指针指向的目标数据对象类型为单位

```c++
int* p;
// 表示的指针p先做*p运算赋值，之后做的是p++运算（指针后移一个数据类型int单位指向下一个int存放的地址）
*p++ = generateNum() 
```

### 指针与数组

指针与数据是计算格式是一样的，但是二者不是相同的，指针可以做\*p++，数组无法做\*a++



## 字符串、向量、数组

## 表达式

### 类型转换

#### 显示转换

格式：*cast-name\<type\>(expression)*

cast-name类型：

- static_cast：任何具有明确定义的类型转换，只要不包括底层const，都可以使用static_cast。static_cast可以找回存在于void*指针中的值
- dynamic_cast：支持运行时类型识别
- const_cast：只有该强制类型转换方式才能将常量转换为非常量，但是不能改变表达式类型，常用于函数重载的上下文中。
- reinterpret_cast：通常为运算对象的位模式提供较低层次上的重新解释



## 动态分配

专门在堆中存放动态分配的数据，c中使用malloc和free函数，c++增加了new和delete操作符，c方式分配内存使用c方式释放内存，c++也一样。

### C++中增加的动态分配方式

#### new/new[]

分配单个目标对：int*p; p = new int; *p = 10;

分配多个目标对象：int* p; p = new int[8];

#### delete/delete[]

释放单个对象：int* p; p = new int; *p = 10; delete p;

释放多个对象：int* p; p =  new int[10]; delete[] p;

### void*类型

哑型指针，暂时不确定类型，使用这个。



## 引用

### 引用的定义

定义格式：数据类型& 变量名称 = 被应用比那辆名称；

示例：int a; int & ref = a;

### 引用的性质

引用类型的变量不占用单独的存储空间

为另一数据对象起个别名，与该对象共享存储空间

### 特殊说明

引用类型的变量必须在定义时初始化

此关联关系在引用类型变量的整个存续期都保持不变

对引用类型变量的操作就是对被引用变量的操作

### 引用作为函数参数

参数传递机制：引用传递，直接修改实际参数值。

```c++
void Swap(int & x, int & y) {
    int t;
    t = x;
    x = y;
    y = t;
    return;
}

int main() {
    int a = 10;
    int b = 20;
    Swap(a, b); // a和b的值都互换了
}
```



## 数据抽象

### 数据抽象

信息缺失：程序中的数据对象只有地址和值，没有数据类型、数据名称数据解释以及数据意义等信息

解决手段：抽象

### 结构化数据类型的性质

- 类型：细节由用户自定义，语言仅提供定义手段
- 成员：结构化数据类型的子数据对象
- 成员类型：每个成员具有确切的类型
- 成员数目：部分结构化数据类型可变，部分固定
- 成员组织：成员组织结构（线性结构或非线性结构）必须显示定义
- 操作集：可以在数据上进行的操作集合

### 数据封装

数据封装：将数据结构和细节隐藏起来

实现方式：分别实现访问数据成员的存取函数

### 信息隐藏

#### 数据封装的问题

只要将结构体定义在头文件中，库的使用者就可以看到该定义，并按照成员格式直接访问，而不调用存取函数

#### 解决方法

将结构体类型的具体细节定义在源文件中，所有针对该类型量的操作都只能通过函数接口来进行，从而隐藏实现细节

#### 信息隐藏示例：

```c++
/* 头文件 "dynarryn.h" */
struct DYNINTS; typedef struct DYNINTS * PDYNINTS;

/* 源文件 "dynarray.cpp" */
struct DYNINTS {
    unsigned int capacity;
    unsigned int count;
    int * items;
    bool modified;
};
```



### 抽象数据类型



## 链表



## 函数指针

用处：函数指针可用于函数回调上，通过作为参数传递到函数参数列表中，函数调用参数列表中的函数指针，然后调用函数指针所指向所对应的函数入口地址调用函数。这样函数指针所指向的函数与调用它的函数进行了解耦，其中一方定义目标函数还有一方可以自己定义回调函数，这样就是回调。

## 抽象链表



## 类

类的概念和意义：

- 属性与行为的辩证统一

程序抽象

- 数据封装、信息隐藏
- 如果没有类的概念，无法定义非指针量，且控制性不佳

对象的概念与意义

- 量
- 对象行为的主动性

### 类的声明与定义

类的定义是使用class关键字而非struct，二者的唯一区别是，struct和class的默认访问权限不太一样，struct默认是public，class默认是private

```c++
class A {
    public:
    	成员变量 成员函数（可以多行的，不用加花括号）
    protected:
    	成员变量 成员函数
    private:
    	成员变量 成员函数（成员变量或成员函数没有加修饰符号，则默认是private的）
}
```

### 类函数的实现

```c++
/* a.h */
class B;
class A {
    public:
    	int GetX();
    	void func(B b); //正确
    private:
    	int x;
    	B b; //错误，内存分配的模式不知道，所以类类型的声明是不能用于数据成员的定义。
}

/* a.cpp */
#include "a.h"
int A::GetX() {
    reutrn this->x;
}
```

### 对象

在类的声明中有3个缺省的函数：

- 缺省的构造函数
- 缺省的拷贝构造函数
- 缺省的析构函数
- 函数

#### 构造函数

- 普通构造：直接初始化类的成员函数构造出一个新的对象
- 拷贝构造：通过左值引用传递类型对象，进行类成员拷贝，构造出一个新的对象。
- 移动构造：通过右值引用，将传递进的对象进行移动构造，和上一个同类型对象指向的类成员内存是同一内存，相当于替换了内存管理者，上一个对象管理的内存交接给了当前对象

#### 构造函数的初始化列表

```c++
// 构造函数的初始化列表格式
class A
{
    public:
     A(int a);
    private a;
};

class B
{
    public:
     B(int a, int b);
    private:
     A a;
     int b;
};

// 实现构造
A::A(int a) : a(a)
{
    
}

B::B(A a, int b) : a(a), b(b)
{
    
}

```



##### 构造函数初始化的目的意义

- 在构造对象时，同步构造内部对象
- 部分成员（常量与引用）只能初始化，不能给你赋值，二者是不一样的。
- 部分成员（类的对象）如果赋值，将导致两次构造
  - 在分配内存时，调用缺省构造函数构造，然后执行构造函数体内的赋值语句再次构造，效率不佳
  - 若类没有缺省构造函数，则会导致问题

##### 注意事项

- 成员初始化按照成员定义顺序，而不是初始化列表顺序
- 必须保持初始化列表和成员定义的顺序一致性，但允许跳过部分成员；否则后续成员可能不会正确初始化

#### 对象的析构

##### 对象析构的意义

- 析构就是终止化，在对象生命周期结束时清除它

##### 对象析构的技术手段：使用析构函数

- 与类类型同名， 前有“~”记号，无返回值类型（包括void类型），无参数
- 析构函数必须公开（某些情况下也可以不公开）
- 可以由系统在销毁对象时自动调用，也可以由程序其他部分直接调用，但两者工作原理不同
- 每个类的析构函数只能有一个
- 若未定义，系统会自动产生一个缺省析构函数，该函数无代码

##### 定义析构函数的目的

- 用于释放对象中动态分配内存的目标数据对象

  ```c++
  // example
  class A{
      public:
       A(int x);
       ~A();
      private:
       int *p;
  };
  
  // 实现
  A::A(int x)
  {
      p = new int;
      *p = x;
  }
  
  A::~A()
  {
      delete p, p = NULL;
  }
  ```

#### 对象数组

- 像普通数组一样定义使用

##### 对象数组的初始化

- 当构造函数单参数时，像普通数组一样构造所有元素

- 当构造函数多参数时，使用下述方法构造

  ```c++
  Circle circles[2] =  {Circle(1.0, 0.0, 0.0), Circle(2.0, 1.0, 1.0)};
  ```

### 类与对象的成员

#### 内联函数

目的：程序优化，展开函数代码而不是调用

##### 内联函数使用的注意事项

- 在函数定以前添加inline关键字，仅在函数原型前使用此关键字无效
- 编译器必须能看见内联函数的代码才能在编译器展开，因而内联函数必须是现在头文件中
- 在类定义中给出函数体的成员函数自动成为内联函数
- 函数体代码量较大，或包含循环，不要使用内联
- 构造函数和西沟函数有可能有隐含的附加操作，慎用内联
- 内联函数仅是建议，编译器会自主选择是否内联

#### 常数据成员

常数据成员：值在程序运行期间不可变

- 定义格式：const类型 数据成员名称
- 初始化：只能通过构造函数中的初始化列表进行

#### 常成员函数

常成员函数：不能修改对象成员值得函数

- 定义格式：类型 成员函数名称(参数列表) const;
- 常成员函数不能调用类中非常成员函数
- 静态成员函数不能定义为常成员函数
- 如果对象为常量，则只能调用其常成员函数

#### 静态数据成员

静态数据成员只有一份，由该类所有对象共享

- 声明格式：static 类型 静态数据成员名称;
- 仅声明，不在对象上分配空间
- 定义格式：类型 类名称::静态数据成员名称 = 初始值;
- 必须在外部初始化，初始化动作与访问控制无关

#### 静态成员函数

- 在类而不是对象上调用
- 目的：访问类的静态数据成员，若要访问类的非静态数据成员，必须指定对象或者使用指向对象的指针

#### 单子模式（单例模式）

单子模式：只存在某类中的单一共享对象，存在某种全局访问策略，以在需要时访问该对象。没有析构对外开放

```c++
class Singleton
{
    public: // 静态成员函数，对象不存在时构造，否则返回之，保证唯一性
    	static Singleton * Get() { if(!_s) _s = new Singleton; return _s; }
    	int GetDate() {
           	return ++a;
        }
    private: // 私有构造函数，禁止在外部构造本类的对象
    	Singleton() {
            a = 0;
        }
    	Singleton(const Singleton & that); // 只声明不实现，禁止拷贝和赋值构造
    	Singleton & operator = (const Singleton & that);
    public: // 在部分系统下使用private亦可，系统简单释放全部内存，并不调用它
    	~Singleton() {} //因此，如果函数非空（如需数据持久化），有可能导致问题
    private:
    	static Singleton * _s; // 静态数据成员，指向本类唯一对象的指针
    	// Destroyer类的唯一任务是删除单子
    	class Destroyer {
            public:
            ~Destroyer() { if(Singleton::s) { delete Singleton::_s, Singleton::_s = NULL; } }
        };
    	static Destroyer _d; // 程序结束时，系统自动调用静态成员的析构函数
    	int a; // 验证数据

}


// 正确析构
class Singleton
{
    public: // 静态成员函数，对象不存在时构造，否则返回之，保证唯一性
    	static Singleton * Get() { if(!_s) _s = new Singleton; return _s; }
    	// 不调用析构函数，Release调用时机由程序员确定
    	static void Release() { if(_s) { free(_s), _s = NULL; } }
    	int GetDate() {
           	return ++a;
        }
    private: // 私有构造函数，禁止在外部构造本类的对象
    	Singleton() {
            a = 0;
        }
    	Singleton(const Singleton & that); // 只声明不实现，禁止拷贝和赋值构造
    	Singleton & operator = (const Singleton & that);
    	~Singleton();
    private:
    	static Singleton * _s; // 静态数据成员，指向本类唯一对象的指针
    	int a; // 验证数据

}

// 正确析构方案二
class Singleton
{
    public: // 静态成员函数，对象不存在时构造，否则返回之，保证唯一性
    	static Singleton * Get() { static  Singleton _s; return _s; }
    	int GetDate() {
           	return ++a;
        }
    private: // 私有构造函数，禁止在外部构造本类的对象
    	Singleton() {
            a = 0;
        }
    	Singleton(const Singleton & that); // 只声明不实现，禁止拷贝和赋值构造
    	Singleton & operator = (const Singleton & that);
    	~Singleton();
    private:
    	int a; // 验证数据

}

// 本实现没有动态内存分配，因而无需销毁单子对象
// 使用方法：定义引用或以Singleton::Get().GetData()方式访问
SingleTon & sing = SingleTon::Get();
int n = sing.GetData();
```

#### 静态常数数据成员

静态常数数据成员：值在程序运行期间不可变，切只有唯一副本

- 定义格式：`static const 类型 数据成员名称`;
- 初始化：只能在类的外部初始化

```C++
class A
{
    private:
    	static const int count;
};
const int A::count = 1; // 初始化时候需要带上const关键字，static可以不用加
```

#### 友元函数与友元类

友元：**慎用**！破坏类数据封装与信息隐藏

- 类的友元可以访问该类对象的私有与保护成员
- 友元可以是函数、其他类成员函数，也可以是类
- 定义格式：`friend 函数或类声明`；
- 两个类的友元关系不可逆，除非互为友元

```C++
// Example
class Circle
{
    friend double Get_Radious();
    friend class Globe; // 将Globe类所有成员函数声明为友元
  private:
    double radius;
};
```



### 继承

#### 继承的基本概念

- 类类型：描述分类的概念
- 继承：描述类之间的血缘（继承）关系
- 基类、派生类
- 父类、子类（不恰当的概念）

#### 继承的意义

- 派生类拥有基类的全部属性与行为
- 派生类可以增加新的属性与行为

#### 单继承

##### 单继承的基本语法格式

- class 派生类名称：派生类型保留字 基类名称 { ... };

##### 派生类型保留字

- public：基类的public、protected成员在派生类中保持，private成员在派生类中不可见（属于基类隐私）

- protected：基类的private成员在派生类中不可见，public、protected成员在派生类中变为protected成员
- private：基类的private成员在派生类中不可见，public、protected成员在派生类中变为private成员
- 设计类时若需要使用继承机制，建议将派生类需要频繁使用的基本数据成员设为protected的

##### 函数覆盖与二义性

```c++
// 派生类成员函数名称与基类相同
class Point { void Print(); };
class Point3D: public Point {void Print(); };
Point pt(1, 2);
Point3D pt3d(1, 2, 3);
// 调用示例
pt.Print(); //调用Point的Print()函数
pt3d.Print(); //调用Point3D的Print()函数
// 如果需要在Point3D中访问Point的Print()函数，使用如下方法
pr3d.Point::Print(); // 使用解析
```

#### 多继承

##### 多继承的基本语法格式

class 派生类名称: 派生类型保留字 基类名称1, 派生类型保留字 基类名称2, ... { ... };

##### 多继承可能导致的问题

派生类中可能包含多个基类副本

```c++
// example
class A { ... };
class B: public A { ... };
class C: public A, protected B { ... };
```

##### 虚基类

##### 虚拟机从的目的

- 取消多继承时派生类中公共基类的多个副本，只保留一份
- 格式：派生时使用关键字virtual

```c++
// Example 
// D中只有A的一份副本
class A { public: void f(); };
class B: virtual public A { public: void f(); }; // virtual 关键字和 public 关键字前后切换是没关系的
class C: virtual public A { public: void f(); };
class D: public B, public C { public: void f(); };
```

#### 派生类的构造函数与析构函数

##### 构造函数的执行顺序

- 调用基类的构造函数，调用顺序与基类在派生类中继承顺序相同
- 调用派生类新增对象成员的构造函数，调用顺序与其在派生类中的定义顺序相同
- 调用派生类的构造函数

##### 析构函数的执行顺序

- 调用派生类的析构函数
- 调用派生类新增对象成员的析构函数，调用顺序与其在派生类中的定义顺序相反
- 调用基类的析构函数，调用顺序与基类在派生类中的继承顺序相反

#### 类的赋值兼容性

**共有派生时，任何基类对象可以出现的位置都可以使用派生类对象代替：**

- 将派生类对象赋值给基类对象，仅赋值基类部分
- 用派生类对象初始化基类对象引用，仅操作基类部分
- 使指向基类的指针指向派生类对象，仅引领基类部分

**保护派生类与私有派生类不可以直接赋值：**

- 尽量不要使用保护派生与私有派生

```c++
// Example
#include <iostream>
#include <string>
using namespace std;
class Base
{
    public:
    	// str_a(s)就是新增对象成员
    	Base(string s): str_a(s) {}
    	Base(const Base & that) { str_a = that.str_a; }
    	void Print() const { cout << "In base: " << str_a << endl; }
};

class Derived: public Base
{
    public:
    	Derived(string s1, string s2): Base(s1), str_b(s2) {} //调用基类构造函数初始化，必须在初始化列表中调用基类初始化函数
    	void Print() const { cout << "In derived: " << str_a + " " + str_b << endl; }
    protected:
    	string str_b;
};
```



### 多态

#### 多态性

- 目的：不同对象在接收到相同消息时做不同响应
- 现象：对应同样成员函数名称，执行不同函数体

#### 多态性的实现

- 虚函数：使用virtual关键字声明成员函数
- 声明格式：virtual 函数返回值 函数名称(参数列表);

#### 纯虚函数

- 充当占位函数，没有任何实现
- 派生类负责实现其具体功能
- 声明格式：virtual void f( int x) = 0;

#### 抽象类

- 带有纯虚函数的类
- 作为类继承层次的上层

#### 虚析构函数

##### 作用：

- 保持多态性需要虚析构函数，以保证能够正确释放对象
- 为了避免内存泄漏，而且是当自对象会有指针成员变量时，才会使用到。即虚析构函数使得在删除指向子类对象的基类指针时，可以调用子类的析构函数来实现释放子类中堆内存的目的，从而防止内存泄漏。

### 编程实践

- 使用面向对象架构实现动态数组库
- 使用面向对象架构实现抽象链表库

## IO库

### 和IO相关的包

W开头的是宽字符（wchar_t类型）版本。

- iostream
  - istream，wistream从流中读取数据
  - ostream，wostream向流写入数据
  - iostream，wostream读写流
- fstream
  - ifstream，wifstream从文件读取数据
  - ofstream，wofstream向文件写入数据
  - fstream，wfstream读写文件
- sstream
  - istringstream，wistringstream从string读取数据
  - ostringstream，wostringstream向string写入数据
  - stringsstream，wstringstream读写string

### 文件IO

#### 文件模式

- in ：以读的方式打开
- out ：以写的方式打开：如果不指定app模式（可以阻止ofstream清空指定文件内容），使用该方式或者直接使用ofstream默认模式时候文件的内容会被丢弃。
- app ：每次写操作前均定位到文件末尾
- ate ： 打开文件后立即定位到文件末尾
- trunc ： 截断文件，在out也被设定的时候才可以被设定该模式
- binary ： 以二进制方式进行IO
- 保留被ofstream打开的文件中已有的数据的唯一方法是显示指定app或in模式

### string流

#### stringstream特有的操作

- sstream strem		strm是一个未绑定的stringstream对象。sstream是头文件sstream中定义的一个类型
- sstream strm(s)      strm是一个sstream对象，保存string s的一个拷贝。此构造函数是explicit的
- strm.str()                 返回strm所保存的string的拷贝
- strm.str(s)               将string s拷贝到strm中。返回void

## 容器库

- 顺序容器：
- 关联容器：
- 无序容器：

### 顺序容器库

- vector ：可变大小数组，支持快速随机访问。在尾部之外的位置插入或删除元素可能很慢
- deque ：双端队列。支持快速随机访问。在头尾位置插入/删除速度很快
- list ：      双向链表。只支持双向顺序访问。在list中任何位置进行插入/删除操作速度都很快
- forward_list ：单向链表。只支持单向顺序访问。在链表任何位置进行插入/删除操作速度都很快
- array ：   固定大小数组。支持快速随机访问。不能添加或删除元素。
- string ：   与vector相似的容器，但专门用于保存字符。随机访问快。在尾部插入/删除速度快

### 顺序容器操作（特有操作）

#### 向顺序容器添加元素

- forward_list有自己专属版本的insert和emplace
- forward_list不支持push_back和emplace_back
- vector和string不支持push_front和emplace_front
- c.push_back(t)：会有一个临时对象的，产生拷贝
- c.emplace_back(t)：在存入容器的时候不会产生拷贝
- c.push_front(t)
- e.emplace_front(t)
- c.insert(p, t)
- c.emplace(p, args)
- c.insert(p, n, t)
- c.insert(p, b, e)
- 注意：向一个vector、string或deque插入元素会使所有指向容器的迭代器，引用和指针失效

#### 向顺序容器删除元素

- forward_list有特殊版本的erase
- forward_list不支持pop_back；vector和string不支持pop_front。
- c.pop_back()：删除尾元素。若c为空，则函数行为未定义，返回void
- c.pop_front()：删除头元素。若c为空，则函数行为未定义，返回void
- c.erase(p)：删除迭代器p指定的元素，返回一个指向被删元素之后元素的迭代器，若p指向尾元素，则返回尾后（pff-the-end）迭代器。若p是尾后迭代器，则函数行为未定义
- c.erase(b, e)：删除迭代器b和e所指定范围内的元素。返回一个指向最后一个被删元素之后的迭代器，若e本身就是尾后迭代器，则函数也返回尾后迭代器。（左闭右开）
- c.clear()：删除c中的所有元素，返回void
- 注意：删除deque中除收尾元素之外的任何元素都会使所有迭代器、引用和指针失效。指向vector或string中删除点之后位置的迭代器、引用和指针都会失效。
- 注意：删除元素的成员函数并不检查其参数。在删除元素之前，程序员必须确保它（们）是存在的

#### 容器操作可能使迭代器失效

- 向容器添加元素：
  - 如果容器是vector或stirng，且存储空间被重新分类，那么指向容器的迭代器、指针和引用都会失效。如果存储空间未重新分配，那么指向插入位置的之前的迭代器、指针和引用不会失效，但是指向插入位置的之后的迭代器、指针和引用都会失效。
  - 如果是deque，那么在插入到首尾元素之外的任何位置都会导致迭代器，指针和引用失效，如果是在首尾位置上添加元素，指向存在的元素的迭代器会失效，但是指针和引用不会失效。
  - 对于list和forward_list，指向容器的迭代器、指针和引用仍旧有效。
- 向容器删除元素
  - 对于list和forward_list，指向容器的迭代器、指针和引用仍旧有效。
  - 如果是deque，那么在插入到首尾元素之外的任何位置都会导致迭代器，指针和引用失效，如果删除的是deque的尾元素，则尾后迭代器会失效，但其它迭代器、指针和引用不受影响；如果是删除首元素，这些也不会受影响
  - 对于vector和string，指向被删除元素之前的元素的迭代器、引用和指针有效。尾后迭代器总会失效

#### 构造string的其他方法

- string s(cp, n)：s是cp指向的数组中前n个字符的拷贝。此数组至少应该包含n个字符
- string s(s2, pos2)：s是string s2 从下标pos2开始的字符的拷贝。若pos2>s2.size()，构造函数的行为未定义
- string s(s2, pos2, len2)：s是string s2从下标pos2开始len2个字符的拷贝，若pos2>s2.size()，构造函数的行为未定义。不管len2的值是多少，构造函数至多拷贝s2.size() - pos2个字符。
- 注意：当从一个const char*创建string时，指针指向的数组必须以空字符结尾，拷贝操作遇到空字符时停止。如果还给string构造函数传递给了计数值，那么数组不必以空字符结尾。如果我们没有传递计数值且数组没有以空字符结尾，或者给定的计数值大于数组大小，则构造函数的行为未定义的。

##### 额外的stirng操作

- append函数是在string末尾进行操作操作的一种简写形式
- replace函数是调用erase和insert的一种简写形式

### 关联容器

#### 关联容器类型

##### 按关键字有序保存元素

- map	关联数组：保存关键字键值对
- set      关键字即值，即只保存关键字的容器
- multimap 关键字可重复出现的map
- multiset    关键字可重复出现的set

#### 无序集合

- unordered_map    用哈希函数组织的map
- unordered_set      用哈希函数组织的set
- unordered_multimap    哈希组织的map：关键字可以重复出现
- unordered_multiset      好像组织的set：关键字可以重复出现

##### 无需容器管理操作

- 桶接口：
  - c.bucket_count()								正在使用的桶的数目
  - c.max_bucket_count()	 				  容器所能容纳的最多的桶的数量
  - c.bucket_size(n)    							 第n个桶有多少个元素
  - c.bucket(k)										  关键字为k的元素在哪个桶中
- 桶迭代
  - load_iterator										可以用来访问桶中元素的迭代器类型
  - const_local_iterator							 通迭代器的const版本
  - c.begin(n), c.end(n)							 桶n的首元素和尾后元素
  - c.cbegin(n), c.cend(n)						  与前两个函数相似，但是返回的是cosnt_local_iterator
- 哈希策略
  - c.load_factor()									  每个桶的平均元素数量，返回float值
  - c.max_load_factor()							  c试图维护的平均桶大小，返回float值。c会在需要时添加新的桶，以使得load_factor <= max_load_factor
  - c.rehash(n)										   重组存储 使得bucket_count >= n 且 bucket_count > size/max_load_factor
  - c.reserve(n)										  重组存储，使得c可以保存n个元素且不必rehash

## 泛型算法

### 初识泛型算法

- 标准库算法对迭代器而不是容器操作，因此，算法不能（直接）添加或删除元素

#### back_inserter

算法不检查写操作，所以如果写入的位置超出了容器的范围，例如fill_n()函数

```c++
vecotr<int> cev; // 空向量
// 修改vec中的10个元素（不存在），程序会报错
fill_n(vec.begin(), 10, 0);
// 解决方法
// 使用back_inserter（该函数属于iterator中的一个函数）函数会将调用的值添加到容器中。
// back_inserter返回的是和传入的容器绑定的迭代器
fill_n(back_inserter(vec), 10, 0);
```

#### 拷贝算法

```c++
// 
vector<int> ivec;
list<int> list;
int a1[] = { 0, 1, 2, 3, 4, 5};
int a2[sizeof(a1)/sizeof(*a1)];	// 和a1的大小一样
// ret 指向拷贝到a2的尾元素之后的位置
auto ret = copt(begin(a1), end(a1), a2);	// 把a1内容拷贝到a2
// 将所有的值为0的元素改为20
replace(list.begin(), list.end(), 0, 20);
// 将list的内容拷贝到ivec上，且将0替换为20。list上的值不变
replace_copy(list.begin(), list.end(), back_inserter(ivec), 0, 20);
```

### 再探迭代器

- 插入迭代器
- 流迭代器
- 反向迭代器
- 移动迭代器

#### 插入迭代器

#### 流迭代器

#### 反向迭代器

- 反向迭代器转正向迭代器的函数iter.base()，反向迭代器是左闭右开，正向迭代器是右闭左开。

#### 移动迭代器

#### 泛型算法结构

- 输入迭代器：只读，不写：单遍扫描，只能递增
- 输出迭代器：只写，不读：单遍扫描，只能递增
- 前向迭代器：可读写：多遍扫描，只能递增
- 双向迭代器：可读写：多遍扫描，可递增递减
- 随机访问迭代器：可读写，多遍扫描，支持全部迭代器运算

## 动态内存

### 动态内存与智能指针

动态内存是，程序的一个内存池，一般被称为自由空间或堆。C++通过new 进行 内存的动态分配，可以通过delete进行销毁。如果在程序结束时没有销毁，就会产生内存泄漏，如果还有指针引用内存，但是内存被释放了，就会产生引用非法内存的指针了。

新标准库提供了两种智能指针来管理动态对象，两个智能指针的区别是，管理底层指针的方式不同，``share_ptr``允许多个指针指向同一个对象，``unique_ptr``则“独占”所指向的指针。``weak_ptr``是一种弱引用，指向``shared_ptr``所管理的对象，三者都是在``memory``头文件中

#### `shared_ptr`和new结合使用

接受指针参数的智能指针构造函数是explicit的，因此我们不能将一个内置指针隐式地转换为一个智能指针，必须使用直接初始化形式来初始化一个智能指针。在使用智能指针作为函数的返回值时，返回值不能为内置指针，因为无法进行隐式转换

```c++
shared_ptr<int> p1 = new int(1024);		// 错误：必须使用直接初始化形式
shared_ptr<int> p2(new int(1024));		// 正确：使用了直接初始化形式
```

使用一个内置指针访问智能指针所负责的对象是危险的，因为无法知道对象何时会被销毁，也不要使用get初始化另一个智能指针或为智能指针赋值

get用来将指针的访问权限传递给代码，只有在确定get返回的指针不会在代码中被delete，才能使用get函数返回指针，以及不要使用get函数返回的指针初始化另外一个智能指针或者为另外一个智能指针进行赋值。

#### 智能指针与异常

在直接管理内存时候，如果在分配和释放同一对象的内存时候，在这两者之间发生异常且未进行捕获导致函数异常退出，那么就会导致释放内存无法进行，导致内存泄漏，但是使用智能指针就会自动进行内存释放

#### 智能指针与哑类

如果对象没有定义析构函数，无法正确的释放内存，那么我们在这里可以使用智能指针创建对象的时候进行初始化传入的内置指针以及删除器函数。在对象进行相应的销毁时，删除器函数会被调用，可以进行对象析构作用。

#### `unique_ptr`

`unique_ptr`不支持拷贝和赋值操作，但是有一个例外，我们可以拷贝或赋值一个将要被销毁的unique_ptr。最常见的例子就是从函数返回一个unique_ptr：

```c++
// 下面两个函数都能正常返回
unique_ptr<int> clone(int p)
{
    return unique_ptr<int>(new int(p));
}

unique_ptr<int> clone(int p)
{
    unique_ptr<int> res(new int(p));
    
    return ret;
}
```

##### `unique_ptr`删除器

`unique_ptr`管理删除器的方式与shared_ptr有些不同，可以有如下作用，在连接上，可以断开连接

```c++
void f(destination &d /* 需要其他参数*/)
{
    connection c = connec(&d);	// 打开连接
    // end_connection 是函数类型，所以需要添加一个*指出我们正在使用该类型的一个指针
    std::unique_ptr<connection, decltype(end_connection)*> p(&c, end_connection);
    // 使用连接
    // 当f退出时（即使是异常退出），connection会正常关闭。
}
```

#### `weak_ptr`

`weaj_ptr`是一种不控制所指向对象生存期的智能指针，它指向由一个`shared_ptr`管理的对象。将一个`weak_ptr`绑定到一个`shared_ptr`不会改变`shared_ptr`的引用计数。如果最后一个指向对象的`shared_ptr`被销毁，对象就会被释放，即使有`weak_ptr`指向该对象，该对象也会被释放的。

- w.expired()：若w.use_cout()为0，返回true，否则返回false

- w.lock()：如果expired为true，返回一个空`shared_ptr`，否则返回一个指向当w的对象的`shared_ptr`

  ```c++
  if (shared_ptr<int> np = wp.lock())		// 如果np不为空则条件成立
  {
      // 在if中，np与p共享对象
  }
  ```

### 动态数组

#### new和数组

动态数组不是数组类型，使用`new T[]`分配的内存为**动态数组**是存在误导的，当用new分配一个数组时，我们并未得到数组类型的对象，而是得到一个数组元素类型的指针。

##### 释放动态数组

```c++
delete p;		// p必须指向一个动态分配的对象或为空
delete [] pa;	// pa必须指向一个动态分配的数组或为空
```

在delete一个数组指针忘了加上方括号，或者delete一个单一对象的指针时使用了方括号，编译器很可能不会给出警告，程序在执行过程中可能会没有任何警告的情况下行为异常。

- `unique_ptr`：用该版本智能指针管理new分配的数组，需要在对象类型后跟一对方括号，调用release函数会自动调用`delete[]`方式进行清除。

- `shared_ptr` ：该版本智能指针管理new分配的数组，需要自己提供定义好的删除器，如果未提供删除器，那么将是未定义的，默认情况下会调用delete清除数组，而不是`delete[]`方式清除数组了。example:

  ```c++
  shared_ptr<int> sp(new int[10], [](int *p) { delete[] p;} );
  sp.reset();		//使用自定义的删除器进行数组的释放
  
  // shared_ptr不直接支持动态数组管理
  // shared_ptr未定义下标运算符，并且不支持指针的算术运算
  for (size_t i = 0; i != 10; i++)
  {
      *(sp.get() + i) = i;	//使用get获取一个内置指针
  }
  ```

#### allocator类

帮助我们将内存分配和对象构造分离开来，定义一个allocator对象，我们要指明allocator可以分配的对象类型。当一个allocator对象分配内存时，它会根据给定的对象类型来确定恰当的内存大小和对齐位置

```c++
allocator<string> alloc;		//可以分配string的allocator对象
auto const p = alloc.allocate(n);	// 分配n个未初始化的string

```

为了使用allocate返回的内存，我们必须使用construct构造对象。使用为构造的内存，其行为是未定义的。直接使用未构造的对象是会有问题的。

allocator中，我们只能对真正构造了的元素进行destroy操作，不过这些销毁的元素我们可以重新使用这部分内存来保存其它string，可以将其归还系统。释放内存通过调用deallocate来完成

`alloc.deallocate(p, n);`

### 使用标准库：文本查询程序

```c++
#include <map.h>
#include <vector.h>
#include <set.h>
#include <iostream>

class TextQuery
{
public:
    TextQuery(ifstream& infile);
    QueryResult query(const std::string& s);
public:
private:
    map<string, std::shared_ptr<std::set<int>>> mapData;
    std::shared_ptr<vector<string>> lineData;	// 输入文件
};

TextQuery::TextQuery(ifstream& infile)
{
    string line;
    stirng word;
    int lineNum = 1;
    while (getline(infile, line))
    {
        //lineData.push_back(line);
        lineData->push_back(line);
        istringstream issline(line);
        while (issline >> word)
        {
        	if (mapData.find(word) != mapData.end())
            {
                mapData[word]->insert(lineNum);
                
            }
            else
            {
                mapData.insert(pair<string, std::shared_ptr<set<int>>>(word, make_shared(new set<int>));
                mapData[word]->insert(lineNum);
            }
            
        }
        lineNum++;
    }
};

QueryResult TextQuery::query(const std::string& s)
{
    static shared_ptr<set<int>> nodata(new set<int>);
    auto loc = mapData.find(s);
    if (loc = mapData.end())
    {
        return QueryResult(s, nodata, lineData);	// 未找到单词
    }
    else
    {
        return QueryResult(s, loc->second, lineData);
    }
}

class QueryResult
{
friend std::ostream& print(std::ostream&, const QueryResult&);
public:
    QueryResult(std::string s, std::shared_ptr<std::set<int>> p, std::shared_ptr<std::vector<std::string>> f): sought(s), lines(p), file(f) { }
private:
    std::string sought;		// 查询单词
    std::shared_ptr<std::set<int>> lines;				// 出现的行号
    std::shared_ptr<std::vector<std::string>> file;		 // 输入文件
};
                               
ostream &print(ostream & os, const QueryResult& qr)
{
    // 调用make_plural来根据szie大小是否等于1打印time或times
    os << qr.sought << " occurs " << qr.lines->size() << " " << make_plural(qr.lines->size(), "time", "s") << endl;
    for (auto num : *qr.lines)
        os << "\t(line " << num << ") " << *(qr.file->begin() + num-1) << endl;
    return os;
}

void runQueries(ifstream &infile)
{
    // infile 是一个ifstream，指向我们要处理的文件
    TextQuery tq(infile);	// 保存文件并建立查询map
    // 与用户交互：提示用户输入要查询的单词，完成查询并打印结果
    while (true)
    {
        cout << "Enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q")
            break;
        print(cout, tq.query(s)) << endl;
    }
}
```

## 拷贝控制

一个类通过五种特殊的成员函数来控制这些操作，包括：拷贝构造函数，拷贝赋值运算符，移动构造函数、移动赋值运算符和析构函数。

### 拷贝、赋值与销毁

#### 拷贝构造函数

拷贝构造函数的第一个参数必须是引用类型，原因如下：

- 因为如果在对第一个形参进行初始化时候，如果是非引用类型，那么我们必须拷贝实参，而我们需要调用实参则需要调用拷贝构造函数，如此循环进行，就无法成功调用。

拷贝构造函数通常不应该是explicit的，拷贝构造在几种情况下都会被隐式地使用。

拷贝初始化发生情况

- 在使用=定义变量时
- 将一个对象作为实参传递给一个非引用类型的形参
- 将一个返回类型为非引用类型的函数返回一个对象
- 用花括号列表初始化一个数组中的元素或一个聚合类中的成员
- 在某些类类型中，还会对它们所分配的对象使用拷贝初始化。例如，当我们初始化标准库容器或事调用其inert或push成员时，容器会对其元素进行拷贝初始化。与之相对，用emplace成员创建的元素都进行直接初始化。

##### 编译器可以绕开拷贝构造函数

例子如下

```c++
string test = "12345";	// 拷贝初始化
string test("12345");	// 编译器略过了拷贝构造函数
```

#### 拷贝赋值运算符

与处理拷贝构造函数一样，如果一个类未定义自己的拷贝构造赋值运算符，编译器会为它生成一个合成拷贝赋值运算符。

#### 析构函数

析构函数不接受参数，因此它不能被重载。所以一个给定的类，只会有唯一一个析构函数。

隐式销毁一个内置指针类型的成员不会delete它所指向的对象。

当指向一个对象的引用或指针离开作用域时，析构函数不会执行

#### 三/五法则

有三个基本操作可以控制类的拷贝操作：拷贝构造函数、拷贝赋值运算符和析构函数，在C++11新的标准下，还可以定义移动构造函数和移动赋值运算符。三/五法则如下

- 需要析构函数的类也需要拷贝和赋值操作
- 需要拷贝操作的类也需要赋值操作，反之亦然

##### 需要析构函数的类也需要拷贝和赋值操作

在直接使用析构函数而不是合成析构函数时，那么析构函数一般会释放指针数据成员，而合成析构函数不会释放指针数据成员，所以在这里我们如果不自己定义拷贝和赋值操作，那么默认的合成拷贝和赋值操作就会是简单的拷贝指针，那么多个对象都会包含相同的指针值，只要其中一个对象析构了，那么就会导致其它对象析构会报错，因为指针数据已经不存在了。

##### 需要拷贝操作的类也需要赋值操作，反之亦然

如果为每个对象分配独一无二序号，这个类需要自定义拷贝函数为每个新创建的对象生成一个新的、独一无二的序号。除此之外，这个拷贝函数从给定对象拷贝所有其他数据成员。这个类还需要定义拷贝赋值运算符，几乎可以肯定它也需要一个拷贝构造函数。

##### 使用`=default`

通过将拷贝控制成员定义为=default来显式地要求编译器生成合成的版本。

我们只能对具有合成版本的成员函数使用`=default`（即，默认构造函数或拷贝控制成员）。

##### 阻止拷贝

```c++
struct NoCopy
{
    NoCopy() = default;
    NoCopy(const Nocopy&) = delete;		// 阻止拷贝
    NoCopy &operator=(const NoCopy&) = delete;		// 阻止赋值
    ~NoCopy() = default;				// 使用合成的析构函数
    // 其它成员
}：
```

使用`=delete`表示我们通知编译器（以及我们代码的读者），我们不希望定义这些成员。同时析构函数不能使用`=delete`方式，因为如果使用这种方式，一个对象就永远无法被正常销毁了

`=delete`和`=default`的区别是，前者可以定义任何函数使用，而后者是只能对编译器可以合成的默认构造函数或拷贝控制成员使用

##### 合成的拷贝控制成员可能是删除的

对某些类来说，编译器将这些合成的成员定义为删除的函数的情况如下：

- 如果类的某个成员的析构函数是删除的或不可访问的（例如是private的），则类的合成析构函数被定义为删除的
- 如果类的某个成员的拷贝构造函数是删除的或不可访问的，则类的合成拷贝构造函数被定义为删除的。**如果类的某个成员的析构函数是删除的或不可访问的，则类合成的拷贝构造函数也被定义为删除的**。
  - 如果类合成的拷贝函数可能会创建出无法删除的对象。
- 如果类的某个成员的拷贝赋值运算符是删除的或不可访问的，或是类有一个const的或引用成员，则类的合成拷贝赋值运算符被定义为删除的。
  - 如果是引用的话，引用在初始化完后，就无法改变变量所对应的对象，再次赋值就只是修改对象的值或者说该内存块内的值
- 如果类的某个成员的析构函数是删除的或不可访问的，或是类有一个引用成员，它没有类内初始化器，或是类有一个const成员，他们没有类内初始化器且其类型未显示定义默认构造函数，则该类的默认构造函数被定义为删除的。

**希望阻止拷贝的类应该使用=delete来定义它们自己的拷贝构造函数和拷贝赋值运算符，而不应该将它们声明为private的**

### 拷贝控制和资源管理

#### 行为像值的类

```c++
// 类值版本
class HasPtr
{
    HasPtr(const std::string &s = std::string()): ps(new std::string(s)), i(0)
    {
        
    }
    HasPtr(const HasPtr &p): ps(new std::string(p.ps)), i(p.i)
    {
        
    }
    HasPtr& operator=(const HasPtr &p)
    {
        auto data = new std::string(*p.ps);
        delete ps;
        ps = data;
        i = p.i;
        return *this;
    }
public:
    int i;
    std::string *ps;
}
```

编写赋值运算符时，有两点需要记住：

- 如果将一个对象赋予在它身上，赋值运算符必须能正确工作。
- 大多数赋值运算符组合了析构函数和拷贝构造函数的工作。

对于一个赋值运算符，正确工作是非常重要的，即使是将一个对象赋予它自身，也要能正确工作。一个好的办法是在销毁左侧运算对象资源之前拷贝右侧运算对象。

#### 定义行为像指针的类

通过拷贝构造或拷贝赋值运算符，拷贝指针成员的本身而不是它指向的string，因为在析构的时候，只有最后一个指针成员的对象销毁时，才能进行析构指针内存，可以采取智能指针`shared_ptr`方式解决，但是如果想直接管理资源，在这种情况下，使用**引用计数**就很有用了。

**引用计数**工作方式如下：

- 除了初始化对象外，每个构造函数（拷贝构造函数除外）还要创建一个引用计数，用来记录有多少对象与正在创建的对象共享状态。当我们创建一个对象时，只有一个对象共享状态，因此将计数器初始化为1。
- 拷贝构造函数不分配新的计数器，而是拷贝给定对象的数据数据成员，包括计数器。拷贝构造函数递增共享的计数器，指出给定对象的状态又被一个新用户所共享。
- 析构函数递减计数器，指出共享状态的用户少了一个。如果计数器变为0，则析构函数释放状态。
- 拷贝赋值运算符递增右侧运算对象的计数器，递减左侧运算对象的计数器。如果左侧运算对象的计数器变为0，意味着它的共享状态没有了用户，拷贝赋值运算符就必须销毁状态。

```c++
// 类指针的HasPtr版本
class HasPtr
{
public:
    HasPtr(const std::strig &s = std::string()): ps(new std::string(s)), i(0), use(new std::size_t(1))
    {
    }
    HasPtr(const HasPtr &p): ps(p.ps), i(ps.i), use(p.use)
    {
        ++*use;
    }
    HasPtr& operator=(const HasPtr &p)
    {
        --*use;
        if (*use == 0)
        {
            delete use;
            delete ps;
        }
        ps = p.ps;
        use = p.use;
        i = p.i;
        ++*use;
        return *this;
    }
    ~HasPtr()
    {
        if(--*use == 0)
        {
            delete use;
            delete ps;
        }
    }
public:
    int i;
    std::string* ps;
    std::size_t* use;
}
```

### 移动语义

移动构造函数需要声明`noexcept`，例如在使用时候如果标准库容器`vector`进行`push_back`时候，发生异常，vector保证，如果我们调用`push_back`时发生异常，vector自身不会发生改变，如果是拷贝构造，发生了直接可以回退到原来的内存上，但是移动构造上在没有进行完所有的元素移动后，触发异常，就会导致已经有部分元素被移动了，新空间中未构造的元素可能尚不存在，这种情况下，vector将不能满足自身保持不变的要求。

#### 移动赋值运算符

移动赋值运算符执行与析构函数和移动构造函数相同的工作，如果我们移动赋值运算符不抛出任何异常，我们应该将它标记为noexcept。

**在移动操作后，移后源对象必须保持有效的、可惜狗的状态，但是用户不能对其值进行任何假设**

#### 合成的移动构造

在类中已经定义了拷贝构造函数和拷贝赋值运算符以及析构函数时，编译器不会为它合成移动构造函数和移动赋值运算符。

编译器合成移动构造函数或移动赋值运算符的条件是，一个类没有定义任何自己版本的拷贝控制成员，且类的每个非static数据成员都可以移动。如果一个成员时类类型，且该类有对应的移动操作，编译器也能移动这个成员。

什么时候将合成的移动操作定义为删除的函数遵循与定义删除的合成拷贝操作类似的原则：

- 与拷贝构造函数不同，移动构造函数被定义为删除的函数条件是：有类成员定义了自己的拷贝构造函数且未定义移动构造函数，或者是有类成员未定义自己的拷贝构造函数且编译器不能为其合成移动构造函数。移动赋值运算符的情况类似
- 如果有类成员的移动构造函数或者移动赋值运算符被定义为删除的或是不可访问的，则类的移动构造函数或移动赋值运算符被定义为删除的。
- 类似拷贝构造函数，如果类的析构函数被定义为删除的或不可访问的，则类的移动构造函数被定义为删除的。
- 类似拷贝构造运算符，如果类成员是const的或是引用，则类的移动赋值运算符被定义为删除的。

**定义了一个移动构造函数或移动赋值运算符的类必须也定义自己的拷贝操作。否则这些成员默认地被定义为删除的**

**如果一个类有一个可用的拷贝构造函数而没有移动构造函数，则其对象是通过拷贝构造函数来“移动”的。拷贝赋值运算符和移动赋值运算符的情况类似。**

#### 拷贝并交换赋值运算符和移动操作

```c++
class HasPtr
{
public:
    // 添加的移动构造函数
    HasPtr(HasPtr &&p) noexcept : ps(p.ps), i(p.i) {p.ps = 0;}
    // 赋值运算符即是移动赋值运算符也是拷贝赋值运算符
    HasPtr& operator=(HasPtr rhs)
    {
        swap(*this, rhs);
        return *this;
    }
    // 其它成员的定义
}
```

### 右值引用和成员函数

```c++
string s1 = "a value", s2 = "another";
auto n = (s1 + s2).find('a');
s1 + s2 = "wow!";

// 在这里，s1 + s2是一个右值，可以对其进行赋值和查找，这是以前版本导致的
// 现在我们希望左侧运算对象(this)是一个左值
// 我们可以在参数列表后放置一个引用限定符
class Foo
{
public:
    Foo &operator=(const Foo&) &;	// 只能向可修改的左值赋值
    // Foo的其他参数
};

Foo &Foo::operator=(const Foo &rhs) &
{
    // 执行将rhs赋予本对象所需要的工作
    return *this;
}

```

引用限定符可以是&和&&，分别指出this可以指向左值或右值。类似const限定符，引用限定符只能用于（非static）成员函数，且必须同时出现在函数的声明和定义中，但是const限定符在引用限定符前。

对于&限定的函数，我们只能将它用于左值；对于&&限定的函数，只能用于右值

```c++
Foo &retFoo();		//返回一个引用；retFoo调用是一个左值
Foo retVal();		// 返回一个值；retVal调用是一个右值
Foo i, j;			// i和j是左值
i = j;				// 正确i是左值
retFoo() = j;		// 正确：retFoo()返回一个左值
retVal() = j;		// 错误：retVal()返回一个右值
i = retVal();		// 正确：我们可以将一个右值作为赋值操作的右侧运算对象
```

**注意：**如果我们定义两个或两个以上具有相同名字和相同参数列表的成员函数，就必须对相应的所有函数都加上引用限定符，或者所有都不加。

## 重载



### 四则运算符重载

```c++
class Couple
{
    public:
    	Couple(int a = 0, int b = 0): _a(a), _b(b) {
        }
    	Couple operator+(const Couple & c);
    	Couple operator*(const Couple & c);
    	Couple operator*(const int & k);
    private:
    	int _a, _b;
};

Couple Couple::opeartor+(const Couple & c)
{
    Couple _t(this->_a + c._a, this->_b + c._b);
    return _t;
}
Couple Couple::operator*(const Couple & c)
{
    Couple _t(this->_a * c._a, this->_b * c._b);
    return _t;
}

Couple Couple::operator*(const int & k)
{
    Couple _t(this->_a * k, this->_b * k);
    return _t;
}

int main()
{
    Couple a(1, 2), b(3, 4), c, d; 
    c = a + b; // 等价于 c = a.operator+(b) ==> c(4, 6)
    d = a + b + c; // 等价于 c = a.operator+(b).operator+(c) ==> d(8, 12)
    c = a * b; // 等价于 c = a.operator*(b) ==> c(3, 8)
    return 0;
}
```

#### 参数必须是Couple类的对象吗？

- 可以不使用引用，但会产生对象拷贝动作（对象拷贝到形式参数上），降低效率
- 可以不是常引用，但无法限制函数内部对参数的修改
- 可以使用指针，但与常规数学公式使用方式不符合

#### 返回值必须是Couple类的对象吗？返回引用是否可行？

- 可以返回引用，但必须是全局对象或通过参数传递进去的Couple对象的引用，不能引用函数内部的局部变量
- 不建议使用引用类型的返回值
- 需要将右操作数累加到左操作数上并返回左操作数时，此时应该重载加赋等操作符，减赋、乘赋、除赋与余赋类似

#### 四则运算符必须重载为成员函数吗？

- 不。可以重载为类的友元函数或普通函数。注意：普通函数无法访问类的私有成员
- 建议重载为友元函数

##### 重载为友元函数

- 优势：显示具有双操作数，且格式一致；操作不局限于当前对象本身，且不要求左操作数必须为本类的对象

- 劣势：显示具有双操作数，不能省略左操作数

  ```c++
  // 重载为友元函数例子：
  class Couple
  {
      public:
      	Couple(int a = 0, int b = 0): _a(a), _b(b) { }
      	friend Couple operator+(const Couple & c1, const Couple & c2);
      	friend Couple operator*(const Couple & c1, const Couple & c2);
      	friend Couple operator*(const Couple & c, const int & k);
      	friend Couple operator*(const int & k, const Couple & c);
      private:
      	int _a, _b;
  };
  ```

##### 数偶数倍乘运算重载的说明

- 应重载为类的友元函数
- 若非友元函数，当倍数为左操作数时，无法解析乘法运算，编译会出错
- 将左操作数k转换为Couple类的对象可以解决上述问题，但意义已不同
- 上述转换要求提供一个单参数的从整数到Couple类的构造函数，如果使用`explicit`修饰改构造函数，隐式类型转换会被禁止；虽然即使不禁止，很多编译器也不进行此转换
- 左右操作数不可互换，重载函数碧玺提供两个版本，它们的函数签名不同。

### 关系与下标操作符重载

#### 为数偶类定义专用的关系操作符

```c++
class Couple
{
	public:
    	Couple(int a = 0, int b = 0): _a(a), _b(b){}
    	friend bool operator==(const Couple & c1, const Couple & c2);
    	friend bool operator!=(const Couple & c1, const Couple & c2);
    private:
    	int _a, _b;
};

bool operator==(const Couple & c1, const Couple & c2)
{
    return (c1._a == c2._a) && (c1._b == c2._b);
}
```

#### 下标操作符重载

##### 下标操作符重载的场合与目的

- 如果对象具有数组成员，且该成员为主要成员，可以重载下标操作符
- 目的：以允许在对象上通过数组下标访问改数组成员的元素

##### 下标操作符必须提供两个版本

- 常函数版本用于处理常量

##### 数组下标越界错误

- 可以再重载函数中处理数组下标越界错误，或使用异常处理机制

```c++
class Couple
{
    public:
    	Couple(int a = 0, int b = 0) { _a[0]=a, _a[1]=b;}
    	int & operator[](int index);
    	const int & operator[](int index) const;
    private:
    	int _a[2];
};

int & operator[](int idnex)
{
    if(index < - || index > 1)
        throw std::out_of_range("index is out of range!");
    return _a[index];
}


const int & operator[](int index) const
{
    if(index < 0 || index > 1)
        throw std::out_of_range("Index is out of range!");
    
    return _a[index];
}


int main()
{
    Couple a(1, 2), b(3, 4);
    cin >> a[0] >> a[1];
    cout << b[0] << " " << b[1] << endl;
    return 0;
}
```



### 赋值操作符重载

#### 赋值操作符重载的一般形式

```c++
// 为数偶类定义专用的赋值操作符
class Couple
{
    public:
    	Couple(int a = 0, int b = 0): _a(a), _b(b){}
    	Couple(const Couple & c): _a(c._a), _b(c._b){}
    Couple & operator=(const Couple & c);
    Couple & operator+=(const Conple & c);
    Couple & operator*=(const Couple & c);
    Couple & operator*=(const int k);
    Couple & operator++();   // 前缀递增
    Couple operator++(int); //后缀递增
    private:
    	int _a, _b;
};

Couple & Couple::operator=(const Couple & c)
{
    if(*this == c)
        return *this;
    _a = c._a;
    _b = c._b;
    return *this;
}

Couple & Couple::operator+=(const Couple & c)
{
    _a += c._a;
    _b += b._b;
    return *this;
}

Couple & Couple::operator*=(const Couple & c)
{
    _a *= c._a;
    _b *= c._b;
    return &this;
}

Couple & Couple::operator+=(const int k)
{
    _a *= k;
    _b *= k;
    return *this;
}
Couple & Couple::opertor++()
{
    ++_a, ++_b;
    return *this;
}

Couple Couple::operator++(int)
{
    Couple _t(*this);
    _a++, _b++;
    return _t;
}
```

##### 赋值操作符的返回值

- 除后缀递增递减操作符，应返回对象的引用，以于C++本身语义相符
- 返回对象需要额外的对象构造，降低效率
- 如果不需要使用返回值以进行连续赋值，可以将返回值设为void，但要注意此时重载的操作符语义与c++不符，不推荐

#### 符合赋值操作符重载


赋值也是一种构造，拷贝、赋值与析构三位一体，一般同时出现

- 缺省赋值构造与拷贝构造为浅构造

- 如果对象没有指针，一般需要重载这三个函数

- 如果对象有指针成员，一般需要重载这三个函数


#### 赋值构造与拷贝构造


  ```c++
  // 浅拷贝和深拷贝
  class A
  {
      public:
      	A(): _n(0), _p(NULL) {}
      	explicit A(int n): _n(n), _p(new int[n]) {}
      	A(int n, int *p): _n(n), _p(p) {}
      	// 后面两行是浅拷贝
      	A(const A & that): _n(that._n), _p(that._p) {}
      	A & operator=(const A & that) { _n = that._n, _p = that._p; return *this;}
      	// 后面两行是深拷贝
      	A(const A & that);
      	A & operator=(const A & that);
      	virtual ~A() { if(_p){ delete[] _p, _p = NULL;}}
      public:
      	int & operator[](int i);
      	const int & operator[](int i) const;
      private:
      	int _n;
      	int *p;
  };
  
  
  // 实现深拷贝
  A::A(const A & that)
  {
      this->_n =  that._n;
      _p = new int[_n];
      for(int i = 0; i < _n; i++)
      {
          _p[i] = that._p[i];
      }
  }
  
  A & A::operator=(const A & that)
  {
      this->_n = that._n;
      if(_p)
          delete[] _p;
      _p = new int[_n];
      for(int i = 0; i < _n; i++)
          _p[i] = that._p[i];
      return *this;
  }
  
  
  ```

  

#### 移动语义（C++11）

介绍：移动语义可以将A对象的指针成员所拥有值，转移给B对象，B对象拥有其所有权，A对象将丧失其所有权，可以减少在深拷贝时，B对象重新动态分配内存空间，进行拷贝。

##### 左值与右值

###### C原始定义

- 左值：可以出现在赋值号左边或右边
- 右值：只能出现在赋值号右边

###### C++定义

- 左值：用于标识非临时对象或非成员函数的表达式，使用的是对象的身份（在内存中的地址）
- 右值：用于标识临时对象的表达式或与任何对象无关的值（纯右值），或者用于标识即将失效的对象的表达式（失效值），使用的是对象的值

##### 左值引用与右值引用

左值引用：`&`

- 无法令左值引用绑定到另外一个对象，所以右值引用必须初始化，

右值引用：`&&`

- 深拷贝需要频繁分配和释放内存，效率极低
- 移动语义的目的：所有权移交，不需要重新构造和析构
- 为与构造函数兼容，移动语义必须为引用，而不能是指针或普通量
- 普通引用传递左值，以允许函数内部修改目标数据对象
- 为区分左值引用，实现移动语义时，必须传递右值引用
- 为确保能够修改目标数据对象，在函数内部必须将右值引用作为左值引用对待

##### 移动赋值与移动构造

```c++
// 移动赋值与移动构造示例
  class A
  {
      public:
      	A(): _n(0), _p(NULL) {}
      	explicit A(int n): _n(n), _p(new int[n]) {}
      	A(int n, int *p): _n(n), _p(p) {}
      	A(A && that);
      	A & operator=(A && that);
      	virtual ~A() { if(_p){ delete[] _p, _p = NULL;}}
      public:
      	int & operator[](int i);
      	const int & operator[](int i) const;
      private:
      	int _n;
      	int *p;
  };

A::A(A && that)
{
    // nullptr: C++11预定义的空指针类型nullptr_t的常对象
    // 可隐式转换为任意指针类型和bool类型，但不能转换为整数类型，以取代NULL
    _n = that._n, _p = that._p, that._n = 0, that._p = nullptr;
    // *this = that; //此代码不会调用下面重载的赋值操作符函数，因为that在函数内是左值，不能当做右值使用，可以传左值引用，不能传右值引用，不能将that（这是左值）传给 A && that（这是右值引用），参数类型不匹配，编译器会报错
    // 具名右值引用that在函数内部被当做左值，不是右值
    // 匿名右值引用才会被当做 右值；理论上如此
    // *this = static_cast<A &&>(that); // 等价于  *this = std::move(that);
    // 上一行代码可以调用下面重载的移动赋值操作符，但是有可能导致程序崩溃
    // 因this指向的本对象可能刚刚分配内存，_p字段所指向的目标数据对象无定义
}

A & A::opeartor=(A && that)
{
    if(_p)
        delete[] _p; // 删除此行代码可能会导致内存泄漏
    // 可以测试是否为同一对象，以避免自身赋值操作，但意义不大
    _n = that._n, _p = that._p, that._n = 0, that._p = nullptr;
    return *this;
}
  
```



##### 移动语义重载

```c++
// 移动语义
// 移动赋值与移动构造示例
  class A
  {
      public:
      	A(): _n(0), _p(NULL) {}
      	explicit A(int n): _n(n), _p(new int[n]) {}
      	A(int n, int *p): _n(n), _p(p) {}
      	// 可以同时提供拷贝构造语义与移动语义版本，前者使用常左值引用
        // 不能修改目标数据对象的值，后者则可以修改
      	A(const A & that);
      	A(A && that);
      	A & operator=(const A & that);
      	A & operator=(A && that);
      	virtual ~A() { if(_p){ delete[] _p, _p = NULL;}}
      public:
      	int & operator[](int i);
      	const int & operator[](int i) const;
      private:
      	int _n;
      	int *p;
 };


int main()
{
    A a(4);
    for(int i = 0; i < 4; i++)
        a[i] = i + 1;
    A b(a);	// 调用拷贝构造版本
    b = a;	// 调用普通赋值版本
    
    // 把左值引用转换为右值引用，否则会调用左值版本
    A c(static_cast<A && >(a));	// 调用移动构造版本
    c = static_cast<A && >(a);	// 调用移动赋值版本
}

```

##### 右值引用的意义

- 右值引用可以使用文字作为函数实际参数

  ```c++
  // 不接受文字作为实际参数，因无法获取文字的左值，就是说如直接传进10
  int f(int & x) {return ++x;}
  
  // 接受文字作为实际参数，传递右值引用
  // 具名右值引用作为左值，匿名右值引用作为右值
  // 在函数内部理论如此，但实际上
  int f(int && x) { return ++x; }
  
  
  int main()
  {
      // 错误代码，++操作符的操作数必须为左值
      // std::cout << ++10 << std::endl;
      // 可能有问题，传递右值引用，但部分编译器可能将其作为左值
      std::cout << f(10) << std::endl; // 11?
      return 0;
  }
  ```

- 避免编写过多的构造与赋值函数
  - 不管是左值引用 还是右值引用，若同时提供拷贝语义与移动语义，需要2对（4个）构造和赋值函数
  - 若通过单独提供成员值得方式构造对象，单成员至少需要2对（4个）构造和赋值函数，双成员至少需要4对（8个）构造和赋值函数
  - 使用右值引用，通过函数模块可以缩减代码编写量
- 完美实现转发

### 流操作符重载

#### 流操作符重载的一般形式

```c++
// 为数偶类定义专用的流操作符
class Couple
{
    public:
    	Couple(int a = 0, int b = 0): _a(a),_b(b) { }
    	// 必须使用此格式，以与流的连续书写特性保持一致
    	friend ostream & operator<<( ostream & os, const Couple & c);
    	friend istream & operator>>(istream & is, Couple & c);
    private:
    	int _a, _b;
};

// 注意：此处实现的流输入输出格式不统一
ostream & operator<<(ostream & os, const Couple & c)
{
    os << "(" << c._a << "," << c._b << ")" << endl;
}

istream & operator>>(istream & os, const Couple & c)
{
    is >> c._a >> c._b;
    return is;
}


int main()
{
    Couple a(1, 2), b;
    cin >> b;
    cout << a << endl;
    return 0;
}
```



#### 流与文件

##### 标准流库

流：数据从源到目的的流动

输入输出流类

- 输入输出流：iostream；输入流：istream；输出流：ostream

字符串流类

- 输入输出字符串流：strstream；输入字符串流：istrstream；输出字符串流：ostrstream

文件流类

- 输出文件流：ofstream；输入文件流：ifstream；输入输出文件流：fstream

全局流对象

- `std::cout`：标准输出流对象，一般对应标准输出设备
- `std::cin`：标准输入流对象，一般对应标准输入设备
- `std::cerr`：标准错误流对象，一般对应标准错误输出设备
- `std::clog`：标准日志流对象，一般对应标准日志输出设备
- `std::cout`、`std::cerr`与`std::ostream`为`std::ostream`类的对象；`std::cin`为`std::istream`类的对象

###### 插入与提取

插入

- 目的：将数据对象插入到流中
- 插入操作符也称为输出操作符
- std::cout << "Hello World!"； // 将字符串插入到输出流

提取

- 从流中提取数据对象
- 提取操作符也成称为输入操作符
- `int a; std::cin >> a;`     // 从输入流中提取整数

注意：因为流可能被重定向或束定，有时使用输入输出描述流操作可能会让人迷惑

###### 常用输入输出流函数

- 判断流是否已经结束：`cin.eof()`
- 读取单个字符：`cin.get(istream::char_type & c)`
- 读取字符串：`cin.get(istream::char_type * s, streamsize n, istream::char_type delimiter = '\n')`
- 读取当行文本：`cin.getline(istream::char_type * s, streamsize n, istream::char_type delimiter = '\n')`
- 读取单个字符：`cout.put(ostream::char_type c)`

##### 流格式

###### 位掩码

- 使用32位整数的位代表流格式标志：`ios_base::fmtflags`
- 每个标志位可单独设置与清除

###### 设置预定义标志位

- `cout.setf(ios_base::showbase);`		// 出书整数前缀，十六进制前添加"0x"

###### 清楚预定义标志位

###### 位组：特定标志位集合，位组中的标志位互相排斥

- `ios_base::adjustfield`、`ios_base::basefield`和`ios_base::floatfield`
- `cout.setf(ios_base::hex, ios_base::basefield);`
- 设置十六进制输出格式，使用单参数版本无效果

###### 流格式标志

设置用户自定义参数：单参数版本

- 设置时传递用户指定值
- `std::out.width(8);` 	 	     // 将最小输出宽度定为8个字符
- `std::cout.precision(8);`    // 将输出精度定为8位
- `std::cout.fill('?');`          // 使用`'?'`填充空白字符位置

获取用户自定义参数：无参数版本

- //  获得当前的输出精确度
- `std::streamsize precision = std::cout.precision();`

##### 操纵符

操纵符的目的：控制流的输入输出格式

- 无参数操纵符函数指针
- 单参数操纵符：函子，既带有函数指针功能的操纵符类的对象，实际上为重载了函数调用操作符的操纵符类

操纵符实例

```c++
// 头文件 "iomanip"
std::cout << "Hello World!" << std::endl;
int n = 1024;
// dec为十进制操纵符，hex为十六进制操纵符，endl为无参数的换行符
std::cout << std::dec << n << '\n' << std::hex << n << std::endl;
```



##### 文件流

###### 文件特性

- 文件一般保存在外部存储设备上
- 文件生命周期可能远远超过创建它的程序本身

###### 文件操作：读、写

- 一般使用文件指针，该指针代表文件的当前访问位置
- 老式的C语言使用文件句柄（handle）或文件描述符（file descriptor）表示某个打开的文件数据对象

###### 文件流的作用

- 头文件：“fstream”
- 按照特定格式重载类的流操作符
- 创建文件流对象，输入输出

###### 文件打开模式

- `std::ios_base::app`：每次插入都定位到文件流的尾部
- `std::ios_base::binary`：使用二进制而不是文本格式打开文件流
- `std::ios_base::in`：流用于输入目的，允许提取，此为`std::ifstream`流缺省设置
- `std::ios_base:out`：流用于输出目的，允许插入，此为`std::ofstream`流缺省设置
- `std::ios_base::trunc`：若文件存在，清楚文件内容，此为`std::ofstream`流缺省设置
- `std::ios_base::ate`：若文件存在，定位到文件尾部文件一般保存在外部存储设备上

##### 状态流

###### 流状态：表示操作成功或失败的状态信息

- `std::ios_base::goodbit`：流完好无损
- `std::ios_base::badbit` ：流已经出现致命错误，一般无法恢复
- `std::ios_base::eofbit` ：流结束时设置
- `std::ios_base::failbit` ：流操作失败时设置

###### 流状态对流操作行为的影响

- 一旦流状态存在错误，所有I/O操作都失效
- 在出现`std::ios_base::failbit`与`std::ios_base::badbit`状态时，输出操作立即停止
- 在非`std::ios_base::goodbit`状态时，输入操作立即停止

##### 流定位

###### 流位置指针

- 位置指针指向下一次读写操作时的数据对象在流中的位置，该指针会随着输入输出操作而不断变化
- 单向流：一个位置指针；
- 双向流：两个位置指针；

###### 留位置指针的获取

- 成员函数`tellp()` ：获取当前的流位置指针（写指针）
- 成员函数`tellg()`：获取当前的流位置指针（读指针）

###### 流位置指针的 定位

- 成员函数`seekp()` ：将文件位置指针定位到某个特定位置，用于插入（输出）目的
- 成员函数`seekg()` ：将文件位置指针定位到某个特定位置，用于提取（输入）目的的定位

###### 流定位函数`seekp()`与`seekg()`

- 单参数版本：可以使用获取的位置指针
- 双参数版本：第一个参数为偏移量；第二个参数为定位基准

###### 定位基准

- `std::ios_base::beg` ：从流的开始位置开始计算偏移量
- `std::ios_base::cur` ：从当前位置开始计算偏移量
- `std::ios_base::end`：从流的结束位置开始和计算偏移量

#### 文件输入输出

```c++
#include <fstream>
#include "point.h"
using namespace std;

int main()
{
    ofstream ofs("~/CPP/filestream/data.txt");
    // ofs.open("~/CPP/filestream/data.txt");
    Point2D pt2d(1, 2);
    Point3D pt3d(3, 4, 5);
    ofs << pt2d;
    ofs << pt3d;
    ofs.close();
    return 0;
};
```

##### 数据持久化

持久化：将数据保存在外部文件中，在程序运行时装入内存，在程序结束时重新写回文件

###### 思考题

- 考虑下述编程任务。存在一个数据结构，需要将其数据流入流出。为提升编程效率，只在必要时进行数据结构持久化，即仅当内存中的数据发生变化时才写入文件。如何实践？提示：（1）需要考虑内存数据的来源和目的地对数据持久化的影响。（2）使用下一章将要讨论的动态型式转换技术，实现效果更佳。

### 操作符重载总结

#### 哪些操作符可以重载？

- 不可重载操作符："::"、"?:"、 "."、".*"、"sizeof"、"#"、"##"、"typeid"
- 其它操作符都可以重载

#### 操作符重载原则

- 只能使用已有的操作符，不能创建新的操作符
- 操作符也是函数，重载遵循函数重载原则
- 重载的操作符不能改变优先级与结合性，也不能改变操作数个数及语法结构
- 重载的操作符不能改变其用于内部类型对象的含义，它只能和用户自定义类型的对象一起使用，或者用于用户定义类型的对象和内部类型的对象混合使用
- 重载的操作符在功能上应与原有功能一致，即保持一致的语义

#### 操作符重载的类型：成员函数或友元函数

- 重载为类的成员函数：少一个参数（隐含this，表示二院表达式的左参数或一元表达式的参数）
- 重载为类的友元函数：没有隐含this参数

##### 成员函数与友元函数

- 一般全局常用操作符（关系操作符、逻辑操作符、流操作符）重载为友元函数。设计对象特殊运算的操作符重载为成员函数
- 一般单目操作符重载为成员函数，双目操作符重载为友元函数
- 部分双目操作符不能重载为友元函数："="、"()"、"[]"、"->"
- 类型转换操作符只能重载为成员函数

#### 重载的操作符参数：一般采用引用形式，主要与数学运算协调

- 实例：`Couple a(1,2), b(3,4),c; c = a + b;`
- 若有定义：`Couple Couple::operator+(Couple*, Couple*){ ... }`
- 则需调用：`Couple a(1,2), b(3,4), c; c = &a + &b`

### 重载、类型转换与运算符

类型转换运算符是类的一种特殊成员函数，它负责将一个类类型的值转换成其它类型。函数如下：

`operator type() const;`

下面是正确使用和错误使用的示例

```c++
class SmallInt;
operator int(SmallInt&);		// 错误：不是成员函数
class SmallInt
{
public:
    int operator() const;					// 错误：指定了返回类型
    operator int(int = 0) const;			// 错误：参数列表不为空
    operator int*() const { return 42; }	// 错误：42不是一个指针
    // 正确的操作，该操作可以在内置类型的前或后进行运算，只需要定义一次就行了
    operator int() const { return val; }
    // 显示类型转换：防止出现意外的错误
    // example: static_cast<int>(si) +3;
    explicit operator int() const { return val; }
}
```

##### 显示转换运算符

显示转换运算符是显式的时，我们也能执行类型转换，不过必须通过显式的强制类型转换才可以。

但是也有例外，如果表达式被用作条件，编译器会自动将显式的类型转换自动应用于它。在下列情况，显式的类型转换将被隐式地执行：

- if、while及do语句的条件部分
- for语句头的条件表达式
- 逻辑非运算符（!），逻辑或运算符（||）、逻辑与运算符（&&）的运算对象
- 条件运算符（? : ）的条件表达式

流当中有operator bool类型转换，所以容易导致出问题

**向bool的类型转换通常用在条件部分，因此operator bool一般定义成explicit的**

**除了显式地向bool类型的转换外，我们应该尽量避免定义类型转换函数，并尽可能地显式那些“显然正确”的非显式构造函数**

### 编程实践 

#### 第一题

使用面向对象技术完成习题7.1，并未有理数类重载必要的操作符

#### 第二题

new与delete操作符可以被重载。研究存储管理技术，重载这两个操作符一实现程序独有的动态存储管理策略。

## 面向对象程序设计

### 继承中的类作用域

#### 在编译是进行名字查找

一个派生类定义了某个成员函数，那么我们只能通过该派生类对象及其派生类的派生类的对象、引用或指针使用定义了的成员函数

### 构造函数与拷贝控制

#### 合成拷贝控制与继承

##### 派生类中删除的拷贝控制与基类的关系

- 如果基类中的默认构造参数、拷贝构造参数、拷贝赋值运算或析构函数是被删除的或者不可访问的，则派生类中对应的成员将是被删除的，原因是编译器不能使用基类成员来执行派生类对象基类部分的构造、赋值或销毁操作。
- 如果在基类中有一个不可访问或删除掉的析构函数，则派生类中合成的默认和拷贝函数将是被删除的，因为编译器无法销毁派生类对象的基类部f份
- 和过去一样，编译器将不会合成一个删除掉的移动操作。当我们使用`=default`请求一个移动操作时，如果基类中对应操作是删除的或不可访问的，那么派生类中该函数将是被删除的，原因是派生类对象的基类部分不可以移动。同样，如果基类的析构函数是删除的活不可访问的，则派生类的移动构造函数也将是被删除的。

#### 继承的构造函数

在继承的构造函数中，如果构造函数中有默认参数（n个），那么继承的构造函数是会继承除了默认构造函数，还有没有形参的构造函数，总数是（n+1个）

继承的构造函数的，在除了两个例外，正常情况都能全部继承：

1. 例外一：派生类定义了自己的构造函数和继承类的构造函数的参数列表一模一样，那么就不会继承基类构造函数
2. 例外二：默认、构造和移动构造函数不会被继承。这些构造函数按照正常规则被合成。继承的构造函数不会被作为用户定义的构造函数来使用，因此，如果一个类只含有继承的构造函数，则它也将拥有一个合成的默认构造函数。

### 容器与继承

容器在存储指针的时候，最好使用智能指针进行存储，

## 模板

### 1.定义模板

### 2.模板实参推断

#### 2.1模板实参推断和引用

当一个函数参数是模板类型参数的一个普通（左值）引用时（即，形如T&）,绑定规定告诉我们，只能传递给它一个左值（如，一个变量或一个返回引用类型的表达式），无法传递右值。

##### 引用折叠

模板参数T如果它的具体类型为某类型的左值引用，那么在用到模板参数T的函数参数列表中，如果出现时右值只用：如下

```c++
template <typename T> void f(T&&);
int c = 1;
int& i = c;
// 其中T为int&，所以变成了int& &&，这个时候使用引用折叠机制，可以变为int&
f(i);
```

- 引用折叠只能应用于间接创建的引用的引用，如类型别名或模板参数

`static_cast`可以显示地将一个左值引用转化为右值引用：

```
// t为string&
static_cast<string &&>(t);
```

- 引用折叠的的好处是可以在完美的转发上使用到

## 泛型编程

### 泛型概览

什么是泛型编程？

- 泛型就是通用类型
- 编写不依赖数据对象形式的代码就是泛型编程

为什么需要泛型编程？

- 动机三问：函数重载，相似类定义与型式兼容性

怎么进行泛型编程？

- 泛型编程技术手段：模板与型式参数化

#### 函数重载问题

解决方案：使用C的含参宏

```c++
#define Min(x, y) ((x) < (y) ? (x):(y))
// 下面的等价于：a = ((b) < (c) ? (b):(c)) * ((b+c) < (b) ? (b+c) : (b));
a = Min(b.c) * Min(b+c, b);

paddlex --data_conversion --source labelme --to PascalVOC --pics G:\paddleXWork\datasets\D0006\JPEGImages --annotations G:\paddleXWork\datasets\D0006\JPEGImages --save_dir G:\paddle
```

##### 缺点

- 无型式检查，无法在编译器检查程序错误
- 宏定义替换式，要注意操作符优先级，错误的宏文本有可能导致问题

##### 结论

- 需要一种机制，能够在语法层面解决宏的问题

#### 相似类定义问题

##### 动态类数组类

- 定义存储整数的动态数组类
- 定义存储浮点数的动态数组类
- 定义存储某类对象的动态数组类
- ...

##### 结论

- 需要一种机制，能够在语法层面解决相似类的重复定义问题，降低编程工作量

#### 型式兼容性

##### C型式转换：(T)x

- 不安全
- 内建型式（int、double）对象转换安全性基本保证
- 类对象转换可能导致无法控制的严重后果

##### C++型式转换：T(x)

- 可能需要单参数构造函数和重载的型式转换操作符
- 不安全
- 如果未实现，转换就不存在

##### 类库架构

- 类的继承和多台频繁要求能够通过基类的指针或引用访问派生类的对象
- 需要沿着类的继承层次，频繁进行对象的型式转换

##### 存在问题

- C/C++已有型式转换均为静态转换，不能适应指针或引用的多态性
- 型式转换必须适应全部型式，并能自如操作；然而很不幸，型式无穷尽，程序员无法编写完备的型式转换代码

##### 保证型式兼容性的机制

- 确保型式转换操作合法有效，并在失败时通知用户
- 需要维护对象的运行期型式信息（run-time type information, RTTI）
- 转换结果确认失败：通过转换操作的返回值确认结果，或者在失败时触发特定信号；后者需要使用异常处理机制



### 异常处理机制

#### 异常处理机制基础

##### 异常的定义

- 程序中可以检测的运行不正常的情况
- 示例：被0除、数组越界、存储空间不足等

##### 异常处理的基本流程

- 某段程序代码在执行操作时发生特殊情况，引发一个特定的异常
- 另一段程序代码捕获异常并处理它

#### 异常的引发

```c++
// 栈设计中进栈和出栈引发的异常

// 异常类：空栈异常类与满栈异常类
class EStackEmpty { };
class EStackFull { };

int JuStack::Pop()
{
    if(IsEmptry())	//	引发空栈异常，构造该异常类的一个对象并抛出
        throw EStackEmpty();
    --_top, --_cnt;
    return _stk[_top];
}

void JuStack::Push(int value)
{
    if(IsFull())	//	引发满栈异常，构造该异常类的一个对象并抛出
        throw EStackFull();
    _stk[_top] = value;
    _top++, _cnt++;
}


```



#### 异常的捕获

```c++
// 主程序，异常的捕获
const int err_stack_full = 1;
int main()
{
    JuStack stack(17);
    try
    {
        for(int i = 0; i < 32; i++)
            stack.Push(i);	//	可能引发异常的函数调用
    }
    catch(const EStackFull &)	//	捕获抛出的异常，执行相应处理
    {
        std:cerr << "Error:Stack full" << std::endl;
        return err_stack_full;
    }
    return 0;
}
```



#### 异常类与异常对象

```c++
// 精心设计异常类，提供必要的异常信息
class EStackFull
{
    public:
    	EStackFull(int i): _value(i) { }
    	int GetValue() { return _value; }
    private:
    	int _value;
};

void JuStack::Push(int value)
{
    if(isFull())
        throw EStackFull(value);	//	使用value构造异常类对象并抛出
    _stk[_top] = value;
    _top++, _cnt++;
}


// 主程序
const int err_stack_full = 1;

int main()
{
    JuStack stack(17);
    try
    {
        for(int i = 0; i < 32; i++)
            stack.push(i);
    }
    catch(const EStackFull & e)		//	使用异常对象获取详细信息
    {
        std::err << "Stack full when trying to push" << e.GetValue() << std::endl;
        return err_stack_full;
    }
    
    return 0;
}
```



#### 异常处理策略

异常类可以派生和继承，形成类库架构

##### 可捕获的异常对象的型式

- 普通型式（包括类）：异常对象需要拷贝
- 对某型对象的引用：没有额外的拷贝动作
- 指向某型式对象的指针：要求对象动态构造或者在catch子句中可以访问

##### catch字句

- 可以有多个catch字句，每个负责捕获一种、一类或全部异常
- 捕获一种：catch( int )、catch( const char * )
- 捕获一类（该类或其派生类异常）：catch( const EStackFull & )
- 捕获全部：catch(...)
- 所有catch字句按照定义顺序执行，因此派生异常类处理必须定义在基类之前，否则不会被执行

##### 异常再引发

- 可以在基本任务完成后重新引发所处理的异常

- 主要用于在程序终止前写入日志和实施特殊清除任务

  ```c++
  try{
      throw AnException();
  }
  catch(...)
  {
      // ...
      throw;
  }
  ```

##### 栈展开

- 异常引发代码和异常处理代码可能属于不同函数
- 当异常发生时，沿着异常处理块的嵌套顺序逆向查找能够处理该异常的catch字句
- 如果找到catch字句，处理该异常
- 异常处理完毕后，程序保持catch子句所在的函数栈框架，不会返回引发异常的函数栈框架
- 函数栈框架消失时，局部对象被析构，但如果未执行delete操作，动态分配的目标对象未析构

##### 未处理异常

- 所有未处理的异常由预定义的std::terminate()函数处理

- 可以使用std::set_terminate()函数设置std::terminate()函数的处理例程

  ```c++
  void term_func()
  {
      exit(-1);
  }
  
  int main()
  {
      try
      {
          set_terminate(term_func);
          throw "Out of memory!";
      }
      catch(int) { /*...*/ }
      return 0;
  }
  ```

##### 描述函数是否引发异常

- 否：throw()
- 是，引发任意型式的异常：throw(...)
- 是，引发某类异常：throw(T)，部分编译器将其作为throw(...)

##### C++11规范

- 否：noexcept，等价于noexcept(true)
- 是：noexcept(false)
- 可能：noexcept(noexcept(expr))，expr为可转换为true或false
- C++11下，建议使用noexcept代替throw

#### 异常描述规范



### 运行期型式信息

#### RRTI

- 运行期标识对象的型式信息
- 优势：允许使用指向基类的指针或引用自如地操纵派生类对象
- typeid：获取表达式的型式；type_info：型式信息类
- 头文件：“typeinfo”

#### 对象转型模板

- dynamic_cast：动态转型
- static_cast：静态转型
- reinterpret_cast：复诠转型
- const_cast：常量转型

#### typeid操作符与type_info类

##### type_info类

- 编译器实现的动态型式信息型式
- 用于在程序运行时保存数据对象的型式信息
- 不能直接使用该类，只能通过typeid操作符
- 调用成员函数name()可以获得类的名称

##### typeid 操作符

```c++
//example
#include <typeinfo>
Programmer p;
Employee & e = p;
// 输出p实际类名的字符串“Programmer”
cout << typeid(e).name() << endl;
```

#### dynamic_cast

##### 动态转型的三种方式

- 向上转型：沿着类继承层次的基类转型
- 向下转型：沿着类继承层次向派生类转型
- 交叉转型：沿着类多重继承层次横向转型

##### 指针的动态转型

- 正确执行时，结果为指向目标类对象的指针
- 错误执行时，结果为0/NULL（c++11：nullptr）

##### 引用的动态转型

- 正确执行时，结果为目标类对象的引用
- 错误执行时，引发bad_cast异常

```c++
// dynamic_cast 示例：假设软件公司包括程序员和经理两类职员，需要按照不同规则支付薪水和奖金。实现如下
class Employee
{
    public:
    	virtual void PaySalary();
    	virtual void PayBonus();
};

class Manager: public Employee
{
    public:
    	virtual void PaySalary();
    	virtual void PayBonus();
};

class Programmer: public Employee
{
    public:
    	virtual void PaySalary();
    	virtual void PayBonus();
};

class Company
{
    public:
    	virtual void PayRoll(Employee * e);
    	virtual void PayRoll(Employee & e);
    private:
    	vector<Employee*> _employees;
};


// 实现
void Company::PayRoll(Employee * e)				// 版本一
{
    // 调用那个成员函数？如果区分程序员和经理？
    e->PaySalary();
    e->PaySalary();
};

void Company::PayRoll(Emplloyee & e)			// 版本二
{
    Programmer * p = dynamic_cast<Programmer*>(e);
    if(p)	// p确实指向程序员对象
    {
        p->PaySalary();
        p->PayBonus();
    }
    else	// 不指向程序员，不发奖金
        e.PaySalary();
};

void Company::PayRoll(Employee & e)				// 版本三
{
    try
    {
        Programmer & p = dynamic_cast<Programmer&>(e);
        p.PaySalary();
        p.PayBonus();
    }
    catch(std::bad_cast)
    {
        e.PaySalary();
    }
};
```

#### static_cast

##### 静态转型的用途

- 与dynamic_cast不同，static_cast不仅可用于指针和引用，海尔可用于其它型式
- 一般用于非类型式的普通数据对象转型
- 可以在类继承层次上进行向上或向下转型

##### 静态转型的问题

- 不进行运行期型式检查，不安全
- 若转型失败，结果无定义

#### reinterpret_cast

##### 复诠转型的目的

- 将任意型式的数据对象转型为目标型式，即重新解释其位序列的意义
- 可以用于整型与指针型的互转

##### 复诠转型的问题

- 由程序员保证重新解释的数据对象是否有意义，编译器简单按照目标型式理解改存储区的内容
- 注意：在64位操作系统中，指针型可能为64位，而整型可能为32位，复诠转型有可能丢失数据活的到错误结果

```c++
#include <iostream>
using namespace std;

int f(void *p)
{
    unsigned int n = reinterpret_cast<unsigned int>(p);
    return n;
}

int main()
{
    int a[8] = {1, 2, 3, 4, 5, 6, 7,8};
    int n = f(a);
    cout << n << endl;
}
```



#### const_cast

##### 常量转型的目的

- 用于取消或设置量的const状态

##### 常量转型的问题

- 如果原始数据对象不能写入，则取消常量修饰可能会导致未知结果

```c++
#include <iostream>

class ConstCastTest
{
    public:
    	void SetNum(int num) { _num = num; }
    	void PrintNum() const;
    private:
    	int _num;
};

void ConstCastTest::PrintNum() const
{
    // 临时取消常量约束，修改目标对象的内容，因为（this）是指向常对象的指针
    const_cast<ConstCastTest*>(this)->_num--;
    std::cout << _num;
}
```



### 模板与型式参数化

#### 转型操作

- 接受目标型式作为模板参数
- `Programmer * p = dynamic_cast<Programmer*>(e)`

#### 模板工作原理

- 使用template\<typename T\> 定义函数模板或类模板
- 体化（instantiation）：使用特定的模板实际参数，生成真生的模板函数和类模板
- 编译模板函数和模板类，生成最终程序代码

#### 模板代码

- 一般放在头文件中：编译器需要看到模板源代码

#### 模板特点

- 抽象性：模板代码高度抽象，是函数和类的模范
- 安全性：型式检查能够发现大多数型式失配问题
- 通用性：函数和类模板定义一次，按需生成函数和类的实体
- 易用性：接口相对直观且高度一致
- 效率：减少冗余代码，提升编程效率；通过编译优化，提升程序执行效率

#### 模板用途

- 函数模板：构造函数集，实现不依赖特定数据结构的抽象算法
- 类模板：构造类集，实现抽象数据结构
- 元编程：构造在编译器执行的运算，提升程序执行效率

#### 模板参数与作用域

- 与其他名字一样，模板参数会隐藏外层作用域中声明的相同名字。但是，与大多数其他上下文不同，在模板内不能重用模板参数名

  ```c++
  typedef double A;
  template <typename A, typename B> void f(A a, B b)
  {
      A tmp = a;	// tmp的类型为模板参数A的类型，而非double
      double B;	// 错误：重声明模板参数B
  }
  ```

  

- 由于参数名不能重用，所以一个模板参数名在一个特定模板参数列表中只能出现一次

  ```c++
  template <typename V, typename V>	//...
  ```

#### 使用类的类型成员

当我们希望通知编译器一个名字表示类型时，必须使用关键字typename，而不能使用class。

### 术语翻译

dereference：引领，好于“解引用”

type：型式，好于“类型”

constructor：建构函数或构造函数

destructor：析构函数或解构函数

#### instance：定体，好于“实例”

- 定体：固定不变的形态、性质、体例或体式；尽量不用“实体”，以区分entity
- 象体：按照类型构造对象定体或对象实体的简称，好于“对象实例”
- 函体：根据函数模板生成的函数定体或函数实体的简称
- 类体：根据类模板生成的类型定体或类型实体的简称；不使用“型体”，因为型并不仅仅只有类
- instantiation：定体化，简称体化，好于“实例化”
- specialization：特体化，简称特化

### 泛型编程实践

#### 标准模板库

##### 标准模板库的内容

- 标准模板类：附属、序偶
- 迭代器
- 标准容器：向量、表、栈、队列、集合、映射等
- 标准算法：查找、排序等

##### 标准模板库型式的使用方法

- “<>”：模板名称<数据对象基型式> 数据对象名称；
- 示例一：`complex<double> a(1.0, 2.0);`
- 示例二：`pair<string, string> name("Zhang", "San");`
- 示例三：`vector<int> v(8);`

##### 复数

###### 一般说明

- 头文件："complex"
- 模板名：complex<>
- 基型式：float、double、long double
- 首选double，float精度太低，long double 已废弃

###### 实部与虚部

- 成员函数real()与imag()

###### 复数操作

- 复数全部操作均可以按照数学格式进行
- cout、cin均已重载：格式为(real, imag)

##### 序偶

###### 一般说明

- 头文件：“utility”
- 模板名：pair<>
- 用于表示总是成对出现的两个对象
- 示例一：`pair<int, double> a(1, 1.0);`
- 示例二：`pair<string, string> name("Zhang", "San");`

###### 使用规则

- 公开的数据成员：first、second
- 示例：cout << name.first << "," << name.second;
- 偶序比较：先比较first大小，同时比较second大小
- make_pair：构造序偶的辅助函数
- 示例：`pair<int, double> a; a = make_pair(1, 1.0);`

##### 向量

###### 向量的目的

- 替代数组，可以像数组一样使用向量

###### 向量的使用

- 定义格式：vector<int> v(8); 	//包含8个整数元素
- operator[]：已重载，使用格式v[i]访问第i个元素
- 向量可以整体赋值
- size()：返回向量中元素数目
- capacity()：返回向量当前可存储的最多元素数目
- clear()：删除向量所有元素，但不释放向量本身
- resize(int newsize)：重新设置向量容量

##### 迭代器

###### 迭代器的分类

- 输入迭代器：提供对象的只读访问
- 输出迭代器：提供对象的只写访问
- 前向迭代器：提供对象的正向（递增）读写访问
- 双向迭代器：提供对象的正向与反向（递增递减）读写访问
- 随机访问迭代器：提供对象的随机读写访问

###### 指针作为迭代器

```c++
// 调用标准模板库的find()函数查找数组元素
#include <iostream>
#include <algorithm>
using namespace std;
const int size = 16;
int main
{
    int a[size];
    for (int i = 0; i < size; i++) a[i] = i;
    int * ip = find(a, a + size, key);
    if (ip == a + size )	// 不要使用NULL做指针测试，直接使用过尾值
        cout << key << " not found" << endl;
    else
        cout << key << "found." << endl;
    return 0;
}
```

###### 向量迭代器

```c++
// 使用迭代器操作向量
#include <iostream>
#include <algorithm>
#inlcude <vector>
using namespace std;
int main()
{
    int key = 7;
    vector<int> iv(10);
    for(int i = 0; i < 10; i++)
        iv[i] = i;
    vector<int>::iterator it, head = iv.begin(), tail = iv.end();
    it = find(head, tail, key);
    if(it != tail)
        cout << "Vector contains the value" << key << endl;
    else
        cout << "Vector does NOT contain the value" << key << endl;
    return 0;
};
```

###### 常迭代器

常迭代器：若不想通过迭代器修改目标对象值，定义迭代器常量

示例：

- `const vector<int>::iterator it;`
- 非法操作：*it = 10;     // 不能修改常迭代器指向的对象

###### 流迭代器

**使用迭代器访问流**

- 将输入输出流作为容器

**使用方式：定义流迭代器对象**

- 示例一：`ostream_iterator<int> oit( cout, " ");`
- 示例二：（从cin获取数据）：`istream_iterator<int> iit(cin);`
- 示例三：（使用空指针创建流结束迭代器）：`istream_iterator<int> iit;`
- 凡是可以出现迭代器参数的标准算法都可以使用

###### 输出流迭代器

```c++
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include "random.h"
using namespace std;
const int size = 8;
const int lower_bound = 10;
const int upper_bound = 99;

void Dispaly(vector<int> & v, const char *s)
{
    cout << endl << s << endl;
    vector<int>::iterator head = v.begin(), tail = v.end();
    ostream_iterator<int> oit( cout, ";");
    copy(head, tail, oit);
    cout << endl;
}

int main()
{
    vector<int> a(size);
    for(int i = 0; i < size; ++i)
        a[i] = GenerateRandomNumber(10, 99);
    Display(a, "Array generated:");
    vector<int>::iterator head = a.begin(), tail = a.end();
    sort( head, tail);
    Display(a, "Arraysorted:");
    reverse( head, tail );
    Dispaly( a, "Array reversed:");
    return 0;
}
```

###### 输入迭代器

```c++
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
using namespace std;
int main()
{
    vector<int> v(4);
    vector<int>::iterator it = v.begin();
    cout << "Enter 4 int s separated by spaces & a char:\n";
    istream_iterator<int> head(cin), tail;
    copy( head, tail, it);
    cin.clear();
    cout << "vector=";
    for( it = v.begin(); it != v.end(); it++)
        cout << *it << "";
    cout << endl;
    return 0;
}
```

###### 表

表：标准模板库中的双向链表

**表的使用**

- 定义包含Point对象的容器：list\<point\>  pts(8);
-  插入：`pts.insert(pts.begin(), Point(1, 2));`
- 表头插入：`pts.push_front(Point(1, 2));`
- 插入：`pts.insert(pts.end(), Point(1, 2));`
- 表尾插入：`pts.push_back(Point(1, 2));`
- 定义包含Point的指针容器：`list<Point*> ppts(8);`
- 插入：`ppts.insert(ppts.begin(), new Point(1,2));`
- 插入：`ppts.insert(ppts.end, new Point(1,2));`
- 删除：`delete ppts.front(); ppts.remove(ppts.front());`
- 判断表是否为空：`if(pts.empty()) cout << "Empty!";`

**表与迭代器**

- 迭代器可以和表协同工作，方式与向量相同

  ```c++
  list<int> a<8>;
  list<int>::iterator it;
  for(it = a.begin(); it!= a.end(); it++)
      *it = GenerateRandomNumber(10, 99);
  ```

**表排序**

- 直接使用表的成员函数：a.sort();	// 默认升序
- 降序排序之一：升序排序后调用成员函数reverse()

- 降序排序之二传入函子`greater_equal<int>()`：`a.sort(greater_equal<int>());`

##### 标准算法

- 查找算法
- 排序算法
- 删除和替换算法
- 排列组合算法
- 算术算法
- 关系算法
- 集合算法
- 生成和编译算法
- 堆算法
- adjacent_find：查找两个相等或满足特定条件的相邻元素
- all_of：当给定区间内的全部元素均满足条件时返回true
- any_of：当给定区间内至少一个元素满足条件时返回true
- binary_search：折半查找，原始数据集已序
- copy：赋值给定区间内的全部元素
- copy_backward：反向复制给定区间内全部元素
- copy_if：复制给定区间满足特定条件的元素
- copy_n：复制特定位置处开始的指定数目的元素
- count：返回给定区间内匹配特定值的元素个数
- count_if：返回给定区间内匹配特定条件的元素个数

##### 标准函子

###### 算术函子

- `plus<T>, minus<T>, multiplies<T>, divides<T>, modulus<T>, negate<T>`

###### 关系函子

- `equal_to<T>, not_equal_to<T>, greater<T>, greater_equal<T>, less<T>, less<equal>`

###### 逻辑函子 

- `logical_and<T>, logical_or<T>, logical_not<T>`

#### 函数模板

##### 函数模板的目的

- 设计通用函数，一适应广泛的数据型式

##### 函数模板的定义格式

- `template<模板型式参数列表> 返回值型式 函数名称(参数列表);`
- 原型：`template<class T> void Swap(T& a, T& b);`
- 实现：`template<class T> void Swap(T& a, T& b) { ... }`

##### 函数模板的体化与特化

- 针对特定型函数，在声明或第一次调用该函数模板时体化
- 每次体化都形成针对特定型参数的重载函数版本
- 文件最终只保留特定型参数的一份体化后的函体
- 显示体化主要用于库设计；显示特化覆盖体化的同型函体

```c++
// 函数模板
template< class T > void f(T t) { /*......*/ }

// 显式体化：使用显式的长整型模板参数
template void f<long>(long n);
// 显式体化：使用d的型式推导模板参数型式
template void f(double d);

// 显式特化：使用显式的整型参数
template<> void f<int> (int n);

// 显示特化：使用c的型式推到模板参数型式
template<> void f(char c);

// example
template< class T > void Swap(T & a, T & b)
{
    T t;
    t = a, a = b, b = t;
}

int main()
{
    int m = 11, n = 7; char a = 'A', b = 'B'; double c = 1.0, d = 2.0;
    Swap(m, n);
    Swap(a, b);
    Swap(c, d);
    return 0;
}
```

#### 函子

编写函数，求某个数据集的最小元，元素型式为T

- 实现策略：使用函数指针作为回调函数参数
- 实现策略：使用函子( function object, functor )作为回调函数参数

```c++
// 函数指针实现
template< typename T >
const T & Min( const T * a, int n, bool (*comparer)(const T&, const T&))
{
    int index = 0;
    for ( int i = 1; i < n; i++)
    {
        if ( conparer(a[i], a[index] ) )
            index = i;
    }
    return a[idnex];
}

// 使用函子实现

```

##### 函子的目的

- 功能上：类似函数指针
- 实现上：重载函数调用操作符，必要时重载小于比较操作符

##### 函子的优点

- 函数指针不能内联，而函子可以，效率更高
- 函子可以拥有任意数量的额外数据，可以保存结果和状态，提高代码灵活性
- 编译时可对函子进行型式检查

##### 函子实现

```c++
// 使用方法
int a[8] = { 2, 3, 1, 6, 4, 5, 8, 7};
int min = Min(a, 8, Comparer<int>());	// 构造匿名函子作为函数参数

template< typename T > class Comparer
{
    public:
    	// 确保型式T已存在或重载operator
    	bool operator()( const T & a, const T & b) { return a < b; }
};

template< typename T, typename Comparer > const T & Min( const T * a, int n, Comparer comparer){
    int index = 0;
    for(int i = 1; i < n; i++)
        if(comparer(a[i], a[index]))
            index = i;
    return a[index];
}
```

#### 完美转发

##### 完美转发的意义

- 库的设计者需要设计一个通用函数，将接收到的参数转发给其它函数
- 转发过程中，所有参数保持原先语义不变

##### 完美转发的实现策略

- 当需要同时提供移动语义与拷贝语义时，要求重载大量建构函数，编程量巨大，易出错
- 右值引用于函数模板相互配合，可以实现完美转发，极大降低代码编写量

```c++
class A
{
    public:
    	A( const string & s, cosnt string & t): _s(s), _t(t) { }
    	A( const string &s, string && t): _s(s), _t(move(t)) { }
    	A( string && s, string && t): _s(move(s)), _t(t) { }
    	A( string && s, string && t): _s(move(s)), _t(move(t)) { }
    private:
    	string _s, _t;
};

int main()
{
    string s1("Hello");
    const string s2("World");
    A a1( s1, s2 );
    A a2( s1, string("Bingo") );
    A a3( string("Good"), s2);
    A a4( string("Good"), string("Bingo") );
    return 0;
}

// 使用完美转发
class A
{
    public:
    	// 根据实际参数型式生成不同的左值或右值引用的建构函数版本
    	// T1或T2可以为不同型，此处相同仅为示例
    	// 实参推演时，引用折叠机制
    	// 当形式参数为T&&型时，当且仅当实际参数为右值或右值引用时，
    	// 实际参数型式才为右值引用
    	// 引用折叠机制与const/volatile无关，保持其参数性质不变
    	// std::forward<T>(t)转发参数的右值引用T&&
    template<typename T1, typename T2> A(T1 && s, T2 && t ): _s(std::forward<T1>(s)), _s(std::forward<T2>(t)) { }
    private:
    	std::string _s, _t;
};

```

####  类模板

##### 类模板的目的

- 设计通用的类型式，以适应广泛的成员数据型式

##### 类模板的定义格式

- `template<> class 类名称 { ... };`

- 原型：`template<typename T> class A;`

##### 类模板成员

- 像普通类的成员一样定义
- 定义在类中或类外均可，后者需要在类名后列些模板参数，以区分非模板类的成员函数
- `template<typename T> T A<T>::f(u)`

##### 类成员函数的模板

- 成员函数可以使用其他模板

```c++
template< typename T > class A
{
    public:
    	template<typename U> T f( const U & u);
};
// 类的模板型式要在韩式模板型式前面的
template<typename T> template<typename U> T A<T>::f( const U & u)
{
    
}
```

##### 类模板的体化

- 与函数模板不同，类模板体化时必须给定模板实际参数，如：`A<T> a;`
- 类模板体化时，编译器生成模板类或成员函数的代码；成员函数在调用时体化，虚函数在类构造时体化

##### 类模板的显示体化

- `template class A<int>;`
- 解决模板库的创建问题，库的使用者可能没有体化的机会，而未体化的模板定义不会出现在目标文件中
- 显式体化类模板后，显式体化其构造函数函数
- 其它成员函数可显式体化，也可不显示体化

##### 类模板的显示特化

- 使用特定的型或值显式特化类模板，以定制类模板代码，如：`template<> class A<char> {...};`
- 显式特化版本覆盖体化版本
- 显式特化并不要求与原始模板相同，特化版本可以具有不同的数据成员或成员函数
- 类模板可以部分特化，结果仍是类模板，以支持类模板的部分定制

##### 类模板的缺省模板参数

- 与函数模板相同，类模板可以具有缺省模板参数

```c++
// 队列
#include <iostream>
#include <cstdlib>
// 空队列异常类
class EQueueEmpty { };
// 队列项类前置声明
template< typename T > class JuQueueItem;
// 队列类
template< typename T> class JuQueue
{
    public:
    	JuQueue(): _head(NULL), _tail(NULL) { }
    	virtual ~JuQueue();
    	virtual void Enter( const T & item );
    	virtual T Leave();
    	bool IsEmpty() const { return _head == 0; }
    private:
    	JuQueueItem<T>* _head, *_tail;
};

// 队列项类，单项链表结构
template< typename T > class JuQueueItem
{
    friend class JuQueue<T>;
    public:
    	JuQueueItem( const T & item ): _item(item)._next(0) { }
    private:
    	T _item;
    	JuQueueItem<T>* _next;
};

// 队列类析构函数
template< typename T > JuQueue<T>::~JuQueue()
{
    while(!IsEmpty())
        Leave();
}
// 入队
template< typename T > void JuQueue<T>::Enter( const T & item)
{
    JuQueueItem<T> *p = new JuQueueItem<T>(item);
    if ( IsEmpty() )
        _head = _tail = p;
    else
        _tail->_next = p, _tail = p;
}
// 出列
template< typename T > T JuQueue<T>::Leave()
{
    if ( IsEmpty() )
        throw EQueueEmpty();
    JuQueueItem<T> *p = _head;
    T _retval = p->_item;
    _head = _head->_next;
    delete p;
    return _retval;
}


int main()
{
    JuQueue<int> * p = new JuQueue<int>;
    for ( int i = 0; i < 10; i++)
        p->Enter(i);
    std::cout << p->Leave() << std::endl;
    
    int *r = new int(10), * q = new int(20);
    JuQueue<int*> * t = new JuQueue<int*>;
    t->Enter(r);
    t->Enter(q);
    int *s = t->Leave();
    std::cout << *s << std::endl;
    
    return 0;
}
```

#### 元编程

##### 什么是元编程（metaprogramming）？

- 利用模块可以进行编译器计算（数值计算、型式计算和代码计算）的特点进行程序设计

##### 为什么可以进行元编程？

- C++是两层语言：执行编译器计算的代码称为静态代码，执行运行期计算的代码称为动态代码
- 模板可用于函数式编程（functional programming）：强调抽象计算，重视模块华，使用递归控制流程
- 模板是图灵完备的：理论上，模板可以执行任何计算任务

##### 为什么需要元编程

- 编译器计算可以是代码更通用，更易用，提升程序执行性能

##### 元编程缺点

- 相对结构化编程，编译效率极低
- 代码丑陋不堪，阅读难、调试难、维护难，易导致戴拿膨胀

##### 元编程可以做什么？

- 数值序列计算、素性判断、控制结构、循环展开、形式判定、表达式、编译器多态、特性、策略、标签、元容器、......
- 注：对操作系统编程而言，元编程意义不大

```c++
// Fibonacci数列
#include <iostream>
// 类模板，计算Fibonacci数列的第i项
template< int i = 1 > class Fibonacci
{
    public:
    	enum {value = Fibonacci<i-1>::value + Fibonacci<i-2>::value };
};
// 类模板特化，递归终止条件
template<> class Fibonacci<2> { public: enum { value = 1}; };
template<> class Fibonacci<1> { public: enum { value = 1}; };

int main()
{
    std::cout << "Fib(" << 1 << ") = " << Fibonacci<1>::value << std::endl;
    std::cout << "Fib(" << 2 << ") = " << Fibonacci<2>::value << std::endl;
    std::cout << "Fib(" << 3 << ") = " << Fibonacci<3>::value << std::endl;
    std::cout << "Fib(" << 4 << ") = " << Fibonacci<4>::value << std::endl;
    return 0;
}
```

```c++
// 素数枚举
#include <iostream>
#include <iomainip>
// 递归计算p是否为素数；若是，索性判定结论answer为1，否则为0；
template< int p, int i > struct PrimeMagicCube
{
    enum { answer = p % i && PrimeMagicCube<p, i - 1>::answer };
};
// 素数魔方类模板部分特化，递归终止条件，除数为1，没有找到因子
template< int i > struct PrimeMagicCube<P, 1> { enum { answer = 1}; };
// 数值类模板，输出不大于i的全部素数
template< int i > struct Number {
    Number<i-1> a;	// 递归定义数值对象
    enum { answer = PrimeMagicCube<i, i-1>::answer };
    void IsPrime()
    {
        // 先降序输出全部素数，然后升序输出全部数值素性序列
        if(answer)
            std::cout << std::setw(4) << std::right << i;
        a.IsPrime();	// 递归调用，计算下一个数值的素性
        std::cout << std::setw(2) << answer;
    }
};
// 数值类模板特化，终止于2
template<> struct Number<2>
{
    enum { answer = 1 };
    void IsPrime()
    {
        std::cout << std::setw(4) << std::right << 2 << std::endl;
        std::cout << std::setw(2) << answer;
    }
};

int main()
{
    Number<100> a;
    std::cout << std::endl;
}
```

#### 事件机制

##### 事件基本概念

- 操作系统或应用程序内部发生某件事，程序的某个组件需要响应该时间，并进行特定处理

##### 面向对象架构中，事件响应函数最可能为成员函数

- 问题：指向类成员函数的指针不能装换为哑型指针void\*，也不能随意转换为指向另一个类的成员函数的指针
- 解决方案：使用指向指向类成员函数的指针的指针

##### 实现策略：事件委托模型

- Event类模板：管理事件响应者对象，实现事件多播
- EventResponsor类模板：响应对象与响应者行为配对

```c++
#include <iostream>
#include <vector>
using namespace std;

// 空类，用于指代响应者对象
class Empty { };

// 事件响应者类模板，保存特定时间的响应者与响应行为
template< typename EventAction > class EventResponsor
{
    public:
    	EventResponsor(): actor(NULL), action(NULL) { }
    	EventResponsor( Empty * actor, EventAction * action): actor(actor), action(action) { }
    	friend bool operator==( const EventResponsor & lhs, const EventResponsor & rhs )
        {
            return lhs.actor == rhs.actor && *lhs.action == *rhs.action;
        }
    public:		// 公开的数据成员，以方便使用者
    	EventAction* action;	// 指向成员函数的指针的指针
    	Empty* actor;  	
};	// template<typename EventAction> class EventResponsor

// 事件类模板，用于管理特定事件的所有响应者
template< typename EventAction > class Event
{
    public:
    	typedef vector< EventResponsor< EventAction > > EventResponsors;
    	typedef typename vector< EventResponsor<EventAction> >::iterator EventIterator;
    
    public:
    	virtual ~Event()
        {
            for(EventIterator it = this->_ers.begin(); it != this->_ers.end(); ++it)
            {
                delete it->action, it->action = NULL;
            }
        }
    	EventResponsors & GetResponsors() { return this->_ers; }


	// 事件绑定，将实际响应者和响应行为挂接到响应者对象上
	template< typename Responsor, typename Action > void Bind( Responsor * actor, Action action)
	{
 	    Action * act = new Action( action );
    	EventResponsor<EventAction> er( (Empty*)actor, (EventAction*)act);
    	bool unbound = true;
    	for( EventIterator it = this->_ers.begin(); it != this->_ers.end(); it++)
    	{
        	if(*it == er)	// 发现重复的事件响应者，说明已绑定
        	{
            	unbound = false;
            	break;
        	}
    	}
    	if( unbound )
        	this->_ers.push_back( er );
    	else
        	delete er.action, er.action = NULL;
	}

	// 接触事件绑定，删除事件响应者对象
	template< typename Responsor, typename Action > void UnBind( Responsor* actor, Action action )
	{
	    Action * act = new Action( action );
	    EventResponsor<EventAction> er( (Empty*)actor, (EventAction*)act );
    	for( EventIterator it = this->_ers.begin(); it != this->_ers.end(); ++it)
    	{
        	if(*it == er)	// 找到待删除的事件响应者对象
        	{
            	delete it->action, this->_ers.erase(it);
            	break;
        	}
    	}
    	delete er.action, er.action = NULL;
	}
	private :
    	EventResponsors _ers;
}; // template<typename EventAction> class Event

// 定义事件委托模型，指向类成员函数的指针
typedef Empty EventDelegator;
typedef void ( EventDelegator::*ValueChanged )(int value, void * tag );

// 触发者
class Trigger
{
    public:
    	Trigger(): _value(0) { }
    	void SetValue( int value, void * tag );
    	int GetValue() { reutnr _value; }
    public:
    	// 值变化事件，公开属性，方便在类外设定
    	Event<ValueChanged> value_changed;
    private:
    	int _value;
};

// 设定值，遍历特定事件的响应者对象列表，逐一触发值变更事件
void Trigger::SetValue(int value, void * tag)
{
    if(_value == value)
        return;
    _value = value;
    Event<ValueChanged>::EventResponsors ers;
    ers = this->value_changed.GetResponsors();
    if(!ers.empty() )
    {
        Event<ValueChanged>::EventIterator it;
        for(it = ers.begin(); it != ers.end(); ++it){
            // 其实调用的是actor对象的成员函数的指针，然后加个括号就是普通函数了
            ((it->actor)->*(*(it->action)))(value, tag ); // 响应事件
        }
    }
}

// 行动者
class Actor
{
    public:
   		// 侦听事件，绑定本对象的事件响应函数到侦听的事件
    	void Listen( Trigger * trigger)
        {
            // Bind()第二个参数是第响应值变更事件的那个事件响应函数的入口地址。
        	trigger->value_changed.Bind( this, & Actor::OnValueChanged);    
        }
    
    	// 停止侦听，从侦听的事件中取消绑定本对象的事件响应活动
    	void Unlisten( Trigger * trigger ) 
        { trigger->value_changed.Unbind( this, &Actor::OnValueChanged); }
    	
    	// 值变更事件的响应函数
    	void OnValueChanged( int value, void * tag )
        { cout << reinterpret_cast<char*>(tag) << value << "." << endl; }
}

int main()
{
    const char * s = "Now  the value is";
    Trigger t;
    Actor a1, a2;
    
    a1.listen(&t);
    a2.listen(&t);
    
    cout << "Listening..." << endl;
    t.SetValue( 10, reinterpret_cast<void*>( const_cast<char*>(s) ) );
    
    a2.Unlisten(&t);
    cout << "Listening again..." << endl;
    t.SetValue( 20, reinterpret_cast<void*>( const_cast<char*>(s) ) );
    
    return 0;
}
```



### 编程实践

###  第一题

使用类模板实现自己的抽象链表类

### 第二题

按照Black-Scholes期权定价模型，衍生品。。。

## 标准库特殊设施

### 1. tuple类型

tuple是可以存储任意个数据类型，pair只能存一对，而tuple可以理解为pair的拓展，可以存储多个

### 2. bitset类型

bitset类型是用于存储二进制数据集的

### 3. 正则表达式

正则表达式库组件：

- regex：表示有一个正则表达式类
- regex_match：将一个字符序列与一个正则表达式匹配
- regex_search：寻找第一个与正则表达式匹配的子序列
- sregex_iterator：迭代器适配器，调用regex_search来遍历一个string中所有匹配的子串
- smatch：容器类，保存在string中搜索的结果
- ssub_match：string中匹配的子表达式的结果

C++中正则表达式是在运行时解析的，不是在编译时解析的。

	### 4.随机数

### 5.IO库

## 用于大型程序的工具

### 1.异常处理

如果在继承关系上，基类虚函数声明为noexcept，那么子类继承该虚函数无法进行声明为noexcept，但是如果基类虚函数没有声明为noexcept，可以抛出异常，那么子类继承的虚函数可以自定义为允许抛出异常和noexcept。

### 2.命名空间

1. 命名空间中，例如友元函数没有声明，但是如果有函数参数，那么在函数参数中，函数参数所属的命名空间也是我们调用友元函数的的候选空间里，会在这些命名空间中查找该函数

#### using声明和using重载

- using声明：是使用命名空间中的某个成员名字，可以使用不同命的命名空间
- using指示：是将使用的命名空间的所有名字都注入，不同命名的空间，可以使用同名的成员名字，只需要将同名带上所属的命名空间

### 3. 多重继承与虚继承

- 在多重继承中，如果多个基类中，有相同的构造函数，那么就需要子类自己定义与之对应的自己的构造函数
- 在多重继承中，拷贝构造，赋值构造和移动构造中，如果派生类定义了自己的这些构造函数，那么就不会调用基类这些操作，但是如果是派生类使用了合成的这些构造，那么就会调用基类构造按继承顺序，从最顶层的基类开始开始

#### 虚继承

虚继承在一个派生类继承了某个基类多次的时候，可以将某个基类的对象进行共享，这样不会生成多个子对象

```c++
// 添加方式
class Raccoon : public virtual ZooAnimal
{
    
}

class Bear : public virtual ZooAnimal
{
    
}

// 虚继承在panda基类中预先写好，在选择继承的时候会用到，这样只有一个ZooAnimal基类部分
class Panda : public Bear, public Raccoon, public Endangered
{
    
};
```

虚基类的某个成员如果被两条派生路径覆盖，那么在继承了这两条派生路径的派生类在使用的时候会产生二义性，这个时候就需要对继承的某个成员进行重新定义。如果只是一条派生路径那么是没问题的。

#### 构造函数与虚继承

在虚派生中，虚基类是由最底层的派生类初始化的。因为如果存在继承多个虚基类时候，不是最底层的派生类初始化，那么就会虚基类初始化多次问题，以及初始化的顺序问题。最底层的派生类初始化构造的时候，先是虚基类构造初始化，再从基类从上到下开始构造。

**虚基类总是先于非虚基类构造，与他们在继承体系中的次序和位置无关。**

如果存在多个虚基类，那么虚基类之间的顺序是按在派生列表中出现的顺序从左向右依次构造。

合成的拷贝构造，移动构造，赋值构造顺序和前面一样，析构顺序则是与构造顺序完全相反。

## 特殊工具与技术

### 1. 控制内存分配

- 调用析构函数会销毁对象，但是不会释放内存

### 2. 运行时类型识别

在运行时类型识别使用dynamic_cast和typeid。

- dynamic_cast：用于将基类的指针或引用安全地转换为派生类的指针或引用
- typeid：用于返回表达式的类型

### 3. 枚举类型

```c++
// 限定作用域的枚举类型声明时候，使用默认成员类型int
enum class intValue;
// 不限定作用域的声明，必须指定成员类型
enum longValues : unsigned long long;
```



### 4. 类成员指针

成员指针使用的方式是`类::* 定义指针名字`，使用是前面的写法，而且

### 5. 嵌套类

嵌套类的成员访问外部类的成员以及外部类成员访问嵌套类都是通过限定符进行限定的

### 6. union:一种节省空间的类

union中的成员，只能有一个可以被定义，其它成员会变为未定义。

**匿名union不能包含受保护的成员或私有成员，也不能定义成员函数，但是不是匿名的可以**

### 7. 局部类

**局部类的所有成员（包括函数在内）都必须完整定义在类的内部。因此，局部类的作用域嵌套类相比相差很远**。

局部类也不允许声明静态成员

局部类只能访问外层作用域定义的类型名、静态变量以及枚举成员。如果定义在某个函数内部，则该函数的普通局部变量不能被该局部类使用。

外层函数对局部类的私有成员没有任何访问特权，但是局部类可以将外层函数声明为友元。而且局部类不能含有静态数据成员。

### 8. 固有的不可移植的特性

#### 1. 位域

位域在使用的方式

```c++
Bit model: 2;	// model为占2位的变量
```



#### 2.volatile限定符

告诉编译器不对限定的成员进行优化，这样在平台切换的时候，可以拥有更好的兼用性

合成的拷贝对bolatile对象无效

#### 3.链接提示：extern "C"

想要把C++代码和其他语言编写的代码放在一起使用，需要有权访问该语言的编译器，并且这个这个编译器与当前的C++编译器是兼容的。

使用 `extern "C"`有单个和复合的，例子如下：

```c++
extern "C" size_t strlen(const char *);
extern "C" 	// extern 后面接的字符串字面值常量代表的是后面编写的函数所使用的语言，花括号内的函数在外层是可见的
{
    int strcmp(const char*, const char*);
    char *strcat(char*, const char *);
}
```

C语言不支持函数重载，所以在使用`extern "C"`的时候，函数名字相同但是参数列表不同的是无法正常使用的
