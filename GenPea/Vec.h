#include <vector>
#include "Nodes.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <memory>
#include <deque>
#include "FileLoader.h"
#include "Timer.h"

using namespace std;

class Vector 
{
private:

public:
	vector<vector<int>> GenCrossover(vector<int>, vector<int>);
	void GenQuicksort(vector<vector<int>> &population, vector<double> &population_distances, int left, int right);
	void GenMutation(vector<int> &instance);
	void GenSelection(vector<vector<int>> &population, vector<double> &population_distances);

	double Genetic(Nodes nodesArr, int pop_destsize, int generations, double crossing_probability, double mutation_probability);

	bool TestGenetic(string outfile, vector<string> filenames, vector<int> pop_size, vector<int> generations, vector<double> crossing_probabilities, vector<double> mutation_probabilities);
	bool GeneticBenchmark(string outfile);

	Vector(void);
};
