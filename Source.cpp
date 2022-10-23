#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char *procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();	
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen: 
		You sent me: Test
Return:
	100 is returned to the C++	
*/
int callIntFunc(string proc, string param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char *paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void Menu() {
	/*Creates the display menu that allows user input for 4 different options.
	Menu selection will be created in a loop that ends when Exit option is selected.
	*/
	bool program_Run = true;  //runs do while loop
	bool correct_Input;
	int user_Choice;          //takes input for menu choice
	string grocery_Type;      //takes input for type of grocery item to be looked up





	do {


		cout << endl;
		cout << "******************************************************************************" << endl;
		cout << "***                       Menu:  Select an option                          ***" << endl;
		cout << "******************************************************************************" << endl;
		cout << endl;
		cout << "******************************************************************************" << endl;
		cout << "***   1. Print List: Amount of Each Purcahsed Item                         ***" << endl;
		cout << "***   2. Print: Amount of Specified Product Purchased                      ***" << endl;
		cout << "***   3. Display Text Histogram                                            ***" << endl;
		cout << "***   4. Exit                                                              ***" << endl;
		cout << "******************************************************************************" << endl;
		cout << endl;

		try {
			std::cin >> user_Choice;
			cout << "******************************************************************************" << endl;
			cout << endl;
			//To catch error if input is not an integer
			//Code found at: http://www.cplusplus.com/reference/istream/istream/ignore/
			while (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(256, '\n');
				cout << "Invalid Entry. Please Try Again." << endl;

				cout << "Please enter only 1, 2, 3, or 4." << endl;
				std::cin >> user_Choice;
				cout << "******************************************************************************" << endl;
				cout << endl;
			}
			if (user_Choice >= 0) {
				//Passes the try test
				//Makes sure the user entered a POSITIVE integer
				//exits the do-while
				correct_Input = true;
			}
			else { throw (user_Choice); }
		}
		catch (...) { cout << "Make a Selection. Enter: 1, 2, 3, or 4." << endl; }


		if (user_Choice == 1) {

			//Prints the total amount of products that were purchased that day and stored in a file
			system("Color 0D");

			cout << endl;
			cout << "******************************************************************************" << endl;
			cout << "*                          Produce Purchased Today                           *" << endl;
			cout << "******************************************************************************" << endl;
			cout << endl;

			CallProcedure("read_File"); //reads the file in python


		}
		else if (user_Choice == 2) {

			// Menu Choice 2 that asks for product name and outputs purchase frequency if valid
			system("Color 03");
			string userString;
			cout << "Enter Product Name: ";
			std::cin >> userString; //Grabs product the user wishes to look up

			int tot = callIntFunc("locate_Total_Product_Amount", userString); //Gets frequency of chosen user item product

			if (tot == -1) {
				cout << "Item Not Found. Try Your Selection Again." << endl; // this validates that the item was not in file due to mispelling, or a integer put into string
			}
			else {
				cout << "There were a total of " << tot << " " << userString << " sold today." << endl; // validates correct input AND prints to console the amount of product purchased/located within file
			}
		}
		else if (user_Choice == 3) {

			// Creates/Writes/Reads .dat file
			system("Color 06");
			CallProcedure("read_AND_Write_File");

		}
		else { program_Run = false; system("Color 04"); } // Ends Program

	} while (program_Run == true); //controls program flow
}



int main()
{

	system("Color 03");

	//starter code calls
	CallProcedure("printsomething");
	cout << callIntFunc("PrintMe", "House") << endl;
	cout << callIntFunc("SquareValue", 2);

	//calls menu function
	Menu();


	//Exit Program Output 
	cout << endl;
	cout << "******************************************************************************" << endl;
	cout << "***                      End Program...                                    ***" << endl;
	cout << "******************************************************************************" << endl;

	return 0;
}