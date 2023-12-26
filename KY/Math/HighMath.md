[TOC]

# 高数笔记

## 第一章 函数 极限 连续

## 第二章 一元函数的微分学

## 第三章 一元函数的积分学

## 第四章 常微分方程

## 4.1 常微分方程概念

## 4,2 一阶微分方程

`y' + p(x)y = Q(x)`的方程称为一阶线性微分方程，一般通过常数变易法或直接利用下面公式
$$
y = e^{p(x)dx[\int Q(x)e^{\int p(x)dx}dx + C]}
$$
 伯努利方程（数学一）

`y' + p(x)y = Q(x)y^n`的方程称为伯努利方程，一般求取方法 `u = y^(1-n)`将原式化为一阶线性微分方程

## 4.3 可降阶的微分方程

1. `y^(n) = f(x)`型的微分方程
2. `y'' = f(x, y')`型的方程：y' = p, y'' = p'，化为一阶微分方程
3. `y'' = f(y, y')`型的方程：令y' = p, y'' = p* dp/dy，化为一阶微分方程

## 4.4 高阶线性微分方程

方程
$$
\begin{align}
	y'' + p(x)y' + q(x)y &= f(x) &\text{二阶线性微分方程一般式} \tag {4.4.3} \\
	y'' + p(x)y' + q(x)y &= 0 &\text{二阶线性齐次微分方程} \tag {4.4.3}\\
	y'' + p(x)y' + q(x)y &= f(x) &\text{二阶线性非齐次微分方程，f(x)不恒等于0} \tag {4.4.4}
\end{align}
$$


p(x), q(x), f(x)，均为连续函数，当f(x)恒等于0时，上面方程(4.4.2)为二阶线性齐次微分方程，反之为非齐次。

**定理1**：如果y1(x) 和y2(x)是上面方程(4.4.3)中的两个线性无关的特解，那么`y = C1y1(x) + C2y2(x)`是方程(4.4.3)的通解

**定理2：**如果y\*是方程(4.4.4)的解，y1(x)和y2(x)齐次线程方程(4.4.3)的两个线性无关的特解，那么`y=C1y1(x)+C2y2(x)+y*(x)`是非齐次线性方程(4.4.4)的通解

**定理3：**如果y1\*(x)和y2\*(x)是非齐次线性方程(4.4.4)的两个特解，则`y(x)=y2*(x)-y1*(x)`是齐次微分方程(4.4.3)的解。

**定理4：**如果y1\*(x), y2\*(x)分别是方程
$$
\begin{align}
	y'' + p(x)y' + q(x)y &= f_1(x) \\
	y'' + p(x)y' + q(x)y &= f_2(x)
\end{align}
$$
的特解，那么y1\*(x)+y2\*(x)是方程
$$
y'' + p(x)y' + q(x)y = f_1(x) + f_2(x)
$$
的一个特解。

### 4.4.2  常系数齐次线性微分方程

二阶常系数齐次微分方程的一般形式
$$
\begin{align}
y'' + py' + qy &= 0 \tag{4.4.5} \label{eConstEq} \\
r^2 + pr + q &= 0 &\text{$\eqref{eq:ConstEq}$的特征方程  }

\end{align}
$$

$$
\left \{
\begin{array}{c}
\begin{align}
y &= C_1e^{r_1x}\ +\ C_2e^{r_2x}, &\text{$r_1$ $\neq$ $r_2$ 为两个不相等的实特征根} \\
y &= (C_1+C_2x)e^{r_1x}, & \text{$r_1$ = $r_2$，二重实特根} \\
y &= e^{\alpha x}(C_1\cos \beta x + C_2\sin \beta x), & \text{$r_1=\alpha+i\beta$和$r_2=\alpha-i\beta$为一对共轭复根}
\end{align}
\end{array}
\right.
$$



### 4.4.3  常系数非齐次线性微分方程

方程(4.4.5)中的右式恒为0表示齐次，不恒为0，为f(x)的时候表示非齐次
$$
\begin{align}
y'' + py' + qy &= f(x) \tag{4.4.6}\\
\end{align}
$$


一般特解为
$$
y^* = 
\begin{cases}
x^kQ_m(x)e^{\lambda x} , & \text{$f(x)=P_m(x)e^{\lambda x}$时，$P_m(x)$表示m次多项式，k为$\lambda$是否为特征值的重复次数，0-2}\\
x^ke^{\alpha x}[R^{(1)}_m(x)\cos \beta x \ + \ R^{(2)}_m(x)\sin \beta x], & \text{$f(x)=e^{\alpha x}[P_l(x)\cos \beta x \ + \ P_n(x) \sin \beta x]$时，$P_l(x)$和$P_n(x)$分别时x的l和n阶多项式，m = max{l, n}，当$\alpha + i\beta$为方程\eqref{ConstEq}的单特征根时，k=1，如果不是方程\eqref{ConstEq}的特征根时，k=0}

\end{cases}
$$


## 第五章 多元函数微分学

## 第六章 二重积分