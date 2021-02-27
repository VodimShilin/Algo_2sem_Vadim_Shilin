#include <iostream>
#include <vector>

long long length = 3'000'000;

long long hash(long long x, std::vector<std::pair<long long, long long>>& table) {
	long long pos = ((x % 471249) * 2143 + 234521) % length;
	while (table[pos].first != x && table[pos].first != -1) { ++pos; }
	if (table[pos].first == -1) {
		table[pos].first = x;
		table[pos].second = x;
	}
	return pos;
}

int main()
{
	std::vector<std::pair<long long, long long>> table(length);
	for (long long i = 0; i < length; ++i) {
		table[i].first = -1;
		table[i].second = -1;
	}

	int n;
	std::cin >> n;
	long long x, y;
	for (int i = 0; i < n; ++i) {
		std::cin >> x >> y;
		int posx = hash(x, table);
		int posy = hash(y, table);
		std::cout << std::abs(table[posx].second - table[posy].second) << "\n";
		std::swap(table[posx].second, table[posy].second);
	}
}