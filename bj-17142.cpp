// 문제 : https://www.acmicpc.net/problem/17142

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

// 상하좌우 체크 하기 위해서 만듦
const int dx[4] = { 0, 0, 1, -1 };
const int dy[4] = { -1, 1, 0, 0 };

vector<pos> virus;
vector<int> pickedVirus;	// 활성화 할 Virus
queue<pos> virusQueue;

void solve(int virusIdx) {

	if (pickedVirus.size() == M) {	// 총 바이러스 중에 M개 만큼 추출. (조합)

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				switch (map[y][x]) {
				case 0:	// 빈 칸
					testMap[y][x] = SPACE;
					break;
				case 1:	// 벽일때
					testMap[y][x] = WALL;
					break;
				case 2:	// 비활성화된 바이러스
					testMap[y][x] = DEACTIVE_VIRUS;
					break;
				default:
					break;
				}
			}
		}

		for (vector<int>::iterator it = pickedVirus.begin(); it != pickedVirus.end(); it++) {
			// M개 만큼 바이러스 활성화
			pos activVirus = virus[(*it)];
			testMap[activVirus.y][activVirus.x] = 0;
			virusQueue.push({ activVirus.x, activVirus.y });
		}

		// 바이러스 활성화 시뮬레이션
		while (!virusQueue.empty()) {
			pos v = virusQueue.front();
			for (int i = 0; i < 4; i++) {
				// 상하좌우으로 확산
				int x = v.x + dx[i];
				int y = v.y + dy[i];
				if (0 <= x && x < N && 0 <= y && y < N) {	// 연구소 내부인지 체크
					if (testMap[y][x] == SPACE || testMap[y][x] == DEACTIVE_VIRUS) {
						// 빈칸이나 비활성화 바이러스가 있을 때만 퍼짐.
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
				if (map[y][x] == 0) {	// 빈칸인지 확인하고
					if (testMap[y][x] == SPACE) {
						// 바이러스가 활성화 되어있는지 확인.
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
