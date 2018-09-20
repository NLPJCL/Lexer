本程序实现了NFA-DFA之间的转换、
NFA数据结构选择：
vector initial_state;
vector final_state;
vector input_char;
map<string, map<string, vector>> transform_f;
DFA数据结构选择
map<vector, map<string, vector>> output_transform_f;
vector output_initial_state;
vector<vector> output_final_state;
使用方法：
1.使用示例程序，分别在三个txt文件中。经过测试，分别成功。
2.自己构造。
目前改进的方向：
1.move函数目前是一种对时间复杂度无贡献的扩大空间的办法，只是为了在其返回值中没有重复的元素。
效率问题出在，当 for (int i = 0; i < T.size(); i++)第一次递归就遍历了很多元素，得到了这一次的A的值，
后边还以遍历一次。重复遍历，浪费时间。
2.目前遇到的NFA的初态都是一个，程序也是按照一个来处理，但实际上NFA的初态是个集合。需要更新一下理论知识。
