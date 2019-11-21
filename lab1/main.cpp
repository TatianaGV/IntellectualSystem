#include "tree_search.h"

using namespace std;

TreeNode::TreeNode(TreeNode *parent, int digit) : parent(parent), digit(digit) {}

QVector<TreeNode*> TreeNode::getNodes(){
    nodes.push_back(new TreeNode(this, digit + 3));
    nodes.push_back(new TreeNode(this, digit * 2));
    //nodes.push_back(new TreeNode(this, digit - 2));
    return nodes;
}

void TreeNode::getPath(TreeNode* tNode, int from){

    QVector<int> order;
    QSharedPointer<TreeNode> Node(tNode);

    while(tNode->digit != from){
        order.push_back(tNode->digit);
        tNode = tNode->parent;
    }
    order.push_back(tNode->digit);

    cout << order[order.size()-1];
    for (int i = order.size()-2; i >= 0; --i){
        cout << " -> " << order[i];
    }
    cout << endl;
}

void TreeNode::findPath(int from, int to){

    TreeNode* treeRoot = new TreeNode(nullptr, from);
    QSharedPointer<TreeNode> tree(treeRoot);

    queue<TreeNode*> queue;
    queue.push(treeRoot);

    while (!queue.empty()){
        //cout<<queue.size()<<endl;
        TreeNode* node = queue.front();

        for (auto tNode: node->getNodes()){
            queue.push(tNode);
        }

        if (node->digit == to) {
            getPath(node, from);
            break;
        }
        queue.pop();
    }
}


//task 1-2
int main() {
    int from, to;
    cin >> from >> to;

    auto time_start = std::chrono::steady_clock::now();
    TreeNode::findPath(from, to);

    auto finish = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = finish-time_start;
    std::cout<< diff.count() << std::endl;

    return 0;
}
