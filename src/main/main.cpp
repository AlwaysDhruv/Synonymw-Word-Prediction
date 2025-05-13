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
    Model model1;
    Preprocess_Txt pre;
    vector<string> input_string;
    vector<string> target_string;
    vector<vector<double>> input;
    vector<vector<double>> target;
    vector<vector<double>> wxh;
    vector<vector<double>> whh;
    vector<vector<double>> why;
    vector<double> bh;
    vector<double> by;
    while(true)
    {
        cout << "Train On New Words For Press[1]"  << endl;
        cout << "Predict The  Words For Press[2] " << endl;
        cout << "Clear Screen       For Press[3] " << endl;
        cout << "Exit For Press [0] " << endl;
        cout << "Enter Your Choise :- ";
        cin >> n;
        if (n==1)
        {
            wxh.clear();
            whh.clear();
            why.clear();
            bh.clear();
            by.clear();
            input.clear();
            target.clear();
            input_string.clear();
            target_string.clear();
            ifstream file("Txt_File_Path");
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
            pre.one_hot_encoding(input, input_string);
            pre.one_hot_encoding(target, target_string);
            rand.random(wxh,whh,why,input.size(),"Hidden_Size");
            rand.random(bh,by,target.size(),"Hidden_Size");
            cout << "How Many Times To Train The Model :- ";
            cin >> train;
            model1.train(input,target,wxh,whh,why,bh,by,train);
            cout << endl << endl;
            cout << "======================================" << endl;
            cout << "Model Are Ready To Prediction...." << endl;
            cout << "======================================" << endl;
            cout << endl << endl;
        }
        else if (n==2)
        {
            string input_str;
            cout << endl << endl;
            cout << "Enter Word To Find Nearest Meaning :- ";
            cin >> input_str;
            cout << endl << endl;
            for (int i = 0; i < input_string.size(); ++i)
            {
                if (input_string[i]==input_str)
                {
                    cout << endl << endl;
                    cout << "======================================" << endl;
                    cout << target_string[model1.predict(input[i],wxh,whh,why,bh,by)] << endl;
                    cout << "======================================" << endl;
                    cout << endl << endl;
                }
            }
        }
        else if (n==3)
            clearScreen();
        else
        {
            break;
        }
    }
    return 0;
}
void clearScreen()
{
    system("cls");
}