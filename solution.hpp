#pragma once

#include <vector>
#include <string>
#include <queue>
#include <initializer_list>

#include <cmath>

#include <iostream>
#include <type_traits>

#define null INT32_MIN

class Node {
public:
    int val;
    Node(int v = 0) : val(v) {}
    virtual ~Node() = default;
};

struct ListNode : public Node {
    using Node::val;
    ListNode *next = nullptr;
    ListNode(int v = 0, ListNode *n = nullptr) : Node(v), next(n) {}
    virtual ~ListNode() = default;
    void free() { delete next; next = nullptr; }
    friend struct ListAdapter;
};

struct ListAdapter {
    ListNode* head = nullptr;
    ListAdapter() = default;
    ListAdapter(std::initializer_list<int> il);
    ~ListAdapter() {delete head; head = nullptr;}
    friend std::ostream& operator<<(std::ostream& os, const ListAdapter& la);
private:
    std::ostream& print(std::ostream& os, const ListNode* ln) const;
};

ListAdapter::ListAdapter(std::initializer_list<int> il) {
    this->head = nullptr;
    auto *p = &(this->head);
    for (const auto &i : il) {
        *p = new ListNode(i);
        p = &((*p)->next);
    }
}

std::ostream& operator<<(std::ostream& os, const ListAdapter& la) {
    os << '[';
    la.print(os, la.head);
    os << ']';
    return os;
}
std::ostream& ListAdapter::print(std::ostream& os, const ListNode* ln) const {
    if (ln == nullptr) {
        return os;
    }
    os << ln->val;
    if (ln->next != nullptr) {
        os << ", ";
    }
    print(os, ln->next);
    return os;
}

struct TreeNode : public Node {
    using Node::val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
public:
    TreeNode(int v = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : Node(v), left(l), right(r) {}
    virtual ~TreeNode() = default;
    void free() { delete left; left = nullptr; delete right; right = nullptr; }
    friend struct TreeAdapter;
};

struct TreeAdapter {
    TreeNode *root = nullptr;
    TreeAdapter() = default;
    TreeAdapter(std::initializer_list<int> il);
    ~TreeAdapter() {delete root; root = nullptr;}
    friend std::ostream& operator<<(std::ostream& os, const TreeAdapter& tr);
private:
    std::ostream& print(std::ostream& os, const TreeNode* tn, unsigned k = 0) const;
    constexpr const static int nani = null;
};

TreeAdapter::TreeAdapter(std::initializer_list<int> il) {
    if (il.begin() == il.end()) {
        this->root = nullptr;
        return;
    }
    std::queue<TreeNode**> qtn;
    qtn.push(&(this->root));
    for (const auto &i : il) {
        if (qtn.empty()) return;
        auto p = qtn.front();
        qtn.pop();
        if (i != nani) {
            *p = new TreeNode(i);
            qtn.push(&((*p)->left));
            qtn.push(&(*p)->right);
        }
        else {
            *p = nullptr;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const TreeAdapter& tr) {
    tr.print(os, tr.root);
    return os;
}
std::ostream& TreeAdapter::print(std::ostream& os, const TreeNode* tn, unsigned k) const {
    if (tn == nullptr) return os;
    os << std::string(4*k, ' ') << '(' << tn->val << ")\n";
    print(os, tn->right, k+1);
    if ((tn->left == nullptr) ^ (tn->right == nullptr)) {
        os << std::string(4*(k+1), ' ') << "( )\n";
    }
    print(os, tn->left, k+1);
    return os;
}

template<typename T> std::ostream& operator<<(std::ostream &os, const std::vector<T> &v) {
    os << '[';
    for (auto it = v.cbegin(); it != v.cend();) {
        if (std::is_same<typename std::decay<T>::type, std::string>::value) {
            os << '\"' << *it << '\"';
        }
        else {
            os << *it;
        }
        ++it;
        if (it != v.cend()) {
            os << ',';
        }
    }
    os << ']';
    return os;
}

// template <typename T> std::vector<T> str2vec(const std::string& s) {
//     std::vector<T> vec;
//     for (const auto& c : s) {
//         if (c == '[') {

//         }
//     }
// }