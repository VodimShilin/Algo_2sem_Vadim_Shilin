#include <iostream>
#include <vector>
#include <string>

const long long num = 1'000'000'000;
const long long num_val = 9;

static long long tie = 0;

class BigInteger {
private:
    std::vector<long long> numbers;
    mutable int sign = 0;
public:
    BigInteger() {
        numbers.push_back(0);
    }

    BigInteger(int sign, const std::vector<long long>& numbers) : numbers(numbers), sign(sign) {}

    BigInteger(long long x) {
        if (x == 0) numbers.push_back(0);
        else if (x < 0) {
            sign = -1;
            x *= -1;
        }
        else sign = 1;

        while (x != 0) {
            numbers.push_back(x % num);
            x /= num;
        }
    }

    friend std::ostream& operator<<(std::ostream&, BigInteger);
    friend std::istream& operator>>(std::istream&, BigInteger&);
    friend long long operator%(BigInteger, long long);

    BigInteger operator-() {
        BigInteger to_return = *this;
        to_return.sign *= -1;
        return to_return;
    }

    bool operator==(const BigInteger& another) const {
        if (sign != another.sign) return false;
        if (sign == 0) return true;
        if (numbers.size() != another.numbers.size()) return false;
        size_t inc = 0;
        while (inc < numbers.size() && numbers[inc] == another.numbers[inc]) { ++inc; }
        if (inc < numbers.size()) return false;
        else return true;
    }

    bool operator<(const BigInteger& another) const {
        if (sign < another.sign) return true;
        else if (sign == 0) return false;
        else {
            if (sign < 0 && numbers.size() > another.numbers.size()) return true;
            else if (sign < 0 && numbers.size() < another.numbers.size()) return false;
            else if (sign > 0 && numbers.size() < another.numbers.size()) return true;
            else if (sign > 0 && numbers.size() > another.numbers.size()) return false;
            else {
                long long i = numbers.size() - 1;
                while (i > 0 && numbers[i] == another.numbers[i]) { --i; }
                return (numbers[i] * sign < another.numbers[i] * sign ? true : false);
            }
        }
    }

    bool operator>(const BigInteger& another) const { return another < *this; }
    bool operator!=(const BigInteger& another) const { return !(*this == another); }
    bool operator<=(const BigInteger& another) const { return !(*this > another); }
    bool operator>=(const BigInteger& another) const { return !(*this < another); }

    long long base() {
        return numbers[0];
    }

    BigInteger& operator++() {
        if (sign == 0) {
            sign = 1;
            ++numbers[0];
        }
        else if (sign == -1) {
            if (numbers.size() == 1 && numbers[0] == 1) *this = 0;
            else {
                sign = 1;
                --* this;
                sign = -1;
            }
        }
        else {
            sign = 1;
            size_t inc = 0;
            ++numbers[inc];
            while (numbers[inc] % num == 0) {
                numbers[inc] = 0;
                if (inc + 1 == numbers.size()) numbers.push_back(1);
                else ++numbers[inc + 1];
            }
        }
        return *this;
    }

    BigInteger& operator--() {
        if (sign == 0) {
            sign = -1;
            ++numbers[0];
        }
        else if (sign == -1) {
            sign = 1;
            ++* this;
            sign = -1;
        }
        else if (sign == 1) {
            if (numbers.size() == 1 && numbers[0] == 1) *this = 0;
            else {
                --numbers[0];
                size_t inc = 0;
                while (numbers[inc] < 0) {
                    numbers[inc] += num;
                    numbers[inc + 1] -= 1;
                }
                if (numbers[numbers.size() - 1] == 0) numbers.pop_back();
            }
        }
        return *this;
    }

    BigInteger operator++(int) {
        BigInteger to_return = *this;
        ++* this;
        return to_return;
    }

    BigInteger operator--(int) {
        BigInteger to_return = *this;
        --* this;
        return to_return;
    }

    BigInteger& operator+=(const BigInteger& another) {
        if (another.sign == 0) return *this;
        else if (sign == 0) {
            *this = another;
            return *this;
        }
        else if (sign * another.sign < 0) {
            sign *= -1;
            *this -= another;
            sign *= -1;
            return *this;
        }
        else if (this == &another) {
            for (size_t i = 0; i < numbers.size(); ++i) {
                numbers[i] *= 2;
            }
            for (size_t i = 0; i < numbers.size(); ++i) {
                if (numbers[i] >= num) {
                    if (i + 1 == numbers.size()) numbers.push_back(numbers[i] / num);
                    else numbers[i + 1] += numbers[i] / num;
                    numbers[i] %= num;
                }
            }
            return *this;
        }
        else {
            size_t i = 0; // long long
            for (i = 0; i < another.numbers.size(); ++i) {
                if (i == numbers.size()) numbers.push_back(another.numbers[i]);
                else numbers[i] += another.numbers[i];
                if (numbers[i] >= num) {
                    if (i + 1 == numbers.size()) numbers.push_back(numbers[i] / num);
                    else numbers[i + 1] += numbers[i] / num;
                    numbers[i] %= num;
                }
            }
            while (i < numbers.size() && numbers[i] >= num) {
                if (i + 1 == numbers.size()) numbers.push_back(numbers[i] / num);
                else numbers[i + 1] += numbers[i] / num;
                numbers[i] %= num;
                ++i;
            }
        }
        return *this;
    }

    BigInteger& operator-=(const BigInteger& another) {
        if (another.sign == 0) return *this;
        else if (this == &another) {
            *this = 0;
            return *this;
        }
        else if (sign == 0) {
            *this = another;
            sign *= -1;
            return *this;
        }
        else if (sign * another.sign < 0) {
            sign *= -1;
            *this += another;
            sign *= -1;
            return *this;
        }
        else {
            BigInteger to_less = *this;
            long long i = 0; // long long
            for (i = 0; static_cast<size_t>(i) < another.numbers.size(); ++i) {
                if (static_cast<size_t>(i) == numbers.size()) numbers.push_back(-another.numbers[i]);
                else numbers[i] -= another.numbers[i];
                if (numbers[i] < 0 && static_cast<size_t>(i) + 1 < numbers.size()) {
                    long long count = (-numbers[i] - 1) / num;
                    numbers[i] += num * (count + 1);
                    numbers[i + 1] -= (count + 1);
                }
            }
            while (static_cast<size_t>(i) < numbers.size() && numbers[i] < 0) {
                long long count = (-numbers[i] - 1) / num;
                numbers[i] += num * (count + 1);
                if (i + 1 == static_cast<long long>(numbers.size())) std::cerr << "assss ";
                numbers[i + 1] -= (count + 1);
                ++i;
            }
            if (static_cast<size_t>(i) < numbers.size()) {

            }
            else {
                if (numbers[numbers.size() - 1] < 0) {
                    numbers[numbers.size() - 1] *= -1;
                    sign *= -1;
                    for (i = numbers.size() - 2; i >= 0; --i) {
                        if (numbers[i] > 0) {
                            numbers[i] -= num;
                            numbers[i + 1] -= 1;
                            numbers[i] *= -1;
                        }
                        else numbers[i] *= -1;
                    }
                }
            }
            i = numbers.size() - 1;
            while (i >= 0 && numbers[i] == 0) {
                numbers.pop_back();
                --i;
            }
            if (numbers.size() == 0) *this = 0;
        }
        return *this;
    }

    BigInteger operator*=(const BigInteger& another) {
        if (sign == 0) return *this;
        else if (another == 0) {
            *this = 0;
            return *this;
        }
        else {
            std::vector<long long> to_return;
            for (long long i = 0; static_cast<size_t>(i) < another.numbers.size(); ++i) {
                long long j = 0;
                while (static_cast<size_t>(j) < numbers.size()) {
                    if (j + i == static_cast<long long>(to_return.size())) to_return.push_back(0);
                    to_return[j + i] += numbers[j] * another.numbers[i];
                    if (to_return[i + j] >= num) {
                        if (j + i + 1 == static_cast<long long>(to_return.size())) to_return.push_back(to_return[j + i] / num);
                        else to_return[j + i + 1] += to_return[j + i] / num;
                        to_return[j + i] %= num;
                    }
                    ++j;
                }
            }
            *this = BigInteger(sign * another.sign, to_return);
            return *this;
        }
    }

    BigInteger& operator/=(const BigInteger& another) {
        if (another.sign == 0) {
            std::cerr << "assssssss";
            return *this;
        } else if (sign == 0) {
            return *this;
        } else if (this == &another) {
            *this = 1;
            return *this;
        } else if (numbers.size() < another.numbers.size()) {
            *this = 0;
            return *this;
        } else if (another == 1) return *this;
        else if (another == -1) {
            sign *= -1;
            return *this;
        } else {
            std::vector<long long> to_return(numbers.size() - another.numbers.size() + 1);
            long long dec = another.numbers.size() - 1;
            long long i = numbers.size() - 1;
            while (i >= dec) {
                if (numbers[i] < another.numbers[dec]) {
                    if (i > dec) {
                        numbers[i - 1] += numbers[i] * num;
                        numbers[i] = 0;
                        --i;
                    } else break;
                }
                long long mid = 10 * num; ///деление
                long long sign = 1;
                long long count = 0;
                while (numbers[i] > another.numbers[dec] || numbers[i] < 0) {
                    mid = (mid + 1) / 2;
                    count += mid * sign;
                    for (long long j = 0; j <= dec; ++j) {
                        if (sign == -1 && j != dec) {
                            numbers[i - dec + j] -= num;
                            numbers[i - dec + j + 1] += 1;
                        }
                        if (j != dec) numbers[i - dec + j] -= another.numbers[j] * mid * sign % num;
                        else numbers[i - dec + j] -= another.numbers[j] * mid * sign;
                        if (j != 0) numbers[i - dec + j] -= another.numbers[j - 1] * mid * sign / num;
                        if (j != dec && numbers[i - dec + j] < 0) {
                            numbers[i - dec + j] += num;
                            numbers[i - dec + j + 1] -= 1;
                        }
                    }
                    if (numbers[i] < 0) sign = -1;
                    else sign = 1;
                    //dec
                }
                if (i == dec && numbers[i] == another.numbers[dec]) {
                    long long j = i;
                    while (j >= 0 && numbers[j] == another.numbers[j]) { --j; }
                    if (j == -1 || numbers[j] >= another.numbers[j]) count += 1;
                }
                if (i > dec) numbers[i - 1] += numbers[i] * num;
                to_return[i - static_cast<long long>(another.numbers.size()) + 1] = count;
                --i;
                //std::cout << count << "\n";
            }

            i = to_return.size() - 1;
            while (to_return[i] == 0 && i > 0) {
                to_return.pop_back();
                --i;
            }
            if (to_return[i] == 0) *this = 0;
            else {
                i = 0;
                while (static_cast<size_t>(i) < to_return.size()) {
                    if (to_return[i] >= num) {
                        if (i + 1 == static_cast<long long>(to_return.size())) to_return.push_back(to_return[i] / num);
                        else to_return[i + 1] += to_return[i] / num;
                        to_return[i] %= num;
                    }
                    ++i;
                }
                *this = BigInteger(sign * another.sign, to_return);
            }
        }
        return *this;
    }

    BigInteger& operator%=(const BigInteger& right) {
        BigInteger c = *this;
        c /= right;
        c *= right;
        return *this -= c;
    }

    explicit operator bool() {
        if (*this != 0) return true;
        return false;
    }

    std::string toString(size_t precession = 0) {
        std::string s;
        std::string ssign;
        std::vector<long long> news = numbers;
        if (sign == -1) ssign.push_back('-');
        long long j = news.size() - 1;
        s += std::to_string(news[j]);
        for (long long i = j - 1; i >= 0; --i) {
            int* nuls = new int[num_val];
            for (long long j = num_val - 1; j >= 0; --j) {
                nuls[j] = news[i] % 10;
                news[i] /= 10;
            }
            for (size_t j = 0; j < num_val; ++j) {
                if ((static_cast<size_t>(i) + 1) * num_val - j == precession) {
                    s.push_back('.');
                }
                s += std::to_string(nuls[j]);
            }
            delete[] nuls;
        }
        if (precession != 0) {
            if (s.size() <= precession) {
                ssign.push_back('0');
                ssign.push_back('.');
                for (size_t i = 0; i < precession - s.size(); ++i) {
                    ssign.push_back('0');
                }
            }

        }
        ssign += s;
        return ssign;
    }
};

std::ostream& operator<<(std::ostream& out, BigInteger write) {
    if (write.sign == -1) out << "-";
    long long j = write.numbers.size() - 1;
    out << write.numbers[j];
    for (long long i = j - 1; i >= 0; --i) {
        int* nuls = new int[num_val];
        for (long long j = num_val - 1; j >= 0; --j) {
            nuls[j] = write.numbers[i] % 10;
            write.numbers[i] /= 10;
        }
        for (long long j = 0; j < num_val; ++j) {
            out << nuls[j];
        }
        delete[] nuls;
    }
    return out;
}

std::istream& operator>>(std::istream& in, BigInteger& read) {
    read = 0;
    std::vector<char> x;
    bool flag = true;
    while (1) {
        char c = in.get();
        if (isspace(c) == 0 && c != '\0' && c != '\n' && c != EOF) {
            if (c == '-') read.sign = -1;
            else {
                if (c != '0') read.sign = 1;
                x.push_back(c);
            }
            break;
        }
        if (c == '\0' || c == EOF) return in;
    }
    while (flag) {
        char c = in.get();
        if (isspace(c) != 0 || c == '\0' || c == '\n' || c == EOF) {
            break;
        }
        x.push_back(c);
    }
    long long inc = 0;
    long long size = x.size();
    while (inc < size && atoi(&x[inc]) == 0) { ++inc; }
    if (inc < size && read.sign == 0) read.sign = 1;
    long long i = size - 1;
    while (i >= inc) {
        long long j = (i - num_val + 1 < inc) ? inc : i - num_val + 1;
        for (long long k = j; k <= i; ++k) {
            read.numbers[read.numbers.size() - 1] *= 10;
            char y = x[k];
            int y_p = atoi(&y);
            read.numbers[read.numbers.size() - 1] += y_p;
        }
        i = j - 1;
        if (i >= inc) read.numbers.push_back(0);
    }

    if (read.numbers.size() == 0 || (read.numbers.size() == 1 && read.numbers[0] == 0)) {
        read = 0;
    }
    return in;
}

BigInteger operator""_BI(unsigned long long x) {
    BigInteger to_return = x;
    return to_return;
}

BigInteger operator+(BigInteger left, const BigInteger& right) {
    return left += right;
}

BigInteger operator-(BigInteger left, const BigInteger& right) {
    return left -= right;
}

BigInteger operator/(BigInteger left, const BigInteger& right) {
    return left /= right;
}

BigInteger operator*(BigInteger left, const BigInteger& right) {
    return left *= right;
}

BigInteger operator%(BigInteger left, const BigInteger& right) {
    return left %= right;
}

const std::vector<long long> powers_of_two{1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144};

class Matrix {
public:
    std::vector<std::vector<long long>> matr;
    Matrix(std::vector<std::vector<long long>> matr): matr(matr) {}
    Matrix(long long x): matr(x, std::vector<long long>(x, 0)) {
        for (int i = 0; i < x; ++i) {
            matr[i][i] = 1;
        }
    }
    Matrix(long long x, bool): matr(x, std::vector<long long>(x, 0)) {}
    Matrix& operator*=(const Matrix& second) {
        Matrix to_return = Matrix(matr.size(), true);
        for (int i = 0; i < matr.size(); ++i) {
            for (int j = 0; j < matr.size(); ++j) {
                for (int k = 0; k < matr.size(); ++k) {
                    to_return.matr[i][j] += matr[i][k] * second.matr[k][j];
                }
            }
        }
        *this = to_return;
        return *this;
    }

    Matrix& operator%=(long long x) {
        for (int i = 0; i < matr.size(); ++i) {
            for (int j = 0; j < matr.size(); ++j) {
                matr[i][j] %= x;
            }
        }
        return *this;
    }
};


int main() {
    long long n;
    while (std::cin >> n && n != 0) {
        std::vector<std::vector<long long>> matr(5, std::vector<long long>(5));
        matr[0][0] = 1; matr[0][1] = 1; matr[0][2] = 1; matr[0][3] = 1; matr[0][4] = 1;
        matr[1][0] = 1; matr[1][1] = 1; matr[1][2] = 1; matr[1][3] = 1; matr[1][4] = 1;
        matr[2][0] = 1; matr[2][1] = 1; matr[2][2] = 1; matr[2][3] = 0; matr[2][4] = 0;
        matr[3][0] = 1; matr[3][1] = 1; matr[3][2] = 1; matr[3][3] = 1; matr[3][4] = 1;
        matr[4][0] = 1; matr[4][1] = 1; matr[4][2] = 1; matr[4][3] = 0; matr[4][4] = 0;

        Matrix ans = 5;
        Matrix p = Matrix(matr);
        --n;
        while (n != 0) {
            if (n & 1) ans *= p;
            Matrix p_ = p;
            p *= p_;
            n >>= 1;
            p %= 999999937ll;
            ans %= 999'999'937ll;
        }

        long long answ = 0;

        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                answ += ans.matr[i][j];
                answ %= 999'999'937ll;
            }
        }
        std::cout << answ % 999'999'937ll << "\n";
    }

    return 0;
}
