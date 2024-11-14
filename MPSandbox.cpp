// this code counts for time complexity of cpp programs.
#include <iostream>
#include <string>
#include <vector>

using namespace std;
vector<string> decomposer(string);

// global testers
string case1 = "int x = 10, y = 8, z = -2;  x = x + y; y = x - y; x = x - y; z = x + y;\n";



int main(){
    cout << "Hello love goodbye"<<endl;

    vector<string> decomposed_string = decomposer(case1);

    for(int i=0; i<decomposed_string.size(); i++){
        cout << decomposed_string[i] << endl;
    }
}

vector<string> decomposer(string input)
{
    int j,i=0;
    string line = "";
    vector<string> out;

    while(input[i]!='\n'){
        if(input[i] == ';'){
            out.push_back(line);
            line = "";
            i++;
            continue;
        }
        if(input[i+1] == '\n'){
            out.push_back(line);
            break;
        }
        line += input[i];
        i++;
    }
    return out;
}


