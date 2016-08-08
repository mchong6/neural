#include "network.h"

network::network(vector<vector<vector<double>>> input)
{
	trainSet = input;
}

vector<vector<double>> network::backPropagateHelp(int n, std::map<int, vector<vector<double>>> & columbus)
{
	if (columbus.find(n) == columbus.end())
	{
		//recursive definition.
		columbus[n] = multiply(multiply(layers[n].getDerivatives(), layers[n+1].getWeight()),backPropagateHelp(n+1, columbus));
	}
	layers[n].d(columbus[n]);
	return columbus[n];
}

void network::backPropagate()
{
	std::map<int, vector<vector<double>>> columbus = {{numLayers - 1, multiply(layers[numLayers - 1].getDerivatives(), error)}};
	backPropagateHelp(0, columbus);
}

void network:: start()
{	
	vector<vector<vector<double>>> test;
	//generate test set
	for (double i = 0; i <= 20; i = i + 0.2)
	{
		test.push_back({{i},{i * i}});
	}

	bool first = false;
	std::ofstream plot;
	plot.open("plot.dat");
	long iteration = 0;

	do
	{
		iteration++;
		//total error.
		errorSquared = 0.0;
		for (const auto &x : trainSet)
		{
			//error used to propagate back. Refresh per input.
			error = {};
			//if first iteration, initialize layers.
			if (!first)
			{
				first = true;
				layers.push_back(layer({x[0]}, 8, false));
				layers.push_back(layer(layers[0].feedForward(), 8, false));
				layers.push_back(layer(layers[1].feedForward(), 1, true));
			}
			else
			{
				//update with next input value.
				layers[0].compute({x[0]});
				layers[1].compute(layers[0].feedForward());	
				layers[2].compute(layers[1].feedForward());	
			}
			//output
			vector<vector<double>> output = layers[2].feedForward();

			//update error
			for (int j = 0; j < (int) x[1].size(); j++)
			{
				double errorVal = output[0][j] - x[1][j];
				errorSquared += .5 * errorVal * errorVal;
				error.push_back({errorVal});
				//std::cout<<output[0][j] - x[1][j];
			}
			//std::cout<<std::endl;
			backPropagate();
			layers[0].update();
			layers[1].update();
			layers[2].update();

		}
		//update weights only after calculating errors for all inputs
		//layers[0].update();
		//layers[1].update();
		plot <<iteration<<" "<<errorSquared<<std::endl;
		std::cout<<errorSquared<<std::endl;
		std::ofstream curve;
		curve.open("curve.dat");
		for (auto & x : test)
		{
			float output = this->test({x[0]});
			curve << x[0][0] << " " << x[1][0] << " " << output<<std::endl;
		}
		curve.close();
	}
	while(errorSquared>1);
	plot.close();
}

vector<vector<double>> network::multiply(vector<vector<double> >A, vector<vector<double> > B)
{
	vector<vector<double>> C;
	for (int i = 0; i < (int) A.size(); i++)
	{
		vector<double>column;
		for(int j = 0; j < (int) B[0].size(); j++)
		{
			double num = 0;
			for (int k = 0; k < (int) B.size(); k++)
			{
				num += (A[i][k] * B[k][j]);
			}
			column.push_back(num);
		}
		C.push_back(column);
	}
	return C;
}

float network::test(vector<vector<double>> input)
{
	layers[0].compute(input);
	layers[1].compute(layers[0].feedForward());
	layers[2].compute(layers[1].feedForward());
	vector<vector<double>> output = layers[2].feedForward();	
	/*float max = 0;
	int num;
	for (int i = 0; i < (int) output[0].size(); i++)
	{
		if (output[0][i] > max)
		{
			max = output[0][i];
			num = i;
		}
	}*/

	return output[0][0];
}

//gnuplot command: gnuplot -persist -e "plot 'curve.dat' using 1:2 with lines, 'curve.dat' using 1:3with points" loop.plt
