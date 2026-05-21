/*
 * Project: Student Grade Management System
 * Author: BILAL MOHAMMED GHANI
 * Student ID: 2526402447
 * Group: Computer Science A
 * Date: May 2026
 * Description: A menu-driven C++ application for recording student scores,
 * calculating grades/remarks, and generating class statistics.
 */
#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <fstream>

/*
	Struct of Student to contain all variables related to the student
*/

struct student {
	std::string studentName; // Student Name variable set as string
	std::string remark; // Student Remark variable set as string ("Pass" or "Fail")
	int studentID = 0; // Student ID variable set as an int
	float quizScore = 0.0; // Student Quiz Score variable set as float (out of 20 marks)
	float midsemScore = 0.0; // Student Mid Semester Score set as float (out of 30 marks)
	float examScore = 0.0; // Student Exam Score set as float (out of 50 marks)
	float totalScore = 0.0; // Student Total Score set as float (sum of quizScore, midsemScore & examScore)
	char grade = ' '; // Student Grade set as char ('A',...,'F')
};

/**
	* isStringOnly function used to validate string inputs as only alphabetical characters. (set as bool type)
	* std::string str : a parameter variable to take the string input for validation.
	* returns true if conditions are met & false if it consists of numeric characters.
*/

bool isStringOnly(std::string str) {
	if (str.empty()) {
		return false;
	}
	for (int i = 0; i < str.length(); i++) {
		if (!isalpha(str[i]) && !isspace(str[i])) {
			return false;
		}
	}
	return true;
}

/**
	* isNumericOnly function used to validate string inputs as only numeric characters. (set as bool type)
	* I created this function purposely for my Student ID variable to be able to take 0 as
	a first digit. (More detail at inputStudentData function).
	* std::string str : a  parameter variable to take the string input for validation.
	* returns true if conditions are met & false if it consists of alphabetical characters.
*/

bool isNumericOnly(std::string str) {
	if (str.empty()) {
		return false;
	}
	for (int i = 0; i < str.length(); i++) {
		if (!isdigit(str[i])) return false;
	}
	return true;
}

/**
	* getValidScore funtion used to check if the right score is entered. (set as float type)
	* std::string prompt : a parameter variable used to create a prompt message to be displayed to the user
	* float min : a parameter variable used to take the minimum score that can be entered.
	* float max : a parameter vaiable used to take the maximum score that can be entered
	* float score : used to initialize a variable named score to recieve the user input of the score.
	* returns score if a valid score is entered else user has to re enter the score until the right one is entered based of the range.
*/

float getValidScore(std::string prompt, float min, float max) {
	float score;
	std::cout << prompt;

	while (!(std::cin >> score) || score < min || score > max) {
		std::cout << "Invalid! Enter a number between " << min << " and " << max << ": ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
	return score;
};

/**
	* inputStudentData funtion used to take user input for student data. (set as an int type)
	* student* studentData : a studentData pointer pass-by address parameter linking back to the active data array in the main function.
	* int size : a parameter variable used to tell the function the maximum limit of the array in the main function.
	* int count : used to initialize a variable name count to keep count of the number of user data entered based of the array index.
	* return count : used to return the number of studentData recorded.
*/

int inputStudentData(student* studentData, int size) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		std::system("cls");
		std::cout << "====================================================\n";
		std::cout << "               STUDENT DATA ENTRY " << i + 1 << "   \n";
		std::cout << "====================================================\n\n";
		std::string choice;

		//  Name Entry String Handling Block

		std::cout << "\nEnter Student Name: ";
			std::getline(std::cin >>std::ws, studentData[i].studentName); // Clear leading stream spaces
			while (!isStringOnly(studentData[i].studentName)) {
				std::cout << "\nInvalid Input!!!! Try Again: ";
				std::getline(std::cin >> std::ws, studentData[i].studentName);
			}

		// ID Entry Validation & Safe Int Casting Parsing

			std::cout << "\nEnter Student ID: ";
			std::string tempID; // This is a temporal ID container for student data. (it enables 0 as starting digit input)
			std::getline(std::cin >> std::ws, tempID); // Clear leading stream spaces
			while (!isNumericOnly(tempID)) { //while loop with the condition that if input on the tempID returns false for the isNumericOnly function, user should only enter a digit.
				std::cout << "\nInvalid Input!!!! Try Again: ";
				std::getline(std::cin >> std::ws, tempID);
			}
			studentData[i].studentID = std::stoi(tempID); //Safe conversion string -> target int data type

		// Score Data Extraction Routines utilizing floating validation traps

			studentData[i].quizScore = getValidScore("\nEnter Quiz Score (0 - 20): ", 0, 20);
			studentData[i].midsemScore = getValidScore("\nEnter Mid-Semester Score (0 - 30): ", 0, 30);
			studentData[i].examScore = getValidScore("\nEnter Exam Score (0 - 50): ", 0, 50);
			std::cout << "\nPlease Remeber to run Option 2 to Compute and Assign Grades....\n";

			count++; //increment of count +1.

		// Enforce fixed collection baseline boundaries constraint check

			if (count >= size) {
				std::cout << "Student Limit of " << size << " reached!!!" << std::endl;
				std::system("pause");
				break;
			}

		// Conditional loop to handle breaks in-between each student record entered.

			std::cout << "Input next student data (y/n)";
			std::cin >> choice;
			while (choice != "y" && choice != "n") {
				std::cout << "Invalid Choice!!!. Try Again: ";
				std::cin >> choice;
			}

			if (choice == "n") { // Exits data entry workflow and forwards tally back to tracking state
				return count;
			}
	}
	return count;
}

/**
	* assignGrades function used to assign grade letters based on the right score. (set as char type)
	* float total : a parameter value for holding the total score to go through the condition.
	* return the right character based of the condition satisfied.
*/

char assignGrades(float total) {
	if (total >= 80) {
		return 'A';
	}
	else if (total >= 70) {
		return 'B';
	}
	else if (total >= 60) {
		return 'C';
	}
	else if (total >= 50) {
		return 'D';
	}
	else {
		return 'F';
	}
}

/**
	* computeGrades function used to calcute the total score as well as assign grades (assignGrades function implemented) and remarks. (set as void type)
	* student* studentData : a studentData pointer pass-by address parameter linking back to the active data array in the main function.
	* int count : a parameter variable used to tell the function the number of student record available.
*/

void computeGrades(student* studentData, int count) {
	if (count == 0) { // To check if no data record is entered.
		std::cout << "No Data Available. Please Input Student Record.\n";
		return;
	}

	// Allocating pointer target addresses for manual traversal offsets

	student* ptr = studentData;

	for (int i = 0; i < count; i++) {
		ptr -> totalScore = ptr -> quizScore + ptr -> midsemScore + ptr -> examScore;

		//Grade Assignment
		ptr -> grade = assignGrades(ptr->totalScore);


		//Remark Assignment
		if (ptr -> totalScore >= 50) {
			ptr -> remark = "Pass";
		}
		else {
			ptr -> remark = "Fail";
		}
		ptr++; // Physically shifts memory alignment pointer blocks ahead to consecutive locations.
	}

	std::cout << "Grades have been Calculated" <<std::endl;
}

/**
	* displayReport function used to display all recorded student data.
	* student* studentData : a studentData pointer pass-by address parameter linking back to the active data array in the main function.
	* int count : a parameter variable used to tell the function the number of student record available.
*/

void displayReports(student* studentData, int count) {
	if (count == 0) { // To check if no data record is entered.
		std::cout << "No Data Available. Input Student Record\n";
		return;
	}
	std::system("cls");
	std::cout << "=============================================\n";
	std::cout << "                 Class Report                \n";
	std::cout << "=============================================\n\n";

	// use of the iomainip header to have fixed width.

	std::cout << "\n" << std::left << std::setw(15) << "ID" << std::setw(20) << "STUDENT NAME" << std::setw(10) << "Total" << std::setw(8) << "Grade" << std::setw(10) << "Remark" << std::endl;
	std::cout << "--------------------------------------------------------------------------\n";

	for (int i = 0; i < count; i++) {
		std::cout << std::left << std::setw(15) << studentData[i].studentID << std::setw(20) << studentData[i].studentName << std::setw(10) << studentData[i].totalScore << std::setw(8) << studentData[i].grade << std::setw(10) << studentData[i].remark << std::endl;
	}
}

/**
	* 
*/

void displayStatistics(student* studentData, int count) {
	int maxScoreIndex = 0;
	int minScoreIndex = 0;
	int passCount = 0;
	int failCount = 0;
	float sum = 0.0;

	if (count == 0) {
		std::cout << "No Data Available. Please Input Student Record\n";
		return;
	}

	for (int i = 0; i < count; i++) {
		if (studentData[i].totalScore > studentData[maxScoreIndex].totalScore) {
			maxScoreIndex = i;
		}

		if (studentData[i].totalScore < studentData[minScoreIndex].totalScore) {
			minScoreIndex = i;
		}

		if (studentData[i].remark == "Pass") {
			passCount++;
		}
		else {
			failCount++;
		}

		sum += studentData[i].totalScore;
	}
	float average = sum / count;
	std::system("cls");
	std::cout << "=============================================\n";
	std::cout << "              Class Statistics               \n";
	std::cout << "=============================================\n\n";
	std::cout << "Total Students: " << count << std::endl;
	std::cout << "Highest Score: " << studentData[maxScoreIndex].totalScore << " ( " << studentData[maxScoreIndex].studentName << " )" << std::endl;
	std::cout << "Lowest Score: " << studentData[minScoreIndex].totalScore << " ( " << studentData[minScoreIndex].studentName << " )" << std::endl;
	std::cout << "Average Score: " << average << std::endl;
	std::cout << "Students Passed: " << passCount << "  Failed: " << failCount <<std::endl;
}

void searchByID(student* studentData, int count) {
	if (count == 0) {
		std::cout << "No Data Available. Please Input Student Record\n";
		return;
	}

	int searchKey;
	bool found = false;
	std::system("cls");
	std::cout << "Enter Student ID To Be Found: ";
	std::cin >> searchKey;

	for (int i = 0; i < count; i++) {
		if (studentData[i].studentID == searchKey) {
			std::cout << "\n===============================" << std::endl;
			std::cout << "        STUDENT FOUND          " << std::endl;
			std::cout << "===============================" << std::endl;
			std::cout << "Name:        " << studentData[i].studentName << std::endl;
			std::cout << "ID:          " << studentData[i].studentID << std::endl;
			std::cout << "Total Score: " << studentData[i].totalScore << std::endl;
			std::cout << "Grade:       " << studentData[i].grade << std::endl;
			std::cout << "Remark:      " << studentData[i].remark << std::endl;
			std::cout << "===============================" << std::endl;

			found = true;
			break;
		}
	}

	if (!found) {
		std::cout << "Student with ID: " << searchKey << " not found\n";
	}

}

int main() {
		student studentData[30];
		int size = sizeof(studentData) / sizeof(studentData[0]);
		int option = 0;
		int studentCount = 0;
		do {
			std::system("cls");
			std::cout << "===============================\n";
			std::cout << "STUDENT GRADE MANAGEMENT SYSTEM\n";
			std::cout << "===============================\n\n";

			std::cout << "1. Enter Student Records \n2. Compute and Assign Grades \n3. Display Full Class Report \n4. Display Class Statistics \n5. Search Student by ID \n6. Exit \nEnter option: ";
			if (!(std::cin >> option)) {
				std::cout << "Invalid input! Please enter a number.\n";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				system("pause"); 
				continue;
			}

			if (option == 1) {
				studentCount = inputStudentData(studentData, size);
			}
			else if (option == 2) {
				computeGrades(studentData, studentCount);
				system("pause");
			}
			else if (option == 3) {
				displayReports(studentData, studentCount);
				std::cout << "\nDone. ";
				system("pause");
			}
			else if (option == 4) {
				displayStatistics(studentData, studentCount);
				system("pause");
			}
			else if (option == 5) {
				searchByID(studentData, studentCount);
				system("pause");
			}

		} while (option != 6);

		std::cout << "\nProgram exited successfully.\n";
		return 0;
}