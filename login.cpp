#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;


class Book {
public:
    int bookID;
    string title;
    string author;
    bool isAvailable;

    Book(int id = 0, string t = "", string a = "")
        : bookID(id), title(t), author(a), isAvailable(true) {}
};


class Student {
public:
    int studentID;
    string name;
    bool hasMembership;
    struct BorrowedBookNode {
        int bookID;
        BorrowedBookNode* next;

        BorrowedBookNode(int id) : bookID(id), next(nullptr) {}
    } *borrowedBooksHead;

    Student(int id = 0, string n = "", bool membership = false)
        : studentID(id), name(n), hasMembership(membership), borrowedBooksHead(nullptr) {}

    void borrowBook(int bookID) {
        BorrowedBookNode* newNode = new BorrowedBookNode(bookID);
        newNode->next = borrowedBooksHead;
        borrowedBooksHead = newNode;
    }

    void returnBook(int bookID) {
        BorrowedBookNode** current = &borrowedBooksHead;
        while (*current) {
            if ((*current)->bookID == bookID) {
                BorrowedBookNode* toDelete = *current;
                *current = (*current)->next;
                delete toDelete;
                return;
            }
            current = &((*current)->next);
        }
    }

    bool hasBorrowedBook(int bookID) {
        BorrowedBookNode* current = borrowedBooksHead;
        while (current) {
            if (current->bookID == bookID)
                return true;
            current = current->next;
        }
        return false;
    }
};

// Define a simple hash table for Books
class BookHashTable {
public:
    struct BookNode {
        Book data;
        BookNode* next;

        BookNode(Book b) : data(b), next(nullptr) {}
    };

    struct Bucket {
        BookNode* head;

        Bucket() : head(nullptr) {}
    };

    Bucket* table;
    int size;

    BookHashTable(int s) : size(s) {
        table = new Bucket[size];
    }

    ~BookHashTable() {
        for (int i = 0; i < size; ++i) {
            BookNode* current = table[i].head;
            while (current) {
                BookNode* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
        delete[] table;
    }

    int hash(int key) { return key % size; }

    void insert(int key, Book book) {
        int index = hash(key);
        BookNode* newNode = new BookNode(book);
        newNode->next = table[index].head;
        table[index].head = newNode;
    }

    Book* search(int key) {
        int index = hash(key);
        BookNode* current = table[index].head;
        while (current) {
            if (current->data.bookID == key)
                return &current->data;
            current = current->next;
        }
        return nullptr;
    }

    void displayBooks() {
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
};

// Define a simple hash table for Students
class StudentHashTable {
public:
    struct StudentNode {
        Student data;
        StudentNode* next;

        StudentNode(Student s) : data(s), next(nullptr) {}
    };

    struct Bucket {
        StudentNode* head;

        Bucket() : head(nullptr) {}
    };

    Bucket* table;
    int size;

    StudentHashTable(int s) : size(s) {
        table = new Bucket[size];
    }

    ~StudentHashTable() {
        for (int i = 0; i < size; ++i) {
            StudentNode* current = table[i].head;
            while (current) {
                StudentNode* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
        delete[] table;
    }

    int hash(int key) { return key % size; }

    void insert(int key, Student student) {
        int index = hash(key);
        StudentNode* newNode = new StudentNode(student);
        newNode->next = table[index].head;
        table[index].head = newNode;
    }

    Student* search(int key) {
        int index = hash(key);
        StudentNode* current = table[index].head;
        while (current) {
            if (current->data.studentID == key)
                return &current->data;
            current = current->next;
        }
        return nullptr;
    }
};


