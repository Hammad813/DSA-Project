#include <iostream>
#include <string>
#include<windows.h>
#include<iomanip>
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

class Book {
public:
    int bookID;
    string title;
    string author;
    bool isAvailable;

    Book() : bookID(0), title(""), author(""), isAvailable(true) {} 
    Book(int id, string t, string a) : bookID(id), title(t), author(a), isAvailable(true) {}
};

class BorrowedBookNode {
public:
    int bookID;
    BorrowedBookNode* next;

    BorrowedBookNode(int id) : bookID(id), next(nullptr) {}
};

class Student {
public:
    int studentID;
    string name;
    bool hasMembership;
    BorrowedBookNode* borrowedBooksHead;

    Student() : studentID(0), name(""), hasMembership(false), borrowedBooksHead(nullptr) {}

    Student(int id, string n, bool membership = false) : studentID(id), name(n), hasMembership(membership), borrowedBooksHead(nullptr) {}

    void borrowBook(int bookID) {
        if (hasMembership) {
            BorrowedBookNode* newNode = new BorrowedBookNode(bookID);
            newNode->next = borrowedBooksHead;
            borrowedBooksHead = newNode;
        } else {
            cout << "Student does not have an active membership and cannot borrow books.\n";
        }
    }

    void returnBook(int bookID) {
        BorrowedBookNode* current = borrowedBooksHead;
        BorrowedBookNode* previous = nullptr;

        while (current) {
            if (current->bookID == bookID) {
                if (previous) {
                    previous->next = current->next;
                } else {
                    borrowedBooksHead = current->next;
                }
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }
    }

    bool hasBorrowedBook(int bookID) {
        BorrowedBookNode* current = borrowedBooksHead;
        while (current) {
            if (current->bookID == bookID) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

class BookNode {
public:
    Book data;
    BookNode* next;

    BookNode(Book d) : data(d), next(nullptr) {}
};

class StudentNode {
public:
    Student data;
    StudentNode* next;

    StudentNode(Student d) : data(d), next(nullptr) {}
};

class BookLinkedList {
public:
    BookNode* head;

    BookLinkedList() : head(nullptr) {}

    void insert(Book data) {
        BookNode* newNode = new BookNode(data);
        newNode->next = head;
        head = newNode;
    }

    Book* search(int bookID) {
        BookNode* current = head;
        while (current) {
            if (current->data.bookID == bookID) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }

    bool remove(int bookID) {
        BookNode* current = head;
        BookNode* previous = nullptr;

        while (current) {
            if (current->data.bookID == bookID) {
                if (previous) {
                    previous->next = current->next;
                } else {
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

class StudentLinkedList {
public:
    StudentNode* head;

    StudentLinkedList() : head(nullptr) {}

    void insert(Student data) {
        StudentNode* newNode = new StudentNode(data);
        newNode->next = head;
        head = newNode;
    }

    Student* search(int studentID) {
        StudentNode* current = head;
        while (current) {
            if (current->data.studentID == studentID) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }

    bool remove(int studentID) {
        StudentNode* current = head;
        StudentNode* previous = nullptr;

        while (current) {
            if (current->data.studentID == studentID) {
                if (previous) {
                    previous->next = current->next;
                } else {
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

class BookHashTable {
private:
    int size;
    BookLinkedList* table;

    int hashFunction(int key) {
        return key % size;
    }

public:
    BookHashTable(int s = 100) : size(s), table(new BookLinkedList[s]) {}

    void insert(int key, Book data) {
        int index = hashFunction(key);
        table[index].insert(data);
    }

    Book* search(int key) {
        int index = hashFunction(key);
        return table[index].search(key);
    }

    bool remove(int key) {
        int index = hashFunction(key);
        return table[index].remove(key);
    }

    void displayBooks() {
        cout << "Books in the Library:\n";
        for (int i = 0; i < size; ++i) {
            BookNode* current = table[i].head;
            while (current) {
                cout << "ID: " << current->data.bookID
                     << ", Title: " << current->data.title
                     << ", Author: " << current->data.author
                     << ", Available: " << (current->data.isAvailable ? "Yes" : "No") << endl;
                current = current->next;
            }
        }
    }

    ~BookHashTable() {
        delete[] table;
    }
};

class LibrarySystem {
private:
    BookHashTable books;
    StudentLinkedList students;
    Validations validator;
    string role;

public:
    LibrarySystem() {}

    void addBook(int bookID, string title, string author) {
        Book book(bookID, title, author);
        books.insert(bookID, book);
        cout << "Book '" << title << "' added to the library.\n";
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

        Student *student = students.search(studentID); // Assuming `students` is a collection supporting `search`
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

    void borrowBook(int studentID, int bookID) {
        Student* student = students.search(studentID);
        Book* book = books.search(bookID);

        if (student && book && book->isAvailable) {
            if (student->hasMembership) {
                book->isAvailable = false;
                student->borrowBook(bookID);
                cout << "Book '" << book->title << "' borrowed by '" << student->name << "'.\n";
            } else {
                cout << "Student does not have an active membership and cannot borrow books.\n";
            }
        } else {
            cout << "Cannot borrow book. It may not be available or the student is not registered.\n";
        }
    }

    void returnBook(int studentID, int bookID) {
        Student* student = students.search(studentID);
        Book* book = books.search(bookID);

        if (student && book && student->hasBorrowedBook(bookID)) {
            book->isAvailable = true;
            student->returnBook(bookID);
            cout << "Book '" << book->title << "' returned by '" << student->name << "'.\n";
        } else {
            cout << "The book was not borrowed by the student.\n";
        }
    }

    void displayBooks() {
        books.displayBooks();
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
                    while(true){
                    cout << "Password : ";
                    cin >> password;
                    if(validator.idValidation(password)){
                        break;
                    }
                    cout<<"Ensure! pasword is not be empty and has no char(alpha) enter!"<<endl;
                    }
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
                    cout << "Student login successful.\n";
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
            system("cls");
            cout << "==========================================" << endl;
            cout << "                ADMIN MENU                " << endl;
            cout << "==========================================" << endl;
            cout << setw(25) << "1. Manage Books" << endl;
            cout << setw(28) << "2. Manage Students" << endl;
            cout << setw(38) << "3. Manage Student Membership" << endl;
            cout << setw(30) << "4. Display All Books" << endl;
            cout << setw(39) << "5. Display All Borrowed Books" << endl;
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
                string convert1;
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
                    while (true)
                    {
                        cin >> convert1;
                        if (validator.idValidation(convert1))
                        {
                            manageChoice = stoi(convert1);
                            break;
                        }
                        cout << "Invalid Option. Please try again !" << endl;
                    }

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
                        cout << "Book added successfully!\n";
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
                string convert1;
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
                    cout << "0. Back to Admin Menu" << endl;
                    cout << "==========================================" << endl;
                    cout << "Enter your choice: ";
                    while (true)
                    {
                        cin >> convert1;
                        if (validator.idValidation(convert1))
                        {
                            manageChoice = stoi(convert1);
                            break;
                        }
                        cout << "Invalid Option. Please try again !" << endl;
                    }

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

                        students.insert(Student(studentID, name)); // Assuming `students` is of type `StudentLinkedList`
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
                manageMembership();
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            }
            case 4:
                displayBooks();
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            case 5:
               displayAllBorrowedBooks();
                cout << "Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
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
            }
            case 3:
            {
            }
            case 4:
            {
            }
            case 0:
                return;
            default:
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
          // userMenu();
        }
    }
};

int main() {
    LibrarySystem librarySystem;
    while (librarySystem.login())
    {
        librarySystem.run();
    }
    return 0;
}