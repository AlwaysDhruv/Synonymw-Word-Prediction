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
	void train(vector<vector<double>> input, vector<vector<double>> target, vector<vector<double>>& xh, vector<vector<double>>& hh, vector<vector<double>>& hy, vector<double>& h, vector<double>& y, int train)
	{
		int ct = 0;
		double sum = 0.0;
		double losses = 0.0;
		vector<double> temp1;
		vector<double> temp2;
		vector<double> temp3;
		vector<vector<double>> temp;
		vector<vector<double>> temp4;
		vector<vector<double>> temp5;
		vector<vector<double>> temp6;
		vector<vector<double>> temp7;
		vector<double> loss;
		vector<vector<double>> error;
		vector<double> bhy;
		vector<double> bhh;
		vector<vector<double>> why;
		vector<vector<double>> wxh;
		vector<vector<double>> whh;
		vector<vector<double>> hidden_value_output;
		for (int i = 0; i < xh.size(); ++i)
		{
			hidden_value_update.push_back(0.0);
		}
		for (int epochs = 0; epochs < train; ++epochs)
		{
			for (int i = 0; i < input.size(); ++i)
			{
				//h = tanh(W_xh * x + W_hh * h_prev + b_h)
				while(ct!=xh.size())
				{
					temp1.push_back(xh[ct][i] * input[i][i]);
					++ct;
				}
				ct = 0;
				for (int j = 0; j < hh.size(); ++j)
				{
					while(ct!=hh[0].size())
					{
						sum += hh[ct][j] * hidden_value_update[ct];
						++ct;
					}
					temp2.push_back(sum);
					sum = 0.0;
					ct = 0;
				}
				for (int j = 0; j < temp2.size(); ++j)
				{
					temp3.push_back(tanh(temp1[j] + temp2[j] + h[j]));
				}
				temp.push_back(temp3);
				temp1.clear();
				temp2.clear();
				ct = 0;
				sum = 0.0;

				//y_raw = W_hy * h + b_y
				for (int j = 0; j < hy[0].size(); ++j)
				{
					for (int i = 0; i < hy.size(); ++i)
					{
						sum += hy[i][j] * temp3[ct];
		 				++ct;
		 				if (ct==temp3.size())
		 				{
		 					ct = 0;
	 					}
	 				}
	 				ct = 0;
	 				temp2.push_back(sum + y[j]);
	 				sum = 0.0;
				}
				temp3.clear();

				//y = softmax(y_raw)
				softmax(temp2,temp3);

				//Loss = -log(y[correct_answer])
				losses += -log(temp3[i]);
				hidden_value_output.push_back(temp3);

				//hidden value update for output prediction
				for (int i = 0; i < temp3.size(); ++i)
				{
					hidden_value_update.push_back(temp3[i]);
				}
				ct = 0;
				sum = 0.0;
				temp1.clear();
				temp2.clear();
				temp3.clear();
				temp4.clear();
			}

			//Displaying Total Loss
			cout << "Train Time : " << epochs + 1 << " Loss : " << losses << endl;
			losses = 0.0;

			//dy = y - target
			for (int i = 0; i < hidden_value_output.size(); ++i)
			{
				for (int j = 0; j < hidden_value_output[0].size(); ++j)
				{
					temp1.push_back(hidden_value_output[i][j] - target[i][j]);
				}
				error.push_back(temp1);
				temp1.clear();
			}
			sum = 0.0;
			for (int i = 0; i < error[0].size(); ++i)
			{
				for (int j = 0; j < error.size(); ++j)
				{
					sum += error[j][i];
				}
				//db_y = dy
				bhy.push_back(sum);
				sum = 0.0;
			}

			//dW_hy = h * dy
			ct = 0;
			int tc = 0;
			for (int k = 0; k < error.size(); ++k)
			{
				for (int i = 0; i < temp[0].size(); ++i)
				{
					for (int j = 0; j < error[0].size(); ++j)
					{
						temp1.push_back(temp[tc][i] * error[k][j]);
					}
					temp4.push_back(temp1);
					temp1.clear();
				}
				++tc;
				if (k==0)
				{
					for (int i = 0; i < temp4.size(); ++i)
					{
						for (int j = 0; j < temp4[0].size(); ++j)
						{
							temp1.push_back(0);
						}
						temp5.push_back(temp1);
						temp1.clear();
					}
				}
				for (int i = 0; i < temp4.size(); ++i)
				{
					for (int j = 0; j < temp4[0].size(); ++j)
					{
						temp1.push_back(temp4[i][j] + temp5[i][j]);
					}
					temp6.push_back(temp1);
					temp1.clear();
				}
				temp5.clear();
				for (int i = 0; i < temp6.size(); ++i)
				{
					for (int j = 0; j < temp6[0].size(); ++j)
					{
						temp1.push_back(temp6[i][j]);
					}
					temp5.push_back(temp1);
					temp1.clear();
				}
				if(k==(error.size() - 1))
				{
					for (int i = 0; i < temp6.size(); ++i)
					{
						for (int j = 0; j < temp6[0].size(); ++j)
						{
							temp1.push_back(temp6[i][j]);
						}
						why.push_back(temp1);
						temp1.clear();
					}
				}
				temp6.clear();
				temp4.clear();
			}

			sum = 0.0;
			for (int j = 0; j < error.size(); ++j)
			{
				for (int i = 0; i < hy.size(); ++i)
				{
					for (int k = 0; k < hy[0].size(); ++k)
					{
						sum += error[j][k] * hy[i][k];
					}
					temp1.push_back(sum);
					sum = 0.0;
				}

				//dh_raw = dh * (1 - h²)
				for (int i = 0; i < temp1.size(); ++i)
				{
					temp2.push_back(temp1[i] * (1 - (tanh(temp[j][i]) * tanh(temp[j][i]))));
				}
				if (j!=0)
					temp6.push_back(temp2);

				//dW_xh = x * dh_raw
				wxh.push_back(temp2);
				temp1.clear();
				temp2.clear();
			}

			//dW_hh = h_prev * dh_raw
			temp5.clear();
			for (int i = 0; i < temp6.size(); ++i)
			{
				for (int j = 0; j < temp6[0].size(); ++j)
				{
					temp1.push_back(0);
				}
				temp5.push_back(temp1);
				temp1.clear();
			}
			tc = 0;
			for (int i = 1; i < temp.size(); ++i)
			{
				for (int k = 0; k < temp[i].size(); ++k)
				{
					for (int l = 0; l < temp6[0].size(); ++l)
					{
						temp1.push_back(temp[i][k] * temp6[tc][l]);
					}
					temp4.push_back(temp1);
					temp1.clear();
				}
				++tc;
				for (int j = 0; j < temp4.size(); ++j)
				{
					for (int i = 0; i < temp4[0].size(); ++i)
					{
						temp1.push_back(temp4[j][i] + temp5[j][i]);
					}
					temp7.push_back(temp1);
					temp1.clear();
				}
				temp5.clear();
				for (int j = 0; j < temp7.size(); ++j)
				{
					for (int i = 0; i < temp7[0].size(); ++i)
					{
						temp1.push_back(temp7[j][i]);
					}
					temp5.push_back(temp1);
					temp1.clear();
				}
				if(i==(temp.size() - 1))
				{
					for (int j = 0; j < temp7.size(); ++j)
					{
						for (int i = 0; i < temp7[0].size(); ++i)
						{
							temp1.push_back(temp7[i][j]);
						}
						whh.push_back(temp1);
						temp1.clear();
					}
				}
				temp7.clear();
				temp4.clear();			
			}

			//db_h = dh_raw
			sum = 0.0;
			for (int i = 0; i < wxh[0].size(); ++i)
			{
				for (int j = 0; j < wxh.size(); ++j)
				{
					sum += wxh[j][i];
				}
				bhh.push_back(sum);
				sum = 0.0;
			}

			//W_xh = W_xh - learning_rate * dW_xh
			//W_hh = W_hh - learning_rate * dW_hh
			//W_hy = W_hy - learning_rate * dW_hy
			//b_hy = b_hy - learning_rate * db_hy
			//b_hh = W_hh - learning_rate * db_hh
			updates(hy,0.01,why);
			updates(y,0.01,bhy);
			updates(xh,0.01,wxh);
			updates(hh,0.01,whh);
			updates(h,0.01,bhh);
			ct = 0;
			tc = 0;
			sum = 0.0;
			wxh.clear();
			whh.clear();
			why.clear();
			bhh.clear();
			bhy.clear();
			temp.clear();
			temp1.clear();
			temp2.clear();
			temp3.clear();
			temp4.clear();
			temp5.clear();
			temp6.clear();
			temp7.clear();
			loss.clear();
			error.clear();
			hidden_value_output.clear();		
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
	int predict(vector<double> input, vector<vector<double>>& xh, vector<vector<double>>& hh, vector<vector<double>>& hy, vector<double>& h, vector<double>& y)
	{
		int ct = 0;
		double sum = 0.0;
		vector<double> temp1;
		vector<double> temp2;
		vector<double> temp3;
		vector<double> temp;
		vector<vector<double>> temp4;
		for (int i = 0; i < xh.size(); ++i)
		{
			hidden_value_update.push_back(0.0);
		}
		for (int i = 0; i < input.size(); ++i)
		{
			if (input[i]==1)
			{
				while(ct!=xh[0].size())
				{
					temp1.push_back(xh[i][ct] * input[i]);
					++ct;
				}
				for (int i = 0; i < temp1.size(); ++i)
				{
					temp.push_back(tanh(temp1[i] + h[i]));
				}
			}
		}
		for (int i = 0; i < hy[0].size(); ++i)
		{
			for (int j = 0; j < hy.size(); ++j)
			{
				sum += hh[j][i] * temp[j];			
			}
			temp2.push_back(sum + y[i]);
			sum = 0.0;
		}
		sum = 0.0;
		softmax(temp2,temp3);
		temp2.clear();
		int max;
		for (int i = 0; i < temp3.size(); ++i)
		{
			sum += temp3[i];
		}
		for (int i = 0; i < temp3.size(); ++i)
		{
			temp2.push_back(temp3[i] / sum);
		}
		vector<double> v;
		for (int i = 0; i < temp3.size(); ++i)
		{
			v.push_back(temp3[i]);
		}
		cout << endl;
		sort(temp3.begin(),temp3.end());
		for (int i = 0; i < v.size(); ++i)
		{
			if (temp3.back()==v[i])
			{
				max = i;
			}
		}
		return max;
	}
};
#endif