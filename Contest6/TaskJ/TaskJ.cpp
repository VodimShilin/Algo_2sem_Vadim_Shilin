#include <iostream>
#include <vector>
 
int main() {
    long long s, n;
    std::cin >> s >> n;
    std::vector<long long> weights(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> weights[i];
    }
    std::vector<std::vector<long long>> dp(s + 1, std::vector<long long>(n + 1));
    for (int i = 0; i <= n; ++i) {
        dp[0][i] = 0;
    }
    for (int i = 0; i <= s; ++i) {
        dp[i][0] = 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < s; ++j) {
            if (i + 1 <= n) dp[j][i + 1] = std::max(dp[j][i + 1], dp[j][i]);
            if (i + 1 <= n && j + weights[i + 1] <= s) {
		    dp[j + weights[i + 1]][i + 1] = std::max(dp[j + weights[i + 1]][i + 1], dp[j][i] + weights[i + 1]);
	    }
        }
    }
    long long k = 0;
    long long max = 0;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= s; ++j) {
            if (j > 0) {
                k += 1;
            }
            if (dp[j][i] > max) max = dp[j][i];
        }
    }
    std::cout << max;
    return 0;
}
