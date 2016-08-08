#include "2d.h"


twoD::twoD(const vector<vector<vector<double>>> input, int filterWidth, int filterHeight, int outputWidth, int outputHeight, int stride)
{
	int height = input[0].size();
	int width = input[0][0].size(); 

	//generate random weights for n+1 X k matrix.
	//srand(time(NULL));
	for (int i = 0; i < width; i++)
	{
		vector<double> column;
		for (int j = 0; j < height; j++)
		{
			column.push_back(((double) rand() /(.5 * RAND_MAX))-1);
		}
		weightBar.push_back(column);
	}

	compute(input, filterWidth, filterHeight, outputWidth, outputHeight, stride);
}

vector<vector<double>> twoD::feedForward()
{
	return output;
}

/*vector<vector<double>> layer::getWeight()
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
*/

void twoD::compute(vector<vector<vector<double>>> const input, int filterWidth, int filterHeight, int outputWidth, int outputHeight, int stride)
{
	//append weight bias
	//reset derivatives of previous input.
	derivatives = {};
	inputBar = input;

	int numInputs = input.size();
	int inputHeight = input[0].size();
	int inputWidth = input[0][0].size();

	int paddingHeight = inputHeight - (filterHeight + (outputHeight - 1) * stride);
	int paddingHeightBot = -paddingHeight / 2;
	int paddingHeightTop = -paddingHeight - paddingHeightBot;

	int paddingWidth = inputWidth - (filterWidth + (outputWidth - 1) * stride);
	int paddingWidthRight = -paddingWidth / 2;
	int paddingWidthLeft = -paddingWidth - paddingWidthRight;



	int curHeight = -paddingHeightTop;
	for (int i = 0; i < outputHeight; i++)
	{
		int curWidth = -paddingWidthLeft;
		vector<double> column;
		for (int j = 0; j < outputWidth; j++)
		{
			double sum = 0;
			for (int h = 0; h < numInputs; h++)
			{
				int scopeHeight = curHeight;
				for (int k = 0; k < filterHeight; k++)
				{
					int scopeWidth = curWidth;
					for (int l = 0; l < filterWidth; l++)
					{
						if (scopeHeight >=0 && scopeHeight < inputHeight && scopeWidth >=0 && scopeWidth < inputWidth)
						{
							sum += input[h][scopeHeight][scopeWidth] * weightBar[k][l];
						}
						scopeWidth++;
					}
					scopeHeight++;
				}
			}
			column.push_back(sum);
			curWidth += stride;
		}
		curHeight += stride;
		output.push_back(column);
	}

	//apply sigmoid
	for (auto &x : output)
	{
		for (auto &y : x)
		{
			y = 1.0 / (1 + exp(-1.0 * y));
			//std::cout<<y<<" ";
		}
	}


	//calculate derivates. Make into matrix.
	/*for (int i = 0; i < outputHeight; i++)
	{
		vector<double> column;
		for (int j = 0; j < outputWidth; j++)
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
	}*/
}

/*void twoD::d(vector<vector<double>> d)
{
	//calculate change
	int numInputs = inputBar.size();
	int inputHeight = inputBar[0].size();
	int inputWidth = inputBar[0][0].size();
	int outputHeight = output.size();
	int outputWidth = output[0].size();


	for (int a = 0; a < (int) weightBar.size(); a++)
	{
		vector<double> column;
		for (int b = 0; b < (int) weightBar[0].size(); b++)
		{
			double sum = 0;
			for (int h = 0; h < numInputs; h++)
			{	
				for (int i = 0; i < outputHeight; i++)
				{
					for (int j = 0; j < outputWidth; j++)
					{
						if (i+a < inputHeight && j+b < inputWidth)
						{
							sum =+ d[h][i][j] * inputBar[i+a][j+b];
						}
					}
				}
			}
			column.push_back(sum);
		}
		change.push_back(column);
	}

	for (auto & x :change)
	{
		for (auto & y : x)
		{
			//constant that determines update magnitude
			y = -.000015 * y;
		}
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


vector<vector<double>> twoD::multiply(vector<vector<double> >A, vector<vector<double> > B)
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
}*/
