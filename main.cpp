#include <iostream>
#include <vector>
#include <stack>
#include "reader.h"
#include "string_utils.h"

using namespace std;

int calculate_expression(const string& expr) {
    stack<int> st;
    int lhs, rhs;
    for (const auto& token: split(expr)) {
        if (isDigit(token))
            st.push(stoi(token));
        else if (token == "+") { rhs = st.top(); st.pop(); lhs = st.top(); st.pop(); st.push(lhs + rhs); }
        else if (token == "-") { rhs = st.top(); st.pop(); lhs = st.top(); st.pop(); st.push(lhs - rhs); }
        else if (token == "*") { rhs = st.top(); st.pop(); lhs = st.top(); st.pop(); st.push(lhs * rhs); }
        else if (token == "/") { rhs = st.top(); st.pop(); lhs = st.top(); st.pop(); st.push(lhs / rhs); }
    }
    return st.top();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "No file path found." << endl << "Usage: " << argv[0] << "<path-to-program-file>";
        exit(-1);
    }
    vector<string> lines = read_file(argv[1]);
    // Print the lines to verify
    for (const auto& line : lines)
        cout << line << "\t=\t" << calculate_expression(line) << endl;

    return 0;
}
