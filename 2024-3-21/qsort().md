### qsort()

头文件：stdlibe.h

#### qsort() 函数的声明:

```
void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*))
```

#### 参数

- **base** -- 指向要排序的数组的第一个元素的指针。
- **nitems** -- 由 base 指向的数组中元素的个数。
- **size** -- 数组中每个元素的大小，以字节为单位。
- **compar** -- 用来比较两个元素的函数。

#### compar函数的定义：

```c
int compar(const void *p1, const void *p2);
```

- 如果compar返回值小于0（< 0），那么p1所指向元素会被排在p2所指向元素的前面 
- 如果compar返回值等于0（= 0），那么p1所指向元素与p2所指向元素的顺序不确定 
- 如果compar返回值大于0（> 0），那么p1所指向元素会被排在p2所指向元素的后面 

因此，如果想让qsort()进行从小到大（升序）排序，那么一个通用的compar函数可以写成这样：

```c
int cmp(const void*a,const void*b){//不声明类型
	return (*(int*)a)-(*(int*)b);//申明指针类型，-1
}
```



#### 使用：以字符串为例

用strcmp(str1,str2);比较字符串：（按从小到大排序）

```c
int cmp(const void* a, const void* b){
    return strcmp(((struct zip*)a)->ch,((struct zip*)b)->ch);
}
```

