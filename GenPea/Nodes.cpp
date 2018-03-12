#include <cmath>
#include <algorithm>
#include <iostream>
#include "Nodes.h"


Nodes::Nodes()
{

}

vector<vector<int> > Nodes::GetNodesArr()
{
    return NodesArr;
}

void Nodes::SetNodesArr(const vector<vector<int>> &nodesArr)
{
	Nodes::NodesArr = nodesArr;
}

void Nodes::InsertNode(vector<int> node)
{
	NodesArr.push_back(node);
}

void Nodes::SetNode(int i, vector<int> node)
{
	NodesArr[i] = node;
}

vector<int> Nodes::GetNode(int i)
{
    if (i < NodesArr.size())
	{
        return NodesArr[i];
    }
	else 
	{
        throw exception();
    }
}

int Nodes::TwoNodesDist(vector<int> node_a, vector<int> node_b)
{
    return (int) sqrt(pow((node_a[0] - node_b[0]), 2) + pow((node_a[1] - node_b[1]), 2));
}

int Nodes::NodesArrDist()
{
    int sum = 0;
    int i;

    if (dataType == 0) 
	{
        cout << "WARNING v1: dataType 0 !!!!!!!!!!!!\n";
        for (i = 0; i < NodesArr.size() - 1; i++)// -1, because we don't want to try to get a non-existing size+1 node
		{ 
            sum += TwoNodesDist(NodesArr[i], NodesArr[i + 1]);
        }
        sum += TwoNodesDist(NodesArr[i], NodesArr[0]); // get the dist between last and first node
    } 
	else 
	{
        for (i = 0; i < nodesOrder.size() - 1; i++) 
		{
            sum += NodesArr[nodesOrder[i]][nodesOrder[i + 1]]; // get the dist from node i to node (i+1)
            // ATSP super debug
        }
        sum += NodesArr[nodesOrder[i]][nodesOrder[0]]; // get the dist between last and first node
    }

    return sum;
}


void Nodes::mixArr()
{
    if (dataType == 0) 
	{
        cout << "WARNING v2: dataType 0 !!!!!!!!!!!!\n";
    } 
	else 
	{
        std::random_shuffle ( nodesOrder.begin(), nodesOrder.end() );
    }
}

bool Nodes::GetDataType()
{
    return dataType;
}

void Nodes::SetDataType(bool dataType)
{
	Nodes::dataType = dataType;
}


vector<int> Nodes::GetNodesOrder()
{
    return nodesOrder;
}


void Nodes::SetNodesOrder(vector<int> nodesOrder)
{
	Nodes::nodesOrder = nodesOrder;
}

void Nodes::InsertToOrder(int x)
{
    nodesOrder.push_back(x);
}
