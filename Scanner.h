#ifndef SCANNER_H
#define SCANNER_H
#include "Token.h"
#include <iostream>
#include <list>
#include <vector>
#include <string>

using namespace std;

//.i
class Scanner {

    private:
    //Used in Scanner constructor
    int iERROR = 999;
    //Used in scan method:
    int iMatrixTransition[6][4] = { 
      {2, iERROR, 2, iERROR}, 
      {1, 1, iERROR, 103},
      {3, iERROR, iERROR, iERROR},
      {104, iERROR, iERROR, iERROR},
      {0, 101, 102, iERROR},
      {iERROR, iERROR, iERROR, iERROR}};
    char c;
    int iState;
    int iIndex;
    string sValue;
    vector<TOKEN> tokens;
    //tokens = new vector<TOKEN>;


    public:

    inline Scanner(){

      /*
      Matrix
             |    0   |   1   |   2   |   3   |
      ------------------------------------------------
      DIGIT  |   2    |  999  |   2   |  999  |
      ------------------------------------------------
      LETTER |   1    |   1   |  999  |  103  | 
      ------------------------------------------------
      #      |   3    |  999  |  999  |  999  |
      ------------------------------------------------
      ;      |  104   |  999  |  999  |  999  |
      ------------------------------------------------
      SPACE  |   0    |  101  |  102  |  999  | 
      ------------------------------------------------
      OTHER  |   999  |  999  |  999  |  999  |

      */
   
    }
    
    inline vector<TOKEN> scan(string s){
      iState = 0;
      iIndex = 0;
      //Check 
      while(iIndex<s.length()){
        sValue="";
        do{
          c=s[iIndex];
          cout<<"state: "<<iState<<" char: "<<c<<" ";
          iIndex++;
          iState=iMatrixTransition[filter(c)][iState];
          cout<<"state: "<<iState<<endl;
          if(iState>0){
            if(isspace(c)){
							sValue+=c;
						}
          }
        }while(iIndex<s.length() && iState<100);
        //Identify the state
        switch(iState){
          case 0:
            return tokens; 
						break;
            
          //INTEGER case
          case 102:
            tokens.push_back( TOKEN (TOKEN::INT,sValue));
            break;
          //Invalid argument case
          case 999:
            sValue+=c;
						if(filter(c)!=4){
              cout<<"LEXICAL ERROR: INVALID ARGUMENT"<<endl;

            }
            
            //return 0; 
						break;
            //Register Case
          case 103:
            //Filter correct values of register
            if(sValue=="#A"||sValue=="#B"||sValue=="#C"||sValue=="#D"){
              tokens.push_back(TOKEN(TOKEN::REG, sValue));
            }
            break;
          case 101:
            //Filter correct values of operator
            if(sValue=="SUM"||sValue=="SUB"||sValue=="MUL"||sValue=="DIV"){
              tokens.push_back( TOKEN(TOKEN::OP, sValue));
            }
            else if(sValue=="MOV"){
              tokens.push_back(TOKEN(TOKEN::AS, sValue));
            }
            case 104:
              tokens.push_back(TOKEN(TOKEN::EOFx, sValue));
            break;
        }
        iState=0;
      }
      return tokens;
    }

    inline int filter(char c){
      //SPACE
			if(isspace(c)){
        return 4;
      }
      //LETTER
      if(c > 64 && c < 91){
        return 1;
      }
      //DIGIT
      if(c > 47 && c < 58){
        return 0;
      }
      //#
      if(c == '#'|| c==35){
        return 2;
      }
      //; END
      if(c == ';' || c==59){
        return 3;
      }
      return iERROR;
    }

};

#endif //   SCANNER_H