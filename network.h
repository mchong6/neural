#ifndef NETWORK_H
#define NETWORK_H

#include "layer.h"
#include <map>
#include <fstream>

class network
{
	public:
		network(vector<vector<vector<double>>> input);
		void start();
		float test(vector<vector<double>> input);
	private:
		vector<vector<double>> multiply(vector<vector<double> >A, vector<vector<double> > B);
		vector<vector<double>> backPropagateHelp(int n, std::map<int, vector<vector<double>>> & columbus);
		void backPropagate();
		vector<vector<vector<double>>> trainSet;
		vector<vector<double>> error;
		vector<layer> layers;
		double errorSquared;
		int numLayers = 3;  //numLayers exclude input layer! 3 is equivalent to 2 hidden + 1 output.
};	

#endif
