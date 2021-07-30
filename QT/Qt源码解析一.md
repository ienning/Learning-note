# Qt源码解析一

## QWidgetBackingStore

该类的责任是，更新window surface 某一区域

## QWidgetBackingStoreTracker

是对一组QWidget指针进行存储的，这些QWidget是使用到了QWidgetBacStore了。

## QWidgetPrivate

内部存放是存放指向QWidget的指针，是QWidgetData的派生，存放着数据

`Q_Q(QWidget)`获取当前当前widget的指针

## QWidget

内部存放了指向 new QWidgetPrivate所指向的堆内存的智能指针

`Q_D(QWidget)`获取QWidgetPrivate的数据指针，能确保在调用可以根据需要调用任意一层的私有数据，因为QWidget类型可以自己定义

