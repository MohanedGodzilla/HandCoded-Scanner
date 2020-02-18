#include<iostream>
#include<fstream>
#include<string>
using namespace std;
string s="";
enum Token {
	PROGRAM_BEGIN,IS_TOKEN,BEGIN_TOKEN,END_TOKEN,VAR_TOKEN,INTEGER_SY,BOOL_TOKEN,WRITE_TOKEN,READ_TOKEN,SIMI_COLON,ASSIGN_SY,
	 ID,IF_TOKEN,THEN_TOKEN,ENDIF_TOKEN,ELSE_TOKEN,WHILE_TOKEN,DO_TOKEN,ENDWHILE_TOKEN,OR_TOKEN,RELATION_TOKEN,COMA_SY,
	 AND_TOKEN,TRUE_TOKEN,FALSE_TOKEN,PLUS_TOKEN,MINUS_TOKEN,DIVISION_TOKEN,MULTI_TOKEN,NUMBERAL_TOKEN,COLOUN_SY,NOT_TOKEN,
	 LPARN, RPARN, END_SOURCE_SY, ERROR_SY };
class Scanner
{
	public:
		Scanner(string filename);
		~Scanner(void);
		Token get_token(void);
		void display_tokens(void);
	private:
		ifstream f;
		Token check_reserved(string s)
		{
			if (s== "program") 
				return PROGRAM_BEGIN;
			else if (s== "is")
				return IS_TOKEN;
			else if (s== "begin")
				return BEGIN_TOKEN;
			else if (s== "end")
				return END_TOKEN;
			else if (s== "var")
				return VAR_TOKEN;
			else if (s== "integer")
				return INTEGER_SY;
			else if (s== "boolean")
				return BOOL_TOKEN;
			else if (s== "if")
				return IF_TOKEN;
			else if (s== "then")
				return THEN_TOKEN;
			else if (s== "else")
				return ELSE_TOKEN;
			else if (s== "while")
				return WHILE_TOKEN;
			else if (s== "do")
				return DO_TOKEN;
			else if (s== "or")
				return OR_TOKEN;
			 else if (s== "and")
				return AND_TOKEN;
			else if (s== "NOT")
				return NOT_TOKEN;
			 else if (s== "true")
				return TRUE_TOKEN;
			 else if (s== "false")
				return FALSE_TOKEN;
			else return ID;
		}
};

Scanner::Scanner(string filename)
{
	f.open(filename);
	if (!f)
	{
		cout<<"Unable to open file"<<endl;
		system("pause");
		exit(1);
	}
}
Scanner::~Scanner(void)
{
	f.close();
}
	
Token Scanner::get_token(void)
{
	char ch;
	f.get(ch);
	while( !f.eof() && isspace(ch)) 
	{
		f.get(ch);
	}
	if ( f.eof())
		return END_SOURCE_SY;
	else if (ch == '(')
		return LPARN;
	else if (ch == ')')
		return RPARN;
	 else if (ch == ':') {
			   f.get(ch);
			   if (isspace(ch)) return COLOUN_SY;
			   else if (ch == '=') return ASSIGN_SY;
			   else {
				   f.putback(ch);
				   return COLOUN_SY;
			   }
		   }
	 else if (ch == ',') return COMA_SY;
	else if (ch == ';')
		return SIMI_COLON;
	else if (ch == '+')
		return PLUS_TOKEN;
	else if (ch == '*')
		return MULTI_TOKEN;
	else if (ch == '-')
		return MINUS_TOKEN;
	else if (ch == '/')
		return DIVISION_TOKEN;
	else if (ch == '=')
		return RELATION_TOKEN;
	else if (ch == '<')
	{
		return RELATION_TOKEN;
		f.get(ch);
		if (ch == '>'||ch=='=')
			return RELATION_TOKEN;
		else return ERROR_SY;
	}
	else if (ch == '>')
	{
		return RELATION_TOKEN;
		f.get(ch);
		if (ch == '=')
			return RELATION_TOKEN; 
		else 
			return ERROR_SY; 
	}
	
	else if (isalpha(ch))
	{
		s = ch; 
		f.get(ch);
		while (!f.eof() && isalnum(ch))
		{ 
			s += ch;
			f.get(ch); 
		}
		f.putback(ch);
		check_reserved(s);
	}
	else if ( isdigit(ch)) // output either real or integer
	{ 
		s = ch; 
		f.get(ch);
		while (!f.eof() && isdigit(ch))
		{ 
			s += ch; 
			f.get(ch); 
		}
		if (ch != '.')
		{
			f.putback(ch); 
			return NUMBERAL_TOKEN; 
		}
	}
	else return ERROR_SY;
};
void Scanner::display_tokens(void)
{
	Token t=get_token();
	while(t!= END_SOURCE_SY)
	{
		switch (t)
		{
			case ERROR_SY: cout << "lexical error: illegal token"<<endl; break;
			case PROGRAM_BEGIN: cout << "program token"<<endl ; break;
			case IS_TOKEN: cout << "is token"<<endl ; break;
			case VAR_TOKEN: cout << "var token"<<endl; break;
			case INTEGER_SY: cout << "integer token"<<endl ; break;
			case BEGIN_TOKEN: cout << "begin token"<<endl ; break;
			case BOOL_TOKEN: cout << "boolean token"<<endl ; break;
			case ID: cout << "id token"<<endl; break;
			case IF_TOKEN: cout << "if token"<<endl ; break;
			case THEN_TOKEN: cout << "then token"<<endl; break;
			case ELSE_TOKEN: cout << "else token"<<endl ; break;
			case WHILE_TOKEN: cout << "while token"<<endl; break;
			case END_TOKEN : cout<< "end token"<<endl; break;
			case DO_TOKEN: cout << "do token"<<endl; break;
			case COLOUN_SY: cout << "colon token"<<endl; break;
			case COMA_SY: cout << "coma token"<<endl; break;
			case ASSIGN_SY: cout << "assign token"<<endl; break;
			case SIMI_COLON: cout << "simiColon token"<<endl; break;
			case OR_TOKEN: cout << "or token"<<endl; break;
			case AND_TOKEN: cout << "and token"<<endl; break;
			case TRUE_TOKEN: cout << "true token"<<endl; break;
			case FALSE_TOKEN: cout << "false token"<<endl; break;
			case RELATION_TOKEN: cout << "relation token"<<endl ; break;
			case PLUS_TOKEN: cout << "+ is token" <<endl; break;
			case MINUS_TOKEN: cout << "- is token"<<endl; break;
			case MULTI_TOKEN: cout << "* is token"<<endl; break;
			case DIVISION_TOKEN: cout << "/ is token"<<endl; break;
			case NUMBERAL_TOKEN: cout << "number token" <<endl; break;
			case LPARN: cout << "lparn token"<<endl ; break;
			case RPARN: cout << "rparn token"<<endl ; break;

		}
		t = get_token();
	}

	if (t== END_SOURCE_SY) 
	{
		cout << "end_of_file " << endl;
	}
}
void main()
{
	string InName;
	cout << "Enter Name of input File : ";
	cin >> InName;
	Scanner in(InName);
	in.display_tokens();
	system("pause");
}