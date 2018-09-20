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
			cout << "������Ҫת����DFA���ļ���" << endl;
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
			cout << "������Ҫ����DFA���ļ���" << endl;
			cin >> file_name;
			cout << "������DFA�ĳ�̬��:Ctrl+z�ӻس���������" << endl;
			string initial_state_0;
			while (cin >> initial_state_0)
			{
				initial_state.push_back(initial_state_0);
			}
			cin.clear();
			cout << "������DFA����̬��:Ctrl+z�ӻس���������" << endl;
			string final_state_0;
			while (cin >> final_state_0)
			{
				final_state.push_back(final_state_0);
			}
			cin.clear();
			cout << "������DFA��������ż�:Ctrl+z�ӻس���������" << endl;
			string input_char_0;
			while (cin >> input_char_0)
			{
				input_char.push_back(input_char_0);
			}
			cin.clear();
			cout << "������DFA��ת�ƺ����ĸ���:" << endl;
			int t;
			cin >> t;
			cout << "������DFA��ת�ƺ���:" << endl;
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
void move(vector<string> T, string &char_0, map<string, map<string, vector<string>>> &transform_f, map<string, string> &A)
//״̬T�е�ĳһ��״̬����һ��char_0�����Ե����״̬ȫ�塣������char_0ǰ���Ծ���k������
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
	//NFA���״̬��
	vector<string> initial_state;
	vector<string> final_state;
	vector<string> input_char;
	map<string, map<string, vector<string>>> transform_f;
	init(initial_state, final_state, input_char, transform_f);
	cout << "DFA�ĳ�̬��";
	for (int i = 0; i < initial_state.size(); i++)
	{
		cout << initial_state[i] << " ";
	}
	cout << endl;
	cout << "DFA����̬��";
	for (int i = 0; i < final_state.size(); i++)
	{
		cout << final_state[i] << " ";
	}
	cout << endl;
	cout << "DFA��ת�ƺ����ǣ�" << endl;
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
	//�ɽ���̬�Ͳ��ɽ���̬��
	set<vector<string>> P;
	P.insert(final_state);
	vector<string> NO_Acceptable;
	//cout << "���ɽ���̬��" ;
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
	//�ָ��
	int w3 = 0;
	for (auto z = P.begin(); z != P.end();)
	{
		if (z->size() != 1)
		{
			for (int q = 0; q < input_char.size(); q++)
			{
				map<string, string> A;
				move(*z, input_char[q], transform_f, A);
				vector<vector<string>> w0;//�����洢��ͬ�������Ϣ��
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
	//�任ת�ƺ�����ϵ��
	for (auto w = P.begin(); w != P.end(); w++)
	{
		string i, j;
		if (w->size() != 1)//ֻ��������Ԫ�صĺϲ���
		{
			auto z = w->begin();
			i = *z;
			z++;
			j = *z;
			//��j������״̬�Ľڵ㣬ת�Ƶ�i���ϡ�
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
			//�������ڵ㵽j��״̬��ת�Ƶ�i���ϡ�
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
	cout << "����֮��DFA��ת�ƺ����ǣ�" << endl;
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
