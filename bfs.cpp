#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

unordered_map<string, vector<pair<string, int>>> graph = {
    {"Bengkulu", {{"Lubuklinggau", 130}, {"Palembang", 300}}},
    {"Lubuklinggau", {{"Palembang", 260}, {"Jambi", 400}}},
    {"Palembang", {{"Jambi", 200}}},
    {"Jambi", {{"Pekanbaru", 450}, {"Medan", 900}}},
    {"Pekanbaru", {{"Duri", 120}}},
    {"Duri", {{"Medan", 500}}},
    {"Medan", {{"Lhokseumawe", 400}}},
    {"Lhokseumawe", {{"Banda Aceh", 270}}},
    {"Banda Aceh", {}}
};

void bfs(string start, string end) {
    unordered_map<string, bool> visited;
    unordered_map<string, string> previous;

    queue<string> q;
    q.push(start);
    visited[start] = true;

    bool found = false;

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        if (current == end) {
            found = true;
            break;
        }

        for (auto neighbor : graph[current]) {
            string nextNode = neighbor.first;
            if (!visited[nextNode]) {
                visited[nextNode] = true;
                previous[nextNode] = current;
                q.push(nextNode);
            }
        }
    }

    if (!found) {
        cout << "Tidak ada jalur dari " << start << " ke " << end << endl;
    } else {
        vector<string> path;
        for (string at = end; at != ""; at = previous[at]) {
            path.push_back(at);
            if (previous.find(at) == previous.end()) break;
        }
        reverse(path.begin(), path.end());

        cout << "Rute dari " << start << " ke " << end << " (BFS) " << endl;
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << endl;
        cout << "Jumlah kota yang dilewati: " << path.size() << endl;
    }
}

int main() {
    string start = "Bengkulu";
    string end = "Banda Aceh";
    
    bfs(start, end);

    return 0;
}
