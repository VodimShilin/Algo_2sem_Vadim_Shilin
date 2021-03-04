#include <fstream>
#include <string>
#include <vector>

#define LENGTH 1'000'000

int hash(const std::string& s, std::vector<std::pair<std::string, std::string>>& table, bool tomb) {
	long long pos = 0;
	for (size_t i = 0; i < s.size(); ++i) {
        long long j = (int)s[i] - (int)'A';
        pos *= 10LL;
		pos += j;
		pos %= LENGTH;
	}
	pos %= 20923;
	pos = (((pos * (static_cast<long long>(s.size()) % 10910)) % 1054094) * 1244) % LENGTH;
	while (pos < LENGTH && table[pos].first != s && table[pos].first != "" && table[pos].first != (tomb == 1 ? "0" : "1")) {
		++pos;
		if (pos == LENGTH) {
			pos *= 432;
			pos += 97826;
			pos %= (LENGTH + 124153);
			pos %= LENGTH;
		}
	}
	return pos;
}

int main()
{
	std::ifstream in ("map.in");
	std::ofstream out("map.out");
	std::vector<std::pair<std::string, std::string>> table(LENGTH, {"", "none"});

	std::string s;
	std::string key;
	std::string value;
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
