# 计算几何笔记

## Convex Hull

### 点在三角形（p, q, s）内求法

利用向量，点在pq，ps，sp向量的左边,利用有向面积，海伦公式与此类似

![ExtremePoint1](E:\workfor2020\Learning-note\Computational geometry\ExtremePoint1.png)

```c++
bool ToLeft( Point p, Point q, Point s)
{
    return Area2(p, q, s) > 0;
}
int Area2(Point p, Point q, Point s)
{
    return p.x * q.y - p.y * q.x
        +  q.x * s.y - q.y * s.x
        +  s.x * p.y - s.y * p.x;
}
```

