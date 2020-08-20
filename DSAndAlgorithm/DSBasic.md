# 数据结构

## 向量

- 向量是数组的抽象与泛化，有一组元素按线性次序封装而成

- 各元素与[0, n)内的秩（rank）一一对应

- 元素的类型不限于基本类型
- 操作、管理维护更加简化、统一与安全
- 可更为便捷地参与复杂数据结构的定制与实现

### 接口与实现

```c++
typedef int Rank; 	//秩
#define DEFAULT_CAPACITY 3		// 默认初始容量（实际应用中可设置为更大）
template <typename T> class Vector { 	// 向量模板类
    private: Rank _size; int _capacity; T* _elem;		// 规模、容量、数据区
    protected:
    	// 内部函数
    	void copyFrom(const T* A, Rank lo, Rank hi);
    	void expand();
    public:
    	// 构造函数
    	// 默认
    	Vector( int c = DEFAULT_CAPACITY )
        {
            _elem = new T[_capacity = c];
            _size = 0;
        }
    	// 数组区间复制
    	Vector( T const * A, Rank lo, Rank hi )	
        {
            copyFrom(A, lo, hi);
        }
    	// 向量区间复制
    	Vector( Vector<T> const & V, Rank lo, Rank hi )
        {
            copyFrom(V._elem, lo, hi );
        }
    	// 向量整体赋值
    	Vector( Vector<T> const& V)
        {
            copyFrom( V, _elem, 0, V._size );
        }
    	// 析构函数
    	// 只读可口
    	// 可写接口
    	// 遍历接口
    	
};
template <typename T> void Vector<T>::copyFrom(const T* A, Rank lo, Rank hi)
{
    _elem = new T[_capacity = 2*(hi - lo)];		// 分配空间
    _size = 0;	// 规模清零
    while (lo < hi)
        _elem[_size++] = A[lo++];				// 复制至_elem[0. hi-lo)
}
template <typename T> void Vector<T>::expand()
{
    // 向量不足时扩容
    if( _size < _capacity ) return;		// 尚未满员时，不必扩容
    _capacity = max(_capacity, DEFAULT_CAPACITY);	// 不低于最小容量
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1];		// 容量加倍
    for( int i = 0; i < _size; i++ )	// 复制原向量内容
        _elem[i] = oldElem[i];			// T为基本类型，或已重载赋值操作符“=”
    delete [] oldElem;					// 释放原空间
}
// 构造函数

// 析构函数

// 只读可口

// 可写接口

// 遍历接口

```

### 可扩充向量

#### 平均分析VS分摊分析

##### 平均复杂度或期望复杂度（average/expected complexity）

根据数据结构各种操作做出概率的分布，将对应的成本加权平均

- 各种可能的操作，作为独立事件分别考察
- 割裂了操作之间的相关性和连贯性
- 往往不能准确地评判数据结构和算法的真实性能

##### 分摊复杂度（amortized complexity）

对数据结构连续地实施足够多次操作，所需总体成本分摊至单次操作

- 从实际可行角度，对一系类操作做整体的考量
- 更加忠实地刻画了可能出现的操作序列
- 可以更为精准地评判数据结构和算法的真实性能

### 无序向量

#### 寻秩访问

```c++
tempalte <typename T> T & Vector<T>::operator[]( Rank r ) const { return _elem[r]; }
```

#### 插入

```c++
template <typename T> Rank Vector::insert(Rank r, T const & e)// e作为秩为r元素插入，0 <= r <= size
{
    expand();		// 若有必要，扩容
    for (int i = _size; i > r; j-- )		// 自后向前
        _elem[i] = _elem[i-1];
    _elem[r] = e;
    _size++;
    return r; 								// 返回秩
}
```

#### 缩容

```c++
template <typename T> void Vector<T>::shrink()
{
    // 填装因子过小时压缩向量所占空间
    if( _capacity < DEFAULT_CAPACITY << 1 )
        return;		// 不致收缩到DEFAULT_CAPACITY以下
    if( _size << 2 > _capacity )
        return; 	// 以25%为界
    T* oldElem = _elem;
    _elem = new T[_capacity >>= 1];		//容量减半
    for ( int i = 0; I < _size; i++ )
        _elem[i] = oldElem[i];			// 复制原向量内容
    delete [] oldElem;					// 释放原空间
}
```

 #### 删除

```c++
template <typename T> int Vector<T>::remove ( Rank lo, Rank hi )
{
    if (lo == hi ) return 0;
    while ( hi < _size )
        _elem[lo++] = _elem[hi++];
    _size = lo;
    shrink();
    return hi - lo;
}
template <typename T> T Vector<T>::remove ( Rank r )
{
    T elem = _elem[r];
    remove(r, r+1);
    return elem;
}
```

#### 唯一化

```c++
template <typename T> int Vector<T>::deduplicate()
{
    int oldSize = _size;
    Rank i = 1;
    while( i < _size )
        (find( _elem[i], 0, i) < 0) ? ++i : remove(i);
    return oldSize - _size;
}
```

#### 遍历

```c++
template<typename T> void Vector<T>::traverse ( void (*visit) (T&))
{
    for( int i = 0; i < _size; i++)
        visit(_elem[i]);
}
// 借助函数对象机制
template<typename T> template<typename VST> void Vector<T>::traverse( VST& visit)
{
    for( int i = 0; i < _size; i++ )
        visit(_elem[i]);
}
```



### 有序向量

#### 唯一化

```c++
// 低效版
template <typename T> int Vector<T>::uniquify()
{
    int oldSize = _size;
    int i = 1;
    while ( i < _size )
        _elem[i -  1] == _elem[i] ? remove[i] : i++;
    return oldSize - _size;
}
// 高效版
template <typename T> int Vector<T>::uniquify()
{
    int j = 0, i = 0;
    while(++j < _size )
        if(_elem[i] != _elem[j])
            _elem[++i] = _elem[j];
    _size = i+1;
    shrink();
    return j - i;
}

```



#### 二分查找

```c++
// 二分查找法（版本A）：在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size
template<typename T> static Rank BindSearch( T* A, T const& e, Rank lo, Rank hi )
{
    while( lo < hi )
    {
        Rank mi = ( lo + hi ) >> i;
        if( e < a[mi] )
            hi = mi;
        else if( A[m] < e )
            lo  = mi + 1;
        else return mi;
    }
    return -1;
}

// 二分查找算法（版本B）
template<typename T> static Rank bindSearch( T* A, const& e, Rank lo, Rank hi )
{
    while( 1 < hi - lo )
    {
        Rank mi = ( lo + hi ) >> 1;
        ( e < A[mi] ) ? hi = mi : lo = mi;
    }
    return ( e == A[lo] ) ? lo : -1;
}

// 二分查找算法（版本C）
template<typename T> static Rank bindSearch( T* A, const& e, Rank lo, Rank hi )
{
    while (lo < hi)
    {
        Rank mi = ( lo + hi ) >> 1;
        ( e < A[mi] ) ? hi = mi : lo = mi + 1;
    }
    return --lo;
}
```



#### Fibonacci查找

```c++
#include "../fibonacci/Fib.h"
template <typename T> static Rank fibSearch( T* A, T const & e, Rank lo, Rank hi )
{
    Fib fib(hi - lo);
    while( lo < hi )
    {
        while( hi - lo < fib.get() )
            fib.prev();
        Rank mi = lo + fib.get() - 1;
        if( e < A[mi] )
            hi = mi;
        else if( A[mi] < e )
            lo = mi + 1;
        else return mi;
    }
    return -1;
}
```

#### 插值查找



### 气泡排序

```C++
// 排序器
template<typename T> void Vector<T>::sort( Rank lo, Rank hi )
{
    switch( rank() % 5 )
    {
        case 1:
            bubbleSort( lo , hi );		// 起泡排序
            break;
        case 2:
            selectionSort( lo, hi );	// 选择排序
            break;
        case 3:
            mergeSort( lo, hi );		// 归并排序
            break;
        case 4:
            heapSort( lo, hi );			// 堆排序
            break;
        case 5:
            heapSort( lo, hi );			// 快速排序
            break;
        case 6:
            insertionSort( lo, hi );		// 插入排序
            break;
            
    }
}

// 起泡排序
template<typename T> void Vector<T>::bubbleSort( Rank lo, Rank hi )
{
    while( !bubble(lo, hi--); )
}

template<typename T> void Vector<T>::bubble( Rank lo, Rank hi )
{
    bool result = true;
    while( ++lo < hi )
    {
        if( _elem[lo - 1] > _elem[lo] )
        {
            swap( _elem[lo - 1], _elem[lo] );
            result = false;
        }
    }
    return result;
}

// 选择排序
template<typename T> void Vector<T>::selectionSort( Rank lo, Rank hi )
{
    int index;
    int max;
    for( int j = hi - 1; j >= lo; j++)
    {
        index = j;
        max = _elem[j];
        for( int i = lo; i <= j; i++)
        {
            if( _elem[i] > max )
            {
                index = i;
                max = _elem[i];
            }
        }
        if( index != j )
        {
        	swap( _elem[index], _elem[j] );
    
        }
    }
    for( int i = lo+1; i < hi; i++)
    {
        if( _elem[i] >= max )
        {
            max = _elem[i];
            index = i;
        }
    }
}

// 归并排序
template<typename T> void Vector<T>::mergeSort( Rank lo, Rank hi )
{
    if( hi - lo < 2)
        return;
    int mi = (lo + hi) / 2;
    mergeSort( lo, mi );
    megerSort( mi, hi );
    merge( lo, mi, hi );
}

template<typename T> void Vector<T>::merge( Rank lo, Rank mi, Rank hi )
{
    T* A = _elem + lo;
    int lb = mi - lo;
    T* B = new T[lb];
    for( Rank i = 0; i < lb; B[i] = A[i++] );
    int lc = hi - mi;
    T* C = _elem + mi;
    for( Rank i = 0, j = 0, k = 0; ( j < lb ) || ( k < lc ); )
    {
        if( ( j < lb ) && ( !( k < lc ) || ( B[j] <= C[k] ) ) )
            A[i++] = B[j++];
        if( ( k < lc ) && ( !( j < lb ) || ( B[j] > C[k] ) ) )
            A[i++] = C[k++];
    }
    delete [] B;
}

// 堆排序
template<typename T> void Vector<T>::heapSort( Rank lo, Rank hi )
{
    
}

// 快速排序
template<typename T> void Vector<T>::quickSort( Rank lo, Rank hi )
{
    
}

// 插入排序
template<typename T> void Vector<T>::insertionSort( Rank lo, Rank hi )
{
    for( int i = lo; i < hi; i++ )
    {
        for( int j = lo; j < i; j++ )
        {
            if( _elem[i] > _elem[j] ){
                int num = _elem[j];
                for( int k = j-1; k >= i; k--)
                {
                    _elem[k+1] = _elem[k];
                }
                _elem[i] = num;
            }
        }
    }
}

template<typename T> void Vector<T>::swap( T a, T b)
{
    T m = a;
    a = b;
    b = m;
    
}
```





## 列表

#### 列表模板类

```c++
typedef int Rank;
#define ListNodePosi(T) ListNode<T>*

template<typename T> struct ListNode
{
    T data;
    ListNodePosi(T) pred;
    ListNodePosi(T) succ;
    ListNode() { }
    ListNode( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL ): data(e), pred(p), succ(s)
    {
      
    }
    ListNodePosi(T) insertAsPred( T const& e);
    ListNodePosi(T) insertAsSucc( T const& e);
}
```



## 二叉树



## 图

