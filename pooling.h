#ifndef POOLING_H
#define POOLING_H

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>

using std::vector;
class pooling
{
	public:
		pooling(vector<vector<vector<double>>> input, int poolWidth, int poolHeight, int outputWidth, int outputHeight, int stride);
		vector<vector<vector<double>>> feedForward();
	private:
		vector<vector<vector<double>>> output;
};

#endif