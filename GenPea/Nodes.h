#ifndef NODES_H
#define NODES_H
#include <vector>

using namespace std;

class Nodes 
{
private:
    vector<vector<int>> NodesArr;
    vector<vector<int>> NodesDistArr;
    bool dataType;
    vector<int> nodesOrder;

public:
    vector<int> GetNodesOrder();

    void SetNodesOrder(vector<int> nodesOrder);
    void InsertToOrder(int x);

    bool GetDataType();
    void SetDataType(bool dataType);

    vector<vector<int> > GetNodesArr();

    void SetNodesArr(const vector<vector<int>> &nodesArr);
    void InsertNode(vector<int> node);
    void SetNode(int i, vector<int> node);

    vector<int> GetNode(int i);


    int TwoNodesDist(vector<int> node_a, vector<int> node_b);
    int NodesArrDist();

    void mixArr();

	Nodes();
};
#endif //NODES_H