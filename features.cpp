#include "features.h"

features::features(vector<vector<vector<double>>> input, int numFilters, int filterWidth, int filterHeight, int outputWidth, int outputHeight, int stride)
{
	srand(time(NULL));
	for (int i = 0; i < numFilters; i++)
	{
		twoD filter(input, filterWidth, filterHeight, outputWidth, outputHeight, stride);
		filters.push_back(filter);
		output.push_back(filter.feedForward());
	}
}

vector<vector<vector<double>>> features::feedForward()
{
	return output;
}