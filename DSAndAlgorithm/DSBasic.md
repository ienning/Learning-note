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
// 二分查找法（版本A）：在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _sizetemplate<typename T> static Rank BindSearch( T* A, T const& e, Rank lo, Rank hi ){    while( lo < hi )    {        Rank mi = ( lo + hi ) >> i;        if( e < a[mi] )            hi = mi;        else if( A[m] < e )            lo  = mi + 1;        else return mi;    }    return -1;}// 二分查找算法（版本B）template<typename T> static Rank bindSearch( T* A, const& e, Rank lo, Rank hi ){    while( 1 < hi - lo )    {        Rank mi = ( lo + hi ) >> 1;        ( e < A[mi] ) ? hi = mi : lo = mi;    }    return ( e == A[lo] ) ? lo : -1;}// 二分查找算法（版本C）template<typename T> static Rank bindSearch( T* A, const& e, Rank lo, Rank hi ){    while (lo < hi)    {        Rank mi = ( lo + hi ) >> 1;        ( e < A[mi] ) ? hi = mi : lo = mi + 1;    }    return --lo;}
```



#### Fibonacci查找

```c++
#include "../fibonacci/Fib.h"template <typename T> static Rank fibSearch( T* A, T const & e, Rank lo, Rank hi ){    Fib fib(hi - lo);    while( lo < hi )    {        while( hi - lo < fib.get() )            fib.prev();        Rank mi = lo + fib.get() - 1;        if( e < A[mi] )            hi = mi;        else if( A[mi] < e )            lo = mi + 1;        else return mi;    }    return -1;}
```

#### 插值查找



### 气泡排序

```C++
// 排序器template<typename T> void Vector<T>::sort( Rank lo, Rank hi ){    switch( rank() % 5 )    {        case 1:            bubbleSort( lo , hi );		// 起泡排序            break;        case 2:            selectionSort( lo, hi );	// 选择排序            break;        case 3:            mergeSort( lo, hi );		// 归并排序            break;        case 4:            heapSort( lo, hi );			// 堆排序            break;        case 5:            quickSort( lo, hi );			// 快速排序            break;        case 6:            insertionSort( lo, hi );		// 插入排序            break;                }}// 起泡排序template<typename T> void Vector<T>::bubbleSort( Rank lo, Rank hi ){    while( !bubble(lo, hi--); )}template<typename T> void Vector<T>::bubble( Rank lo, Rank hi ){    bool result = true;    while( ++lo < hi )    {        if( _elem[lo - 1] > _elem[lo] )        {            swap( _elem[lo - 1], _elem[lo] );            result = false;        }    }    return result;}// 选择排序template<typename T> void Vector<T>::selectionSort( Rank lo, Rank hi ){    int index;    int max;    for( int j = hi - 1; j >= lo; j++)    {        index = j;        max = _elem[j];        for( int i = lo; i <= j; i++)        {            if( _elem[i] > max )            {                index = i;                max = _elem[i];            }        }        if( index != j )        {        	swap( _elem[index], _elem[j] );            }    }    for( int i = lo+1; i < hi; i++)    {        if( _elem[i] >= max )        {            max = _elem[i];            index = i;        }    }}// 归并排序template<typename T> void Vector<T>::mergeSort( Rank lo, Rank hi ){    if( hi - lo < 2)        return;    int mi = (lo + hi) / 2;    mergeSort( lo, mi );    megerSort( mi, hi );    merge( lo, mi, hi );}template<typename T> void Vector<T>::merge( Rank lo, Rank mi, Rank hi ){    T* A = _elem + lo;    int lb = mi - lo;    T* B = new T[lb];    for( Rank i = 0; i < lb; B[i] = A[i++] );    int lc = hi - mi;    T* C = _elem + mi;    for( Rank i = 0, j = 0, k = 0; ( j < lb ) || ( k < lc ); )    {        if( ( j < lb ) && ( !( k < lc ) || ( B[j] <= C[k] ) ) )            A[i++] = B[j++];        if( ( k < lc ) && ( !( j < lb ) || ( B[j] > C[k] ) ) )            A[i++] = C[k++];    }    delete [] B;}// 堆排序template<typename T> void Vector<T>::heapSort( Rank lo, Rank hi ){    }// 快速排序template<typename T> void Vector<T>::quickSort( Rank lo, Rank hi ){    }// 插入排序template<typename T> void Vector<T>::insertionSort( Rank lo, Rank hi ){    for( int i = lo; i < hi; i++ )    {        for( int j = lo; j < i; j++ )        {            if( _elem[i] > _elem[j] ){                int num = _elem[j];                for( int k = j-1; k >= i; k--)                {                    _elem[k+1] = _elem[k];                }                _elem[i] = num;            }        }    }}template<typename T> void Vector<T>::swap( T a, T b){    T m = a;    a = b;    b = m;    }
```





## 列表

#### 列表模板类

```c++
typedef int Rank;#define ListNodePosi(T) ListNode<T>*template<typename T> struct ListNode{    T data;    ListNodePosi(T) pred;    ListNodePosi(T) succ;    ListNode() { }    ListNode( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL ): data(e), pred(p), succ(s)    {          }    ListNodePosi(T) insertAsPred( T const& e);    ListNodePosi(T) insertAsSucc( T const& e);}
```

## 栈与队列

### 括号匹配的递归实现

```c++
void trim( const char exp[], int& lo, int& hi ){    // 删除exp[lo, hi]不含括号的最长前缀、后缀    while((lo <= hi ) && (exp[lo] != "(") && (exp[lo] != ")") )        lo++;    while((lo <= hi) && (exp[hi] != "(") && (exp[hi] != ")") )        hi--;}int divide( const char exp[], int & lo, int& hi ){    // 切分exp[lo, hi]，使exp匹配仅当子表达式匹配    int mi = lo;    int crc = 1;	// crc为[lo, mi]范围内左、右括号数目之差    while( ( 0 < crc ) && ( ++mi < hi ) )	// 逐个检查各字符，知道左、右括号数目相等，或者越界    {        if( exp[mi] == ")" ) crc--;        if( exp[mi] == "(" ) crc++;    }    return mi;    }bool paren( const char exp[], int lo, int hi ){	// 检查表达式exp[lo, hi]是否匹配括号（递归版）    trim( exp, lo, hi );	// 先匹配左右两边的括号    if( lo > hi )        return true;    if( exp[lo] != "(" )	// 检查左边是否为左括号        return false;    if( exp[hi] != ")" )	// 检查右边是否为右括号        return false;    int mi = divide( exp, lo, hi );	// exp[lo, mi]是完整的括号对。当然前提是mi < hi情况下。    if( mi > hi )        return false;    return paren( exp, lo + 1, mi - 1 ) && paren( exp, mi + 1, hi );}bool paren( const char exp[], int lo, int hi ){	// 迭代实现    Stack<char> S;    for( int i = lo; i <= hi; i++ )    {        switch( exp[i] )        {            case '(':            case '[':            case '{':                S.push( exp[i] );                break;            case ')':                if( ( S.empty() ) || ( S.pop() != '(' ) )                    return false;                break;            case ']':                if( ( S.empty() ) || ( S.pop() != '[' ) )                    return false;                break;            case '}':                if( ( S.empty() ) || ( S.pop() != '}' ) )                    return false;                break;            default:                break;        }    }    return S.empty();}float evaluate( char* S, char*& BPN ){	// 对（已剔除空白格的）表达式S求值，并转换为逆波兰式RPN    Stack<float> opnd;    Stack<char> optr;    optr.push( '\0' );    while( !optr.empty() )    {        if( isDigit( *S ) )        {            readNumber( S, opnd );            append( RPN, opnd.top() );        }        else        {            switch( orderBetween( optr.top(), *S ) )            {                case '<':                    optr.push( *S );                    S++;                    break;                case '=':                    optr.pop();                    S++;                    break;                case '>':                    {                    char op = optr.pop();                    append( RPN, op );                    if( '!' == op )                    {                        float pOpnd = opnd.pop();                        opnd.push( calcu( op, pOpnd ) );                    }                    else                    {                        float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop();                        opnd.push( calcu( pOpnd1, op, pOpnd2 ) );                    }                    break;                    }                default:                    exit( -1 );            }        }    }    }
```

### 试探回溯法

```c++
struct Queen{    int x, y;    Queen( int xx = 0, int yy = 0 ): x( xx ), y( yy ) { };    bool operator== (Queen const& q ) const {        return ( x == q.x ) || ( y == q.y ) || ( x + y == q.x + q.y ) || ( x - y == q.x - q.y );    }    bool operator!=( Queen const& q ) const { return !( *this == q ); }};void placeQueens( int N ){    Stack<Queen> solu;    Queen q( 0, 0 );    do    {        if ( N <= solu.size() || N <= q.y )        {	// 如果该行没有位置可以放Queen，就返回上一行，对上一行的Queen进行列增加            q = solu.pop();            q.y++;        }        else        {            while( ( q.y < N ) && ( 0 <= solu.find( q ) ) )            {	// 遍历每列，找到与前面不相同的Queen                q.y++;                nCheck++;            }            if( N > q.y )            {	// 开始进入下一行                solu.push( q );                if( N <= solu,size )                    nSolu++;                q.x++;                q.y = 0;            }        }    } while( ( 0 < q.x ) || ( q.y < N ) );}
```

### 迷宫算法

```c++
typedef enum { AVAILABLE, ROUTE, BACKTRACKED, WALL } Status;typedef enum { UNKNOWN, EAST, SOUTH, WEST, NORTH, NO_WAY } ESWN;inline ESWN nextESWN( ESWN eswn ) { return ESWN( eswn + 1 ); }struct Cell{    int x, y;    Status status;    ESWN incoming, outgoing;};#define LABY_MAX 24Cell laby[LABY_MAX][LABY_MAX];inline Cell* neighbor( Cell* cell ){    switch( cell-> outgoing )    {        case EAST : return cell + LABY_MAX;        case SOUTH: return cell + 1;        case WEST: return cell - LABY_MAX;        case NORTH: return cell - 1;        default:            exit(-1);    }}inline Cell* advance( Cell* cell ){    Cell* next;    switch( cel-> outgoing )    {        case EAST:            next = cell + LABY_MAX;            next->incoming = WEST;            break;        case SOUTH:            next = cell + 1;            next->incoming = NORTH;            break;        case WEST:            next = cell - LABY_MAX;            next->incoming = ESAT;            break;        case NORTH:            next = cell - 1;            next->incoming = SOUTH;            break;        default:            exit(-1);    }    return next;}bool labyrinth( Cell Laby[LABY_MAX][LABY_MAX], Cell* s, Cell* t){    if( ( AVAILABLE != s->status ) || ( AVAILABLE != t->status ) ) return false;    Stack<Cell*> path;    s->incoming = UNKNOWN;    s->status = ROUTE;    path.push( s );    do    {        Cell* c = path.top();        if( c == t ) return true;                while( NO_WAY > ( c->outgoing = nextESWN( c->outgoing ) ) )		// 寻找出去的方向            if( AVAILABLE == neighbor(c)->status )                break;        if( NO_WAY <= c->outgoing )		// 该路口没有方向选择，进行回溯，将原来标记的status值为ROUTE改为BACKTRACKED        {            c->status = BACKTRACKED;            c = path.pop();        }        else        {	// 将下一个可利用的点添加到path，并标记为路径            path.push( c = advance( c ) );            c->outgoing = UNKNOWN;            c->status = ROUTE;        }    } while( !path.empty() );    return false;}
```



## 二叉树

```c++
// 二叉树的遍历// 先序遍历（递归版）// 先序遍历（迭代版）// 中序遍历（递归版）// 中序遍历（迭代版）template<typename T, typename VST> void travIn_I2( BinNodePosi(T) x, VST& visit ){    Stack<BinNodePosi(T)> S;    while(true)    {        if(x)        {            S.push(x);            x = x->lc;        }        else if(!s.siEmpty())        {               x = S.pop();        	visit(x);            x = x->rc;        }        else            break;    }}// 后序遍历（递归版）// 后序遍历（迭代版）
```



### Huffman编码

```c++
// PFC编码树 #include "../BinTree/BinTree.h";typedef BinTree<char> PFCTree;#include "../Vector/Vector.h"typedef Vector<PFCTree*> PFCForest;#include "../Bitmap/Bitmap.h"		// 练习2-34的代码#include "../Skiplist/Skiplist.h"	// 引入Skiplist式词典结构实现typedef Skiplist<char, char*> PFCTable;	// PFC编码表，词条格式为：（key = 字符， value = 编码串）#define N_CHAR (0x80 - 0x20)		// 只考虑可打印字符int main(int argc, char* argv[]){    PFCForest* forest = initForest();    PFCTree* tree = generateTree(forest);    release(forest);    PFCTable* table = generateTable(tree);    for( int i = 1; i < argc; i++)    {        Bitmap codeString;        int n = ecode( table, codeString, argc[i] );	// 根据编码表生成（长度为n）        decode(tree, codeString, n);					// 利用编码树，对长度为n的二进制编码串解码（直接输出）    }    release(table);    release(tree);    return 0;}PFCForest* initForest(){    PFCForest* forest = new PFCForest;    for ( int i = 0; i < N_CHAR; i++ )    {        forest.insert(i, new BinTree());        (*forest)[i]->insertAsRoot( 0x20 + i );    }    return forest;}PFCTree* generateTree( PFCForest* forest ){    srand((unsigned int) time(NULL));    while( 1 < forest->size() )    {        PFCTree* s = new PFCTree;        s->insertAsRoot('^');        Rank r1 = rand() % forest->size();        s->attachAsLC(s->root(), (*forest)[r1]);        forest->remove(r1);        Rank r2 = rand() % forest->size();        s->attachAsRC(s->root(), (*forest)[r2]);        forest->remove(r2);        forest->insert(forest->size(), s);    }    return (*forest)[0];	// 至此forest中只存在一棵树，即全局编码树}// 通过遍历获取各个字符编码void generateCT(Bitmap* code, int length, PFCTable* table, BinNodePosi(char) v){    if(IsLeaf(*v))    {        table->put(v->data, code->bits2string(length));        return;    }    if(HasChild(*v))    {        code->clear(length);        generateCT(code, length + 1, table, v->lc);    }    if( HasRChild(*v) )    {        code->set(length);        generateCT(code, length + 1, table, v->rc);    }}// 构造编码表PFCTable* generateTable( PFCTree* tree ){    PFCTable* table = new PFCTable;    Bitmap* code = new Bitmap;    generateCT( code, 0, table, tree->root() );    release(code);    return table;}int encode( PFCTable* table, Bitmap& codeString, char* s ){    int n = 0;    for( size_t m = strlen(s), i = 0; i < m; i++ )    {        char** pCharCode = table->get(s[i]);        if(!pCharCode)            pCharCode = table->get(s[i] + 'A' - 'a');        if(!pCharCode)            pCharCode = table->get( ' ' );        printf( "%s", *pCharCode );			// 输出当前字符的编码        for( size_t m = strlen(*pCharCode), j = 0; j < m; j++ )            '1' == *(*pCharCode + j) ? codeString.set(n++) : codeString.clear(n++);    }    return n;}void decode( PFCTree* tree, Bitmap& code, int n ){    BinNodePosi(char) x = tree->root();    for( int i = 0; i < n; i++ )    {        x = code.test(i) ? x->rc : x->lc;        if(IsLeaf(*x))        {            printf("%c", x->data);            x = tree->root();        }    }}
```

```c++
// huffman编码树#define N_CHAR (0x80 - 0x20);struct HuffChar{    char ch;    int weight;    HuffChar(char c = '^', int w = 0) : ch(c), weight(w) { };    bool operator<(HuffChar const& hc )    {        return weight > hc.weight;	// 故意大小颠倒    }    bool operator==(HuffChar const& hc )    {        return weight == hc.weight;    }}#define HuffTree BinTree<HuffChar>#include "../List/List.h";typedef List<HuffTree*> HuffForest;#include "../Bitmap/Bitmap.h"typedef Bitmap HuffCode;#include "../Hashtable/Hashtable.h";typedef Hashtable<char, char*> HuffTable;int main(int argc, char* argv ){    int* freq = statistics(argv[1]);    Hufforest* forest = initForest(freq);    release(freq);    HuffTree* tree = generateTree(forest);    release(forest);    HuffTable* table = generateTable(tree);    for( int i = 2; i < argc; i++ )    {        Bitmap* codeString = new Bitmap;        int n = encode(table, codeString, argv[i]);        decode(tree, codeString, n);        release(codeString);    }    release(table);    release(tree);    return 0;}int* statistics(char* sample_text_file){    int* freq = new int[N_CHAR];    memset(freq, 0, sizeof(int)*N_CHAR);    FILE* fp = fopen(sample_text_file, "r");    for( char ch; 0 < fscanf(fp, "%c", &ch); )        if(ch >= 0x20)            freq[ch-0x20]++;    fclose(fp);    return freq;}HuffForest* initForest(int* freq){    HuffForest* forest = new HuffForest;    for( int i = 0; i < N_CHAR; i++ )    {        forest->insert(i, new HuffTree);        forest->last()->data->insertAsRoot(HuffChar(0x20+i, freq[i]));    }    return forest;}HuffTree* minHChar( HuffForest* forest ){    // ListNodePosi(HuffTree*) p = forest->first();    // ListNodePosi(HuffTree*) minChar = p;    // 上面是源码，增加的ListNodePosi是没用的，多加的？记得去视频课上查看    (HuffTree*) p = forest->first();    (HuffTree*) minChar = p;    int minWeight = p->data->root()->data.weight;    while(forest->valid(p = p->succ))        if(minWeight > p->data->root()->data.weight)        {            minWeight = p->data->root()->data.weight;            minChar = p;        }    return forest->remove(minChar);}HuffTree* generateTree(HuffForest* forest){    while(1 < forest->size())    {        HuffTree* T1 = minChar(forest);        HuffTree* T2 = minCHar(forest);        HuffTree* S = new HuffTree();        S->insertAsRoot(HuffChar('^', T1->root->data.weight + T2->root->data.weight));        S->attachAsLC(S->root(), T1);        S->attachAsRC(S->root(), T2);        forest->insertAsLast(S);    }    return forest->first()->data;}static void generateCT(Bitmap* code, int length, huffTable* table, BinNodePosi(HuffChar) v){    if(IsLeaf(*v))    {        table->put(v->data.ch, code->bits2string(length));        return;    }    if(HasLChild(*v))    {        code->clear(length);        generateCT(code, length + 1, table, v->lc);    }    if(HasRChild(*v))    {        code->set(length);        generateCT(code, length + 1, table, v->rc);    }}HuffTable* generateTable(HuffTree* tree){    HuffTable* table = new HuffTable;    Bitmap* code = new Bitmap;    generateCT(code, 0, table, tree->root() );    release(code);    return table;}int encode(HuffTable* table, Bitmap* codeString, char* s){    int n = 0;    for(size_t m = strlen(s), i = 0; i < m; i++)    {        char** pCharCode = table->get(s[i]);        if(!pCharCode) pCharCode = table->get(s[i] + 'A' - 'a');        if(!pCharCode) pCHarCode = table->get(' ');        printf("%s", *pCharCode);        for(size_t m = strlen(*pCharCode), j = 0; j < m; j++)        {            '1' == *(*pCharCode+j) ? codeString->set(n++) : codeString->clear(n++);        }    }    printf("\n");    return n;}int decode(HuffTree* tree, Bitmap* code, int n){    BinNodePosi(HuffChar) x = tree->root();    for( int i = 0; i < n; i++)    {        x = code->test(i) ? x->rc : x->lc;        if(IsLeaf(*x))        {            printf("%c", x->data.ch);            x = tree->root();        }    }}
```



## 图

### 抽象数据类型

#### Graph模板类

```c++
typedef enum { UNDISCOVERD, DISCOVERED, VISITED } VStatus;				// 顶点状态typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType;	// 边在遍历树中所属的类型template <typename Tv, typename Te>									// 边在遍历树中所属的类型class Graph{		// 图Graph模板类private:	void reset()    {		// 所有顶点、边的辅助信息复位        for ( int i = 0; i < n; i++ )        {            status(i) = UNDISCOVERED;            dTime(i) = fRime(i) = -1;            parent(i) = -1;            priority(i) = INT_MAX;            for ( int j = 0; j < n; j++ )            {                if ( exists( i, j ) ) type(i, j) = UNDETERMINED;            }        }    }    void BFS( int, int& );						// （连通域）广度优先搜索算法    void DFS( int, int& );						// （连通域）深度优先搜索算法    void BCC( int, int&, Stack<int>& );			// （连通域）基于DFS的双连通分量分解算法    bool TSort(int, int&, Stack<Tv>* );			// （连通域）基于DFS的拓扑排序算法    template <typename PU> void PFS( int, PU );	// （连通域）优先级搜索框架}template <typename Tv, typename Te>void Graph<Tv, Te>::bfs( int s ){    reset();    int clock = 0;    int v = s;    do        if( UNDISCOVERED == status(v) )            BFS( v, clock);    while ( s != ( v = ( ++v % n ) ) );}template <typename Tv, typename Te>void Graph<Tv, Te>::BFS( int v, int* clock ){    Queue<int> Q;    status(v) = DISCOVERED;    Q.enqueue(v);    while( !Q.empty() )    {        int v = Q.dequeue();        dTime(v) = ++clock;        for ( int u = firstNbr(v); -1 < u; u = nextNbr(v, u) )        {            if( UNDISCOVERED == status(u) )            {                status(u) = DISCOVERED;                Q.enqueue(u);                type(v, u) = TREE;                parent(u) = v;            }            else            {                type(v, u) = CROSS;            }        }        status(v) = VISITED;    }}template<typename Tv, typename Te> void Graph<Tv, Te>::dfs(int s){    reset();    int v = s;    int clock = 0;    do    {        if(status(v) == UNDISCOVERED)            DFS(v, clock);    } while (s != (v = ++v % n))}template<typename Tv, typename Te> void Graph<Tv, Te>::DFS(int s, int& clock){    dTime(v) = ++clock;    status(v) = DISCOVERED;    for( int u = firstNbr(v); -1 < u; u = nextNbr(v, u) )    {        switch( status(u) )        {            case UNDISCOVERED:                status(v, u) = TREE;                parent(u) = v;                DFS(u, clock);                break;            case DISCOVERED:                status(v, u) = BACKWORD;                break;            default:                status(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;                break;        }    }    status(v) = VISITED;    fTime(v) = ++clock;}// 基于DFS的拓扑排序算法template<typename Tv, typename Te> Stack<Tv>* Graph<Tv, Te>::tSort(int s){    retset();    int clock = 0;    int v = s;    Stack<Tv>* S = new Stack<Tv>;    do    {        if (UNDISCOVERED == status(v) )            if ( !TSort(v, clock, S) )            {                while ( !S->empty() )                {                 	S->pop();                    break;				}            }    } while( s != ( v == ( ++v % n ) ) );    return S;}template <typename Tv, typename Te> bool Graph<Tv, Te>::TSort( int v, int& clock, Stack<Tv>* S ){    dTime(v) = ++clock;    status(v) = DISCOVERED;    for ( int u = firstNbr(v); u > -1; u = nextNbr(v, u) )    {        switch ( status(u) )        {            case UNDISCOVERED:                parent(u) = v;                type(v, u) = TREE;                if ( !TSort( u, clock, S ) )                    return false;                break;            case DISCOVERED:                type(v, u) = BACKWORD;                return false;            default:                type( v, u ) = ( dTime(v) < dTime(u) ) ? FORWARD : CROSS;                break;        }    }    status(v) = VISITED;    S->push(vectex(v));    return true;}template <typename Tv, typename Te> void Graph<Tv, Te>::bcc( int s ){    reset();    int clock = 0;    int v = s;    Stack<int> S;    do    {        if ( UNDISCOVERED == status(v) )        {            BCC( v, clock, S );            S.pop();        }    }    while ( s != ( v = ( ++v % n ) ) );}template <typename Tv, typename Te> void Graph<Tv, Te>::BCC( int v, int& clock, Stack<int>& S){    hca(v) = dTime(v) = ++clock;    status(v) = DISCOVERED;    S.push(v);    for ( int u = firstNbr(v); u > -1; u = nextNbr(v, u) )    {        switch( status(u) )        {            case UNDISCOVERED:                parent(u) = v;                type(u, v) = TREE;                BCC( u, clock, S);                if ( hca(u) , dTime(v) )                {                    hca(v) = min(hca(v), hca(u));                }                else                {                    while( v != S.pop());                    S.push(v);                }                break;            case DISCOVERED:                type(v, u) = BACKWARD;                if ( u != parent(v) )                    hca(v) = min(hca(v), dTime(u) );                break;            default:                type(v, u) = (dTime(v) < dTIme(u)) ? FORWARD : CROSS;                break;        }    }    status(v) = VISITED;}// 最短路径：通过使用广度遍历，类似于树的层次遍历，都是按照从最短距离到最长距离，一步步遍历下去template <typename Tv, typename Te> void Graph<Tv, Te>::bcc(int s){    reset();    int clock = 0;    int v = s;    Stack<int> s;    do        if ( UNDISCOVERED == status(v) )        {            BCC(v, clock, S);            S.pop();        }    while (s != ( v = (++v % n) ) );}#define hca(x) (fTime(x))	// 利用此处闲置的fTime[]充当hca[]template <typename Tv, typename Te> void Graph<Tv, Te>::BCC(int v, int& clock, Stack<int>& S){    hca(v) == dTime(v) = ++clock;    status(v) = DISCOVERED;    S.push(v);    for ( int u = firstNbr(v); -1 < u; u = nextNbr(v, u) )    {        switch( status(u) )        {            case UNDISCOVERED:                parent(u) = v;                type(v, u) = TREE;                BCC(u, clock, S);                if( hca(u) < dTime(v) )                    hca(v) = min( hca(v), hca(v) );                else                {                    while( v!= S.pop() );                    S.push(v);                }                break;            case DISCOVERED:                type(v, u) = BACKWARD;                if(u != parent(v))                    hca(v) = min(hca(v), dTime(u));                break;            default:                type(v, u) = (dTime(v) < dTime(u) ) ? FORWARD : CROSS;                break;        }    }    status(v) = VISITED;}template <typename Tv, typename Te> template <typename PU> void Graph<Tv, Te>::pfs( int s, PU prioUpdater ){    reset();    int v = s;    do        if (UNDISCOVERED == status(v))            PFS(v, prioUpdater);    while (s != (v == (++v % n)));}template<typename Tc, typename Te> template <typename PU> void Graph<Tv, Te>::PFS(int s, PU prioUpdater ){    priority(s) = 0;    status(s) = VISITED;    parent(s) = -1;    while(1)    {        for( int w = firstNbr(s); -1 < w; w = nextNbr(s, w))            prioUpdater( this, s, w );        for( int shortest = INT_MAX, w = 0; w < n; w++ )        {            if ( UNDISCOVERED == status(w) )                if( shortest > priority(w) )                {                    shortest = priority(w);                    s = w;                }        }        if( VISITED == status(s) )            break;        status(s) = VISITED;        type(parent(s), s) = TREE;    }}#undef hca// using PFS() to do prim algorithmtemplate <typename Tv, typename Te> struct PrimPU {    virtual void opeartor()( Graph<Tv, Te>* g, int uk, int v )    {        if ( UNDISCOVERED == g->status(v) )        {            if (g->priority(v) > g->weight(uk, v) )            {            	g->priority(v) = g->weight(uk, v);            	g->parent(v) = uk;            }        }    }};template <typename Tv, typename Te> struct DijkstraPU{    virtual void opeartor() (Graph<Tv, Te>* g, int uk, int v)    {        if( UNDISCOVERED == g->status(v) )            if (g->priority(v) > g->priority(uk) + g->weight(uk, v))            {                g->priority = g->priority(uk) + g->weight(uk, v);                g->parent(v) = uk;            }    }}
```

## 搜索树

```c++
#include "../BinTree/BinTree.h"template <typename T> class BST: public BinTree<T>{protected:    BinNodePosi(T) _hot;    BinNodePosi(T) connect34(BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));public:    virtual BinNodePosi(T) & search (const T& e);    virtual BinNodePosi(T) insert (const T& e);    virtual bool remove( const T& e );    };template <typename T> static BinNodePosi(T) & searchIn( BinNodePosi(T) & v, const T& e, BinNodePosi(T) & hot ){    if( !v || ( e == v->data ) )        return v;    hot = v;    return searchIn((( e < v->data ) ? v->lc : v->rc), e, hot);}template <typename T> BindNodePosi(T) & BST<T>::search( const T& e){    return searchIn(_root, e, _hot=NULL);}template <typename T> BindNodePosi(T) BST<T>::insert( const T& e ){    BindNodePosi(T) & x = search(e);    if (x)        return x;    x = new BinNode<T>(e, _hot);    _size++;    updateHightAbove(x);    return x;}template <typename T> bool BST<T>::remove( const T& e){    BinNodePosi(T) &x = search(e);    if (!x)        return false;    removeAr(x, _hot);    _size--;    updateHeightAbove(_hot);    return true;}template <typename T> static BindNodePosi(T) removeAt(BindNodePosi(T) & x, BindNodePosi(T) & hot){    BinNodePosi(T) w = x;    BinNodePosi(T) succ = NULL;    if( !HasLChild(*x) )        succ = x = x->rc;    else if ( !HasRChild(*x) )        succ = x= x->lc;;    else    {        w = w->succ();        swap( x->data, w->data );        BinNodePosi(T) u = w->parent;        (( u == x) ? u->rc : u->lc ) = succ = w->rc;    }    hot = w->parent;    if ( succ )        succ->parent = hot;    release( w->data );    release( w );    return succ;    }
```



```c++
#include "../BST/BST.h"#define Balanced(x) ( stature( (x).lc ) == stature( (x).rc ) )#define BalFac(x) ( stature( (X).lc ) - stature( (x).rc ) )#define AvlBalanced(x) ( ( -2 < BalFac(X) ) && ( BalFac(x) < 2 ) )template <typename T> class AVL : public BST<T>{public:    BinNodePosi(T) insert( const T& e );    bool remove( const T& e);};#define tallerChild(x) ( \     stature( (x)->lc ) > stature( (x)->rc ) ? (x)->lc : ( \     stature( (x)->lc ) < stature( (x)->rc ) ? (x)->rc : ( \     IsLChild( *(x) ) ? (x)->lc : (x)->rc \                                                        ) \                                                        ) \)template <typename T> BinNodePosi(T) AVL<T>::insert( const T& e )    {        BinNodePosi(T) & x = search(e);        if(x)            return x;        BinNodePosi(T) xx = x = new BinNode<T>( e, _hot );        _size++;        for ( BinNodePosi(T) g = _hot; g; g = g->parent )        {            if ( !AvlBalanced(*g))            {                FromParentTo(*g) = rotateAt( tallerChild( tallerChild(g) ) );                break;            }            else                updateHeight(g);		}        return xx;    }template <typename T> bool AVL<T>::remove( const T& e ){    BinNodePosi(T) & x = search(e);    if( !x )        return false;    removeAt( x, _hot );    _size--;    for ( BinNodedPosi(T) g = _hot; g; g = g->parent )    {        if (!AvlBalanced( *g ) )            g = FromParentTo( *g ) = rotateAt( tallerChild( tallerChild( g ) ) );        updateHeight( g );     }    return true;}// 平衡树“3+4”操作template <typename T> BinNodePosi(T) BST<T>::connect34 (	BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,	BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3){    a->lc = T0;    T0->parent = a;    a->rc = T1;    T1->parent = T1;    updateHeight(a);    b->lc = a;    a->parent = b;    b->rc = c;    c->parent = b;    c->lc = T2;    T2->parent = c;    c->rc = T3;    T3->parent = c;    updateHeight(c);    updateHeight(b);    return b;    }// BST节点旋转变换统一算法（3节点 + 4子树），返回调整之后局部子树根节点的位置template <typename T> BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v){    BinNodePosi(T) p = v->parent;    BinNodePosi(T) g = p->parent;    if (IsLChild(*p))    {        if (IsLChild(*v))        {        	p->parent = g->parent;               return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);        }        else        {            v->parent = g->parent;            return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);        }    }	    else    {        if (ISLChild(*v))        {            v->parent = g->parent;            return conenct34(g, v, p, g->lc, v->lc, v->rc, p->rc);        }        else        {            p->parent = g->parent;            return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);        }    }}
```

## 高级搜索树

**数据局部性**包含以下两个方面：

1. 刚刚被访问的元素，极有可能在不久后的将来被再次访问
2. 被访问的元素，极有可能在不久之前被访问的某个元素附近。

### 伸展树

```c++
#include "../BST/BST.h"	// 基于BST实现Splaytemplate <typename T> class Splay : public BST<T>{protected:    BinNodePosi(T) splay(BinNodePosi(T) v);public:    BinNodePosi(T) & search(const T& e);	 // 查找    BinNodePosi(T) insert(const T& e);		 // 插入    bool remove(const T& e);				// 删除};// 在节点*p与*lc（可能为空）之间父（左）子关系template <typename NodePosi> inline void attachAsLChild( NodePosi p, NodePosi lc){    p->lc = lc;    if (lc)        lc->parent = p;}// 在节点*p与*rc（可能为空）之间建立父（右）子关系template <typename NodePosi> inline void attachAsRChild( NodePosi p, NodePosi rc){    p->rc = rc;    if (rc)    {        rc->parent = p;    }}// Splay树伸展算法：从节点v出发逐层伸展template <typename T> BinNodePosi(T) splay(BinNodePosi(T) v){    if (!v)        return;    BinNodePosi(T) p;    BinNodePosi(T) g;    while ((p = v->parent) && (g = p->parent))    {        BinNodePosi(T) gg = g->parent;        if(IsLChild(*v))        {            if(IsLChild(*p))            {                attachAsLChild(g, p->rc);                attachAsLChild(p, v->rc);                attachAsRChild(p, g);                attachAsRChild(v, p);            }            else            {                attachAsLChild(g, v->rc);                attachAsLChild(v, g);                attachAsRChild(p, v->lc);                attachAsLChild(v, p);            }        }        else        {            if(IsRChild(*v))            {                attachAsRChild(g, p->lc);                attachAsRChild(p, v->lc);                attachAsLChild(v, p);                attachAsLChild(p, g);            }            else            {             	attachAsRChild(g, v->lc);                attachAsLChild(p, v->rc);                attachAsLChild(v, g);                attachAsRChild(v, p);            }        }        if (!gg)            v->parent = NULL;        else        {            ( g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);        }        updateHeight(g);        updateHeight(p);        updateHeight(v);    }    if (p = v->parent)    {        if (IsLChild(*v))        {            attachAsLChild(p, v->lc);            attachAsRChild(v, p);        }        else        {            attachAsRChild(p, v->lc);            attachAsLChild(v, p);        }        updateHeight(p);        updateHeight(v);    }    v->parent = NULL;    return v;}template <typename T> BinNodePosi(T) & Splay<T>::search(const T& e){    BinNodePosi(T) p = searchIn( _root, e, _hot=NULL);    _root = splay(p ? p : _hot);	// 将最后一个访问的节点伸展至于根    return _root;}// 将元素e插入伸展树中template <typename T> BinNodePosi(T) Splay<T>::insert(const T& e){    if (!_root )    {        _size++;        return _root = new BinNode<T>(e);    }    if (e == search(e)->data)        return _root;    _size++;    BinNodePosi(T) t = _root;    if (_root->data < e)    {        t->parent = _root = new BinNode<T>(e, NULL, t, t->rc);        if (HasRChild(*t))        {            t->rc->parent = _root;            t->rc = NULL;        }    }    else     {        t->parent = _root = newBinnode<T>(e, NULL, t->lc, t);        if (HasLChild(*t))        {            t->lc->parent = _root;            t->lc = NULL;        }    }    updateHeightAbove(t);    return _root;}template <typename T> bool Splay<T>::remove( const T& e){    if (!_root || (e != search(e)->data))        return false;    BinNodePosi(T) w = _root;    if (!HasLChild(*_root))    {        _root = _root->rc;        if (_root)            _root->parent = NULL;    }    else if (!HasRChild(*_root))    {        _root = _root->lc;        if (_root)            _root->parent = NULL;    }    else    {        BinNodePosi(T) lTree = _root->lc;        lTree->parent = NULL;        _root->lc = NULL;        _root = _root->rc;        _root->parent = NULL;        search(w->data);        _root->lc = lTree;        lTree->parent = _root;    }    release(w->data);    release(w);    _size--;    if(_root)        updateHeight(_root);    return true;}
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

template <typename T> void solveDoubleRed(binNodePosi(T) x)
{
    if (IsRoot(*x))
    {
        _root->color = RB_BLACK;
        _root->height++;
    }
    BiNodePosi(T) p = x->parent;
    if(IsBlack(p))
        return;
    BinNodePosi(T) g = p->parent;
    BinNdoePosi(T) u = uncle(x);
    if (IsBlack(u))
    {
        if (IsLChild(x) == IsLChild(p))
            p->color = RB_BLACK;
        else
            x->color = RB_BLACK;
        g->color = RB_RED;
        BinNodePosi(T) gg = g->parent;	// 曾祖父
        BinNodePosi(T) r = FromParentTo(*g) = rotateAt(x);	// 调整后的子树根结点
        r->parent = gg;
    } else
    {
        p->color = RB_BLACK;
        p->height++;
        u->color = RB_BLACK;
        u->height++;
        if(!IsRoot(*g))
            g->color = RB_RED;
        solveDoubleRed(g);
    }
}

template <typename T> void sloveDoubleBlack(BinNodePosi(T) r)
{
    BinNodePosi(T) p = r ? r->parent : _hot;	  		// r的父亲
    if (!p)
        return;
    BinNodePosi(T) s = (r == p->lc) ? p->rc : p->lc;	// r的兄弟 
    if (IsBlack(s))
    {
        BinNodePosi(T) t = NULL;
        if (IsRed(s->rc)) t = s->rc;
        if (IsRed(s->lc)) t = s->lc;
        if (t)
        {
            RBColor oldColor = p->color;
            BinNodePosi(T) b = FromParentTo(*p) = rotateAt(t);
            if (HasLChild(*b))
            {
                b->lc->color = RB_BLACK;
                updateHeight( b->lc );
            }
            if (HasRChild(*b))
            {
                b->rc->color = RB_BLACK;
                updateHeight( b->rc );
            }
            b->color = oldColor;
            updateHeight( b );
        }
        else
        {
            s->color = RB_RED;
            s->height--;
            if (IsRed(p))  //BB-2R
            {
                p->color = RB_BLACK;
            }
            else // BB-2B
            {
                p->height--;
                solveDoubleBlack(p);
            }
        }
    }
    else
    {
        s->color = RB_BLACK;
        p->color = RB_RED;
        BinNodePosi(T) t = ISLChild(*s) ? s->lc : s->rc;
        _hot = p;
        FromParentTo(*p) = rotateAt(t);
        solveDoubleBlack(r);
    }
}

template <typename T> BinNodePosi(T) insert(const T& e)
{
    BinNodePosi<T> & x = search(e);
    if(x)
        return x;
    x = new BinNode<T> (e, _hot, NULL, NULL, -1);
    _size++;
    solveDoubleRed(x);
    return x ? x : _hot->parent;
}

template <typename T> bool remove(const T& e)
{
    BinNodePosi(T)& x = search(e);
    if( !x )
        return false;
    BinNodePosi(T) r = removeAt(x, _hot);	// 如果删除节点的左或右子树不存在，那么返回的是被删除节点的孩子
    									// 如果删除的节点的左右孩子存在，那么返回的是被删除节点准备删除之前的后继节点的后后继节点（所以可能为空）。
    if( !(--_size))
        return true;
    if ( !_hot )	// 如果是根节点被删除，那么就是说明该树是无法同时拥有左右子树的。
    {
        _roor->color = RB_BLACK;
        updateHeight(_root);
        return true;
    }
    if (IsRed(r))
    {
        r->color = RB_BLACK;
    	r->height++;
        return true;
    }
    solveDoubleBlack(r);
    return true;
    
}
```

### kd-树

```c++
KdTree* buildKdTree(P, d)
{
    if (P == {p})
        createLeaf(p); 			// 构造递归基
    root = CreateKdNode();		// 创建（子）树根
    root->splitDirection = Even(d) ? VERTICAL : HORIZONTAL;		// 确定划分方向
    root->splitLine = FindMedian(root->splitDirection, P);		// 确定中位点
	(P1, P2) = Divide(O, root->splitDirection, root->splitLine);// 子集划分
    root->lc = buildKdTree(P1, d + 1);						  // 在深度为d+1的层次，递归构造左子树
    root->rc = buildKdTree(P2, d + 1);						  // 在深度为d+1的层次，递归构造右子树
    return root;
}

KdSearch(v, R)
{
    if (isLeaf(v))		// 若抵达叶节点，直接输出
    {
        if(inside(v, R))
            report(v);
        return;
    }
    
    if(region(v->lc) 属于 R)
        reportSubtree(v->lc);
    else if (region(v->lc) 相交于 R 不为空)
        KdSearch(v->lc, R);
    
    if (region(v->rc) 属于 R)
        reportSubtree(v->rc);
    else if (region(v->rc) 相交于 R 不为空)
        KdSearch（v->rc, R);
    
}

```

## 词典

```c++
// 定义词典的操作接口
template <typename K, typename V> struct Dictionary
{
    virtual int size() const = 0;		// 当前词条总数
    virtual bool put(K, V) = 0;			// 插入词条（禁止雷同词条时可能失效）
    virtual V* get(K k) = 0;			// 读取词条
    virtual bool remove(K k) = 0;		// 删除词条
};


```



### 跳转表

```c++
#include "../List/List.h"		// 引入列表
#include "../Entry/Entry.h"		// 引入词条
#include "Quadlist.h"			// 引入Quadlist
#include "../Dictionary/Dictionary.h"	// 引入词典

template <typename K, typename V>
class Skiplist : public Dictionary<K, V>, public List<Quadlist<Entry<K, V>>*>
{
protected:
    bool skipSearch
    (
        ListNode<Quadlist<Entry<K, V>>*>* &qlist,
        QuadListNode<Entry<K, V>>* &p,
        K& k
    );
    
public:
    int size() const
    {
        return empty() ? 0 : last()->data->size();		// 底层Quadlist的规模
    }
    int level() { return List::size(); }			   // 层高 == #Quadlist，不一定开放
    bool put(K, V);									 // 插入（注意与Map）
    V* get(K k);									// 读取
    bool remove(K k);								// 删除
};

template <typename K, typename V> V* Skiplist<K, V>::get(K k)	// 跳转表词条查找方法
{
    if (empty())
        return NULL;
    ListNode<Quadlist<Entry<K, V>>*>* qlist = first();		// 从顶层Quadlist的
    QuadlistNode<Entry<K, V>>* p = qlist->data->first();	// 首节点开始
    return skipSearch( qlist, p, k) ? & ( p->entry.value ) : NULL;	// 查找并报告
}	// 有多个命中时靠后者优先，靠后是是指纵列的最上层

template <typename K, typename V> bool skiplist<K, V>::skipSearch( ListNode<Quadlist<Entry<K, V>>*>* &qlist, QuadlistNode<Entry<K, V>>* &p, K& k)	// 从指定层qlist的首节点p出发
{		// 向右、向下查找目标关键码k
    while(true)	// 在每一层
    {
        while( p->succ && (p->entry.key <= k))	// 从前向后查找
            p = p->succ;	// 直到出现更大的key或溢出至trailer
        p = p->pred;		// 此时倒回一步
        if ( p->pred && (k == p->entry.key))
            return true;
        qlist = qlist->succ;	// 否则转入下一层
        if (!qlist->succ)
            return false;		// 若已到穿透底层，则意味着失败
        p = ( p->pred ) ? p->below : qlist->data->first();	// 否则转至当前塔的下一节点
    }
    
}

// 跳转词表插入算法
template <typename K, typename V>
bool Skiplist<K, V>::put(K k, V v)
{
    Entry<K, V> entry = Entry<K, V>(k, v);	// 待插入的词条（将被随机地插入多个副本）
    if (empty())
        inseryAsFirst(new Qualist<Entry<K, V>>);	// 插入首个Entry
    ListNode<Quadlist<Entry<K, V>>*>* qlist = first();	// 得到顶层
    QuadlistNode<Entry<K, V>>* p = qlist->data->first();	// 从顶层四联表的首节点出发
    if (skipSearch(qlist, p, k))	// 找到P的键是不大于k的
        while (p->below) p = p->below();	//如果有雷同的词条，强制转到塔底
    qlist = last();		//  因为p已经在底层了，所以qlist也应该在底层
    QuadlistNode<Entry<K,V>>* b = qlist->data->insertAfterAbove(e, p);	//新节点b即新塔基座
    while (rand() & 1)	// 通过随机确定新塔是否需要再长高一层
    {
        while( qlist->data->valid(p) && !p->above)
            p = p->pred;	// 找出不低于此高度的最近前驱
        if (!qlist->data->valid(p))		// p的前驱是header
        {
            if (qlist == first())	//当前高度就是最高的高度
            {
                insertAsFirst(new Quadlist<Entry<K, V>>);	//创建新的一层
            }
            p = qlist->pred->data->first()->pred();			// 将p转至上一层Skiplist的header
        }
        else
        {
            p = p->above;
        }
        qlist = qlist->pred;		//上升一层
        b = qlist->data->insertAfterAbove(e, p, b);		// 将新节点插在p之后，b之上
    }
    return true;		// Dictionary允许重复元素，故插入必成功，与hashTable等Map略有差异
}


template <typename T>
QlistNodePosi(T) Skiplist<T>::remove(K k)
{
    if (empty())		// 空表情况
        return false;
    ListNode<Quadlist<Entry<K, V>>*>* qlist = first();		// 从顶层Quadlist开始
    QuadlistNode<Entry<K, V>>* p = qlist->data->first();	// 首节点开始
    if (!skipSearch(qlist, p, k))
        return false;		// 目标词条不存在，直接返回
    do {	// 若目标词条存在，则逐层拆除与之对应的塔
        QuadlsitNode<Entry<K, V>>* lower = p->below();		// 记住下一层节点
        qlist->data->remove(p);							  // 删除当前节点
        p = lower;
        qlist = qlist->succ;							  // 转入下一层
    } while( qlist->succ);		// 不断重复，直到塔基
    while (!empty() && first()->data->empty())				// 逐一地
        List::remove(first());		// 清除已可能不含词条的顶层Quadlist
    return true;		// 删除操作成功完成
}
```

#### 四联表

```c++
#include "QuadlistNode.h"		// 引入Quadlist节点类
template <typename T> class Quadlist	// Quadlist模板类，单层
{
private:
    int _size;		// 规模
    QlistNodePosi(T) header;		// 头哨兵
    QlistNodePosi(T) trailer;		// 尾哨兵
protected:
    void init();		// Quadlist创建时的初始化
    int clear();		// 清除所有节点
    
public:
    Quadlist() { init(); }		// 默认
    ~Quadlist() { clear(); delete header; delete trailer; }		// 删除所有节点，释放哨兵
    Rank size() const { return _size; }		// 规模
    bool empty() const { return _size <= 0; }		// 判空
    QlistNodePosi(T) first() const { return header->succ; }		// 首节点位置
    QlistNodePosi(T) last() const { return trailer->pred; }		// 末节点位置
    bool valid( QlistNodePosi(T) p );		// 判断位置p是否合法
    { return p &&  ( trailer != p ) && ( header != p ); }
    // 可写访问接口
    T remove { QlistNodePosi(T) p };		// 删除（合法）位置p处的节点，返回被删除节点的数值
    QlistNodePosi(T)  // 将*e作为p的后继、b的上邻插入
    insertAfetrAbove(T const& e, QlistNodePosi(T) p, QlistNodePosi(T) b = NULL);
    // 遍历
    void traverse (void (*)(T&));			// 遍历各节点，依次实施指定操作（函数指针，只读或局部修改）
    template <typename VST>					// 操作器
    void traverse( VST& );					// 遍历各节点，依次实施指定操作（函数对象，可全局性修改节点）
};

template <typename T> void Quadlist<T>::init()	// Quadlist初始化，创建Quad
{
    header = new QuadlistNode<T>;		// 创建头哨兵节点
    trailer = new QuadlistNode<T>;		// 创建为哨兵节点
    header->succ = trailer; header->pred = NULL;	// 沿横向联接哨兵
    trailer->pred = header; tailer->succ = NULL;	// 沿横向联接哨兵
    header->above = trailer->above = NULL;			// 纵向的后继置空
    header->below = trailer->below = NULL;			// 纵向的前驱置空
    _size = 0;	//记录规模
}

template <typename T>
QlistNodePosi(T) Quadlist<T>::insertAfterAbove( T const& e, QlistNodePosi(T) p, QlistNodePosi(T) b = NULL )		// 将e作为p的后继，b的上邻插入Quadlist
{
    _size++;
    return p->insertAsSuccAbove(e, b);	// 返回新节点的位置（below = NULL）
}

template <typename T>		// 删除Quadlist内位置p处的节点，返回其中存放的词条
T Quadlist<T>::remove (QlistNodePosi(T) p)		// assert:: p为Quadlist中的合法位置
{
    p->pred->succ = p->succ; p->succ->pred = p->pred; _size--;	// 摘除节点
    T e = p->entry;
    delete p;	// 备份词条删除节点
    return e;
}

template <typename T>
int Quadlist<T>::clear()
{
    int oldSize = _size;
    while (0 < _size)
        remove(header->succ);	// 逐个删除所有节点
    return oldSize;
}
```

#### 四联表节点

```c++
#include "../Entry/Entry.h"
#define QlistNodePosi(T) QuadlistNode<T>*	// 跳转表节点位置

template <typename T> struct QuadlistNode
{
    T entry;		// 所存词条
    QlistNodePosi(T) pred;	QlistNodePosi(T) succ;		// 前驱、后继
    QlistNodePosi(T) above;	QlistNodePosi(T) below;		// 上邻、下邻
    QuadlistNode
    (
        T e = T(), 
        QlistNodePosi(T) p = NULL, 
        QListNodePosi(T) s = NULL,
        QlistNodePosi(T) a = NULL,
        QlistNodePosi(T) b = NULL
    ) : entry (e), pred(p), succ(s), above(a), below(b) { }
    QlistNodePosi(T) insertAsSuccAbove	// 插入新节点，以当前节点为前缀，以节点b为下邻
        ( T const& e, QlistNodePosi(T) b = NULL );
};

template <typename T>
QlistNodePosi(T) Quadlist<T>::insertAfterAbove(T const& e, QlistNodePosi(T) = b = NULL)
{
    QlistNodePosi(T) x = new QuadlistNode<T> (e, this, succ, NULL, b);		// 创建新节点
    succ->pred = x;
    succ = x;				// 设置水平逆向链接
    if (b)
        b->above = x;		// 设置垂直逆向连接
    return x;			    // 返回新节点的位置 
}
 
```

### 散列表

```c++
#include "../Dictionary/Dictionary.h"	// 引入词典ADT
#include "../Bitmap/bitmap.h"		// 引入位图

template <typename K, typename V> // Key, value
class Hashtable: public Dictionary<K, V>
{
    // 符合Dictionary接口的Hashtable模板类
private:
    Entry<K, V>** ht;	// 桶数组，存放词条指针
    int M;	// 桶数组容量
    int N;	// 词条数量
    Bitmap* lazyRemoval;	// 懒惰删除标记
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))
protected:
    int probe4Hit( const K& k);		// 沿关键码K对应的查找链，找到词条匹配的桶
    int probe4Free( const K& k);	// 沿关键码k对应的查找链，找到首个可用空桶
    void rehash();				   // 重散列算法：扩充桶数组，保证装填因子在警戒线以下
public:
    Hashtable(int c = 5);		// 创建一个容量不小于c的散列表（为测试暂时选用较小的默认值）
    ~Hashtable();			   // 释放桶数组及其中各（非空）元素所指向的词条
    int size() const { return N; }	// 当前的词条数目
    bool put(K, V);				   // 插入（禁止雷同词条，故可能失败）
    V* get(K k);				   // 读取
    bool remove(K k);			   // 删除
};


template <typename K, typename V> Hashtabe<K, V>::Hashtable( int c )	// 创建散列表，容量为不小于c的素数M
{
    M = primeNLT( c, 1048576, "../../_input/prime-1048576-bitmap.txt");		// 不小于c的素数M
    N = 0; ht = new Entry<K, V>*[M];		// 开辟桶数组（还需申请核对成功），初始装填因子为N/M = 0%
    memset( ht, 0, sizeof(Entry<K, V>* ) *M);	// 初始化各桶
    lazyRemoval = new Bitmap(M);		// 懒惰删除标记比特图
}

int primeNLP(int c, int n, char* file)	// 根据file文件中的记录，在[c, n)内取最小的素数
{
    Bitmap B(file, n);		// file已经按位图格式，记录了n以内的所有素数，因此只要
    while (c < n)	// 从c开始，逐位地
    {
        if (B.test(c))
            c++;	// 测试即可
        else
            return c;	// 返回收个发现的素数
    }
    return c;	// 若没有这样的素数，返回n（实用中不能如此简化处理）
}

template <typename K, typename V> Hashtable<K, V>::~Hashtable()	//析构前释放桶数组及非空词条
{
    for ( int i = 0; i < M; i++)	// 逐一检查各桶
        if (ht[i])
            release(ht[i]);	// 释放非空的桶
    release(ht);	// 释放桶数组
    release(lazyRemoval);	// 释放懒惰删除标记
} // release()负责释放负责结构，与算法无直接关系，详见代码包

template <typename K, typename V>
V* Hashtable::get(K k)	// 散列表词条查找算法
{
    int r = probe4Hit(k);
    return ht[r] ? & (ht[r]->value) : NULL;	// 禁止词条的key值雷同
}

template <typename K, typename V> int Hashtable<K, V>::probe4Hit(const K& k)
{
    int r = hashCode(k) % M;	// 从起始桶（按除余确定）出发
    while( (ht[r] && (k != ht[r]->key)) || ( !ht[r] && lazilyRemoved(r)))
    {
        r = (r+1) % M;	// 沿查找链线性试探：跳过所有冲突的桶，以及带懒惰删除标记的桶
    }
    return r;		// 调用者根据ht[r]是否为空，即可判断查找是否成功。
}

template <typename K, typename V>
bool Hashtable<K, V>::remove(K k)	// 散列表词条删除算法
{
    int r = prob4Hit(k);
    if (!ht[r])
        return false;	// 对应词条不存在时，无法删除
    release(ht[r]);		// 释放桶中词条
    ht[r] = NULL;
    maskAsRemoved(r);	// 设置懒惰删除标记
    N--;			   // 更新词条总数
    return true;
}

template <typename K, typename V>
bool Hashtable<K, V>::put(K k, V v)		// 散列表词条插入
{
    if (hr[probe4Hit(k)])
        return false;	// 雷同元素不必重复插入
    int r = probe4Free(k);	// 为新的词条找个空桶（只要装填因子控制得当，必然成功）
    ht[r] = new Entry<K, V>(k, v);
    ++N;	// 插入（注意：懒惰删除标记位无需复位）
    if (N * 2 > M)
        rehash();		// 装填因子高于50%后重散列
    return true;
}

template <typename K, typename V>
int Hashtable<K, V>::probe4Free(const K& k)
{
    int r = hashCode(k) % M;	//从起始桶（按除余法确定）出发
    while (ht[r])
        r = (r+1) % M;	// 沿查找链桶试探，直到首个空桶（无论是否带有懒惰删除标记）
    return r;		// 为保证空桶总能找到，装填因子及散列表需要合理设置
}

template <typename K, typename V>
void Hashtable<K, V>::rehash()
{
    int old_capacity = M;
    Entry<K, V>** old_ht = ht;
    M = primeMLT( 2 * M, 1048576, "../../_input/prime-1048576-bitmap.txt");	// 容量至少加倍
    N = 0;
    ht = new Entry<K, V>*[M];
    memset(ht, 0, sizeof(Entry<K, V>*)*M);	// 新桶数组
    release(lazyRemoval);
    lazyRemoval = new Bitmap(M);	// 新开懒惰删除标记比特图
    for (int i = 0; i < old_capicity; i++)	// 扫描原桶数组
    {
        if (old_ht[i])	// 将空桶中的词条逐一
            put(old_ht[i]->key, old_ht[i]->value);	// 插入至新的桶数组
    }
    release(old_ht);		// 释放原桶数组---由于其中原先存放的词条均转移，故只需释放桶数组本身
}
```



```c++
// hashCode()的实现
static size_t hashCode(char c)
{
    return (size_t) c;	// 字符
}

static size_t hashCode(int k)
{
    return (size_t) k;	// 整数
}

static size_t hashCode(long long  l)
{
    return (size_t) ((i >> 32) + (int)i);	// 长长整数
}

static size_t hashCode(char s[])	// 生成字符串的循环位移散列码
{
    int h = 0;	//散列码
    for (size_t n = strlen(s), i = 0; i < n; i++)
    {
        h = (h << 5) | (h >> 27);		//自左向右，逐个处理每一字符
        h += (int)s[i];		// 散列码循环左移5位，再累加当前字符
    }
    return (size_t) h;	// 如此所的的散列码，可以理解为“多项式散列码”
} // 对于英语单词，“循环左移5位”是实验统计得出的最佳值
```

## 第10章 优先级队列

### 优先级队列ADT

```c++
// 宏
#define InHeap(n, i) (((-1) < (i)) && ((i) < (n)))	// 判断PQ[i]是否合法
#define Parent(i) ((i-1) >> 1)		// PQ[i]的父节点(floor((i-1)/2)，i无论正负)
#define LastInternal(n) Parent(n-1)	// 走后一个内部节点（即末节点的父亲）
#define LChild(i) ( 1 + ((i) << 1 ))	// PQ[i]的父节点（floor((i-1)/2)，i无论正负）
#define RChild(i) ((1 + (i)) << 1)	// PQ[i]的右孩子
#define ParentValid(i) (0 < i)		// 判断PQ[i]是否有父亲
#define LChildValid(n, i) InHeap(n,  LChild(i)) // 判断PQ[i]是否有一个（左）孩子
#define RChildValid(n, i) InHeap(n, RChild(i))	// 判断PQ[i]是否有两个孩子
#define Bigger(PQ, i, j)	(lt(PQ[i]. PQ[j]) ? j : i)	// 取最大者（等时前者优先）
#define ProperParent(PQ, n, i)	/* 父子（至多）三者中的大者*/ \
    ( RChildValid(n, i) ? Bigger(PQ, Bigger(PQ, i, LChild(i) ), RChild(i) ) : \
     ( LChildValid(n, i) ? Bigger(PQ, i, LChild(i)) : i \
	 ) \
    ) // 相等时，父节点优先，如此可避免不必要的交换


// 接口定义
template <typename T> struct PQ	// 优先级队列PQ模板类
{
    virtual void insert(T) = 0;	// 按照比较器确定的优先级次序插入词条
    virtual T getMax() = 0;	// 取出优先级最高的词条
    virtual T delMax() = 0;	// 删除优先级最高的词条
}

// 编码算法
HuffTree* generateTree(HuffForest* forest)
{
    while (1 < forest->size())
    {
        HuffTree* s1 = forest->delMax();
        HuffTree* s2 = forest->delMax();
        HuffTree* s = new HuffTree();
        s->insertAsRoot(HuffChar('^', s1->root()->data.weight + s2->root()->data.weight));
        s->attachAsLC(s->root(), s1);
        s->attachAsRc(s->root(), s2);
        forest->insert(s);	// 将合并后的huffman数插回Huffman森林
    }
    HuffTree* tree = forest->delMax();	// 至此，森林中的最后一棵树
    return tree;
}


// PQ_ComplHeap模板类
template <typename T> class PQ_ComplHeap : public PQ<T>, public Vector<T>	// 完全二叉堆
{
protected:
    Rank percolateDown( Rank n, Rank i);	// 下滤
    Rank percolateUp(Rank i);	// 上滤
    void heapify(Rank n);	// Floyd建堆算法
public:
    PQ_ComplHeap() { }	// 默认构造
    PQ_ComplHeap(T* A, Rank n) { copyFrom(A, 0, n); heapify(n); }	// 批量构造
    void insert(T);	//按照比较器确定的优先级次序，插入词条
    T getMax();	// 读取优先级最高的词条
    T delMax();	// 删除优先级最高的词条
};	//PQ_ComplHeap

template <typename T> T PQ_ComplaHeap<T>::getMax()
{
    return _elem[0];
} //取优先级最高的词条

template <typename T> void PQ_ComplHeap<T>::insert( T e )	// 将词条完全插入二叉堆中
{
    Vector<T>::insert(e);	// 首先将新词条接至向量末尾
    percolateUp(_size - 1);	// 在对该词条实施上滤调整
}


template <typename T> void PQ_ComplHeap<T>::percolateUp( Rank i )
{
    while (ParentValid(i)) {
        Rank j = parent(i);
        if (lt(_elem[i], _elem[j]))
            break;	// 一单当前父子不再逆序，上滤旋即完成
        swap(_elem[i], _elem[j]);
        i = j;	// 否则当前父子交换位置，并继续考查上一层
    }
    return i;	// 返回上滤最终抵达的位置
}

template <typename T> void PQ_ComplHeap<T>::delMax()
{
    T maxElem = _elem[0];
    _elem[0] = _elem[--_size];	// 清除堆顶，代替以末词条
    percolateDown(_size, 0);	// 对新堆实施下滤
    return maxElem;		// 返回此前备份的最大词条
}

template <typename T> void PQ_ComplHeap<T>::percolateDown(Rank n, Rank i)
{
    Rank j;		// i及其（至多两个）孩子中，堪为父者
    while (i != (j = ProperParent(_elem, n, i)))	// 只要i非j，则
    {
        swap(_elem[i], _elem[j]);
        i = j;
    }	// 二者换位，并继续考查下降后的i
    return i;	// 返回下滤抵达的位置（亦i亦j）
}

template <typename T> void PQ_ComplHeap<T>::heapify(Rank n)	// Floyd建堆算法，O(n)时间
{
    for (int i = LastInternal(n); InHeap(n, i); i--)	// 自底而上，依次
        percolateDown(n, i);	// 下滤各内部节点
}

template <typename T> void Vector<T>::heapSort(Rank lo, Rank hi)
{
    PQ_ComplHeap<T> H (_elem + lo, hi - lo);	// 将待排序区建成一个完全二叉堆O(n)
    while (!H.empty())	// 反复地摘除最大元素并归入已排序的后缀，直至堆空
        _elem[--hi] = H.delMax();		// 等效于堆顶与末元素兑换后下滤
}


```

### 左式堆

`npl(lc(x)) >= npl(rc(x))`

`npl(x)`即等于x到外部节点的最近距离

任一内部节点的左孩子npl都不小于其右孩子，但是其高度不一定都比右孩子高

```c++
#include "../PQ/PQ.h"
#include "../BinTree/BinTree.h"	//引入二叉树节点模板类

template <typename T>
class PQ_LeftHeap : public PQ<T>, public BinTree<T>	// 基于二叉树，以左式堆形式实现的PQ
{
public:
    PQ_LeftHeap() { }	// 默认构造函数
    PQ_LeftHeap(T* E, int n)	//批量构造：可改进为Floyd建堆算法
    {
        for (int i = 0; i < n; i++)
            insert(E[i]);
    }
    void insert(T);	// 按照比较器确定的优先级次序插入元素
    T getMax();		// 取出优先级最高的元素
    T delMax();		// 删除优先级最高的元素
};	//PQ_LeftHeap

template <typename T>	// 根据相对优先级确定适宜的方式，合并以a和b为根节点的两个左式堆
static BinNodePosi(T) merge (BinNodePosi(T) a, BinNodePosi(T) b)
{
    if (!a) return b;	// 退化情况
    if (!b) return b;	// 退化情况
    if (lt(a->data, b->data))
        swap(a, b);	// 一般情况：首先确保b不大
    a->rc = merge(a->rc, b);
    a->rc->parent = a;	//并更新父子关系
    return a;	// 返回合并后的堆顶
}	// 本算法只实现结构上的合并，堆的规模须由上层调用者负责更新

template <typename T> PQ_LeftHeap<T>::delMax()	// 要求当前队列非空
{
    BinNodePosi(T) lHeap = _root->lc;	// 左子堆
    BinNodePosi(T) rHeal = _root->rc;	// 右子堆
    T e = _root->data;
    delete _root;
    _size--;	// 删除根节点
    _root = merge(lHeap, rHeap);	// 原左右子堆合并
    if (_root) _root->parent = NULL;	// 若堆非空，还需要相应设置父子链接
    return e;	// 返回原根节点的数据项
}

template <typename T> void PQ_LeftHeap<T>::insert(T e)
{
    BinNodePosi(T) v = new BinNode<T>(e);	// 为e创建一个二叉树节点
    _root = merge(_root, v);	// 通过合并完成新节点插入
    _root->parent = NULL;		// 既然此时堆非空，还需要相应设置父子链接
    _size++;				   // 更新规模
}
```



## 第11章串

### 串匹配蛮力算法

```c++
// 方法一：
int match( char* P, char* T){
    size_t n = strlen(T), i = 0;	// 文本串长度、当前接受比对字符串的位置
    size_t m = strlen(P), j = 0;	// 模式串长度、当前接受比对字符串的位置
    while (j < m && i < n)	// 自左向右逐个比对字符
    {
        if (P[j] == T[i])	// 匹配
        {
            i++;
            j++;	// 转入下一个字符
        }
        else
        {
            i -= j - 1;
            j = 0;	// 文本串回退，模式串重置
        }
    }
    return i - j;	// 返回为0是，匹配到结果
}

// 方法二：
int match(char* P, char* T)
{
    size_t n = strlen(T), i = 0;	// 文本串长度，与模式串首字符对齐的位置
    size_t m = strlen(P), j = 0;	// 模式串长度，当前接受比对字符串的位置
    for (i = 0; i < n - m + 1; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (T[i+j] == P[j])	//匹配
            {
                
            }
            else
            {
                break;
            }
        }
        if (j >= m)
            break;
    }
    return i; // 如果i大于等于n-m+1，表示不匹配
}
```

### KMP算法

```c++
int match(char* P, char* T)	// KMP算法
{
    int* next = buildNext(P);	// 构建next表
    int n = (int)strlen(T), i = 0;	// 文本串指针
    int m = (int)strlen(P), j = 0;	// 模式串指针
    while (j < m && i < n){
        // j为-1是从0回退的，所以已经做过T[i]和P[0]的判断
        if (0 > j || T[i] == P[j])
        {
            i++;
            j++;
        }
        else
        {
            
            j = next[j];	// 模式串右移（文本串不用回退）
        }
    }
    delete [] next;	// 释放next表
    return i - j; // 返回0表示匹配
}

// 构造next表
int* buildNext(char* P)	//模式串P的next表
{
    size_t m = strlen(P), j = 0;	// 主串指针
    int* N = new int[m];	// next表
    int t = N[0] = -1;		// 模式串指针
    while (j < m-1)
    {
        if (0 > t || P[j] == P[t])	// 匹配
        {
            t++;
            j++;
            N[j] = t;
        }
        else
        {
            t = N[t];
        }
    }
    return N;
}

// 优化后的构造next表
int* buildNext(char* P)	//模式串P的next表
{
        size_t m = strlen(P), j = 0;	// 主串指针
    int* N = new int[m];	// next表
    int t = N[0] = -1;		// 模式串指针
    while (j < m-1)
    {
        if (0 > t || P[j] == P[t])	// 匹配
        {
            t++;
            j++;
            N[j] = (P[j] != P[t]) ? t : N[t];	// 在这里优化了
        }
        else
        {
            t = N[t];
        }
    }
    return N;
}
```

### BM算法

```c++
// BM算法
int match(char *P, char *T)	// 兼顾Bad Character与Good Suffix
{
    int* bc = buildBc(P);	// 构造BC表
    int* gs = buildGS(P);	// 构造GS表
    size_t i = 0;
    while(strlen(T) >= i + strlen(P))	// 不断右移（距离可能不止一个字符）模式串
    {
        int j = strlen(P) - 1;	// 从模式串最末尾的字符开始
        while (P[j] == T[i+j])	// 自右向左比对
            if (0 > --j)
                break;
        if (0 > j)	// 若极大匹配后缀 == 整个模式串（说明已经完全匹配）
            break;	// 返回匹配位置
        else // 否则，适当地移动模式串
            i += __max(gs[j], j - bc[T[j+i]]);	// 位移量根据BC表和GS表选择大者
    }
    delete [] gs;
    delete [] bc;
    return i;
}

int* buildBC(char *P)
{
    int* bc = new int[256];	// bc表与字符串等长
    for (size_t j = 0; j < 256; j++)
        bc[j] = -1;	// 初始化：首先假设所有字符均未在P中出现
    for (size_t m = strlen(P), j=0; j < m; j++)
        bc[P[j]] = j;		// 画家算法
    return bc;
}

int* buildSS(char *P)
{
    int m = strlen(P);
    int* ss = new int[m];	// Suffix Size表
    ss[m-1] = m;		   // 对最后一个字符串而言，与之匹配的最长后缀就是整个P串
    // 以下，从倒数第二个字符其自右向左扫描P，依次计算出ss[]其余各项
    for (int lo = m-1, hi = m-1,j=lo-1; j >= 0; j--)
    {
        if ((lo < j) && (ss[m-hi+j-1] <= j - lo))	// 情况一
            ss[j] = ss[m-hi+j-1];	// 直接利用此前以计算出的ss[]
        else	// 情况二
        {
            hi = j; lo = __min(lo, hi);
            while ((0 <= lo) && (P[lo] == P[m-hi+lo-1]))	// 二重循环？
                lo--;	// 逐个对比处于(lo, hi]前端的字符
            ss[j] = hi - lo;
        }
    }
    return ss;
}

int* buildGS(char* p)	// 构造好后缀位移量表：O(m)
{
    int* ss = buildSS(P);	// Suffix Size table
    size_t m = strlen(P);	int* gs = new int[m];	// Good Suffix shift table
    for (size_t j = 0; i < m; j++)
        gs[j] = m;	// 初始化
    for (size_t i = 0, j = m-1; j < UINT_MAX; j--)	// 逆向逐一扫描各字符P[j]
    {
        if (j+1 == ss[j])	// 若P[0,j] = P[m-j-1, m)，则
            while (i < m - j -1)	// 对于P[m-j-1]左侧的每个字符P[i]而言（二重循环？其实不是）
                gs[i++] = m - j - 1;	// m-j-1都是gs[i]的一种选择
    }
    for (size_t j = 0; j < m-1; j++)	// 画家算法
    {
            gs[m-ss[j]-1] = m-j-1;	// m-j-1必是其gs[m-ss[j]-1]值的一种选择
    }
    delete [] ss;
    return gs;
}
```

### Karp-Rabin算法

将字符串转为自然数表示，有进制表示。而进制的表示中，是字母表中的规模为d时，字符串可以表示d+1进制的整数。一个字符串表示的数包含了其任意一个子字符串的数。

```c++
#define M 97	// 散列表长度：既然这里并不需要真地存储散列表，不妨取更大的素数，以降低误判的可能性
#define R 10	// 基数：对于二进制串，取2；对于十进制串
#define DIGIT(S, i) ((S)[i] - '0')	//取十进制串S的第i位数字值（假定S合法）
typedef __int64 HashCode;	// 用64位整数实现散列码
bool check1by1 (char* P, char* T, size_t i);
HashCode prepareDm(size_t m);
void updateHash(HashCode& hashT, char* T, size_t m, size_t K, HashCode Dm);

int match(char* P, char* T)	// 串匹配算法（Karp-Rabin）
{
    size_t m = strlen(P), n = strlen(T);		// assert: m <= n
    HashCode Dm = prepareDm(m), hashP = 0, hashT = 0;
    for (size_t i = 0; i < m; i++)
    {
        hashP = (hashP*R + DIGIT(P, i)) % M;	// 计算模式串对应的散列值
        hashT = (hashP*R + DIGIT(T, i)) % M;	// 计算文本串（前m位）的初始散列值
    }
    for (size_t k = 0; ; )
    {
        if (hashT == hashP)
            if (check1by1(P, T, K))
                return K;
        if (++K > n - m)
            return K;	// assert: K > n - m，表示无匹配6
        else updateHash(hashT, T, m, K, Dm);	// 否则，更新子串散列码，继续查找
    }
}

bool check1by1(char* P, char* T, size_t i)
{
    size_t m = strlen(P);
    for (size_t j = 0; i < m; j++, i++)
    {
        if (P[j] != T[i])
            return false;
    }
    return true;
    
}

HashCode prepareDm(size_t m)
{
    HashCode Dm = 1;
    for (int i = 1; i < m; i++)
    {
        Dm = (Dm*R) % M;		// 直接累乘m-1次，并取模
    }
    return Dm;
}

void updateHash(HashCode& hashT, char* T, size_t K, HashCode Dm)
{
    HashT = (hashT - Dm*DIGIT(T, K-1)) % M;		// 减去头部值，在前一基础上，去除首位T[K-1]
    hashT = (hashT*R + DIGIT(T, K+m-1)) % M;	// 添加末位T[K+m-1]
    if (0>hashT)
        hashT += M;		// 确保散列码落在合法区间内	
}
```



## 第12章排序

### 快速排序

```c++
// 快速排序算法
template <typename T>
void Vector<T>::quickSort(Rank lo, Rank hi)
{
    if (hi  - lo < 2)
        return;
    Rank mi = partition(lo, hi-1);
    quickSort(lo, mi);
    quickSort(mi + 1, hi);
}

template <typename T>
void Vector<T>::quickSort(Rank lo, Rank hi)		// 版本A：基本形式
{
    swap(_elem[lo], _elem[lo + rank()%(hi-lo+1)]);	// 任选一个与首元素交换
    T pivot = _elem[lo];	// 以随机交换后的首元素为轴点
    while (lo < hi)
    {
        while ((lo < hi) && (pivot <= _elem[hi]))	// 在不小小于pivot的前提下
        {
            hi--;
        }
        _elem[lo] = _elem[hi];
        while ((lo < hi) && (_elem[lo] <= pivot))
        {
            lo++;
        }
        _elem[hi] = _elem[lo];
    }
    _elem[lo] = pivot;
    return lo;
}

template <typename T>	// 轴点构造算法：通过调整元素位置构造区间[lo, hi]的轴点，并返回其秩
Rank Vector<T>::partition( Rank lo, Rank hi)	// 版本B：可优化多个关键码雷同的退化情况
{
    swap(_elem[lo], _elem[lo+rand()%(hi-lo+1)]);	// 任选一个元素与首元素交换
    T pivot = _elem[lo];
    while (lo < hi)
    {
        while (lo < hi)
        {
            if (pivot < _elem[hi])
                hi--;
            else
            {
                _elem[lo++] = _elem[hi];
                break;
            }
        }
        while (lo < hi)
        {
            if (_elem[lo] < pivot)	// 在小于pivot的前提下
                lo++;
            else	// 直至遇到不小于pivot者
            {
                _elem[hi--] = _elem[lo];
                break;
            }
        }
    }
    _elem[lo] = pivot;
    return lo;
}
```

### 选取与中位数

```c++
template <typename T> bool majority(Vector<T> A, T& maj)	// 众数查找算法：T可以判等
{
    maj = majEleCandidate(A);		// 必要性：选出候选者maj
    return majEleCheck(A, maj);		// 充分性：验证maj是否的确当选
}
```

