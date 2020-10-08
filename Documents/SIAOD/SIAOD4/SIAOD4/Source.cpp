#include <iostream>
#include <fstream>
using namespace std;

int NEDGES = 0;
int NVERTEX = 0;
const char *FNAME = "Text.txt";
fstream fin(FNAME);

struct Graf
{
	int from;
	int to;
	int weight;
};

int checkin(int arg)
{
	if (arg < 0 or arg > NVERTEX)
	{
		cout << "�� ����� ������� �������\n";
		system("pause");
		return 1;
	}
	else return 0;
}

int checkNEdges()
{
	if (!fin)
	{
		cout << "���� �� ������\n";
		getchar();
		return 1;
	}

	if (fin.peek() == EOF)
	{
		cout << "���� ����\n";
		return 2;
	}

	char *mass = new char[256];
	while (fin.getline(mass, 256))
		NEDGES++;
	delete[]mass;

	fin.clear();
	fin.seekg(0);
	return 0;
}

Graf* read()
{
	Graf *edges = new Graf[NEDGES];
	cout << "и��� �����:\n";
	for (int i = 0; i < NEDGES; i++)
	{
		fin >> edges[i].from;
		fin >> edges[i].to;

		if (NVERTEX < edges[i].from)
			NVERTEX = edges[i].from;
		else if (NVERTEX < edges[i].to)
			NVERTEX = edges[i].to;

		fin >> edges[i].weight;

		cout << "�� " << edges[i].from << " � " << edges[i].to << " ����� � ����� " << edges[i].weight << endl;
	}
	return edges;
}

void dinamicProgramming(int start, int finish, Graf *edges)
{
	long int *path = new long int[NVERTEX+1];

	for (int i = 0; i < NVERTEX+1; i++)
		path[i] = INT_MAX;

	path[start] = 0;
	int *showPath = new int[NEDGES];

	for (int i = 0; i < NVERTEX; i++)
		for (int j = 0; j < NEDGES; j++)
			if (path[edges[j].to] > path[edges[j].from] + edges[j].weight)
			{
				path[edges[j].to] = path[edges[j].from] + edges[j].weight;
				showPath[edges[j].to] = edges[j].from;
			}

	cout << "\n\t\t\t����� ������������� ����������������\n";
	if (path[finish] == INT_MAX)
		cout << "�� " << start << " � " << finish << ": ���� ���" << endl;
	else
	{
		cout << "���� �� " << start << " � " << finish << " ����� ���: " << path[finish] << endl;

		cout << finish;
		for (int cur = showPath[finish]; cur != start; cur = showPath[cur])
			cout << " <- " << cur;

		cout << " <- " << start << endl;
	}
}

int getTree(int x, int *tree)
{
	if (x == tree[x])
		return x;
	else return tree[x] = getTree(tree[x], tree);
}

bool unite(int x, int y, int *tree)
{
	x = getTree(x, tree);
	y = getTree(y, tree);

	if (x == y)
		return false;
	tree[x] = y;
	return true;
}

void sort(Graf *edges)
{
	Graf Temp;

	for (int i = 0; i < NEDGES; i++)
		for (int j = 0; j < NEDGES; j++)
			if (edges[j + 1].weight < edges[j].weight)
			{
				Temp = edges[j + 1];
				edges[j + 1] = edges[j];
				edges[j] = Temp;
			}
}

void kruskal(Graf *edges)
{
	sort(edges);

	int *tree = new int[NVERTEX+1];
	for (int i = 0; i < NVERTEX+1; i++)
		tree[i] = i;

	Graf *ost = new Graf[NEDGES];
	int k = 0;
	for (int i = 0; i < NEDGES; i++)
	{
		int x = edges[i].from;
		int y = edges[i].to;

		if (unite(x, y, tree))
		{
			ost[k] = edges[i];
			k++;
		}
	}

	int sum = 0;
	cout << "\n\t\t\t�������� ��������\nи��� ��������� ������: \n";
	for (int size = 0; size < k; size++)
	{
		sum += ost[size].weight;
		cout << ost[size].from << "<->" << ost[size].to << endl;
	}

	cout << "��� ��������� ������: " << sum << "\n";
}

void main()
{
	setlocale(LC_ALL, "rus");

	if (checkNEdges())
		return;
	
	Graf *edges = new Graf[NEDGES];
	edges = read();
	
	int start;
	int finish;

	cout << "\n\n������� ������� ������: ";
	cin >> start;
	if (checkin(start))
		return;

	cout << "������� �������� �������: ";
	cin >> finish;
	if (checkin(finish))
		return;
	
	dinamicProgramming(start, finish, edges);
	kruskal(edges);

	system("pause");
	delete[]edges;
}
