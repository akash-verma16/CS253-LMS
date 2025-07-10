#include "LMS_Model.hpp"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std ;

BooksDBM::BooksDBM() {
    vector<string> data = readFromFile("./LMS_DB/books.csv", 9) ;
    vector<Books*> books = {} ;
    if( data.size() == 1 ) return ;

    for(int i = 0 ; i < data.size() ; i+=9){
        Books* book = new Books(data[i], data[i+1] , data[i+2], data[i+3], stoi(data[i+4]) , data[i+5]) ;
        book -> setUser(data[i+6]) ;
        book -> setBorrowDate(data[i+7]) ; 
        book -> setDueDate(data[i+8]) ; 
        books.push_back(book) ;
    }
    this -> books = books ;
}

//ISBN,Title,Author,Publisher,Year,Status,User,Borrow_Date,Due_Date

BooksDBM::~BooksDBM() {
    vector<string> data = {} ;
    for(int i = 0 ; i < books.size() ; i++ ) {
        data.push_back(books[i] -> getISBN()) ;
        data.push_back(books[i] -> gettitle()) ;
        data.push_back(books[i] -> getauthor());
        data.push_back(books[i] -> getpublisher()) ; 
        data.push_back(to_string(books[i] -> getyear()) ) ; 
        data.push_back(books[i] -> getStatus()) ; 
        data.push_back(books[i] -> getUser()) ; 
        data.push_back(books[i] -> showBorrowDate()) ; 
        data.push_back(books[i] -> showDueDate()) ;  
    }
    writeToFile("./LMS_DB/books.csv", data, 9) ;
}

void BooksDBM::UpdateBooks(Books* book) {
   
    for (int i = 0 ; i < books.size() ; i++ ) {
        if( books[i] -> getISBN() == book -> getISBN() ) {
            books[i] = book ;
            return ;
        }
    }
}

Books* BooksDBM::SelectBooks(string ISBN) {
    for(int i = 0 ; i < books.size() ; i++ ) {
        if( books[i] -> getISBN() == ISBN ) {
            return books[i] ;
        }
    }
    return NULL ;
}

vector<Books*> BooksDBM::ListBooks() {
    return books ;
}

void BooksDBM::AddBooks(Books* book) {
    Books* temp = SelectBooks(book -> getISBN()) ;
    if( temp != NULL ) {
        cout << "BookID/ISBN already exists!" << endl ;
        return ;
    }
    books.push_back(book) ;
    cout << "Book added successfully!" << endl ;
}

void BooksDBM::DeleteBooks(string ISBN) {
    for (int i = 0 ; i < books.size() ; i++ ) {
        if( books[i] -> getISBN() == ISBN ) {
            books.erase(books.begin() + i) ;
            cout << "Book deleted successfully!" << endl ;
            return ;
        }
    }
    cout << "BookId/ISBN does not exist!" << endl ;
}

void BooksDBM::DeleteBooksUserID(string userid) {
    for (int i = 0 ; i < books.size() ; i++ ) {
        if( books[i] -> getUser() == userid ) {
            books[i] -> setUser("") ;
            books[i] -> setBorrowDate("") ;
            books[i] -> setDueDate("") ;
        }
    }
}

//Students : UserID,Password,Name,Dues,Number of Overdue Books,Number of Books Borrowed

StudentDBM::StudentDBM() {
    vector<string> data = readFromFile("./LMS_DB/students.csv", 6) ;
    if( data.size() == 1 ) return ;
    for(int i = 0 ; i < data.size() ; i+=6){
        Student* student = new Student(data[i], data[i+1], data[i+2], stoi(data[i+3]), stoi(data[i+4]),stoi(data[i+5])) ;
        students.push_back(student) ;
    }
    this -> students = students ;
}

StudentDBM::~StudentDBM() {
    vector<string> data ;
    for( int i = 0 ; i < students.size() ; i++ ) {
        data.push_back(students[i] -> getUserId()) ;
        data.push_back(students[i] -> getPassword()) ;
        data.push_back(students[i] -> getName()) ;
        data.push_back(to_string(students[i] -> getDues())) ;
        data.push_back(to_string(students[i] -> getNumberOfOverDueBooks())) ;
        data.push_back(to_string(students[i] -> getNumberOfBooksBorrowed())) ;
    }
    writeToFile("./LMS_DB/students.csv", data , 6) ;
}

 void StudentDBM::UpdateStudent(Student* student) {

    for(int i = 0 ; i < students.size() ; i++ ){
        if( students[i] -> getUserId() == student -> getUserId() ) {
            students[i] = student ;
            return ;
        }
    }
}

Student* StudentDBM::SelectStudent(string userid) {
    for(int i = 0 ; i < students.size() ; i++ ){
        if( students[i] -> getUserId() == userid ) {
            return students[i] ;
        }
    }
    return NULL ;
}

vector<Student*> StudentDBM::ListStudents() {
    return students ;
}

void StudentDBM::AddStudent(Student* student) {
    Student* check = SelectStudent(student->getUserId()) ;
    if( check != NULL ) {
        cout << "UserID already exists!" << endl ;
        return ;
    }
    students.push_back(student) ;
    cout << "Student added successfully!" << endl ;
}

void StudentDBM::DeleteStudent(string userid) {
    for(int i = 0 ; i < students.size() ; i++ ){
        if( (students[i] -> getUserId()) == userid ) {
            students.erase(students.begin() + i) ;
            cout << "Student deleted successfully!" << endl ;
            return ;
        }
    }
    cout << "UserID does not exist!" << endl ;
}

//UserID,Password,Name,Number of Overdue Books,Number of Books Borrowed

FacultyDBM::FacultyDBM() {
    vector<string> data = readFromFile("./LMS_DB/faculty.csv", 5) ;
    vector<Faculty*> facultys ;
    if ( data.size() == 1 ) return ;
    for(int i = 0 ; i < data.size() ; i+=5){
        Faculty* faculty = new Faculty(data[i], data[i+1], data[i+2], stoi(data[i+3]), stoi(data[i+4])) ;
        facultys.push_back(faculty) ;
    }
    this -> facultys = facultys ;
}

FacultyDBM::~FacultyDBM() {
    vector<string> data ;
    for( int i = 0 ; i < facultys.size() ; i++ ) {
        data.push_back(facultys[i] -> getUserId()) ;
        data.push_back(facultys[i] -> getPassword()) ;
        data.push_back(facultys[i] -> getName()) ;
        data.push_back(to_string(facultys[i] -> getNumberOfOverDueBooks())) ;
        data.push_back(to_string(facultys[i] -> getNumberOfBooksBorrowed())) ;
    }
    writeToFile("./LMS_DB/faculty.csv", data, 5) ;
}



void FacultyDBM::UpdateFaculty(Faculty* faculty){
    for( int i = 0 ; i < facultys.size() ; i++ ) {
        if( facultys[i] -> getUserId() == faculty -> getUserId() ) {
            facultys[i] = faculty ;
            return ;
        }
    }
}

Faculty* FacultyDBM::SelectFaculty(string userid) {
    for(int i = 0 ; i < facultys.size() ; i++){
        if( facultys[i] -> getUserId() == userid ) {
            return facultys[i] ;
        }
    }
    return NULL ;
}

vector<Faculty*> FacultyDBM::ListFacultys() {
    return facultys ;
}

void FacultyDBM::AddFaculty(Faculty* faculty) {
    Faculty* check = SelectFaculty(faculty->getUserId()) ;
    if( check != NULL ) {
        cout << "UserID already exists!" << endl ;
        return ;
    }
    facultys.push_back(faculty) ;
    cout << "Faculty Added!" << endl ;
}

void FacultyDBM::DeleteFaculty(string userid) {
    for( int i = 0 ; i < facultys.size() ; i++ ) {
        if( facultys[i] -> getUserId() == userid ) {
            facultys.erase(facultys.begin() + i) ;
            cout << "Faculty Deleted!" << endl ;
            return ;
        }
    }
    cout << "Faculty not found!" << endl ;
}

//Librarian1,password1,Harry,

LibrarianDBM::LibrarianDBM() {
    vector<string> data = readFromFile("./LMS_DB/Librarian.csv", 3) ;
    vector<Librarian*> librarians = {} ;
    if( data.size() == 1 ) return ;
    for(int i = 0 ; i < data.size() ; i+=3){
        Librarian* librarian = new Librarian(data[i], data[i+1], data[i+2]) ;
        librarians.push_back(librarian) ;
    }
    this -> librarians  = librarians ;
}

LibrarianDBM::~LibrarianDBM() {
    vector<string> data = {} ;
    for(int i = 0 ; i < librarians.size() ; i++ ) {
        data.push_back(librarians[i] -> getUserId()) ;
        data.push_back(librarians[i] -> getPassword()) ;
        data.push_back(librarians[i] -> getName()) ;
    }
    writeToFile("./LMS_DB/Librarian.csv", data, 3) ;
}

void LibrarianDBM::UpdateLibrarian(Librarian* librarian) {
    for (int i = 0 ; i < librarians.size() ; i++ ) {
        if( librarians[i] -> getUserId() == librarian -> getUserId() ) {
            librarians[i] = librarian ;
            return ;
        }
    }
}

Librarian* LibrarianDBM::SelectLibrarian(string userid) {
    for(int i = 0 ; i < librarians.size() ; i++ ) {
        if( librarians[i] -> getUserId() == userid ) {
            return librarians[i] ;
        }
    }
    return NULL ;
}

vector<Librarian*> LibrarianDBM::ListLibrarians() {
    return librarians ;
}

void LibrarianDBM::AddLibrarian(Librarian* librarian) {
    Librarian* temp = SelectLibrarian(librarian -> getUserId()) ;
    if( temp != NULL ) {
        cout << "UserID already exists!" << endl ;
        return ;
    }
    librarians.push_back(librarian) ;
    cout << "Manager Added!" << endl ;
}

void LibrarianDBM::DeleteLibrarian(string userid) {
    for(int i = 0 ; i < librarians.size() ; i++ ) {
        if( librarians[i] -> getUserId() == userid ) {
            librarians.erase(librarians.begin() + i) ;
            cout << "Manager Deleted!" << endl ;
            return ;
        }
    }
    cout << "UserID does not exist!" << endl ;
}

//UserID,HistoryType,ISBN,BorrowDate,DueDate,ReturnDate

AccountDBM::AccountDBM() {
    vector<string> data = readFromFile("./LMS_DB/account.csv", 6) ;
    vector<Account*> accounts = {} ;
    if( data.size() == 1 ) return ;
    for(int i = 0 ; i < data.size() ; i+=6){
        Account* account = new Account(data[i], data[i+1], data[i+2], data[i+3], data[i+4], data[i+5]) ;
        accounts.push_back(account) ;
    }
    this -> accounts = accounts ;
}

AccountDBM::~AccountDBM() {
    vector<string> data = {} ;
    for(int i = 0 ; i < accounts.size() ; i++ ) {
        data.push_back(accounts[i] -> getUserID()) ;
        data.push_back(accounts[i] -> getHistoryType()) ;
        data.push_back(accounts[i] -> getISBN()) ;
        data.push_back(accounts[i] -> getBorrowDate()) ;
        data.push_back(accounts[i] -> getDueDate()) ;
        data.push_back(accounts[i] -> getReturnDate()) ;
    }
    writeToFile("./LMS_DB/account.csv", data, 6) ;
}


void AccountDBM::UpdateAccount(Account* account) {
    for (int i = 0 ; i < accounts.size() ; i++ ) {
        if(accounts[i]->getUserID() == account->getUserID() && 
           accounts[i]->getISBN() == account->getISBN() &&
           accounts[i]->getHistoryType() == "CUR") { 
            accounts[i]->setReturnDate(account->getReturnDate());
            accounts[i]->setHistoryType(account->getHistoryType());
            return ;
        }
    }
}


Account* AccountDBM::SelectAccount(string userid , string ISBN , string historytype) {
    for(int i = 0 ; i < accounts.size() ; i++ ) {
        if( accounts[i] -> getUserID() == userid  && accounts[i] -> getISBN() == ISBN && accounts[i] -> getHistoryType() == historytype ) {   
            return accounts[i] ;
        }
    }
    return NULL ;
}

vector<Account*> AccountDBM::ListAccounts() {
    return accounts ;
}

void AccountDBM::AddAccount(Account* account) {
    Account* temp = SelectAccount(account -> getUserID() , account -> getISBN() , account -> getHistoryType()) ;
    if( temp != NULL ) {
        cout << "UserID already exists!" << endl ;
        return ;
    }
    accounts.push_back(account) ;
    cout << "Account Added!" << endl ;
}

void AccountDBM::DeleteAccount(string userid) {
    int flag = 0 ; 
    for(int i = 0 ; i < accounts.size() ; i++ ) {
        cout << accounts[i] -> getUserID() << endl ;
        if( accounts[i] -> getUserID() == userid ) {
            accounts.erase(accounts.begin() + i) ;
            i--;
        }
    }
    cout << "Account Deleted!" << endl ;

}



