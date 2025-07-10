#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class User {
    protected:
        std::string userid;
        std::string password;
        std::string name;
    public:
        void setUserId(std::string userid);
        void setPassword(std::string password);
        void setName(std::string name);
        std::string getUserId();
        std::string getPassword();
        std::string getName();
};



class Books {
    private:
        std::string ISBN;
        std::string title;
        std::string author;
        std::string publisher;
        int year;
        std::string status;
        std::string user;
        std::string borrow_date;
        std::string due_date;
        int fine = 10;

    public:
        Books(std::string ISBN, std::string title, std::string author, std::string publisher, int year, std::string status, std::string user, std::string borrow_date, std::string due_date); //
        Books();  //
        Books(std::string ISBN, std::string title , std::string author, std::string publisher, int year ,std::string status ) ; // 
        void setISBN(std::string ISBN); //
        void settitle(std::string title); //
        void setauthor(std::string author); //
        void setpublisher(std::string publisher); //
        void setyear(int year); //
        void setstatus(std::string status); //
        void setBorrowDate(std::string due_date); //
        void setDueDate(std::string due_date); //
        void setUser(std::string); //
        void setfine(int fineperday); //
        bool isAvailable();  //
        int CalculateFine(int days);  //
        int CalculateDues(int days); //
        std::string getISBN(); //
        std::string gettitle(); //
        std::string getauthor(); //
        std::string getpublisher(); //
        int getyear(); //
        std::string getStatus(); //
        std::string showBorrowDate();  //
        std::string showDueDate();  //
        std::string getUser();  //
        int getfine();  //
         bool BorrowBooks(std::string userid, int user_type ,std::string ISBN);  //
         void DisplayBorrowedBooks(std::string userid);  // 
        // bool DisplayAvailableBooks();  //
        // void DisplayAllBorrowedBooks();  //
};


class Library{
    public:
        void DisplayAllBooks();  //
        bool DisplayAvailableBooks();  //
        void DisplayAllBorrowedBooks();  //
        void DisplaAllreservedbooks() ; 
        void DisplayAllStudents();  //
        void DisplayAllFacultys();  //
        void DisplayAllLibrarians();  //     
       

} ; 

class Account {
    protected:
        std:: string userid ; 
        std:: string history_type ; 
        std:: string ISBN ; 
        std:: string borrow_date ; 
        std:: string due_date ; 
        std:: string return_date ; 

    public:
        Account(std::string userid, std::string history_type, std::string ISBN, std::string borrow_date, std::string due_date, std::string return_date); //
        Account(); 
        void setUserID(std::string userid); 
        void setHistoryType(std::string history_type); 
        void setISBN(std::string ISBN); 
        void setBorrowDate(std::string borrow_date); 
        void setDueDate(std::string due_date); 
        void setReturnDate(std::string return_date); 
        std::string getUserID(); 
        std::string getHistoryType(); 
        std::string getISBN(); 
        std::string getBorrowDate(); 
        std::string getDueDate(); 
        std::string getReturnDate();
        void DisplayCurHistory(std::string userid);
         void DisplayPrevHistory(std::string userid);
};

class Student : public User {
    private:
        int dues;
        int num_overdue_books;
        int num_Books_Borrowed;
    public:
        bool authenticate(std::string, std::string); //
        Student(); //
        Student(std::string userid, std::string password, std::string name); //
        Student(std::string userid, std::string password, std::string name, int dues, int num_overdue_books, int num_Books_Borrowed); //        
        int getDues(); //
        int getNumberOfOverDueBooks(); //
        int getNumberOfBooksBorrowed(); //
        void setDues(int dues); //
        void setNumberOfOverDueBooks(int num_overdue_books);
        void setNumberOfBooksBorrowed(int num_Books_Borrowed); //
        int MaxBooks(); //
        std::string StudentLogin(); //
        void ReturnRequest(); //
        void clearDues(); //
};

class Faculty : public User {
    private:
        int num_overdue_books;
        int num_Books_Borrowed;
    public:
        Faculty(std::string userid, std::string password, std::string name, int num_overdue_books, int num_Books_Borrowed); //
        Faculty(std::string userid, std::string password, std::string name);  // 
        Faculty(); // 
        int getNumberOfOverDueBooks();  //
        int getNumberOfBooksBorrowed();  //
        bool authenticate(std::string, std::string); //
        void setNumberOfOverDueBooks(int num_overdue_books);  // 
        void setNumberOfBooksBorrowed(int num_Books_Borrowed); //
        int MaxBooks();  //
        std::string FacultyLogin();  //
        void ReturnRequest();  // 
};

class Librarian : public User {
    public:
        bool authenticate(std::string, std::string);  //
        Librarian(std::string userid, std::string password, std::string name);   //
        Librarian();   //
        std::string LibrarianLogin();  //
        void AddUser(int user_type);   //
        void DeleteUser(int user_type);  //
        void UpdateUser(int user_type);  //
        void AddBooks();  //
        void DeleteBooks();  // 
        void UpdateBooks();  // 
};

class StudentDBM{
    private:
        std::vector<Student*> students;
    public:
        StudentDBM();  // 
        void AddStudent(Student* student);  // 
        void DeleteStudent(std::string userid);  // 
        void UpdateStudent(Student* student);  // 
        Student* SelectStudent(std::string userid);  // 
        std::vector<Student*> ListStudents();  // 
        ~StudentDBM(); // 
};

class BooksDBM{
    private:
        std::vector<Books*> books;
    public:
        BooksDBM();  //
        void AddBooks(Books* books);  // 
        void DeleteBooks(std::string ISBN);  // 
        void UpdateBooks(Books* books);  // 
        Books* SelectBooks(std::string ISBN);  // 
        std::vector<Books*> ListBooks();  // 
        void DeleteBooksUserID(std::string userid);  // 
        ~BooksDBM();  // 
};


class LibrarianDBM{
    private:
        std::vector<Librarian*> librarians;
    public:
        LibrarianDBM();  // 
        void AddLibrarian(Librarian* Librarian); // 
        void DeleteLibrarian(std::string userid); // 
        void UpdateLibrarian(Librarian* Librarian); // 
        Librarian* SelectLibrarian(std::string userid); // 
        std::vector<Librarian*> ListLibrarians(); // 
        ~LibrarianDBM(); // 
};

class FacultyDBM{
    private:
        std::vector<Faculty*> facultys; 
    public:
        FacultyDBM(); // 
        void AddFaculty(Faculty* faculty); // 
        void DeleteFaculty(std::string userid);  // 
        void UpdateFaculty(Faculty* faculty);  // 
        Faculty* SelectFaculty(std::string userid);  // 
        std::vector<Faculty*> ListFacultys();  // 
        ~FacultyDBM();  //  
};
class AccountDBM{
    private:
        std::vector<Account*> accounts;
    public:
        AccountDBM();  // 
        void AddAccount(Account* account);  // 
        void DeleteAccount(std::string userid);  // 
        void UpdateAccount(Account* account);  // 
        Account* SelectAccount(std::string userid , std:: string ISBN , std:: string history_type);  // 
        std::vector<Account*> ListAccounts();  // 
        ~AccountDBM();  // 
};

struct Date { int d, m, y; };

int countLeapYears(Date d);
int DaysDiff(std::string, std::string);
bool confirm();

std::vector<std::string> readFromFile(std::string filename, int columns);
void writeToFile(std::string filename, std::vector<std::string> data, int columns);

bool isNumber(std::string s);
bool isDecimal(std::string s);

