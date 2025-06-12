#include <cstdlib>
#include <windows.h>
#include <commdlg.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Preprocess.h"
#include "Values.h"
#include "Train.h"

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
        while (getline(file, line)) pre.tokenize(input_string, target_string, vocab_string, line);
        file.close();
    }
    else cout << "Unable to open file!" << endl;
    for (int i = 0; i < input_string.size(); ++i)
    {
        int index;
        vector<double> temp;
        for (int j = 0; j < vocab_string.size(); ++j)
            if (input_string[i]==vocab_string[j])
            {
                index = j;
                break;
            }
        pre.one_hot_encoding(temp,vocab_string.size(),index);
        input.push_back(temp);
        temp.clear();
    }
    for (int i = 0; i < target_string.size(); ++i)
    {
        int index;
        vector<double> temp;
        for (int j = 0; j < vocab_string.size(); ++j)
            if (target_string[i]==vocab_string[j])
            {
                index = j;
                break;
            }
        pre.one_hot_encoding(temp,vocab_string.size(),index);
        target.push_back(temp);
        temp.clear();
    }
    rand.random(wxh,whh,why,vocab_string.size(),4);
    rand.random(bh,by,vocab_string.size(),4);
    model.train(input,target,wxh,whh,why,bh,by,10000);
    for (int i = 0; i < input.size(); ++i) cout << vocab_string[model.predict(input[i],wxh,why,bh,by)] << endl;
    return 0;
}
void clearScreen()
{
    system("cls");
}