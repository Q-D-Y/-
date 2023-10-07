#include <iostream>
#include <vector>
#include <algorithm>
/*
要在n个城市间建立通信网络，任意两城市之间可通过单跳直接通信，也可通过多跳间接通信，例如城市A与C要实现通信，
可直接建立A与C的通信链路，也可通过中间城市B，分别建立A与B以及B与C的通信链路。在这n个城市中某些城市对数据传输的效率和安全性要求级别较高，
因此需要通过编译码和加解密技术确保数据传输的高效率和高可靠性。基于以上背景和描述，请回答以下问题并用代码实现相应的功能。
1）假设要在n个城市间建立一个简单的通信网络，实现n个城市间可自由通信，基于该要求只需建立n-1条链路即可。
已知任意两个城市之间建立通信链路的经济代价，那么如何以最低的经济代价建设这个通信网？
（这里的经济代价可考虑为任意两个城市之间建立一条通信链路的成本）请用至少两种算法设计一个经济代价最小的通信网，
并对两种不同算法的效率进行分析。基于设计的算法，请根据图1给出的城市网络经济代价验证算法的正确性。
*/
using namespace std;

class graph
{
public:
	int N_Nums = 0;//节点数
	int E_Nums = 0;//边数
	vector<int> Note = {};//节点
	vector<vector<int>> Edge;//边
	vector<vector<int>> Min_Tree = { {} };//最小通信网
};
bool cmp(vector<int> x, vector<int> y)
{
	return x[2] < y[2];
}
graph graphinit(graph c)
{
	cin >> c.N_Nums;
	cin >> c.E_Nums;
	for (int i = 1; i <= c.N_Nums; ++i) {
		c.Note.push_back(i);
	}
	for (int i = 0; i < c.E_Nums; ++i) {
		c.Edge.push_back({});
		for (int j = 0; j < 3; ++j) {
			int T;
			cin >> T;
			c.Edge[i].push_back(T);
		}
	}
	sort(c.Edge.begin(), c.Edge.end(), cmp);
	return c;
}


graph Kruskal(graph c)
{
	vector<vector<int>> groups = {};
	for (int i = 0; i < c.N_Nums+1; ++i)
	{
		groups.push_back({i,i});
	}
	//groups记录分组情况，groups[x][y],x代表节点号,y代表节点的分组号
	int E_count = 0;
	for (int i = 0; i < c.E_Nums; ++i)
	{
		i = i % c.E_Nums;
		if (groups[c.Edge[i][0]][1] != groups[c.Edge[i][1]][1])
		{
			int tmpMin = min(groups[c.Edge[i][0]][1], groups[c.Edge[i][1]][1]);
			for (int k = 0; k < c.N_Nums+1; ++k)
			{
				if (k == c.Edge[i][0] || k == c.Edge[i][1]) continue;
				if (groups[k][1] == groups[c.Edge[i][0]][1] || groups[k][1] == groups[c.Edge[i][1]][1])
				{
					groups[k][1] = tmpMin;
				}
			}
			groups[c.Edge[i][0]][1] = groups[c.Edge[i][1]][1] = tmpMin;
			c.Min_Tree.push_back(c.Edge[i]);
			++E_count;
		}
		if (E_count == c.N_Nums - 1)
		{
			return c;
		}
	}
}
graph Prim(graph c)
{
	vector<bool>avai(c.N_Nums+1,true);//分组，true代表未选中，false代表已选中
	avai[1] = false;
	int minDis = INT_MAX;//记录最小值
	int edgeNo = 0;//记录选中的最小边
	for (int i = 0; i < c.N_Nums - 1; ++i)
	{
		for (int k = 0; k < c.E_Nums; ++k)
		{
			if (avai[c.Edge[k][0]]^avai[c.Edge[k][1]])//前后两节点不同时可用或不可用时说明一个在蓝区另一个在白区
			{
				if (minDis > c.Edge[k][2])
				{
					minDis = c.Edge[k][2];
					edgeNo = k;
				}
				
			}
		}
		c.Min_Tree.push_back(c.Edge[edgeNo]);
		avai[c.Edge[edgeNo][0]] = avai[c.Edge[edgeNo][1]] = false;
		minDis = INT_MAX;
		edgeNo = 0;
	}
	return c;
}
/*
int main()
{
	graph cities1;
	graph cities2;
	cities1 = cities2 = graphinit(cities1);
	cities1 = Kruskal(cities1);
	cities2 = Prim(cities2);
	return 0;
}
*/