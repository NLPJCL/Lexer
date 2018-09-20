#include<deque>
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<set>
#include<algorithm>
using namespace std;
void init(vector<string> &initial_state, vector<string> &final_state, vector<string> &input_char, map<string, map<string, vector<string>>> &transform_f)
//选择使用示例程序或者输入DFA的初态集，终态集，输入符号，和转换函数。
{
	int i = 0;
	while (1)
	{
		cout << "请选择：\n1：使用示例程序，见readme。\n2：自己构造NFA" << endl;
		cin >> i;
		if (i == 1)
		{
			string file_name;
			cout << "请输入要转换的DFA的文件名" << endl;
			cin >> file_name;
			ifstream f(file_name);
			if (!f)
			{
				cout << "输入错误" << endl;
			}
			string line;
			//获取初态集合。
			getline(f, line);
			int i0 = line.find("\t");
			initial_state.push_back(line.substr(0, i0));
			while (1)
			{
				int i = i0;
				i0 = line.find("\t", i + 1);
				if (i0 == line.npos)
				{
					break;
				}
				initial_state.push_back(line.substr(i + 1, i0 - i - 1));
			}
			//获取终态集合。
			getline(f, line);
			i0 = line.find("\t");
			final_state.push_back(line.substr(0, i0));
			while (1)
			{
				int i = i0;
				i0 = line.find("\t", i + 1);
				if (i0 == line.npos)
				{
					break;
				}
				final_state.push_back(line.substr(i + 1, i0 - i - 1));
			}
			//获取输入字符集合
			getline(f, line);
			i0 = line.find("\t");
			input_char.push_back(line.substr(0, i0));
			while (1)
			{
				int i = i0;
				i0 = line.find("\t", i + 1);
				if (i0 == line.npos)
				{
					break;
				}
				input_char.push_back(line.substr(i + 1, i0 - i - 1));
			}
			//获取转换函数。
			string former_state = initial_state[0];
			map<string, vector<string>> transform;
			string state;
			while (getline(f, line))
			{
				int i = line.find("\t");
				state = line.substr(0, i);
				int i0 = line.find(" ", i + 1);
				string char_0 = line.substr(i + 1, i0 - i - 1);
				vector<string> output_states;
				if (state != former_state)
				{
					transform_f[former_state] = transform;
					transform.clear();
				}
				while (1)
				{
					int i = i0;
					i0 = line.find(" ", i + 1);
					if (i0 == line.npos)
					{
						break;
					}
					output_states.push_back(line.substr(i + 1, i0 - i - 1));
				}
				former_state = state;
				transform[char_0] = output_states;
			}
			transform_f[former_state] = transform;
			break;
		}
		else if (i == 2)
		{
			string file_name;
			cout << "请输入要保存DFA的文件名" << endl;
			cin >> file_name;
			cout << "请输入DFA的初态集:Ctrl+z加回车结束输入" << endl;
			string initial_state_0;
			while (cin >> initial_state_0)
			{
				initial_state.push_back(initial_state_0);
			}
			cin.clear();
			cout << "请输入DFA的终态集:Ctrl+z加回车结束输入" << endl;
			string final_state_0;
			while (cin >> final_state_0)
			{
				final_state.push_back(final_state_0);
			}
			cin.clear();
			cout << "请输入DFA的输入符号集:Ctrl+z加回车结束输入" << endl;
			string input_char_0;
			while (cin >> input_char_0)
			{
				input_char.push_back(input_char_0);
			}
			cin.clear();
			cout << "请输入DFA的转移函数的个数:" << endl;
			int t;
			cin >> t;
			cout << "请输入DFA的转移函数:" << endl;
			string former_state = "1234567";
			map<string, vector<string>> transform;
			string state;
			for (int q = 0; q <t; q++)
			{

				string char_0;
				vector<string> output_states;
				string output_state;
				cout << "请输入初始的状态" << endl;
				cin >> state;
				cout << "请输入输入字符" << endl;
				cin >> char_0;
				cout << "请输入输出状态集，Ctrl+z加回车结束输入" << endl;
				if (state != former_state)
				{
					transform_f[former_state] = transform;
					transform.clear();
				}
				while ((cin >> output_state))//
				{
					output_states.push_back(output_state);
				}
				cin.clear();
				transform[char_0] = output_states;
				former_state = state;
			}
			transform_f[former_state] = transform;
			ofstream save_trans_f(file_name);
			//储存初始状态到文件中
			for (int i = 0; i < initial_state.size(); i++)
			{
				save_trans_f << initial_state[i] << "\t";

			}
			save_trans_f << endl;
			//把终止状态储存到文件中
			for (int i = 0; i < final_state.size(); i++)
			{
				save_trans_f << final_state[i] << "\t";

			}
			save_trans_f << endl;
			//把输入字符串储存到文件中
			for (int i = 0; i < input_char.size(); i++)
			{
				save_trans_f << input_char[i] << "\t";

			}
			save_trans_f << endl;
			//把转移函数储存到文件中
			for (auto w = transform_f.begin(); w != transform_f.end(); w++)
			{
				for (auto w0 = w->second.begin(); w0 != w->second.end(); w0++)
				{
					save_trans_f << w->first << "\t" << w0->first << " ";
					for (int q = 0; q < w0->second.size(); q++)
					{
						save_trans_f << w0->second[q] << " ";
					}
					save_trans_f << endl;
				}
			}
			break;
		}
		else;
	}

}
void closure(vector<string> A, map<string, map<string, vector<string>>> &transform_f, vector<string> &B)
//返回A集合中任意一个元素经过任意条K弧（空弧)所能到达的状态集合B
{
	if (A.size() != 0)
	{
		vector<string> C;
		for (int i = 0; i < A.size(); i++)
		{
			auto w = transform_f.find(A[i]);
			if (w != transform_f.end())
			{
				auto w0 = w->second.find("k");
				if (w0 != w->second.end())
				{
					for (int j = 0; j < w0->second.size(); j++)
					{
						B.push_back(w0->second[j]);
						C.push_back(w0->second[j]);
					}
				}
			}
		}
		A = C;
		closure(A, transform_f, B);
	}
	else
	{
		return;
	}
}
void move(vector<string> T, string &char_0, map<string, map<string, vector<string>>> &transform_f, map<string, string> &A)
//状态T中的某一个状态经过一次char_0弧可以到达的状态全体。（经过char_0前可以经过k弧。）
{

	for (int i = 0; i < T.size(); i++)
	{

		vector<string> C;
		auto w = transform_f.find(T[i]);
		if (w != transform_f.end())
		{
			auto w0 = w->second.find("k");
			if (w0 != w->second.end())
			{
				for (int j = 0; j < w0->second.size(); j++)
				{
					C.push_back(w0->second[j]);
				}
				move(C, char_0, transform_f, A);
			}
			else
			{
				w0 = w->second.find(char_0);
				if (w0 != w->second.end())
				{
					for (int j = 0; j < w0->second.size(); j++)
					{

						A[w->first] = w0->second[j];
					}
				}
			}
		}
	}
}
int main()
{
	//NFA相关状态。
	vector<string> initial_state;
	vector<string> final_state;
	vector<string> input_char;
	map<string, map<string, vector<string>>> transform_f;
	init(initial_state, final_state, input_char, transform_f);
	cout << "DFA的初态：";
	for (int i = 0; i < initial_state.size(); i++)
	{
		cout << initial_state[i] << " ";
	}
	cout << endl;
	cout << "DFA的终态：";
	for (int i = 0; i < final_state.size(); i++)
	{
		cout << final_state[i] << " ";
	}
	cout << endl;
	cout << "DFA的转移函数是：" << endl;
	for (auto w = transform_f.begin(); w != transform_f.end(); w++)
	{
		for (auto w0 = w->second.begin(); w0 != w->second.end(); w0++)
		{
			cout << "f(" << w->first;
			cout << "," << w0->first << ")->";
			for (int i = 0; i < w0->second.size(); i++)
			{
				cout << w0->second[i] << " ";
			}
			cout << endl;
		}
	}
	//可接受态和不可接受态。
	set<vector<string>> P;
	P.insert(final_state);
	vector<string> NO_Acceptable;
	//cout << "不可接受态：" ;
	for (auto w = transform_f.begin(); w != transform_f.end(); w++)
	{
		if (binary_search(final_state.begin(), final_state.end(), w->first))
		{
			continue;
		}
		NO_Acceptable.push_back(w->first);
	}
	NO_Acceptable.erase(unique(NO_Acceptable.begin(), NO_Acceptable.end()), NO_Acceptable.end());
	sort(NO_Acceptable.begin(), NO_Acceptable.end());
	P.insert(NO_Acceptable);
	//分割法。
	int w3 = 0;
	for (auto z = P.begin(); z != P.end();)
	{
		if (z->size() != 1)
		{
			for (int q = 0; q < input_char.size(); q++)
			{
				map<string, string> A;
				move(*z, input_char[q], transform_f, A);
				vector<vector<string>> w0;//用来存储不同分组的信息。
				for (auto w = P.begin(); w != P.end(); w++)
				{
					vector<string> w1;
					for (auto e = A.begin(); e != A.end(); e++)
					{
						if (binary_search(w->begin(), w->end(), e->second))
						{
							w1.push_back(e->first);
						}
					}
					if (w1.size() != 0)
					{
						w0.push_back(w1);
					}
				}
				if (w0.size() != 1)
				{
					P.erase(*z);
					for (auto w = w0.begin(); w != w0.end(); w++)
					{
						P.insert(*w);
					}
					break;
				}
			}
		}
		z = P.begin();
		for (int i = 0; i < w3; i++)
		{
			z++;
		}
		w3++;
	}
	//变换转移函数关系。
	for (auto w = P.begin(); w != P.end(); w++)
	{
		string i, j;
		if (w->size() != 1)//只考虑两个元素的合并。
		{
			auto z = w->begin();
			i = *z;
			z++;
			j = *z;
			//将j到其他状态的节点，转移到i身上。
			auto  q = transform_f.find(j);
			auto q0 = transform_f.find(i);
			for (int e = 0; e < input_char.size(); e++)
			{
				auto z0 = q0->second.find(input_char[e]);
				auto z = q->second.find(input_char[e]);
				if (z != q->second.end())
				{
					if (z->second[0] != z0->second[0])
					{
						z0->second.push_back(z->second[0]);
					}
				}
			}
			transform_f.erase(j);
			//将其他节点到j的状态，转移到i身上。
			for (auto w0 = transform_f.begin(); w0 != transform_f.end(); w0++)
			{
				for (auto w1 = w0->second.begin(); w1 != w0->second.end(); w1++)
				{
					for (int y = 0; y < w1->second.size(); y++)
					{
						if (w1->second[y] == j)
						{
							w1->second[y] = i;
						}
					}
					w1->second.erase(unique(w1->second.begin(), w1->second.end()), w1->second.end());
				}
			}
		}
	} 
	cout << "化简之后DFA的转移函数是：" << endl;
	for (auto w = transform_f.begin(); w != transform_f.end(); w++)
	{
		for (auto w0 = w->second.begin(); w0 != w->second.end(); w0++)
		{
			cout << "f(" << w->first;
			cout << "," << w0->first << ")->";
			for (int i = 0; i < w0->second.size(); i++)
			{
				cout << w0->second[i] << " ";
			}
			cout << endl;
		}
	}
	system("pause");
	return 0;
}
