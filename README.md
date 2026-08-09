#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <limits>
#include <conio.h>
#include <sstream>

using namespace std;

class ELearningSystem
{
private:
    string name, email, phone, dept, password;
    string role;
    string currentUserEmail;
    string currentUserName;
    string currentUserDept;
    string currentUserPhone;
    string securityQuestion;
    string securityAnswer;
    string courseID;
    string courseName;
    string semester;
    string credit;
    string assignmentTitle;
    string assignmentDescription;
    string assignmentDeadline;
    string assignmentPDF;

public:

    void teacherDashboard();
    void viewProfile();
    void manageCourses();
    void createCourse();
    void uploadLecture();
    void uploadAssignment();
    void viewAssignments();
    void viewSubmissions();
    void gradeStudents();
    void viewGrades();
    void lectureManagement();
    void assignmentManagement();
    void attendance();
    void viewAttendance();        // NEW - student side
    void studentList();
    void changePassword();
    void forgotPassword();
    void myAssignments();
    void studentDashboard();
    void courseEnrollment();
    void viewEnrolledCourses();
    void submitAssignment();

    void courseMenu();
    void assignmentMenu();
    void teacherCourseMenu();
    void teacherStudentMenu();
    void registerUser();
    void loginUser();

    bool isValidName(string name)
    {
        return !name.empty() && isupper(name[0]);
    }

    bool isValidEmail(string email)
    {
        size_t at = email.find('@');
        size_t dot = email.find('.', at);

        return (at != string::npos &&
                dot != string::npos &&
                at > 0 &&
                dot < email.length() - 1);
    }

    bool emailExists(string email)
    {
        ifstream file("users.txt");

        if (!file)
            return false;

        string line;

        while (getline(file, line))
        {
            stringstream ss(line);

            string role1, email1;

            getline(ss, role1, ',');
            getline(ss, email1, ',');

            if (email1 == email)
            {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

    bool courseIDExists(string cID)
    {
        ifstream file("courses.txt");

        if (!file)
            return false;

        string line;

        while (getline(file, line))
        {
            stringstream ss(line);

            string id;
            getline(ss, id, ',');

            if (id == cID)
            {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

    bool isValidPhone(string phone)
    {
        if (phone.length() != 11) return false;
        if (phone.substr(0, 2) != "01") return false;

        for (char c : phone)
            if (!isdigit(c)) return false;

        return true;
    }

    bool isValidDept(string dept)
    {
        if (dept.empty()) return false;

        for (char c : dept)
            if (!isupper(c)) return false;

        return true;
    }

    bool isStrongPassword(string pass)
    {
        if (pass.length() < 6) return false;

        bool upper = false, lower = false, digit = false, special = false;

        for (char c : pass)
        {
            if (isupper(c)) upper = true;
            else if (islower(c)) lower = true;
            else if (isdigit(c)) digit = true;
            else special = true;
        }

        return upper && lower && digit && special;
    }

    string inputPassword()
    {
        string pass = "";
        char ch;

        while (true)
        {
            ch = getch();

            if (ch == 13)
                break;
            else if (ch == 8)
            {
                if (!pass.empty())
                {
                    pass.pop_back();
                    cout << "\b \b";
                }
            }
            else
            {
                pass += ch;
                cout << "*";
            }
        }

        cout << endl;
        return pass;
    }
};

void ELearningSystem::registerUser()
{
    cout << "\n===== REGISTER =====\n";

    int roleChoice;

    do
    {
        cout << "\nSelect Role\n";
        cout << "1. Student\n";
        cout << "2. Teacher\n";
        cout << "Choice: ";
        cin >> roleChoice;
        cin.ignore();

        if (roleChoice == 1)
            role = "Student";
        else if (roleChoice == 2)
            role = "Teacher";
        else
            cout << "Invalid Choice!\n";

    }
    while (roleChoice != 1 && roleChoice != 2);

    do
    {
        cout << "Name: ";
        getline(cin, name);

        if (!isValidName(name))
            cout << "[ERROR] First letter must be CAPITAL!\n";

    }
    while (!isValidName(name));

    do
    {
        cout << "Email: ";
        getline(cin, email);

        if (!isValidEmail(email))
        {
            cout << "[ERROR] Invalid email format!\n";
            continue;
        }

        if (emailExists(email))
        {
            cout << "[ERROR] Email already registered! Please login.\n";
            return;
        }

    }
    while (!isValidEmail(email));

    do
    {
        cout << "Phone: ";
        getline(cin, phone);

        if (!isValidPhone(phone))
            cout << "[ERROR] Must start with 01 and be 11 digits!\n";

    }
    while (!isValidPhone(phone));

    do
    {
        cout << "Department (CAPITAL LETTERS): ";
        getline(cin, dept);

        if (!isValidDept(dept))
            cout << "[ERROR] Only CAPITAL letters allowed!\n";

    }
    while (!isValidDept(dept));

    do
    {
        cout << "\nPassword: ";
        password = inputPassword();

        if (!isStrongPassword(password))
        {
            cout << "\n[WEAK PASSWORD]\n";
            cout << "Password must contain:\n";
            cout << "- At least 6 characters\n";
            cout << "- Uppercase letter\n";
            cout << "- Lowercase letter\n";
            cout << "- Digit\n";
            cout << "- Special character\n\n";
        }

    }
    while (!isStrongPassword(password));

    int questionChoice;

    cout << "\nChoose Security Question\n";
    cout << "1. What is your mother's name?\n";
    cout << "2. What is your favourite color?\n";
    cout << "3. What is your birth place?\n";
    cout << "4. What is your favourite teacher?\n";

    do
    {
        cout << "Choice: ";
        cin >> questionChoice;
        cin.ignore();

        switch (questionChoice)
        {
        case 1:
            securityQuestion = "What is your mother's name?";
            break;
        case 2:
            securityQuestion = "What is your favourite color?";
            break;
        case 3:
            securityQuestion = "What is your birth place?";
            break;
        case 4:
            securityQuestion = "What is your favourite teacher?";
            break;
        default:
            cout << "Invalid Choice!\n";
        }

    }
    while (questionChoice < 1 || questionChoice > 4);

    cout << "Answer: ";
    getline(cin, securityAnswer);

    ofstream file("users.txt", ios::app);
    file << role << "," << email << "," << password << "," << name << ","
         << phone << "," << dept << ","
         << securityQuestion << "," << securityAnswer << "\n";
    file.close();

    cout << "\n=====================================\n";
    cout << "   Registration Successful!\n";
    cout << "=====================================\n";

    char choice;

    cout << "Do you want to see your password? (Y/N): ";
    cin >> choice;

    if (choice == 'Y' || choice == 'y')
    {
        cout << "\nYour Password: " << password << endl;
    }

    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void ELearningSystem::loginUser()
{
    string e, p;
    bool found = false;

    cout << "\n===== LOGIN =====\n";

    cout << "Email: ";
    getline(cin, e);

    cout << "Password: ";
    p = inputPassword();

    char choice;
    cout << "\nShow Password? (Y/N): ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 'Y' || choice == 'y')
    {
        cout << "\nPassword : " << p << endl;
    }

    ifstream file("users.txt");

    if (!file)
    {
        cout << "\n=====================================\n";
        cout << "No account found!\n";
        cout << "Please register first.\n";
        cout << "=====================================\n";
        return;
    }

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string role1, email1, password1;
        string name1, phone1, dept1;
        string question1, answer1;

        getline(ss, role1, ',');
        getline(ss, email1, ',');
        getline(ss, password1, ',');
        getline(ss, name1, ',');
        getline(ss, phone1, ',');
        getline(ss, dept1, ',');
        getline(ss, question1, ',');
        getline(ss, answer1, ',');

        if (email1 == e && password1 == p)
        {
            found = true;

            role = role1;
            currentUserName = name1;
            currentUserEmail = email1;
            currentUserPhone = phone1;
            currentUserDept = dept1;

            break;
        }
    }

    file.close();

    if (found)
    {
        cout << "\n=====================================\n";
        cout << "Login Successful!\n";
        cout << "Welcome, " << currentUserName << "!\n";
        cout << "Role : " << role << endl;
        cout << "=====================================\n";

        if (role == "Student")
            studentDashboard();
        else
            teacherDashboard();
    }
    else
    {
        cout << "\n=====================================\n";
        cout << "Invalid Email or Password!\n";
        cout << "Please try again.\n";
        cout << "=====================================\n";
    }
}

void ELearningSystem::studentDashboard()
{
    int choice;

    while(true)
    {
        system("cls");

        cout<<"=====================================\n";
        cout<<"       STUDENT DASHBOARD\n";
        cout<<"=====================================\n";

        cout<<"1. View Profile\n";
        cout<<"2. Courses\n";
        cout<<"3. Assignments\n";
        cout<<"4. View Grades\n";
        cout<<"5. View Attendance\n";
        cout<<"6. Change Password\n";
        cout<<"7. Logout\n";
        cout<<"0. Back to Main Menu\n";

        cout<<"\nChoice : ";
        cin>>choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice)
        {
        case 1:
            viewProfile();
            break;

        case 2:
            courseMenu();
            break;

        case 3:
            assignmentMenu();
            break;

        case 4:
            viewGrades();
            break;

        case 5:
            viewAttendance();
            break;

        case 6:
            changePassword();
            break;

        case 7:
        {
            char ans;

            cout<<"\nAre you sure you want to logout? (Y/N): ";
            cin>>ans;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(ans=='Y' || ans=='y')
            {
                cout<<"\nLogging out...\n";
                return;
            }

            break;
        }

        case 0:
            return;

        default:
            cout << "\nInvalid Choice!\n";
            system("pause");
        }
    }
}

void ELearningSystem::courseMenu()
{
    int choice;

    while(true)
    {
        system("cls");

        cout<<"=====================================\n";
        cout<<"             COURSES\n";
        cout<<"=====================================\n";

        cout<<"1. Enroll in Course\n";
        cout<<"2. View Enrolled Courses\n";
        cout<<"0. Back\n";

        cout<<"\nChoice : ";
        cin>>choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice)
        {
        case 1:
            courseEnrollment();
            break;

        case 2:
            viewEnrolledCourses();
            break;

        case 0:
            return;

        default:
            cout << "\nInvalid Choice!\n";
            system("pause");
        }
    }
}

void ELearningSystem::assignmentMenu()
{
    int choice;

    while(true)
    {
        system("cls");

        cout<<"=====================================\n";
        cout<<"           ASSIGNMENTS\n";
        cout<<"=====================================\n";

        cout<<"1. View Assignments\n";
        cout<<"2. Submit Assignment\n";
        cout<<"0. Back\n";

        cout<<"\nChoice : ";
        cin>>choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice)
        {
        case 1:
            myAssignments();
            break;

        case 2:
            submitAssignment();
            break;

        case 0:
            return;

        default:
            cout << "\nInvalid Choice!\n";
            system("pause");
        }
    }
}

void ELearningSystem::viewProfile()
{
    cout << "\n========== PROFILE ==========\n";
    cout << "Name       : " << currentUserName << endl;
    cout << "Email      : " << currentUserEmail << endl;
    cout << "Phone      : " << currentUserPhone << endl;
    cout << "Department : " << currentUserDept << endl;
    cout << "Role       : " << role << endl;
    cout << "=============================\n";

    system("pause");
}

void ELearningSystem::changePassword()
{
    string oldPass, newPass;

    while (true)
    {
        cout << "\n===== CHANGE PASSWORD =====\n";
        cout << "1. Continue\n";
        cout << "2. Back\n";
        cout << "Choice: ";

        int op;
        cin >> op;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (op == 2)
            return;

        if (op == 1)
            break;

        cout << "\nInvalid Choice!\n";
        system("pause");
        system("cls");
    }

    cout << "\nEnter Old Password: ";
    oldPass = inputPassword();

    ifstream file("users.txt");
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(file, line))
    {
        stringstream ss(line);

        string role1, email1, password1, name1, phone1, dept1, question1, answer1;

        getline(ss, role1, ',');
        getline(ss, email1, ',');
        getline(ss, password1, ',');
        getline(ss, name1, ',');
        getline(ss, phone1, ',');
        getline(ss, dept1, ',');
        getline(ss, question1, ',');
        getline(ss, answer1, ',');

        if (email1 == currentUserEmail)
        {
            if (password1 != oldPass)
            {
                cout << "\nWrong Old Password!\n";
            }
            else
            {
                string answer;

                cout << "\nSecurity Question:\n";
                cout << question1 << endl;
                cout << "Answer: ";
                getline(cin, answer);

                if (answer != answer1)
                {
                    cout << "\nWrong Security Answer!\n";
                }
                else
                {
                    string newP, confirmPass;

                    do
                    {
                        cout << "\nNew Password : ";
                        newP = inputPassword();

                        if (!isStrongPassword(newP))
                            cout << "\nWeak Password!\n";

                    }
                    while (!isStrongPassword(newP));

                    cout << "Confirm Password : ";
                    confirmPass = inputPassword();

                    if (newP != confirmPass)
                    {
                        cout << "\nPassword Doesn't Match!\n";
                    }
                    else
                    {
                        password1 = newP;
                        found = true;
                        cout << "\nPassword Changed Successfully.\n";
                    }
                }
            }
        }

        temp << role1 << "," << email1 << "," << password1 << "," << name1 << ","
             << phone1 << "," << dept1 << "," << question1 << "," << answer1 << "\n";
    }

    file.close();
    temp.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (!found)
        cout << "\nPassword Change Failed.\n";

    system("pause");
}

void ELearningSystem::forgotPassword()
{
    string email;

    cout << "\n========== FORGOT PASSWORD ==========\n";
    cout << "Enter Email (0 = Back): ";
    getline(cin, email);

    if (email == "0")
        return;

    ifstream file("users.txt");

    if (!file)
    {
        cout << "No user found!\n";
        return;
    }

    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(file, line))
    {
        stringstream ss(line);

        string role1, email1, password1, name1, phone1, dept1;
        string question1, answer1;

        getline(ss, role1, ',');
        getline(ss, email1, ',');
        getline(ss, password1, ',');
        getline(ss, name1, ',');
        getline(ss, phone1, ',');
        getline(ss, dept1, ',');
        getline(ss, question1, ',');
        getline(ss, answer1, ',');

        if (email1 == email)
        {
            found = true;
            cout << "\nSecurity Question:\n";
            cout << question1 << endl;

            string answer;

            cout << "Answer: ";
            getline(cin, answer);

            if (answer == answer1)
            {
                string newPass;

                do
                {
                    cout << "Enter New Password: ";
                    newPass = inputPassword();

                    if (!isStrongPassword(newPass))
                        cout << "Weak Password! Try Again.\n";

                }
                while (!isStrongPassword(newPass));

                string confirmPass;

                cout << "Confirm Password: ";
                confirmPass = inputPassword();

                if (newPass != confirmPass)
                {
                    cout << "\nPassword Doesn't Match!\n";
                }
                else
                {
                    password1 = newPass;
                    cout << "\nPassword Reset Successful!\n";
                }
            }
            else
            {
                cout << "\nWrong Security Answer!\n";
            }
        }

        temp << role1 << "," << email1 << "," << password1 << ","
             << name1 << "," << phone1 << "," << dept1 << ","
             << question1 << "," << answer1 << "\n";
    }

    file.close();
    temp.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (!found)
        cout << "\nEmail not found!\n";

    system("pause");
}

void ELearningSystem::teacherDashboard()
{
    int choice;

    while (true)
    {
        system("cls");

        cout << "=====================================\n";
        cout << "        TEACHER DASHBOARD\n";
        cout << "=====================================\n";

        cout << "1. My Profile\n";
        cout << "2. Courses\n";
        cout << "3. Students\n";
        cout << "4. Change Password\n";
        cout << "5. Logout\n";

        cout << "\nChoice : ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            viewProfile();
            break;
        case 2:
            teacherCourseMenu();
            break;
        case 3:
            teacherStudentMenu();
            break;
        case 4:
            changePassword();
            break;
        case 5:
            cout << "\nLogging out...\n";
            return;
        default:
            cout << "\nInvalid Choice!\n";
            system("pause");
        }
    }
}

void ELearningSystem::teacherCourseMenu()
{
    int choice;

    while (true)
    {
        system("cls");

        cout << "=====================================\n";
        cout << "             COURSES\n";
        cout << "=====================================\n";

        cout << "1. Manage Courses\n";
        cout << "2. Lecture Management\n";
        cout << "3. Assignment Management\n";
        cout << "0. Back\n";

        cout << "\nChoice : ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            manageCourses();
            break;
        case 2:
            lectureManagement();
            break;
        case 3:
            assignmentManagement();
            break;
        case 0:
            return;
        default:
            cout << "\nInvalid Choice!\n";
            system("pause");
        }
    }
}

void ELearningSystem::teacherStudentMenu()
{
    int choice;

    while (true)
    {
        system("cls");

        cout << "=====================================\n";
        cout << "             STUDENTS\n";
        cout << "=====================================\n";

        cout << "1. Student List\n";
        cout << "2. Grade Students\n";
        cout << "3. Attendance\n";
        cout << "0. Back\n";

        cout << "\nChoice : ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            studentList();
            break;
        case 2:
            gradeStudents();
            break;
        case 3:
            attendance();
            break;
        case 0:
            return;
        default:
            cout << "\nInvalid Choice!\n";
            system("pause");
        }
    }
}

void ELearningSystem::manageCourses()
{
    int choice;

    while (true)
    {
        system("cls");

        cout << "=====================================\n";
        cout << "        MANAGE COURSES\n";
        cout << "=====================================\n";

        cout << "1. Create Course\n";
        cout << "2. View My Courses\n";
        cout << "3. Search Course\n";
        cout << "4. Edit Course\n";
        cout << "5. Delete Course\n";
        cout << "6. Back\n";

        cout << "\nChoice : ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            createCourse();
            break;

        case 2:
        {
            system("cls");

            ifstream file("courses.txt");
            string line;
            bool found = false;

            cout << "=====================================\n";
            cout << "         MY COURSES\n";
            cout << "=====================================\n\n";

            while (getline(file, line))
            {
                stringstream ss(line);
                string id, cname, department, sem, cr, email;

                getline(ss, id, ',');
                getline(ss, cname, ',');
                getline(ss, department, ',');
                getline(ss, sem, ',');
                getline(ss, cr, ',');
                getline(ss, email, ',');

                if (email == currentUserEmail)
                {
                    found = true;
                    cout << "Course ID   : " << id << endl;
                    cout << "Course Name : " << cname << endl;
                    cout << "Department  : " << department << endl;
                    cout << "Semester    : " << sem << endl;
                    cout << "Credit      : " << cr << endl;
                    cout << "\n-------------------------------------\n";
                }
            }

            file.close();

            if (!found)
                cout << "No Course Found.\n";

            system("pause");
            break;
        }

        case 3:
        {
            system("cls");

            string searchID;

            cout << "=====================================\n";
            cout << "          SEARCH COURSE\n";
            cout << "=====================================\n\n";

            cout << "Enter Course ID : ";
            getline(cin, searchID);

            ifstream file("courses.txt");
            string line;
            bool found = false;

            while (getline(file, line))
            {
                stringstream ss(line);
                string id, cname, department, sem, cr, email;

                getline(ss, id, ',');
                getline(ss, cname, ',');
                getline(ss, department, ',');
                getline(ss, sem, ',');
                getline(ss, cr, ',');
                getline(ss, email, ',');

                if (id == searchID && email == currentUserEmail)
                {
                    found = true;
                    cout << "\n========== COURSE FOUND ==========\n";
                    cout << "Course ID   : " << id << endl;
                    cout << "Course Name : " << cname << endl;
                    cout << "Department  : " << department << endl;
                    cout << "Semester    : " << sem << endl;
                    cout << "Credit      : " << cr << endl;
                    cout << "==================================\n";
                }
            }

            file.close();

            if (!found)
                cout << "\nCourse Not Found!\n";

            system("pause");
            break;
        }

        case 4:
        {
            system("cls");

            string searchID;

            cout << "=====================================\n";
            cout << "           EDIT COURSE\n";
            cout << "=====================================\n\n";

            cout << "Enter Course ID : ";
            getline(cin, searchID);

            ifstream file("courses.txt");
            ofstream temp("temp.txt");

            string line;
            bool found = false;

            while (getline(file, line))
            {
                stringstream ss(line);
                string id, cname, department, sem, cr, email;

                getline(ss, id, ',');
                getline(ss, cname, ',');
                getline(ss, department, ',');
                getline(ss, sem, ',');
                getline(ss, cr, ',');
                getline(ss, email, ',');

                if (id == searchID && email == currentUserEmail)
                {
                    found = true;

                    cout << "\nCurrent Information\n";
                    cout << "Course Name : " << cname << endl;
                    cout << "Department  : " << department << endl;
                    cout << "Semester    : " << sem << endl;
                    cout << "Credit      : " << cr << endl;

                    cout << "\nEnter New Course Name : ";
                    getline(cin, cname);
                    cout << "Enter New Department : ";
                    getline(cin, department);
                    cout << "Enter New Semester : ";
                    getline(cin, sem);
                    cout << "Enter New Credit : ";
                    getline(cin, cr);
                }

                temp << id << "," << cname << "," << department << "," << sem << ","
                     << cr << "," << email << "\n";
            }

            file.close();
            temp.close();

            remove("courses.txt");
            rename("temp.txt", "courses.txt");

            if (found)
                cout << "\nCourse Updated Successfully.\n";
            else
                cout << "\nCourse Not Found.\n";

            system("pause");
            break;
        }

        case 5:
        {
            system("cls");

            string searchID;
            char confirm;

            cout << "=====================================\n";
            cout << "          DELETE COURSE\n";
            cout << "=====================================\n\n";

            cout << "Enter Course ID : ";
            getline(cin, searchID);

            ifstream file("courses.txt");
            ofstream temp("temp.txt");

            string line;
            bool found = false;

            while (getline(file, line))
            {
                stringstream ss(line);
                string id, cname, department, sem, cr, email;

                getline(ss, id, ',');
                getline(ss, cname, ',');
                getline(ss, department, ',');
                getline(ss, sem, ',');
                getline(ss, cr, ',');
                getline(ss, email, ',');

                if (id == searchID && email == currentUserEmail)
                {
                    found = true;
                    cout << "\nCourse Found!\n";
                    cout << "Course Name : " << cname << endl;

                    cout << "\nAre you sure you want to delete this course? (Y/N): ";
                    cin >> confirm;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (confirm == 'Y' || confirm == 'y')
                    {
                        cout << "\nCourse Deleted Successfully!\n";
                        continue;
                    }
                }

                temp << id << "," << cname << "," << department << "," << sem << ","
                     << cr << "," << email << "\n";
            }

            file.close();
            temp.close();

            remove("courses.txt");
            rename("temp.txt", "courses.txt");

            if (!found)
                cout << "\nCourse Not Found!\n";

            system("pause");
            break;
        }

        case 6:
            return;

        default:
            cout << "\nInvalid Choice!\n";
            system("pause");
        }
    }
}

void ELearningSystem::createCourse()
{
    system("cls");

    cout << "=====================================\n";
    cout << "          CREATE COURSE\n";
    cout << "           (0 = Back)\n";
    cout << "=====================================\n";

    cout << "Course ID : ";
    getline(cin, courseID);

    if (courseID == "0")
        return;

    if (courseIDExists(courseID))
    {
        cout << "\n[ERROR] This Course ID already exists! Use a different ID.\n";
        system("pause");
        return;
    }

    cout << "Course Name    : ";
    getline(cin, courseName);
    cout << "Department     : ";
    getline(cin, dept);
    cout << "Semester       : ";
    getline(cin, semester);
    cout << "Credit         : ";
    getline(cin, credit);

    ofstream file("courses.txt", ios::app);
    file << courseID << "," << courseName << "," << dept << "," << semester << ","
         << credit << "," << currentUserEmail << "\n";
    file.close();

    cout << "\n=====================================\n";
    cout << "Course Created Successfully.\n";
    cout << "=====================================\n";

    system("pause");
}
void ELearningSystem::uploadLecture()
{
    system("cls");

    string lectureTitle, lectureDesc, lectureLink;

    cout << "=====================================\n";
    cout << "          UPLOAD LECTURE\n";
    cout << "       (Google Drive Link)\n";
    cout << "=====================================\n\n";

    cout << "Course ID       : ";
    getline(cin, courseID);

    if (courseID == "0")
        return;

    // Check whether this course belongs to the current teacher
    ifstream courseFile("courses.txt");
    string line;
    bool ownsCourse = false;

    while (getline(courseFile, line))
    {
        stringstream ss(line);

        string id, cname, department, sem, cr, temail;

        getline(ss, id, ',');
        getline(ss, cname, ',');
        getline(ss, department, ',');
        getline(ss, sem, ',');
        getline(ss, cr, ',');
        getline(ss, temail, ',');

        if (id == courseID && temail == currentUserEmail)
        {
            ownsCourse = true;
            break;
        }
    }

    courseFile.close();

    if (!ownsCourse)
    {
        cout << "\n[ERROR] This Course ID doesn't belong to you!\n";
        system("pause");
        return;
    }

    cout << "Lecture Title   : ";
    getline(cin, lectureTitle);

    cout << "Description     : ";
    getline(cin, lectureDesc);

    cout << "Google Drive Link: ";
    getline(cin, lectureLink);

    if (lectureLink.empty())
    {
        cout << "\n[ERROR] Google Drive link cannot be empty!\n";
        system("pause");
        return;
    }

    ofstream file("lectures.txt", ios::app);

    file << courseID << ","
         << lectureTitle << ","
         << lectureDesc << ","
         << lectureLink << ","
         << currentUserEmail << "\n";

    file.close();

    cout << "\n=====================================\n";
    cout << "Lecture Added Successfully!\n";
    cout << "Google Drive Link Saved.\n";
    cout << "=====================================\n";

    system("pause");
}


void ELearningSystem::lectureManagement()
{
    int choice;

    while (true)
    {
        system("cls");

        cout << "=====================================\n";
        cout << "        LECTURE MANAGEMENT\n";
        cout << "=====================================\n";

        cout << "1. Upload Lecture\n";
        cout << "2. View My Lectures\n";
        cout << "3. Back\n";

        cout << "\nChoice : ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            uploadLecture();
            break;

        case 2:
        {
            system("cls");

            ifstream file("lectures.txt");
            string line;
            bool found = false;

            cout << "=====================================\n";
            cout << "          MY LECTURES\n";
            cout << "=====================================\n\n";

            while (getline(file, line))
            {
                stringstream ss(line);

                string cID, title, description, lectureLink, em;

                getline(ss, cID, ',');
                getline(ss, title, ',');
                getline(ss, description, ',');
                getline(ss, lectureLink, ',');
                getline(ss, em, ',');

                if (em == currentUserEmail)
                {
                    found = true;

                    cout << "Course ID   : " << cID << endl;
                    cout << "Title       : " << title << endl;
                    cout << "Description : " << description << endl;
                    cout << "Drive Link  : " << lectureLink << endl;

                    cout << "\n-------------------------------------\n";
                }
            }

            file.close();

            if (!found)
                cout << "No Lecture Found.\n";

            system("pause");
            break;
        }

        case 3:
            return;

        default:
            cout << "\nInvalid Choice!\n";
            system("pause");
        }
    }
}

void ELearningSystem::uploadAssignment()
{
    system("cls");

    cout << "=====================================\n";
    cout << "        UPLOAD ASSIGNMENT\n";
    cout << "       (Google Drive Link)\n";
    cout << "=====================================\n\n";

    cout << "Course ID          : ";
    getline(cin, courseID);

    if (courseID == "0")
        return;

    // Check whether this course belongs to current teacher
    ifstream courseFile("courses.txt");
    string line;
    bool ownsCourse = false;

    while (getline(courseFile, line))
    {
        stringstream ss(line);

        string id, cname, department, sem, cr, temail;

        getline(ss, id, ',');
        getline(ss, cname, ',');
        getline(ss, department, ',');
        getline(ss, sem, ',');
        getline(ss, cr, ',');
        getline(ss, temail, ',');

        if (id == courseID && temail == currentUserEmail)
        {
            ownsCourse = true;
            break;
        }
    }

    courseFile.close();

    if (!ownsCourse)
    {
        cout << "\n[ERROR] This Course ID doesn't belong to you!\n";
        system("pause");
        return;
    }

    cout << "Title              : ";
    getline(cin, assignmentTitle);

    cout << "Description        : ";
    getline(cin, assignmentDescription);

    cout << "Deadline           : ";
    getline(cin, assignmentDeadline);

    cout << "Google Drive Link  : ";
    getline(cin, assignmentPDF);

    if (assignmentPDF.empty())
    {
        cout << "\n[ERROR] Google Drive link cannot be empty!\n";
        system("pause");
        return;
    }

    ofstream file("assignments.txt", ios::app);

    file << courseID << ","
         << assignmentTitle << ","
         << assignmentDescription << ","
         << assignmentDeadline << ","
         << assignmentPDF << ","
         << currentUserEmail << "\n";

    file.close();

    cout << "\n=====================================\n";
    cout << "Assignment Added Successfully!\n";
    cout << "Google Drive Link Saved.\n";
    cout << "=====================================\n";

    system("pause");
}
void ELearningSystem::viewAssignments()
{
    system("cls");

    ifstream file("assignments.txt");
    string line;
    bool found = false;

    cout << "=====================================\n";
    cout << "       MY ASSIGNMENTS\n";
    cout << "=====================================\n\n";

    while (getline(file, line))
    {
        stringstream ss(line);
        string cID, title, description, deadline, pdf, em;

        getline(ss, cID, ',');
        getline(ss, title, ',');
        getline(ss, description, ',');
        getline(ss, deadline, ',');
        getline(ss, pdf, ',');
        getline(ss, em, ',');

        if (em == currentUserEmail)
        {
            found = true;
            cout << "Course ID    : " << cID << endl;
            cout << "Title        : " << title << endl;
            cout << "Description  : " << description << endl;
            cout << "Deadline     : " << deadline << endl;
            cout << "PDF File     : " << pdf << endl;
            cout << "\n-------------------------------------\n";
        }
    }

    file.close();

    if (!found)
        cout << "No Assignment Found.\n";

    system("pause");
}

void ELearningSystem::viewSubmissions()
{
    system("cls");

    cout << "=====================================\n";
    cout << "         VIEW SUBMISSIONS\n";
    cout << "=====================================\n\n";

    ifstream courseFile("courses.txt");
    string myCourseIDs[100];
    int myCourseCount = 0;
    string line;

    while (getline(courseFile, line))
    {
        stringstream ss(line);
        string id, cname, department, sem, cr, temail;

        getline(ss, id, ',');
        getline(ss, cname, ',');
        getline(ss, department, ',');
        getline(ss, sem, ',');
        getline(ss, cr, ',');
        getline(ss, temail, ',');

        if (temail == currentUserEmail && myCourseCount < 100)
        {
            myCourseIDs[myCourseCount] = id;
            myCourseCount++;
        }
    }
    courseFile.close();

    if (myCourseCount == 0)
    {
        cout << "You have not created any course yet.\n";
        system("pause");
        return;
    }

    ifstream subFile("submissions.txt");

    if (!subFile)
    {
        cout << "No Submissions Found.\n";
        system("pause");
        return;
    }

    bool found = false;

    while (getline(subFile, line))
    {
        stringstream ss(line);
        string cID, title, studentEmail, subFileName;

        getline(ss, cID, ',');
        getline(ss, title, ',');
        getline(ss, studentEmail, ',');
        getline(ss, subFileName, ',');

        bool belongsToMe = false;

        for (int i = 0; i < myCourseCount; i++)
        {
            if (myCourseIDs[i] == cID)
            {
                belongsToMe = true;
                break;
            }
        }

        if (belongsToMe)
        {
            found = true;
            cout << "Course ID       : " << cID << endl;
            cout << "Assignment      : " << title << endl;
            cout << "Student Email   : " << studentEmail << endl;
            cout << "Submitted File  : " << subFileName << endl;
            cout << "\n-------------------------------------\n";
        }
    }

    subFile.close();

    if (!found)
        cout << "No Submissions Found for Your Courses.\n";

    system("pause");
}

void ELearningSystem::assignmentManagement()
{
    int choice;

    while (true)
    {
        system("cls");

        cout << "=====================================\n";
        cout << "      ASSIGNMENT MANAGEMENT\n";
        cout << "=====================================\n";

        cout << "1. Upload Assignment\n";
        cout << "2. View Assignments\n";
        cout << "3. View Submissions\n";
        cout << "4. Back\n";

        cout << "\nChoice : ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            uploadAssignment();
            break;
        case 2:
            viewAssignments();
            break;
        case 3:
            viewSubmissions();
            break;
        case 4:
            return;
        default:
            cout << "\nInvalid Choice!\n";
            system("pause");
        }
    }
}

void ELearningSystem::gradeStudents()
{
    system("cls");

    string cID, studentEmail, grade;

    cout << "=====================================\n";
    cout << "         GRADE STUDENTS\n";
    cout << "          (0 = Back)\n";
    cout << "=====================================\n\n";

    cout << "Enter Course ID    : ";
    getline(cin, cID);

    if (cID == "0")
        return;

    ifstream courseFile("courses.txt");
    bool ownsCourse = false;
    string line;

    while (getline(courseFile, line))
    {
        stringstream ss(line);
        string id, cname, department, sem, cr, temail;

        getline(ss, id, ',');
        getline(ss, cname, ',');
        getline(ss, department, ',');
        getline(ss, sem, ',');
        getline(ss, cr, ',');
        getline(ss, temail, ',');

        if (id == cID && temail == currentUserEmail)
        {
            ownsCourse = true;
            break;
        }
    }
    courseFile.close();

    if (!ownsCourse)
    {
        cout << "\n[ERROR] This Course ID doesn't belong to you or doesn't exist!\n";
        system("pause");
        return;
    }

    cout << "Enter Student Email: ";
    getline(cin, studentEmail);

    ifstream enrollFile("enrollments.txt");
    bool enrolled = false;

    while (getline(enrollFile, line))
    {
        stringstream ss(line);
        string eCID, eEmail;

        getline(ss, eCID, ',');
        getline(ss, eEmail, ',');

        if (eCID == cID && eEmail == studentEmail)
        {
            enrolled = true;
            break;
        }
    }
    enrollFile.close();

    if (!enrolled)
    {
        cout << "\n[ERROR] This student is not enrolled in this course!\n";
        system("pause");
        return;
    }

    cout << "Enter Grade (e.g. A+, A, B, C, F): ";
    getline(cin, grade);

    if (grade.empty())
    {
        cout << "\n[ERROR] Grade cannot be empty!\n";
        system("pause");
        return;
    }

    ifstream file("grades.txt");
    ofstream temp("temp.txt");

    bool alreadyGraded = false;

    while (getline(file, line))
    {
        stringstream ss(line);
        string gCID, gEmail, gGrade;

        getline(ss, gCID, ',');
        getline(ss, gEmail, ',');
        getline(ss, gGrade, ',');

        if (gCID == cID && gEmail == studentEmail)
        {
            gGrade = grade;
            alreadyGraded = true;
        }

        temp << gCID << "," << gEmail << "," << gGrade << "\n";
    }

    if (!alreadyGraded)
    {
        temp << cID << "," << studentEmail << "," << grade << "\n";
    }

    file.close();
    temp.close();

    remove("grades.txt");
    rename("temp.txt", "grades.txt");

    cout << "\n=====================================\n";
    if (alreadyGraded)
        cout << "Grade Updated Successfully!\n";
    else
        cout << "Grade Assigned Successfully!\n";
    cout << "=====================================\n";

    system("pause");
}

void ELearningSystem::viewGrades()
{
    system("cls");

    cout << "=====================================\n";
    cout << "           MY GRADES\n";
    cout << "=====================================\n\n";

    ifstream file("grades.txt");

    if (!file)
    {
        cout << "No Grades Available Yet.\n";
        system("pause");
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line))
    {
        stringstream ss(line);
        string cID, sEmail, grade;

        getline(ss, cID, ',');
        getline(ss, sEmail, ',');
        getline(ss, grade, ',');

        if (sEmail == currentUserEmail)
        {
            found = true;
            cout << "Course ID : " << cID << endl;
            cout << "Grade     : " << grade << endl;
            cout << "\n-------------------------------------\n";
        }
    }

    file.close();

    if (!found)
        cout << "No Grades Available Yet.\n";

    system("pause");
}

// NEW: Teacher marks attendance using an interactive tick-box UI
void ELearningSystem::attendance()
{
    system("cls");

    string cID, date;

    cout << "=====================================\n";
    cout << "         MARK ATTENDANCE\n";
    cout << "          (0 = Back)\n";
    cout << "=====================================\n\n";

    cout << "Enter Course ID : ";
    getline(cin, cID);

    if (cID == "0")
        return;

    ifstream courseFile("courses.txt");
    bool ownsCourse = false;
    string line;

    while (getline(courseFile, line))
    {
        stringstream ss(line);
        string id, cname, department, sem, cr, temail;

        getline(ss, id, ',');
        getline(ss, cname, ',');
        getline(ss, department, ',');
        getline(ss, sem, ',');
        getline(ss, cr, ',');
        getline(ss, temail, ',');

        if (id == cID && temail == currentUserEmail)
        {
            ownsCourse = true;
            break;
        }
    }
    courseFile.close();

    if (!ownsCourse)
    {
        cout << "\n[ERROR] This Course ID doesn't belong to you or doesn't exist!\n";
        system("pause");
        return;
    }

    cout << "Enter Date (e.g. 09-08-2026) : ";
    getline(cin, date);

    if (date.empty())
    {
        cout << "\n[ERROR] Date cannot be empty!\n";
        system("pause");
        return;
    }

    // Load enrolled students for this course
    string studentEmails[100];
    string studentNames[100];
    int studentCount = 0;

    ifstream enrollFile("enrollments.txt");

    while (getline(enrollFile, line))
    {
        stringstream ss(line);
        string eCID, eEmail;

        getline(ss, eCID, ',');
        getline(ss, eEmail, ',');

        if (eCID == cID && studentCount < 100)
        {
            studentEmails[studentCount] = eEmail;

            ifstream userFile("users.txt");
            string uline;
            string foundName = eEmail;

            while (getline(userFile, uline))
            {
                stringstream us(uline);
                string urole, uemail, upass, uname;

                getline(us, urole, ',');
                getline(us, uemail, ',');
                getline(us, upass, ',');
                getline(us, uname, ',');

                if (uemail == eEmail)
                {
                    foundName = uname;
                    break;
                }
            }
            userFile.close();

            studentNames[studentCount] = foundName;
            studentCount++;
        }
    }
    enrollFile.close();

    if (studentCount == 0)
    {
        cout << "\nNo Students Enrolled in this Course.\n";
        system("pause");
        return;
    }

    // Interactive tick-box selection (all Present by default)
    bool absentFlags[100] = {false};
    int cursor = 0;

    while (true)
    {
        system("cls");

        cout << "=====================================\n";
        cout << "         MARK ATTENDANCE\n";
        cout << "   Course: " << cID << "   Date: " << date << "\n";
        cout << "=====================================\n\n";
        cout << "All students are Present by default.\n";
        cout << "UP/DOWN = Move | SPACE = Toggle Absent | ENTER = Confirm\n\n";

        for (int i = 0; i < studentCount; i++)
        {
            if (i == cursor)
                cout << " > ";
            else
                cout << "   ";

            cout << "[" << (absentFlags[i] ? "x" : " ") << "] "
                 << studentNames[i] << " (" << studentEmails[i] << ")";

            if (absentFlags[i])
                cout << "   <-- ABSENT";

            cout << "\n";
        }

        int ch = getch();

        if (ch == 224 || ch == 0)
        {
            int ch2 = getch();

            if (ch2 == 72)          // Up arrow
            {
                cursor--;
                if (cursor < 0)
                    cursor = studentCount - 1;
            }
            else if (ch2 == 80)     // Down arrow
            {
                cursor++;
                if (cursor >= studentCount)
                    cursor = 0;
            }
        }
        else if (ch == 32)          // Space
        {
            absentFlags[cursor] = !absentFlags[cursor];
        }
        else if (ch == 13)          // Enter
        {
            break;
        }
    }

    ofstream file("attendance.txt", ios::app);

    int presentCount = 0, absentCount = 0;

    for (int i = 0; i < studentCount; i++)
    {
        string status = absentFlags[i] ? "Absent" : "Present";
        file << cID << "," << date << "," << studentEmails[i] << "," << status << "\n";

        if (absentFlags[i])
            absentCount++;
        else
            presentCount++;
    }

    file.close();

    system("cls");
    cout << "=====================================\n";
    cout << "Attendance Saved Successfully!\n";
    cout << "=====================================\n";
    cout << "Present : " << presentCount << endl;
    cout << "Absent  : " << absentCount << endl;
    cout << "=====================================\n";

    system("pause");
}

// NEW: Student views their own attendance history + percentage
void ELearningSystem::viewAttendance()
{
    system("cls");

    string cID;

    cout << "=====================================\n";
    cout << "         MY ATTENDANCE\n";
    cout << "          (0 = Back)\n";
    cout << "=====================================\n\n";

    cout << "Enter Course ID : ";
    getline(cin, cID);

    if (cID == "0")
        return;

    ifstream file("attendance.txt");

    if (!file)
    {
        cout << "\nNo Attendance Record Found.\n";
        system("pause");
        return;
    }

    string line;
    int totalClasses = 0, presentCount = 0, absentCount = 0;

    cout << "\n=====================================\n";
    cout << "     ATTENDANCE HISTORY (" << cID << ")\n";
    cout << "=====================================\n\n";

    while (getline(file, line))
    {
        stringstream ss(line);
        string aCID, aDate, aEmail, aStatus;

        getline(ss, aCID, ',');
        getline(ss, aDate, ',');
        getline(ss, aEmail, ',');
        getline(ss, aStatus, ',');

        if (aCID == cID && aEmail == currentUserEmail)
        {
            totalClasses++;

            if (aStatus == "Present")
                presentCount++;
            else
                absentCount++;

            cout << "Date : " << aDate << "   Status : " << aStatus << endl;
        }
    }

    file.close();

    if (totalClasses == 0)
    {
        cout << "No Attendance Record Found for This Course.\n";
        system("pause");
        return;
    }

    double percentage = (double)presentCount / totalClasses * 100;

    cout << "\n-------------------------------------\n";
    cout << "Total Classes : " << totalClasses << endl;
    cout << "Present       : " << presentCount << endl;
    cout << "Absent        : " << absentCount << endl;
    cout << "Attendance %  : " << percentage << "%\n";
    cout << "=====================================\n";

    system("pause");
}

void ELearningSystem::studentList()
{
    system("cls");

    cout << "=====================================\n";
    cout << "          STUDENT LIST\n";
    cout << "=====================================\n\n";

    ifstream file("users.txt");

    if (!file)
    {
        cout << "No Student Found!\n";
        system("pause");
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line))
    {
        stringstream ss(line);

        string role1, email1, password1;
        string name1, phone1, dept1;
        string question1, answer1;

        getline(ss, role1, ',');
        getline(ss, email1, ',');
        getline(ss, password1, ',');
        getline(ss, name1, ',');
        getline(ss, phone1, ',');
        getline(ss, dept1, ',');
        getline(ss, question1, ',');
        getline(ss, answer1, ',');

        if (role1 == "Student")
        {
            found = true;
            cout << "Name       : " << name1 << endl;
            cout << "Email      : " << email1 << endl;
            cout << "Phone      : " << phone1 << endl;
            cout << "Department : " << dept1 << endl;
            cout << "\n-------------------------------------\n";
        }
    }

    file.close();

    if (!found)
        cout << "No Student Registered.\n";

    system("pause");
}
void ELearningSystem::myAssignments()
{
    system("cls");

    cout << "=====================================\n";
    cout << "        MY ASSIGNMENTS\n";
    cout << "=====================================\n\n";

    // ================================
    // Step 1: Find Student's Courses
    // ================================

    ifstream enrollFile("enrollments.txt");

    if (!enrollFile)
    {
        cout << "No Enrollment Found.\n";
        system("pause");
        return;
    }

    string enrolledIDs[100];
    int enrolledCount = 0;
    string line;

    while (getline(enrollFile, line))
    {
        stringstream ss(line);

        string cID;
        string studentEmail;

        getline(ss, cID, ',');
        getline(ss, studentEmail, ',');

        if (studentEmail == currentUserEmail && enrolledCount < 100)
        {
            enrolledIDs[enrolledCount] = cID;
            enrolledCount++;
        }
    }

    enrollFile.close();

    // ================================
    // Step 2: Check Enrollment
    // ================================

    if (enrolledCount == 0)
    {
        cout << "You are not enrolled in any course yet.\n";
        cout << "Enroll in a course first to see its assignments.\n";

        system("pause");
        return;
    }

    // ================================
    // Step 3: Open Assignment File
    // ================================

    ifstream file("assignments.txt");

    if (!file)
    {
        cout << "No Assignment Found.\n";

        system("pause");
        return;
    }

    bool found = false;

    // Store Google Drive links
    string assignmentLinks[100];

    int linkCount = 0;

    // ================================
    // Step 4: Read Assignments
    // ================================

    while (getline(file, line))
    {
        stringstream ss(line);

        string cID;
        string title;
        string description;
        string deadline;
        string pdf;
        string teacherEmail;

        getline(ss, cID, ',');
        getline(ss, title, ',');
        getline(ss, description, ',');
        getline(ss, deadline, ',');
        getline(ss, pdf, ',');
        getline(ss, teacherEmail, ',');

        // ================================
        // Check whether student is enrolled
        // ================================

        bool isEnrolled = false;

        for (int i = 0; i < enrolledCount; i++)
        {
            if (enrolledIDs[i] == cID)
            {
                isEnrolled = true;
                break;
            }
        }

        // ================================
        // Show Assignment
        // ================================

        if (isEnrolled)
        {
            found = true;

            if (linkCount < 100)
            {
                assignmentLinks[linkCount] = pdf;
            }

            cout << "Assignment " << (linkCount + 1) << "\n";

            cout << "Course ID    : " << cID << endl;
            cout << "Title        : " << title << endl;
            cout << "Description  : " << description << endl;
            cout << "Deadline     : " << deadline << endl;
            cout << "Google Drive : " << pdf << endl;

            cout << "\n-------------------------------------\n";

            linkCount++;
        }
    }

    file.close();

    // ================================
    // Step 5: No Assignment Found
    // ================================

    if (!found)
    {
        cout << "No Assignment Available for Your Enrolled Courses.\n";

        system("pause");
        return;
    }

    // ================================
    // Step 6: Open Google Drive Link
    // ================================

    cout << "\n=====================================\n";
    cout << "       OPEN ASSIGNMENT\n";
    cout << "=====================================\n";

    cout << "Enter Assignment Number to Open\n";
    cout << "Enter 0 to Back\n";

    cout << "\nChoice : ";

    int choice;

    cin >> choice;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // ================================
    // Back
    // ================================

    if (choice == 0)
    {
        return;
    }

    // ================================
    // Check Choice
    // ================================

    if (choice < 1 || choice > linkCount)
    {
        cout << "\nInvalid Assignment Number!\n";

        system("pause");
        return;
    }

    // ================================
    // Get Selected Google Drive Link
    // ================================

    string selectedLink = assignmentLinks[choice - 1];

    // ================================
    // Open Link in Default Browser
    // ================================

    string command = "start \"\" \"" + selectedLink + "\"";

    system(command.c_str());

    cout << "\nGoogle Drive link opened in your browser.\n";

    system("pause");
}


void ELearningSystem::submitAssignment()
{
    system("cls");

    string cID, title, submissionFile;

    cout << "=====================================\n";
    cout << "       SUBMIT ASSIGNMENT\n";
    cout << "          (0 = Back)\n";
    cout << "=====================================\n\n";

    cout << "Enter Course ID       : ";
    getline(cin, cID);

    if (cID == "0")
        return;

    cout << "Enter Assignment Title: ";
    getline(cin, title);

    ifstream assignFile("assignments.txt");
    bool assignmentExists = false;
    string line;

    while (getline(assignFile, line))
    {
        stringstream ss(line);
        string acID, atitle, adesc, adeadline, apdf, aemail;

        getline(ss, acID, ',');
        getline(ss, atitle, ',');
        getline(ss, adesc, ',');
        getline(ss, adeadline, ',');
        getline(ss, apdf, ',');
        getline(ss, aemail, ',');

        if (acID == cID && atitle == title)
        {
            assignmentExists = true;
            break;
        }
    }
    assignFile.close();

    if (!assignmentExists)
    {
        cout << "\nAssignment Not Found for this Course!\n";
        system("pause");
        return;
    }

    ifstream subCheck("submissions.txt");
    bool alreadySubmitted = false;

    while (getline(subCheck, line))
    {
        stringstream ss(line);
        string scID, stitle, semail, sfile;

        getline(ss, scID, ',');
        getline(ss, stitle, ',');
        getline(ss, semail, ',');
        getline(ss, sfile, ',');

        if (scID == cID && stitle == title && semail == currentUserEmail)
        {
            alreadySubmitted = true;
            break;
        }
    }
    subCheck.close();

    if (alreadySubmitted)
    {
        cout << "\nYou have already submitted this assignment!\n";
        system("pause");
        return;
    }

    cout << "Enter Your Submission File Name (e.g. answer.pdf): ";
    getline(cin, submissionFile);

    ofstream file("submissions.txt", ios::app);
    file << cID << "," << title << "," << currentUserEmail << ","
         << submissionFile << "\n";
    file.close();

    cout << "\n=====================================\n";
    cout << "Assignment Submitted Successfully!\n";
    cout << "=====================================\n";

    system("pause");
}

void ELearningSystem::courseEnrollment()
{
    system("cls");

    string searchID;

    cout << "=====================================\n";
    cout << "         COURSE ENROLLMENT\n";
    cout << "           (0 = Back)\n";
    cout << "=====================================\n\n";

    cout << "Enter Course ID to Enroll : ";
    getline(cin, searchID);

    if (searchID == "0")
        return;

    ifstream courseFile("courses.txt");
    bool courseExists = false;
    string courseNameFound;

    string line;
    while (getline(courseFile, line))
    {
        stringstream ss(line);
        string id, cname, department, sem, cr, temail;

        getline(ss, id, ',');
        getline(ss, cname, ',');
        getline(ss, department, ',');
        getline(ss, sem, ',');
        getline(ss, cr, ',');
        getline(ss, temail, ',');

        if (id == searchID)
        {
            courseExists = true;
            courseNameFound = cname;
            break;
        }
    }
    courseFile.close();

    if (!courseExists)
    {
        cout << "\nCourse Not Found!\n";
        system("pause");
        return;
    }

    ifstream enrollCheck("enrollments.txt");
    bool alreadyEnrolled = false;

    while (getline(enrollCheck, line))
    {
        stringstream ss(line);
        string cID, studentEmail;

        getline(ss, cID, ',');
        getline(ss, studentEmail, ',');

        if (cID == searchID && studentEmail == currentUserEmail)
        {
            alreadyEnrolled = true;
            break;
        }
    }
    enrollCheck.close();

    if (alreadyEnrolled)
    {
        cout << "\nYou are already enrolled in this course!\n";
        system("pause");
        return;
    }

    ofstream file("enrollments.txt", ios::app);
    file << searchID << "," << currentUserEmail << "\n";
    file.close();

    cout << "\n=====================================\n";
    cout << "Successfully Enrolled in: " << courseNameFound << "\n";
    cout << "=====================================\n";

    system("pause");
}

void ELearningSystem::viewEnrolledCourses()
{
    system("cls");

    cout << "=====================================\n";
    cout << "        MY ENROLLED COURSES\n";
    cout << "=====================================\n\n";

    ifstream enrollFile("enrollments.txt");

    if (!enrollFile)
    {
        cout << "No Enrollment Found.\n";
        system("pause");
        return;
    }

    string line;
    bool found = false;

    while (getline(enrollFile, line))
    {
        stringstream ss(line);
        string cID, studentEmail;

        getline(ss, cID, ',');
        getline(ss, studentEmail, ',');

        if (studentEmail == currentUserEmail)
        {
            ifstream courseFile("courses.txt");
            string cline;

            while (getline(courseFile, cline))
            {
                stringstream cs(cline);
                string id, cname, department, sem, cr, temail;

                getline(cs, id, ',');
                getline(cs, cname, ',');
                getline(cs, department, ',');
                getline(cs, sem, ',');
                getline(cs, cr, ',');
                getline(cs, temail, ',');

                if (id == cID)
                {
                    found = true;
                    cout << "Course ID   : " << id << endl;
                    cout << "Course Name : " << cname << endl;
                    cout << "Department  : " << department << endl;
                    cout << "Semester    : " << sem << endl;
                    cout << "Credit      : " << cr << endl;
                    cout << "\n-------------------------------------\n";
                    break;
                }
            }
            courseFile.close();
        }
    }

    enrollFile.close();

    if (!found)
        cout << "No Enrolled Course Found.\n";

    system("pause");
}

int main()
{
    ELearningSystem obj;
    int choice;

    while (true)
    {
        system("cls");
        cout << "        E-LEARNING PLATFORM\n";

        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Forgot Password\n";
        cout << "4. Exit\n";
        cout << "choice : ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            obj.registerUser();
            break;

        case 2:
            obj.loginUser();
            break;

        case 3:
            obj.forgotPassword();
            break;

        case 4:
            cout << "\nThank you for using E-Learning Platform.\n";
            return 0;

        default:
            cout << "\nInvalid Choice! Please try again.\n";
        }
    }

    return 0;
}
