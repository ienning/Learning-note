# Paddle

## 介绍

### 图像语义分割（Segmentation）

语义分割和分类不一样，语义分割比较精细

- 图像分割：
- 图像语义分割：给每个pixel分类
- 图像实例分割：给每个框里的object分mask
- 图像全景分割：背景pixel分类+框里的mask
- 视频目标分割：通常会给定目标MASK，求特定的MASK
- 视频实例分割：根据目标检测的框，求目标的mask

### 应用场景

1. 人像分割
2. 自动驾驶（行人、车辆分割、车道线检测）
3. 医学图像（病理、CT、MRI）
4. 工业质检、分拣机器人

### 图像语义分割（Segmentation）

#### 基本流程：

- 输入：图像（RGB）
- 算法：深度学习模型
- 输出：分类结果（与输入大小一致的单通道图）
- 训练过程：
  - 输入：
  - 前向：
  - 计算损失：
  - 反向：
  - 更新权重：

#### 语义分割性能指标

- mIoU：分割每一类别的交并比（IOU），pred和Gt的交集除以他们之间的并集

- mAcc：Pred和Gt（Ground truth）对应位置的“分类”准确率

## FCN

- Upsample：越变越大
  - Up-sampling
    - 可以使用双线性插值
  - Transpose Conv
  - Un-pooling
    - 上采样时候，对扩大的位置进行填充

#### 优缺点：

- 优点：
  - 任意尺寸输入
  - 效率高（相较以前）
  - 结合浅层信息
- 缺点：
  - 分割结果不够精细
  - 没有考虑上下文信息（约等于旁边有什么）

## UNet & PSPNet

### UNet



### PSPNet

利用上下文信息

- 操作
  - Adaptive Pool
    - C不变，H，W改变
    - 有公式计算的
    - ![PSPAdaptivePooling](C:\Users\Jingduo-Dolphin\Pictures\learnnote\PSPAdaptivePooling.png)
  - conv 1x1
    - H，W不变，C改变
  - upsample
  - Concat

#### Recap:Dilated Convolution

Dilated Conv = Atrous Conv = 空洞卷积

能将感受野变大

- 理解一：将kernel扩大填0
- 理解二：featuremap间隔计算Conv

## DeepLab系列

### DeepLab V1-网络结构

- VGG Layers 5：Atous Conv
- FC6： Atrous Conv
- FC7：Conv1X1
- classification X：
  - Conv（stride）+ ReLU + Drop
  - Conv1X1 + ReLU + Drop
  - Conv1X1（n_classes）

## Graph-based分割

## 实例分割

- 语义分割：每个像素所属类别（包括stuff类和object类）
  - stuff类：是指没有具体边界的类别，比如天空，大海，路面等
  - object：是指有边界的类别，比如汽车，人等。
- 实例分割：每个object类别和mask（只有object类，所以要判断每个像素是属于object类还是背景）
- 全景分割：每个像素类别和object类别的实例ID

#### Mask R-CNN

训练使用正样本

重要组件：

1. RPN（Region Proposal Network）
2. Feaure Pyramid Network
3. Head Architecture



