#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <fstream>
#include <sstream>
#include <locale>;

using namespace std;

const string FILE_NAME = "../input.txt";

/// ���� ��� ������������� �������
class Token {
public:
    string lexeme;
    string type;

    Token(string lexeme, string type) : lexeme(lexeme), type(type) {}
};

/// ������� ��� ���������� ���� �������
string getTokenType(string lexeme) {
    if (regex_match(lexeme, regex("\\d+\\.\\d*|\\d*\\.\\d+"))) {
        return "����� � ��������� �������";
    } else if (regex_match(lexeme, regex("0x[0-9a-fA-F]+"))) {
        return "س������������ �����";
    } else if (regex_match(lexeme, regex("\\d+"))) {
        return "�����";
    } else if (regex_match(lexeme, regex("\"[^\"]*\"|'[^']*'"))) {
        return "�����";
    } else if (regex_match(lexeme, regex("//.*"))) {
        return "������������ ��������";
    } else if (regex_match(lexeme, regex("/\\*(.|\\n)*?\\*/"))) {
        return "�������������� ��������";
    } else if (
               lexeme == "if" ||
               lexeme == "else" ||
               lexeme == "while" ||
               lexeme == "for" ||
               lexeme == "public" ||
               lexeme == "static" ||
               lexeme == "void" ||
               lexeme == "class" ||
               lexeme == "int" ||
               lexeme == "long" ||
               lexeme == "char" ||
               lexeme == "float" ||
               lexeme == "double" ||
               lexeme == "boolean"
               ) {
        return "������������� �����";
    } else if (lexeme == "+" || lexeme == "-" || lexeme == "*" || lexeme == "/") {
        return "��������";
    } else if (lexeme == "=") {
        return "�������� ���������";
    } else if (lexeme == "==") {
        return "�������� ���������";
    } else if (lexeme == ";" || lexeme == "," || lexeme == "(" || lexeme == ")") {
        return "��������� ����";
    } else if (regex_match(lexeme, regex("^[a-zA-Z_][a-zA-Z0-9_]*$"))) {
        return "�������������";
    } else {
        return "����������� �������";
    }
}

int main() {
    setlocale (LC_CTYPE, "ukr");

    regex pattern(R"(;|[,()\"']+|[a-zA-Z_]\w*|0[xX][0-9a-fA-F]+|\d*\.\d+|\d+\.\d*|\d+|//[^$]*|==|=|[+\-*/])");

    vector<Token> tokens;

    ifstream file(FILE_NAME);

    if (!file.is_open()) {
        cerr << "File open error! No " << FILE_NAME << endl;
        return 0;
    }

    string line;

    while (getline(file, line)) {
        sregex_iterator it(line.begin(), line.end(), pattern);
        sregex_iterator it_end;
        while (it != it_end) {
            string lexeme = it->str();
            string type = getTokenType(lexeme);
            tokens.push_back(Token(lexeme, type));
            ++it;
        }
    }

    cout << "��������� � ������: ������� - ���" << endl;
    for (const Token& token : tokens) {
        cout << token.lexeme << " - " << token.type << endl;
    }

    return 0;
}
