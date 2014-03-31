#include<iostream>
#include<sstream>
using namespace std;

bool isRunning=true;
stringstream buf;

string parse(const string exp)
{
	buf.str(string());
	buf << exp;
	
	string cmd;
	buf >> cmd;

	switch(cmd)
	{
		case "print":	// prints content of actual
	}

}

int main()
{
	string command;
	int line=0;
	while (isRunning)
	{
		line++;
		getline(cin, command);
		try
		{
			cout << parse(command) << '\n';
		}
		catch(...)
		{
			cerr << "Parse error in line " << line << ":\n";
			cerr << command;
			return 1;
		}
	}
	return 0;
}

