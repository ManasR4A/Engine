#include "iostream"
#include "conio.h"
#include "Containers/String/String.h"

// A CUSTOM FUNCTION TO TAKE INPUTOF A STRING UNTILL THE USER INPUTS <ENTER> AND RETURNS A POINTER TO THE MALLOCED STRING;
char* GetString()
{
	char i_ch = NULL;
	int count = 1;
#pragma warning (disable:6011) // DISABLED THIS WARNING CUZ THE FUNCTION WILL ONLY BE CALLED IF THERE IS A STRING TO TAKE IN

	// initialize the string with \0
	char* string = (char*)malloc(count);
	string[0] = '\0';

	// adding new chars until enter is pressed
	while (1)
	{
		i_ch = static_cast<char>(_getch()); // gets single char input
		if (i_ch != '\r') // checks if the char is not enter
		{
			std::cout << i_ch; // prints the char on screen to give the user a visual confirmation
			char* temp = _strdup(string); // making a temp copy of the string in a new allocated memory
			char* navTemp = temp, * navString;

			count++;
			free(string);
			// #pragma warning (disable:6011)
			string = (char*)malloc(count);
			navString = string;

			// copy the temp string byte by byte
			while (*navTemp != '\0')
			{
				*navString = *navTemp;
				navTemp++;
				navString++;
			}
			free(temp);
			// adding the new char at the end and also adding the \0 at the end
			*navString = i_ch;
			navString++;
			*navString = '\0';
		}
		else
			break;
	}
	std::cout << " " << count << "\n";
	return string;
}