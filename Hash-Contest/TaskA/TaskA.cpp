#include <iostream>
#include <string>
#include <vector>

long long length = 1'000'000;

std::vector<char> letters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

int hash(const std::string& s, const std::vector<std::pair<std::string, long long>>& table) {
	long long pos = 0;
	for (size_t i = 0; i + 1 < std::min(30U, s.size()); ++i) {
                long long j = int(s[i]) - (int)'a';
                pos *= 10LL;
                pos += j;
		pos %= length;
	}
	pos %= 20923;
        pos = (((pos * (static_cast<long long>(s.size()) % 10910)) % 1054094) * 1244) % length;
        while (pos < length && table[pos].first != s && table[pos].first != "") {
                ++pos;
                if (pos == length) {
                        pos *= 432;
                        pos += 97826;
                        pos %= (length + 124153);
                        pos %= length;
                }
        }
	return pos;
}

int hash_table(const std::string& s, std::vector<std::pair<std::string, long long>>& table) {
	long long pos = hash(s, table);

	if (table[pos].first == "") {
		table[pos].first = s;
	}
	return pos;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::vector<std::pair<std::string, long long>> table(length, {"", 0});
	std::string s;
	long long value = 0;
	while (std::cin >> s) {
		std::cin >> value;
		int pos = hash_table(s, table);
		table[pos].second += value;
		std::cout << table[pos].second << "\n";
	}
}
