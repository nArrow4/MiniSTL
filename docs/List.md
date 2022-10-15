## List

list相比vector会更复杂一些，因为不是连续线性空间。

* **class中typedef的用处**

更多的是一种限制作用域的用处

* **typedef和using**

using是现代C++对typedef的一个扩充，可应用于类模板的别名。

* **[traits编程技巧](https://zhuanlan.zhihu.com/p/85809752)**

在STL中经常会用到某些相应型别(assotiated type)，有几种方法可以解决这个问题：

1. 函数模板自动推导
2. 内嵌类型

但是函数模板不能推导返回值，内嵌类型不支持原生指针。Traits技巧就是针对这一情形，通过加入一个中间层判断原生指针。并对原生指针的方法进行偏特化。

```cpp
template <typename T>
class Iter {
    typedef T value_type;
};

template <typename T>
struct traits {
    typedef typename T::value_type value_type;
};

template <typename T>
struct traits<T*> {
    typedef T value_type;
};

template <typename T>
struct traits<const T*> {
    typedef T value_type;
};
```

Iter是需要支持的迭代器，后面两个traits是用偏特化支持的原生指针。

* **为什么需要list_node_base**

base节点维护前后向的移动操作，node节点存储数据

* **list迭代器**

list迭代器需要有递增、递减、解引用等操作（双向链表）

* **operator++和operator++(int)**

operator++对应前缀++，operator++(int)是后缀++。编译器会自动添加0。
注意实现时前后缀的区别