#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <limits>
#include <conio.h>
#include <sstream>
#include <windows.h>
#include <commdlg.h>

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

public:
    string browsePDF();
    void studentDashboard();
    void teacherDashboard();
    void viewProfile();
    void manageCourses();
    void createCourse();
    void uploadLecture();
    void uploadAssignment();
    void viewAssignments();
    void gradeStudents();
    void quizManagement();
    void attendance();
    void announcements();
    void studentList();
    void courseProgress();
    void messages();
    void changePassword();
    void forgotPassword();
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

            if (ch == 13) // Enter
                break;

            else if (ch == 8) // Backspace
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

    void registerUser()
    {
        cout << "\n===== REGISTER =====\n";

        //role choice kora
        int roleChoice;

        do
        {
            cout << "\nSelect Role\n";
            cout << "1. Student\n";
            cout << "2. Teacher\n";
            cout << "Choice: ";
            cin >> roleChoice;
            cin.ignore();

            if(roleChoice==1)
                role="Student";
            else if(roleChoice==2)
                role="Teacher";
            else
                cout<<"Invalid Choice!\n";

        }
        while(roleChoice!=1 && roleChoice!=2);

        // NAME
        do
        {
            cout << "Name: ";
            getline(cin, name);

            if (!isValidName(name))
                cout << "[ERROR] First letter must be CAPITAL!\n";

        }
        while (!isValidName(name));

        // EMAIL
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

        // PHONE
        do
        {
            cout << "Phone: ";
            getline(cin, phone);

            if (!isValidPhone(phone))
                cout << "[ERROR] Must start with 01 and be 11 digits!\n";

        }
        while (!isValidPhone(phone));

        // DEPARTMENT
        do
        {
            cout << "Department (CAPITAL LETTERS): ";
            getline(cin, dept);

            if (!isValidDept(dept))
                cout << "[ERROR] Only CAPITAL letters allowed!\n";

        }
        while (!isValidDept(dept));

        // PASSWORD


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

            switch(questionChoice)
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
        while(questionChoice < 1 || questionChoice > 4);

        cout << "Answer: ";
        getline(cin, securityAnswer);

        // SAVE TO FILE

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
    void loginUser()
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

        if(choice=='Y' || choice=='y')
        {
            cout<<"\nPassword : "<<p<<endl;
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

                // Logged in user information
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
            if(role=="Student")
            {
                studentDashboard();
            }
            else
            {
                teacherDashboard();
            }

        }

        else
        {
            cout << "\n=====================================\n";
            cout << "Invalid Email or Password!\n";
            cout << "Please try again.\n";
            cout << "=====================================\n";
        }
    }

};
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
        cout<<"2. Change Password\n";
        cout<<"3. Logout\n";
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
            changePassword();
            break;

        case 3:
        {
            char ans;

            cout << "\nAre you sure you want to logout? (Y/N): ";
            cin >> ans;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(ans=='Y' || ans=='y')
            {
                cout << "\nLogging out...\n";
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

Start:

    cout << "\n===== CHANGE PASSWORD =====\n";
    cout << "1. Continue\n";
    cout << "2. Back\n";
    cout << "Choice: ";

    int op;
    cin >> op;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(op == 2)
    {
        return;
    }

    if(op != 1)
    {
        cout << "\nInvalid Choice!\n";
        system("pause");
        system("cls");
        goto Start;
    }

    cout << "\nEnter Old Password: ";
    oldPass = inputPassword();

    ifstream file("users.txt");
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while(getline(file, line))
    {
        stringstream ss(line);

        string role1,email1,password1,name1,phone1,dept1,question1,answer1;

        getline(ss, role1, ',');
        getline(ss, email1, ',');
        getline(ss, password1, ',');
        getline(ss, name1, ',');
        getline(ss, phone1, ',');
        getline(ss, dept1, ',');
        getline(ss, question1, ',');
        getline(ss, answer1, ',');

        if(email1==currentUserEmail)
        {
            if(password1!=oldPass)
            {
                cout<<"\nWrong Old Password!\n";

                temp<<role1<<","<<email1<<","<<password1<<","<<name1<<","
                    <<phone1<<","<<dept1<<","<<question1<<","<<answer1<<"\n";

                continue;
            }
            string answer;

            cout << "\nSecurity Question:\n";
            cout << question1 << endl;

            cout << "Answer: ";
            getline(cin, answer);

            if(answer != answer1)
            {
                cout << "\nWrong Security Answer!\n";

                temp<<role1<<","<<email1<<","<<password1<<","<<name1<<","
                    <<phone1<<","<<dept1<<","<<question1<<","<<answer1<<"\n";

                continue;
            }





            string newPass;
            string confirmPass;

            do
            {
                cout<<"\nNew Password : ";
                newPass=inputPassword();

                if(!isStrongPassword(newPass))
                    cout<<"\nWeak Password!\n";

            }
            while(!isStrongPassword(newPass));

            cout<<"Confirm Password : ";
            confirmPass=inputPassword();

            if(newPass!=confirmPass)
            {
                cout<<"\nPassword Doesn't Match!\n";

                temp<<role1<<","<<email1<<","<<password1<<","<<name1<<","
                    <<phone1<<","<<dept1<<","<<question1<<","<<answer1<<"\n";

                continue;
            }

            password1=newPass;

            found=true;

            cout<<"\nPassword Changed Successfully.\n";
        }

        temp<<role1<<","<<email1<<","<<password1<<","<<name1<<","
            <<phone1<<","<<dept1<<","<<question1<<","<<answer1<<"\n";
    }

    file.close();
    temp.close();

    remove("users.txt");
    rename("temp.txt","users.txt");

    if(!found)
        cout<<"\nPassword Change Failed.\n";

    system("pause");

}

void ELearningSystem::forgotPassword()
{
    string email;

    cout << "\n========== FORGOT PASSWORD ==========\n";
    cout << "Enter Email (0 = Back): ";
    getline(cin, email);

    if(email=="0")
    {
        return;
    }

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

            if(answer == answer1)
            {
                string newPass;

                do
                {
                    cout << "Enter New Password: ";
                    newPass = inputPassword();

                    if(!isStrongPassword(newPass))
                        cout << "Weak Password! Try Again.\n";

                }
                while(!isStrongPassword(newPass));

                string confirmPass;

                cout << "Confirm Password: ";
                confirmPass = inputPassword();

                if(newPass != confirmPass)
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
    {
        cout << "\nEmail not found!\n";
    }

    system("pause");

}

void ELearningSystem::teacherDashboard()
{

    int choice;

    while(true)
    {
        system("cls");

        cout<<"=====================================\n";
        cout<<"        TEACHER DASHBOARD\n";
        cout<<"=====================================\n";

        cout<<"1. My Profile\n";
        cout<<"2. Manage Courses\n";
        cout<<"3. Create Course\n";
        cout<<"4. Upload Lecture\n";
        cout<<"5. Upload Assignment\n";
        cout<<"6. View Assignments\n";
        cout<<"7. Grade Students\n";
        cout<<"8. Quiz Management\n";
        cout<<"9. Attendance\n";
        cout<<"10. Announcements\n";
        cout<<"11. Student List\n";
        cout<<"12. Course Progress\n";
        cout<<"13. Messages\n";
        cout<<"14. Change Password\n";
        cout<<"15. Logout\n";

        cout<<"\nChoice : ";
        cin>>choice;
        cin.ignore();

        switch(choice)
        {
        case 1:
            viewProfile();
            break;

        case 2:
            manageCourses();
            break;

        case 3:
            createCourse();
            break;

        case 4:
            uploadLecture();
            break;

        case 5:
            uploadAssignment();
            break;

        case 6:
            viewAssignments();
            break;

        case 7:
            gradeStudents();
            break;

        case 8:
            quizManagement();
            break;

        case 9:
            attendance();
            break;

        case 10:
            announcements();
            break;

        case 11:
            studentList();
            break;

        case 12:
            courseProgress();
            break;

        case 13:
            messages();
            break;

        case 14:
            changePassword();
            break;

        case 15:
            cout<<"\nLogging out...\n";
            return;

        default:
            cout<<"\nInvalid Choice!\n";
            system("pause");
        }
    }
}
void ELearningSystem::manageCourses()
{
    int choice;

    while(true)
    {
        system("cls");

        cout<<"=====================================\n";
        cout<<"        MANAGE COURSES\n";
        cout<<"=====================================\n";

        cout<<"1. View My Courses\n";
        cout<<"2. Search Course\n";
        cout<<"3. Edit Course\n";
        cout<<"4. Delete Course\n";
        cout<<"5. Back\n";

        cout<<"\nChoice : ";
        cin>>choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice)
        {
        case 1:
{
    system("cls");

    ifstream file("courses.txt");

    string line;

    cout<<"=====================================\n";
    cout<<"         MY COURSES\n";
    cout<<"=====================================\n\n";

    bool found = false;

    while(getline(file,line))
    {
        stringstream ss(line);

        string id,name,department,sem,cr,email;

        getline(ss,id,',');
        getline(ss,name,',');
        getline(ss,department,',');
        getline(ss,sem,',');
        getline(ss,cr,',');
        getline(ss,email,',');

        if(email==currentUserEmail)
        {
            found=true;

            cout<<"Course ID   : "<<id<<endl;
            cout<<"Course Name : "<<name<<endl;
            cout<<"Department  : "<<department<<endl;
            cout<<"Semester    : "<<sem<<endl;
            cout<<"Credit      : "<<cr<<endl;

            cout<<"\n-----------------------------\n";
        }
    }

    if(!found)
    {
        cout<<"No Course Found.\n";
    }

    file.close();

    system("pause");
    break;
}

       case 2:
{
    system("cls");

    string searchID;

    cout<<"=====================================\n";
    cout<<"         SEARCH COURSE\n";
    cout<<"=====================================\n\n";

    cout<<"Enter Course ID : ";
    getline(cin, searchID);

    ifstream file("courses.txt");

    string line;
    bool found=false;

    while(getline(file,line))
    {
        stringstream ss(line);

        string id,name,department,sem,cr,email;

        getline(ss,id,',');
        getline(ss,name,',');
        getline(ss,department,',');
        getline(ss,sem,',');
        getline(ss,cr,',');
        getline(ss,email,',');


        if(id==searchID && email==currentUserEmail)
        {
            found=true;

            cout<<"\n========== COURSE FOUND ==========\n";

            cout<<"Course ID   : "<<id<<endl;
            cout<<"Course Name : "<<name<<endl;
            cout<<"Department  : "<<department<<endl;
            cout<<"Semester    : "<<sem<<endl;
            cout<<"Credit      : "<<cr<<endl;

            cout<<"==================================\n";
        }
    }

    file.close();

    if(!found)
    {
        cout<<"\nCourse Not Found!\n";
    }

    system("pause");
    break;
}
       case 3:
{
    system("cls");

    string searchID;

    cout<<"=====================================\n";
    cout<<"          EDIT COURSE\n";
    cout<<"=====================================\n\n";

    cout<<"Enter Course ID : ";
    getline(cin, searchID);

    ifstream file("courses.txt");
    ofstream temp("temp.txt");

    string line;
    bool found=false;

    while(getline(file,line))
    {
        stringstream ss(line);

        string id,name,department,sem,cr,email;

        getline(ss,id,',');
        getline(ss,name,',');
        getline(ss,department,',');
        getline(ss,sem,',');
        getline(ss,cr,',');
        getline(ss,email,',');

        if(id==searchID && email==currentUserEmail)
        {
            found=true;

            cout<<"\nCurrent Information\n";
            cout<<"Course Name : "<<name<<endl;
            cout<<"Department  : "<<department<<endl;
            cout<<"Semester    : "<<sem<<endl;
            cout<<"Credit      : "<<cr<<endl;

            cout<<"\nEnter New Course Name : ";
            getline(cin,name);

            cout<<"Enter New Department : ";
            getline(cin,department);

            cout<<"Enter New Semester : ";
            getline(cin,sem);

            cout<<"Enter New Credit : ";
            getline(cin,cr);
        }

        temp<<id<<","
            <<name<<","
            <<department<<","
            <<sem<<","
            <<cr<<","
            <<email<<"\n";
    }

    file.close();
    temp.close();

    remove("courses.txt");
    rename("temp.txt","courses.txt");

    if(found)
        cout<<"\nCourse Updated Successfully.\n";
    else
        cout<<"\nCourse Not Found.\n";

    system("pause");
    break;
}

        case 4:
{
    system("cls");

    string searchID;
    char confirm;

    cout<<"=====================================\n";
    cout<<"         DELETE COURSE\n";
    cout<<"=====================================\n\n";

    cout<<"Enter Course ID : ";
    getline(cin, searchID);

    ifstream file("courses.txt");
    ofstream temp("temp.txt");

    string line;
    bool found=false;

    while(getline(file,line))
    {
        stringstream ss(line);

        string id,name,department,sem,cr,email;

        getline(ss,id,',');
        getline(ss,name,',');
        getline(ss,department,',');
        getline(ss,sem,',');
        getline(ss,cr,',');
        getline(ss,email,',');

        if(id==searchID && email==currentUserEmail)
        {
            found=true;

            cout<<"\nCourse Found!\n";
            cout<<"Course Name : "<<name<<endl;

            cout<<"\nAre you sure you want to delete this course? (Y/N): ";
            cin>>confirm;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(confirm=='Y' || confirm=='y')
            {
                cout<<"\nCourse Deleted Successfully!\n";
                continue;
            }
        }

        temp<<id<<","
            <<name<<","
            <<department<<","
            <<sem<<","
            <<cr<<","
            <<email<<"\n";
    }

    file.close();
    temp.close();

    remove("courses.txt");
    rename("temp.txt","courses.txt");

    if(!found)
    {
        cout<<"\nCourse Not Found!\n";
    }

    system("pause");
    break;
}

        case 5:
            return;

        default:
            cout<<"\nInvalid Choice!\n";
            system("pause");
        }
    }
}

void ELearningSystem::createCourse()
{
    system("cls");

    cout << "=====================================\n";
    cout << "          CREATE COURSE\n";
    cout << "=====================================\n";

    cout << "Course ID      : ";
    getline(cin, courseID);

    cout << "Course Name    : ";
    getline(cin, courseName);

    cout << "Department     : ";
    getline(cin, dept);

    cout << "Semester       : ";
    getline(cin, semester);

    cout << "Credit         : ";
    getline(cin, credit);

    ofstream file("courses.txt", ios::app);

    file << courseID << ","
         << courseName << ","
         << dept << ","
         << semester << ","
         << credit << ","
         << currentUserEmail << "\n";

    file.close();

    cout << "\n=====================================\n";
    cout << "Course Created Successfully.\n";
    cout << "=====================================\n";

    system("pause");
}

void ELearningSystem::uploadLecture()
{
    cout<<"\nUpload Lecture Feature Coming Soon...\n";
    system("pause");
}

void ELearningSystem::uploadAssignment()
{
    cout<<"\nUpload Assignment Feature Coming Soon...\n";
    system("pause");
}

void ELearningSystem::viewAssignments()
{
    cout<<"\nView Assignments Feature Coming Soon...\n";
    system("pause");
}

void ELearningSystem::gradeStudents()
{
    cout<<"\nGrade Students Feature Coming Soon...\n";
    system("pause");
}

void ELearningSystem::quizManagement()
{
    cout<<"\nQuiz Management Feature Coming Soon...\n";
    system("pause");
}

void ELearningSystem::attendance()
{
    cout<<"\nAttendance Feature Coming Soon...\n";
    system("pause");
}

void ELearningSystem::announcements()
{
    cout<<"\nAnnouncements Feature Coming Soon...\n";
    system("pause");
}

void ELearningSystem::studentList()
{
    cout<<"\nStudent List Feature Coming Soon...\n";
    system("pause");
}

void ELearningSystem::courseProgress()
{
    cout<<"\nCourse Progress Feature Coming Soon...\n";
    system("pause");
}

void ELearningSystem::messages()
{
    cout<<"\nMessages Feature Coming Soon...\n";
    system("pause");
}
string ELearningSystem::browsePDF()
{
    char filename[MAX_PATH] = "";

    OPENFILENAME ofn;

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;

    // PDF
    ofn.lpstrFilter = "PDF Files\0*.pdf\0All Files\0*.*\0";

    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    if(GetOpenFileName(&ofn))
    {
        return string(filename);
    }

    return "";
}
int main()
{

    ELearningSystem obj;
    int choice;

    while (true)
    {   system("cls");
        cout << "        E-LEARNING PLATFORM\n";


        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Forgot Password\n";
        cout << "4. Exit\n";
        cout<<"choice : ";
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
