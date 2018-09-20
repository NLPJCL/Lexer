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
			cout << "请输入要转换的NFA的文件名" << endl;
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
			cout << "请输入要保存NFA的文件名" << endl;
			cin >> file_name;
			cout << "请输入NFA的初态集:Ctrl+z加回车结束输入" << endl;
			string initial_state_0;
			while (cin >> initial_state_0)
			{
				initial_state.push_back(initial_state_0);
			}
			cin.clear();
			cout << "请输入NFA的终态集:Ctrl+z加回车结束输入" << endl;
			string final_state_0;
			while (cin >> final_state_0)
			{
				final_state.push_back(final_state_0);
			}
			cin.clear();
			cout << "请输入NFA的输入符号集:Ctrl+z加回车结束输入" << endl;
			string input_char_0;
			while (cin >> input_char_0)
			{
				input_char.push_back(input_char_0);
			}
			cin.clear();
			cout << "请输入NFA的转移函数的个数:" << endl;
			int t;
			cin >> t;
			cout << "请输入NFA的转移函数:" << endl;
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
void move(vector<string> T, string &char_0, map<string, map<string, vector<string>>> &transform_f, vector<string> &A)
//状态T中的某一个状态经过一次char_0弧可以到达的状态全体。（经过char_0前可以经过k弧。）
//tramsform_f是转移函数。A是状态全体。Q是避免重复加入的函数。
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
						A.push_back(w0->second[j]);
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

	//DFA相关状态。
	map<vector<string>, map<string, vector<string>>> output_transform_f;
	vector<string> output_initial_state;
	vector<vector<string>> output_final_state;
	set<string> search;//来检测是否为终态
	init(initial_state, final_state, input_char, transform_f);
	cout << "NFA的初态：";
	for (int i = 0; i < initial_state.size(); i++)
	{
		cout << initial_state[i] << " ";
	}
	cout << endl;
	cout << "NFA的终态：";
	for (int i = 0; i < final_state.size(); i++)
	{
		cout << final_state[i] << " ";
		search.insert(final_state[i]);
	}
	cout << endl;
	cout << "NFA的转移函数是：" << endl;
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
	//求出初态。
	vector<string> B = initial_state;
	closure(initial_state, transform_f, B);
	sort(B.begin(), B.end());
	deque<vector<string>> C;//当stack用。
	C.push_back(B);
	set<vector<string>> sign;//标记符号。
	sign.insert(B);

	vector<string> T;
	output_initial_state = B;//DFA的初始状态。
	while (C.size() != 0)
	{
		T = C.front();
		C.pop_front();
		//DFA的终态。
		for (auto q = search.begin(); q != search.end(); q++)
		{
			if (binary_search(T.begin(), T.end(), *q))
			{
				output_final_state.push_back(T);
			}
		}
		map<string, vector<string>> W;
		for (int i = 0; i < input_char.size(); i++)
		{
			vector<string> A;
			move(T, input_char[i], transform_f, A);
			sort(A.begin(), A.end());
			A.erase(unique(A.begin(), A.end()), A.end());
			vector<string> Z = A;
			closure(A, transform_f, Z);
			sort(Z.begin(), Z.end());
			if (Z.size() == 0)
			{
				Z.push_back("111111");
				W[input_char[i]] = Z;
				continue;
			}
			if (sign.find(Z) == sign.end())
			{
				sign.insert(Z);
				C.push_front(Z);
			}

			W[input_char[i]] = Z;
		}
		output_transform_f[T] = W;
	}
	cout << "DFA的初态：";
	for (int i = 0; i < output_initial_state.size(); i++)
	{
		cout << output_initial_state[i] << " ";
	}
	cout << endl;
	cout << "DFA的终态：";
	sort(output_final_state.begin(), output_final_state.end());
	for (int i = 0; i < output_final_state.size(); i++)
	{
		for (int j = 0; j < output_final_state[i].size(); j++)
		{
			cout << output_final_state[i][j] << " ";
		}
	}
	cout << endl;
	cout << "DFA的转移函数是(111111为空集)：" << endl;
	for (auto w = output_transform_f.begin(); w != output_transform_f.end(); w++)
	{
		for (auto w0 = w->second.begin(); w0 != w->second.end(); w0++)
		{
			cout << "f(";
			for (int i = 0; i < w->first.size(); i++)
			{
				cout << w->first[i] << " ";
			}
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