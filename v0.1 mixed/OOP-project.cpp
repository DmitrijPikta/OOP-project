
#include "myLib.h"

void Vector_vertion();
void C_array_vertion();

int main()
{
    while (true) {
        cout << "Please choose program version and enter:" << endl;
        cout << "'1' - to choose vector version" << endl;
        cout << "'2' - to choose C array version" << endl;
        string choosed_version;
        cin >> choosed_version;
        if (choosed_version == "1") {
            cout << "<<<<<<<<<<<<<<<<<<<<<<< Vector vertion >>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
            Vector_vertion();
            break;
        }
        else if (choosed_version == "2") {
            cout << "<<<<<<<<<<<<<<<<<<<<<<< C array vertion >>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
            C_array_vertion();
            break;
        }
        else {
            cout << "Please enter '1' or '2'" << endl;
        }
    }

    return 0;
}

void Vector_vertion() {
    Stud student;
    vector <Stud> grupe;

    while (true) {
        cout << "Please choose that you want to do and enter:" << endl;
        cout << "'1' - to create a student and by hand enter his intormation" << endl;
        cout << "'2' - to create a student, by hand enter his name and automatically generate his marks" << endl;
        cout << "'3' - to create a student and automatically generate all his information" << endl;
        cout << "'4' - to finish work and see results" << endl;

        string entered_action;
        cin >> entered_action;

        if (entered_action != "1" and entered_action != "2" and entered_action != "3" and entered_action != "4") {
            cout << "Please enter one command from menu" << endl;
            continue;
        }

        if (entered_action == "4") {
            break;
        }

        if (entered_action == "3") {
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

        if (entered_action == "2") {
            generate_marks(student);
            grupe.push_back(student);
            student.Homework_marks.clear();
            continue;
        }

        cout << "Please input student's one homework mark, when to save it, press enter. To finish entering marks enter double slash '//'" << endl;
        string entered_mark;
        cin >> entered_mark;
        while (entered_mark != "//") {
            try {
                int checked_mark = stoi(entered_mark);
                if (checked_mark < 0 or checked_mark > 10) {
                    cout << "Entered simbol can not be a mark" << endl;
                    cin >> entered_mark;
                    continue;
                }
                student.Homework_marks.push_back(checked_mark);
            }
            catch (exception) {
                cout << "Entered simbol can not be a mark" << endl;
            }
            cin >> entered_mark;
        }

        cout << "Please input student's exam mark" << endl;
        cin >> entered_mark;
        bool exam_mark_have_saved = false;

        while (!exam_mark_have_saved) {
            try {
                int checked_mark = stoi(entered_mark);
                if (checked_mark < 0 or checked_mark > 10) {
                    cout << "Entered simbol can not be a mark" << endl;
                    cin >> entered_mark;
                    continue;
                }
                student.exam_mark = checked_mark;
                exam_mark_have_saved = true;
            }
            catch (exception) {
                cout << "Entered simbol can not be a mark" << endl;
                cin >> entered_mark;
            }
        }

        grupe.push_back(student);
        student.Homework_marks.clear();
    }

    if (!grupe.empty()) {
        cout << "if you want to count with average value, enter 'a', if with madiana, enter 'm'" << endl;
        string entered_simbol_for_avarege_or_mediana;
        bool for_average_homework_mark;
        cin >> entered_simbol_for_avarege_or_mediana;

        while (true) {
            if (entered_simbol_for_avarege_or_mediana == "a") {
                for_average_homework_mark = true;
                break;
            }
            else if (entered_simbol_for_avarege_or_mediana == "m") {
                for_average_homework_mark = false;
                break;
            }
            else {
                cout << "Entered wrong simbol. Please enter 'a' - average or 'm' - mediana" << endl;
                cin >> entered_simbol_for_avarege_or_mediana;
            }
        }
        Get_final_mark(grupe, for_average_homework_mark);
        Print_final_mark(grupe, for_average_homework_mark);
    }
    else {
        cout << "There are no students here" << endl;
    }
}

void C_array_vertion() {
    Stud student;
    int capacity_for_grupe = 10;
    int size_for_grupe = 0;
    Stud* grupe_array = new Stud[capacity_for_grupe];

    while (true) {
        cout << "Please choose that you want to do and enter:" << endl;
        cout << "'1' - to create a student and by hand enter his intormation" << endl;
        cout << "'2' - to create a student, by hand enter his name and automatically generate his marks" << endl;
        cout << "'3' - to create a student and automatically generate all his information" << endl;
        cout << "'4' - to finish work and see results" << endl;

        string entered_action;
        cin >> entered_action;

        if (entered_action != "1" and entered_action != "2" and entered_action != "3" and entered_action != "4") {
            cout << "Please enter one command from menu" << endl;
            continue;
        }

        if (entered_action == "4") {
            break;
        }

        if (entered_action == "3") {
            generate_name_C_array(student);
            generate_marks_C_array(student);
            Add_value_to_array(grupe_array, size_for_grupe, capacity_for_grupe, student);
            student.capacity_for_hw_marks = 10;
            student.size_for_hw_marks = 0;
            continue;
        }

        cout << "Please input student's name" << endl;
        cin >> student.name;

        cout << "Please input student's second name" << endl;
        cin >> student.second_name;

        if (entered_action == "2") {
            generate_marks_C_array(student);
            Add_value_to_array(grupe_array, size_for_grupe, capacity_for_grupe, student);
            student.capacity_for_hw_marks = 10;
            student.size_for_hw_marks = 0;
            continue;
        }

        cout << "Please input student's one homework mark, when to save it, press enter. To finish entering marks enter double slash '//'" << endl;
        string entered_mark;
        cin >> entered_mark;
        while (entered_mark != "//") {
            try {
                int checked_mark = stoi(entered_mark);
                if (checked_mark < 0 or checked_mark > 10) {
                    cout << "Entered simbol can not be a mark" << endl;
                    cin >> entered_mark;
                    continue;
                }
                student.homework_marks[student.size_for_hw_marks] = checked_mark;
                student.size_for_hw_marks++;
            }
            catch (exception) {
                cout << "Entered simbol can not be a mark" << endl;
            }
            cin >> entered_mark;
        }

        cout << "Please input student's exam mark" << endl;
        cin >> entered_mark;
        bool exam_mark_have_saved = false;

        while (!exam_mark_have_saved) {
            try {
                int checked_mark = stoi(entered_mark);
                if (checked_mark < 0 or checked_mark > 10) {
                    cout << "Entered simbol can not be a mark" << endl;
                    cin >> entered_mark;
                    continue;
                }
                student.exam_mark = checked_mark;
                exam_mark_have_saved = true;
            }
            catch (exception) {
                cout << "Entered simbol can not be a mark" << endl;
                cin >> entered_mark;
            }
        }

        Add_value_to_array(grupe_array, size_for_grupe, capacity_for_grupe, student);
        student.capacity_for_hw_marks = 10;
        student.size_for_hw_marks = 0;
    }

    if (size_for_grupe > 0) {
        cout << "if you want to count with average value, enter 'a', if with madiana, enter 'm'" << endl;
        string entered_simbol_for_avarege_or_mediana;
        bool for_average_homework_mark;
        cin >> entered_simbol_for_avarege_or_mediana;

        while (true) {
            if (entered_simbol_for_avarege_or_mediana == "a") {
                for_average_homework_mark = true;
                break;
            }
            else if (entered_simbol_for_avarege_or_mediana == "m") {
                for_average_homework_mark = false;
                break;
            }
            else {
                cout << "Entered wrong simbol. Please enter 'a' - average or 'm' - mediana" << endl;
                cin >> entered_simbol_for_avarege_or_mediana;
            }
        }
        Get_final_mark_C_array(grupe_array, size_for_grupe, for_average_homework_mark);
        Print_final_mark_C_array(grupe_array, size_for_grupe, for_average_homework_mark);
    }
    else {
        cout << "There are no students here" << endl;
    }
}

    
