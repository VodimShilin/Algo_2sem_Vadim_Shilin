#include <fstream>
#include <string>
#include <vector>

long long length = 1'000'000;
std::vector<char> letters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

int hash(const std::string& s, std::vector<std::pair<std::string, std::string>>& table, bool tomb) {
	long long pos = 0;
	for (size_t i = 0; i < s.size(); ++i) {
		long long j = 0;
		while (j < 52 && s[i] != letters[j]) { ++j; }
		pos *= 10LL;
		pos += j;
		pos %= length;
	}
	pos %= 20923;
	pos = (((pos * (static_cast<long long>(s.size()) % 10910)) % 1054094) * 1244) % length;
	while (pos < length && table[pos].first != s && table[pos].first != "" && table[pos].first != (tomb == 1 ? "0" : "1")) {
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

int main()
{
	std::ifstream in ("map.in");
	std::ofstream out("map.out");
	std::vector<std::pair<std::string, std::string>> table(length);
	for (size_t i = 0; i < length; ++i) {
		table[i].first = "";
		table[i].second = "none";
	}

	std::string s, key, value;
	while (in >> s) {
		in >> key;
		if (s == "put") {
			in >> value;
			int pos = hash(key, table, 1);
			table[pos].first = key;
			table[pos].second = value;
		} else if (s == "delete") {
			int pos = hash(key, table, 0);
			if (table[pos].first == key) {
				table[pos].first = "0";
				table[pos].second = "none";
			}
		} else {
			int pos = hash(key, table, 0);
			out << table[pos].second << "\n";
		}
	}
}