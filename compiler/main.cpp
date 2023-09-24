#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <experimental/optional>
#include <stdio.h>
#include <time.h>
#include <map>

#include "TokenType.c"
#include "utilities.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "generator.hpp"

using namespace std;
string getSource(const string path)
{
    /* Reads the file and returns its content */
    ifstream input(path);
    string source, line;
    while (getline(input, line))
    {
        source += line + '\n';
    }
    return source;
}
void debug(deque<Token> composed)
{
    for (unsigned short int i = 0; i < composed.size(); i++)
    {
        cout << composed.at(i).type << " | " << composed.at(i).value << endl;
    }
}
int main(int argc, char *argv[])
{
    double exec_time{0.0};
    clock_t begin = clock();
    if (argc < 2)
    {
        cerr << "Error: Not enough arguments." << endl;
        return EXIT_FAILURE;
    }
    cout << "\nCompiling " << argv[1] << "...\n-------------------------\n\n";

    string source = getSource(argv[1]);

    Lexer lexer = Lexer(source);
    deque<Token> tokens = lexer.tokenize();
    debug(tokens);

    Parser parser = Parser(tokens);
    Root exit = parser.parse();

    Generator generator = Generator(exit.childs.at(0));
    string assembly = generator.generate();

    cout << assembly << endl;

    clock_t split_t = clock();
    cout << "Split phase finished in " << (double)(split_t - begin) / CLOCKS_PER_SEC << " seconds.\n";

    fstream file("out.asm", ios::out);
    file << assembly;
    return EXIT_SUCCESS;
}