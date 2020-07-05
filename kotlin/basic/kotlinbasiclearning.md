# Tips

## 字符串

```kotlin
// 可以使用 ${变量或函数} 在字符串中直接使用
// example：
fun main() {
    val a = 1 // val是不允许修改的，只是用一次
    var b = 2 // var是可以修改的
    b++
    println("a is ${a} and b is ${b}") // 输出结果： a is 1 and b is 2
}
```

## 空值和null

变量值可以为空时候需要在声明处的类型后添加 `?` 来标识该引用可以为空。