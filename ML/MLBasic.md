# 机器学习基本算法

## K-近邻算法



## 决策树



## 朴素贝叶斯算法



## Logistics回归

## 支持向量机

## AdaBoost 

AdaBoost是adaptive boosting（自适应boosting）的缩写

- 优点：返回错误率低，易编码，可以应用在大部分分类器上，无参数调整
- 缺点：对离群点敏感
- 使用数据类型：数值型和标称型数据

### AdaBoost的一般流程

1. 收集数据：可以使用任意方法
2. 准备数据：依赖于所使用的的弱分类器类型，本章使用的是单层决策树，这种分类器可以处理任何数据类型。当然也可以使用任意分类器作为弱分类器。作为弱分类器，简单分类器的效果更好
3. 分析数据：可以使用任意方法
4. 训练算法：AdaBoost的大部分时间都用在训练上，分类器将多次在同一数据集上训练弱分类器。
5. 测试算法：计算分类的错误率
6. 使用算法：同SVM一样，AdaBoost预测两个类别中一个。如果想把它应用到多个类别的场合，那么就要像多类SVM中的做法一样对AdaBoost进行修改。

### 非均衡分类问题

#### 分类性能度量指标

- 正确率：公式为（真正例/(真正例+伪正例)）
- 召回率：公式为（真正例/(真正例+伪反例)）
- ROC曲线：代表接受者操作特征

### 基于代价函数的分类器决策控制

### 处理非均衡问题的数据抽样方法

- 欠抽样：删除样例
- 过抽样：复制样例

## 树回归

- 优点：可以对复杂和非线性的数据建模
- 缺点：结果不易理解
- 使用数据类型：数值型和标称型数据

### 树回归的一般方法

1. 收集数据：采用任意方法收据数据
2. 准备数据：需要数值型数据，标称型数据应该映射成二值型数据
3. 分析数据：绘出数据的二维可视化显示结果，以字典方式生成树
4. 训练算法：大部分时间都花费在叶节点树模型的构建上
5. 测试算法：使用测试数据上的R2值来分析模型的效果
6. 使用算法：使用训练出的树做预测，预测结果还可以用来做很多事情

## 感知机

## 隐马尔科夫模型

## 条件随机场



## K-均值聚类算法

### 优缺点

- 优点：容易实现
- 缺点：可能收敛到局部最小值，在大规模数据集上收敛较慢
- 使用数据类型：数值型数据

## Apriori算法

 ### 优缺点

- 优点：易编码实现
- 缺点：在大数据集上可能较慢
- 使用数据类型：数值型或标称型数据

### Apriori算法的一般过程

1. 收集数据：用任意方法
2. 准备数据：任何数据类型都可以，因为我们只保存集合
3. 分析数据：使用任意方法
4. 训练算法：使用spriori算法来找到频繁项集
5. 测试算法：不需要测试过程
6. 使用算法：用于发现频繁项集以及物品之间的关联规则

## FP-growth算法

## 奇异值分解

## 主成分分析

## 潜在语义分析

## 概率潜在语义分析

## 马尔可夫链蒙特卡洛法

## 潜在狄利克雷分配

## PageRank算法
