#include <cstdlib>
#include <windows.h>
#include <commdlg.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../Preprocessing/Preprocess.h"
#include "../Weights_Biases/Values.h"
#include "../Training/Train.h"

using namespace std;

void clearScreen();

int main()
{
    int n;
    string line;
    Random rand;
    double train;
    Model model;
    vector<double> bh;
    vector<double> by;
    Preprocess_Txt pre;
    vector<double> temp;
    vector<vector<double>> wxh;
    vector<vector<double>> whh;
    vector<vector<double>> why;
    vector<string> vocab_string;
    vector<string> input_string;
    vector<string> target_string;
    vector<vector<double>> input;
    vector<vector<double>> target;
    ifstream file("E:\\Dhruv\\Vanilla2\\Test.txt");
    if (file.is_open())
    {
        while (getline(file, line))
        {
            pre.tokenize(input_string, target_string, line);
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file!" << endl;
    }
    for (int i = 0; i < input_string.size(); ++i)
    {
        pre.one_hot_encoding(temp,input_string.size() + target_string.size(),i);
        input.push_back(temp);
        temp.clear();
    }
    for (int i = input_string.size(); i < input_string.size() + target_string.size(); ++i)
    {
        pre.one_hot_encoding(temp,input_string.size() + target_string.size(),i);
        target.push_back(temp);
        temp.clear();
    }
    rand.random(wxh,whh,why,input.size() + target.size(),4);
    rand.random(bh,by,input.size() + target.size(),4);
    model.train(input,target,wxh,whh,why,bh,by,1000);

    cout << target_string[model.predict(input[1],wxh,why,bh,by)];
    return 0;
}
void clearScreen()
{
    system("cls");
}