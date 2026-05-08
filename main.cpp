#include <iostream>
#include <string>
#include "sqlite3.h"
using namespace std;

/* Program name: Database Connection and Callbacks
*  Author: Lauren Davis
*  Date last updated: 5/8/2026
* Purpose: This program opens a connection to the Chinook database. For each album a track listing will be shown and each album will appear in the results once. If the connection doesn't open successfully an error message will print and end the program, if it opens successfully, a success message will print when it.
*/

int callback(void *data, int argc, char **argv, char **azColName);

int main()
{
	open the database first
	return 0;
}
