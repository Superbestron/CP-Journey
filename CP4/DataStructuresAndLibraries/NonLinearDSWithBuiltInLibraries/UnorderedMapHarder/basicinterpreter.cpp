#include <bits/stdc++.h>

using namespace std;

unordered_map<char, int> variables;

void print(string& parse) {
    if (parse[0] == '\"') cout << parse.substr(1, parse.size() - 2);
    else cout << variables[parse[0]];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int label, curr_label = INT32_MAX;
    string s, command;
    map<int, string> instructions;
    while (cin >> label) {
        getline(cin, s);
        instructions[label] = s;
        curr_label = min(curr_label, label);
    }

    start:
    auto it = instructions.find(curr_label);
    while (it != instructions.end()) {
        string instruction = it->second;
        int end = instruction.find(' ', 1);
        command = instruction.substr(0, end);
        instruction.erase(0, command.size() + 1);

        if (command == " LET") {
            istringstream parse(instruction);
            string variable, action, op1, op2;
            // skip the '='
            parse >> variable >> op1 >> op1;
            int val1, val2;
            if (isupper(op1[0])) val1 = variables[op1[0]];
            else val1 = stoi(op1);
            // check if just a single operand
            if (!parse.eof()) {
                parse >> action >> op2;
                if (isupper(op2[0])) val2 = variables[op2[0]];
                else val2 = stoi(op2);
                if (action == "+") val1 += val2;
                else if (action == "-") val1 -= val2;
                else if (action == "*") val1 *= val2;
                else val1 /= val2;
            }
            // save the result
            variables[variable[0]] = val1;
        } else if (command == " PRINT") {
            print(instruction);
        } else if (command == " PRINTLN") {
            print(instruction);
            cout << '\n';
        } else {
            istringstream parse(instruction);
            string op1, action, op2, jump;
            parse >> op1 >> action >> op2;
            bool condition;
            int val1, val2;
            if (isupper(op1[0])) val1 = variables[op1[0]];
            else val1 = stoi(op1);
            if (isupper(op2[0])) val2 = variables[op2[0]];
            else val2 = stoi(op2);
            if (action == "=") condition = val1 == val2;
            else if (action == ">") condition = val1 > val2;
            else if (action == "<") condition = val1 < val2;
            else if (action == "<>") condition = val1 != val2;
            else if (action == "<=") condition = val1 <= val2;
            else condition = val1 >= val2;
            if (condition) {
                parse >> jump >> jump >> jump;
                curr_label = stoi(jump);
                goto start;
            }
        }
        it++;
    }
}