#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <algorithm>
#include <cctype>
using namespace std;

class Validations
{
public:
    bool idValidation(const string &idString)
    {
        if (idString.empty() || idString.find(' ') != string::npos)
        {
            return false;
        }
        for (char ch : idString)
        {
            if (!isdigit(ch))
            {
                return false;
            }
        }
        return true;
    }

    bool stringValidation(const string &str)
    {
        if (str.empty())
        {
            return false;
        }
        for (char ch : str)
        {
            if (!isspace(ch))
            {
                if (!isdigit(ch))
                {
                    return true;
                }
            }
        }
        return false;
    }
};

class Book
{
public:
    int bookID;
    string title;
    string author;
    int availableCopies;
    bool isAvailable;

    Book() : bookID(0), title(""), author(""), isAvailable(true) {}
    Book(int id, string t, string a) : bookID(id), title(t), author(a), availableCopies(5) {}
};

class BorrowedBookNode
{
public:
    int bookID;
    BorrowedBookNode *next;

    BorrowedBookNode(int id) : bookID(id), next(nullptr) {}
};

class Student

{
public:
    int studentID;
    string name;
    bool hasMembership;
    BorrowedBookNode *borrowedBooksHead;

    Student() : studentID(0), name(""), hasMembership(false), borrowedBooksHead(nullptr) {}

    Student(int id, string n, bool membership = false) : studentID(id), name(n), hasMembership(membership), borrowedBooksHead(nullptr) {}

    void borrowBook(int bookID)
    {
        if (hasMembership)
        {
            BorrowedBookNode *newNode = new BorrowedBookNode(bookID);
            newNode->next = borrowedBooksHead;
            borrowedBooksHead = newNode;
        }
        else
        {
            cout << "Student does not have an active membership and cannot borrow books.\n";
        }
    }

    void returnBook(int bookID)
    {
        BorrowedBookNode *current = borrowedBooksHead;
        BorrowedBookNode *previous = nullptr;

        while (current)
        {
            if (current->bookID == bookID)
            {
                if (previous)
                {
                    previous->next = current->next;
                }
                else
                {
                    borrowedBooksHead = current->next;
                }
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }
    }

    bool hasBorrowedBook(int bookID)
    {
        BorrowedBookNode *current = borrowedBooksHead;
        while (current)
        {
            if (current->bookID == bookID)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

class BookNode
{
public:
    Book data;
    BookNode *next;

    BookNode(Book d) : data(d), next(nullptr) {}
};

class StudentNode
{
public:
    Student data;
    StudentNode *next;

    StudentNode(Student d) : data(d), next(nullptr) {}
};

class BookLinkedList
{
public:
    BookNode *head;

    BookLinkedList() : head(nullptr) {}

    void insert(Book data)
    {
        BookNode *newNode = new BookNode(data);
        newNode->next = head;
        head = newNode;
    }

    Book *search(int bookID)
    {
        BookNode *current = head;
        while (current)
        {
            if (current->data.bookID == bookID)
            {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }

    bool remove(int bookID)
    {
        BookNode *current = head;
        BookNode *previous = nullptr;

        while (current)
        {
            if (current->data.bookID == bookID)
            {
                if (previous)
                {
                    previous->next = current->next;
                }
                else
                {
                    head = current->next;
                }
                delete current;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }
};

class StudentLinkedList
{
public:
    StudentNode *head;

    StudentLinkedList() : head(nullptr) {}

    void insert(Student data)
    {
        StudentNode *newNode = new StudentNode(data);
        newNode->next = head;
        head = newNode;
    }

    Student *search(int studentID)
    {
        StudentNode *current = head;
        while (current)
        {
            if (current->data.studentID == studentID)
            {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }

    void loadStudentData(string name[], int &i)
    {
        cout << "111";
        StudentNode *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data.name;
            name[i++] = temp->data.name;
            temp = temp->next;
        }
        cout << "222";
    }
    void displaySearchStudents(string name)
    {
        cout << "Searched data in the Library: \n";

        StudentNode *current = head;
        while (current)
        {
            string lowerName = current->data.name;
            for (size_t i = 0; i < lowerName.length(); ++i)
            {
                lowerName[i] = std::tolower(lowerName[i]);
            }
            if (lowerName.find(name) != string::npos)
            {
                cout << "\nName : " << current->data.name
                     << "\nStudent Id: " << current->data.studentID << endl;
            }
            current = current->next;
        }
    }
    void displayStudents()
    {
        StudentNode *current = head;
        if (current == nullptr)
        {
            cout << "\nNo Students Found\n";
            return;
        }
        cout << "All Students Record: \n";

        while (current)
        {
            cout << "\nName : " << current->data.name
                 << "\nStudent Id: " << current->data.studentID << endl;
            current = current->next;
        }
    }

    bool remove(int studentID)
    {
        StudentNode *prev = nullptr, *current = head;

        while (current)
        {
            if (current->data.studentID == studentID)
            {
                if (prev)
                {
                    prev->next = current->next;
                }
                else
                {
                    head = current->next;
                }
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }
};

class BookHashTable
{
private:
    int size;
    BookLinkedList *table;

    int hashFunction(int key)
    {
        return key % size;
    }

public:
    int getSize() const { return size; }
    BookLinkedList *getTable() const { return table; }
    BookHashTable(int s = 100) : size(s), table(new BookLinkedList[s]) {}

    void insert(int key, Book data)
    {
        int index = hashFunction(key);
        table[index].insert(data);
    }

    Book *search(int key)
    {
        int index = hashFunction(key);
        return table[index].search(key);
    }

    void LoadBookData(string bookName[], string bookAuther[], int &k, int &j)
    {
        for (int i = 0; i < size; ++i)
        {
            BookNode *current = table[i].head;
            while (current)
            {
                bookName[k++] = current->data.title;
                bookAuther[j++] = current->data.author;
                current = current->next;
            }
        }
    }
    void displaySearchBooks(string name)
    {
        cout << "Searched data in the Library: \n";
        for (int i = 0; i < size; ++i)
        {
            BookNode *current = table[i].head;
            while (current)
            {
                string lowerName = current->data.title;
                for (size_t i = 0; i < lowerName.length(); ++i)
                {
                    lowerName[i] = std::tolower(lowerName[i]);
                }
                string lowerauther = current->data.author;
                for (size_t i = 0; i < lowerauther.length(); ++i)
                {
                    lowerauther[i] = std::tolower(lowerauther[i]);
                }
                if (lowerName.find(name) != string::npos || lowerauther.find(name) != string::npos)
                {
                    cout << "\nID: " << current->data.bookID
                         << "\nTitle: " << current->data.title
                         << "\nAuthor: " << current->data.author
                         << "\nAvailable Copies: " << current->data.availableCopies << endl;
                }
                current = current->next;
            }
        }
    }
    void displayBooks()
    {
        cout << "Books in the Library:\n";
        for (int i = 0; i < size; ++i)
        {
            BookNode *current = table[i].head;
            while (current)
            {
                cout << "\nID: " << current->data.bookID
                     << "\nTitle: " << current->data.title
                     << "\nAuthor: " << current->data.author
                     << "\nAvailable Copies: " << current->data.availableCopies << endl;
                current = current->next;
            }
        }
    }
    void remove(int key)
    {
        int index = hashFunction(key);
        table[index].remove(key); // Assume BookLinkedList has a remove method
    }

    ~BookHashTable()
    {
        delete[] table;
    }
};

class LibrarySystem
{
private:
    string requestedname[100];
    int requestedID[100];
    int requestcount;

    BookHashTable books;
    StudentLinkedList students;
    string role;
    Validations validator;

public:
    LibrarySystem()
    {
        requestcount = 0;
    }
    void requestPanel()
    {
        if (requestcount == 0)
        {
            cout << "\nNo Request Recived Yet!\n\n";

            cin.get();
            return;
        }
        else
        {
            int r = 1;
            cout << "\nTotal Recived requets : " << requestcount;
            for (int i = 0; i < requestcount; i++)
            {
                cout << "\nRequest :" << r++;
                cout << "\nStudent Name : " << requestedname[i];
                cout << "\nStudent Id : " << requestedID[i];
                cout << "\nApprove Request (y/n): ";
                string choice;
                cin >> choice;
                if (!validator.stringValidation(choice))
                {
                    cout << "Invalid option. Please try again.\n";
                    continue;
                }
                if (choice == "y" || choice == "Y")
                {
                    students.insert(Student(requestedID[i], requestedname[i]));
                    cout << "Student added successfully!\n";
                    cout << "Press Enter to continue...";
                    if (i < requestcount)
                    {
                        for (int j = i; j < requestcount; j++)
                        {
                            requestedID[j] = requestedID[j + 1];
                            requestedname[j] = requestedname[j + 1];
                        }
                    }
                    i--;
                    requestcount--;
                }
                else if (choice == "n" || choice == "N")
                {
                    cout << endl;
                    continue;
                }
                else
                {
                    cout << "Invalid option. Please try again.\n";
                }
            }
        }
    }
    void addBook(int bookID, string title, string author)
    {
        Book book(bookID, title, author);
        Book *find = books.search(bookID);
        if (find)
        {
            cout << "Already book id exists so please give another id " << endl;
        }
        else
        {
            books.insert(bookID, book);
            cout << "Book added successfully!\n";
        }
    }

    void loadBooks(const std::string &filename)
    {
        ifstream inFile(filename.c_str());
        if (!inFile)
        {
            cerr << "Error opening file for reading!" << endl;
            return;
        }
        int bookID;
        string title, author, line;

        while (getline(inFile, line))
        {
            stringstream ss(line);
            string idStr;
            if (getline(ss, idStr, ','))
            {
                bookID = stoi(idStr);
            }
            if (getline(ss, title, ','))
            {
                // Removing leading space if any
                if (!title.empty() && title[0] == ' ')
                {
                    title.erase(0, 1);
                }
            }
            if (getline(ss, author))
            {
                // Removing leading space if any
                if (!author.empty() && author[0] == ' ')
                {
                    author.erase(0, 1);
                }
            }
            books.insert(bookID, Book(bookID, title, author));
        }
        inFile.close();
    }

    void saveBooks(const std::string &filename)
    {
        ofstream outFile(filename.c_str());
        if (!outFile)
        {
            cerr << "Error opening file for writing!" << endl;
            return;
        }
        int size = books.getSize();
        BookLinkedList *table = books.getTable();
        for (int i = 0; i < size; ++i)
        {
            BookNode *current = table[i].head;
            while (current)
            {
                outFile << current->data.bookID << "," << current->data.title << "," << current->data.author << "\n";
                current = current->next;
            }
        }
        outFile.close();
    }

    void addStudent(int studentID, string name, bool hasMembership = false)
    {
        Student student(studentID, name, hasMembership);
        Student *find = students.search(studentID);
        if (find)
        {
            cout << "Student id is already exist please enter another one" << endl;
        }
        else
        {
            students.insert(student);
            cout << "Student '" << name << "' registered in the library.\n";
        }
    }

    void manageMembership()
    {
        system("cls");
        int studentID;
        cout << "==========================================" << endl;
        cout << "            MANAGE MEMBERSHIP             " << endl;
        cout << "==========================================" << endl;
        cout << "Enter Student ID: ";
        cin >> studentID;

        Student *student = students.search(studentID); // Assuming students is a collection supporting search
        if (student)
        {
            cout << "Student found: " << student->name << endl;
            cout << "Current Membership Status: "
                 << (student->hasMembership ? "Active" : "Inactive") << endl;

            cout << "==========================================" << endl;
            cout << "1. Activate Membership" << endl;
            cout << "2. Cancel Membership" << endl;
            cout << "0. Back to Admin Menu" << endl;
            cout << "==========================================" << endl;
            cout << "Enter your Option: ";

            int option;
            cin >> option;

            switch (option)
            {
            case 1:
                if (!student->hasMembership)
                {
                    student->hasMembership = true;
                    cout << "Membership activated for student '" << student->name << "'.\n";
                }
                else
                {
                    cout << "Membership is already active for student '" << student->name << "'.\n";
                }
                break;

            case 2:
                if (student->hasMembership)
                {
                    student->hasMembership = false;
                    cout << "Membership canceled for student '" << student->name << "'.\n";
                }
                else
                {
                    cout << "The student '" << student->name << "' does not have an active membership.\n";
                }
                break;

            case 0:
                cout << "Returning to Admin Menu...\n";
                return;

            default:
                cout << "Invalid choice. Returning to Admin Menu.\n";
                return;
            }
        }
        else
        {
            cout << "Student not found.\n";
        }
    }

    void borrowBook(int studentID, int bookID)
    {
        Student *student = students.search(studentID);
        Book *book = books.search(bookID);
        if (student && student->hasMembership && book && book->availableCopies > 0)
        {
            student->borrowBook(bookID);
            book->availableCopies--;
            cout << "Book ID " << bookID << " borrowed by Student ID " << studentID << ".\n";
        }
        else
        {
            cout << "Borrowing failed. Ensure student is valid, has membership, and there are available copies of the book.\n";
        }
    }
    void returnBook(int studentID, int bookID)
    {
        Student *student = students.search(studentID);
        Book *book = books.search(bookID);

        if (student && book && student->hasBorrowedBook(bookID))
        {
            book->isAvailable = true;
            student->returnBook(bookID);
            cout << "Book '" << book->title << "' returned by '" << student->name << "'.\n";
        }
        else
        {
            cout << "The book was not borrowed by the student.\n";
        }
    }

    void displayBooks()
    {
        books.displayBooks();
    }

    void searchBook()
    {
        const int size = 1000;

        string bookname[size];
        string bookAuthor[size];
        int i = 0, j = 0;
        books.LoadBookData(bookname, bookAuthor, i, j);
        string *matchedNames = new string[i];
        string *matchedAuthers = new string[j];

        string currentInput = "";

        while (true)
        {
            system("cls");
            cout << " ---------------------------------------\n";
            cout << "| Enter a key to search: " << currentInput << "\t\t|";
            cout << "\n ---------------------------------------\n";

            int matchCountnames = 0;
            int matchCountAuthers = 0;
            if (!currentInput.empty())
            {
                cout << "\n\n";
                string lowerInput = currentInput;
                transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);

                for (int i = 0; i < size; i++)
                {
                    string lowerName = bookname[i];
                    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

                    if (lowerName.find(lowerInput) != string::npos)
                    {
                        matchedNames[matchCountnames++] = bookname[i]; // Add matched name to matchedNames
                    }
                }
                for (int i = 0; i < size; i++)
                {

                    string lowerName = bookAuthor[i];
                    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

                    if (lowerName.find(lowerInput) != string::npos)
                    {
                        matchedAuthers[matchCountAuthers++] = bookAuthor[i]; // Add matched name to matchedNames
                    }
                }
                if (matchCountnames > 0 || matchCountAuthers > 0)
                {
                    for (int i = 0; i < matchCountnames; i++)
                    {
                        cout << matchedNames[i] << "\n";
                    }
                    for (int i = 0; i < matchCountAuthers; i++)
                    {
                        cout << matchedAuthers[i] << "\n";
                    }
                }

                else
                {
                    cout << "No Data found.\n";
                }
            }
            char ch = getch();

            if (ch == 13)
            {
                if (matchCountnames <= 0 && matchCountAuthers <= 0)
                {
                    break;
                }
                string lowerInput = currentInput;
                transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);

                bool found = false;

                system("CLS");
                books.displaySearchBooks(lowerInput);
                break;
            }
            else if (ch == 27)
            { // Escape key
                cout << "\nSearch discarded. Returning to main menu.\n";
                break;
            }

            // Handle backspace
            else if (ch == 8)
            {
                if (!currentInput.empty())
                {
                    currentInput.pop_back();
                }
            }
            else
            {
                currentInput += ch;
            }
        }
    }

    void searchStudent()
    {
        const int size = 1000;

        string name[size];
        int i = 0;
        cout << "444;";
        students.loadStudentData(name, i);
        string *matchedNames = new string[i];
        cout << "444";
        string currentInput = "";

        while (true)
        {
            system("cls");
            cout << " ---------------------------------------\n";
            cout << "| Enter a key to search: " << currentInput << "\t\t|";
            cout << "\n ---------------------------------------\n";

            int matchCountnames = 0;
            if (!currentInput.empty())
            {
                cout << "\n\n";
                string lowerInput = currentInput;
                transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);

                for (int i = 0; i < size; i++)
                {
                    string lowerName = name[i];
                    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

                    if (lowerName.find(lowerInput) != string::npos)
                    {
                        matchedNames[matchCountnames++] = name[i]; // Add matched name to matchedNames
                    }
                }

                if (matchCountnames > 0)
                {
                    for (int i = 0; i < matchCountnames; i++)
                    {
                        cout << matchedNames[i] << "\n";
                    }
                }
                else
                {
                    cout << "No Data found.\n";
                }
            }
            char ch = getch();

            if (ch == 13)
            {
                if (matchCountnames <= 0)
                {
                    break;
                }
                string lowerInput = currentInput;
                transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);

                bool found = false;

                system("CLS");
                students.displaySearchStudents(lowerInput);
                break;
            }
            else if (ch == 27)
            { // Escape key
                cout << "\nSearch discarded. Returning to main menu.\n";
                break;
            }

            // Handle backspace
            else if (ch == 8)
            {
                if (!currentInput.empty())
                {
                    currentInput.pop_back();
                }
            }
            else
            {
                currentInput += ch;
            }
        }
    }

    void displayBorrowedBooks(int studentID)
    {
        Student *student = students.search(studentID);
        if (student)
        {
            BorrowedBookNode *current = student->borrowedBooksHead;
            cout << "Books borrowed by '" << student->name << "':\n";
            while (current)
            {
                Book *book = books.search(current->bookID);
                if (book)
                {
                    cout << "ID: " << book->bookID
                         << ", Title: " << book->title
                         << ", Author: " << book->author << endl;
                }
                current = current->next;
            }
        }
        else
        {
            cout << "Student not found.\n";
        }
    }

    void displayAllBorrowedBooks()
    {
        StudentNode *currentStudent = students.head; // Assuming students is a linked list of StudentNode
        if (!currentStudent)
        {
            cout << "No students found in the system.\n";
            return;
        }

        bool foundAnyBooks = false; // To check if at least one borrowed book exists
        while (currentStudent)
        {
            if (currentStudent->data.borrowedBooksHead) // Check if the student has borrowed any books
            {
                foundAnyBooks = true;
                cout << "==========================================" << endl;
                cout << "Student ID: " << currentStudent->data.studentID << endl;
                cout << "Name: " << currentStudent->data.name << endl;
                cout << "Borrowed Books:\n";

                BorrowedBookNode *currentBook = currentStudent->data.borrowedBooksHead;
                while (currentBook)
                {
                    Book *book = books.search(currentBook->bookID); // Assuming books is a hash table or linked list
                    if (book)
                    {
                        cout << "  - ID: " << book->bookID
                             << ", Title: " << book->title
                             << ", Author: " << book->author << endl;
                    }
                    currentBook = currentBook->next;
                }
            }
            currentStudent = currentStudent->next;
        }

        if (!foundAnyBooks)
        {
            cout << "No borrowed books found in the system.\n";
        }
    }

    bool login()
    {
        string username, password;
        string choice;
        int attempts = 3;
        string filename = "books.txt";
        loadBooks(filename);
        do
        {

            cout << "==========================================" << endl;
            cout << "         WELCOME TO THE LIBRARY           " << endl;
            cout << "          MANAGEMENT SYSTEM               " << endl;
            cout << "==========================================" << endl;
            cout << setw(20) << "1. Admin" << endl;
            cout << setw(22) << "2. Student" << endl;
            cout << setw(19) << "3. Exit" << endl;
            cout << "==========================================" << endl;
            cout << "Enter your option: ";
            while (true)
            {
                cin >> choice;
                if (validator.idValidation(choice))
                    ;
                break;
            }
            if (choice == "1")
            {
                system("cls");
                while (attempts-- > 0)
                {
                    cin.ignore();
                    while (true)
                    {
                        cout << "==========================================" << endl;
                        cout << "               Admin Login           " << endl;
                        cout << "==========================================" << endl;
                        cout << "Username : ";
                        getline(cin, username);
                        if (validator.stringValidation(username))
                        {
                            break;
                        }
                        cout << "Ensure! username is not be empty and has no numbers enter!" << endl;
                    }
                    cout << "Password : ";
                    cin >> password;
                    if (username == "admin" && password == "123")
                    {
                        cout << "Logging in";
                        for (int i = 0; i < 5; i++)
                        {
                            cout << ".";
                            Sleep(400);
                        }
                        cout << endl;
                        cout << "Admin login successful.\n";
                        Sleep(1000);
                        role = "admin";
                        return true;
                    }
                    cout << "Sorry to login as admin.Invalid credentials. Attempts remaining: " << attempts << "\n";
                }
            }
            else if (choice == "2")
            {
                system("cls");
                cout << "==========================================" << endl;
                cout << "          STUDENT LOGIN OPTIONS           " << endl;
                cout << "==========================================" << endl;
                cout << "1. Already registered in the library" << endl;
                cout << "2. New user" << endl;
                cout << "==========================================" << endl;
                cout << "Enter your option: ";
                int studentChoice;
                cin >> studentChoice;

                if (studentChoice == 1)
                {
                    role = "student";
                    return true;
                }
                else if (studentChoice == 2)
                {
                    cout << "You are a new user. Here are the available books:\n";
                    role = "New user";
                    return true;
                }
                else
                {
                    cout << "Invalid choice. Returning to main menu.\n";
                }
            }
            else if (choice == "3")
            {
                saveBooks(filename);
                cout << "Exiting,Thank u for using the system ." << endl;
                return false;
            }
            else
            {
                cout << "Invalid option.Please enter the correct option " << endl;
            }
        } while (true);
        return false;
    }

    void adminMenu()
    {
        int choice;
        string convert;
        while (true)
        {
            cout << "==========================================" << endl;
            cout << "                ADMIN MENU                " << endl;
            cout << "==========================================" << endl;
            cout << setw(25) << "1. Manage Books" << endl;
            cout << setw(28) << "2. Manage Students" << endl;
            cout << setw(28) << "3. Manage Requests" << endl;
            cout << setw(38) << "4. Manage Student Membership" << endl;
            cout << setw(30) << "5. Display All Books" << endl;
            cout << setw(39) << "6. Display All Borrowed Books" << endl;
            cout << setw(27) << "7. Find Something" << endl;
            cout << setw(35) << "0. Logout from Admin Menu" << endl;
            cout << "==========================================" << endl;
            cout << "Enter your Option: ";
            while (true)
            {
                cin >> convert;
                if (validator.idValidation(convert))
                {
                    choice = stoi(convert);
                    break;
                }
                cout << "Invalid Option. Please try again !" << endl;
            }
            switch (choice)
            {
            case 1:
            {
                int manageChoice;
                while (true)
                {
                    system("cls");
                    cout << "==========================================" << endl;
                    cout << "             MANAGE BOOKS MENU            " << endl;
                    cout << "==========================================" << endl;
                    cout << "1. Add Book" << endl;
                    cout << "2. Edit Book" << endl;
                    cout << "3. Delete Book" << endl;
                    cout << "0. Back to Admin Menu" << endl;
                    cout << "==========================================" << endl;
                    cout << "Enter your choice: ";
                    cin >> manageChoice;

                    switch (manageChoice)
                    {
                    case 1:
                    {
                        int bookID;
                        string bookIDstr, title, author;

                        while (true)
                        {
                            cout << "Enter Book ID: ";
                            cin >> bookIDstr;
                            if (validator.idValidation(bookIDstr))
                            {
                                bookID = stoi(bookIDstr);
                                break;
                            }
                            cout << "Invalid Book ID. Please enter a valid numeric ID.\n";
                        }

                        cin.ignore();
                        while (true)
                        {
                            cout << "Enter Book Title: ";
                            getline(cin, title);
                            if (validator.stringValidation(title))
                                break;
                            cout << "Invalid title. Title cannot be empty or whitespace only.\n";
                        }

                        while (true)
                        {
                            cout << "Enter Book Author: ";
                            getline(cin, author);
                            if (validator.stringValidation(author))
                                break;
                            cout << "Invalid author. Author name cannot be empty or whitespace only.\n";
                        }

                        addBook(bookID, title, author);
                        cout << "Press Enter to continue...";
                        cin.get(); // Pause before returning to menu
                        break;
                    }
                    case 2:
                    {
                        int bookID;
                        string bookIDstr;

                        while (true)
                        {
                            cout << "Enter Book ID to Edit: ";
                            cin >> bookIDstr;
                            if (validator.idValidation(bookIDstr))
                            {
                                bookID = stoi(bookIDstr);
                                break;
                            }
                            cout << "Invalid Book ID. Please enter a valid numeric ID.\n";
                        }

                        Book *book = books.search(bookID);
                        if (book)
                        {
                            string newTitle, newAuthor;
                            cin.ignore();

                            while (true)
                            {
                                cout << "Enter New Title (leave blank to keep current): ";
                                getline(cin, newTitle);
                                if (newTitle.empty() || validator.stringValidation(newTitle))
                                    break;
                                cout << "Invalid title. Title cannot be empty or whitespace only.\n";
                            }

                            while (true)
                            {
                                cout << "Enter New Author (leave blank to keep current): ";
                                getline(cin, newAuthor);
                                if (newAuthor.empty() || validator.stringValidation(newAuthor))
                                    break;
                                cout << "Invalid author. Author name cannot be empty or whitespace only.\n";
                            }

                            if (!newTitle.empty())
                                book->title = newTitle;
                            if (!newAuthor.empty())
                                book->author = newAuthor;

                            cout << "Book details updated successfully!\n";
                        }
                        else
                        {
                            cout << "Book not found!\n";
                        }
                        cout << "Press Enter to continue...";
                        cin.ignore();
                        cin.get();
                        break;
                    }
                    case 3:
                    {
                        int bookID;
                        string bookIDstr;

                        while (true)
                        {
                            cout << "Enter Book ID to Delete: ";
                            cin >> bookIDstr;
                            if (validator.idValidation(bookIDstr))
                            {
                                bookID = stoi(bookIDstr);
                                break;
                            }
                            cout << "Invalid Book ID. Please enter a valid numeric ID.\n";
                        }

                        if (books.search(bookID))
                        {
                            books.remove(bookID);
                            cout << "Book deleted successfully!\n";
                        }
                        else
                        {
                            cout << "Book not found!\n";
                        }
                        cout << "Press Enter to continue...";
                        cin.ignore();
                        cin.get();
                        break;
                    }
                    case 0: // Back to Admin Menu
                        cout << "Returning to Admin Menu..." << endl;
                        Sleep(1000); // Optional pause for clarity
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                        cout << "Press Enter to continue...";
                        cin.ignore();
                        cin.get();
                    }
                    break;
                }
                break;
            }
            case 2: // Manage Students
            {
                int manageChoice;
                while (true)
                {
                    system("cls");
                    cout << "==========================================" << endl;
                    cout << "             MANAGE STUDENTS MENU         " << endl;
                    cout << "==========================================" << endl;
                    cout << "1. Add Student" << endl;
                    cout << "2. Edit Student" << endl;
                    cout << "3. Delete Student" << endl;
                    cout << "4. Display All Students" << endl;
                    cout << "0. Back to Admin Menu" << endl;
                    cout << "==========================================" << endl;
                    cout << "Enter your choice: ";
                    cin >> manageChoice;

                    switch (manageChoice)
                    {
                    case 1: // Add Student
                    {
                        int studentID;
                        string studentIDstr, name;

                        while (true)
                        {
                            cout << "Enter Student ID: ";
                            cin >> studentIDstr;
                            if (validator.idValidation(studentIDstr))
                            {
                                studentID = stoi(studentIDstr);
                                break;
                            }
                            cout << "Invalid Student ID. Please enter a valid numeric ID.\n";
                        }

                        cin.ignore();
                        while (true)
                        {
                            cout << "Enter Student Name: ";
                            getline(cin, name);
                            if (validator.stringValidation(name))
                                break;
                            cout << "Invalid name. Name cannot be empty or numeric.\n";
                        }

                        students.insert(Student(studentID, name)); // Assuming students is of type StudentLinkedList
                        cout << "Student added successfully!\n";
                        cout << "Press Enter to continue...";
                        cin.get();
                        break;
                    }
                    case 2: // Edit Student
                    {
                        int studentID;
                        string studentIDstr, newName;

                        while (true)
                        {
                            cout << "Enter Student ID to Edit: ";
                            cin >> studentIDstr;
                            if (validator.idValidation(studentIDstr))
                            {
                                studentID = stoi(studentIDstr);
                                break;
                            }
                            cout << "Invalid Student ID. Please enter a valid numeric ID.\n";
                        }

                        Student *student = students.search(studentID);
                        if (student)
                        {
                            cin.ignore();
                            while (true)
                            {
                                cout << "Enter New Name (leave blank to keep current): ";
                                getline(cin, newName);
                                if (newName.empty() || validator.stringValidation(newName))
                                    break;
                                cout << "Invalid name. Name cannot be empty or numeric.\n";
                            }

                            if (!newName.empty())
                                student->name = newName;

                            cout << "Student details updated successfully!\n";
                        }
                        else
                        {
                            cout << "Student not found!\n";
                        }
                        cout << "Press Enter to continue...";
                        cin.ignore();
                        cin.get();
                        break;
                    }
                    case 3:
                    {
                        int studentID;
                        string studentIDstr;

                        while (true)
                        {
                            cout << "Enter Student ID to Delete: ";
                            cin >> studentIDstr;
                            if (validator.idValidation(studentIDstr))
                            {
                                studentID = stoi(studentIDstr);
                                break;
                            }
                            cout << "Invalid Student ID. Please enter a valid numeric ID.\n";
                        }

                        if (students.remove(studentID)) // Use the remove method
                        {
                            cout << "Student deleted successfully!\n";
                        }
                        else
                        {
                            cout << "Student not found!\n";
                        }
                        cout << "Press Enter to continue...";
                        cin.ignore();
                        cin.get();
                        break;
                    }
                    case 4:
                    {
                        students.displayStudents();
                        break;
                    }
                    case 0:
                        cout << "Returning to Admin Menu..." << endl;
                        Sleep(1000);
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                        cout << "Press Enter to continue...";
                        cin.ignore();
                        cin.get();
                    }
                    break;
                }
                break;
            }
            case 3:
            {
                // system("cls");
                requestPanel();
                break;
            }
            case 4:
            {
                manageMembership();
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            }
            case 5:
            {
                displayBooks();
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            }
            case 6:
            {
                displayAllBorrowedBooks();
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            }
            case 7:
            {
                int manageChoice;
                while (true)
                {
                    system("cls");
                    cout << "==========================================" << endl;
                    cout << "             MANAGE BOOKS MENU            " << endl;
                    cout << "==========================================" << endl;
                    cout << "1. Search Book" << endl;
                    cout << "2. Search Student" << endl;
                    cout << "0. Back to Admin Menu" << endl;
                    cout << "==========================================" << endl;
                    cout << "Enter your choice: ";
                    cin >> manageChoice;

                    switch (manageChoice)
                    {
                    case 1:
                    {
                        searchBook();
                        break;
                    }
                    case 2:
                    {
                        searchStudent();
                        break;
                    }
                    case 0: // Back to Admin Menu
                        cout << "Returning to Admin Menu..." << endl;
                        Sleep(1000); // Optional pause for clarity
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                        cout << "Press Enter to continue...";
                        cin.ignore();
                        cin.get();
                    }
                    break;
                }
                break;
            }
            case 0:
                cout << "Successfully logout!!" << endl;
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
            }
        }
    }
    void studentMenu()
    {
        int sID;
        cout << "Enter Your ID: ";
        cin >> sID;
        Student *student = students.search(sID);
        if (!student)
        {
            cout << "\nSorry You are not Registered Yet\nRequest or Contact Admin First\n\n";
            return;
        }
        cout << "Student login successful.\n";
        int choice;
        while (true)
        {
            cout << "==========================================" << endl;
            cout << "               STUDENT MENU               " << endl;
            cout << "==========================================" << endl;
            cout << setw(30) << "1. Display All Books" << endl;
            cout << setw(30) << "2. Check borrow Book" << endl;
            cout << setw(24) << "3. Borrow Book" << endl;
            cout << setw(24) << "4. Return Book" << endl;
            cout << setw(24) << "5. Search Book" << endl;
            cout << setw(30) << "0. Back to Main Menu" << endl;
            cout << "==========================================" << endl;
            cout << "Enter your Option: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                displayBooks();
                break;
            case 2:
            {
                int studentID;
                cout << "Enter Student ID: ";
                cin >> studentID;
                displayBorrowedBooks(studentID);
                break;
            }
            case 3:
            {
                int studentID, bookID;
                cout << "Enter Student ID: ";
                cin >> studentID;
                cout << "Enter Book ID: ";
                cin >> bookID;
                borrowBook(studentID, bookID);
                break;
            }
            case 4:
            {
                int studentID, bookID;
                cout << "Enter Student ID: ";
                cin >> studentID;
                cout << "Enter Book ID: ";
                cin >> bookID;
                returnBook(studentID, bookID);
                break;
            }
            case 5:
            {
                searchBook();
                break;
            }
            case 0:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
    void request()
    {

        int studentID;
        string studentIDstr, name;

        while (true)
        {
            cout << "Enter Your ID: ";
            cin >> studentIDstr;
            if (validator.idValidation(studentIDstr))
            {
                requestedID[requestcount] = stoi(studentIDstr);
                break;
            }
            cout << "Invalid Student ID. Please enter a valid numeric ID.\n";
        }

        cin.ignore();
        while (true)
        {
            cout << "Enter Your Name: ";
            getline(cin, name);
            if (validator.stringValidation(name))
            {
                requestedname[requestcount] = name;
                break;
            }
            cout << "Invalid name. Name cannot be empty or numeric.\n";
        }
        requestcount++;
        cout << "Request sended successfully!\n";
        cout << "Press Enter to continue...";
        cin.get();
    }
    void userMenu()
    {
        string choice;
        system("cls");
        while (true)
        {
            cout << "==========================================" << endl;
            cout << "                 USER MENU                " << endl;
            cout << "==========================================" << endl;
            cout << setw(30) << "1. Display All Books" << endl;
            cout << setw(37) << "2. Request for registration" << endl;
            cout << setw(30) << "0. Back to Main Menu" << endl;
            cout << "==========================================" << endl;
            cout << "Enter your Option: ";
            cin >> choice;

            if (!validator.idValidation(choice))
            {
                cout << "Invalid option. Please try again.\n";
                continue;
            }

            if (choice == "1")
            {
                displayBooks();
            }
            else if (choice == "2")
            {
                request();
                break;
            }
            else if (choice == "0")
            {
                cout << "Returning to main menu...\n";
                break;
            }
            else
            {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
    void run()
    {
        if (role == "admin")
        {
            adminMenu();
        }
        else if (role == "student")
        {
            studentMenu();
        }
        else if (role == "New user")
        {
            userMenu();
        }
    }
};

int main()
{
    LibrarySystem librarySystem;
    while (librarySystem.login())
    {
        librarySystem.run();
    }
    return 0;
}