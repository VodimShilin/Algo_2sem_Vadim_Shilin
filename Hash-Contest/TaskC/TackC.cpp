#include <iostream>
#include <vector>

bool is_not_full(long long w, long long h, long long n) {
	return ((w * h > 12 && w * h - 12 > 5 * (n - 4)) || w > 3 * n || h > 3 * n);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::vector<std::pair<long long, long long>> coords;
    long long w;
    long long h;
    long long n;
    long long x; 
    long long y;
    std::cin >> w >> h >> n;
    if (is_not_full(w, h, n)) {
	    std::cout << "No";
    } else {
        for (long long i = 0; i < n; ++i) {
            std::cin >> x >> y;
            if (x >= 0 && x <= w + 1 && y >= 0 && y <= h + 1) {
		        coords.push_back({ x,y });
	        }
        }
        n = coords.size();
        std::vector<std::vector<bool>> table(w + 2, std::vector<bool>(h + 2));
        for (long long i = 0; i < n; ++i) {
            table[coords[i].first][coords[i].second] = 1;
            if (coords[i].second <= h) {
		        table[coords[i].first][coords[i].second + 1] = 1;
	        }
            if (coords[i].second >= 1) {
		        table[coords[i].first][coords[i].second - 1] = 1;
	        }
            if (coords[i].first <= w) {
		        table[coords[i].first + 1][coords[i].second] = 1;
	        }
            if (coords[i].first >= 1) {
		        table[coords[i].first - 1][coords[i].second] = 1;
	        }
        }
        bool is_full_flag = 1;
        for (size_t i = 1; i <= w && is_full_flag == 1; ++i) {
            for (size_t j = 1; j <= h && is_full_flag == 1; ++j) {
                if (table[i][j] == 0) {
			        is_full_flag = 0;
		        }
            }
        }
        if (is_full_flag == 0) {
		    std::cout << "No";
	    } else std::cout << "Yes";

    }
}
