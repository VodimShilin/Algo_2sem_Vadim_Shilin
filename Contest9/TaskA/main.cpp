#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <deque>

const int INF = 2'147'483'647;

struct element {
    element(int value, int8_t side): value(value), side(side) {}
    int value;
    int8_t side;
    int prev = -1;
};

class Graph{
public:
    Graph(): n(64), list_of_adjacency(n) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (((i % 8 - j % 8 + (i / 8 - j / 8) == 3) || (j % 8 - i % 8 + (i / 8 - j / 8) == 3)) &&
                        i / 8 - j / 8 > 0 && i / 8 - j / 8 < 3 && (i - j) % 8 != 0) {
                    list_of_adjacency[i].push_back(j);
                    list_of_adjacency[j].push_back(i);
                }
            }
        }
    }

    void print_smallest_path(std::string& f, std::string& s) {
        std::deque<std::string> ans = double_side_bfs((f[0] - 'a') * 8 + atoi(&f[1]) - 1, (s[0] - 'a') * 8 + atoi(&s[1]) -1);
        if (f == ans.front()) {
            for (auto i = ans.begin(); i != ans.end(); ++i) {
                std::cout << *i << "\n";
            }
        } else {
            for (auto i = ans.rbegin(); i != ans.rend(); ++i) {
                std::cout << *i << "\n";
            }
        }
    }

    std::deque<std::string> double_side_bfs(int f, int s) {
        std::queue<element> q;
        std::vector<element> dist(64, {INF, 0});
        q.push({f, -1});
        q.push({s, 1});
        dist[f] = {0, -1};
        dist[s] = {0, 1};
        while (!q.empty()) {
            element v = q.front();
            q.pop();
            for (int to: list_of_adjacency[v.value]) {
                if (dist[to].side * dist[v.value].side == -1) {
                    int ptr = v.value;
                    std::deque<std::string> to_return;
                    while (ptr != -1) {
                        std::string s;
                        s += static_cast<char>('a' + (ptr / 8));
                        s += std::to_string(ptr % 8 + 1);
                        to_return.push_back(s);
                        ptr = dist[ptr].prev;
                    }
                    ptr = to;
                    while (ptr != -1) {
                        std::string s;
                        s += static_cast<char>('a' + (ptr / 8));
                        s += std::to_string(ptr % 8 + 1);
                        to_return.push_front(s);
                        ptr = dist[ptr].prev;
                    }
                    return to_return;
                }
                if (dist[to].value != INF) continue;
                dist[to].value = dist[v.value].value + 1;
                dist[to].side = v.side;
                dist[to].prev = v.value;
                q.push({to, v.side});
            }
        }
    }

private:
    long long n;
    long long m;
    std::vector<std::pair<long long, long long>> pairs;
    std::vector<std::vector<long long>> matrix_of_adjacency;
    std::vector<std::vector<long long>> number_of_edge;
    std::vector<std::vector<long long>> list_of_adjacency;
    std::vector<std::vector<long long>> matrix_of_incidence;
};

int main() {
    std::string first, second;
    std::cin >> first >> second;
    Graph g;
    g.print_smallest_path(first, second);
    return 0;
}
