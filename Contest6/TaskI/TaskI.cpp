#include <iostream>
#include <vector>
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    long long n;
    std::cin >> n;
    std::vector<long long> values(n);
    for(int i = 0; i < n; ++i) {
        std::cin >> values[i];
    }
    long long max = 0;
    for (int i = 0; i < n; ++i) {
        if (values[i] > max) {
            max = values[i];
        }
    }
    std::vector<long long> numbers(max + 1, 0);
    long long sum = 1;
    for (long long i: values) {
        long long x = sum - numbers[i];
        numbers[i] = sum;
        sum += x % 1'000'000'007;
    }
    std::cout << (sum - 1) % 1'000'000'007;
    return 0;
}
