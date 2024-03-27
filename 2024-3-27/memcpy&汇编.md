## memcpy:

### 1：函数参数

```
void *
memcpy (dstpp, srcpp, len) 
     void *dstpp;
     const void *srcpp;
     size_t len;
```

忽略这种传参的形式，传入的三个参数分别是`目的地址（void *dstpp）`、`源地址(const void *srcpp)`、`长度(size_t len)`。

### 2：地址被转换成`unsigned long int`保存。

```
 unsigned long int dstp = (long int) dstpp;
 unsigned long int srcp = (long int) srcpp;
```

8个字节的地址被转换成`unsigned long int`保存，因为`sizeof(unsigned long int) = 8`，刚好是8字节，如果还是不能理解把地址转成`unsigned long int`，看下面的程序：

```
#include<stdio.h>

int main(int argc,char *argv[])
{
    int a = 256;  
    int *p = &a;
    unsigned long int ds = (long int)p;
    printf("%d %d\n",*(int *)ds,sizeof(unsigned long int));

    return 0;
}
```

![这里写图片描述](https://img-blog.csdn.net/20161118223842716)

地址只有一个唯一的`ds`，上面的程序是将`ds`转成`int*`，是因为我们将它按照`int`对待了，那如果我想以字节`char`处理它呢，那是不是转成`char *`就行了，我们用下面这张图先分析下上面代码的情况。
![这里写图片描述](https://img-blog.csdn.net/20161118225903445)

`a` 变量的值为`256`，是一个`int` 类型的，`4 个字节`，在内存中的分布就像上面所示。我们将地址转成`int *`，那么接着我就会处理四个字节，如果我将地址转成`char *`，那我只处理一个字节不就好了。代码变成这样:

```
#include<stdio.h>

int main(int argc,char *argv[])
{
    int a = 256;
    int *p = &a;
    unsigned long int ds = (long int)p;
    printf("%d %d\n",*(char *)ds,sizeof(unsigned long int));

    return 0;
}
```

![这里写图片描述](https://img-blog.csdn.net/20161118230336817)

果然，输出的值变为了`0`,就是我们上面图中`char *`只指向第一个字节。为0。

好了，说了这么多，有什么用呢？

不要着急，我们继续往下走看源码；

### 3：拷贝数量较小，采用 `one byte one byte`拷贝。

```
 if (len >= OP_T_THRES)  //OP_T_THRES=16 {
    ......
 }
 BYTE_COPY_FWD (dstp, srcp, len);

 return dstpp;
}
```

如果 `len >= OP_T_THRES`（`OP_T_THRES`在不同的系统或者平台有不同的值，通常为16或者8），那就按照`if`中的结构处理，否则执行`BYTE_COPY_FWD (dstp, srcp, len)`。也就是拷贝的长度如果大于16或者8，我们采用`if`中的策略，如果小于16或者8，就 `one byte one byte`拷贝。

### 4：如果拷贝数量较大，采用`if`中的策略

数量较大势必会牵扯到内存对齐的问题：

```
/* Copy just a few bytes to make DSTP aligned.  */
len -= (-dstp) % OPSIZ;  
BYTE_COPY_FWD (dstp, srcp, (-dstp) % OPSIZ);
```

`(-dstp) % OPSIZ`这个神奇的式子可以算出来对齐需要移动的字节数，就像下面这样：
![这里写图片描述](https://img-blog.csdn.net/20161118232813395)

这一部分比较少的字节仍然采用 `one byte one byte`拷贝。

```
BYTE_COPY_FWD (dstp, srcp, (-dstp) % OPSIZ);  //传的参数为(-dstp) % OPSIZ),就是对齐需要拷贝的字节数
```

此时的`len`就为对齐之后的剩余大小了，之后的处理方式直接按照虚拟内存页的大小来加快拷贝效率。

```
 /* Copy whole pages from SRCP to DSTP by virtual address manipulation,as much as possible.  */
    PAGE_COPY_FWD_MAYBE (dstp, srcp, len, len);
```

如果后面还有剩余部分，还可以采用一个字一个字拷贝：

```
 WORD_COPY_FWD (dstp, srcp, len, len);

 /* Fall out and copy the tail.  */
```

大家肯定注意到了源码中的三个函数：

1. BYTE_COPY_FWD (dstp, srcp, (-dstp) % OPSIZ);
2. PAGE_COPY_FWD_MAYBE (dstp, srcp, len, len);
3. WORD_COPY_FWD (dstp, srcp, len, len);

其中 dstp 和 srcp 都是保存了地址的 `unsigned long int`类型的数。那为什么传入它们竟然能实现在按照不同的类型`byte`，`page`，`word`来拷贝呢（忽略有没有`page` 这种类型的细节，我只是想说前面三种类型大小是不同的），那一定在这三个函数中做了类似与我们前面举的例子的转化，我们去找找看，果然，找到一些情况。

在`memcopy.h`中

![这里写图片描述](https://img-blog.csdn.net/20161118235006638)

转成 `byte *`再去操作，因为是`one byte one byte`拷贝。

在`pagecopy.h`中

![这里写图片描述](https://img-blog.csdn.net/20161118234940200)

转成`vm_address_t类型`去处理。

在`wordcopy.c`中

![这里写图片描述](https://img-blog.csdn.net/20161118234752503)

其中 `op_t`是一个宏定义，为`unsigned long int`。

### 5： 总结

说了这么多，我们基本从宏观上缕清了memcpy的流程。

- 先用`unsigned long int` 保存地址
- 然后判断需要拷贝的大小，如果小于 `OP_T_THRES`，直接`one byte one byte`拷贝。
- 如果大于 `OP_T_THRES`，首先对齐。然后需要对齐的部分按照`one byte one byte`拷贝。对齐之后的按照`one page one page`拷贝，最后剩余的还可以按照`one word one word`拷贝。





### 汇编搬运字节：

1. cld

   复位方向表标记位 DF，即 DF = 0。DF为 0 则源寄存器地址 ESI/EDI (源寄存器/目标寄存器) 递增，1 则递减。

2. rep

   表示重复，repeat，当 ECX (计数器) > 0 的时候就一直 rep。

3. movsb

   就是搬移字串，汇编搬移字串有 movsb 和 movsw 两种，movsb 就是 moving string byte，就是一次搬一个字节，mvsw就是搬移字了

4. 还有几个寄存器关键字

   EAX, EBX, ECX, EDX, ESI, EDI, EBP, ESP等都是X86汇编语言中CPU上的通用寄存器的名称，是32位的寄存器。如果用C语言来解释，可以把这些寄存器当作变量看待。

   EAX 是"累加器"(accumulator), 它是很多加法乘法指令的缺省寄存器。
   EBX 是"基地址"(base)寄存器, 在内存寻址时存放基地址。
   **ECX 是计数器(counter), 是重复(REP)前缀指令和LOOP指令的内定计数器。**
   EDX 则总是被用来放整数除法产生的余数。
   **ESI/EDI 分别叫做"源/目标索引寄存器"(source/destination index),因为在很多字符串操作指令中, DS:ESI指向源串,而ES:EDI指向目标串.**
   EBP 是"基址指针"(BASE POINTER), 它最经常被用作高级语言函数调用的"框架指针"(frame pointer).

5. 所以上面 =D 代表设置 EDI 目标索引寄存器，=S 是 ESI 源索引寄存器，=c 是 ECX 计数器

   OK，接下来是那些冒号，插入C代码中的一个汇编语言代码片断可以分成四部分，以“：”号加以分隔，其一般形式为：

   ```
   指令部：输出部：输入部：损坏部 
   ```

6. 指令部就是上面几个指令啦无需多言，我们先看输出部

   ：

   =D 这样的语句是对输出部的约束条件：

   常用约束条件一览

   ```
   m, v, o —— 表示内存单元；
   r —— 表示任何寄存器；
   q —— 表示寄存器eax、ebx、ecx、edx之一；
   i, h  —— 表示直接操作数；
   E, F  —— 表示浮点数；
   g —— 表示”任意“；
   a, b, c, d  —— 分表表示要求使用寄存器eax、ebx、ecx和edx；
   S, D  —— 分别表示要求使用寄存器esi和edi；
   I —— 表示常数（0到31）。
   ```

   所以 "=D" (dst_bp), "=S" (src_bp), "=c" (__d0) 就是把 dst_bp 放进 EDI 寄存器， src_bp 放进 ESI 寄存器， __d0 放进 ECX 寄存器。

7. 再来看输入部

   :"0" (dst_bp), "1" (src_bp), "2" (nbytes) 这里的 0, 1, 2 不属于上面约束条件的字母，而是数字，数字代表跟输出部的第 0/1/2 个约束条件是同一个寄存器，那就很好理解了，就是说 EDI 寄存器里面将会输入 dst_bp, ESI 会输入 src_bp，最后的 ECX 会输入 nbytes 这个变量。

8. 最后看损坏部

   这里以“memory”为约束条件，表示操作完成后内存中的内容已有改变，如果原来某个寄存器（也许在本次操作中并未用到）的内容来自内存，则现在可能已经不一致。

9. **总的来说**就是使用movsb指令来按字节搬运字符串，先设置了 EDI, ESI, ECX 几个寄存器的值, 其中EDI寄存器存放拷贝的目的地址，ESI寄存器存放拷贝的源地址，ECX为需要拷贝的字节数。所以最后汇编执行完之后，EDI中的值会保存到dst_bp中，ESI中的值会保存到src_bp中。
