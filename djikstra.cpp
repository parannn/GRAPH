#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <climits>
#include <algorithm> 

using namespace std;

typedef pair<int, string> NodeDistance;

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

void dijkstra(string start, string end) {
    
    unordered_map<string, int> distances;
    unordered_map<string, string> previous;

    for (const auto& node : graph) {
        distances[node.first] = INT_MAX;
    }
    distances[start] = 0;

    priority_queue<NodeDistance, vector<NodeDistance>, greater<NodeDistance>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int currentDistance = pq.top().first;
        string currentNode = pq.top().second;
        pq.pop();

        if (currentNode == end) {
            break;
        }

        for (auto neighbor : graph[currentNode]) {
            string nextNode = neighbor.first;
            int weight = neighbor.second;
            int newDistance = currentDistance + weight;

            if (newDistance < distances[nextNode]) {
                distances[nextNode] = newDistance;
                previous[nextNode] = currentNode;
                pq.push({newDistance, nextNode});
            }
        }
    }

    if (distances[end] == INT_MAX) {
        cout << "Tidak ada jalur dari " << start << " ke " << end << endl;
    } else {
        cout << "Jarak terpendek dari " << start << " ke " << end << " adalah " << distances[end] << " km." << endl;

        vector<string> path;
        for (string at = end; at != ""; at = previous[at]) {
            path.push_back(at);
            if (previous.find(at) == previous.end()) break;
        }
        reverse(path.begin(), path.end());

        cout << "Rutenya: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
}

int main() {
    string start = "Bengkulu";
    string end = "Banda Aceh";
    
    dijkstra(start, end);

    return 0;
}
