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

	bool operator>(Item &a)
	{
		return this->str1 > a.str1;
	}

	bool operator<(Item &a)
	{
		return this->str1 < a.str1;
	}

	bool operator>=(Item &a)
	{
		return this->str1 >= a.str1;
	}

	bool operator<=(Item &a)
	{
		return this->str1 <= a.str1;
	}
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

enum MyType
{
	INTRO,
	WELCOME,
	MENU
};

void sort_List_Item(Item lst[], int len)
{
	for (int i = 0; i < len; i++)
		for (int j = i; j < len; j++)
			if (lst[i] > lst[j])
			{
				Item temp = lst[i];
				lst[i] = lst[j];
				lst[j] = temp;
			}
}

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
	MyType type = INTRO;
	while (true)
	{
		getline(inFile, line);
		stringstream ss(line);
		string str1;
		ss >> str1;
		if (str1 == "{" || str1 == "")
		{
			continue;
		}
		else if (str1 == "},")
		{
			type = INTRO;
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
			type = WELCOME;
			continue;
		}
		else if (str1 == "Menu" && str0 == "{")
		{
			type = MENU;
			continue;
		}
		else if (str1 == "IntroTime")
		{
			ret.introTime = stod(str0);
			continue;
		}

		if (type == INTRO)
		{
			ret.intro[ret.lenIntro].str1 = str1;
			ret.intro[ret.lenIntro].str2 = str2;
			ret.lenIntro++;
		}
		else if (type == WELCOME)
		{
			ret.wel[ret.lenWel].str1 = str1;
			ret.wel[ret.lenWel].str2 = str2;
			ret.lenWel++;
		}
		else if (type == MENU)
		{
			ret.menu[ret.lenMenu].str1 = str1;
			ret.menu[ret.lenMenu].str2 = str2;
			ret.lenMenu++;
		}
	}
	sort_List_Item(ret.wel, ret.lenWel);
	sort_List_Item(ret.menu, ret.lenMenu);
	inFile.close();
}

void LoadMenu()
{
	// TODO: write code to load menu from the configuration file
	for (int i = 0; i < ret.lenWel; i++)
	{
		cout << ret.wel[i].str2 << endl;
	}
	// sleep(ret.introTime);
}

void DisplayMenu()
{
	// TODO: Display the menu loaded from configuration file
	// system("clear");
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

void get(string _str)
{
	if (_str == "Introduction")
	{
		for (int i = 0; i < ret.lenIntro; i++)
		{
			cout << ret.intro[i].str1 << ": " << ret.intro[i].str2 << endl;
		}
		sleep(ret.introTime);
		system("clear");
		LoadMenu();
	}
	else if (_str == "Login")
	{
		cout << "Chức năng đang trong quá trình phát triển!" << endl;
		sleep(ret.introTime);
		system("clear");
		LoadMenu();
	}
	else if (_str == "Registration")
	{
		cout << "Chức năng đang trong quá trình phát triển!" << endl;
		sleep(ret.introTime);
		system("clear");
		LoadMenu();
	}
	else if (_str == "Help")
	{
		cout << "Bạn muốn giúp đỡ, vui lòng liên hệ thầy Dũng :v" << endl;
		sleep(ret.introTime);
		system("clear");
		LoadMenu();
	}
	else if (_str == "Exit")
	{
		cout << "exiting..." << endl;
		__isExiting = true;
	}
	else
	{
		cout << "Chức năng không tồn tại trong hệ thống, vui lòng liên hệ K' Đen để thêm chức năng này!" << endl;
		sleep(ret.introTime);
		system("clear");
		LoadMenu();
	}
	
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
		system("clear");
		LoadMenu();
	}
	else
	{
		int num = stoi(line);
		if (num < 1 || num > ret.lenMenu)
		{
			cout << "Please select a number from 1 to 5." << endl;
			sleep(ret.introTime);
			system("clear");
			LoadMenu();
		}
		else
		{
			get(ret.menu[num-1].str2);
		}
	}
}
