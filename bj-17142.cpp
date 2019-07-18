// ���� : https://www.acmicpc.net/problem/17142

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int SPACE = -3;
const int WALL = -1;
const int DEACTIVE_VIRUS = -2;

const int INFI = (int)1e9;

struct pos {
	int x = -1;
	int y = -1;
};

int N, M;	// N = map's size, M = Initial active virus size
int map[50][50];
int testMap[50][50];
int minResult = INFI;

// �����¿� üũ �ϱ� ���ؼ� ����
const int dx[4] = { 0, 0, 1, -1 };
const int dy[4] = { -1, 1, 0, 0 };

vector<pos> virus;
vector<int> pickedVirus;	// Ȱ��ȭ �� Virus
queue<pos> virusQueue;

void solve(int virusIdx) {

	if (pickedVirus.size() == M) {	// �� ���̷��� �߿� M�� ��ŭ ����. (����)

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				switch (map[y][x]) {
				case 0:	// �� ĭ
					testMap[y][x] = SPACE;
					break;
				case 1:	// ���϶�
					testMap[y][x] = WALL;
					break;
				case 2:	// ��Ȱ��ȭ�� ���̷���
					testMap[y][x] = DEACTIVE_VIRUS;
					break;
				default:
					break;
				}
			}
		}

		for (vector<int>::iterator it = pickedVirus.begin(); it != pickedVirus.end(); it++) {
			// M�� ��ŭ ���̷��� Ȱ��ȭ
			pos activVirus = virus[(*it)];
			testMap[activVirus.y][activVirus.x] = 0;
			virusQueue.push({ activVirus.x, activVirus.y });
		}

		// ���̷��� Ȱ��ȭ �ùķ��̼�
		while (!virusQueue.empty()) {
			pos v = virusQueue.front();
			for (int i = 0; i < 4; i++) {
				// �����¿����� Ȯ��
				int x = v.x + dx[i];
				int y = v.y + dy[i];
				if (0 <= x && x < N && 0 <= y && y < N) {	// ������ �������� üũ
					if (testMap[y][x] == SPACE || testMap[y][x] == DEACTIVE_VIRUS) {
						// ��ĭ�̳� ��Ȱ��ȭ ���̷����� ���� ���� ����.
						testMap[y][x] = testMap[v.y][v.x] + 1;
						virusQueue.push({ x, y });
					}
				}
			}
			virusQueue.pop();
		}

		int maxInMap = 0;

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				if (map[y][x] == 0) {	// ��ĭ���� Ȯ���ϰ�
					if (testMap[y][x] == SPACE) {
						// ���̷����� Ȱ��ȭ �Ǿ��ִ��� Ȯ��.
						return;
					}
					else {
						maxInMap = max(maxInMap, testMap[y][x]);
					}
				}
			}
		}
		minResult = min(minResult, maxInMap);
		return;
	}

	if (virusIdx + 1 <= virus.size()) {
		pickedVirus.push_back(virusIdx);
		solve(virusIdx + 1);
		pickedVirus.pop_back();
		solve(virusIdx + 1);
	}
	
}


int main() {
	std::ios::sync_with_stdio(false);

	cin >> N >> M;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
			if (map[y][x] == 2) {
				virus.push_back({ x, y });
			}
		}
	}

	solve(0);

	if (minResult == INFI) {
		minResult = -1;
	}

	cout << minResult;

}
