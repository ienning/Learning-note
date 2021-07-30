# `QApplication`源码解析

QT在开启程序时候，都会调用`Qpplication`对象的exec函数。

继承关系

`QCoreApplication->QGuiApplication->QApplication`

下面是有一个Qt应用程序创建的过程，

```c++
#include <QWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    SelfDefineWidget w;
    w.show();
    a.exec();
}
```

## `QWidget`

在调用`w.show()`函数时，`QWidget`调用到的是`QWidgetPrivate`的`setVisible(bool)`函数，

## `QApplication`

在`QCoreApplication`中，会调用`QEventLoop`的exec函数进入事件循环，循环调用`QEventLoop::processEvents()`函数

```c++
bool QEventLoop::processEvents(ProcessEventsFlags flags)
{
    Q_D(QEventLoop);
    if (!d->threadData->hasEventDispatcher())
        return false;
    // 调用的是QEventDispatcher对象的processEvents方法，就是事件分发机制
    return d->threadData->eventDispatcher.load()->processEvents(flags);
}
```



