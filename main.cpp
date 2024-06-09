#include <iostream>
#include <fstream>
#include <string>
#include <map>



bool fileIsEmpty(const std::string& fileName);


//file writing/reading
std::map<std::string, std::pair<std::string, std::string>> readFile(const std::string& fileName);
void writeFile(const std::string& fileName, const std::string& choreName, const std::string& choreDescription, const std::string& choreDate);


//menus
void addChoreMenu();
void viewChoresMenu();
void mainMenu();


int main()
{
	mainMenu();

	return 0;
}


void writeFile(const std::string& fileName, const std::string& choreName, const std::string& choreDescription, const std::string& choreDate)
{
	std::ofstream file(fileName, std::ios::app);

	if (file.is_open())
	{
		file << choreName << std::endl;
		file << choreDescription << std::endl;
		file << choreDate << std::endl;
	}

	file.close();
}

bool fileIsEmpty(const std::string& fileName)
{
	std::ifstream file(fileName);

	//if its equal to eof return true else return false
	return file.peek() == std::ifstream::traits_type::eof();
}


std::map<std::string, std::pair<std::string, std::string>> readFile(const std::string& fileName)
{
	//the name is a key and the choreAttributes variable is the value
	std::map<std::string, std::pair<std::string, std::string>> data;

	std::string choreName, choreDescription, choreDate;
	//description and date
	std::pair<std::string, std::string> choreAttributes;

	std::ifstream file(fileName);

	if (file.is_open())
	{
		/*the info in the file goes as:
		- line 1: chore name
		- line 2: chore Description
		- line 3: chore date*/


		std::string line;
		int lineNum = 1;
		
		while (std::getline(file, line))
		{
			switch (lineNum)
			{
				case 1:
					choreName = line;
					break;
				case 2:
					choreDescription = line;
					break;
				case 3:

					//since its the last line of our chore info and we have the chore name, description and date, make the std::pair and append the info into the std::map

					choreDate = line;

					choreAttributes = { choreDescription, choreDate };
					data[choreName] = choreAttributes;

					//make the lineNum 0, because it will be 1 because of the lineNum++
					lineNum = 0;
					break;
			}
			lineNum++;
		}
	}

	file.close();
	return data;
}

void mainMenu()
{
	int choice;

	system("CLS");

	std::cout << "----TO DO LIST----\n";
	std::cout << "1. Add a chore\n";
	std::cout << "2. View chores\n";
	std::cout << "3. Exit\n";

	std::cout << "Input:";
	std::cin >> choice;

	switch (choice)
	{
	case 1:
		addChoreMenu();
		break;

	case 2:
		viewChoresMenu();
		break;

	case 3:
		std::exit(0);

	default:
		system("CLS");
		std::cout << "Wrong option!\n";
		break;
	}
}

void addChoreMenu()
{
	int choresNum, choice;
	std::string choreName, choreDescription, choreDate;

	system("CLS");

	std::cout << "----ADD A CHORE----\n";
	
	std::cout << "Number of chores:";
	std::cin >> choresNum;

	std::cin.ignore();
	for (int i = 0; i < choresNum; i++)
	{
		system("CLS");
		std::cout << "Chore name:";
		std::getline(std::cin, choreName);

		std::cout << '\n';

		std::cout << "Chore description:";
		std::getline(std::cin, choreDescription);

		std::cout << '\n';

		std::cout << "Chore date(DD-MM-YYYY):";
		std::getline(std::cin, choreDate);

		writeFile("chores.txt", choreName, choreDescription, choreDate);
	}
	
	std::cout << "1. Return to menu\n";
	std::cout << "Any other number. exit\n";
	std::cout << "Input:";
	std::cin >> choice;

	choice == 1 ? mainMenu() : std::exit(0);


}

void viewChoresMenu()
{

	//no chores menu
	if (fileIsEmpty("chores.txt"))
	{
		int choice;

		system("CLS");
		std::cout << "No chores added yet!\n";

		std::cout << "1. Return to menu\n";
		std::cout << "Any other Number. Exit";

		std::cin >> choice;

		choice == 1 ? mainMenu() : std::exit(0);
	}

	//chores greater than 0 menu
	else
	{
		int choice;

		std::map<std::string, std::pair<std::string, std::string>> data = readFile("chores.txt");
		std::map<std::string, std::pair<std::string, std::string>>::iterator itr;


		//print the chore data
		system("CLS");
		for (itr = data.begin(); itr != data.end(); itr++)
		{
			std::string choreName = itr->first;

			std::pair<std::string, std::string> choreAttributes = itr->second;

			std::string choreDescription = choreAttributes.first;
			std::string choreDate = choreAttributes.second;

			std::cout << "=================\n";
			std::cout << "CHORE NAME:" << choreName << std::endl;
			std::cout << "CHORE DESCRIPTION:" << choreDescription << std::endl;
			std::cout << "CHORE DATE:" << choreDate << std::endl;
		}


		std::cout << "1. Return to menu\n";
		std::cout << "Any other number. exit\n";
		std::cout << "Input:";
		std::cin >> choice;

		choice == 1 ? mainMenu() : std::exit(0);
	}

}