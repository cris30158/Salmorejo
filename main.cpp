#include "Quarzum.h"
/*

    Minimal main.cpp, all the procedures are into Quarzum.h

*/
int main(int argc, char *argv[])
{
    /*
    Throw error if file is not found or there is an invalid format
    */
    if (argc < 2)
    {
        throwError(FILE_NOT_FOUND);
    }
    validateFormat(argv);
    chechForConfigFile(argv[1]);
    string a;
    // If all is correct, compile the source code
    compile(getSource(argv[1]));

    return 0;
}