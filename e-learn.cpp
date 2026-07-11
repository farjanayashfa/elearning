#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <limits>
#include<conio.h>
#include <windows.h>
#include <sstream>
#include <ctime>
#include <cstdlib>

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
    int generatedOTP;
    string securityQuestion;
    string securityAnswer;

public:
    void studentDashboard();
    void teacherDashboard();
    void viewProfile();
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

        cout << "\nSecurity Question: ";
        getline(cin, securityQuestion);

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

        default:

            cout<<"\nInvalid Choice!\n";
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

    cout << "\n===== CHANGE PASSWORD =====\n";

    cout << "Enter Old Password: ";
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

            generatedOTP = 100000 + rand() % 900000;

            ofstream otpFile("OTP_Message.txt");

            otpFile << "=====================================\n";
            otpFile << "      E-LEARNING PLATFORM\n";
            otpFile << "=====================================\n\n";
            otpFile << "Change Password OTP\n\n";
            otpFile << "Email : " << email1 << "\n";
            otpFile << "OTP : " << generatedOTP << "\n";

            otpFile.close();

            cout << "\nSending OTP";

            for(int i=0; i<3; i++)
            {
                cout<<".";
                Sleep(500);
            }

            cout<<"\n\nOTP Sent Successfully!\n";
            cout<<"Please check OTP_Message.txt\n";

            int otp;

            cout<<"\nEnter OTP : ";
            cin>>otp;
            cin.ignore();

            if(otp!=generatedOTP)
            {
                cout<<"\nWrong OTP!\n";

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
    cout << "Enter Email: ";
    getline(cin, email);

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

            generatedOTP = 100000 + rand() % 900000;

            ofstream otpFile("OTP_Message.txt");

            otpFile << "=====================================\n";
            otpFile << "      E-LEARNING PLATFORM\n";
            otpFile << "=====================================\n\n";
            otpFile << "Password Reset OTP\n\n";
            otpFile << "Email : " << email1 << "\n";
            otpFile << "OTP : " << generatedOTP << "\n";

            otpFile.close();

            cout << "\nSending OTP";
            for(int i=0; i<3; i++)
            {
                cout<<".";
                Sleep(500);
            }

            cout << "\n\nOTP Sent Successfully!\n";
            cout << "Please check OTP_Message.txt\n";

            int otp;
            cout << "\nEnter OTP: ";
            cin >> otp;
            cin.ignore();

            if (otp == generatedOTP)
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

                password1 = newPass;

                cout << "\nPassword Reset Successful!\n";
            }
            else
            {
                cout << "\nWrong OTP!\n";
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
        cout<<"       TEACHER DASHBOARD\n";
        cout<<"=====================================\n";

        cout<<"1. View Profile\n";
        cout<<"2. Change Password\n";
        cout<<"3. Logout\n";
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
        default:

            cout<<"\nInvalid Choice!\n";
            system("pause");
        }
    }
}

int main()
{
    srand(time(0));

    ELearningSystem obj;
    int choice;

    while (true)
    {
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

