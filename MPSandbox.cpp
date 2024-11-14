#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

// Function declarations
vector<string> decomposer(const string &input);
string lineIdentifier(const string &line);

// Global testers
string case1 = "int x = 10, y = 8, z = -2;  x = x + y; y = x - y; x = x - y; z = x + y;\n";

// Regular expressions
regex declaration_regex(R"((int|float|double|char)\s+\w+\s*=\s*[^;]+;)");
regex assignment_regex(R"(\b\w+\s*=\s*[^;]+;)");
regex if_regex(R"(\bif\s*\(.*\))");
regex if_else_regex(R"(\bif\s*\(.*\)\s*\{.*\}\s*else\s*\{.*\})");
regex for_regex(R"(\bfor\s*\(.*;.*;.*\))");

int main(){
    cout << "Analyzing the code...\n";

    vector<string> decomposed_string = decomposer(case1);

    for(const string &line : decomposed_string){
        cout << line << " --> " << lineIdentifier(line) << endl;
    }

    return 0;
}

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

// Identifies the type of code line based on regex matches.
string lineIdentifier(const string &line){
    if (regex_match(line, declaration_regex))
        return "declaration";
    else if (regex_match(line, assignment_regex))
        return "assignment";
    else if (regex_match(line, if_regex))
        return "if statement";
    else if (regex_match(line, if_else_regex))
        return "if-else statement";
    else if (regex_match(line, for_regex))
        return "for loop";
    else {
        cout << "Error: Unidentified line:\n" << line << endl;
        return "unidentified";
    }
}
