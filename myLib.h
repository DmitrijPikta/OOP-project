#pragma once


#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::exception;
using std::setw;
using std::left;
using std::setprecision;


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
void Print_final_mark(vector<Stud> grupe);


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
	cout << amount_of_marks << endl;
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
	cout << left << setw(10) << "Pavarde" << setw(10) << "Vardas" << setw(10) << "Galutinis ";
	if (for_average_homework_mark) {
		cout << "(vid.)" << endl;
	}
	else {
		cout << "(med.)" << endl;
	}
	cout << "------------------------------------" << endl;
	for (int i = 0; i < grupe.end() - grupe.begin(); i++) {
		cout << left << setw(10) << grupe[i].second_name << setw(10) << grupe[i].name << setprecision(2) << grupe[i].final_mark << endl;
	}
}
