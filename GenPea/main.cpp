#include "Vec.h"

int main(int argc, char *argv[])
{
	Vector *Vec = new Vector();

	vector<string> File_Names;
	string FileNames;

	vector<int> PopulationSize;
	int Population_Size;

	vector<int> Generations_;
	int Generations;

	vector<double> CrossingProbabilities;
	double Crossing_Probabilities;

	vector<double> MutationProbabilities;
	double Mutation_Probabilities;

	bool a = true;
	int Dane;

	while (a)
	{
		cout << "1. Podaj danne dla algorytmu genetycznego.\n"
				"2. Uruchom benchmark algorytmu genetycznego.\n"
				"0. EXIT.\n";
		cout << ">>";
		cin >> Dane;

		switch (Dane)
		{
		case 1:
			cout << "Podaj nazwe pliku.\n >>";
				cin >> FileNames;
			cout << "Podaj rozmiar populacji.\n >>";
				cin >> Population_Size;
			cout << "Podaj ilosc generacij.\n >>";
				cin >> Generations;
			cout << "Podaj prawdopodobienstwa krzyzowania.\n >>";
				cin >> Crossing_Probabilities;
			cout << "Podaj prawdopodobienstwe mutacji.\n >>";
				cin >> Mutation_Probabilities;

			File_Names =	 { FileNames };
			PopulationSize = { Population_Size };
			Generations_ =	 { Generations };
			CrossingProbabilities = { Crossing_Probabilities };
			CrossingProbabilities = { Mutation_Probabilities };

			Vec->TestGenetic(((string)argv[0]) + ".genetic.csv", File_Names, PopulationSize, Generations_, CrossingProbabilities, CrossingProbabilities);
			break;
		case 2:
			Vec->GeneticBenchmark(((string)argv[0]) + ".genetic.csv");
			break;
		case 0:
			a = false;
			break;
		}
	}
}
