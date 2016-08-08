#include "pooling.h"

pooling::pooling(vector<vector<vector<double>>> input, int poolWidth, int poolHeight, int outputWidth, int outputHeight, int stride)
{
	int numInputs = input.size();
	int inputHeight = input[0].size();
	int inputWidth = input[0][0].size();

	int paddingHeight = inputHeight - (poolHeight + (outputHeight - 1) * stride);
	int paddingHeightBot = -paddingHeight / 2;
	int paddingHeightTop = -paddingHeight - paddingHeightBot;

	int paddingWidth = inputWidth - (poolWidth + (outputWidth - 1) * stride);
	int paddingWidthRight = -paddingWidth / 2;
	int paddingWidthLeft = -paddingWidth - paddingWidthRight;

	for (int h = 0; h < numInputs; h++)
	{
		vector<vector<double>> singleOut;
		int curHeight = -paddingHeightTop;
		for (int i = 0; i < outputHeight; i++)
		{
			int curWidth = -paddingWidthLeft;
			vector<double> column;
			for (int j = 0; j < outputWidth; j++)
			{
				double max = 0;
				int scopeHeight = curHeight;
				for (int k = 0; k < poolHeight; k++)
				{
					int scopeWidth = curWidth;
					for (int l = 0; l < poolWidth; l++)
					{
						if (scopeHeight >=0 && scopeHeight < inputHeight && scopeWidth >=0 && scopeWidth < inputWidth)
						{
							if (input[h][scopeHeight][scopeWidth] > max)
							{
								max = input[h][scopeHeight][scopeWidth];
							}
						}
						scopeWidth++;
					}
					scopeHeight++;
				}
				
				column.push_back(max);
				curWidth += stride;
			}
			curHeight += stride;
			singleOut.push_back(column);
		}
		output.push_back(singleOut);
	}
}

vector<vector<vector<double>>> pooling::feedForward()
{
	return output;
}