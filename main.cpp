#include "network.h"
#include "2d.h"
#include "features.h"
#include "pooling.h"

int main()
{
	vector<vector<vector<double>>> input;
	for (double i = 0; i <= 20; i++)
	{
		double random = (double) rand() / ((1.0/20) * RAND_MAX);
		input.push_back({{random},{random * random}});
	}

	/*vector<vector<double>> temp;
	for (double i = 0; i < 4; i++)
	{
		temp.push_back({i,i,i,i});
	}
	input.push_back(temp);
	input.push_back(temp);

	features filter(input, 3, 2, 2, 3, 3, 1);
	pooling pool(filter.feedForward(), 2, 2, 2, 2, 1);*/

	network Mine(input);
	Mine.start();
	while (true)
	{
		float testNum;
		std::cout<<"Input: ";

		while(!(std::cin>>testNum))
		{
			std::cout << "Bad Value!";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		vector<vector<double>> testVec = {{}};
		testVec[0].push_back(testNum);
		/*for (int i = 0; i < 11; i++)
		{
			testVec[0].push_back(0);
		}
		testVec[0][testNum] = 1;*/
		float output = Mine.test(testVec);
		std::cout<<"Output: "<<output<<" Correct: "<<testNum * testNum<<" Pecentage error: "<<(testNum * testNum - output)/(output) * 100<<std::endl;
		std::cout<<std::endl;
	}
}