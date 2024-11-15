#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;


// Function declarations
int assignmentCounter(string);
string processInput();
vector<int> forCounter(string, int);

// Global testers
string case1 = "int x = 10, y = 8, z = -2;  x = x + y; y = x - y; x = x - y; z = x + y;\n";

string nestedLoopCase = "for (int i = 0; i < rows; ++i) for (int j = 0; j < cols; ++j) matrix[i][j] = i * cols + j;";

// Decomposes input into individual lines of code.
vector<string> decomposer(const string &input) {
    vector<string> out;
    string line = "";
    int brace_count = 0; // Tracks whether we're inside a block (e.g., for loops or if statements)

    for (char c : input) {
        if (c == '{') {
            brace_count++; // Entering a block
            line += c;
        } else if (c == '}') {
            brace_count--; // Exiting a block
            line += c;

            if (brace_count == 0) { // If the block is complete
                out.push_back(line);
                line = "";
            }
        } else if (c == ';' && brace_count == 0) {
            // End of a simple statement
            line += c;
            out.push_back(line);
            line = "";
        } else {
            line += c; // Continue adding characters
        }
    }

    // Add any remaining line (for cases where there's no semicolon or braces at the end)
    if (!line.empty()) {
        out.push_back(line);
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

vector<int> lineCounter(string line, int iterations = 1) {
    vector<int> out;
    string lineType = lineIdentifier(line);

    if (lineType == "assignment") {
        int assignment_cost = assignmentCounter(line);
        out.push_back(assignment_cost * iterations);
    } else if (lineType == "for") {
        // Call forCounter with `n` iterations
        vector<int> loop_costs = forCounter(line, iterations);
        out.insert(out.end(), loop_costs.begin(), loop_costs.end());
    } else {
        cout << "Error: Unidentified line: " << line << endl;
        out.push_back(-9999); // Error value
    }
    return out;
}



int assignmentCounter(string input) {
    regex assignment_pattern("(=|\\+=|-=|\\*=|/=|%=)"); // Matches any assignment operation
    sregex_iterator iter(input.begin(), input.end(), assignment_pattern);
    sregex_iterator end;

    int count = 0;
    while (iter != end) {
        ++iter;
        ++count;
    }
    return count;
}


vector<int> forCounter(string input, int iterations) {
    vector<int> costs;

    // Assume each loop runs `n` iterations
    int loop_iterations = iterations;

    // For the sake of example, let's assume the input includes lines separated by ';'
    vector<string> loop_body = decomposer(input);

    for (const string& line : loop_body) {
        int line_cost = assignmentCounter(line) * loop_iterations;
        costs.push_back(line_cost);
    }
    return costs;
}


void printVector(vector<int> in){
    cout << "Vector: ";
    for(int i=0; i< in.size(); i++){
        cout << in[i] <<", ";
    }
}

//run locally : g++ -o parser MPSandbox.cpp  
string processInput() {
    int n;
    cin >> n; // Number of lines
    cin.ignore(); // Ignore newline character

    string input, line;
    for (int i = 0; i < n; ++i) {
        getline(cin, line);
        input += line + "\n";
    }

    vector<string> lines = decomposer(input);
    int fixed_cost = 0;
    int loop_cost = 0;

    for (const string& line : lines) {
        if (lineIdentifier(line) == "assignment") {
            fixed_cost += assignmentCounter(line);
        } else if (lineIdentifier(line) == "for") {
            vector<int> loop_contribution = lineCounter(line, 1); // Assume 1 iteration initially
            for (int cost : loop_contribution) {
                loop_cost += cost;
            }
        }
    }

    string complexity = "T(n) = " + to_string(loop_cost) + "n + " + to_string(fixed_cost);
    return complexity;
}


int main() {
    string case1 = R"(int x = -2, y = 9, min = 0;
cin >> x;
cin >> y;
min = x;
if (y < min) {
    min = y;
}
x = min;
y = x;
if (x == y) {
    x = x + y;
    y = x - y;
    x = x - y;
}
min = y < x;)";

    // Call the decomposer function
    vector<string> statements = decomposer(case1);

    // Print each decomposed statement
    for (const string &stmt : statements) {
        cout << "[" << stmt << "]" << endl;
    }

    return 0;
}

// int main(){
//     string out = processInput();
//     cout <<endl<< out;

//     return 0;
// }