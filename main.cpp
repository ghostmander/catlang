/*! \file main.cpp
    \brief Binds everything together.
    \todo Move lexer specific parts to its own header
    \todo Add functionality to be able to use both postfix and infix notation.
*/
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include "reader.h"
#include "string_utils.h"

using namespace std;

/**Quick utility function to convert all inxfix math into postfix notation.
 * This function uses the shunting yard algorithm to convert infix notation to postfix notation.
 * The function uses a stack to keep track of the operators and operands. It involves the following steps:
 * -# For all the input tokens, Read the next token;
 *   -# If token is an operator (x):
 *     -# While there is an operator (y) at the top of the operators stack and either (x) is left-associative and its precedence is less or equal to that of (y), or (x) is right-associative and its precedence is less than (y):
 *       -# Move (y) from the stack to output buffer;
 *     -# Push (x) on the stack;
 *   -# Else If token is left parenthesis, then push it on the stack;
 *   -# Else If token is a right parenthesis:
 *     -# Until the top token (from the stack) is left parenthesis, pop from the stack to the output buffer;
 *     -# Also pop the left parenthesis but don't include it in the output buffer;
 *   -# Else add token to output buffer.
 * -# While there are still operator tokens in the stack, pop them to output
 *
 * @param infix Infix expression to convert into postfix
 * @return Returns a vector of tokens in polish postfix notation
 */
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

/**
 * Evaluator class to manage all variables and program counters in the future.
 * The class will have a map of variables and their values. It will also have a function to evaluate the program.
 * This will be moved to a separate file in the future.
 */
class Evaluator {
public:
    unordered_map<string, int> variable_map = {}; ///< Map of variables and their values

    /**
     * Function to calculate the expression from the postfix notation.
     * This will call the infix_to_rpn function to convert the infix expression to postfix notation. It will then process postfix notation to calculate the result.
     * @param expr Expression to calculate
     * @return Returns the result of the expression
     */
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

    /**
     * This function will evaluate the line and store the result in the variable map, if required.
     * @param line The line to be evaluated.
     */
    void evaluate_line(const string &line) {
        vector<string> line_comps = split(line, "=", true);
        int res = calculate_expression(line_comps[line_comps.size() - 1]);
        if (line_comps.size() == 2)
            variable_map[line_comps[0]] = res;
        cout << line << " = " << res << endl;
    }

    /**
     * This will execute the program line by line.
     * @param lines Code array, split line wise
     */
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
