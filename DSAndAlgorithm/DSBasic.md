[TOC]

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
            quickSort( lo, hi );			// 快速排序
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

## 栈与队列

### 括号匹配的递归实现

```c++
void trim( const char exp[], int& lo, int& hi )
{
    // 删除exp[lo, hi]不含括号的最长前缀、后缀
    while((lo <= hi ) && (exp[lo] != "(") && (exp[lo] != ")") )
        lo++;
    while((lo <= hi) && (exp[hi] != "(") && (exp[hi] != ")") )
        hi--;
}

int divide( const char exp[], int & lo, int& hi )
{
    // 切分exp[lo, hi]，使exp匹配仅当子表达式匹配
    int mi = lo;
    int crc = 1;	// crc为[lo, mi]范围内左、右括号数目之差
    while( ( 0 < crc ) && ( ++mi < hi ) )	// 逐个检查各字符，知道左、右括号数目相等，或者越界
    {
        if( exp[mi] == ")" ) crc--;
        if( exp[mi] == "(" ) crc++;
    }
    return mi;
    
}

bool paren( const char exp[], int lo, int hi )
{	// 检查表达式exp[lo, hi]是否匹配括号（递归版）
    trim( exp, lo, hi );	// 先匹配左右两边的括号
    if( lo > hi )
        return true;
    if( exp[lo] != "(" )	// 检查左边是否为左括号
        return false;
    if( exp[hi] != ")" )	// 检查右边是否为右括号
        return false;
    int mi = divide( exp, lo, hi );	// exp[lo, mi]是完整的括号对。当然前提是mi < hi情况下。
    if( mi > hi )
        return false;
    return paren( exp, lo + 1, mi - 1 ) && paren( exp, mi + 1, hi );
}

bool paren( const char exp[], int lo, int hi )
{	// 迭代实现
    Stack<char> S;
    for( int i = lo; i <= hi; i++ )
    {
        switch( exp[i] )
        {
            case '(':
            case '[':
            case '{':
                S.push( exp[i] );
                break;
            case ')':
                if( ( S.empty() ) || ( S.pop() != '(' ) )
                    return false;
                break;
            case ']':
                if( ( S.empty() ) || ( S.pop() != '[' ) )
                    return false;
                break;
            case '}':
                if( ( S.empty() ) || ( S.pop() != '}' ) )
                    return false;
                break;
            default:
                break;
        }
    }
    return S.empty();
}

float evaluate( char* S, char*& BPN )
{	// 对（已剔除空白格的）表达式S求值，并转换为逆波兰式RPN
    Stack<float> opnd;
    Stack<char> optr;
    optr.push( '\0' );
    while( !optr.empty() )
    {
        if( isDigit( *S ) )
        {
            readNumber( S, opnd );
            append( RPN, opnd.top() );
        }
        else
        {
            switch( orderBetween( optr.top(), *S ) )
            {
                case '<':
                    optr.push( *S );
                    S++;
                    break;
                case '=':
                    optr.pop();
                    S++;
                    break;
                case '>':
                    {
                    char op = optr.pop();
                    append( RPN, op );
                    if( '!' == op )
                    {
                        float pOpnd = opnd.pop();
                        opnd.push( calcu( op, pOpnd ) );
                    }
                    else
                    {
                        float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop();
                        opnd.push( calcu( pOpnd1, op, pOpnd2 ) );
                    }
                    break;
                    }
                default:
                    exit( -1 );
            }

        }
    }
    
}
```

### 试探回溯法

```c++
struct Queen
{
    int x, y;
    Queen( int xx = 0, int yy = 0 ): x( xx ), y( yy ) { };
    bool operator== (Queen const& q ) const {
        return ( x == q.x ) || ( y == q.y ) || ( x + y == q.x + q.y ) || ( x - y == q.x - q.y );
    }
    bool operator!=( Queen const& q ) const { return !( *this == q ); }
};

void placeQueens( int N )
{
    Stack<Queen> solu;
    Queen q( 0, 0 );
    do
    {
        if ( N <= solu.size() || N <= q.y )
        {	// 如果该行没有位置可以放Queen，就返回上一行，对上一行的Queen进行列增加
            q = solu.pop();
            q.y++;
        }
        else
        {
            while( ( q.y < N ) && ( 0 <= solu.find( q ) ) )
            {	// 遍历每列，找到与前面不相同的Queen
                q.y++;
                nCheck++;
            }
            if( N > q.y )
            {	// 开始进入下一行
                solu.push( q );
                if( N <= solu,size )
                    nSolu++;
                q.x++;
                q.y = 0;
            }
        }
    } while( ( 0 < q.x ) || ( q.y < N ) );
}
```

### 迷宫算法

```c++
typedef enum { AVAILABLE, ROUTE, BACKTRACKED, WALL } Status;

typedef enum { UNKNOWN, EAST, SOUTH, WEST, NORTH, NO_WAY } ESWN;

inline ESWN nextESWN( ESWN eswn ) { return ESWN( eswn + 1 ); }

struct Cell
{
    int x, y;
    Status status;
    ESWN incoming, outgoing;
};

#define LABY_MAX 24
Cell laby[LABY_MAX][LABY_MAX];


inline Cell* neighbor( Cell* cell )
{
    switch( cell-> outgoing )
    {
        case EAST : return cell + LABY_MAX;
        case SOUTH: return cell + 1;
        case WEST: return cell - LABY_MAX;
        case NORTH: return cell - 1;
        default:
            exit(-1);
    }
}

inline Cell* advance( Cell* cell )
{
    Cell* next;
    switch( cel-> outgoing )
    {
        case EAST:
            next = cell + LABY_MAX;
            next->incoming = WEST;
            break;
        case SOUTH:
            next = cell + 1;
            next->incoming = NORTH;
            break;
        case WEST:
            next = cell - LABY_MAX;
            next->incoming = ESAT;
            break;
        case NORTH:
            next = cell - 1;
            next->incoming = SOUTH;
            break;
        default:
            exit(-1);
    }
    return next;
}

bool labyrinth( Cell Laby[LABY_MAX][LABY_MAX], Cell* s, Cell* t)
{
    if( ( AVAILABLE != s->status ) || ( AVAILABLE != t->status ) ) return false;
    Stack<Cell*> path;
    s->incoming = UNKNOWN;
    s->status = ROUTE;
    path.push( s );
    do
    {
        Cell* c = path.top();
        if( c == t ) return true;
        
        while( NO_WAY > ( c->outgoing = nextESWN( c->outgoing ) ) )		// 寻找出去的方向
            if( AVAILABLE == neighbor(c)->status )
                break;
        if( NO_WAY <= c->outgoing )		// 该路口没有方向选择，进行回溯，将原来标记的status值为ROUTE改为BACKTRACKED
        {
            c->status = BACKTRACKED;
            c = path.pop();
        }
        else
        {	// 将下一个可利用的点添加到path，并标记为路径
            path.push( c = advance( c ) );
            c->outgoing = UNKNOWN;
            c->status = ROUTE;
        }
    } while( !path.empty() );
    return false;
}
```



## 二叉树

```c++
// 二叉树的遍历

// 先序遍历（递归版）

// 先序遍历（迭代版）

// 中序遍历（递归版）

// 中序遍历（迭代版）
template<typename T, typename VST> void travIn_I2( BinNodePosi(T) x, VST& visit )
{
    Stack<BinNodePosi(T)> S;
    while(true)
    {
        if(x)
        {
            S.push(x);
            x = x->lc;
        }
        else if(!s.siEmpty())
        {   
            x = S.pop();
        	visit(x);
            x = x->rc;
        }
        else
            break;
    }
}
// 后序遍历（递归版）

// 后序遍历（迭代版）

```



### Huffman编码

```c++
// PFC编码树 
#include "../BinTree/BinTree.h";
typedef BinTree<char> PFCTree;

#include "../Vector/Vector.h"
typedef Vector<PFCTree*> PFCForest;

#include "../Bitmap/Bitmap.h"		// 练习2-34的代码
#include "../Skiplist/Skiplist.h"	// 引入Skiplist式词典结构实现
typedef Skiplist<char, char*> PFCTable;	// PFC编码表，词条格式为：（key = 字符， value = 编码串）


#define N_CHAR (0x80 - 0x20)		// 只考虑可打印字符


int main(int argc, char* argv[])
{
    PFCForest* forest = initForest();
    PFCTree* tree = generateTree(forest);
    release(forest);
    PFCTable* table = generateTable(tree);
    for( int i = 1; i < argc; i++)
    {
        Bitmap codeString;
        int n = ecode( table, codeString, argc[i] );	// 根据编码表生成（长度为n）
        decode(tree, codeString, n);					// 利用编码树，对长度为n的二进制编码串解码（直接输出）
    }
    release(table);
    release(tree);
    return 0;
}

PFCForest* initForest()
{
    PFCForest* forest = new PFCForest;
    for ( int i = 0; i < N_CHAR; i++ )
    {
        forest.insert(i, new BinTree());
        (*forest)[i]->insertAsRoot( 0x20 + i );
    }
    return forest;
}

PFCTree* generateTree( PFCForest* forest )
{
    srand((unsigned int) time(NULL));
    while( 1 < forest->size() )
    {
        PFCTree* s = new PFCTree;
        s->insertAsRoot('^');
        Rank r1 = rand() % forest->size();
        s->attachAsLC(s->root(), (*forest)[r1]);
        forest->remove(r1);
        Rank r2 = rand() % forest->size();
        s->attachAsRC(s->root(), (*forest)[r2]);
        forest->remove(r2);
        forest->insert(forest->size(), s);
    }
    return (*forest)[0];	// 至此forest中只存在一棵树，即全局编码树
}

// 通过遍历获取各个字符编码
void generateCT(Bitmap* code, int length, PFCTable* table, BinNodePosi(char) v)
{
    if(IsLeaf(*v))
    {
        table->put(v->data, code->bits2string(length));
        return;
    }
    if(HasChild(*v))
    {
        code->clear(length);
        generateCT(code, length + 1, table, v->lc);
    }
    if( HasRChild(*v) )
    {
        code->set(length);
        generateCT(code, length + 1, table, v->rc);
    }
}

// 构造编码表
PFCTable* generateTable( PFCTree* tree )
{
    PFCTable* table = new PFCTable;
    Bitmap* code = new Bitmap;
    generateCT( code, 0, table, tree->root() );
    release(code);
    return table;
}

int encode( PFCTable* table, Bitmap& codeString, char* s )
{
    int n = 0;
    for( size_t m = strlen(s), i = 0; i < m; i++ )
    {
        char** pCharCode = table->get(s[i]);
        if(!pCharCode)
            pCharCode = table->get(s[i] + 'A' - 'a');
        if(!pCharCode)
            pCharCode = table->get( ' ' );
        printf( "%s", *pCharCode );			// 输出当前字符的编码
        for( size_t m = strlen(*pCharCode), j = 0; j < m; j++ )
            '1' == *(*pCharCode + j) ? codeString.set(n++) : codeString.clear(n++);
    }
    return n;
}

void decode( PFCTree* tree, Bitmap& code, int n )
{
    BinNodePosi(char) x = tree->root();
    for( int i = 0; i < n; i++ )
    {
        x = code.test(i) ? x->rc : x->lc;
        if(IsLeaf(*x))
        {
            printf("%c", x->data);
            x = tree->root();
        }
    }
}
```

```c++
// huffman编码树
#define N_CHAR (0x80 - 0x20);
struct HuffChar
{
    char ch;
    int weight;
    HuffChar(char c = '^', int w = 0) : ch(c), weight(w) { };
    bool operator<(HuffChar const& hc )
    {
        return weight > hc.weight;	// 故意大小颠倒
    }
    bool operator==(HuffChar const& hc )
    {
        return weight == hc.weight;
    }
}
#define HuffTree BinTree<HuffChar>
#include "../List/List.h";
typedef List<HuffTree*> HuffForest;

#include "../Bitmap/Bitmap.h"
typedef Bitmap HuffCode;

#include "../Hashtable/Hashtable.h";
typedef Hashtable<char, char*> HuffTable;

int main(int argc, char* argv )
{
    int* freq = statistics(argv[1]);
    Hufforest* forest = initForest(freq);
    release(freq);
    HuffTree* tree = generateTree(forest);
    release(forest);
    HuffTable* table = generateTable(tree);
    for( int i = 2; i < argc; i++ )
    {
        Bitmap* codeString = new Bitmap;
        int n = encode(table, codeString, argv[i]);
        decode(tree, codeString, n);
        release(codeString);
    }
    release(table);
    release(tree);
    return 0;
}

int* statistics(char* sample_text_file)
{
    int* freq = new int[N_CHAR];
    memset(freq, 0, sizeof(int)*N_CHAR);
    FILE* fp = fopen(sample_text_file, "r");
    for( char ch; 0 < fscanf(fp, "%c", &ch); )
        if(ch >= 0x20)
            freq[ch-0x20]++;
    fclose(fp);
    return freq;
}

HuffForest* initForest(int* freq)
{
    HuffForest* forest = new HuffForest;
    for( int i = 0; i < N_CHAR; i++ )
    {
        forest->insert(i, new HuffTree);
        forest->last()->data->insertAsRoot(HuffChar(0x20+i, freq[i]));
    }
    return forest;
}

HuffTree* minHChar( HuffForest* forest )
{
    // ListNodePosi(HuffTree*) p = forest->first();
    // ListNodePosi(HuffTree*) minChar = p;
    // 上面是源码，增加的ListNodePosi是没用的，多加的？记得去视频课上查看
    (HuffTree*) p = forest->first();
    (HuffTree*) minChar = p;
    int minWeight = p->data->root()->data.weight;
    while(forest->valid(p = p->succ))
        if(minWeight > p->data->root()->data.weight)
        {
            minWeight = p->data->root()->data.weight;
            minChar = p;
        }
    return forest->remove(minChar);
}

HuffTree* generateTree(HuffForest* forest)
{
    while(1 < forest->size())
    {
        HuffTree* T1 = minChar(forest);
        HuffTree* T2 = minCHar(forest);
        HuffTree* S = new HuffTree();
        S->insertAsRoot(HuffChar('^', T1->root->data.weight + T2->root->data.weight));
        S->attachAsLC(S->root(), T1);
        S->attachAsRC(S->root(), T2);
        forest->insertAsLast(S);
    }
    return forest->first()->data;
}

static void generateCT(Bitmap* code, int length, huffTable* table, BinNodePosi(HuffChar) v)
{
    if(IsLeaf(*v))
    {
        table->put(v->data.ch, code->bits2string(length));
        return;
    }
    if(HasLChild(*v))
    {
        code->clear(length);
        generateCT(code, length + 1, table, v->lc);
    }
    if(HasRChild(*v))
    {
        code->set(length);
        generateCT(code, length + 1, table, v->rc);
    }
}

HuffTable* generateTable(HuffTree* tree)
{
    HuffTable* table = new HuffTable;
    Bitmap* code = new Bitmap;
    generateCT(code, 0, table, tree->root() );
    release(code);
    return table;
}

int encode(HuffTable* table, Bitmap* codeString, char* s)
{
    int n = 0;
    for(size_t m = strlen(s), i = 0; i < m; i++)
    {
        char** pCharCode = table->get(s[i]);
        if(!pCharCode) pCharCode = table->get(s[i] + 'A' - 'a');
        if(!pCharCode) pCHarCode = table->get(' ');
        printf("%s", *pCharCode);
        for(size_t m = strlen(*pCharCode), j = 0; j < m; j++)
        {
            '1' == *(*pCharCode+j) ? codeString->set(n++) : codeString->clear(n++);
        }
    }
    printf("\n");
    return n;
}

int decode(HuffTree* tree, Bitmap* code, int n)
{
    BinNodePosi(HuffChar) x = tree->root();
    for( int i = 0; i < n; i++)
    {
        x = code->test(i) ? x->rc : x->lc;
        if(IsLeaf(*x))
        {
            printf("%c", x->data.ch);
            x = tree->root();
        }
    }
}
```



## 图

### 抽象数据类型

#### Graph模板类

```c++
typedef enum { UNDISCOVERD, DISCOVERED, VISITED } VStatus;				// 顶点状态
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType;	// 边在遍历树中所属的类型

template <typename Tv, typename Te>									// 边在遍历树中所属的类型
class Graph
{		// 图Graph模板类
private:
	void reset()
    {		// 所有顶点、边的辅助信息复位
        for ( int i = 0; i < n; i++ )
        {
            status(i) = UNDISCOVERED;
            dTime(i) = fRime(i) = -1;
            parent(i) = -1;
            priority(i) = INT_MAX;
            for ( int j = 0; j < n; j++ )
            {
                if ( exists( i, j ) ) type(i, j) = UNDETERMINED;
            }
        }
    }
    void BFS( int, int& );						// （连通域）广度优先搜索算法
    void DFS( int, int& );						// （连通域）深度优先搜索算法
    void BCC( int, int&, Stack<int>& );			// （连通域）基于DFS的双连通分量分解算法
    bool TSort(int, int&, Stack<Tv>* );			// （连通域）基于DFS的拓扑排序算法
    template <typename PU> void PFS( int, PU );	// （连通域）优先级搜索框架
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs( int s )
{
    reset();
    int clock = 0;
    int v = s;
    do
        if( UNDISCOVERED == status(v) )
            BFS( v, clock);
    while ( s != ( v = ( ++v % n ) ) );
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS( int v, int* clock )
{
    Queue<int> Q;
    status(v) = DISCOVERED;
    Q.enqueue(v);
    while( !Q.empty() )
    {
        int v = Q.dequeue();
        dTime(v) = ++clock;
        for ( int u = firstNbr(v); -1 < u; u = nextNbr(v, u) )
        {
            if( UNDISCOVERED == status(u) )
            {
                status(u) = DISCOVERED;
                Q.enqueue(u);
                type(v, u) = TREE;
                parent(u) = v;
            }
            else
            {
                type(v, u) = CROSS;
            }
        }
        status(v) = VISITED;
    }
}

template<typename Tv, typename Te> void Graph<Tv, Te>::dfs(int s)
{
    reset();
    int v = s;
    int clock = 0;
    do
    {
        if(status(v) == UNDISCOVERED)
            DFS(v, clock);
    } while (s != (v = ++v % n))
}

template<typename Tv, typename Te> void Graph<Tv, Te>::DFS(int s, int& clock)
{
    dTime(v) = ++clock;
    status(v) = DISCOVERED;
    for( int u = firstNbr(v); -1 < u; u = nextNbr(v, u) )
    {
        switch( status(u) )
        {
            case UNDISCOVERED:
                status(v, u) = TREE;
                parent(u) = v;
                DFS(u, clock);
                break;
            case DISCOVERED:
                status(v, u) = BACKWORD;
                break;
            default:
                status(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;
    fTime(v) = ++clock;
}

// 基于DFS的拓扑排序算法
template<typename Tv, typename Te> Stack<Tv>* Graph<Tv, Te>::tSort(int s)
{
    retset();
    int clock = 0;
    int v = s;
    Stack<Tv>* S = new Stack<Tv>;
    do
    {
        if (UNDISCOVERED == status(v) )
            if ( !TSort(v, clock, S) )
            {
                while ( !S->empty() )
                {
                 	S->pop();
                    break;
				}
            }
    } while( s != ( v == ( ++v % n ) ) );
    return S;
}
template <typename Tv, typename Te> bool Graph<Tv, Te>::TSort( int v, int& clock, Stack<Tv>* S )
{
    dTime(v) = ++clock;
    status(v) = DISCOVERED;
    for ( int u = firstNbr(v); u > -1; u = nextNbr(v, u) )
    {
        switch ( status(u) )
        {
            case UNDISCOVERED:
                parent(u) = v;
                type(v, u) = TREE;
                if ( !TSort( u, clock, S ) )
                    return false;
                break;
            case DISCOVERED:
                type(v, u) = BACKWORD;
                return false;
            default:
                type( v, u ) = ( dTime(v) < dTime(u) ) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;
    S->push(vectex(v));
    return true;
}

template <typename Tv, typename Te> void Graph<Tv, Te>::bcc( int s )
{
    reset();
    int clock = 0;
    int v = s;
    Stack<int> S;
    do
    {
        if ( UNDISCOVERED == status(v) )
        {
            BCC( v, clock, S );
            S.pop();
        }
    }
    while ( s != ( v = ( ++v % n ) ) );
}

template <typename Tv, typename Te> void Graph<Tv, Te>::BCC( int v, int& clock, Stack<int>& S)
{
    hca(v) = dTime(v) = ++clock;
    status(v) = DISCOVERED;
    S.push(v);
    for ( int u = firstNbr(v); u > -1; u = nextNbr(v, u) )
    {
        switch( status(u) )
        {
            case UNDISCOVERED:
                parent(u) = v;
                type(u, v) = TREE;
                BCC( u, clock, S);
                if ( hca(u) , dTime(v) )
                {
                    hca(v) = min(hca(v), hca(u));
                }
                else
                {
                    while( v != S.pop());
                    S.push(v);
                }
                break;
            case DISCOVERED:
                type(v, u) = BACKWARD;
                if ( u != parent(v) )
                    hca(v) = min(hca(v), dTime(u) );
                break;
            default:
                type(v, u) = (dTime(v) < dTIme(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;
}
// 最短路径：通过使用广度遍历，类似于树的层次遍历，都是按照从最短距离到最长距离，一步步遍历下去
template <typename Tv, typename Te> void Graph<Tv, Te>::bcc(int s)
{
    reset();
    int clock = 0;
    int v = s;
    Stack<int> s;
    do
        if ( UNDISCOVERED == status(v) )
        {
            BCC(v, clock, S);
            S.pop();
        }
    while (s != ( v = (++v % n) ) );
}

#define hca(x) (fTime(x))	// 利用此处闲置的fTime[]充当hca[]
template <typename Tv, typename Te> void Graph<Tv, Te>::BCC(int v, int& clock, Stack<int>& S)
{
    hca(v) == dTime(v) = ++clock;
    status(v) = DISCOVERED;
    S.push(v);
    for ( int u = firstNbr(v); -1 < u; u = nextNbr(v, u) )
    {
        switch( status(u) )
        {
            case UNDISCOVERED:
                parent(u) = v;
                type(v, u) = TREE;
                BCC(u, clock, S);
                if( hca(u) < dTime(v) )
                    hca(v) = min( hca(v), hca(v) );
                else
                {
                    while( v!= S.pop() );
                    S.push(v);
                }
                break;
            case DISCOVERED:
                type(v, u) = BACKWARD;
                if(u != parent(v))
                    hca(v) = min(hca(v), dTime(u));
                break;
            default:
                type(v, u) = (dTime(v) < dTime(u) ) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;
}
template <typename Tv, typename Te> template <typename PU> void Graph<Tv, Te>::pfs( int s, PU prioUpdater )
{
    reset();
    int v = s;
    do
        if (UNDISCOVERED == status(v))
            PFS(v, prioUpdater);
    while (s != (v == (++v % n)));
}

template<typename Tc, typename Te> template <typename PU> void Graph<Tv, Te>::PFS(int s, PU prioUpdater )
{
    priority(s) = 0;
    status(s) = VISITED;
    parent(s) = -1;
    while(1)
    {
        for( int w = firstNbr(s); -1 < w; w = nextNbr(s, w))
            prioUpdater( this, s, w );
        for( int shortest = INT_MAX, w = 0; w < n; w++ )
        {
            if ( UNDISCOVERED == status(w) )
                if( shortest > priority(w) )
                {
                    shortest = priority(w);
                    s = w;
                }
        }
        if( VISITED == status(s) )
            break;
        status(s) = VISITED;
        type(parent(s), s) = TREE;
    }
}
#undef hca

// using PFS() to do prim algorithm
template <typename Tv, typename Te> struct PrimPU {
    virtual void opeartor()( Graph<Tv, Te>* g, int uk, int v )
    {
        if ( UNDISCOVERED == g->status(v) )
        {
            if (g->priority(v) > g->weight(uk, v) )
            {
            	g->priority(v) = g->weight(uk, v);
            	g->parent(v) = uk;
            }
        }
    }
};

template <typename Tv, typename Te> struct DijkstraPU
{
    virtual void opeartor() (Graph<Tv, Te>* g, int uk, int v)
    {
        if( UNDISCOVERED == g->status(v) )
            if (g->priority(v) > g->priority(uk) + g->weight(uk, v))
            {
                g->priority = g->priority(uk) + g->weight(uk, v);
                g->parent(v) = uk;
            }
    }
}
```

## 搜索树

```c++
#include "../BinTree/BinTree.h"

template <typename T> class BST: public BinTree<T>
{
protected:
    BinNodePosi(T) _hot;
    BinNodePosi(T) connect34(BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
public:
    virtual BinNodePosi(T) & search (const T& e);
    virtual BinNodePosi(T) insert (const T& e);
    virtual bool remove( const T& e );
    
};
template <typename T> static BinNodePosi(T) & searchIn( BinNodePosi(T) & v, const T& e, BinNodePosi(T) & hot )
{
    if( !v || ( e == v->data ) )
        return v;
    hot = v;
    return searchIn((( e < v->data ) ? v->lc : v->rc), e, hot);
}

template <typename T> BindNodePosi(T) & BST<T>::search( const T& e)
{
    return searchIn(_root, e, _hot=NULL);
}

template <typename T> BindNodePosi(T) BST<T>::insert( const T& e )
{
    BindNodePosi(T) & x = search(e);
    if (x)
        return x;
    x = new BinNode<T>(e, _hot);
    _size++;
    updateHightAbove(x);
    return x;
}

template <typename T> bool BST<T>::remove( const T& e)
{
    BinNodePosi(T) &x = search(e);
    if (!x)
        return false;
    removeAr(x, _hot);
    _size--;
    updateHeightAbove(_hot);
    return true;
}

template <typename T> static BindNodePosi(T) removeAt(BindNodePosi(T) & x, BindNodePosi(T) & hot)
{
    BinNodePosi(T) w = x;
    BinNodePosi(T) succ = NULL;
    if( !HasLChild(*x) )
        succ = x = x->rc;
    else if ( !HasRChild(*x) )
        succ = x= x->lc;;
    else
    {
        w = w->succ();
        swap( x->data, w->data );
        BinNodePosi(T) u = w->parent;
        (( u == x) ? u->rc : u->lc ) = succ = w->rc;
    }
    hot = w->parent;
    if ( succ )
        succ->parent = hot;
    release( w->data );
    release( w );
    return succ;
    
}
```



```c++
#include "../BST/BST.h"
#define Balanced(x) ( stature( (x).lc ) == stature( (x).rc ) )
#define BalFac(x) ( stature( (X).lc ) - stature( (x).rc ) )
#define AvlBalanced(x) ( ( -2 < BalFac(X) ) && ( BalFac(x) < 2 ) )
template <typename T> class AVL : public BST<T>
{
public:
    BinNodePosi(T) insert( const T& e );
    bool remove( const T& e);
};

#define tallerChild(x) ( \ 
    stature( (x)->lc ) > stature( (x)->rc ) ? (x)->lc : ( \ 
    stature( (x)->lc ) < stature( (x)->rc ) ? (x)->rc : ( \ 
    IsLChild( *(x) ) ? (x)->lc : (x)->rc \
                                                        ) \
                                                        ) \
)

template <typename T> BinNodePosi(T) AVL<T>::insert( const T& e )
    {
        BinNodePosi(T) & x = search(e);
        if(x)
            return x;
        BinNodePosi(T) xx = x = new BinNode<T>( e, _hot );
        _size++;
        for ( BinNodePosi(T) g = _hot; g; g = g->parent )
        {
            if ( !AvlBalanced(*g))
            {
                FromParentTo(*g) = rotateAt( tallerChild( tallerChild(g) ) );
                break;
            }
            else
                updateHeight(g);
		}
        return xx;
    }

template <typename T> bool AVL<T>::remove( const T& e )
{
    BinNodePosi(T) & x = search(e);
    if( !x )
        return false;
    removeAt( x, _hot );
    _size--;
    for ( BinNodedPosi(T) g = _hot; g; g = g->parent )
    {
        if (!AvlBalanced( *g ) )
            g = FromParentTo( *g ) = rotateAt( tallerChild( tallerChild( g ) ) );
        updateHeight( g ); 
    }
    return true;
}

// 平衡树“3+4”操作
template <typename T> BinNodePosi(T) BST<T>::connect34 (
	BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
	BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
)
{
    a->lc = T0;
    T0->parent = a;
    a->rc = T1;
    T1->parent = T1;
    updateHeight(a);
    b->lc = a;
    a->parent = b;
    b->rc = c;
    c->parent = b;
    c->lc = T2;
    T2->parent = c;
    c->rc = T3;
    T3->parent = c;
    updateHeight(c);
    updateHeight(b);
    return b;
    
}

// BST节点旋转变换统一算法（3节点 + 4子树），返回调整之后局部子树根节点的位置
template <typename T> BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v)
{
    BinNodePosi(T) p = v->parent;
    BinNodePosi(T) g = p->parent;
    if (IsLChild(*p))
    {
        if (IsLChild(*v))
        {
        	p->parent = g->parent;   
            return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        }
        else
        {
            v->parent = g->parent;
            return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    }	
    else
    {
        if (ISLChild(*v))
        {
            v->parent = g->parent;
            return conenct34(g, v, p, g->lc, v->lc, v->rc, p->rc);
        }
        else
        {
            p->parent = g->parent;
            return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
        }
    }
}
```

## 高级搜索树

**数据局部性**包含以下两个方面：

1. 刚刚被访问的元素，极有可能在不久后的将来被再次访问
2. 被访问的元素，极有可能在不久之前被访问的某个元素附近。

### 伸展树

```c++
#include "../BST/BST.h"	// 基于BST实现Splay
template <typename T> class Splay : public BST<T>
{
protected:
    BinNodePosi(T) splay(BinNodePosi(T) v);
public:
    BinNodePosi(T) & search(const T& e);	 // 查找
    BinNodePosi(T) insert(const T& e);		 // 插入
    bool remove(const T& e);				// 删除
};
// 在节点*p与*lc（可能为空）之间父（左）子关系
template <typename NodePosi> inline void attachAsLChild( NodePosi p, NodePosi lc)
{
    p->lc = lc;
    if (lc)
        lc->parent = p;
}

// 在节点*p与*rc（可能为空）之间建立父（右）子关系
template <typename NodePosi> inline void attachAsRChild( NodePosi p, NodePosi rc)
{
    p->rc = rc;
    if (rc)
    {
        rc->parent = p;
    }
}

// Splay树伸展算法：从节点v出发逐层伸展
template <typename T> BinNodePosi(T) splay(BinNodePosi(T) v)
{
    if (!v)
        return;
    BinNodePosi(T) p;
    BinNodePosi(T) g;
    while ((p = v->parent) && (g = p->parent))
    {
        BinNodePosi(T) gg = g->parent;
        if(IsLChild(*v))
        {
            if(IsLChild(*p))
            {
                attachAsLChild(g, p->rc);
                attachAsLChild(p, v->rc);
                attachAsRChild(p, g);
                attachAsRChild(v, p);
            }
            else
            {
                attachAsLChild(g, v->rc);
                attachAsLChild(v, g);
                attachAsRChild(p, v->lc);
                attachAsLChild(v, p);
            }
        }
        else
        {
            if(IsRChild(*v))
            {
                attachAsRChild(g, p->lc);
                attachAsRChild(p, v->lc);
                attachAsLChild(v, p);
                attachAsLChild(p, g);
            }
            else
            {
             	attachAsRChild(g, v->lc);
                attachAsLChild(p, v->rc);
                attachAsLChild(v, g);
                attachAsRChild(v, p);
            }
        }
        if (!gg)
            v->parent = NULL;
        else
        {
            ( g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
        }
        updateHeight(g);
        updateHeight(p);
        updateHeight(v);
    }
    if (p = v->parent)
    {
        if (IsLChild(*v))
        {
            attachAsLChild(p, v->lc);
            attachAsRChild(v, p);
        }
        else
        {
            attachAsRChild(p, v->lc);
            attachAsLChild(v, p);
        }
        updateHeight(p);
        updateHeight(v);
    }
    v->parent = NULL;
    return v;
}

template <typename T> BinNodePosi(T) & Splay<T>::search(const T& e)
{
    BinNodePosi(T) p = searchIn( _root, e, _hot=NULL);
    _root = splay(p ? p : _hot);	// 将最后一个访问的节点伸展至于根
    return _root;
}

// 将元素e插入伸展树中
template <typename T> BinNodePosi(T) Splay<T>::insert(const T& e)
{
    if (!_root )
    {
        _size++;
        return _root = new BinNode<T>(e);
    }
    if (e == search(e)->data)
        return _root;
    _size++;
    BinNodePosi(T) t = _root;
    if (_root->data < e)
    {
        t->parent = _root = new BinNode<T>(e, NULL, t, t->rc);
        if (HasRChild(*t))
        {
            t->rc->parent = _root;
            t->rc = NULL;
        }
    }
    else 
    {
        t->parent = _root = newBinnode<T>(e, NULL, t->lc, t);
        if (HasLChild(*t))
        {
            t->lc->parent = _root;
            t->lc = NULL;
        }
    }
    updateHeightAbove(t);
    return _root;
}

template <typename T> bool Splay<T>::remove( const T& e)
{
    if (!_root || (e != search(e)->data))
        return false;
    BinNodePosi(T) w = _root;
    if (!HasLChild(*_root))
    {
        _root = _root->rc;
        if (_root)
            _root->parent = NULL;
    }
    else if (!HasRChild(*_root))
    {
        _root = _root->lc;
        if (_root)
            _root->parent = NULL;
    }
    else
    {
        BinNodePosi(T) lTree = _root->lc;
        lTree->parent = NULL;
        _root->lc = NULL;
        _root = _root->rc;
        _root->parent = NULL;
        search(w->data);
        _root->lc = lTree;
        lTree->parent = _root;
    }
    release(w->data);
    release(w);
    _size--;
    if(_root)
        updateHeight(_root);
    return true;
}
```

### B-树

```c++
#include "../vector/vector.h"
#include "BTNode.h"
#define BTNodePosi(T) BTNode<T>*

template <typename T> struct BTNode
{
    BTNodePosi(T) parent;
    Vector<T> key;
    Vector<BTNodePosi(T)> child;
    BTNode()
    {
        parent = NULL;
        child.insert(0, NULL);
    }
    BTNode( T e, BTNodePosi(T) lc = NULL, BTNodePosi(T) rc = NULL)
    {
        parent = NULL;
        key.insert(0, e);
        child.insert(0, lc);
        child.insert(1, rc);
        if(lc) lc->parent = this;
        if(rc) rc->parent = this;
    }
};

template <typename T> class BTree
{
protected:
    int _size;			// 存放的关键码总数
    int _order;			// B-树的阶次，至少3（创建时指定，一般不能修改）
    BTNodePosi(T) _root;	// 根节点
    BTNodePosi(T) _hot;		// BTree::search()最后访问的非空(除非树空)的节点位置
    void solveOverflow(BTNodePosi(T));	// 因插入而上溢之后的分裂处理
    void solveUnderflow(BTNodePosi(T));	// 因删除而下溢之后的合并处理
public:
    BTree (int order = 3): _order(order), _size(0)
    {
        _root = new BTNode<T>();
    }
    ~BTNode()
    {
        if(_root)
            release(_root);
    }
    int const order()
    {
        return _order;
    }
    
    int const size()
    {
        return _size;
    }
    
    BTNodePosi(T) & root()
    {
        return _root;
        
    }
    
    bool empty() const
    {
        return !_root;
    }
    
    BTNodePosi(T) search(const T& e);
    bool insert( const T& e);
    bool remove( const T& e);
    
}
template <typename T> void BTree::solveOverflow(BTNodePosi(T) v)
{
    if (_order >= v->child.size())
        return;
    // 从v的中间关键码开始拆分结点v变成两个结点
    Rank s = _order / 2;
    BTNodePosi(T) u = new BTNode<T>();
    for (Rank j = 0; j < _order - s - 1; j++)
    {
        u->key.insert(j, v->key.remove(s+1));
        u->child.insert(j, v->child.remove(s+1));
    }
    u->child.insert(_order-s-1, v->child.remove(s+1));

    if (u->child[0])
    {
    	for(Rank j = 0; j < _order-s; j++)
    	{
        	u->child[j]->parent = u;
    	}
    }
    // 将关键码上升到父节点
    BTNodePosi(T) p = v->parent;
    if(!p)
    {
        _root = p = new BTNode<T>();
        v->parent = p;
        p->child[0] = v;
    }
    Rank r = 1 + p->key.search(v->key[0]);
    p->key.insert(r, v->key.remove(s));
    p->child.insert(r+1, u);
    u->parent = p;
    
    sloveOverflow(p);
}

template <typename T> void BTree::solveUnderflow(BTNodePosi(T) v)
{
    if ((_order+1)/2 <= v->child.size())
        return;
    BTNodePosi(T) p = v->parent;
    if (!p)
    {
        // v作为树根且有唯一的子节点
        if (!v->key.size() && v->child[0])
        {
            _root = v->child[0];
            _root->parent = NULL;
            v->child[0] = NULL;
            release(v);
        }
        return;
    }
    Rank r = 0;
    while ( p->child[r] != v )
        r++;
    // 情况1：向左兄弟借关键码
    if (r > 0)
    {
        BTNodePosi(T) ls = p->child[r-1];
        if((_order+1)/2 < ls->child.size())
        {
            v->key.insert(0, p->key[r-1]);
            p->key.insert(r-1, ls->key.remove(ls->key.size() - 1));
            v->child.insert(0, ls->child.remove(ls->child.size() - 1));
            if (v->child[0])
                v->child[0]->parent = v;
            return;
        }
    }
    // 情况2：向右兄弟借关键码
    if (r < p->child.size() - 1)
    {
        BTNodePosi(T) rs = p->child[r+1];
        if ((_order+1/2) < rs->child.size())
        {
            v->key.insert(v->key.size(), p->key[r]);
            p->key[r] = rs->key.remove(0);
            v->child.insert(v->child.size(), rs->child.remove(0));
            if (p->child[v->child.size-1])
            {
                p->child[v->child.size-1]->parent = v;
            }
            return;
        }
    }
    // 情况3：左右兄弟可能为空（不会同时为空），或者左右兄弟太瘦
    if(0 < r)
    {
        // 和左兄弟合并
        
        BTNodePosi(T) ls = p->child[r-1];
        ls->key.insert(ls->key.size(), p->key.remove(r-1));
        p->child.remove(r);
        ls->child.insert(ls->child.size(), v->child.remove(0));
        if (ls->child[ls->child.size() - 1])
			ls->child[ls->child.size-1]->parent = ls;
        while (!v->key.empty())
        {
            ls->key.insert(ls->key.size(), v->key.remove(0));
            ls->child.insert(ls->child.size(), v->child.remove(0));
            if (ls->child[ls->child.size() - 1])
                ls->child[ls->child.szie() - 1]->parent = ls;
        }
        release(v);
    }
    else
    {
        // 和右兄弟合并
        BTNodePosi(T) rs = p->child[r+1];
        rs->key.insert(0, p->key.remove(r));
        p->child.remove(r);
        rs->child.insert(0, v->child.remove(v->child.size()-1));
        if(rs->child[0])
            rs->child[0]->parent = rs;
        while (!v->key.empty())
        {
            rs->key.insert(0, v->key.remove(v->key.size()-1));
            rs->child.insert(0, v->child.remove(v->child.size()-1));
        	if (rs->child[0])
            {
                rs->child[0]->parent = rs;
            }
        }
        release(v);
            
    }
    solveUnderflow(p);
    return;
    
}

template <typename T> void BTree::search(const T& e)
{
    BTNodePosi(T) v = _root;
    _hot = NULL;
    while (v)
    {
        Rank r = v->key.search(e);		// 在当前节点找到不大于e的最大关键码
        if (( 0 <= r ) && (e == v->key[r] ) )
        {
            return v;
        }
        _hot = v;
        v = v->child[r+1];
    }
    return NULL;
}

template <typename T> bool BTree::insert(const T& e)
{
    BTNodePosi(T) v = search(e);
    if (v)
        return false;
    Rank r = _hot->key.search(e);
    _hot->key.insert(r+1, e);
    _hot->child.insert(r+2, NULL);
    _size++;
    solveOverflow(_hot);		// 如果有必要，需要做分裂
    return true;
}

template <typename T> bool BTree::remove(const T& e)
{
    BTNodePosi(T) v = search(e);
    if (!v)
        return false;
    Rand r = v->key.search(e);
    if (v->child[0])
    {
        BTNodePosi(T) u = v->child[r+1];
        while (u->child[0])
            u = u->child[0];
        v->key[r] = u->key[0];
        v = u;
        r = 0;
    }
    v->key.remove(r);
    v->child.remove(r+1);	
    _size--;
    solveUnderflow(v);
    return true;
}

```



### 红黑树

```c++
#include "../BST/BST.h"

#define IsBlack(p) (!(p) || (RB_BLACK == (p)->color))	// 外部节点也视作黑节点
#define IsRed(p) (!IsBlack(p))		// 非黑即红
#define BlackHeightUpdated(x) ( \
	/* RedBlack 高低更新条件 */ \
    ( stature((x).lc) == stature((x).rc) ) && ((x).height == (IsRed(& x) ? stature((x).lc) : stature((x).lc)+1 )) \
)

template <typename T> class RedBlack : public BST<T>
{
protected:
    void solveDouble(BinNodePosi(T) x);		// 双红修正
    void solveDoubleBlack(BinNodePosi(T) x);	// 双黑修正
    int updateHeight(BinNodePosi(T) x);		// 更新节点x的亮度
public:
    BinNodePosi(T) insert( const T& e);		// 插入
    bool remove(const T& e);				// 删除
    
};

template <typename T> int ReadBlack::updateHeight(BinNodePosi(T) x)
{
    x->height = max(stature(x->lc), stature(x->rc));
    return IsBlack(x) ? x->height++ : x->height;
}

template <typename T> void solveDouble(binNodePosi(T) x)
{
    
}

template <typename T> void sloveDoubleBlack(BinNodePosi(T) x)
{
    
    
}

template <typename T> BinNodePosi(T) insert(const T& e)
{
    
}

template <typename T> bool remove(const T& e)
{
    
}
```

### kd-树

```c++

```

