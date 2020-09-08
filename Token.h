#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <string>


using namespace std;

//.i
class TOKEN {

  private:
  
	string value;

	public:

  enum Type{ INT, REG, OP, AS, EOFx};
	Type type;
  
	inline TOKEN(Type ctype, string cvalue){
		this->type = ctype;
		this->value = cvalue;
	}

	inline Type getType(){
		return this->type;
	}

	inline string getValue(){
		return this->value;
	}

	inline void setType(Type ty){
		this->type = ty;
	}

	inline void setValue(string val){
		this->value = val;
	}

  inline bool checkToken(TOKEN token){
		if(token.value.length() > 0){
			return (type == token.type && (value == token.value));
		} else {
			return (type == token.type);
		}
	}

	inline string toString(){
		string s = "";
    s += type;
    s += "- ";
    s += value;
    s += "]";
		return s;
	}

	void print(){
		cout << "<" << type <<">" << endl;
	}

};



#endif //   TOKEN_H