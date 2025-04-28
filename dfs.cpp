#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Graph bertipe adjacency list berbobot
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

// Fungsi rekursif untuk DFS
bool dfsUtil(string current, string end, unordered_map<string, bool>& visited, vector<string>& path) {
    visited[current] = true;
    path.push_back(current);

    if (current == end) {
        return true;
    }

    for (auto neighbor : graph[current]) {
        string nextNode = neighbor.first;
        if (!visited[nextNode]) {
            if (dfsUtil(nextNode, end, visited, path)) {
                return true; // Jika ditemukan, berhenti
            }
        }
    }

    // Backtrack
    path.pop_back();
    return false;
}

// Fungsi DFS
void dfs(string start, string end) {
    unordered_map<string, bool> visited;
    vector<string> path;

    bool found = dfsUtil(start, end, visited, path);

    if (!found) {
        cout << "Tidak ada jalur dari " << start << " ke " << end << endl;
    } else {
        cout << "Rute dari " << start << " ke " << end << " (DFS):" << endl;
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
    
    dfs(start, end);

    return 0;
}
