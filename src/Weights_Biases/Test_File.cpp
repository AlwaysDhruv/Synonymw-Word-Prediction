#include <string>
#include <vector>
#include <random>

using namespace std;

class Random
{
	public:
	void random(vector<double>&, int);
	void random(vector<vector<double>>&, int , int);
	void random(vector<double>& h, vector<double>&, int , int);
	void random(vector<vector<double>>&, vector<vector<double>>&, vector<vector<double>>&, int, int);
};

int main(int argc, char const *argv[])
{
	Random rand;
    vector<vector<double>> wxh;
    vector<vector<double>> whh;
    vector<vector<double>> who;
    vector<double> bh;
    vector<double> bo;
    rand.random(wxh,whh,who,5,2);
    rand.random(bh,bo,5,2);
	return 0;
}

void Random::random(vector<double>& output, int count)
{
	for (int j = 0; j < count; ++j)
	{
		random_device rd;
   		mt19937 gen(rd());
   		uniform_real_distribution<> dist(0.0, 1.0);
   		output.push_back(dist(gen));
	}
}

void Random::random(vector<vector<double>>& output, int columns, int rows)
{
	for (int i = 0; i < columns; ++i)
	{
		vector<double> temp;
		for (int j = 0; j < rows; ++j)
		{
			random_device rd;
    		mt19937 gen(rd());
    		uniform_real_distribution<> dist(0.0, 1.0);
    		temp.push_back(dist(gen));
		}
		output.push_back(temp);
	}
}
void Random::random(vector<double>& h, vector<double>& o, int input, int output)
{
	for (int j = 0; j < input; ++j)
	{
		random_device rd;
   		mt19937 gen(rd());
   		uniform_real_distribution<> dist(0.0, 1.0);
   		h.push_back(dist(gen));
	}
	for (int j = 0; j < output; ++j)
	{
		random_device rd;
   		mt19937 gen(rd());
   		uniform_real_distribution<> dist(0.0, 1.0);
   		o.push_back(dist(gen));
	}		
}
void Random::random(vector<vector<double>>& xh, vector<vector<double>>& hh, vector<vector<double>>& ho, int input, int hidden)
{
	//Wxh = (input,hidden)
	for (int i = 0; i < input; ++i)
	{
		vector<double> temp;
		for (int j = 0; j < hidden; ++j)
		{
			random_device rd;
    		mt19937 gen(rd());
    		uniform_real_distribution<> dist(0.0, 1.0);
    		temp.push_back(dist(gen));
		}
		xh.push_back(temp);
	}
	//Whh = (hidden,hidden)
	for (int i = 0; i < hidden; ++i)
	{
		vector<double> temp;
		for (int j = 0; j < hidden; ++j)
		{
			random_device rd;
    		mt19937 gen(rd());
    		uniform_real_distribution<> dist(0.0, 1.0);
    		temp.push_back(dist(gen));
		}
		hh.push_back(temp);
	}
	//Who = (input,hidden)
	for (int i = 0; i < input; ++i)
	{
		vector<double> temp;
		for (int j = 0; j < hidden; ++j)
		{
			random_device rd;
    		mt19937 gen(rd());
    		uniform_real_distribution<> dist(0.0, 1.0);
    		temp.push_back(dist(gen));
		}
		ho.push_back(temp);
	}			
}