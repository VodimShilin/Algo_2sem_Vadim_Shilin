#include <iostream>
#include <vector>
 
int main() {
    long long n;
    std::cin >> n;
    std::vector<std::vector<long long>> dp(n + 1, std::vector<long long>(n + 1, 0)); // power i, max j
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            for (int k = 0; k <= (j / 2); ++k) {
                dp[i][j] += dp[i - j][k];
            }
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += dp[n][i];
    }
    std::cout << ans;
    return 0;
}

