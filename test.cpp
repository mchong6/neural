#include <vector>
#include <time.h>
#include <stdlib.h>
#include <iostream>



std::vector<std::vector<int> > multiply(std::vector<std::vector<int> >A, std::vector<std::vector<int> > B)
{
	std::vector<std::vector<int>> C;
	for (int i = 0; i < A.size(); i++)
	{
		std::vector<int>column;
		for(int j = 0; j < B[0].size(); j++)
		{
			int num = 0;
			for (int k = 0; k < B.size(); k++)
			{
				num += (A[i][k] * B[k][j]);
			}
			column.push_back(num);
		}
		C.push_back(column);
	}
	return C;
}

int main(void)
{
	std::vector<std::vector<int>> A = {{6,3,0},{2,5,1},{9,8,6}};
	std::vector<std::vector<int>> B = {{7, 4}, {6,7}, {5,0}};
	std::vector<std::vector<int>> temp = multiply(A,B );
	for (auto x : temp)
	{
		for (auto y : x)
		{
			std::cout<<y<<" ";
		}
		std::cout<<std::endl;
	}
}