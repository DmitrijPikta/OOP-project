#pragma once


#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::exception;
using std::setw;
using std::left;
using std::setprecision;
using std::fixed;


struct Stud {
	string name;
	string second_name;
	vector <int> Homework_marks;
	int exam_mark;
	double final_mark;
};

double Get_average_for_homework_mark(Stud student);
double Get_mediana_for_homework_mark(Stud student);
void Get_final_mark(vector <Stud>& grupe, bool for_average_homework_mark);
void Print_final_mark(vector<Stud> grupe, bool for_average_homework_mark);
int Get_size_for_string_printing(vector<Stud> grupe);
void generate_marks(Stud& student);
void generate_name(Stud& student);


void Get_final_mark(vector <Stud>& grupe, bool for_average_homework_mark)
{
	for (int i = 0; i < grupe.end() - grupe.begin(); i++) {
		if (for_average_homework_mark) {
			grupe[i].final_mark = 0.6 * grupe[i].exam_mark + 0.4 * Get_average_for_homework_mark(grupe[i]);
		}
		else {
			grupe[i].final_mark = 0.6 * grupe[i].exam_mark + 0.4 * Get_mediana_for_homework_mark(grupe[i]);
		}
	}
}

double Get_average_for_homework_mark(Stud student)
{
	int suma_of_marks = 0;
	int amount_of_marks = 0;
	for (int i = 0; i < student.Homework_marks.end() - student.Homework_marks.begin(); i++) {
		suma_of_marks += student.Homework_marks[i];
		amount_of_marks++;
	}
	if (amount_of_marks == 0) {
		return 0;
	}
	return (double)suma_of_marks / amount_of_marks;
}

double Get_mediana_for_homework_mark(Stud student)
{
	int amount_of_marks = student.Homework_marks.end() - student.Homework_marks.begin();
	if (amount_of_marks == 0) {
		return 0;
	}
	else if (amount_of_marks % 2 == 0) {
		return double(student.Homework_marks[(double)amount_of_marks / 2 - 0.5] + student.Homework_marks[(double)amount_of_marks / 2 + 0.5]) / 2;
	}
	else {

		return student.Homework_marks[amount_of_marks / 2];
	}
}

void Print_final_mark(vector<Stud> grupe, bool for_average_homework_mark)
{
	int size = Get_size_for_string_printing(grupe);
	cout << left << setw(size) << "Pavarde" << setw(size) << "Vardas" << "Galutinis ";
	if (for_average_homework_mark) {
		cout << "(vid.)" << endl;
	}
	else {
		cout << "(med.)" << endl;
	}

	cout << string(size + size + 18, '-') << endl;

	for (int i = 0; i < grupe.end() - grupe.begin(); i++) {
		cout << left << setw(size) << grupe[i].second_name << setw(size) << grupe[i].name << fixed << setprecision(2) << grupe[i].final_mark << endl;
	}
}

int Get_size_for_string_printing(vector<Stud> grupe)
{
	int max_length_of_string = 0;
	for (int i = 0; i < grupe.end() - grupe.begin(); i++) {
		if (grupe[i].name.length() > max_length_of_string or grupe[i].second_name.length() > max_length_of_string) {
			if (grupe[i].name.length() > grupe[i].second_name.length()) {
				max_length_of_string = grupe[i].name.length();
			}
			else {
				max_length_of_string = grupe[i].second_name.length();
			}
		}
	}

	if (max_length_of_string < 11) {
		return 12;
	}
	else {
		return max_length_of_string + 2;
	}
}

void generate_marks(Stud &student) 
{
	std::random_device rd;									// Create a random device and seed the generator
	std::mt19937 gen(rd());									// Mersenne Twister engine
	std::uniform_int_distribution<int> distrib(1, 10);      // Define range 1 to 10
	for (int i = 0; i < distrib(gen); i++) {
		student.Homework_marks.push_back(distrib(gen));
	}
	student.exam_mark = distrib(gen);
}

void generate_name(Stud& student)
{
	vector<string> Names = {
	"Alice", "Bob", "Charlie", "David", "Emma",
	"Frank", "Grace", "Henry", "Ivy", "Jack",
	"Karen", "Liam", "Mia", "Noah", "Olivia",
	"Paul", "Quinn", "Rachel", "Sam", "Tina"
	};
	vector<string> Second_names = {
		"Smith", "Johnson", "Williams", "Brown", "Jones",
		"Miller", "Davis", "Garcia", "Rodriguez", "Martinez",
		"Hernandez", "Lopez", "Gonzalez", "Wilson", "Anderson",
		"Thomas", "Taylor", "Moore", "Jackson", "Martin"
	};

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distrib(0, 19);

	student.name = Names[distrib(gen)];
	student.second_name = Second_names[distrib(gen)];
}
