#include "Praser.h"
#include "Scanner.h"
#include "Token.h"
#include <iostream>
#include <fstream>
#include <list>


using namespace std;
int main() {
  //Initial objects and variables
  Praser praser;
  Scanner scanner;
  vector<TOKEN> tokens;
  ifstream ifFile;
  string sLine;

  //Inside de parentesis you need to write the file name
  ifFile.open("File1.txt");

  //Reading file
  while(!ifFile.eof()){

    getline(ifFile,sLine);
    cout << sLine << endl;
    
    tokens = scanner.scan(sLine);
  
    praser.parse(tokens);
    
  }

  ifFile.close();
  return 0;
}