������ʵ����NFA-DFA֮���ת����
NFA���ݽṹѡ��
vector initial_state;
vector final_state;
vector input_char;
map<string, map<string, vector>> transform_f;
DFA���ݽṹѡ��
map<vector, map<string, vector>> output_transform_f;
vector output_initial_state;
vector<vector> output_final_state;
ʹ�÷�����
1.ʹ��ʾ�����򣬷ֱ�������txt�ļ��С��������ԣ��ֱ�ɹ���
2.�Լ����졣
Ŀǰ�Ľ��ķ���
1.move����Ŀǰ��һ�ֶ�ʱ�临�Ӷ��޹��׵�����ռ�İ취��ֻ��Ϊ�����䷵��ֵ��û���ظ���Ԫ�ء�
Ч��������ڣ��� for (int i = 0; i < T.size(); i++)��һ�εݹ�ͱ����˺ܶ�Ԫ�أ��õ�����һ�ε�A��ֵ��
��߻��Ա���һ�Ρ��ظ��������˷�ʱ�䡣
2.Ŀǰ������NFA�ĳ�̬����һ��������Ҳ�ǰ���һ����������ʵ����NFA�ĳ�̬�Ǹ����ϡ���Ҫ����һ������֪ʶ��
