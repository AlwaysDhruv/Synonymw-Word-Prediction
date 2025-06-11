/*
This Header File Are used for data preprocess.
It will convert data(raw) into the suitable formate that model can understand and process on data.
Example - 
    Sentence :- “Everything  Are  The  Inspiration  Of God  Made!!”
        Step 0. Input Data :-
            1.  Upload File (eg..txt)

        Step 1 . Data Preprocessing :- 
            1.  Text Cleaning :-
                a.  Lowercase :-
                    i.   everything  are  the  inspiration  of god made!!
                b.  Remove Special Or Punctuation Characters And Numbers(IF Not Needed) :-
                    i.  everything are  the  inspiration  of god made
                c.  Remove Extra Spaces :-
                    i.  everything are the inspiration of god made
                d.  Stop Word :- 
                    i.  everything inspiration god made
            2.  Tokenization :- 
                a.  Split Words Into Tokens :-
                    i.  ['everything', 'inspiration', 'god', 'made']
            3.  Vocabulary Building :-
                i.  ['everything' : 1 , 'inspiration' : 2, 'god' : 3, 'made' : 4]
            4.  Text To Sequence :-
                i.  ['everything', 'inspiration', 'god', 'made'] -> [1,2,3,4]
            5.  One Hot Encoding (Data):-
                i.  1 -> [1,0,0,0]
                ii. 2 -> [0,1,0,0]
                iii.    3 -> [0,0,1,0]
                iv. 4 -> [0,0,0,1]

                (Final Result)

        “Everything  Are  The  Inspiration  Of God  Made!!”

                            To 

        [1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]
*/

#ifndef PREPROCESS_H
#define PREPROCESS_H

#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

//Class For Preprocess Txt File
class Preprocess_Txt
{
    private:
    vector<int> space_index;
    public:

    //Check Stanza Or Sentence Lenght How Many Words in that!!        
    int strlen(string str)
    {
        int ct = 0;
        for (int i = 0; i < str[i]!='\0'; ++i)
        {
            ++ct;
        }
        return ct;
    }

    //How Many Space In The Stanza Or Sentence That will Give Space Index Number
    int space_index_no(string str)
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

    //Convert All words into the tokens and remove all special character and spaces
    void tokenize(vector<string>& input, vector<string>& target, vector<string>& vocab, string str)
    {
        int ct = 0;
        string resuly = "";
        vector<char> v;
        vector<string> temp;
        space_index_no(str);
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
            input.push_back(resuly);
            vocab.push_back(resuly);
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
        target.push_back(resuly);
        vocab.push_back(resuly);
        v.clear();
        resuly = "";
        ct = 0;
        space_index.clear();
        temp.clear();
    }

    //convert all tokens to one hot values
    void one_hot_encoding(vector<double>& output, int size, int index)
    {
        vector<double> v;
        for (int i = 0; i < size; ++i)
        {
            output.push_back(0);    
        }
        output.erase(output.begin() + index);
        output.insert(output.begin() + index,1);
    }
    int word2index(vector<string>& v, string str)
    {
        int n;
        for (int i = 0; i < v.size(); ++i)
        {
            if (v[i]==str)
            {
                n = i + 1;
            }
        }
        return n;
    }
};
#endif