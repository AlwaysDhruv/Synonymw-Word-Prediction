#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

class Preprocess_Txt
{
    private:
    vector<int> space_index;
    public:
    int strlen(string str);
    int space_index_no(string str);
    void tokenize(vector<string>& output,string str);
    void One_Hot_Encoding(vector<vector<double>>& output, vector<string>& input);
};

using namespace std;

int main()
{
    ifstream file("E:\\Dhruv\\NLP\\dialogs.txt");
    string line;
    Preprocess_Txt pre;
    vector<string> result;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            pre.tokenize(result,line);
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file!" << endl;
    }
    vector<vector<double>> final_output;
    pre.One_Hot_Encoding(final_output,result);
    for (int i = 0; i < final_output.size(); ++i)
    {
        for (int j = 0; j < final_output[i].size(); ++j)
        {
            cout << final_output[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

int Preprocess_Txt::strlen(string str)
{
    int ct = 0;
    for (int i = 0; i < str[i]!='\0'; ++i)
    {
        ++ct;
    }
    return ct;
}

int Preprocess_Txt::space_index_no(string str)
{
    for (int i = 0; i < strlen(str); ++i)
    {
        if(str[i]==' ')
        {
            space_index.push_back(i);
        }
    }
    return 0;
}

void Preprocess_Txt::tokenize(vector<string>& output,string str)
{
    int ct = 0;
    space_index_no(str);
    vector<char> v;
    string resuly = "";
    for (int i = 0; i < space_index.size(); ++i)
    {
        for (int j = ct; j < space_index[i]; ++j)
        {
            if(str[ct] != '!' && str[ct] != ',' && str[ct] != '.' && str[ct] != '?' &&
            str[ct] != ':' && str[ct] != ';' && str[ct] != '\'' && str[ct] != '"' &&
            str[ct] != '(' && str[ct] != ')' && str[ct] != '[' && str[ct] != ']' &&
            str[ct] != '{' && str[ct] != '}' && str[ct] != '<' && str[ct] != '>' &&
            str[ct] != '-' && str[ct] != '_' && str[ct] != '/' && str[ct] != '\\' &&
            str[ct] != '@' && str[ct] != '#' && str[ct] != '$' && str[ct] != '%' &&
            str[ct] != '^' && str[ct] != '&' && str[ct] != '*' && str[ct] != '+' &&
            str[ct] != '=' && str[ct] != '|' && str[ct] != '~' && str[ct] != '`' && str[ct] != ' ')
            {
                v.push_back(str[j]);
            }
            ++ct;
        }
        for(char ch : v)
        {
            resuly += ch;
        }
        output.push_back(resuly);
        resuly = "";
        v.clear();
    }
    for (int i = ct; i < strlen(str); ++i)
    {
        if(str[ct] != '!' && str[ct] != ',' && str[ct] != '.' && str[ct] != '?' &&
        str[ct] != ':' && str[ct] != ';' && str[ct] != '\'' && str[ct] != '"' &&
        str[ct] != '(' && str[ct] != ')' && str[ct] != '[' && str[ct] != ']' &&
        str[ct] != '{' && str[ct] != '}' && str[ct] != '<' && str[ct] != '>' &&
        str[ct] != '-' && str[ct] != '_' && str[ct] != '/' && str[ct] != '\\' &&
        str[ct] != '@' && str[ct] != '#' && str[ct] != '$' && str[ct] != '%' &&
        str[ct] != '^' && str[ct] != '&' && str[ct] != '*' && str[ct] != '+' &&
        str[ct] != '=' && str[ct] != '|' && str[ct] != '~' && str[ct] != '`' && str[ct] != ' ')
        {
            v.push_back(str[i]);
        }
        ++ct;
    }
    for(char ch : v)
    {
        resuly += ch;
    }
    output.push_back(resuly);
    cout << endl;
    v.clear();
    resuly = "";
    ct = 0;
    space_index.clear();
}

void Preprocess_Txt::One_Hot_Encoding(vector<vector<double>>& output, vector<string>& input)
{
    vector<double> temp;
    for (int i = 0; i < input.size(); ++i)
    {
        for (int j = 0; j < input.size(); ++j)
        {
            temp.push_back(0);    
        }
        temp.erase(temp.begin() + i);
        temp.insert(temp.begin() + i,1);
        output.push_back(temp);
        temp.clear();
    }
}