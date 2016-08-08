#include "layer.h"


layer::layer(const vector<vector<double>> input, int outputLength, bool lastLayer)
{
	this->lastLayer = lastLayer;
	//generate random weights for n+1 X k matrix.
	srand(time(NULL));
	for (int i = 0; i < (int) input[0].size() + 1; i++)
	{
		vector<double> column;
		for (int j = 0; j < outputLength; j++)
		{
			column.push_back(((double) rand() /(.5 * RAND_MAX))-1);
			//column.push_back(rand());
		}
		weightBar.push_back(column);
	}
	compute(input);
}

vector<vector<double>> layer::feedForward()
{
	return output;
}

vector<vector<double>> layer::getWeight()
{
	vector<vector<double>> mine = weightBar;
	mine.pop_back();
	return mine;
}
vector<vector<double>> layer:: getDerivatives()
{
	return derivatives;
}
vector<vector<double>> layer:: getChange()
{
	return change;
}
void layer::compute(vector<vector<double>> const input)
{
	//append weight bias
	//reset derivatives of previous input.
	derivatives = {};
	inputBar = input;
	inputBar[0].push_back(1);
	output = multiply(inputBar, weightBar);

	if (!lastLayer)
	{
		for (auto & x : output)
		{
			for (auto & y : x)
			{
				y = 1.0 / (1 + exp(-1.0 * y));
			}
		}
	}

	//calculate derivates. Make into matrix.
	int size = output[0].size();
	for (int i = 0; i < size; i++)
	{
		vector<double> column;
		for (int j = 0; j < size; j++)
		{
			column.push_back(0);
		}
		derivatives.push_back(column);
	}
	for (int i = 0; i < size; i++)
	{
		if (!lastLayer)
		{
			derivatives[i][i] = output[0][i] * (1 - output[0][i]);
		}
		else
		{
			derivatives[i][i] = 1;
		}
	}
}

void layer::d(vector<vector<double>> d)
{
	//calculate change
	vector<vector<double>> newChange = multiply(d, inputBar);
	for (auto & x :newChange)
	{
		for (auto & y : x)
		{
			//constant that determines update magnitude
			y = -.000015 * y;
		}
	}


	//transpose
	vector<vector<double>> transposed;
	for (int col = 0; col < (int) newChange[0].size(); col++)
	{
		vector<double> column;
		for (int row = 0; row < (int) newChange.size(); row++)
		{
			column.push_back(newChange[row][col]);
		}
		transposed.push_back(column);
	}

	//if change is not yet initialized
	if (change.size() == 0)
	{
		change = transposed;
	}
	//sum up all changes for different input
	else
	{
		for (int i = 0; i < (int)change.size(); i++)
		{
			for (int j = 0; j < (int)change[0].size(); j++)
			{
				change[i][j] += transposed[i][j];
			}
		}	
	}
}

vector<vector<double>> layer::multiply(vector<vector<double> >A, vector<vector<double> > B)
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

void layer::update()
{
	for (int i = 0; i < (int)weightBar.size(); i++)
	{
		for (int j = 0; j < (int)weightBar[0].size(); j++)
		{
			//update weightBar
			weightBar[i][j] += change[i][j];
		}
	}
	//reset change after every update.
	change = {};
}