## allocator & constructor

用于为所有的容器管理空间、构造析构，也就是负责创建和销毁对象

* **为什么用静态构造函数？**

为了初始化静态成员变量（否则构造函数只在实例化时调用）

* **可变参函数模板...Args**

样例见demos/template_parameter_pack.cpp，
也就是说这个模板的参数类型数量不定

以及可变参什么时候用...扩展？（未解决）
forward之后...

* **[new operator, operator new, placement new](https://blog.csdn.net/WUDAIJUN/article/details/9273339)**

new operator就是平时实例化对象用的那个

operator new是一个运算符函数，用于分配内存空间

placement new是一种特殊的operator new，定义与new.h中，用于在ptr的地址上构造对象。使用方法为::new(ptr) A()

> A* a = new A();
> 使用new运算符初始化一个对象时
> 1. 调用::operator new**函数（这就意味着可重载）**来分配内存
> 2. 调用构造函数构造对象
> 3. 返回对象的指针

* **[万能引用, 引用折叠Args&&..., 完美转发std::forward](https://zhuanlan.zhihu.com/p/50816420)**

万能引用

```cpp
// 万能引用的例子，
template <typename T>
void func(T&& t) {}

// T为int，那么穿进去就变成int &&，推导为右值
// T为int &，那么穿进去就变成int& &&，推导为左值
// T为int &&，那么穿进去就变成int&& &&，推导为右值
```

引用折叠

万能引用是通过引用折叠来实现的。C++11中有左值和右值的概念，引用折叠可以理解为把两个引用连接在一起

1. T& &     -> &
2. T& &&    -> &
3. T&& &    -> &
4. T&& &&   -> &&

完美转发

为了将左值以左值的形式传递，右值以右值的形式传递（看起来好像是废话）

其实是为了避免右值引用变量传递时被当成左值的问题（函数形参被当成左值处理）

forward实现时其实就是强转成T&&

```cpp
template <typename T>
T&& func(T& t) {
    return static_cast<T&&>(t);
}
```

* **std::remove_reference**

消除变量的引用类型，返回原始类型。需要特别注意在形参中用的时候，需要加typename指定类型

```cpp
T& t_ref;
std::remove_reference(t_ref)::type t;   // t的类型为T
// 原理就是 typedef T type;
```

* **[typename指定类型](https://feihu.me/blog/2014/the-origin-and-usage-of-typename/#%E9%99%90%E5%AE%9A%E5%90%8D%E5%92%8C%E9%9D%9E%E9%99%90%E5%AE%9A%E5%90%8D)**

用typename告诉编译器后面是一个类型，而不是一个变量。否则在使用静态成员变量的时候会有问题（比如forward源码中）

* **allocator中的变参construct为什么不能写成一行？（未解决）**

```cpp
template<typename T, typename ...Args>
vs
template<typename T>
template<typename ...Args>
```

* **std::is_trivially_destructible**

判断对象是否是"trivially destructible"，和std::true_type/false_type一起用（true_type和true的区别在于true_type是类型而true是值），这里主要是为了编译期确定使用的函数，进行重载决议。

1. 有隐式的析构函数（没有显示定义）
2. 析构函数不能是virtual的
3. 所有非静态成员变量必须也是trivially destructible的

* **destory_aux中的destory(&*first)是什么意思？**

明面上看是一个解引用再取地址（好像什么都没做）

但是如果传入的first是一个类的迭代器，重载之后的解引用得到的是对应位置元素，然后再取地址，才能得到这个元素本身的地址。