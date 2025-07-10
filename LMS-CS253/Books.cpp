#include "LMS_Model.hpp"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std ;


int Books::CalculateDues(int days) {
    int price = 0 ;
    //price = days*(this->getRent()) ;
    price = days*(this->fine) ;
    return price ;
}

int Books::CalculateFine(int days) {
    int fine = 0 ;
    fine  = days*(this->fine) ;
    return fine ;
}

Books::Books(){
    ISBN  = "" ;
    title = "" ; 
    author = "" ;
    publisher = "" ;
    year =  0 ; 
    status = "" ; 
    user = "" ; 
    borrow_date = "" ; 
    due_date = "" ; 
}

Books::Books(string ISBN, string title , string author, string publisher, int year , string status , string user , string borrow_date , string due_date) {
    this->ISBN = ISBN;
    this->title =  title ; 
    this->author = author;
    this->publisher = publisher;
    this->year = year;
    this->status = status;
    this->user = user;
    this->borrow_date = borrow_date ; 
    this->due_date = due_date ; 
}

Books::Books(string ISBN, string title , string author, string publisher, int year , string status ) {
    this->ISBN = ISBN;
    this->title =  title ; 
    this->author = author;
    this->publisher = publisher;
    this->year = year;
    this->status = status;
    this->user = "" ; 
    this->borrow_date = "" ; 
    this->due_date = "" ; 
}

void Books::DisplayBorrowedBooks(string userid) {
    int flag = 0 ;
    vector<Books*> BooksList = BooksDBM().ListBooks() ;
    cout << "-----------------------------------" << endl ;
    cout << "          Books Borrowed           " << endl ;
    cout << "-----------------------------------" << endl ;
    cout <<  endl ;
    for( int i = 0 ; i < BooksList.size() ; i++ ) {
        if( BooksList[i] -> getUser() == userid ) {
            flag = 1 ;
            cout << "ISBN: " << BooksList[i] -> getISBN() << endl ;
            cout << "Title: " << BooksList[i] -> gettitle() << endl ;
            cout << "Borrow Date : " << BooksList[i]->showBorrowDate() << endl;
            cout << "Due Date : " << BooksList[i] -> showDueDate() << endl;
            cout << endl ;            
        }
    }
    if( flag == 0 ) {
        cout << "No Books Borrowed!" << endl ;
        cout << endl ;
    }
    cout << "-----------------------------------" << endl ;
}


void Books::setDueDate(string due_date) {
    this -> due_date = due_date ;
}

void Books::setBorrowDate(string borrow_date) {
    this -> borrow_date = borrow_date ;
}

void Books::setUser(string user) {
    this -> user = user ;
}

void Books::setyear(int year) {
    this -> year = year ;
}

void Books::setstatus( string status) {
    this -> status = status ;
}

void Books::setauthor(string author) {
    this -> author = author ;
}

void Books::setISBN(string ISBN) {
    this -> ISBN = ISBN ;
}


void Books::settitle(string title) {
    this -> title = title ; 
}

void Books::setpublisher(string publisher) {
    this->publisher = publisher  ;
}


string Books::getUser() {
    return user ;
}

string Books::getISBN() {
    return ISBN ;
}

string Books::getauthor() {
    return author ;
}

string Books::gettitle() {
    return title ;
}

string Books::getpublisher() {
    return publisher ;
}

void Books::setfine(int fine) {
    this -> fine = fine  ;
}

int  Books::getfine() {
    return fine ;
}

int Books::getyear() {
    return year ;
}

string Books::getStatus() {
    return status ;
 
}

string Books::showDueDate() {
    return due_date ;
}

string Books::showBorrowDate() {
    return borrow_date ;
}

bool Books::isAvailable() {
    if( user == "" ) {
        return true ;
    }
    return false ;
}



bool Books::BorrowBooks(string userid, int user_type, string ISBN) {
    time_t now = time(0) ; 
    tm *ltm = localtime(&now);
    string borrow_date = to_string(ltm->tm_mday) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(1900 + ltm->tm_year) ;
     
    
    int days  ; 
    if(user_type == 0) days = 15 ; 
    else if(user_type == 1) days = 30 ; 
    time_t now2 = time(0) + days*24*60*60 ;
    tm *ltm2 = localtime(&now2);
    string due_date = to_string(ltm2->tm_mday) + "-" + to_string(1 + ltm2->tm_mon) + "-" + to_string(1900 + ltm2->tm_year) ;

    cout << "-----------------------------------" << endl ;
    cout << "[NOTE] Due date will before the midnight of " << due_date << endl ;
    cout << "-----------------------------------" << endl ;
    if(!confirm()) return false ;    
    this-> borrow_date = borrow_date ;
    this -> due_date = due_date ;
    this -> user = userid ;
    this -> status = "Borrowed"    ;
    BooksDBM().UpdateBooks(this) ;
    
    string str = "CUR" ; 
    string return_date = "" ;
    Account* acc = new Account(userid, str, ISBN, borrow_date, due_date, return_date) ;
    AccountDBM().AddAccount(acc) ;
    

    if( user_type == 0 ) {
        Student* student = StudentDBM().SelectStudent(userid) ;
        student -> setNumberOfBooksBorrowed(student -> getNumberOfBooksBorrowed() + 1) ;
        StudentDBM().UpdateStudent(student) ;
    } else if( user_type == 1 ) {
        Faculty* faculty = FacultyDBM().SelectFaculty(userid) ;
        faculty -> setNumberOfBooksBorrowed(faculty -> getNumberOfBooksBorrowed() + 1) ;
        FacultyDBM().UpdateFaculty(faculty) ;
    }
    cout << "Book Borrowed successfully!" << endl ;
    cout << "May you have a pleasant day.. :) " << endl ;
    return true ;
}


