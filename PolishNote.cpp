#include <iostream>
#include <string>
#pragma warning (disable: 4996)
using namespace std;

int PolishTranslator(char** str, int counter)
{
	int **stack = new int*[256];
	for (int i = 0; i < 12; ++i)
		stack[i] = new int;
	int *res = new int;
	int Top = -1;

	for (int i = 0; i < counter; i++)
	{
		if ((strcmp(str[i], "+") == 0 || strcmp(str[i], "-") == 0 || strcmp(str[i], "*") == 0 || strcmp(str[i], "/") == 0))
		{
			if (Top < 1) throw "incorrect note";
			if ((strcmp(str[i], "+") == 0))
			{
				*res = *stack[Top] + *stack[Top - 1];
			}

			if (strcmp(str[i], "-") == 0)
			{
				*res = *stack[Top - 1] - *stack[Top];
			}

			if (strcmp(str[i], "*") == 0)
			{
				*res = *stack[Top] * *stack[Top - 1];
			}

			if (strcmp(str[i], "/") == 0)
			{
				if (*stack[Top] == 0) throw "u can't devide by zero";
				*res = *stack[Top - 1] / *stack[Top];
			}

			Top = Top - 1;
			*stack[Top] = *res;
		}
		else 
		{
			Top++;
			*stack[Top] = atoi(str[i]);
		}
	}
	if (Top != 0) throw "Incorrect note";
	return *stack[Top];
}

int main()
{
	cout << "give me the string with \" \" as delims:" << endl;
	char* expression = new char[255];
	cin.getline(expression, 255);

	char** str = new char*[255];	//итоговая строка

	char* buf;	//промежуточная строка
	int counter = 0;

	buf = strtok(expression, " ");

		while (buf != NULL)
		{
			int f = 0;
			if (strcmp(buf, "+") == 0 || strcmp(buf, "-") == 0 || strcmp(buf, "*") == 0 || strcmp(buf, "/") == 0)
			{
				f = 1;
			}

			if (f) {
				str[counter] = buf;
				counter++;
			}
			else
			{
				f = 1;
				int x = 0;
				if (buf[0] == '-') x = 1;
				for (; x < strlen(buf) && f; x++) {
					if (!isdigit(buf[x])) f = 0;
				}

				if (f) {
					str[counter] = buf;
					counter++;
				}
			}
			buf = strtok(NULL, " ");
		}

		try
		{
			cout << "the result is " << PolishTranslator(str, counter) << endl;
		}
		/*catch (int *stack[])
		{
			cout << "U can't divide by 0" << endl;
		}*/
		catch (const char* str)
		{
			cout << "Incorrect, try again" << endl;
		}
		
	system("pause");
	return 0;
}