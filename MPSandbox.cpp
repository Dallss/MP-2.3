#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;


// Function declarations
int assignmentCounter(string);
string processInput();
vector<int> forCounter(string);

// Global testers
string case1 = "int x = 10, y = 8, z = -2;  x = x + y; y = x - y; x = x - y; z = x + y;\n";

string nestedLoopCase = "for (int i = 0; i < rows; ++i) for (int j = 0; j < cols; ++j) matrix[i][j] = i * cols + j;";

// Decomposes input into individual lines of code.
vector<string> decomposer(const string &input)
{
    vector<string> out;
    string line = "";
    for (char c : input) {
        if (c == ';') {
            out.push_back(line + ";");
            line = "";
        } else {
            line += c;
        }
    }
    return out;
}


regex hasEqualPattern("=");
regex hasForPattern("for");
// Identifies the type of code line based on regex matches.
string lineIdentifier(const string line){
    if (regex_search(line, hasEqualPattern))
        return "assignment";
    else if (regex_search(line, hasForPattern))
        return "for";
    // else if ()
    //     return "if statement";
    // else if ()
    //     return "if-else statement";
    // else if ()
    //     return "for_loop";
    else {
        cout << "Error: Unidentified line:\n" << line << endl;  //catches invalid lines || unaccounted for
        return "unidentified";
    }
}

vector<int> lineCounter(string line){
    vector<int> out;
    string lineType = lineIdentifier(line);
    if(lineType == "assignment"){
        //add to last element
        out.back() += assignmentCounter(line); 
    }
    else if(lineType == "for"){
        //call forCounter. it should return an element/elemtss
        vector<int> toAppend = forCounter(line);
        out.insert(out.end(), toAppend.begin(), toAppend.end()); // Appends result of forCounter 

    }
    else{
        out.push_back(-9999);
        return out;
    }
    return out;
}


int assignmentCounter(string input){
    std::regex pattern("(=|\\+|\\-|\\*|\\/)");
    std::sregex_iterator iter(input.begin(), input.end(), pattern);
    std::sregex_iterator end;

    int count = 0;
    while (iter != end) {
        std::cout << "Found operator: " << iter->str() << std::endl;
        ++iter;
        ++count;
    }

    std::cout << "Total matches: " << count << std::endl;

    return 0;
}

vector<int> forCounter(string input){
    vector<int> out;

    //process for;
    out = lineCounter(input);
    
    return out;
    
}

void printVector(vector<int> in){
    cout << "Vector: ";
    for(int i=0; i< in.size(); i++){
        cout << in[i] <<", ";
    }
}

//run locally : g++ -o parser MPSandbox.cpp  
string processInput() {
    cout << "Processing input" << endl;

    int n = 0;            // Number of strings to process
    string out = "";      // Final output string
    string temp = "";     // Temporary string for input

    // Read the first input as a number
    cin >> n;  // This will read the number of lines (if that's your intent)

    cin.ignore();  // To ignore the newline character after reading the number

    // Read the next `n` lines and append them to `out`
    for (int i = 0; i < n; i++) {
        getline(cin, temp);   // Read the entire xline
        out.append(temp);      // Append the line to the output without a newline
    }
    return out;
}



int main(){
    string out = processInput();
    cout <<endl<< out;

    return 0;
}