#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
/*
a.初始化：从终端读入字符集大小n，以n个字符和n个权值，建立哈夫曼树，并将它存在于hfmTree中。
b.编码：利用建好的哈夫曼树（如不在内存，则从文件hfmTree中读入），对文件TobeTran中的正文进行编码，然后将结果存入文件CodeFile中。
c.译码：利用已建好的哈夫曼树将文件CodeFile中的代码进行译码，结果存入文件TextFile中。
d.印哈夫曼树：将已在内存中的哈夫曼树以直观的方式（树）显示在终端上，同时将此字符形式的哈夫曼树写入文件TreePrint中。
*/
using namespace std;
class Node
{
public:
	int nums;
	char C;
	int LC=-1;
	int RC=-1;

};
class alphabet
{
public:
	vector<char> ch;
	vector<string> code;
	void init(vector<Node> C);//深度优先生成编码表
};
void alphabetInit(vector<char>& ch, vector<string>& code ,vector<Node> C,int head,string tmp)
{
	if (C[head].LC != -1)
	{
		alphabetInit(ch, code, C, C[head].LC, tmp + '0');
		alphabetInit(ch, code, C, C[head].RC, tmp + '1');
	}
	else
	{
		ch.push_back(C[head].C);
		code.push_back(tmp);
	}
}
void alphabet::init(vector<Node> C)
{
	int head = C.size() - 1;
	string tmp;
	alphabetInit(ch,code,C,head,tmp);

}
void fileWrite(string name,vector<Node> C)
{
	ofstream out(name);
	for (int i=0;i<C.size();++i)
	{
		out << to_string(i)+' ' << C[i].C << ' ' << C[i].LC << ' ' << C[i].RC << endl;
	}
	out.close();

}
//将hfm树的数组按顺序输出到指定文件
string read_txt_file(const string& file_path) {
	ifstream file(file_path);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << file_path << std::endl;
		return "";
	}
	string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	file.close();
	return content;
}
//读文件
string encode(string plain, alphabet al)
{
	string res;
	for (auto i : plain)
	{
		for (int j = 0; j < 27; ++j)
		{
			if (i == al.ch[j])
			{
				res += al.code[j];
			}
		}
	}
	return res;
}
//编码，缺编码表排序！！！！
void decode()
{

}//没写完
//加密，还没写！！！！
bool cmpNode(const Node& x, const Node& y)
{
	return x.nums < y.nums;
}
vector<Node> nodeInit(vector<Node> C)
{
	C[0].C = ' ';
	C[0].nums = 186;
	vector<int>tmp = { 186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,63,15,1,48,51,80,23,8,18,1,16,1 };
	for (int i = 1; i <= 26; ++i)
	{
		C[i].C = 'A' + i - 1;
		C[i].nums = tmp[i];
	}
	return C;
}
Node* buildHfmTree(vector<Node>&charSet)
{
	Node* tmp1{};
	int tmp = 0;
	while ( (tmp+2) <= charSet.size())
	{
		sort(charSet.begin(), charSet.end(), cmpNode);
		charSet.push_back({ charSet[tmp].nums + charSet[tmp + 1].nums ,'!',tmp,tmp+1});
		tmp += 2;
	}
	tmp1 = &charSet[charSet.size()-1];
	return tmp1;
}

int main()
{
	vector<Node> test(27);
	test = nodeInit(test);
	Node* head;
	head = buildHfmTree(test);
	alphabet test1;
	test1.init(test);
	fileWrite("hfmTree.txt", test);
	cout << encode(read_txt_file("plain.txt"),test1);
	return 0;
}