#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>

using std::vector;

class layer
{
	public:
		layer(const vector<vector<double>> input, int outputLength, bool lastLayer);
		vector<vector<double>> feedForward();
		vector<vector<double>> getWeight();
		vector<vector<double>> getDerivatives();
		vector<vector<double>> getChange();
		void d(vector<vector<double>> d);
		void compute(const vector<vector<double>>  input);
		void update();

	private:
		bool lastLayer;
		vector<vector<double>> inputBar;
		vector<vector<double>> weightBar;
		vector<vector<double>> output;
		vector<vector<double>> derivatives;
		vector<vector<double>> change;
		vector<vector<double>> multiply(vector<vector<double> >A, vector<vector<double> > B);

};


#endif
