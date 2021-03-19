        #include <iostream>
        #include <vector>
        #include <string>
    
        class element {
        public:
            int length = 0;
            char prev = ' ';
            char value = ' ';
            element() = default;
            element(char value): length(1), value(value) {}
            element(char value, element previous): length(previous.length + 1), prev(previous.value), value(value) {}
            bool operator>(const element& second) const {
                return length > second.length;
            }
            bool operator<(const element& second) const {
                return second > *this;
            }
        };
    
        template <typename Iterator>
        using Iter = std::conditional_t<std::is_same_v<Iterator, std::string::iterator>, std::string::iterator, std::string::reverse_iterator>;
    
        template <typename Iterator>
        std::vector<element> lsc(std::string& first, std::string& second, Iter<Iterator> begin_f, Iter<Iterator> end_f, Iter<Iterator> begin_s, Iter<Iterator> end_s){
            std::vector<std::vector<element>> dp(2, std::vector<element>(end_s - begin_s + 2));
            int c = 0;
            for (Iter<Iterator> it = begin_f; it != end_f; ++it) {
                c = (it - begin_f) % 2;
                for (Iter<Iterator> j = begin_s; j != end_s; ++j) {
                    dp[c][j - begin_s + 1] = element();
                    //if (j - begin_s >= 2) dp[(2 + c - 1) % 2][j - begin_s - 2] = element();
                    dp[c][j - begin_s + 1] = std::max(dp[(2 + c - 1) % 2][j - begin_s + 1], dp[c][j - begin_s]);
                    //if (first[it - begin_f] == second[j - begin_s]) {
                    char fi = *it.base();
                    char se = *j.base();
                    if (*it.base() == *j.base()){
                        if (dp[(2 + c - 1) % 2][j - begin_s].length + 1 > dp[c][j - begin_s + 1].length) {
                            dp[c][j - begin_s + 1].length = 1 + dp[(2 + c - 1) % 2 ][j - begin_s].length;
                            dp[c][j - begin_s + 1].prev = dp[(2 + c - 1) % 2][j - begin_s].value;
                            dp[c][j - begin_s + 1].value = *it.base();//first[it - begin_f];
                        }
                    }
                }
            }
            return dp[c];
        };
    
        void hirschberg(std::string& first, std::string& second, std::string::iterator begin_f, std::string::iterator end_f, std::string::iterator begin_s, std::string::iterator end_s, std::string& ans) {
            if (end_s == begin_s) {
                return;
            }
            if (end_f == begin_f + 1) {
                bool flag_exist = false;
                for (std::string::iterator it = begin_s; it != end_s && !flag_exist; ++it) {
                    if (*it == *begin_f) {
                        flag_exist = true;
                    }
                }
                if (flag_exist) {
                    ans.push_back(*begin_f);
                }
                return;
            }
            std::string::iterator mid = begin_f + (end_f - begin_f - 1) / 2;
            std::vector<element> f = lsc<std::string::iterator>(first, second, begin_f, mid + 1, begin_s, end_s);
            std::vector<element> s = lsc<std::string::reverse_iterator>(first, second, std::make_reverse_iterator(end_f - 1), std::make_reverse_iterator(mid), std::make_reverse_iterator(end_s - 1), std::make_reverse_iterator(begin_s - 1));
            int max = s[end_s - begin_s].length;
            std::string::iterator max_it = begin_s - 1;
            for (std::string::iterator j = begin_s; j != end_s; ++j) {
                if (f[j - begin_s + 1].length + s[end_s - j - 1].length > max) {
                    max = f[j - begin_s + 1].length + s[(end_s - j - 1)].length;
                    max_it = j;
                }
            }
            hirschberg(first, second, begin_f, mid + 1, begin_s, max_it + 1, ans);
            hirschberg(first, second, mid + 1, end_f, max_it + 1, end_s, ans);
        }
    
        void change(std::string& first_in, std::string& second_in) {
            int n = first_in.size();
            int m = second_in.size();
            std::vector<bool> first(128);
            std::vector<bool> second(128);
            for (int i = 0; i < n; ++i) {
                first[(int)first_in[i]] = true;
            }
            for (int i = 0; i < m; ++i) {
                second[(int)second_in[i]] = true;
            }
            std::string first_s, second_s;
            for (int i = 0; i < n; ++i) {
                if (second[(int)first_in[i]]) {
                    first_s.push_back(first_in[i]);
                }
            }
            for (int i = 0; i < m; ++i) {
                if (first[(int)second_in[i]]) {
                    second_s.push_back(second_in[i]);
                }
            }
            first_in = first_s;
            second_in = second_s;
        }
    
        int main() {
            std::string first_s, second_s;
            std::cin >> first_s >> second_s;
            change(first_s, second_s);
            if (first_s.size() < second_s.size()) std::swap(first_s, second_s);
            int n = first_s.size();
            int m = second_s.size();
            std::string ans;
            hirschberg(first_s, second_s, first_s.begin(), first_s.end(), second_s.begin(), second_s.end(), ans);
            std::cout << ans;
            return 0;
        }

