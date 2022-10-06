
## vector

vector属于序列式容器，是和array很类似的数据结构。区别在于vector可以动态扩容，而array需要重新配置空间。

同时vector可以随机读取，所以提供一个Random Access Iterator。

#### 一些思考

* **关于什么时候用_begin，什么时候用begin()**

我的理解是如果有const重载直接_begin就行，否则还是begin()让编译器决定。

* **关于一些代码规范**

实现代码只有两三行的就放到定义时实现，否则还是放到类外面好一点，不然显得代码非常臃肿。

* **辅助函数设计**

有很多函数的功能类似（特别是重载的），所以就通过这种辅助函数的方式把其中相同的功能抽象出来，从而增加可读性，减少代码量。

#### 支持的API

* 迭代器

begin、end、cbegin、cend、size、capacity、max_size、empty、reserve、shrink_to_fit

* 访问元素

[]、at、front、back、data

* 容器

支持emplace、push_back、emplace_back、assign、insert、erase、resize、swap等。支持各种左值、右值和迭代器形式。

#### Q & A

* **std::is_same**

用于判断两个类型是否一致，vector里面用于静止bool类型（STL中对bool类型做了优化，不是按byte寻址，而是一个元素一个bit，所以在这里所幸就不支持了）

```cpp
std::is_same<T, bool>::value
```
可以判断该类型是否为同样的类型

* **static_assert**

可以理解为编译器的assert

* **const重载**

之后类的const对象才能调用的重载函数

```cpp
void func() const {}
```

* **enable_if**

```cpp
std::enable_if<B, T>::type
```
只有当第一个模板参数为true的时候，才会定义type类型为T。

用在迭代器操作的时候，为了判断时候这个函数的时候两个形参都是迭代器。在代码中多次用到。

* **initializer_list**

用于初始化对象（写起来就是花括号的形式）

```cpp
void func(std::initializer_list<value_type> il) {}
```

使用的时候直接值传递即可，不需要加引用。因为initializer_list本身就是引用而非拷贝。

* **noexcept**

告诉编译器这个函数不会产生异常，这样编译器可以做更多优化。一旦产生异常，程序就会终止。