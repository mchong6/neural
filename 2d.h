#ifndef TWOD_H
#define TWOD_H

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>

using std::vector;

class twoD
{
	public:
		twoD(const vector<vector<vector<double>>> input, int filterWidth, int filterHeight, int outputWidth, int outputHeight, int stride);
		vector<vector<double>> feedForward();
		/*vector<vector<double>> getWeight();
		vector<vector<double>> getDerivatives();
		vector<vector<double>> getChange();*/
		void d(vector<vector<double>> d);
		void compute(vector<vector<vector<double>>> const input, int filterWidth, int filterHeight, int outputWidth, int outputHeight, int stride);
		void update();//

	private:
		vector<vector<vector<double>>> inputBar;
		vector<vector<double>> weightBar;
		vector<vector<double>> output;
		vector<vector<double>> derivatives;
		vector<vector<double>> change;
		vector<vector<double>> multiply(vector<vector<double> >A, vector<vector<double> > B);

};


#endif
