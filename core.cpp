//
// Created by Nguyen Duc Dung on 2019-02-15.
//
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>
#include <unistd.h>

using namespace std;

/// Prototype declaration
void Initialization();
void Finalization();

void LoadConfiguration();
void LoadMenu();
void DisplayMenu();
void ProcessUserChoice();
///--------------------------------------------------------------------

bool __coreInitialized = false; /// an example of global variable
int __userChoice;				/// a global variable to store user choice
bool __isExiting = false;		/// this variable should be turn on when the program exits
// TODO: add more global variables to complete tasks

struct Item
{
	string str1, str2;
};

struct Lst
{
	Item intro[256];
	int lenIntro;
	Item wel[256];
	int lenWel;
	Item menu[256];
	int lenMenu;
	double introTime;
};
Lst ret;

///--------------------------------------------------------------------
/**
 * Function: Initialization
 * Purpose:  Initialize anything necessary in your program before starting
 * Input:    None
 * Output:   None
 */
void Initialization()
{
	LoadConfiguration();
	LoadMenu();
	// TODO: write the code to initialize the program
	__coreInitialized = true;
	ret.lenIntro = ret.lenWel = ret.lenMenu = 0;
}

/**
 * Function: Finalization
 * Purpose:  Clean up everything before the program exits
 * Input:    None
 * Output:   None
 */
void Finalization()
{
	// TODO: write the code to clean up when the program exits
}

void LoadConfiguration()
{
	// TODO: write code to load data from the configuration file
	ifstream inFile("conf.json");
	string line;
	int type = 0;
	while (true)
	{
		getline(inFile, line);
		stringstream ss(line);
		string str1;
		ss >> str1;
		if (str1 == "{" || str1 == "}," || str1 == "")
		{
			continue;
		}
		else if (str1 == "}")
		{
			break;
		}

		char str[256];
		ss.getline(str, 256, '\"');
		string str0(str);
		stringstream ss0(str0);
		ss0 >> str0;

		ss.getline(str, 256, '\"');
		string str2(str);

		str1 = str1.substr(1, str1.length() - 3);

		if (str1 == "WelcomeText" && str0 == "{")
		{
			type = 1;
			continue;
		}
		else if (str1 == "Menu" && str0 == "{")
		{
			type = 2;
			continue;
		}
		else if (str1 == "IntroTime")
		{
			ret.introTime = stod(str0);
			continue;
		}

		if (type == 0)
		{
			ret.intro[ret.lenIntro].str1 = str1;
			ret.intro[ret.lenIntro].str2 = str2;
			ret.lenIntro++;
		}
		else if (type == 1)
		{
			ret.wel[ret.lenWel].str1 = str1;
			ret.wel[ret.lenWel].str2 = str2;
			ret.lenWel++;
		}
		else if (type == 2)
		{
			ret.menu[ret.lenMenu].str1 = str1;
			ret.menu[ret.lenMenu].str2 = str2;
			ret.lenMenu++;
		}
	}
	inFile.close();
}

void LoadMenu()
{
	// TODO: write code to load menu from the configuration file
	for (int i = 0; i < ret.lenWel; i++)
	{
		cout << ret.wel[i].str2 << endl;
	}
	sleep(ret.introTime);
}

void DisplayMenu()
{
	// TODO: Display the menu loaded from configuration file
	system("clear");
	for (int i = 0; i < ret.lenMenu; i++)
	{
		cout << i + 1 << ". " << ret.menu[i].str2 << endl;
	}
	cout << "Please select:" << endl;
}

bool isinteger(string const &n) noexcept
{
	if (isdigit(n[0]) || (n.size() > 1 && (n[0] == '-' || n[0] == '+')))
	{
		for (string::size_type i{1}; i < n.size(); ++i)
			if (!isdigit(n[i]))
				return false;
		return true;
	}
	return false;
}

void ProcessUserChoice()
{
	// TODO: Read user input and process
	string line;
	getline(cin, line);
	if (!isinteger(line))
	{
		cout << "Invalid input, please input an integer number." << endl;
		sleep(ret.introTime);
	}
	else
	{
		int num = stoi(line);
		if (num < 1 || num > ret.lenMenu)
		{
			cout << "Please select a number from 1 to 5." << endl;
			sleep(ret.introTime);
		}
		else
		{
			cout << ret.menu[num - 1].str2 << endl;
			__isExiting = true;
		}
	}
}
