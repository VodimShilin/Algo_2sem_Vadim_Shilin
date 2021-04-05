#include <iostream>
#include <vector>
#include <algorithm>

std::pair<int, int> genHash(const long long p = 65537) {
    int x = rand() % p;
    int y = rand() % p;
    return std::pair(x, y);
}

long long hashValue(long long x, long long m, const std::pair<long long, long long>& hash, const long long p = 65537) {
    long long r = ((hash.first * x + hash.second) % p) % m;
    return r;
}

struct HashTable {
public:
    HashTable(const std::vector<int>& input): hash(input.size()){
        bool flag = false;
        size_t m = input.size();
        construct_outer_table(input, m);
        construct_inner_table(input);
    }

    int value(int x) {
        int i = hashValue(x, table.size(), main_hash);
        return table[i][hashValue(x, table[i].size(), hash[i])].second;
    }

private:
    std::pair<int, int> main_hash;
    std::vector<std::vector<std::pair<int, int>>> table;
    std::vector<std::pair<int, int>> hash;

    void construct_outer_table(const std::vector<int>& input, size_t m) {
        bool constructed_flag = false;
        while (!constructed_flag) {
            std::vector<std::vector<std::pair<int, int>>> new_table(m);
            main_hash = genHash();
            for (size_t i = 0; i < m; ++i) {
                new_table[hashValue(i, m, main_hash)].push_back(std::pair(i, input[i]));
            }
            size_t sum = 0;
            for (size_t i = 0; i < 0; ++i) {
                sum += 2 * new_table[i].size() * new_table[i].size();
            }
            if (sum <= 16 * m) {
                constructed_flag = true;
                table = new_table;
            }
        }
    }

    void construct_inner_table(const std::vector<int>& input) {
        bool constructed_flag = false;
        for (size_t i = 0; i < input.size(); ++i) {
            constructed_flag  = false;
            while(!constructed_flag) {
                constructed_flag = true;
                size_t size = table[i].size();
                std::vector<std::pair<int, int>> new_bucket(2 * size * size, std::pair(-1, -1));
                std::pair<int, int> hash_buck = genHash();
                for (size_t j = 0; j < table[i].size(); ++j) {
                    if (new_bucket[hashValue(table[i][j].first, new_bucket.size(), hash_buck)] == std::pair(-1, -1)) {
                        new_bucket[hashValue(table[i][j].first, new_bucket.size(), hash_buck)] = table[i][j];
                    } else {
                        constructed_flag  = false;
                        break;
                    }
                }
                if (constructed_flag) {
                    table[i] = new_bucket;
                    hash[i] = hash_buck;
                }
            }
        }
    }

};

struct Pairs {
    int x = 0;
    int y = 0;

    Pairs(int x, int y): x(x), y(y) {}
};

struct Vertex {
    int index = 0;
    int degree = 0;
    std::vector<int> children;

    bool flag = false;
    Vertex(int ind): index(ind) {}

    bool operator>(const Vertex& second) const {
        return degree > second.degree;
    }
    bool operator<(const Vertex& second) const {
        return second > *this;
    }
    bool operator==(const Vertex& second) const {
        return !(*this > second) && !(second > *this);
    }
};

double triangles(int n, std::vector<Vertex>& table, HashTable& indexes) {
    double ans = 0;
    for (int i = 0; i < n; ++i) {
        for (size_t j = 0; j < table[i].children.size(); ++j) {
            table[indexes.value(table[i].children[j])].flag = true;
        }
        for (size_t j = 0; j < table[i].children.size(); ++j) {
            for (size_t k = 0; k < table[indexes.value(table[i].children[j])].children.size(); ++k) {
                if (table[indexes.value(table[indexes.value(table[i].children[j])].children[k])].flag) ans += 1;
            }
        }
        for (size_t j = 0; j < table[i].children.size(); ++j) {
            table[indexes.value(table[i].children[j])].flag = false;
        }
    }
    return ans;
}

int main() {
    std::cout.precision(6);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    int m;
    int x;
    int y;
    std::cin >> n >> m;
    std::vector<Pairs> pairs;
    std::vector<Vertex> table;
    for (int i = 0; i < n; ++i) {
        table.push_back(i);
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> x >> y;
        pairs.push_back(Pairs(x - 1, y - 1));
        ++table[x - 1].degree;
        ++table[y - 1].degree;
    }
    std::sort(table.begin(), table.end());
    std::vector<int> indexes_of_values(n);
    for (int i = 0; i < n; ++i) {
        indexes_of_values[table[i].index] = i;
    }
    HashTable indexes(indexes_of_values);
    for (int i = 0; i < m; ++i) {
        if (indexes.value(pairs[i].x) < indexes.value(pairs[i].y)) { std::swap(pairs[i].x, pairs[i].y); }
        table[indexes.value(pairs[i].y)].children.push_back(pairs[i].x);
    }
    double ans = triangles(n, table, indexes);
    std::cout << std::fixed << ans / 4;
    return 0;
}
