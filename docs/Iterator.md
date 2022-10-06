## iterator

迭代器的行为类似指针，具体来说有五种：

1. Input Iterator：只读
2. Output Iterator：只写
3. Forward Iterator：可读写，只能前向
4. Bidirectional Iterator：可读写，可以双向
5. Random Access Iterator：可读写，随机顺序

iterator中用到了很多traits和模板技巧，学到许多:)

* **iterator_traits中的偏特化**

这一部分的实现可以参考《STL源码剖析》，但是这本书中的STL版本较老，基础部分是都有的，iterator_traits_impl和iterator_traits_helper暂无。

偏特化大概意思：对于一个有多个模板参数的模板，指定其中若干个模板参数，生成另一个模板。同时还有一个全特化的概念，就是所有的模板参数都确定了。

在迭代器设计中主要是为了取出数据的实际类型

```cpp
template <typename T, typename V, typename U>
class A{};

// 偏特化
template <typename V, typename U>
class A<int, V, U> {};

// 全特化
template <>
class A<int, float, double> {};
```

用这种方式可以萃取出数据的类型（T、T*、const T*）

其中的category_type是为了**重载决议**，在编译器确定对应迭代器使用的函数。这一点和上面Constructor中的true_type和false_type是类似的。

* **has_iterator_cat**

使用了SFINAE（Substitution Failure Is Not An Error，匹配失败不是错误）技巧，用来检测类T中是否定义了iterator_category。

这种方法适用于检测类是否包含某些成员变量

* **std::is_convertible**

用于判断两种类型能否隐式转换

```sh
is_convertible <A, B>::value;
```

* **判断迭代器类型**

这里谈一下设计思路

最终目的肯定是实现is_xxx_iterator<Iterator>这种接口，
抽象一下就变成了has_iterator_cat_of<Iterator, xxx_iterator_tag>这样。
也就是说重复的代码都放大has_iterator_cat_of中了。