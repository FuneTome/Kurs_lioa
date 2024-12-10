#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int** G, len, *pairU, *pairV, *dist;
vector <int> u, v;

void printG() {
	cout << "\t���� G: \n\n";
	for (int i = 0; i < len; i++) {
		cout << "\t";
		for (int j = 0; j < len; j++) {
			cout << G[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "\n\t������� ������������ U: ";
	for (int i = 0; i < u.size(); i++) cout << u[i] << " ";
	cout << "\n\t������� ������������ V: ";
	for (int i = 0; i < v.size(); i++) cout << v[i] << " ";
}

//������� �������� � ������ ������������ ����������� �������
bool find_part(int s) { 
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == s) return true;
	}
	return false;
}

void creatG() {
	//���� ����� �����
	while(1){
		cout << "\n\t������� ����� �����: ";
		cin >> len;
		if (len <= 1) cout << "\n\t����������� ��������� ������, ���������� �����!\n";
		else break;
	}
	srand(time(0));
	//������������� ������ �� �������������
	while(1){
		for (int i = 0; i < len; i++) {
			if (rand() % 11 > 5) u.push_back(i + 1);
			else v.push_back(i + 1);
		}
		if (v.size() < 1 || u.size() < 1 || u.size() < v.size()) { u.clear(); v.clear(); continue; }
		else break;
	}
	//������������� � ���������� �������
	G = new int* [len];
	for (int i = 0; i < len; i++) {
		G[i] = new int[len];
	}
	for (int i = 0; i < len; i++)
		for (int j = 0; j < len; j++)
			G[i][j] = 0;

	//���������� ����� ����� ���������
	vector <int>::iterator j;
	srand(time(0));
	for (int i = 0; i < len; i++) {
		if (find_part(i + 1)){
			for (j = u.begin(); j != u.end(); ++j) {
				int s = *j;
				if (s - 1 == i) continue;
				if (rand() % 11 < 5) G[i][s - 1] = G[s - 1][i] = 1;
			}
		}
		else {
			for (j = v.begin(); j != v.end(); ++j) {
				int s = *j;
				if (s - 1 == i) continue;
				if (rand() % 11 < 5)	G[i][s - 1] = G[s - 1][i] = 1;
			}
		}
	}
	printG();
}

bool bfs(){
	queue <int> q;
	for (int i = 1; i <= u.size(); i++) {
		//���� ��������� ������� �� ��������� � �������
		if (pairU[i] == 0) {
			dist[i] = 0;
			q.push(i);
		}
		else dist[i] = INT_MAX;
	}
	dist[0] = INT_MAX;
	while (!q.empty()) {
		int s = q.front();
		q.pop();
		//���� ������� �� ����� ���� � ����� ���������� ����� �������� ���� � ����
		if (dist[s] < dist[0]) {
			vector <int>::iterator i;
			for (i = u.begin(); i != u.end(); ++i) {
				int ss = *i, k = 0;
				for (int j = 0; j < len; j++) {
					if (G[ss - 1][j] == 1) {
						if (dist[pairV[k]] == INT_MAX) {
							dist[pairV[k]] = dist[s] + 1;
							q.push(pairV[k]);
						}
						k++;
					}
				}
			}
		}
	}
	return (dist[0] != INT_MAX);
}

bool dfs(int t){
	if (t != 0) {
		vector <int>::iterator i;
		for (i = u.begin(); i != u.end(); ++i) {
			int ss = *i, k = 0;
			for (int j = 0; j < len; j++) {
				if (G[ss - 1][j] == 1) {
					if(dist[pairV[k]] == dist[t - 1] + 1){
						if (dfs(pairV[k]) == true) {
							pairV[k] = t;
							pairU[t] = j;
							return true;
						}
					}
					k++;
				}
			}
		}
		dist[t] = 0;
		return false;
	}
	return true;
}

int Hopkroft_Karp_alg(){
	//1 � 2 ������� ������ ���� � ���������, 3 - ���������� ����� ������ �������� ��������� 
	pairU = new int[u.size() + 1], pairV = new int[v.size() + 1], dist = new int[u.size() + 1];
	for (int i = 0; i <= u.size(); i++) pairU[i] = 0;
	for (int i = 0; i <= v.size(); i++) pairV[i] = 0;
	
	//������������� ����������
	int result = 0;
	//���� ���� ������������� ����
	while (bfs()){
		for (int i = 1; i <= u.size(); i++) //���� ��������� ������� ���������� � �������� �� ��������� ���� �� ���
			if (pairU[i] == 0 && dfs(i))
				result++;
	}
	return result;
}

void zeroing() {
	delete[]G;
	u.clear();
	v.clear();
}

void menu() {
	int n;
	cout << "\n\t1. ��������� ��������\n\t2. �����";
		while (1) {
			cout << "\n�������� �����: ";
			cin >> n;
			switch (n) {
			case(1): {
				creatG();
				cout << "\n\n\t������������ ������������� �����: " << Hopkroft_Karp_alg() << "\n\n";
				cout << "\t��������� ������ �������� ��� ���? \n\t1 - ��\n\t0 - ���\n\t��� �����: ";
				cin >> n;
				if (n) { zeroing(); menu(); }
				else exit(0);
			}
			case(2): {
				exit(0);
			}
			default: cout << "\n������ ������ ���, ���������� �����";
			}
		}
}

int main() {
	setlocale(LC_ALL, "");
	menu();
	return 0;
}