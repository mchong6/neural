#ifndef FLEX_H
#define FLEX_H

#include "layer.h"

class flex
{
	public:
		flex(vector<vector<double>> input);
		vector<vector<vector<double>>> feedForward();
	private:
		vector<vector<vector<double>>> output;
		vector<layer> layers;
};

#endif