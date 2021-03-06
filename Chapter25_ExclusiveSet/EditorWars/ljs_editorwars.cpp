#include <iostream>
#include <vector>

using namespace std;

int find(int a, vector<int>& disj);
int merge(int pa, int pb, vector<int>& disj, vector<int>& rank, vector<int>& size);
bool ack(int pa, int pb, vector<int>& disj, vector<int>& rank, vector<int>& size, vector<int>& enemy);
bool dis(int pa, int pb, vector<int>& disj, vector<int>& rank, vector<int>& size, vector<int>& enemy);
void result(vector<int>& disj, vector<int>& size, vector<int>& enemy);

void solution() {
    int n, m;
    cin >> n >> m;
    vector<int> disj(n);
    for (int i=0; i<n; i++) disj[i] = i;
    vector<int> rank(n, 1);
    vector<int> size(n, 1);
    vector<int> enemy(n, -1);
    string s;
    int a, b;
    bool cont = false;
    for (int i=0; i < m; i++) {
        cin >> s >> a >> b;
        if (cont) continue;
        int pa = find(a, disj);
        int pb = find(b, disj);
        if (s == "ACK") cont = ack(pa, pb, disj, rank, size, enemy);
        else cont = dis(pa, pb, disj, rank, size, enemy);
        if (cont) {
            cout << "CONTRADICTION AT " << i+1 << endl;
        }
    }
    if (cont) return;
    result(disj, size, enemy);
}

int find(int a, vector<int>& disj) {
    if (a == -1) return -1;
    if (a == disj[a]) return a;
    return disj[a] = find(disj[a], disj);
}

int merge(int pa, int pb, vector<int>& disj, vector<int>& rank, vector<int>& size) {
    if (pa == -1 || pb == -1 || pa == pb) return max(pa, pb);
    if (rank[pa] > rank[pb]) swap(pa, pb);
    disj[pa] = pb;
    size[pb] += size[pa];
    if (rank[pa] == rank[pb]) rank[pb]++;
    return pb;
}

bool ack(int pa, int pb, vector<int>& disj, vector<int>& rank, vector<int>& size, vector<int>& enemy) {
    if (enemy[pa] != pb) {
        int m = merge(pa, pb, disj, rank, size);
        int e = merge(find(enemy[pa], disj), find(enemy[pb], disj), disj, rank, size);
        enemy[m] = e;
        if (e != -1) enemy[e] = m;
        return false;
    }
    return true;
}

bool dis(int pa, int pb, vector<int>& disj, vector<int>& rank, vector<int>& size, vector<int>& enemy) {
    if (pa != pb) {
        enemy[pa] = merge(find(enemy[pa], disj), pb, disj, rank, size);
        enemy[pb] = merge(find(enemy[pb], disj), pa, disj, rank, size);
        return false;
    }
    return true;
}

void result(vector<int>& disj, vector<int>& size, vector<int>& enemy) {
    int res = 0;
    for (int i=0; i < disj.size(); i++) {
        if (i == disj[i] && i > enemy[i]) {
            if (enemy[i] != -1) res += max(size[i], size[enemy[i]]);
            else res += size[i];
        }
    }
    cout << "MAX PARTY SIZE IS " << res << endl;
}

int main() {
    int c;
    cin >> c;
    while (c--) solution();
    return 0;
}
