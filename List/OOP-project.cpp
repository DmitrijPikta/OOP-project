#include "header.h"

int main()
{
    Stud student;
    list<Stud> grupe;

    while (true)
    {
        cout << "Please choose that you want to do and enter:" << endl;
        cout << "'1' - to create a student and by hand enter his intormation" << endl;
        cout << "'2' - to create a student, by hand enter his name and automatically generate his marks" << endl;
        cout << "'3' - to create a student and automatically generate all his information" << endl;
        cout << "'4' - to enter students using txt file" << endl;
        cout << "'5' - to finish work and see results" << endl;
        cout << "'6' - to generate file with students" << endl;

        string entered_action;
        cin >> entered_action;

        if (entered_action != "1" && entered_action != "2" && entered_action != "3" && entered_action != "4" && entered_action != "5" && entered_action != "6")
        {
            cout << "Please enter one command from menu" << endl;
            continue;
        }

        if (entered_action == "5")
        {
            break;
        }

        if (entered_action == "6")
        {
            while (true)
            {
                cout << "Please enter how you want to name new file: ";
                string filename;
                cin >> filename;
                cout << "Plese enter how much do you want to have students in file: ";
                int number_of_students;
                while (true)
                {
                    try
                    {
                        cin >> number_of_students;
                        if (number_of_students <= 0)
                        {
                            throw std::runtime_error("");
                        }
                        else
                        {
                            break;
                        }
                    }
                    catch (exception)
                    {
                        cout << "Please enter number > 0" << endl;
                    }
                }
                bool file_created;
                file_created = Generate_file_with_students(number_of_students, 8, filename);
                if (file_created)
                {
                    break;
                }
            }
            continue;
        }

        if (entered_action == "4")
        {
            Enter_students_using_txt_file_bufer_P(grupe);
            continue;
        }

        if (entered_action == "3")
        {
            generate_name(student);
            generate_marks(student);
            grupe.push_back(student);
            student.Homework_marks.clear();
            continue;
        }

        cout << "Please input student's name" << endl;
        cin >> student.name;

        cout << "Please input student's second name" << endl;
        cin >> student.second_name;

        if (entered_action == "2")
        {
            generate_marks(student);
            grupe.push_back(student);
            student.Homework_marks.clear();
            continue;
        }

        cout << "Please input student's one homework mark, when to save it, press enter. To finish entering marks enter double slash '//'" << endl;
        string entered_mark;
        cin >> entered_mark;
        while (entered_mark != "//")
        {
            try
            {
                int checked_mark = stoi(entered_mark);
                if (checked_mark < 0 || checked_mark > 10)
                {
                    cout << "Entered simbol can not be a mark" << endl;
                    cin >> entered_mark;
                    continue;
                }
                student.Homework_marks.push_back(checked_mark);
            }
            catch (exception)
            {
                cout << "Entered simbol can not be a mark" << endl;
            }
            cin >> entered_mark;
        }

        cout << "Please input student's exam mark" << endl;
        cin >> entered_mark;
        bool exam_mark_have_saved = false;

        while (!exam_mark_have_saved)
        {
            try
            {
                int checked_mark = stoi(entered_mark);
                if (checked_mark < 0 || checked_mark > 10)
                {
                    cout << "Entered simbol can not be a mark" << endl;
                    cin >> entered_mark;
                    continue;
                }
                student.exam_mark = checked_mark;
                exam_mark_have_saved = true;
            }
            catch (exception)
            {
                cout << "Entered simbol can not be a mark" << endl;
                cin >> entered_mark;
            }
        }

        grupe.push_back(student);
        student.Homework_marks.clear();
    }

    if (!grupe.empty())
    {
        cout << "if you want to count with average value, enter 'a', if with madiana, enter 'm', if with both, enter 'b'" << endl;
        string entered_simbol_for_avarege_or_mediana;
        bool for_average_homework_mark;
        bool for_both_homework_mark = false;
        cin >> entered_simbol_for_avarege_or_mediana;

        while (true)
        {
            if (entered_simbol_for_avarege_or_mediana == "a")
            {
                for_average_homework_mark = true;
                break;
            }
            else if (entered_simbol_for_avarege_or_mediana == "m")
            {
                for_average_homework_mark = false;
                break;
            }
            else if (entered_simbol_for_avarege_or_mediana == "b")
            {
                for_average_homework_mark = true;
                for_both_homework_mark = true;
                break;
            }
            else
            {
                cout << "Entered wrong simbol. Please enter 'a' - average, 'm' - mediana and 'b' - both" << endl;
                cin >> entered_simbol_for_avarege_or_mediana;
            }
        }

        Get_final_mark(grupe, for_average_homework_mark, for_both_homework_mark);

        cout << "If you want to get results in terminal, enter 't', if you want to get results in file, enter 'f'" << endl;
        bool print_results_in_terminal;
        while (true)
        {
            string entered_simbol_to_choose_printing;
            cin >> entered_simbol_to_choose_printing;
            if (entered_simbol_to_choose_printing == "t")
            {
                print_results_in_terminal = true;
                break;
            }
            else if (entered_simbol_to_choose_printing == "f")
            {
                print_results_in_terminal = false;
                break;
            }
            else
            {
                cout << "Entered wrong simbol. Please enter 't' or 'f'" << endl;
            }
        }

        string entered_number_to_choose_sort;
        string parametr;
        while (true)
        {
            cout << "Please choose which attribute you want to sort. Please enter:" << endl;
            cout << "'1' - to sort by name" << endl;
            cout << "'2' - to sort by second name" << endl;
            if (for_both_homework_mark)
            {
                cout << "'3' - to sort by final result with average value" << endl;
                cout << "'4' - to sort by final result with mediana value" << endl;
            }
            else if (for_average_homework_mark)
            {
                cout << "'3' - to sort by final result with average value" << endl;
            }
            else
            {
                cout << "'3' - to sort by final result with mediana value" << endl;
            }

            cin >> entered_number_to_choose_sort;
            if (entered_number_to_choose_sort == "1")
            {
                parametr = "name";
                break;
            }
            else if (entered_number_to_choose_sort == "2")
            {
                parametr = "second_name";
                break;
            }
            else if (entered_number_to_choose_sort == "3")
            {
                parametr = "final_mark";
                break;
            }
            else if (entered_number_to_choose_sort == "4")
            {
                parametr = "second_final_mark";
                break;
            }
            cout << "Entered wrong simbol" << endl;
        }

        list<Stud> best_grupe;
        list<Stud> worst_grupe;
        cout << "Start of sorting" << endl;
        Sort_students(grupe, parametr);

        string entered_simbol_for_dividing;
        while (true)
        {
            cout << "Choose how do you want to divide students. Enter:" << endl;
            cout << "'1' to use first method" << endl;
            cout << "'2' to use second method" << endl;
            cout << "'3' to use third method" << endl;
            cin >> entered_simbol_for_dividing;
            if (entered_simbol_for_dividing == "1")
            {
                cout << "Start of dividing for two grupes" << endl;
                Divide_for_two_grupse(grupe, best_grupe, worst_grupe);
                break;
            }
            else if (entered_simbol_for_dividing == "2")
            {
                cout << "Start of dividing for two grupes" << endl;
                Divide_for_two_grupse(grupe, worst_grupe);
                break;
            }
            else if (entered_simbol_for_dividing == "3")
            {
            }
            cout << "Entered wrong simbol" << endl;
        }

        cout << "Start of printing" << endl;
        if (best_grupe.size() > 0 || grupe.size() > 0)
        {
            if (entered_simbol_for_dividing == "1")
            {
                Print_final_mark(best_grupe, for_average_homework_mark, for_both_homework_mark, print_results_in_terminal);
            }
            else
            {
                Print_final_mark(grupe, for_average_homework_mark, for_both_homework_mark, print_results_in_terminal);
            }
        }
        if (worst_grupe.size() > 0)
        {
            Print_final_mark(worst_grupe, for_average_homework_mark, for_both_homework_mark, print_results_in_terminal);
        }
    }
    else
    {
        cout << "There are no students here" << endl;
    }

    cout << "Time of generating file: " << time_of_generating_file << endl;
    cout << "Time of reading file: " << time_of_reading_file << endl;
    cout << "Time of cultulating final mark: " << time_of_culculating << endl;
    cout << "Time of sorting: " << time_of_sorting << endl;
    cout << "Time of dividing to best and worst grupe: " << time_of_dividing << endl;
    cout << "Time of writing: " << time_of_writing_files << endl;
    cout << "Time of working with file: " << time_of_reading_file + time_of_culculating + time_of_sorting + time_of_dividing + time_of_writing_files << endl;
    return 0;
}
