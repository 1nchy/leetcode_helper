# Leetcode Helper

## 摘要

leetcode 常常以列表的形式给出一个二叉树或链表，为了方便本地调试程序，故随手写出 `solution.hpp` 用来完成二叉树和链表的构造。

## 简述

~~~cpp
TreeAdapter _ta({1,2,2,3,3,null,null,4,4});
ListAdapter _la({5,2,13,3,8});
const TreeNode* _pt_root = _ta.root;
const ListNode* _pl_head = _la.head;
std::cout << _ta << std::endl;
std::cout << _la << std::endl;
~~~

简单，无需多言
