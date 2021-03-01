#include <iostream>
#include <vector>

#define LENGTH 3'000'000

long long hash(long long x, std::vector<std::pair<long long, long long>>& table) {
    long long pos = ((x % 471249) * 2143 + 234521) % LENGTH;
    while (table[pos].first != x && table[pos].first != -1) { ++pos; }
    return pos;
}

long long hash_table(long long x, std::vector<std::pair<long long, long long>>& table) {
	long long pos = hash(x, table);
	if (table[pos].first == -1) {
		table[pos].first = x;
		table[pos].second = x;
	}
	return pos;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
	std::vector<std::pair<long long, long long>> table(LENGTH, {-1, -1});
	int n;
	std::cin >> n;
	long long x, y;
	for (int i = 0; i < n; ++i) {
		std::cin >> x >> y;
		int posx = hash_table(x, table);
		int posy = hash_table(y, table);
		std::cout << std::abs(table[posx].second - table[posy].second) << "\n";
		std::swap(table[posx].second, table[posy].second);
	}
}