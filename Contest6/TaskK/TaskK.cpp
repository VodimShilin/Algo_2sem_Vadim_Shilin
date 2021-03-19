#include <iostream>
#include <vector>
#include <algorithm>
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, c;
    std::cin >> n;
    std::vector<long long> values;
    for (int i = 0; i < n; ++i) {
        long long x;
        std::cin >> x;
        values.push_back(x);
    }
    std::cin >> c;
    std::vector<long long> sum1;
    std::vector<long long> sum2;
    std::vector<bool> uses(n);
    sum1.push_back(0);
    for (int i = 0; i < n / 2; ++i) {
        int length = sum1.size();
        for (size_t j = 0; j < length; ++j) {
            if (values[i] + sum1[j] <= c) sum1.push_back(values[i] + sum1[j]);
        }
    }
    sum2.push_back(0);
    for (int i = n / 2; i < n; ++i) {
        int length = sum2.size();
        for (size_t j = 0; j < length; ++j) {
            if (values[i] + sum2[j] <= c) sum2.push_back(values[i] + sum2[j]);
        }
    }
    std::sort(sum1.begin(), sum1.end());
    std::sort(sum2.begin(), sum2.end());
    int i = 0;
    int j = static_cast<int>(sum2.size()) - 1;
    long long ans = 0;
    while (i < sum1.size() && j >= 0) {
        if (sum1[i] + sum2[j] <= c) ans += j + 1;
        if (i + 1 < sum1.size() && sum1[i + 1] + sum2[j] <= c) ++i;
        else if (j > 0 && i + 1 < sum1.size()) {
            while (j > 0 && i + 1 < sum1.size() && sum1[i + 1] + sum2[j] > c) --j;
            ++i;
        }
        else break;
    }
    std::cout << ans;
}
