main.cpp

是两个程序的集合。

DFA-NFA.h 

本程序实现了NFA-DFA之间的转换、

使用方法：

1.使用示例程序，输入文件名。分别在三个txt文件（1 f.txt   2 NFA.txt 3 NFA_3.txt）中。经过测试，分别成功。

2.自己构造。

![image](https://github.com/NLPJCL/Lexer/blob/master/%E8%AF%8D%E6%B3%95%E5%88%86%E6%9E%90%E7%B3%BB%E5%88%97%E7%A8%8B%E5%BA%8F/1.png)
目前改进的方向：

1.move函数目前是一种对时间复杂度无贡献的方法。

（在move中会重复遍历）会增加重复节点，之后知识用STL的去重函数去重，可以优化。

2.目前遇到的NFA的初态都是一个，程序也是按照一个来处理，但实际上NFA的初态是个集合。需要更新一下理论知识。

NFA.h化简（初始版本测试程序较少，发现有bug可联系我QQ：953977230）

使用方法：

1.使用示例程序，输入文件名(DFA.txt)。经过测试，成功。

2.自己构造。

![image](https://github.com/NLPJCL/Lexer/blob/master/%E8%AF%8D%E6%B3%95%E5%88%86%E6%9E%90%E7%B3%BB%E5%88%97%E7%A8%8B%E5%BA%8F/clipboard.png)



