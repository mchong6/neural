#ifndef FEATURES_H
#define FEATURES_H

#include "2d.h"

class features
{
	public:
		features(vector<vector<vector<double>>> input, int numFilters, int filterWidth, int filterHeight, int outputWidth, int outputHeight, int stride);
		vector<vector<vector<double>>> feedForward();
	private:
		vector<vector<vector<double>>> output;
		vector<twoD> filters;
};

#endif