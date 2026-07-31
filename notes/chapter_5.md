# chapter 5

## 5.1 指针与地址
1. 内存地址用16进制：计算机底层是2进制，但是太长，而十六进制对应四个二进制位，方便表示。
- 一个指针8字节，64位，刚好16个十六进制数字0~f
- 高地址->Stack->Heap->.bss->.data->.rodata->.text->低地址
    - .text: 放机器码
    - .rodata: 只读数据（字符串常量等等）`"Hello world"`
    - .data: 已经初始化的全局变量和静态变量`int x = 10` `static int x = 10 `
    - .bss: 未初始化或初始化为0的全局变量和静态变量`int x` `static int x`
- 高字节和低字节
    - 假设32位整数：0x12345678：1 字节 = 8 bits = 2 个十六进制数。这个数有4字节，0x12是最高有效字节(MSB, Most Significant Byte), 0x78是最低有效字节(LSB, Least Significant Byte).
    - 机器有大小端之分，高字节和低字节在内存里的顺序不一定。大端是高字节放在低地址，小端是低字节放在低地址。大部分是小端机器。
```c
// 例如小端:
0x1000      78
0x1001      56
0x1002      34
0x1003      12
```
2. `*p++ `` (*p)++` `++*p`

3. 通用类型指针`void *`
    - 可以指向任何类型，但是不能直接解引用。显示类型转换
    - 可提升：隐藏类型+比较函数
        - qsort：base+cmp_int()
        - LRU 通用键值对:void *key, void *value, key_equal()

## 5.2 指针与函数参数

1. 栈帧与函数调用

每调用一次函数，在**栈**上为该函数准备一个新的**栈帧**，用于保存该次函数调用所需的信息，例如局部变量、部分参数、返回地址以及需要保存的寄存器等。栈通常向**低地址方向增长**，后调用的函数栈帧通常位于更低的地址。函数返回后，栈帧会被销毁。

CPU 通过**程序计数器 PC**记录下一条要执行的机器指令的地址；在 x86-64 中通常是 `RIP`。执行函数调用时，CPU 会保存返回位置，然后跳转到被调用函数的机器代码地址，并建立相应的栈帧。函数执行 `return` 后，根据保存的返回地址跳回调用者，继续执行后面的指令。

机器指令本身存放在内存中，**x86-64 的指令长度不是固定的**，CPU 会根据机器指令的编码确定其长度，从而找到下一条指令。

2. 二级指针：改谁就传谁的地址：对照python，里面的binding，就是f = g，是f绑定到g绑定的那个函数对象，这两个互不影响，比如修改g，f还是指向原来的那个函数对象。这个指针差不多，就是两个名字一样，但是实际上是不同的name，对新栈帧里面这个函数name修改不会影响原来的。比如想要修改链表的头节点，如果传Node *head，新栈帧里面的head和原来head不一样，只是存的值相同（指向同一个链表），main.head-->link<--new.head，对这个head修改只是影响这个head。所以传**Node **phead**

3. 自定义字符流缓冲区，实现回读
```c
// 超前读入
#define BUFSIZE 128

char buf[BUFSIZE];
int bufp = 0;   // buf中下一个空闲位置

int getch(void)
{
    return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE) 
        printf("ungetch: too many characters\n");
    else 
        buf[bufp++] = c;
}
```

4. 头文件`<ctype.h>`
```c 
// 跳过空白
while (isspace(c = getch()))    
    ;  

// 判断数字
if (isdigit(c)) {...}

// 大小写等等
```