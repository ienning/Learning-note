[TOC]

# 6. 图像处理

## 6.1 线性滤波：方框滤波，均值滤波，高斯滤波

### 6.1.1 噪声消除

消除噪声一般是平滑处理和滤波操作

### 6.1.2 方框滤波

方框滤波的卷积核内的值都是为1

### 6.1.3 均值滤波

均值滤波的卷积核内部是方框滤波的卷积核归一化后的结果，就是1/(kernel.size)

### 6.1.4 高斯滤波

高斯滤波是通过正态分布的方式，设定卷积核中的每个系数，可以设置X和Y方向的sigma参数，调整分布的幅度或者说宽度。

## 6.2 非线性滤波：中值滤波，双边滤波

### 6.2.1 非线性滤波概述

线性滤波是每个输出像素都是几个输入像素的加权和，好处是简单，但是不会去除噪声像素，只是变得柔和。而非线性滤波不是通过简单的加权和

### 6.2.2 中值滤波

中值滤波通过目标像素中邻近点的中值，通过这样消除噪音，如果是奇数个点，那么取中间值，如果是偶数个点，取中间两个中值求平均得到

### 6.2.3 双边滤波

双边滤波是结合图像的空间邻近度和像素值相似度的一种这种处理。比高斯滤波多了一个高斯方差sigma-d，是基于空间分布的高斯滤波函数，所以再边缘附近，离的较远的像素不会对边缘上的像素值影响太多。保证了边缘附近像素值的保存。对彩色图像中的高频噪声，双边滤波器不能够干净地过滤，只能对低频信息进行较好地滤波。

## 6.3 图像处理形态学：腐蚀，膨胀，开运算，闭运算，形态学梯度，顶帽，黑帽

### 6.3.1 形态学概述

数学形态学是一门建立在格伦和拓扑学基础之上的图像分析学科，是数学形态学图像处理的基本理论。

### 6.3.2 腐蚀

腐蚀和膨胀是对白色区域进行的操作。

### 6.3.3 膨胀

高灰度值吃低灰度值

### 6.3.4 开运算

先腐蚀和膨胀：用于消除小物体（偏向高灰度值），以及对较大物体进行平滑处理且不改变其面积。

### 6.3.5 闭运算

先膨胀后腐蚀：用于排除小型黑洞。

### 6.3.6 形态学梯度

膨胀图和腐蚀图之差，用于突出轮廓边缘

### 6.3.7 顶帽

原图像和开运算之差：得到的效果图突出了比原图轮廓周围的区域更明亮的区域，且和这一操作与选择的核的大小相关

### 6.3.8 黑帽

闭运算和原图像之差：黑帽运算后的效果图突出了比原图轮廓周围的区域更暗区域

## 6.4 漫水填充

填充指定的颜色

## 6.5 图像缩放

主要使用resize，可以设定x和y方向的比例系数以及目标图像的大小



## 6.6 图像金字塔

上采样和下采样；

下采样使用的高斯金字塔

拉普拉斯金字塔：用于获取采样过程中丢失的信息，预测残差

resize：再放大的时候通过使用插值的方式填充

## 6.7 阈值化 

阈值化主要是对灰度图进行二值化，一般是两个API，一个是自己指定的，一个是自适应。

## 6.8 总结

![chapter6](.\src\chapter6.png)

# 7. 图像变换

## 7.1 基于OpenCV的边缘检测

### 7.1.1 边缘检测的一般步骤

1. 滤波：边缘检测主要基于图像的一阶和二阶导数，但是导数对噪声很敏感，所以要通过滤波器来改善，主要是使用高斯滤波
2. 增强：将图像灰度点领域值有显著变化的的点凸显出来。可用计算梯度幅值确定。
3. 检测：有些点梯度值比较大，不是要找的边缘点，可以采用阈值化的方法来检测

### 7.1.2 canny边缘检测

特点：

- 低错误率：标识出尽可能多的实际边缘，同时尽可能地减少噪音产生的误报。
- 高定位性：标识出的边缘与图像中的实际边缘尽可能接近。
- 最小响应：图像中的边缘只能标识一次，并且可能存在的图像噪声不应标识为边缘。

步骤：

1. 消除噪声：一般使用高斯平滑滤波器卷积降噪。
2. 计算梯度幅值和方向：按照Sobel滤波器的步骤来操作，一对卷积阵列分别作用X和Y方向，Gx和Gy，然后它们各自平方之和再开根以及再计算arctan(Gy/Gx)得到角度
3. 非极大值抑制：排除边缘像素，仅保留一些细线条
4. 滞后阈值：
   1. 采用双阈值，高阈值和低阈值
   2. 大于高阈值的像素保留，小于低阈值的像素被排除，再高阈值和低阈值之间的像素，如果有和大于高阈值的像素连接，那么也会被保留，反之排除。

### 7.1.3 sobel算子

介绍：

sobel主要用于边缘检测的离散微分算子。结合了高斯平滑和微分求导，用来计算图像灰度函数的近似梯度。在图像任何一点使用此算子，都将会产生对应的梯度矢量或者是其法矢量

步骤：

1. 在X和Y方向分别卷积得到Gx和Gy
   $$
   G_x =  \begin{bmatrix} 
   					   -1 & 0 & +1 \\
   					   -2 & 0 & +2 \\
   					   -1 & 0 & +1 \\
   		\end{bmatrix} * I
   \\G_y = \begin{bmatrix} 
   					   -1 & -2 & +1 \\
   					    0 &  0 &  0 \\
   					   +1 & +2 & +1 \\
   		\end{bmatrix} * I
   $$
   
2. $$
   \sqrt{G^2_x+G^2_y}
   $$

   使用上面公式获得近似梯度

### 7.1.4 Laplacian 算子

介绍：

Laplacian算子是n维欧几里得空间中的一个二阶微分算子，定义为梯度grad的散度div

步骤：

### 7.1.5 scharr滤波器

介绍：

scharr为滤波器，不是算子，一般配合sobel算子使用，Scharr滤波器计算x或y方向的图像差分。

步骤：

## 7.2霍夫变换

### 7.2.1 简介

霍夫变换是图像处理中的一种特征提取技术，该过程在一个参数空间中通过计算累计结果的局部最大值得到一个符合该特定形状的集合作为霍夫变换结果。用于检测直线，扩展后可以检测圆和椭圆

- 标准霍夫变换：HoughLines函数
- 多尺度霍夫变换：HoughLines函数
- 累积概率霍夫变换：HoughLinesP函数

### 7.2.3 霍夫梯度法的原理

用于解决圆变换

步骤：

1. 对图像应用边缘检测，比如canny边缘检测
2. 对边缘图像中地每个非零点，考虑局部梯度，即用Sobel()函数计算x和y方向地Sobel一阶导数得到梯度。
3. 利用得到的梯度，由斜率指定的直线上的每一个点都在累加器中被累加，这里的斜率是从一个指定的最小值到指定的最大值的距离。
4. 同时，标记边缘图像中每一个非0像素的位置。
5. 然后从二维累加器中这些点中选择候选的中心，这些中心都大于给定阈值并且大于其所有近邻。这些候选中心按照累加值降序排列，以便于最支持像素的中心首先出现。
6. 接下来对每一个中心，考虑所有的非0像素
7. 这些像素按照其与中心的距离排序。从到最大半径的最小距离算起，选择非0像素最支持的一条半径。
8. 如果一个中心收到边缘图像非0像素最充分的支持，并且到前期被选择的中心有足够的距离，那么它就会被保留下来。
9. 

优缺点：

优点：

1. 通过排序，

缺点：

1. 原始的Hough变换找圆，计算量很大，而且如果对查找圆的半径不加控制，不但运算量巨大，而且精度也不足，在输入噪声点不多的情况下，找圆效果远不如拟合找圆；为了提高找圆精度，相比拟合法，需要提供更多的参数加以控制，参数要求比较严格，且总体稳定性不佳

## 7.3 重映射

重映射是将一张图像的某个位置的像素放置到另一个指定位置的过程

## 7.4 仿射变换

仿射变换是指在几何中，一个向量空间进行一次线性变换并接上一个平移，变换为另一个向量空间的过程，它保持了二维图形的平直性（平直性是指变换前后的图形之间的相对位置保持不变，平行线依旧是平行线，且直线上点的位置顺序不变）。



## 7.5 直方图均衡化

直方图均衡化是通过拉伸像素强突分布范围来增强图像对比度的一种方法。

# 8.图像轮廓与图像分割修复

## 8.1 查找并绘制轮廓

寻找了轮廓使用的是`findContours()`函数，绘制轮廓函数是`drawContours()`函数

## 8.2 寻找物体的凸包

凸包概念：给定二维平面上的点集，凸包就是将最外层的点连接起来构成的凸多边形，它是能包含点集中的所有点

## 8.3 使用多边形将轮廓包围

1. 返回外部矩形边界：boundingRect()函数
2. 寻找最小包围矩形：minAreaRect()函数
3. 寻找最小包围圆形：minEnclosingCircle()函数
4. 用椭圆拟合二维点集：fitEllipse()函数
5. 逼近多边形曲线：approxPolyDP()函数

## 8.4 图像的矩

图像的矩集通常描述了该图像形状的全局特征，并提供了大量的关于该图像不同类型的几何特征信息，比如大小，位置，方向及形状等。矩用来计算形状的重心，面积，主轴和其它形状特征。

- 使用moments计算图像所有的矩
- 使用contourArea计算轮廓面积
- 使用arcLength计算轮廓或曲线长度

## 8.5 分水岭算法

函数watershed实现的分水岭算法是基于标记的分割算法中的一种，在把图像传给函数之前，我们需要大致勾标记出图像中的期望进行分割的区域，它们被标记为正指数。

## 8.6 图像修复

图像修复技术是利用那些已经被破坏区域的边缘，即边缘的颜色和结构，繁殖和混合到损坏的图像中，以达到图像修补的目的。

- inpaint()函数是进行图像修补的

# 9. 直方图与匹配

## 9.1 图像直方图概述

在统计学中，直方图是一种对数据分布情况的图形表示，是一种二维统计图表，它的两个坐标分别是统计样本和该样本对应的某个属性的度量。

## 9.2 直方图的计算与绘制

- 计算直方图：calcHist()函数：用于计算一个或者多个阵列的直方图
- 找寻最值：minMaxLoc()函数：找到全局最小值和最大值

## 9.3 直方图对比

## 9.4 反向投影

## 9.5 模板匹配

模板匹配算法主要是通过窗口滑动的方式进行的。进行匹配的算法方式有多种。



# 10.角点检测

## 10.1 Harris角点检测

图像特征类型分为以下三类：

1. 边缘
2. 角点（感兴趣关键点）：再某一点的任意方向的一个微小的变动都会引起灰度很大的变化，那么我们称之为角点。
3. 斑点（感兴趣区域）







## 10.2 Shi-Tomasi角点检测

该方法是Harris算法的改进。

## 10.3 亚像素级角点检测



# 11特征检测与匹配

## 11.1 SURF特征点检测

## 11.2 SURF特征提取

## 11.3 使用FLANN进行特征点匹配

## 11.4 寻找已知物体

## 11.5 ORB特征提取

按Die的统计结果

按缺陷的统计结果