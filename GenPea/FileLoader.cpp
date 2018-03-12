#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include "Nodes.h"

using namespace std;

Nodes *convFromOldTSPtoATSP(Nodes *NodesArr)
{
	Nodes *newNodesArr = new Nodes();
    newNodesArr->SetDataType(1);

    for (int i = 0; i < NodesArr->GetNodesArr().size(); i++)
	{
        vector<int> singleNode;
        for (int j = 0; j < NodesArr->GetNodesArr().size(); j++)
		{
            int Distance;
            if (i == j) 
			{
				Distance = INT32_MAX;
            } else 
			{
				Distance = NodesArr->TwoNodesDist(NodesArr->GetNode(i), NodesArr->GetNode(j));
            }
            singleNode.push_back(Distance);
        }
        newNodesArr->InsertNode(singleNode);
        singleNode.clear();
    }

    for (int a = 0; a < newNodesArr->GetNodesArr().size(); a++) 
	{
        newNodesArr->InsertToOrder(a);
    }
    return newNodesArr;
}

bool loadFile(string filename, Nodes *NodesArr)
{
    ifstream thefile(filename);

    string Line;
    bool nodesData = false;

    if (thefile.is_open()) 
	{
        cout << "File Opend \"" << filename << "\".\n";

        regex DimensionPattern("DIMENSION(.+?)([0-9]+)");

        int Dimension;

        while (getline(thefile, Line))
		{
            smatch DimensionResult;
            if (regex_search(Line, DimensionResult, DimensionPattern))
			{
				Dimension = atoi(DimensionResult[2].str().c_str());
            }
            if (Line == "NODE_COORD_SECTION")
			{
				NodesArr->SetDataType(0); // tsp 100%
                nodesData = true;
                continue; // skip the starting line
            }
            if (Line == "EDGE_WEIGHT_SECTION")
			{
				NodesArr->SetDataType(1); // atsp 100%
                nodesData = true;
                break; // we exit getline way of things
            }
            if (Line == "EOF") // for the TSP only
			{
                nodesData = false;
                break; // we don't need to parse anymore
            }

            if (nodesData) // real tsp data we're intrested in
			{ 
                if (NodesArr->GetDataType() == 0)
				{
                    stringstream ssin(Line);
                    vector<int> singleNode;
                    int i = 0;
                    while (ssin.good() && i <= 3) 
					{
                        int temp;
                        ssin >> temp;
                        if (i == 0)// if tsp
						{ 
                            ++i;
                            continue; // skip the first val (num of tsp node)
                        }
                        singleNode.push_back(temp);
                        ++i;
                    }
					NodesArr->InsertNode(singleNode);
                }

            }
        }

        if (NodesArr->GetDataType() == 1)
		{
            int i = 0;

            vector<int> singleNode;
            while (i < pow(Dimension, 2))
			{
                int temp;
                thefile >> temp;
                singleNode.push_back(temp);

                if (i != 0 && (i + 1) % Dimension == 0)
				{
					NodesArr->InsertNode(singleNode);
                    singleNode.clear();
                }
                ++i;
            }

            for (int a = 0; a < NodesArr->GetNodesArr().size(); a++)
			{
				NodesArr->InsertToOrder(a);
            }
        }

        thefile.close();

        if (NodesArr->GetDataType() == 0)
		{
            *NodesArr = *convFromOldTSPtoATSP(NodesArr);
        }

        return true;
    } 
	else 
	{
        cout << "Warning: unable to open file \"" << filename << "\".\n";
        return false;
    }
}
