#include "header.h"

double time_of_generating_file = 0;
double time_of_reading_file = 0;
double time_of_dividing = 0; // For best and worst
double time_of_sorting = 0;
double time_of_culculating = 0;
double time_of_writing_files = 0;

void Get_final_mark(list<Stud> &grupe, bool for_average_homework_mark, bool for_both_homework_mark)
{
	//---------------------------------------------------------------------------
	auto start = std::chrono::high_resolution_clock::now(); // Time
	//---------------------------------------------------------------------------
	for (Stud &student : grupe)
	{
		if (for_average_homework_mark && for_both_homework_mark)
		{
			student.final_mark = 0.6 * student.exam_mark + 0.4 * Get_average_for_homework_mark(student);
			student.second_final_mark = 0.6 * student.exam_mark + 0.4 * Get_mediana_for_homework_mark(student);
		}
		else if (for_average_homework_mark)
		{
			student.final_mark = 0.6 * student.exam_mark + 0.4 * Get_average_for_homework_mark(student);
		}
		else
		{
			student.final_mark = 0.6 * student.exam_mark + 0.4 * Get_mediana_for_homework_mark(student);
		}
	}
	//-----------------------------------------------------------------
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start; // Time
	time_of_culculating += diff.count();
	//-----------------------------------------------------------------
}

double Get_average_for_homework_mark(Stud student)
{
	int suma_of_marks = 0;
	int amount_of_marks = 0;
	for (int mark : student.Homework_marks)
	{
		suma_of_marks += mark;
		amount_of_marks++;
	}
	if (amount_of_marks == 0)
	{
		return 0;
	}
	return (double)suma_of_marks / amount_of_marks;
}

double Get_mediana_for_homework_mark(Stud student)
{
	student.Homework_marks.sort();

	auto it = student.Homework_marks.begin();
	int amount_of_marks = student.Homework_marks.size();
	if (amount_of_marks == 0)
	{
		return 0;
	}
	else if (amount_of_marks % 2 == 0)
	{
		std::advance(it, (amount_of_marks / 2) - 1);
		return (*it + *(++it)) / 2.0;
	}
	else
	{
		std::advance(it, amount_of_marks / 2);
		return *it;
	}
}

void Print_final_mark(list<Stud> &grupe, bool for_average_homework_mark, bool for_both_homework_mark, bool print_results_in_terminal)
{
	//---------------------------------------------------------------------------
	auto start = std::chrono::high_resolution_clock::now(); // Time
	//---------------------------------------------------------------------------
	string output;
	auto Print_results = [print_results_in_terminal](string output, std::ofstream &fr)
	{
		if (print_results_in_terminal)
		{
			cout << output;
		}
		else
		{
			fr << output;
		}
	};

	string filename;
	if (grupe.back().final_mark >= 5)
	{
		filename = "Best_grupe.txt";
	}
	else
	{
		filename = "Worst_grupe.txt";
	}

	int size = Get_size_for_string_printing(grupe);
	int size_of_atribute_for_marks;
	if (for_both_homework_mark)
	{
		size_of_atribute_for_marks = 18 + 16;
	}
	else
	{
		size_of_atribute_for_marks = 18;
	}

	if (print_results_in_terminal)
	{
		cout << left << setw(size) << "Pavarde" << setw(size) << "Vardas" << "Galutinis ";
		if (for_both_homework_mark)
		{
			cout << "(vid.)" << " " << "Galutinis (med.)" << endl;
		}
		else if (for_average_homework_mark)
		{
			cout << "(vid.)" << endl;
		}
		else
		{
			cout << "(med.)" << endl;
		}
		cout << string(size + size + size_of_atribute_for_marks, '-') << endl;
	}
	else
	{
		std::ofstream fr(filename);
		fr << left << setw(size) << "Pavarde" << setw(size) << "Vardas" << "Galutinis ";
		if (for_both_homework_mark)
		{
			fr << "(vid.)" << " " << "Galutinis (med.)" << endl;
		}
		else if (for_average_homework_mark)
		{
			fr << "(vid.)" << endl;
		}
		else
		{
			fr << "(med.)" << endl;
		}
		fr << string(size + size + size_of_atribute_for_marks, '-') << endl;
		fr.close();
	}
	std::ofstream fr(filename, std::ios::app);
	std::ostringstream oss;
	if (!for_both_homework_mark)
	{
		for (Stud student : grupe)
		{
			oss << left << setw(size) << student.second_name << setw(size) << student.name << fixed << setprecision(2) << student.final_mark << endl;
			output = oss.str();
			oss.str(""); // Clears the string content
			oss.clear(); // Reset error flags (e.g., EOF)
			Print_results(output, fr);
		}
	}
	else
	{
		for (Stud student : grupe)
		{
			oss << left << setw(size) << student.second_name << setw(size) << student.name << fixed << setprecision(2) << setw(17) << student.final_mark << student.second_final_mark << endl;
			output = oss.str();
			oss.str("");
			oss.clear();
			Print_results(output, fr);
		}
	}
	fr.close();
	//-----------------------------------------------------------------
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start; // Time
	time_of_writing_files += diff.count();
	//-----------------------------------------------------------------
}

int Get_size_for_string_printing(list<Stud> &grupe)
{
	int max_length_of_string = 0;
	for (Stud student : grupe)
	{
		if (student.name.length() > max_length_of_string || student.second_name.length() > max_length_of_string)
		{
			if (student.name.length() > student.second_name.length())
			{
				max_length_of_string = student.name.length();
			}
			else
			{
				max_length_of_string = student.second_name.length();
			}
		}
	}

	if (max_length_of_string < 11)
	{
		return 12;
	}
	else
	{
		return max_length_of_string + 2;
	}
}

void generate_marks(Stud &student)
{
	std::random_device rd;							   // Create a random device and seed the generator
	std::mt19937 gen(rd());							   // Mersenne Twister engine
	std::uniform_int_distribution<int> distrib(1, 10); // Define range 1 to 10
	for (int i = 0; i < distrib(gen); i++)
	{
		student.Homework_marks.push_back(distrib(gen));
	}
	student.exam_mark = distrib(gen);
}

void generate_marks(list<int> &Marks, int number_of_marks)
{
	std::random_device rd;							   // Create a random device and seed the generator
	std::mt19937 gen(rd());							   // Mersenne Twister engine
	std::uniform_int_distribution<int> distrib(1, 10); // Define range 1 to 10
	for (int i = 0; i < number_of_marks; i++)
	{
		Marks.push_back(distrib(gen));
	}
}

void generate_name(Stud &student)
{
	list<string> Names = {
		"Alice", "Bob", "Charlie", "David", "Emma",
		"Frank", "Grace", "Henry", "Ivy", "Jack",
		"Karen", "Liam", "Mia", "Noah", "Olivia",
		"Paul", "Quinn", "Rachel", "Sam", "Tina"};
	list<string> Second_names = {
		"Smith", "Johnson", "Williams", "Brown", "Jones",
		"Miller", "Davis", "Garcia", "Rodriguez", "Martinez",
		"Hernandez", "Lopez", "Gonzalez", "Wilson", "Anderson",
		"Thomas", "Taylor", "Moore", "Jackson", "Martin"};

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distrib(0, 19);

	auto it = Names.begin();
	std::advance(it, distrib(gen));
	student.name = *it;

	it = Second_names.begin();
	std::advance(it, distrib(gen));
	student.second_name = *it;
}

void Sort_students(list<Stud> &grupe, string parametr)
{
	//---------------------------------------------------------------------------
	auto start = std::chrono::high_resolution_clock::now(); // Time
	//---------------------------------------------------------------------------
	if (parametr == "final_mark")
	{
		grupe.sort([](const Stud &a, const Stud &b)
				   { return a.final_mark > b.final_mark; });
	}
	else if (parametr == "second_final_mark")
	{
		grupe.sort([](const Stud &a, const Stud &b)
				   { return a.second_final_mark > b.second_final_mark; });
	}
	else if (parametr == "name")
	{
		grupe.sort([](const Stud &a, const Stud &b)
				   { return a.name > b.name; });
	}
	else if (parametr == "second_name")
	{
		grupe.sort([](const Stud &a, const Stud &b)
				   { return a.second_name > b.second_name; });
	}
	//-----------------------------------------------------------------
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start; // Time
	time_of_sorting += diff.count();
	//-----------------------------------------------------------------
}

bool Generate_file_with_students(int number_of_students, int number_of_marks, string filename)
{
	std::ifstream fd(filename);
	if (fd)
	{
		fd.close();
		cout << "Change file name, where is file with this name" << endl;
		return false;
	}
	fd.close();

	if (filename.length() < 4 || filename.substr(filename.size() - 4) != ".txt")
	{
		cout << "Change file name, file can not have this name. Good name example: 'example.txt'" << endl;
		return false;
	}
	//---------------------------------------------------------------------------
	auto start = std::chrono::high_resolution_clock::now(); // Time
	//---------------------------------------------------------------------------
	std::ofstream fr(filename);

	fr << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
	for (int i = 0; i < number_of_marks; i++)
	{
		fr << "ND" << left << setw(8) << i + 1;
	}
	fr << "Egz." << endl;

	list<int> Marks;
	for (int i = 0; i < number_of_students; i++)
	{
		fr << "Vardas" << left << setw(14) << i + 1 << "Pavarde" << setw(13) << left << i + 1;
		generate_marks(Marks, number_of_marks + 1);
		for (int j; j < number_of_marks; j++)
		{
			fr << left << setw(10) << Marks.front();
			Marks.pop_front();
		}
		fr << Marks.front() << endl;
		Marks.pop_front();
	}

	fr.close();
	//-----------------------------------------------------------------
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start; // Time
	time_of_generating_file += diff.count();
	//-----------------------------------------------------------------
	return true;
}

void Divide_for_two_grupse(list<Stud> &grupe, list<Stud> &best_grupe, list<Stud> &worst_grupe)
{
	//---------------------------------------------------------------------------
	auto start = std::chrono::high_resolution_clock::now(); // Time
	//---------------------------------------------------------------------------
	int size_of_grupe = grupe.size();
	for (int i = 0; i < size_of_grupe; i++)
	{
		if (grupe.front().final_mark >= 5)
		{
			best_grupe.push_back(grupe.front());
			grupe.pop_front();
		}
		else
		{
			worst_grupe.push_back(grupe.front());
			grupe.pop_front();
		}
	}
	//-----------------------------------------------------------------
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start; // Time
	time_of_dividing += diff.count();
	//-----------------------------------------------------------------
}

void Divide_for_two_grupse(list<Stud> &grupe, list<Stud> &worst_grupe)
{
	//---------------------------------------------------------------------------
	auto start = std::chrono::high_resolution_clock::now(); // Time
	//---------------------------------------------------------------------------
	Sort_students(grupe, "final_mark");
	while (grupe.back().final_mark < 5)
	{
		worst_grupe.push_back(grupe.back());
		grupe.pop_back();
	}
	//-----------------------------------------------------------------
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start; // Time
	time_of_dividing += diff.count();
	//-----------------------------------------------------------------
}

void Divide_for_two_grupse_v3(list<Stud> &grupe, list<Stud> &best_grupe, list<Stud> &worst_grupe)
{
	//---------------------------------------------------------------------------
	auto start = std::chrono::high_resolution_clock::now(); // Time
	//---------------------------------------------------------------------------
	std::copy_if(grupe.begin(), grupe.end(), std::back_inserter(best_grupe), [](const Stud s)
				 { return s.final_mark >= 5; });

	std::copy_if(grupe.begin(), grupe.end(), std::back_inserter(worst_grupe), [](const Stud s)
				 { return s.final_mark < 5; });

	grupe.clear();
	//-----------------------------------------------------------------
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start; // Time
	time_of_dividing += diff.count();
	//-----------------------------------------------------------------
}

void Enter_students_using_txt_file_bufer_P(list<Stud> &grupe)
{
	string file_name;
	Stud student;
	int mark;

	string element;
	bool last_homework_mark = false;
	int number_of_homework_marks = -1;

	while (true)
	{
		cout << "Please enter file name" << endl;
		cin >> file_name;
		std::ifstream fd(file_name);

		try
		{
			if (!fd)
			{
				throw std::runtime_error("");
			}
			//---------------------------------------------------------------------------
			auto start = std::chrono::high_resolution_clock::now(); // Time
			//---------------------------------------------------------------------------
			std::stringstream my_buffer;
			my_buffer << fd.rdbuf();
			fd.close();
			cout << "Nuskaityta i buferi" << endl;

			my_buffer >> element >> element;
			while (!last_homework_mark)
			{
				number_of_homework_marks++;
				my_buffer >> element;
				if (element == "Egz.")
				{
					last_homework_mark = true;
				}
			}

			string line;
			getline(my_buffer, line);
			while (getline(my_buffer, line))
			{
				std::stringstream ss(line);
				ss >> student.name >> student.second_name;
				for (int i = 0; i < number_of_homework_marks; i++)
				{
					ss >> mark;
					student.Homework_marks.push_back(mark);
				}
				ss >> student.exam_mark;
				grupe.push_back(student);
				student.Homework_marks.clear();
			}

			//-----------------------------------------------------------------
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> diff = end - start; // Time
			time_of_reading_file += diff.count();
			//-----------------------------------------------------------------
		}
		catch (exception)
		{
			cout << "unable to open file" << endl;
			continue;
		}
		break;
	}
}
