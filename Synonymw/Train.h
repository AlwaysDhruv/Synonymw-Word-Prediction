/*
			Here's a simplified list of all the key RNN formulas, explained in plain terms:
			
			### 1. Forward Pass (Making Predictions)
			**Hidden State Calculation:**
			```
			h = tanh(W_xh * x + W_hh * h_prev + b_h)
			```
			- `W_xh`: Input weights
			- `x`: Current input (e.g., [1,0,0] for "happy")
			- `W_hh`: Recurrent weights
			- `h_prev`: Previous hidden state (starts as zeros)
			- `b_h`: Hidden layer bias
			- `tanh`: Squashes values between -1 and 1
			
			**Output Calculation:**
			```
			y_raw = W_hy * h + b_y
			y = softmax(y_raw)
			```
			- `W_hy`: Output weights
			- `b_y`: Output bias
			- `softmax`: Converts to probabilities (sums to 1)
			
			### 2. Loss Calculation
			```
			Loss = -log(y[correct_answer])
			```
			- Only cares about the probability given to the correct answer
			- Lower loss = better prediction
			
			### 3. Backward Pass (Learning)
			**Output Layer Gradients:**
			```
			dy = y - target
			dW_hy = h * dy
			db_y = dy
			```
			
			**Hidden Layer Gradients:**
			```
			dh = W_hy.T * dy + (future gradient)
			dh_raw = dh * (1 - h²)  # Because of tanh
			```
			
			**Weight Updates:**
			```
			dW_xh = x * dh_raw
			dW_hh = h_prev * dh_raw
			db_h = dh_raw
			```
			
			### 4. Updating Weights
			```
			W_xh = W_xh - learning_rate * dW_xh
			W_hh = W_hh - learning_rate * dW_hh
			W_hy = W_hy - learning_rate * dW_hy
			(biases update similarly)
			```
*/

#ifndef PREPROCESśS_H
#define PREPROCESS_H

#include <cmath>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

class Model
{
	vector<double> hidden_value_update;
	public:
	void train(vector<vector<double>>& input, vector<vector<double>>& target, vector<vector<double>>& xh, vector<vector<double>>& hh, vector<vector<double>>& hy, vector<double>& h, vector<double>& y, int train)
	{
		for (int epochs = 0; epochs < train; ++epochs)
		{
			double losses = 0.0;
			for (int i = 0; i < input.size(); ++i)
			{
				double sum = 0.0;
				vector<double> temp1;
				vector<double> temp;
				vector<double> dh;
				vector<double> dh_raw;
				vector<double> loss;
				vector<double> bhy;
				vector<double> bhh;
				vector<vector<double>> why;
				vector<vector<double>> wxh;
				vector<double> hidden_value_output;
				for (int j = 0; j < xh.size(); ++j)
				{
					for (int k = 0; k < xh[0].size(); ++k)
					{
						sum += xh[j][k] * input[i][k];
					}
					temp.push_back(tanh(sum + h[j]));
					sum = 0.0;
				}
				for (int j = 0; j < hy.size(); ++j)
				{
					for (int k = 0; k < hy[0].size(); ++k)
					{
						sum += hy[j][k] * temp[k]; 
					}
					temp1.push_back(sum + y[j]);
					sum = 0.0;
				}
				softmax(temp1,hidden_value_output);
				for (int j = 0; j < target[0].size(); ++j)
				{
					if (target[i][j]==1)
					{
						losses += -log(hidden_value_output[j]);
						break;
					}
				}
				for (int j = 0; j < hidden_value_output.size(); ++j)
				{
					loss.push_back(hidden_value_output[j] - target[i][j]);
					bhy.push_back(loss.back());
				}
				for (int j = 0; j < loss.size(); ++j)
				{
					for (int k = 0; k < temp.size(); ++k)
					{
						temp1.push_back(loss[j] * temp[k]);
					}
					why.push_back(temp1);
					temp1.clear();
				}
				for (int j = 0; j < hy[0].size(); ++j)
				{
					for (int k = 0; k < hy.size(); ++k)
					{
						sum += hy[k][j] * loss[k];
					}
					dh.push_back(sum);
					sum = 0.0;
				}
				for (int j = 0; j < temp.size(); ++j)
				{
					dh_raw.push_back((1 - temp[j] * temp[j]) * dh[j]);
					bhh.push_back(dh_raw.back());
				}
				for (int j = 0; j < dh_raw.size(); ++j)
				{
					for (int k = 0; k < input[i].size(); ++k)
					{
						temp1.push_back(dh_raw[j] * input[i][k]);
					}
					wxh.push_back(temp1);
					temp1.clear();
				}
				updates(xh,0.01,wxh);
				updates(y,0.01,bhy);
				updates(hy,0.01,why);
				updates(h,0.01,bhh);
				sum = 0.0;
				temp1.clear();
				temp.clear();
				dh.clear();
				dh_raw.clear();
				loss.clear();
				bhy.clear();
				bhh.clear();
				why.clear();
				wxh.clear();
				hidden_value_output.clear();				
			}
			if (epochs % 1000 == 0)
			{
				cout << "Training Complete : " << epochs << " Loss : " << losses << endl;
			}
		}		
	}
	int predict(vector<double>& input, vector<vector<double>>& xh, vector<vector<double>>& hy, vector<double>& h, vector<double>& y)
	{
		int index;
		double sum = 0.0;
		vector<double> temp1;
		vector<double> temp;
		vector<double> final_output;
		for (int j = 0; j < xh.size(); ++j)
		{
			for (int k = 0; k < xh[0].size(); ++k)
			{
				sum += xh[j][k] * input[k];
			}
			temp.push_back(tanh(sum + h[j]));
			sum = 0.0;
		}
		for (int j = 0; j < hy.size(); ++j)
		{
			for (int k = 0; k < hy[0].size(); ++k)
			{
				sum += hy[j][k] * temp[k];
			}
			temp1.push_back(sum + y[j]);
			sum = 0.0;
		}
		softmax(temp1,final_output);
		temp1.clear();
		for (int i = 0; i < final_output.size(); ++i)
		{
			temp1.push_back(final_output[i]);
		}
		sort(final_output.begin(),final_output.end());
		for (int i = 0; i < temp1.size(); ++i)
		{
			if (temp1[i]==final_output.front())
			{
				index = i;
				break;
			}
		}
		return index;
	}
	void show(vector<vector<double>>& v)
	{
		for (int i = 0; i < v.size(); ++i)
		{
			for (int j = 0; j < v[0].size(); ++j)
			{
				cout << v[i][j] << " ";
			}
			cout << endl;
		}
	}
	void show(vector<double>& v)
	{
		for (int i = 0; i < v.size(); ++i)
		{
			cout << v[i] << " ";
		}
	}
	void softmax(vector<double>& input, vector<double> & output) 
	{
    	double maxVal = *max_element(input.begin(), input.end());
    	double sum = 0.0;
    	for (double val : input)
    	{
        	sum += exp(val - maxVal);
    	}
    	for (size_t i = 0; i < input.size(); ++i)
    	{
    		output.push_back(exp(input[i] - maxVal) / sum);
    	}
	}
	void updates(vector<vector<double>>& weights, float Learning_Rate, vector<vector<double>>& gradients)
	{
		for (int j = 0; j < weights.size(); ++j)
		{
			for (int i = 0; i < weights[0].size(); ++i)
			{
				weights[j][i] -= Learning_Rate * gradients[j][i]; 
			}
		}
	}
	void updates(vector<double>& biases, float Learning_Rate, vector<double>& gradients)
	{
		for (int j = 0; j < biases.size(); ++j)
		{
			biases[j] -= Learning_Rate * gradients[j];
		}
	}
};
#endif