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
//ѡ��ʹ��ʾ�������������DFA�ĳ�̬������̬����������ţ���ת��������
{
	int i = 0;
	while (1)
	{
		cout << "��ѡ��\n1��ʹ��ʾ�����򣬼�readme��\n2���Լ�����NFA" << endl;
		cin >> i;
		if (i == 1)
		{
			string file_name;
			cout << "������Ҫת����NFA���ļ���" << endl;
			cin >> file_name;
			ifstream f(file_name);
			if (!f)
			{
				cout << "�������" << endl;
			}
			string line;
			//��ȡ��̬���ϡ�
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
			//��ȡ��̬���ϡ�
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
			//��ȡ�����ַ�����
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
			//��ȡת��������
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
			cout << "������Ҫ����NFA���ļ���" << endl;
			cin >> file_name;
			cout << "������NFA�ĳ�̬��:Ctrl+z�ӻس���������" << endl;
			string initial_state_0;
			while (cin >> initial_state_0)
			{
				initial_state.push_back(initial_state_0);
			}
			cin.clear();
			cout << "������NFA����̬��:Ctrl+z�ӻس���������" << endl;
			string final_state_0;
			while (cin >> final_state_0)
			{
				final_state.push_back(final_state_0);
			}
			cin.clear();
			cout << "������NFA��������ż�:Ctrl+z�ӻس���������" << endl;
			string input_char_0;
			while (cin >> input_char_0)
			{
				input_char.push_back(input_char_0);
			}
			cin.clear();
			cout << "������NFA��ת�ƺ����ĸ���:" << endl;
			int t;
			cin >> t;
			cout << "������NFA��ת�ƺ���:" << endl;
			string former_state = "1234567";
			map<string, vector<string>> transform;
			string state;
			for (int q = 0; q <t; q++)
			{

				string char_0;
				vector<string> output_states;
				string output_state;
				cout << "�������ʼ��״̬" << endl;
				cin >> state;
				cout << "�����������ַ�" << endl;
				cin >> char_0;
				cout << "���������״̬����Ctrl+z�ӻس���������" << endl;
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
			//�����ʼ״̬���ļ���
			for (int i = 0; i < initial_state.size(); i++)
			{
				save_trans_f << initial_state[i] << "\t";

			}
			save_trans_f << endl;
			//����ֹ״̬���浽�ļ���
			for (int i = 0; i < final_state.size(); i++)
			{
				save_trans_f << final_state[i] << "\t";

			}
			save_trans_f << endl;
			//�������ַ������浽�ļ���
			for (int i = 0; i < input_char.size(); i++)
			{
				save_trans_f << input_char[i] << "\t";

			}
			save_trans_f << endl;
			//��ת�ƺ������浽�ļ���
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
//����A����������һ��Ԫ�ؾ���������K�����ջ�)���ܵ����״̬����B
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
//״̬T�е�ĳһ��״̬����һ��char_0�����Ե����״̬ȫ�塣������char_0ǰ���Ծ���k������
//tramsform_f��ת�ƺ�����A��״̬ȫ�塣Q�Ǳ����ظ�����ĺ�����
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
	//NFA���״̬��
	vector<string> initial_state;
	vector<string> final_state;
	vector<string> input_char;
	map<string, map<string, vector<string>>> transform_f;

	//DFA���״̬��
	map<vector<string>, map<string, vector<string>>> output_transform_f;
	vector<string> output_initial_state;
	vector<vector<string>> output_final_state;
	set<string> search;//������Ƿ�Ϊ��̬
	init(initial_state, final_state, input_char, transform_f);
	cout << "NFA�ĳ�̬��";
	for (int i = 0; i < initial_state.size(); i++)
	{
		cout << initial_state[i] << " ";
	}
	cout << endl;
	cout << "NFA����̬��";
	for (int i = 0; i < final_state.size(); i++)
	{
		cout << final_state[i] << " ";
		search.insert(final_state[i]);
	}
	cout << endl;
	cout << "NFA��ת�ƺ����ǣ�" << endl;
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
	//�����̬��
	vector<string> B = initial_state;
	closure(initial_state, transform_f, B);
	sort(B.begin(), B.end());
	deque<vector<string>> C;//��stack�á�
	C.push_back(B);
	set<vector<string>> sign;//��Ƿ��š�
	sign.insert(B);

	vector<string> T;
	output_initial_state = B;//DFA�ĳ�ʼ״̬��
	while (C.size() != 0)
	{
		T = C.front();
		C.pop_front();
		//DFA����̬��
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
	cout << "DFA�ĳ�̬��";
	for (int i = 0; i < output_initial_state.size(); i++)
	{
		cout << output_initial_state[i] << " ";
	}
	cout << endl;
	cout << "DFA����̬��";
	sort(output_final_state.begin(), output_final_state.end());
	for (int i = 0; i < output_final_state.size(); i++)
	{
		for (int j = 0; j < output_final_state[i].size(); j++)
		{
			cout << output_final_state[i][j] << " ";
		}
	}
	cout << endl;
	cout << "DFA��ת�ƺ�����(111111Ϊ�ռ�)��" << endl;
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