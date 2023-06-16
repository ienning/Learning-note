# 深度探索C++对象模型学习

## 第一章关于对象

1. C++虚函数使用虚函数表，

2. C++对象中直接存储的非static的member data，对于函数分为非static函数，static函数以及virtual函数，分别放在一个table中，每个函数占据一个slot，table的地址，通过对象内部存储指针指向这些地址。同时虚函数存储的第一个slot，存储的是指向实际类。

3. C++继承的类，在子类对象中，最开始版本是直接存储指向基类的指针，后面是使用一个base point table point，间接访问base class point，好处是base class的改变不会影响到子类的object的大小，牺牲的是时间和空间。

4. 在C++中为了兼容C的东西，所以很多使用class的地方要支持struct，比如声明时候使用的class，定义使用struct是可以的，模板使用使用\<class Type\>struct 不行。

5. 类型为void*的指针和NoPublic的派生行为，可以是多态的，但是没有被语言明确支持，需要通过程序员显式的转换操作才能管理。

6. 在使用VS的编译器的时候，如果父类没有虚函数被声明定义，子类继承后无法进行多态使用。

   ```c++
   class Base
   {
       void functionA()
       {}
   };
   class Derived: public Base
   {
       void functionA()
       {}
   };
   
   int main()
   {
       Base* base = new Derived();
       base->functionA();
       Derived* derived = dynamic_cast<Derived*>(base); // 使用VS编译器报错，没有动态绑定，但是只要Base内有定义了virtual的函数，就可以了。原理暂时不晓得。dynamic_cast这个有关系：dynamic_cast要求基类至少含有一个函数virtual函数
       // 下面这个就可以
       Derived* derived = (Derived*) base;
       base->functionA();	
   }
   
   
   ```

7. 如果一个base class object被直接初始化为（或是被指定为）一个derived class object，derived object就会被切割，以塞入较小的base type内存中，derived type将没有留下任何蛛丝马迹。
