/*
	Sentence :- “Everything  Are  The  Inspiration  Of God  Made”

		Importtant For Weights and Biases :- 

			1.	Input Size = 7 (How Many Words In The Sentence)
			2.	Hidde Size = 2 (Depends Of Dataset)
				Explanation :-
	
				Hidden Size | When to Use
		
				32 – 128 | Small datasets or simple tasks.
				128 – 512 | Medium datasets and moderately complex tasks.
				512 – 1024+ | Large datasets and complex tasks like language modeling or chatbots.
	
			3.	Output Size = 7 (Also Count Of Words)

		Xt = TimeSteps that are which tokens values count for eg.. in my senetence tokens count are the 7.
		Ht-1 = Xt  - 1 (eg.. Ht-1 =  X2  - 1) for the hidden state update by using previous hidden state value.

		why weights and biases :- 
			The weights and biases values are the random value in essenial stages but when losses optimized by using gradient decents method
			make the weights and biases suitable for predict.
		
		Wxh = random(Input Size, Hidden Size) -> Matrix
		Whh = random(Hidden Size, Hidden Size) -> Matrix
		Bh = random((1, Input size)) -> Flatten Vactor
		Who = random(Hidden Size,Output Size) -> Matrix
		Bo = random((1, Output size)) -> Flatten Vactor
*/

#ifndef PREPROCESśS_H
#define PREPROCESS_H

#include <string>
#include <vector>
#include <random>

using namespace std;

class Random
{
	public:
	void random(vector<double>& h, vector<double>& o, int input, int output)
	{
		for (int j = 0; j < output; ++j)
		{
			random_device rd;
    		mt19937 gen(rd());
    		uniform_real_distribution<> dist(0);
    		h.push_back(dist(gen));
		}
		for (int j = 0; j < input; ++j)
		{
			random_device rd;
    		mt19937 gen(rd());
    		uniform_real_distribution<> dist(0);
    		o.push_back(dist(gen));
		}		
	}

	void random(vector<vector<double>>& xh, vector<vector<double>>& hh, vector<vector<double>>& ho, int input, int hidden)
	{
		//Wxh = (hidden,input)
		for (int i = 0; i < hidden; ++i)
		{
			vector<double> temp;
			for (int j = 0; j < input; ++j)
			{
				random_device rd;
	    		mt19937 gen(rd());
	    		uniform_real_distribution<> dist(0.1, 0.01);
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
	    		uniform_real_distribution<> dist(0.1, 0.01);
	    		temp.push_back(dist(gen));
			}
			hh.push_back(temp);
		}
		//Why = (input,hidden)
		for (int i = 0; i < input; ++i)
		{
			vector<double> temp;
			for (int j = 0; j < hidden; ++j)
			{
				random_device rd;
	    		mt19937 gen(rd());
	    		uniform_real_distribution<> dist(0.1, 0.01);
	    		temp.push_back(dist(gen));
			}
			ho.push_back(temp);
		}			
	}
};
#endif