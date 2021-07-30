[TOC]

# Qt基础知识

## 1.元对象

### Q_OBJECT

Q_OBJECT宏是用于启动元对象特性的，启动后可以使用动态特性、信号和槽等功能。

## 2.属性系统

#### QVariant类

QVariant是封装了一个属性类型类的类，一次只能保存一个单一类型的值，对于其不支持类型（如用户自定义的类型），则需要使用Q_DECLARE_METATYPE(Type)宏进行注册。

### 信号与槽

信号与槽是Qt的核心，为此Qt引进了一些关键字：signal，slot，emit。这些不是C++关键字是Qt特有的，这些关键字会被Qt的moc转化为标准的C++语句。信号与槽使用的是观察者模式

moc工具不拓展#define，因此，在signals和slots中携带参数的宏函数不能正确工作，以及

#### 信号使用

- 信号使用signals关键字声明，在其后面有一个冒号“:”，在其前面不能有public、private、protected访问控制符，信号默认是public的。
- 信号只需像函数那样声明即可，其中可以有参数，参数的主要作用是用于和槽的通信，就想普通函数的参数传递规则一样。信号虽然像函数，但是对它的调用方式不一样，信号需要使用emit关键字发射。
- 信号只需声明，不能对其进行定义，信号是由moc自动生成的。
- 信号的返回值只能是void类型的。
- 因为信号位于类中，因此发射信号的位置需要位于该类的成员函数中或该类能见到信号的标识符的位置。

#### 槽函数

- 声明槽需要使用slots关键字，在其后面有一个冒号“:”，且槽需使用public、private、protected访问控制符之一。
- 槽就是一个普通的函数，可以像使用普通一样使用，槽与普通函数的主要区别是，草可以与信号关联。

#### 信号与槽的关系

- 槽的参数和类型需要与信号参数的类型相对应
- 槽的参数不能比信号的参数多，因为多余的参数无法接收到信号传递来的值，那么在槽函数中使用这些参数会发生错误
- 若信号的参数比槽的参数，则多于的参数将被忽略
- 一个信号可以与多个槽函数连接，一个槽函数可以与多个信号连接，一个信号也可以与另一个信号关联。
- 若一个信号关联到多个槽时，则发射信号时，槽函数执行顺序是随机执行。
- 若信号连接到另一个信号，则当第一个信号发射时，会立即发射第二个信号。

#### 信号与槽的关联

信号与槽的关联总共有5种型式

#### 断开信号和槽的关联

使用disconnect函数断开连接，重载的种类共有6种形式

### 对象树与生命期

#### 组合模式与对象树

- 组合模式的基本思想：使用父类类型的指针指向子类对象，并把这个指针存储在一个数组中（使用容器更方便），然后每创建一个类对象就向这个容器中添加一个指向该对象的指针

#### QObject类、对象树、生命期

- 对象创建规则：
  1. 子对象通常应创建在堆中（使用new创建），此时就不在需要使用delete将其删除了，当父对象被删除时，子对象会被自动删除。
  2. 对于Qt程序，自子对象应该创建在堆上，不应该创建在栈上
  3. 如果子对象创建在栈上，那么会出现两次删除记录，一次是父对象删除子对象，然后还有一次是在子对象自己删除。那么在第一次被删除后，第二次删除就会出现问题。C++规定，子对象会被先删除，由Qt对象树克制，子对象会被从父对象的列表中移除，当父对象生命期结束时就不会删除子对象了。
- 对象删除规则：
  1. 父对象会自动删除子对象。父对象拥有对象的所有权，父对象被删除时会在析构函数自动删除其子对象
  2. 手动删除子对象时，会把该子对象从父对象列表中移除，避免父对象删除时，再一次删除子对象。防止Object对象出现被两次删除的记录
  3. 当一个对象被删除时，会发出destroyed()信号，可以捕捉信号以避免对QObject对象的悬垂引用。

### 事件

#### QApplication、QGuiApplication、QCoreApplication

1. 继承关系，左侧为父类，从左到右按顺序继承下去：

   QObject<-QCoreApplication<-QGuiApplication<-QApplication

2. 一个程序只能有一个QCoreApplication及其子的对象。
3. QCoreApplication：主要提供无GUI程序的事件循环。
4. QGUIApplication：用于管理GUI程序的控制流和主要设置。
5. QApplication：该类专门为QGuiApplication提供基于QWidget的程序所需的一些功能，主要用于处理部件的初始化、最终化。

#### 事件传递（分发）及处理

事件传递步骤是从下到上。子对象没有被处理，就交给上一级对象处理，循环往复。

事件在传递中，使用的event()函数，event()根据事件类型传递给不同的事件处理函数，

事件传递中，Qt使用5种方式来处理事件：

1. 重新实现各部件内部默认的事件处理函数，比如重新实现paintEvent()、mousePressEvent()等事件处理函数，这是最常用、最简单的方式
2. 重新实现QObject::event()函数（需要基础QObject），使用该方式，可以再时间到达默认的事件处理函数之前捕获到该事件。改方式常被用来处理Tab键的默认意义。在重新实现event()函数时，必须对未明确处理的时间调用基类的event()函数，比如，若子类化QWidget，并重写了event函数，但未调用父类event()函数，则程序可能不会正常显示界面
3. 在QObject对象上注册事件过滤器，对象一但使用installEventFilter()注册，传递给目标对象的所有事件都会先传递给这个监视对象的eventFilter()函数。同一个对象注册了对个事件过滤器，则按照注册的逆序一次激活这些事件过滤器。
4. 在QApplication注册事件过滤器。该方式与重新实现notify()函数一样强大。程序中的每个对象的事件在发送到其他事件过滤器之前都会发送到QApplication这个eventFilter()函数中。
5. 子类化QApplication，并重新实现QCoreApplication::notify()函数，由事件传递机制可知，notify()提供了对事件的完全控制，功能很强大，但是重写函数就比较复杂，比较少被用到，这是唯一能在事件过滤器之前捕获到事件的方式

#### 事件的接受和忽略

- 事件可以被接受或被忽略，被接受的事件不会传递到其他对象，被忽略的事件会被传递到其他对象上或者被抛弃。
- 使用QEvent::accept()函数表示接受一个事件，QEvent::ignore()函数表示忽略一个事件
- Qt默认值是accept（接受事件），但是在QWidget的默认时间处理函数（比如KeyPressEvent()）中，默认值是ignore()，因为这样可以更好实现事件的传递。
- 注意：在QCloseEvent(关闭事件)有一些不同，QCloseEvent::ignore()表示取消操作关闭，而QCloseEvent::accept()则表示让Qt继续关闭操作。

#### 事件过滤器

Qt实现事件过滤器的步骤如下：

1. Qt调用：`void QObject::installEventFilter(QObject* filterObj)`把filterObj对象注册为事件过滤器，filterObj也称为过滤器对象。事件过了长期通常在构造函数中进行注册。
2. 在上一步注册的filterObj对象，通过调用`bool QObject::eventFilter(QObject* obj, QEvent* e)`来接收拦截到的事件。也就说拦截到的事件在filterObj对象中的eventFilter函数中处理。eventFilter的第一个参数obj指向的是事件本应传递到的目标对象。
3. 使用QObject：：removeEventFilter(QObject *obj)函数可以删除事件过滤器

使用事件过滤器的原因：应对不同控件对某个操作同时采取相同的响应操作时，事件过滤器可以将对不同的控件分别进行各自的响应操作。

#### 自定义事件与事件的发送

##### 发送事件由以下两个函数完成

- `static void QCoreApplication::postEvent(QObject* receiver, QEvent* event, int priority=Qt::NormalEventPriority);`
- `static bool QCoreApplication::sendEvent(QObject* receiver, QEvent* event)`
- receiver：指向接收事件的对象
- event：表示需要发送的事件
- priority：表示事件的优先级，事件会按优先级排序，高优先级在前面。其取值为枚举类型Qt::EventPriority中的枚举值

##### 发送事件（sendEvent）和发布时间（postEvent）

1. 发布（post）事件：
   - 把事件添加到事件队列中，并立即返回。
   - 发布事件必须在堆（比如使用 new）上创建事件，因为事件被发布后，事件队列将获得事件的所有权并自动将其删除。发布事件后再访问该时间是不安全的。
   - 发布事件还可以对事件进行合并（或称为压缩），比如在返回事件循环之前连续发布了多个相同的事件，则这多个相同的事件会自动合并为一个单一的事件。可合并的事件有鼠标移动事件、调整大小事件等。
2. 发送（send）事件：把事件直接发送给接收事件的目标对象。事件发送之后不会被删除，发送的事件通常创建在堆栈上。

## 3.Qt窗口及QWidget类

### QtWidgets简介

QWidget是所有用户界面类的基类，它的父类是QObject和QPaintDevie：

- QObject：是所有Qt对象的基类
- QPaintDevie：是所有可绘制对象的基类

### Qt中窗口的基本概念

1. 在AndroidUI的类称为空间，而在Qt中这些被称为窗口部件，简称部件，比如：主窗口、对话框、按钮、标签等。
2. 窗口是窗口，窗口部件是窗口部件，二者是不同概念，前者是没有父部件的部件，后者可以有。
3. 容器：容器是可以容纳其它部件的部件，也可以被其它容器容纳，所以也不是窗口。

## 4.Qt常用部件

### 按钮部件

关系继承图

- QWidget
  - QDialogButtonBox
  - QAbstractButton
    - QCheckBox
    - QRadioButton
    - QToolButton
    - QPushButton
      - QCommandLinkButton

按钮在按下的时候，会先执行按下状态，然后执行选中状态，若鼠标再次点击按钮时候，首先设置按下状态，然后再清除按钮的选择状态。在每次鼠标释放时会清除按钮的按下状态。

#### QPushButton类（标准按钮）

1. 默认按钮：是指当用户按下enter时，默认按钮会被自动按下
2. 自动默认按钮：是指在满足一些条件时会自动成为默认按钮的按钮，比如当自动默认按钮获得焦点时，会自动成为默认按钮，普通按钮即使获得焦点也不会成为默认按钮。
3. 默认按钮和自动默认按钮，在其周围通常会绘制一个额外的边框，最多可达3个像素或更多，Qt会保存这个空间在默认按钮的周围，因此，自动默认按钮和默认按钮可能会有更大的默认尺寸。在Qt中，自动默认按钮不会显示这个边框 ，但默认按钮会显示，因此从外观上看，有这个边框的按钮就是默认按钮。

##### 默认按钮规则

- 一次只能有一个按钮是默认按钮，若同时设置多个默认按钮，则最后设置的按钮是默认按钮
- 按下空格键始终单击的是具有焦点的按钮（这是按下空格键与enter键的不同）

- 默认按钮和自动默认按钮的行为：默认按钮的行为仅在对话框中有作用，也就是说若不是在对话框中，则不一定按以下规则执行。
  - 按下Enter（回车）键时，若自动默认按钮当前具有焦点，则按下自动默认按钮
  - 按下Enter（回车）键时，若对话框中有自动默认按钮但没有默认按钮，则按下当前具有焦点的自动默认按钮，若此时没有按钮具有焦点，则按下焦点链中的下一个自动默认按钮。

### 容器部件

- QDialogButtonBox（按钮框）
- QButtonGrup（按钮组）
- QGroupBox（组框）

#### QDialogButtonBox（按钮框）

1. QDialogButtonBox是直接继承自QWidget类的。把多个按钮组织在一起，比如关闭某个窗口时，可能会弹出，一个对话框，有YES和NO的按钮进行选择，这就是QDialogButtonBox。

#### QButtonGroup

#### QGroupBox

- `void clicked(bool checked = false);`发送实际同其它clicked信号，但要注意：若调用setChecked()发不会发送该信号。

### 带边框的部件

#### QFrame类

#### QLbale类（标签）

#### QLCDNumber类（LCD数字）

### 输入部件

#### QComboBox类（下拉列表、组合框）

#### QLineEdit

#### QValidator（行编辑器QLineEdit使用）

### 旋转框（微调按钮）

#### QAbstractSponBox（旋转框或微调框）

- QWidget类的直接子类，不是抽象类，也未提供实际功能，仅为旋转框提供了一些外观的形式以及需要子类实现的成员
- 旋转框是由微调按钮（调整数值）和行编辑器（显示数值）组成的

#### QSpinBox类中的属性

- QSpinBox类时QAbstractSponBox类的直接子类和具体实现
- QSpinBox类被设计用于处理整数和离散值集合，对于浮点值使用QDoubleSpinBox类实现。
- QSpinBox类默认支持整数值，但是可以通过其内部成员函数进行拓展，以支持使用不用的字符串。

### 时间系统

时间系统类：QDate、QTime、QDateTime，QTimer、QDateTimeEdit、QDateEdit、QTimeEdit等

- QDate、QTime、QDateTime：这三个类是QtCore模块中独立的类，分别用于描述日期（年月日），时间（小时，分，秒）以及日期时间。但是不负责直接显示日期和时间的显示
- QTimer（计时器）：该类是QObject类的直接子类
- QDateTimeEdit、QDateEdit、QTimeEdit：这三个类都是直接继承QAbstractSpinBox类。主要用于显示（在界面上显示）、调整和编辑日期和时间
- QCalendarWidget：该类直接继承自QWidget类，用于描述日历

#### QDate

- 可以获得年月日，周，以及所在的年份的第几周，第几天，当前月份的第几天

## 5. 多线程

### QWaitCondition

#### QWaitCondition::wait()和QWaitCondition::wakeAll()

- 在某一线程（该线程已经调用了QMutex::lock()）中调用QWaitCondition::wait(QMutex\*)其它线程如果想获得信号量的锁，需要调用QMutex::lock()函数（和前面的线程是同一个QMutex类型变量），会触发系统底层的wait_block让QWaitCondition::wait(QMutex\*)瞬间释放所信号量，让后面的子线程可以进行操作，进而使用QWaitCondition::wakeAll()，示例代码如下

```C++
// 线程一
mutex->lock();
Send(&message);
condition.wait(mutex); // 线程进入睡眠
if (m_receivedMessage)
    HandleMessage(m_receivedMessage);
mutex->unlock();
// 线程二
m_receivedMessage = parseMessage(buffer);
mutex->lock();	// 调用此信号量的加锁函数，系统出现阻塞，会让线程一中的condition.wait(mutex)瞬间解锁mutex，使得线程二中的mutex获得加锁（其中释放瞬间是原子操作）
condition.wakeAll(); // 唤醒线程一
mutex->unlock();
```



## 6. 网络



