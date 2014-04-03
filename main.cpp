#include<iostream>
#include<sstream>
#include<vector>
#include"Histogram.h"
using namespace std;

bool isRunning=true;
stringstream ss;

vector<Histogram> v;
int a,b;

void print()	// bez argumentow
{
	cout << a << ": " << v[a];// << "\n";
}
void printall()	// bez argumentow
{
	for(int i=0; i<v.size(); i++) cout << i << ": " << v[i];
//	cout << "\n";
}
void howmany()	// bez argumentow
{
	cout << v.size() << "\n";
}
void quit()	// bez argumentow
{
	isRunning = false;
}
void newhist()	// bez argumentow
{
	Histogram h;
	v.push_back(h);
}
void set1()	// jeden argument
{
	unsigned int t;
	ss >> t;
	if (t>=v.size()) throw "Index out of range.";
	a=t;
}
void set2()	// jeden argument
{
	unsigned int t;
	ss >> t;
	if (t>=v.size()) throw "Index out of range.";
	b=t;
}
void addh()	// bez argumentow
{
	v.push_back(v[a]+v[b]);
}
void subh()	// bez arg
{
	v.push_back(v[a]-v[b]);
}
void mulh()	// bez arg
{
	v.push_back(v[a]*v[b]);
}
void addval()	// 2 arg - key, value
{
	keydata key;
	valdata val;
	ss >> key >> val;
	v[a].addValue(key,val);
}
void subval()	// 2 arg - key, value
{
	keydata key;
	valdata val;
	ss >> key >> val;
	v[a].subValue(key,val);
}
void setval()	// 2 arg - key, value
{
	keydata key;
	valdata val;
	ss >> key >> val;
	v[a].setValue(key,val);
}
void getval()	// 1 arg - key
{
	keydata key;
	ss >> key;
	cout << v[a].getValue(key) << "\n";
}

void help()
{
	cout << "print - wypisuje zawartosc histogramu wskazanego przez set1\n";
	cout << "printall - wypisuje zawartosc wszystkich histogramow\n";
	cout << "howmany - wypisuje licznosc histogramow\n";
	cout << "quit - wychodzi z programu\n";
	cout << "newhist - tworzy nowy histogram\n";
	cout << "set1 - ustawia pierwszy indeks pomocniczy\n";
	cout << "set2 - ustawia drugi indeks pomocniczy\n";

	cout << "addh - dodaje histogramy (wynik wrzuca jako nowy histogram)\n";
	cout << "subh - odejmuje histogramy (j/w)\n";
	cout << "mulh - mnozy histogramy - generuje przeciecie (j/w)\n";

	cout << "addval - dodaje wartosc do histogamu wskazanego przez set1\n";
	cout << "subval - odejmuje wartosc od histogramu wskazanego przez set1\n";
	cout << "setval - ustawia wartosc w histogramie wskazanym przez set1\n";

	cout << "getval - wypisuje wartosc\n";
	cout << "debug - wypisuje wiadomosc diagnostyczna\n";
	
}

void debug()
{
	string buf;
	while(!ss.eof())
	{
		ss >> buf;
		cout << buf << " ";
	}
	cout << "\n";
}

void parse(const string exp)
{
//	ss.str(string());
	ss.str("");
	ss.clear();
	ss << exp;
	
	string cmd;
	ss >> cmd;

	if (cmd == "print") print();	// wypisuje zawartosc histogramu wskazanego przez set1
	else if (cmd == "printall") printall();	// wypisuje zawartosc wszystkich histogramow
	else if (cmd == "howmany") howmany();	// wypisuje licznosc histogramow
	else if (cmd == "quit") quit();	// wychodzi z programu
	else if (cmd == "newhist") newhist();	// tworzy nowy histogram
	else if (cmd == "set1") set1();	// ustawia pierwszy indeks pomocniczy
	else if (cmd == "set2") set2();	// ustawia drugi indeks pomocniczy

	else if (cmd == "addh") addh();	// dodaje histogramy (wynik wrzuca jako nowy histogram)
	else if (cmd == "subh") subh();	// odejmuje histogramy (j/w)
	else if (cmd == "mulh") mulh();	// mnozy histogramy - generuje przeciecie (j/w)

	else if (cmd == "addval") addval();	// dodaje wartosc do histogamu wskazanego przez set1
	else if (cmd == "subval") subval();	// odejmuje wartosc od histogramu wskazanego przez set1
	else if (cmd == "setval") setval();	// ustawia wartosc w histogramie wskazanym przez set1

	else if (cmd == "getval") getval();	// wypisuje wartosc
	else if (cmd == "help") help();	// wypisuje pomoc
	else if (cmd == "debug") debug();	// wypisuje wiadomosc diagnostyczna
	else throw "Illegal command.";

	return;
}

int main(int argc, char** argv)
{
	v.push_back(Histogram());
	string command;
	int line=0;
	while (isRunning)
	{
		line++;
		getline(cin, command);
		if(command == "" || command[0]=='#') continue;
		try
		{
			parse(command);
		}
		catch(...)
		{
			cerr << "Parse error in line " << line << ":\n";
			cerr << command << "\n";
		//	return 1;
		}
	}
	return 0;
}

