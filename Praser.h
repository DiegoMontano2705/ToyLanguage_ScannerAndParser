#ifndef PRASER_H
#define PRASER_H
#include <iostream>
#include <vector>
#include "Token.h"
#include <string>


using namespace std;

//.i
class Praser {

    private:
		enum Type{ INT, REG, OP, AS, EOFx};
    Type type;
    
		public:
    
    //Empty Constructor
    inline Praser(){}

    inline void parse(vector<TOKEN> tokens){
			parseS(tokens);
			cout << "Valid Input" << endl;
		}

    inline void parseS(vector<TOKEN> tokens){
      //Empty token
			if(tokens.size() == 0){
				//Error no token
        cout << "ERROR: Token not founded" << endl;
        return;
			}

      //END
			if(tokens[0].getType() == TOKEN::EOFx){
				// EOF
        match(tokens, TOKEN(TOKEN::EOFx,";"));
        return;
			}

			switch(tokens[0].getType()){
				// OP
				case TOKEN::OP:
          cout << "OPERATION" << endl;
					match(tokens, TOKEN(TOKEN::OP, ""));
					match(tokens, TOKEN(TOKEN::REG, ""));
					break;
				// AS
				case TOKEN::AS:
          cout << "ASSIGMMENT" << endl;
					match(tokens, TOKEN(TOKEN::AS,"MOV"));
					if(tokens[0].getType() == TOKEN::REG){
						match(tokens, TOKEN(TOKEN::REG, ""));
					} else if(tokens[0].getType() == TOKEN::INT) {
						match(tokens, TOKEN(TOKEN::INT, ""));
					}
					break;

				default:
				break;
          cout << "ERROR" << endl;
					return;
			}

			match(tokens, TOKEN(TOKEN::REG, ""));
			parseS(tokens);

		}

		inline bool match(vector<TOKEN> tokens, TOKEN expectedToken){
			if((tokens.size() != 0) && tokens[0].checkToken(expectedToken)){
				tokens.erase(tokens.begin());
				return true;
			} else {
				if(tokens.size() == 0){
					cout << "ERROR IN TOKEN: Size = 0" << endl;
				} 
			}
			return false;
		}


};

#endif //   PRASER_H