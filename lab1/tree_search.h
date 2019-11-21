#pragma once

#include <iostream>
#include <queue>
#include <chrono>
#include <QSharedPointer>

class TreeNode{

    int digit;
    TreeNode* parent;
    QVector<TreeNode*> nodes;

public:

    TreeNode(TreeNode* parent, int digit);

    QVector<TreeNode*> getNodes();

    static void getPath(TreeNode* tNode, int from);
    static void findPath(int from, int to);
};

