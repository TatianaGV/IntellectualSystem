#include <queue>
#include <QMap>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "QVector"
#include <QSharedPointer>

using namespace std;

class ForwardNode{
public:
    long long digit;
    ForwardNode* parent;

    ForwardNode(long long digit, ForwardNode* parent = nullptr) : digit(digit) , parent(parent) {}

    QVector<ForwardNode*> getNodes(){
        QVector<ForwardNode*> nodes;
        nodes.push_back(new ForwardNode(digit + 3, this));
        nodes.push_back(new ForwardNode(digit * 2, this));
        return nodes;
    }
};

class BackNode{
public:
    long long digit;
    BackNode* parent;

    BackNode(long long digit, BackNode* parent = nullptr) : digit(digit) , parent(parent) {}

    QVector<BackNode*> getNodes(){
        QVector<BackNode*> nodes;
        nodes.push_back(new BackNode(digit - 3, this));
        if (digit % 2 ==0)
            nodes.push_back(new BackNode(digit / 2, this));
        return nodes;
    }
};

QVector<long long> getPath(ForwardNode* fNode, BackNode* bNode){
    QVector<long long> numbers(0);

    numbers.push_back(fNode->digit);
    fNode = fNode->parent;

    while (fNode!= nullptr){
        numbers.push_back(fNode -> digit);
        fNode = fNode ->parent;
    }
    reverse(numbers.begin(), numbers.end());

    bNode = bNode->parent;
    while (bNode != nullptr){
        numbers.push_back(bNode -> digit);
        bNode = bNode ->parent;
    }

    return numbers;
}

void showPath(QVector<long long>& numbers){
    cout << numbers[0];
    for (int i = 1; i <numbers.size(); ++i){
        cout << " -> " << numbers[i];
    }
    cout << endl;
}

pair<ForwardNode*, BackNode*> bidirectional(long long from, long long to){
    // start 2 queues, one from start, second from end
    // create 2 sets, sets<TreeNode*>

    map<long long, ForwardNode*> fSet;
    map<long long, BackNode*> bSet;

    queue<pair<ForwardNode*, long long>> fqueue;
    queue<pair<BackNode*, long long>> bqueue;


    ForwardNode* fNode = new ForwardNode(from);
    fqueue.emplace(fNode, 0);
    fSet.emplace(from, fNode);

    BackNode* bNode = new BackNode(to);
    bqueue.emplace(bNode, 0);
    bSet.emplace(to, bNode);

    int i = 1;
    while (true){
        //cout<<fqueue.size()<<" "<<bqueue.size()<<endl;

        if (!fqueue.size() || !bqueue.size()) {
            cout << "Решений нет" << endl;
            break;
        }
        while (!fqueue.empty()){
            auto node = fqueue.front();
            if (node.second == i)
                break;
            fqueue.pop();

            auto it = bSet.find(node.first->digit);
            if (it != bSet.end()){
                return make_pair(node.first, it->second);
            }
            for (auto fN: node.first->getNodes()){
                if (fN->digit > to)
                    continue;
                if (fSet.find(fN -> digit) == fSet.end()) {
                    fSet.emplace(fN->digit, fN);
                    fqueue.emplace(fN, i);
                }
            }
        }

        while (!bqueue.empty()){
            auto node = bqueue.front();
            if (node.second == i)
                break;
            bqueue.pop();

            auto it = fSet.find(node.first->digit);
            if (it != fSet.end()){
                return make_pair(it->second, node.first);
            }

            for (auto fN: node.first->getNodes()){
                if (bSet.find(fN -> digit) == bSet.end()) {
                    bSet.emplace(fN->digit, fN);
                    bqueue.emplace(fN, i);
                }
            }
        }
        i++;
    }
}


int main(){

    int from, to;
    cin >> from >> to;
    auto time_start = std::chrono::steady_clock::now();

    pair<ForwardNode*, BackNode*> nodes = bidirectional(from, to);
    QVector<long long> path = getPath(nodes.first, nodes.second);
    showPath(path);

    auto finish = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = finish-time_start;
    std::cout<< diff.count() << std::endl;

    return 0;
}