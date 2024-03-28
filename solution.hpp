#pragma once

#include <vector>
#include <string>
#include <queue>
#include <initializer_list>

#include <cmath>

#include <iostream>
#include <type_traits>

#ifndef NEW_ENDL
// #define NEW_ENDL 0
#endif

#define null INT32_MIN

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
    ~ListNode() {
        delete next;
        next = nullptr;
    }
    friend struct ListAdapter;
};

struct ListAdapter {
    ListNode* head;
    ListAdapter() = default;
    ListAdapter(std::initializer_list<int> il);
    ~ListAdapter() {delete head; head = nullptr;}
    friend std::ostream& operator<<(std::ostream& os, const ListAdapter& la);
private:
    std::ostream& print(std::ostream& os, const ListNode* ln) const;
};

ListAdapter::ListAdapter(std::initializer_list<int> il) {
    if (il.size() == 0) {
        this->head = nullptr;
        return;
    }
    auto &p = this->head;
    for (const auto &i : il) {
        auto q = new ListNode(i);
        p = q;
        p = p->next;
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
    TreeNode* left;
    TreeNode* right;
public:
    TreeNode() : Node() {}
    TreeNode(int x) : Node(x) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : Node(x, left, right, nullptr) {}
    ~TreeNode() {
        delete left; delete right;
        left = nullptr; right = nullptr;
        delete next;
        next = nullptr;
    }
    friend struct TreeAdapter;
};

struct TreeAdapter {
    Node *root;
    TreeAdapter() = default;
    TreeAdapter(std::initializer_list<int> il);
    ~TreeAdapter() {delete root; root = nullptr;}
    friend std::ostream& operator<<(std::ostream& os, const TreeAdapter& tr);
private:
    std::ostream& print(std::ostream& os, const Node* tn, unsigned k = 0) const;
    constexpr const static int nani = null;
};

TreeAdapter::TreeAdapter(std::initializer_list<int> il) {
    if (il.begin() == il.end()) {
        this->root = nullptr;
        return;
    }
    std::queue<Node**> qtn;
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
std::ostream& TreeAdapter::print(std::ostream& os, const Node* tn, unsigned k) const {
    if (tn == nullptr) return os;
    os << std::string(4*k, ' ') << '(' << tn->val << ")\n";
    print(os, static_cast<TreeNode*>(tn->right), k+1);
    if ((tn->left == nullptr) ^ (tn->right == nullptr)) {
        os << std::string(4*(k+1), ' ') << "( )\n";
    }
    print(os, static_cast<TreeNode*>(tn->left), k+1);
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
    #ifdef NEW_ENDL
    os << std::endl;
    #endif
    return os;
}

// template <typename T> std::vector<T> str2vec(const std::string& s) {
//     std::vector<T> vec;
//     for (const auto& c : s) {
//         if (c == '[') {

//         }
//     }
// }