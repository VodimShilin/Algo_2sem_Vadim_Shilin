#include <iostream>
#include <vector>
#include <algorithm>

struct obj {
    long long x = 0;
    long long y = 0;

    obj(long long x, long long y) : x(x), y(y){}

    bool operator>(const obj& second) const{
        return (x > second.x) || (x == second.x && y > second.y);
    }
    bool operator<(const obj& second) const{
        return second > *this;
    }
    bool operator==(const obj& second) const{
        return !(*this > second) && !(*this < second);
    }
    bool operator!=(const obj& second) const{
        return !(*this == second);
    }
    bool operator>=(const obj& second) const{
        return (*this == second || *this > second);
    }
    bool operator<=(const obj& second) const{
        return (*this == second || *this < second);
    }
};


long long length = 1'000'000'001;

int hash(long long y) {
    long long pos = (y * 1 + 1'000'000'001) % length - 1;
    return pos;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::vector<std::pair<long long, long long>> coords;
    long long w, h, n, x, y;
    std::cin >> w >> h >> n;
    if ((w * h > 12 && w * h - 12 > 5 * (n - 4)) || w > 3 * n || h > 3 * n) std::cout << "No";
    else {
        for (long long i = 0; i < n; ++i) {
            std::cin >> x >> y;
            if (x >= 0 && x <= w + 1 && y >= 0 && y <= h + 1) coords.push_back({ x, y });
        }
        n = coords.size();
        std::vector<std::vector<bool>> table(w + 2, std::vector<bool>(h + 2));
        for (long long i = 0; i < n; ++i) {
            table[coords[i].first][coords[i].second] = 1;
            if (coords[i].second <= h) table[coords[i].first][coords[i].second + 1] = 1;
            if (coords[i].second >= 1) table[coords[i].first][coords[i].second - 1] = 1;
            if (coords[i].first <= w) table[coords[i].first + 1][coords[i].second] = 1;
            if (coords[i].first >= 1) table[coords[i].first - 1][coords[i].second] = 1;
        }
        bool flag = 1;
        for (size_t i = 1; i <= w && flag == 1; ++i) {
            for (size_t j = 1; j <= h && flag == 1; ++j) {
                if (table[i][j] == 0) flag = 0;
            }
        }
        if (flag == 0) std::cout << "No";
        else std::cout << "Yes";

    }
}
