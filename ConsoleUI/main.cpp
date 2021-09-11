/*
*
*@author - Muhammed Suwaneh
*@ESOGU Department of Computer Engineering
*
*
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip> // for well formatted outputs
#include <string>
#include <windows.h> // for resizing the console
#include <conio.h>
#define max_size 100

using namespace std;

typedef struct studentInfo {

	char id[13];
	char fullName[31];
	char address[51];
	unsigned int midterm, final;
	float average_Score;
	string course;
	string letter;
	string email;
	string MobilePhone;

}studentInfo;

studentInfo temp;

void display(studentInfo*, int);
void add(studentInfo*, int);
int search_Student(studentInfo*);
void delete_student(studentInfo*);
void update(studentInfo*);
void list_students(studentInfo*, int);
float computeExamScores(unsigned int, unsigned int);
string grade(float);

int n;
char temp_ID[13];
char temp_FullName[31], temp_Address[51];
string temp_course;
float temp_avg_score;
string temp_letter;
string temp_PhoneNumber, temp_Email;

void main() {
    
	// control size of console

	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);

	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1280, 650, true);

	int n;
	cout << "\t\t\t\t\tEnter database size: ";
	cin >> n;

	cin.ignore();

	studentInfo *database = new studentInfo[n];

	if (database) {

		cout << "\t\t\t\t\tMemory allocated succesfully" << endl;
		display(database, n);
	}

	delete[] database;
	cout << endl;
	system("pause");
}

/// <summary>
/// Displays the dashboard
/// </summary>
/// <param name="database"></param>
/// <param name="struct_size"></param>
void display(studentInfo *database, int struct_size) {

	char choice;

	do {

		cout << endl;
		cout << "\t\t\t+++++++++++++++ STUDENT INFORMATION MANAGEMENT SYSTEM ++++++++++++++++++++++ " << endl;
		cout << endl << "\t\t\t CURRENT DATABASE SIZE: " << struct_size << endl;
		cout << endl;

		cout << "\t\t\t----[A] ADD NEW STUDENT" << endl;
		cout << "\t\t\t----[D] DELETE" << endl;
		cout << "\t\t\t----[U] UPDATE" << endl;
		cout << "\t\t\t----[L] LIST" << endl;
		cout << "\t\t\t----[Q] QUIT" << endl;
		cout << endl;
		cout << "\t\t\tChoose an operation is perform: ";
		choice = _getch();
		system("cls");

		if (choice == 'a' || choice == 'A') {

			add(database, struct_size);
		}

		else if (choice == 'd' || choice == 'D') {

			delete_student(database);
		}

		else if (choice == 'u' || choice == 'U') {

			update(database);
		}

		else if (choice == 'l' || choice == 'L') {

			list_students(database, struct_size);
		}

		else if (choice == 'q' || choice == 'Q') {

			cout << "\t\t\tProgram successfully Terminated" << endl;
			cout << "\t\t\t---------------------------------" << endl;
			cout << endl;
			cout << endl;
			exit(0);
 		}

	} while (choice != 'q' || choice != 'Q');
}

/// <summary>
/// Creates a new student 
/// </summary>
/// <param name="database"></param>
/// <param name="struct_size"></param>
void add(studentInfo* database, int struct_size) {

	cout << endl << "\t\t\t++++++++++ ADD A STUDENT +++++++++++" << endl;

	cout << endl;

	if (n > struct_size) {

		cout << "\t\t\tDatabase is full" << endl;
	}
	
	else {

		cout << "\t\t\tEnter student's ID(Max: 12 chars): ";
		cin.getline(temp_ID, 13);
		strcpy_s(database[n].id, temp_ID);

		cout << endl;

		cout << "\t\t\tEnter student's fullname(Max: 30 chars): ";
		cin.getline(temp_FullName, 31);
		strcpy_s(database[n].fullName, temp_FullName);
		cout << endl;

		cout << "\t\t\tEnter taken course name (CENG 101): ";
		getline(cin, temp_course);
		database[n].course.assign(temp_course, 0, temp_course.length());

		cout << endl;
		cout << "\t\t\tEnter mid term grade: ";
		cin >> database[n].midterm;

		cout << endl;
		cout << "\t\t\tEnter final grade: ";
		cin >> database[n].final;

		database[n].average_Score = computeExamScores(database[n].midterm, database[n].final);
		cout << endl;

		database[n].letter = grade(database[n].average_Score);

		cin.ignore();

		cout << "\t\t\tEnter student's address(Max: 50 chars): ";
		cin.getline(temp_Address, 51);
		strcpy_s(database[n].address, temp_Address);

		cout << endl;
		cout << "\t\t\tEnter Phone Number (Ex: 0 (555) 1244645): ";
		getline(cin, temp_PhoneNumber);

		database[n].MobilePhone.assign(temp_PhoneNumber, 0, temp_PhoneNumber.length());
		cout << endl;

		cout << "\t\t\tEnter student's email (abc@abc.com): ";
		getline(cin, temp_Email);

		database[n].email.assign(temp_Email, 0, temp_Email.length());

		n++;
		cout << endl;
	
	}

	cout << "\t\t\tSaved" << endl;
	cout << "\t\t\tpress any key to return to main" << endl;
	_getch();
	system("cls");
}

/// <summary>
/// Deletes a student 
/// </summary>
/// <param name="database"></param>
void delete_student(studentInfo *database) {


	cout << endl;
	cout << "\t\t\t----------- DELETE A STUDENT ------------" << endl;
	cout << endl;
	int index;
	char choice;

	index = search_Student(database);
	
	cout << endl;
	cout << "\t\t\t---------------------------------" << endl;

	if (index != -1) {

		cout << "\t\t\tStudent found" << endl;
		cout << "\t\t\tStudent details" << endl;
		cout << "\t\t\t---------------------------------" << endl;

		cout << "\t\t\tName: " << database[index].fullName << endl;
		cout << "\t\t\tID: " << database[index].id << endl;
		cout << "\t\t\tCourse Taken: " << database[index].course << endl;
		cout << "\t\t\tAverage Score: " << database[index].average_Score << endl;
		cout << "\t\t\tGrade: " << database[index].letter << endl;
		cout << "\t\t\tAddress: " << database[index].address << endl;
		cout << "\t\t\tPhone Number: " << database[index].MobilePhone << endl;
		cout << "\t\t\tEmail: " << database[index].email << endl;

		cout << endl << "\t\t\tDo you wish to delete student ? (y / n): ";
		cin >> choice;

		cin.ignore();

		if (choice == 'y' || choice == 'Y') {

			for (int i = index + 1; i < n; i++, index++) {

				database[i - 1] = database[i];
			}

			n = n - 1;      
			
			cout << "\t\t\tDeleted";
		}

		else {

			cout << endl << "\t\t\tNo operation performed" << endl;
		}	
	}

	else {

		cout << "\t\t\tStudent not found in database" << endl;
	}
    
	cout << endl;
	cout << "\t\t\tpress any key to return to main" << endl;
	_getch();
	system("cls");
}

/// <summary>
/// Updates a students info
/// </summary>
/// <param name="database"></param>
void update(studentInfo *database) {


	cout << endl;
	cout << "\t\t\t*********** UPDATE STUDENT INFO ***********" << endl;

	
	int index;
	char choice;

	index = search_Student(database);

	cout << endl;
	cout << "\t\t\t---------------------------------" << endl;
	if (index != -1) {

		cout << "\t\t\tStudent found" << endl;
		cout << "\t\t\tStudent details" << endl;
		cout << "\t\t\t---------------------------------" << endl;

		cout << "\t\t\tName: " << database[index].fullName << endl;
		cout << "\t\t\tID: " << database[index].id << endl;
		cout << "\t\t\tCourse Taken: " << database[index].course << endl;
		cout << "\t\t\tAverage Score: " << database[index].average_Score << endl;
		cout << "\t\t\tGrade: " << database[index].letter << endl;
		cout << "\t\t\tAddress: " << database[index].address << endl;
		cout << "\t\t\tPhone Number: " << database[index].MobilePhone << endl;
		cout << "\t\t\tEmail: " << database[index].email << endl;

		cout << "\t\t\t---------------------------------" << endl;
		cout << endl;
	
		cout << "\t\t\tUpdate student's fullname(Max: 30 chars): ";
		cin.getline(temp_FullName, 31);
		strcpy_s(database[index].fullName, temp_FullName);
		cout << endl;

		cout << "\t\t\tEnter new ID: ";
		cin.getline(temp_ID, 13);

		strcpy_s(database[index].id, temp_ID);

		cout << endl;
		cout << "\t\t\tEnter new course taken: ";
		getline(cin, temp_course);
		database[index].course.assign(temp_course, 0, temp_course.length());

		cout << endl;
		cout << "\t\t\tEnter new mid term grade: ";
		cin >> database[index].midterm;

		cout << endl;
		cout << "\t\t\tEnter new final grade: ";
		cin >> database[index].final;

		database[index].average_Score = computeExamScores(database[index].midterm, database[index].final);
		cout << endl;

		database[index].letter = grade(database[index].average_Score);

		cin.ignore();

		cout << "\t\t\tEnter student's new address(Max: 50 chars): ";
		cin.getline(temp_Address, 51);
		strcpy_s(database[index].address, temp_Address);

		cout << endl;
		cout << "\t\t\tEnter new Phone Number (Ex: 0 (555) 1244645): ";
		getline(cin, temp_PhoneNumber);

		database[index].MobilePhone.assign(temp_PhoneNumber, 0, temp_PhoneNumber.length());
		cout << endl;

		cout << "\t\t\tEnter student's new mail (abc@abc.com): ";
		getline(cin, temp_Email);

		database[index].email.assign(temp_Email, 0, temp_Email.length());
	}

	else {

		cout << "\t\t\tStudent not found in database" << endl;
	}
	

	cout << endl;
	cout << "\t\t\tpress any key to return to main" << endl;
	_getch();
	system("cls");
}

/// <summary>
/// Displays a list of all students and their info
/// </summary>
/// <param name="database"></param>
/// <param name="struct_size"></param>
void list_students(studentInfo *database, int struct_size) {


	cout << endl;
	cout << "\t\t\t\t\t\t.................. STUDENT LIST ........................" << endl;
	cout << endl;
	int i, j;

	for (i = 0; i < n; i++) {

		for (j = i; j < n; j++) {

			if (strcmp(database[i].fullName, database[j].fullName) > 0) {

				temp = database[i];
				database[i] = database[j];
				database[j] = temp;
		   }
		}
	}

	cout << endl;
	cout << left << setw(20) << "|Students";
	cout << left << setw(20) << "|IDs";
	cout << left << setw(20) << "|Courses Taken";
	cout << left << setw(20) << "|Average Scores";
	cout << left << setw(20) << "|Grades";
	cout << left << setw(20) << "|Addresses";
	cout << left << setw(20) << "|Emails";
	cout << left << setw(20) << "|Phone Numbers";

	cout << endl;

	cout << left << setw(10) << "--------------------";
	cout << left << setw(10) << "--------------------";
	cout << left << setw(10) << "--------------------";
	cout << left << setw(10) << "-------------------";
	cout << left << setw(10) << "-------------------";
	cout << left << setw(10) << "-------------------";
	cout << left << setw(10) << "-------------------";
	cout << left << setw(10) << "-------------------";

	cout << endl;

	for (int i = 0; i < n; i++) {

		cout << endl;
		cout << left << setw(20) << database[i].fullName;
		cout << left << setw(20) << database[i].id;
		cout << left << setw(20) << database[i].course;
		cout << left << setw(20) << database[i].average_Score;
		cout << left << setw(20) << database[i].letter;
		cout << left << setw(20) << database[i].address;
		cout << left << setw(20) << database[i].email;
		cout << left << setw(20) << database[i].MobilePhone;
		cout << endl;
	}

	cout << endl;

	cout << "\n\n";
	cout << "\t\t\tpress any key to return to main" << endl;
	_getch();
	system("cls");
}

/// <summary>
/// Computes students average exam score
/// </summary>
/// <param name="midterm"></param>
/// <param name="final"></param>
/// <returns>average exam score</returns>
float computeExamScores(unsigned int midterm, unsigned int final) {

	float Exam_Avg = (float)((final * 0.6) + (midterm * 0.4));

	return Exam_Avg;
}

/// <summary>
/// COmputes a students grade
/// </summary>
/// <param name="average_Score"></param>
/// <returns>student grade</returns>
string grade(float average_Score) {

	if (average_Score >= 90)
		return "AA";
	else if (average_Score >= 85)
		return "BB";
	else if (average_Score >= 75)
		return "CC";
	else if (average_Score >= 50)
		return "DD";
	else
		return "FF";
}

/// <summary>
/// Search for student 
/// </summary>
/// <param name="database"></param>
/// <returns></returns>
int search_Student(studentInfo* database) {

	int i, index = 0;

	cout << endl;
	cout << "\t\t\t Enter the ID of the student you wish to search: ";
	cin.getline(temp_ID, 13);

	for (i = 0; i < n; i++) {

		if (strcmp(database[i].id, temp_ID) == 0) {

			index = i;
			break;
		}

		else {

			index = -1;
		}
	}

	if (index != -1) {

		return index;
	}

	else {

		return -1;
	}
}
