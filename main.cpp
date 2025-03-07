#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include "reader.h"
#include "string_utils.h"

using namespace std;

vector<string> infix_to_rpn(const string& infix) {
    stack<string> st;
    vector<string> output;
    unordered_map<string, pair<int, string>> opPrec = {
            { "+", make_pair(0, "L") },  // ADDITION
            { "-", make_pair(0, "L") },  // SUBTRACTION
            { "/", make_pair(5, "L") },  // DIVISION
            { "*", make_pair(5, "L") },  // MULTIPLICATION
            { "%", make_pair(5, "L") },  // MODULUS
            { "^", make_pair(10, "R") }, // EXPONENT
    };
    for (const auto &token: split(infix)) {
        if (opPrec.count(token) != 0) {
            while (!st.empty() && opPrec.count(st.top()) != 0 &&
                   ((opPrec[token].second == "L" && opPrec[token].first <= opPrec[st.top()].first) ||
                    (opPrec[token].second == "R" && opPrec[token].first < opPrec[st.top()].first))) {
                output.push_back(st.top());
                st.pop();
            }
            st.push(token);
        }
        else if (token == "(")
            st.push(token);
        else if (token == ")") {
            while (!st.empty() && st.top() != "(") {
                output.push_back(st.top());
                st.pop();
            }
            st.pop();
        }
        else
            output.push_back(token);
    }
    while (!st.empty()) {
        output.push_back(st.top());
        st.pop();
    }
    return output;
}


class Evaluator {
    unordered_map<string, int> variable_map = {};

    int calculate_expression(const string &expr) {
        stack<int> st;
        int lhs, rhs;


        for (const auto &token: infix_to_rpn(expr)) {
            if (isDigit(token))
                st.push(stoi(token));
            else if (variable_map.count(token))
                st.push(variable_map[token]);
            else if (token == "+") {
                rhs = st.top();
                st.pop();
                lhs = st.top();
                st.pop();
                st.push(lhs + rhs);
            }
            else if (token == "-") {
                rhs = st.top();
                st.pop();
                lhs = st.top();
                st.pop();
                st.push(lhs - rhs);
            }
            else if (token == "*") {
                rhs = st.top();
                st.pop();
                lhs = st.top();
                st.pop();
                st.push(lhs * rhs);
            }
            else if (token == "/") {
                rhs = st.top();
                st.pop();
                lhs = st.top();
                st.pop();
                st.push(lhs / rhs);
            }
        }
        return st.top();
    }
public:
    void evaluate_line(const string &line) {
        vector<string> line_comps = split(line, "=", true);
        int res = calculate_expression(line_comps[line_comps.size() - 1]);
        if (line_comps.size() == 2)
            variable_map[line_comps[0]] = res;
        cout << line << " = " << res << endl;
    }

    void evaluate_program(const vector<string>& lines) {
        for (const auto& line : lines)
            evaluate_line(line);
        for (const auto& [key, value] : variable_map)
            cout << "Key:[" << key << "] Value:[" << value << "]\n";
    }
};




int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "No file path found." << endl << "Usage: " << argv[0] << "<path-to-program-file>";
        exit(-1);
    }
    vector<string> lines = read_file(argv[1]);
//    for (const auto& tok : infix_to_rpn("A ^ 2 + 2 * A * B + B ^ 2"))
//        cout << tok << ' ';
//    cout << endl;
    Evaluator evaluator;
    evaluator.evaluate_program(lines);
    // Print the lines to verify
//    for (const auto& line : lines)
//        cout << line << "\t=\t" << calculate_expression(line) << endl;

    return 0;
}
