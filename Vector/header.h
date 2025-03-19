#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::exception;
using std::fixed;
using std::left;
using std::setprecision;
using std::setw;
using std::string;
using std::vector;

struct Stud
{
	string name;
	string second_name;
	vector<int> Homework_marks;
	int exam_mark;
	double final_mark;
	double second_final_mark;
};

extern double time_of_generating_file;
extern double time_of_reading_file;
extern double time_of_dividing; // For best and worst
extern double time_of_sorting;
extern double time_of_culculating;
extern double time_of_writing_files;

double Get_average_for_homework_mark(Stud student);
double Get_mediana_for_homework_mark(Stud student);
void Get_final_mark(vector<Stud> &grupe, bool for_average_homework_mark, bool for_both_homework_mark);
void Print_final_mark(vector<Stud> &grupe, bool for_average_homework_mark, bool for_both_homework_mark, bool print_results_in_terminal);
int Get_size_for_string_printing(vector<Stud> &grupe);
void generate_marks(Stud &student);
void generate_marks(vector<int> &Marks, int number_of_marks);
void generate_name(Stud &student);
void Sort_students(vector<Stud> &grupe, string parametr);
bool Generate_file_with_students(int number_of_students, int number_of_marks, string filename);
void Divide_for_two_grupse(vector<Stud> &grupe, vector<Stud> &best_grupe, vector<Stud> &worst_grupe);
void Divide_for_two_grupse(vector<Stud> &grupe, vector<Stud> &worst_grupe);
void Enter_students_using_txt_file_bufer_P(vector<Stud> &grupe);
