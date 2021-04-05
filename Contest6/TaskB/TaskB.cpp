#include <iostream>
#include <vector>
#include <algorithm>

class element {
public:
    element() = default;
    element(long long a, long long i) : a(a), i(i) {}

    long long get() {
        return a;
    }
    long long index() {
        return i;
    }

    bool operator>(const element& second) const {
        return a > second.a || (a == second.a && i > second.i);
    }
    bool operator<(const element& second) const {
        return second > *this;
    }
    bool operator==(const element& second) const {
        return !(*this > second) && !(second > *this);
    }
    bool operator>=(const element& second) const {
        return *this == second || *this > second;
    }
    bool operator<=(const element& second) const {
        return *this == second || second > *this;
    }
    long long length = 1;
    element* prev = nullptr;
private:
    long long a = 0;
    long long i = 0;

};

template <typename T>
class SegmentTreeMaxSequence {
private:
    class Node;
public:
    SegmentTreeMaxSequence<T>(std::vector<element> elements): size(elements.size()), order(elements) {
        long long i = size;
        while (i > 0) {
            tree.push_back(std::vector<Node>(i));
            if (i % 2 != 0 && tree[tree.size() - 1].size() != 1) {
                ++i;
            }
            i /= 2;
        }
        long long power_of_two;
        for (i = 0, power_of_two = 1; i < tree.size(); ++i, power_of_two *= 2) {
            powers_of_two.push_back(power_of_two);
        }
    }

    void modify(long long index, Node point) {
        for (long long floor = 0; floor < tree.size(); ++floor, index /= 2) {
            tree[floor][index] = std::max(tree[floor][index], point);
        }
    }

    element* find() {
        for (int i = 0; i < size; ++i) {
            Node max_prev = get_max(order[i].index());
            order[i].prev = max_prev.our;
            max_prev.our = &order[i];
            max_prev.length += 1;
            modify(order[i].index(), max_prev);
        }
        return tree[tree.size() - 1][0].our;
    }

private:
    long long size = 0;

    class Node {
    public:
        element* our = nullptr;
        long long length = 0;
        Node() = default;
        Node(long long x): length(1) {}
        Node(long long x, element* previous): length(previous->length + 1) {}
        bool operator<(const Node& second) const {
            return length < second.length;
        }
        bool operator>(const Node& second) const {
            return second < *this;
        }
        bool operator==(const Node& second) const {
            return !(*this < second && second < *this);
        }
    };

    Node get_max(long long index) {
        if (index == 0) return Node();
        long long cur_index = 0;
        long long floor = tree.size() - 1;
        Node max;
        while (floor > 0) {
            if (index < cur_index * powers_of_two[floor] + powers_of_two[floor] / 2) {
                --floor;
                cur_index *= 2;
            } else if (index == cur_index * powers_of_two[floor] + powers_of_two[floor] / 2) {
                max = std::max(max, tree[floor - 1][cur_index * 2]);
                break;
            } else {
                max = std::max(max, tree[floor - 1][cur_index * 2]);
                cur_index *= 2;
                cur_index += 1;
                --floor;
            }
        }

        return max;
    }

    std::vector<std::vector<Node>> tree;
    std::vector<long long> powers_of_two;
    std::vector<element> order;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    long long n;
    std::cin >> n;
    if (n == 0) {
        std::cout << 0;
        return 0;
    }
    std::vector<long long> s(n);
    std::vector<element> s_sorted(n);
    for (int i = 0; i < n; ++i) {
        long long a;
        std::cin >> a;
        s[n - 1 - i] = a;
        s_sorted[n - 1 - i] = {a, n - 1 - i};
    }
    std::sort(s_sorted.begin(), s_sorted.end());
    SegmentTreeMaxSequence<long long> tree = s_sorted;
    element* ans = tree.find();
    std::vector<long long> indexes;
    while (ans != nullptr) {
        indexes.push_back(ans->index());
        ans = ans->prev;
    }
    std::cout << indexes.size() << "\n";
    for (int i = 0; i < indexes.size(); ++i) {
        std::cout << n - indexes[i] << "\n";
    }
    return 0;
}

