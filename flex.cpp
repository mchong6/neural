#include "flex.h"

flex::flex(vector<vector<double>> input, int numNodes, int stride, int numOutput)
{
	srand(time(NULL));
	int numInputs = input.size();
	int numLayers = ceil((numInputs - numNodes) / (float) stride);

	for (int i = 0, step = 0; i < numLayers; i++, step += stride)
	{
		vector<vector<double>> subInput;
		for (int j = 0; j < numNodes; j++)
		{
			if (step+j < numInputs)
			{
				subInput.push(input[step+j]);
			}
		}
		layer subLayer(subInput, numOutput, false);
		layers.push_back(subLayer);
		output.push_back(filter.feedForward());
	}
}

vector<vector<vector<double>>> flex::feedForward()
{
	return output;
}