#include "LMS_Model.hpp"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std ;

Faculty::Faculty( string userid,  string password,  string name, int num_overdue_books,  int num_Books_Borrowed) {
    this -> userid = userid ;
    this -> password = password ;
    this -> name = name ;
    this -> num_overdue_books = num_overdue_books ;
    //this -> dues = dues ;
    this -> num_Books_Borrowed = num_Books_Borrowed ;
}

Faculty::Faculty( string userid,  string password,  string name) {
    this -> userid = userid ;
    this -> password = password ;
    this -> name = name ;
    this -> num_overdue_books = 0 ;
    this -> num_Books_Borrowed = 0 ;
}

Faculty::Faculty() {
    this -> userid = "" ;
    this -> password = "" ;
    this -> name = "" ;
    this -> num_Books_Borrowed = 0 ;
    this -> num_overdue_books = 0 ;
}


int Faculty::getNumberOfBooksBorrowed() {
    return num_Books_Borrowed ;
}

int Faculty::getNumberOfOverDueBooks() {
    return num_overdue_books ;
}


void Faculty::setNumberOfBooksBorrowed(int num_books_borrowed) {
    this -> num_Books_Borrowed = num_books_borrowed ;
}

void Faculty::setNumberOfOverDueBooks(int num_overdue_books) {
    this -> num_overdue_books = num_overdue_books ;
}


bool Faculty::authenticate(string userid, string password) {

    Faculty *faculty = FacultyDBM().SelectFaculty(userid) ;
    if( faculty == NULL ) {
        return false ;
    }
    if( faculty -> password == password ) {
        return true ;
    }
    return false ;
}

int Faculty::MaxBooks() {
    return 5 ;
}

string Faculty::FacultyLogin() {
    string userid, password ;
    Faculty faculty ;
    
    for( int i = 0 ; i < 3 ; i++ ){
        std::cout << "-----------------------------------" << endl ;
        std::cout << "           LOGIN WINDOW            " << endl ;
        std::cout << "-----------------------------------" << endl ;
        
        std::cout << "[Input] Enter UserID Option: " ;
        cin >> userid ;
        cin.clear(); 
        cin.ignore(10000, '\n');
        
        std::cout << "[Input] Enter Password Option: " ;
        cin >> password ;
        cin.clear(); 
        cin.ignore(10000, '\n');
        
        faculty.setUserId(userid) ;
        faculty.setPassword(password) ;

        if ( faculty.authenticate(userid, password) ) {
            std::cout << "Login Successful!" << endl ;
            return userid ;
        }
        
        else {
            std::cout << "Login Failed!" << endl ;
            if( i == 2 ) {
                std::cout << "Maximum attempts reached!" << endl ;
                return "" ;
            }
        }
    }
}

void Faculty::ReturnRequest() {
    std::cout << "-----------------------------------" << endl ;
    std::cout << "          RETURN A BOOK             " << endl ;
    std::cout << "-----------------------------------" << endl ;
    Books().DisplayBorrowedBooks(userid) ;

    if( this -> getNumberOfBooksBorrowed() == 0 ) return ;

    std::cout << "[Input] Enter ISBN of Book to be returned: " ;
    string ISBN ;
    cin >> ISBN ;
    cin.clear();
    cin.ignore(10000, '\n');

    Books *bookcheck = BooksDBM().SelectBooks(ISBN) ; 

    if( bookcheck == nullptr ) {
        std::cout << "No book with provided BookID available for you to return." << endl ;
        return ;
    }
    if( bookcheck -> getUser() != userid ) {
        std::cout << "No Book with provided BookID available for you to return." << endl ;
        return ;
    }
        
    time_t now = time(0) ;
    tm *ltm2 = localtime(&now);
    string today = to_string(ltm2->tm_mday) + "-" + to_string(1 + ltm2->tm_mon) + "-" + to_string(1900 + ltm2->tm_year) ;

    int days = DaysDiff(bookcheck -> showDueDate(), today) ;
    if( days > 0 ) {
        float fine = bookcheck->CalculateFine(days) ;
        std::cout << "Book is returned " << days << " days late!" << endl ;
        if(!confirm()) return ;
        this -> setNumberOfBooksBorrowed(this -> getNumberOfBooksBorrowed() - 1) ;
        FacultyDBM().UpdateFaculty(this) ;
        bookcheck -> setUser("") ;
        bookcheck -> setBorrowDate("") ;
        bookcheck -> setDueDate("") ;
        bookcheck -> setstatus("Available");
        Account* acc = AccountDBM().SelectAccount(userid, ISBN , "CUR") ;
        acc -> setReturnDate(today) ;
        acc -> setHistoryType("PREV") ;
        AccountDBM().UpdateAccount(acc) ;
        BooksDBM().UpdateBooks(bookcheck) ;
        std::cout << "Book returned successfully!" << endl ;
        std::cout << "May you have a pleasant day.. :) " << endl ;
    }

    else {
        if(!confirm()) return ;
        this -> setNumberOfBooksBorrowed(this -> getNumberOfBooksBorrowed() - 1) ;
        FacultyDBM().UpdateFaculty(this) ;
        bookcheck -> setUser("") ;
        bookcheck -> setBorrowDate("") ;
        bookcheck -> setDueDate("") ;
        bookcheck -> setstatus("Available");
        Account* acc = AccountDBM().SelectAccount(userid, ISBN , "CUR") ;
        acc -> setReturnDate(today) ;
        acc -> setHistoryType("PREV") ;
        acc -> setDueDate("") ;
        AccountDBM().UpdateAccount(acc) ;
        BooksDBM().UpdateBooks(bookcheck) ;
        std::cout << "Book returned successfully!" << endl ;
        std::cout << "May you have a pleasant day.. :) " << endl ;
    }        
}

