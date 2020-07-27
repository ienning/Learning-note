

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



## 字符串



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
- 部分成员（常量与引用）只能初始化，不嗯给你赋值
- 部分成员（类的对象）如果复制，将导致两次构造
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

## 操作符重载

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

- 左值：用于标识非临时对象或非成员函数的表达式
- 右值：用于标识临时对象的表达式或与任何对象无关的值（纯右值），或者用于标识即将失效的对象的表达式（失效值）

##### 左值引用与右值引用

左值引用：`&`

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



### 编程实践

#### 第一题

使用面向对象技术完成习题7.1，并未有理数类重载必要的操作符

#### 第二题

new与delete操作符可以被重载。研究存储管理技术，重载这两个操作符一实现程序独有的动态存储管理策略。

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

#### const_cast



### 模板与型式参数化

### 泛型编程实践

### 编程实践



## 程序环境

### 程序执行环境

### 输入输出

### 文件系统

### 设备

### 库

### makefile文件

### 编程实践



## 进程

### 进程基本概念

### 信号

### 进程管理

### 进程间通信

### 进程池

### 编程实践



## 线程

### 线程基本概念

### 线程管理

### 线程同步机制

### C++11线程库

### 编程实践



## 网络

### Internet网络协议

### 套接字

### 编程实践

