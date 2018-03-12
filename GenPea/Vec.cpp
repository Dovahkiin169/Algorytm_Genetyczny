#include "Vec.h"


Vector::Vector(void)
{

}

vector<vector<int>> Vector::GenCrossover(vector<int> ArrOrder1, vector<int> ArrOrder2)
{
	vector<vector<int>> ChildrensOrder;
	vector<int> Temp;
	ChildrensOrder.push_back(Temp);
	ChildrensOrder.push_back(Temp);

	vector<int> rod1;
	vector<int> rod2;

	int Point1 = rand() % (ArrOrder1.size() - 1); // rand crossing point 1, say in the middle (1/2)
	int Point2 = Point1 + 1 + (rand() % (ArrOrder1.size() - 1 - Point1)); // rand crossing point 2, after p1

	int endRozmiar = ArrOrder1.size() - Point2;

	int iter1 = 0;
	int iter2 = 0;

	int iter3 = 0;
	int iter4 = 0;
	//dodajemy do naszych vektorow danne miedzy pierwsym punktym a drugim punktym
	for (int i = Point1; i < Point2; i++)
	{
		ChildrensOrder[0].push_back(ArrOrder1[i]);
		ChildrensOrder[1].push_back(ArrOrder2[i]);
	}
	//zapisujemy danne do vektorow pomocniczych zeby wykonach krosowanie 
	for (int i = Point2; i < ArrOrder2.size(); i++)
	{
		rod1.push_back(ArrOrder1[i]);
		rod2.push_back(ArrOrder2[i]);
	}
	//zapisujemy danne do vektorow pomocniczych zeby wykonach krosowanie 
	for (int i = 0; i < Point2; i++)
	{
		rod1.push_back(ArrOrder1[i]);
		rod2.push_back(ArrOrder2[i]);
	}

	// copy the cities that were ommited from arr1, but take them in order in which they are in arr2
	for (int i = 0; i < ArrOrder2.size(); i++)
	{
		// if a city from arr2 is not in the childrensOrder[0]
		if (!(find(ChildrensOrder[0].begin(), ChildrensOrder[0].end(), rod2[i]) != ChildrensOrder[0].end()))
		{
			if (iter1 >= endRozmiar)
			{
				ChildrensOrder[0].insert(ChildrensOrder[0].begin() + iter3, rod2[i]);
				iter3++;
			}
			else
			{
				ChildrensOrder[0].push_back(rod2[i]); // add it
			}
			iter1++;
		}
		// if a city from arr1 is not in the childrensOrder[1]
		if (!(find(ChildrensOrder[1].begin(), ChildrensOrder[1].end(), rod1[i]) != ChildrensOrder[1].end()))
		{
			if (iter2 == endRozmiar || iter2 > endRozmiar)
			{
				ChildrensOrder[1].insert(ChildrensOrder[1].begin() + iter4, rod1[i]);
				iter4++;
			}
			else
			{
				ChildrensOrder[1].push_back(rod1[i]); // add it
			}
			iter2++;
		}
	}
	return ChildrensOrder;
}

void  Vector::GenQuicksort(vector<vector<int>> &Population, vector<double> &PopulationDistanc, int Left, int Right)
{
	vector<int> TempVect;
	double TempDistanc;

	int i = Left;
	int j = Right;
	double x = PopulationDistanc[(Left + Right) / 2];
	do
	{
		while (PopulationDistanc[i] < x)
		{
			i++;
		}
		while (PopulationDistanc[j] > x)
		{
			j--;
		}

		if (i <= j)
		{
			//swap(tab[i], tab[j]);
			TempVect = Population[i]; // copy the bigger
			Population[i] = Population[j]; // replace bigger with smaller
			Population[j] = TempVect; // replace old-smaller with copied bigger
			TempDistanc = PopulationDistanc[i];
			PopulationDistanc[i] = PopulationDistanc[j];
			PopulationDistanc[j] = TempDistanc;

			i++;
			j--;
		}
	} while (i <= j);

	if (Left < j)
	{
		GenQuicksort(Population, PopulationDistanc, Left, j);
	}

	if (Right > i)
	{
		GenQuicksort(Population, PopulationDistanc, i, Right);
	}
}

void  Vector::GenMutation(vector<int> &Instance)
{
	int Point1 = rand() % (Instance.size() - 1); // rand point 1
	int Point2 = Point1 + 1 + (rand() % (Instance.size() - 1 - Point1)); // rand point 2, after p1
	int Difference = Point2 - Point1;


	// 0 ... p1 _abc_ p2 ... X
	// 0 ... p2 _cba_ p1 ... X
	for (int i = 0; i <= Difference; i++)
	{
		int Temp = Instance[Point1 + i]; // temp = a
		Instance[Point1 + i] = Instance[Point2 - i]; // a = c
		Instance[Point2 - i] = Temp; // c = temp ( = a)
	}
}

void  Vector::GenSelection(vector<vector<int>> &Population, vector<double> &PopulationDistanc)
{
	vector<vector<int>> NewPopulation;
	vector<double>		NewPopulationDistances;

	// sort from small to big
	GenQuicksort(Population, PopulationDistanc, 0, PopulationDistanc.size() - 1);

	int PopulationSize = PopulationDistanc.size();
	int SelectSum = PopulationSize * (PopulationSize + 1) / 2; // sum of the whole ranking

	for (int i = 0; i < PopulationSize; i++)
	{
		double inv_selection_probability = i / SelectSum; // smallest is 1st, biggest is last; so smallest is 1/X, biggest is n/X (the biggest fraction)
		if (((double)rand() / RAND_MAX) > inv_selection_probability)  // for smallest (if eg 0.5 > inv_select_prob) is true, 1/X is gonna be very small so smaller than 0.5
		{
			NewPopulation.push_back(Population[i]);
			NewPopulationDistances.push_back(PopulationDistanc[i]);
		}
	}

	Population = NewPopulation;
	PopulationDistanc = NewPopulationDistances;
}

double Vector::Genetic(Nodes NodesArr, int PopulationDestSize, int Generations, double CrossingProbability, double MutationProbability)
{
	Nodes *TempArr = new Nodes();
	vector<vector<int>> Population;
	vector<double> PopulationDistanc;

	double distance;

	int p1;
	int p2;

	try
	{
		distance = NodesArr.NodesArrDist();
		TempArr->SetNodesArr(NodesArr.GetNodesArr()); // copy nodesArr to tempArr
		TempArr->SetDataType(NodesArr.GetDataType());

		if (NodesArr.GetDataType() == 1)
		{
			TempArr->SetNodesOrder(NodesArr.GetNodesOrder());
		}

		// generate 1st population of destsize
		for (int i = 0; i < PopulationDestSize; i++)
		{
			TempArr->mixArr(); // do a permutation
			Population.push_back(TempArr->GetNodesOrder());
			PopulationDistanc.push_back(TempArr->NodesArrDist());
		}

		// loop for #(generations)
		for (int a = 0; a < Generations; a++)
		{
			// linear ranking, calc the chance of getting to new population
			GenSelection(Population, PopulationDistanc);

			int pop_size = PopulationDistanc.size();

			// crossing all left after selection
//			for (int i = 0; i < pop_size; i++)
//			{
			for (int j = 0; j < pop_size/2; j++)
				{

			p1 = rand() % pop_size;
			p2 = rand() % pop_size;
			while (p1 == p2)
			{
				p2 = rand() % pop_size;
			}
					if (((double)rand() / RAND_MAX) < CrossingProbability)
					{
						vector<vector<int>> crossed = GenCrossover(Population[p1], Population[p2]);

						if (((double)rand() / RAND_MAX) < MutationProbability)
						{
							GenMutation(crossed[0]);
						}
						if (((double)rand() / RAND_MAX) < MutationProbability)
						{
							GenMutation(crossed[1]);
						}

						Population.push_back(crossed[0]);
						Population.push_back(crossed[1]);
						TempArr->SetNodesOrder(crossed[0]);
						PopulationDistanc.push_back(TempArr->NodesArrDist());
						TempArr->SetNodesOrder(crossed[1]);
						PopulationDistanc.push_back(TempArr->NodesArrDist());
					}
				}
//			}

			// sort population from best to worst
			GenQuicksort(Population, PopulationDistanc, 0, PopulationDistanc.size() - 1);

			// if too many...
			if (PopulationDistanc.size() > PopulationDestSize)
			{
				Population.resize(PopulationDestSize);
				PopulationDistanc.resize(PopulationDestSize);
			}


			// our solution is always @ first position
			distance = PopulationDistanc[0];
			//            cout<<"new distance: "<<distance<<"\n";
		}
		return distance;

	}
	catch (exception e)
	{
		cout << "Error: node number out of bounds.\n" << e.what() << "\n";
	}

	return -1;
}

bool Vector::GeneticBenchmark(string outfile)
{
	Timer * Time = new Timer();
	vector<string> filenames =
	{
		//   "tsp\\pr1002.tsp",
		   "tsp\\pr439.tsp",
		//   "tsp\\eil51.tsp",
		//   "atsp\\ftv55.atsp",
		//   "atsp\\ry48p.atsp",
			// "atsp\\br17.atsp",
			// "atsp\\ft53.atsp"
			 //"tsp\\a280.tsp",
		//	 "tsp\\pr439.tsp",
		//	 "tsp\\gr17.tsp",
	    //	 "tsp\\berlin52.tsp"
	};
	int Dane= 107217;
	double Distance;
	Nodes *NodesArr;

	ofstream results;
	results.open(outfile, ofstream::out | ofstream::app);

	for (string &filename : filenames)
	{
		NodesArr = new Nodes();

		if (!loadFile(filename, NodesArr))
		{
			if (!loadFile("..\\" + filename, NodesArr))
			{
				replace(filename.begin(), filename.end(), '\\', '/');
				if (!loadFile(filename, NodesArr))
				{
					cout << "File load error!\n";
					return false;
				}
			}
		}

		vector<int> PopulationSize = { 80 }; // size of population
		vector<int> Generations = { 800 }; // num of generations
		vector<double> CrossingProbability = { 0.7, 0.8, 0.9 };
		vector<double> MutationProbability = { 0.3, 0.2, 0.1 };

		int sampleSize = 1;
		for (int &PopulationDestSize : PopulationSize)
		{
			for (int &GenerationCount : Generations)
			{
				for (double &CrossingProbability : CrossingProbability)
				{
					for (double &MutationProbability : MutationProbability)
					{
						double SumDistance = 0;
						double AverageDistance = 0;

						for (int i = 0; i < sampleSize; i++)
						{
							Time->startTimer();
							Distance = Genetic(*NodesArr, PopulationDestSize, GenerationCount, CrossingProbability, MutationProbability);
							Time->ZapiszDoPlikuEndTimer(0, "Czas wykonanaia Algorytmu");

							SumDistance += Distance;
						}
						AverageDistance = SumDistance / sampleSize;
					//	cout << "Nazwa Pliku: " << filename << ", " << "Rozmiar Populacji :" << PopulationDestSize << ", " << "Rozmiar Generacji :" << GenerationCount << ", " << "Prawdopodobienstwo krzyzowania :" << CrossingProbability << ", " << "Prawdopodobienstwo mutacji :" << MutationProbability << ", " << "Dlugosc sciezki :" << (int)AverageDistance << "\n";
						double procent = ((AverageDistance-Dane)*100)/ Dane;
						cout << filename << ", " << PopulationDestSize << ", " << GenerationCount << ", " << CrossingProbability << ", " << MutationProbability << ", " << (int)AverageDistance << ", " << procent<< "\n";
					}
				}
			}
		}
	}

	results.close();
	return true;
}

bool Vector::TestGenetic(string outfile,vector<string> Filenames, vector<int> PopulationSize, vector<int> Generations, vector<double> CrossingProbability, vector<double> MutationProbability)
{
	Timer * Time = new Timer();
	vector<string> filenames = Filenames;

	double Distance;
	Nodes *NodesArr;

	ofstream results;
	results.open(outfile, ofstream::out | ofstream::app);

	for (string &filename : filenames)
	{
		NodesArr = new Nodes();

		if (!loadFile(filename, NodesArr))
		{
			if (!loadFile("..\\" + filename, NodesArr))
			{
				replace(filename.begin(), filename.end(), '\\', '/');
				if (!loadFile(filename, NodesArr))
				{
					cout << "File load error!\n";
					return false;
				}
			}
		}

		vector<int>    Population_Sizes = PopulationSize;
		vector<int>    generations = Generations;
		vector<double> Crossing_Probabilities = CrossingProbability;
		vector<double> Mutation_Probabilities = MutationProbability;

		int sampleSize = 1;
		for (int &PopulationDestSize : Population_Sizes)
		{
			for (int &GenerationCount : generations)
			{
				for (double &Crossing_Probability : Crossing_Probabilities)
				{
					for (double &Mutation_Probability : Mutation_Probabilities)
					{
						double SumDistance = 0;
						double AverageDistance = 0;

						for (int i = 0; i < sampleSize; i++)
						{
							Time->startTimer();
							Distance = Genetic(*NodesArr, PopulationDestSize, GenerationCount, Crossing_Probability, Mutation_Probability);
							Time->ZapiszDoPlikuEndTimer(0, "Czas wykonanaia Algorytmu");

							SumDistance += Distance;
						}
						AverageDistance = SumDistance / sampleSize;
						cout <<"Nazwa Pliku: "<< filename << "," <<"Rozmiar Populacji :"<< PopulationDestSize << "," <<"Rozmiar Generacji :"<< GenerationCount << "," <<"Prawdopodobienstwo krzyzowania :"<< Crossing_Probability << "," <<"Prawdopodobienstwo mutacji :"<< Mutation_Probability << "," <<"Dlugosc sciezki :"<<(int)AverageDistance << "\n";
					}
				}
			}
		}
	}
	results.close();
	return true;
}