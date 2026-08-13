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

## 5.3

1. &a[i] == a + i

## 5.4

## 5.5

1. 在使用`strncpy`时，不会保证最后的'\0'一定能够复制进入，所以保险的做法是在使用时多留一个位置给'\0
```c
char src[10000] = "something"
char dest[100];
strncpy(dest, src, sizeof(dest) - 1);
dest[sizeof(dest) - 1] = '\0';
```

2. 带有计数限制n的常见做法
```c
// 递减计数
while(n--) {
    ...
}

// 剩余数量，更直观
size_t remain = n;
while (remain > 0) {
    ...
    remain--;
}

// 维护一个边界指针
char *end = p + n;
while (p < n) {
    ...
    p++;
}
```

## 5.6

1. `getline(char *s, int lim)`函数: 默认`'\n'`是字符串的一部分，最后一个位置强制写为`'\0'`，也就是说最多读取lim - 1个字符
```c
int getline(char *s, int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}

```
2. 在遇到计数器的时候尝试使用自减减少计算，有数组时尝试使用自增简化
```c
void writelines(char **lineptr, int nlines)
{
    while (nlines--) 
        printf("%s\n", *lineptr++);
}
```

3. 函数指针：`返回类型 (*指针名)(参数列表);`
    - 函数名本身是地址，保存了该函数机器代码的地址，而函数指针指向这段运算函数的机器码
    - 例如：`int (*fp)(int, int)`表示fp是一个指针，指向一个函数，这个函数接受两个int类型的参数并且返回一个int类型的值，调用时fp(1, 2)或(*fp)(1, 2)
    - typedef简化写法：`typedef int (*Compare)(const void *, const void *);`然后`Compare cmp` 和 `int (*cmp)(const void *, const void *)`等价

4. 快排函数`qsort`
- 第一版，拆分不同职责函数
    ```c
    void swap(void *a, void *b, size_t size)
    {
        unsigned char tmp;  // unsigned char可以访问任意对象的字节表示

        for (size_t i = 0; i < size; i++) {     // 先把通用指针转化为unsigned char再取字节
            tmp = ((unsigned char *)a)[i];
            ((unsigned char *)a)[i] = ((unsigned char *)b)[i];
            ((unsigned char *)b)[i] = tmp;
        }
    }

    void *element(void *base, size_t index, size_t size)   // 直接用void*，因为后面的函数传地址都是void*，可以减少一次类型转换
    {
        return (void *)((char *)base + index * size);
    }

    void qsort(void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *))
    {
        // 元素个数小于2直接返回
        if (nmemb < 2)
            return;
        
        // 将第nmemb / 2 个元素设置为标准值
        size_t pivot = nmemb / 2;

        swap(base, element(base, pivot, size), size);
        size_t last_index = 0;    // 小于基准的区间中的最后一个元素下标

        for (size_t i = 1; i < nmemb; i++) {
            if (cmp(element(base, i, size), 0) < 0) 
                swap(element(base, i, size), element(base, ++last_index, size), size);
        }

        // 换回去
        swap(base, element(base, last_index, size), size);

        // 基准左右分区递归
        if (last_index > 0)
            qsort(base, last_index, size, cmp);
        if (last_index + 1 < nmemb)
            qsort(element(base, last_index + 1, size) , nmemb - last_index - 1, size, cmp);
    }

    int cmp_int(const void *a, const void *b)
    {
        int x = *(const int *)a;
        int y = *(const int *)b;

        if (x < y)
            return -1;
        else if (x > y)
            return 1;
        return 0;
    }

    ```
- 再版，划分嵌套函数，处理“第几个元素”:**外层提供API，内层使用更适合算法的数据结构**
```c
int cmp_int(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y)
        return -1;
    else if (x > y)
        return 1;
    return 0;
}

void swap(void *a, void *b, size_t size)
{
    unsigned char tmp;  // unsigned char可以访问任意对象的字节表示

    for (size_t i = 0; i < size; i++) {     // 先把通用指针转化为unsigned char再取字节
        tmp = ((unsigned char *)a)[i];
        ((unsigned char *)a)[i] = ((unsigned char *)b)[i];
        ((unsigned char *)b)[i] = tmp;
    }
}

void *element(void *base, size_t index, size_t size)   // 直接用void*，因为后面的函数传地址都是void*，可以减少一次类型转换
{
    return (void *)((char *)base + index * size);
}

void qsort(void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *))
{
    // 防止下溢
    if (nmemb < 2)
        return;

    quick_sort(base, 0, nmemb - 1, size, cmp);  //  初始化一个数组并启动排序
}

void quick_sort(void *base, size_t left, size_t right, size_t size, int (*cmp)(const void *,const void *))
{
    if (left >= right)
        return;

    size_t pivot = partition(base, left, right, size, cmp);

    // 防止下溢
    if (pivot > left)
        quick_sort(base, left, pivot - 1, size, cmp);
    if (pivot < right)
        quick_sort(base, pivot + 1, right, size, cmp);
}


size_t partition(void *base, size_t left, size_t right, size_t size, int (*cmp)(const void *,const void *))
{
    size_t last = left;     // 小于基准值的区间的最后一个元素的下标，初始值为0 ，代表该区间为空

    for (size_t i = left + 1; i <= right; i++) {
        if (cmp(element(base, i, size), element(base, left, size)) < 0)
            swap(element(base, i, size), element(base, ++last, size), size);
    }

    swap(element(base, left, size), element(base, last, size), size);

    return last;
}

```

## 5.7

1. 在使用布尔值作为分类标准时，**不用三元运算，直接使用赋值**`    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
`

2. `assert`宏定义封装，实现自定义输出

3. 底层函数负责检查和返回状态，上层决定如何展示：本小节中年份日期转换中进行错误检查，实现是判断年份或者日期不符合时直接printf输出错误信息，但是底层函数值负责检查，所以错误如何处理应该交给上层决定
```c
// 使用错误码来返回转换状态
enum {
    OK,
    INVALID_MONTH,
    INVAILD_DAY
}
// 上层函数根据错误码进一步处理
```

## 5.8

1. **函数内部私有，但是需要长期存在的数据，需要内部static**，比如根据输入的月份返回对应月份的名称，这个名称是在函数内部查表寻找的，但是需要返回，如果不static，那函数内部的名称就是局部变量，返回会发生segmentation fault。 
    - 之后的lexer，如果引入关键字的对照，需要建立keyword表
    ```c
    Token *get_keyword(char *)
    {
        static Token table[] = {
            {"if", TOKEN_IF},
            {"while", TOKEN_WHILE},
            ...
        };
        // 对照lexeme中是否为关键字
        ...
        return &table[i];
    }
    ```


## 5.11



    