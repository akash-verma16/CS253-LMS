#include "LMS_Model.hpp"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std ;

Student::Student( string userid,  string password,  string name) {
    this -> userid = userid ;
    this -> password = password ;
    this -> name = name ;
    this -> dues = 0 ;
    this -> num_overdue_books =  0;
    this -> num_Books_Borrowed = 0 ;
}


Student::Student( string userid,  string password,  string name,  int dues ,  int num_overdue_books , int num_Books_Borrowed) {
    this -> userid = userid ;
    this -> password = password ;
    this -> name = name ;
    this -> dues = dues ;
    this -> num_overdue_books = num_overdue_books ;
    this -> num_Books_Borrowed = num_Books_Borrowed ;
}


int Student::getNumberOfBooksBorrowed() {
    return num_Books_Borrowed ;
}

void Student::setDues(int dues) {
    this -> dues = dues ;
}

int Student::getNumberOfOverDueBooks() {
    return num_overdue_books ;
}

int Student::getDues() {
    return dues ;
}

string User::getUserId() {
    return userid ;
}

string User::getName() {
    return name ;
}


Student::Student() {
    userid = "" ;
    password = "" ;
    name = "" ;
    dues = 0 ;
    num_overdue_books =  0;
    num_Books_Borrowed = 0 ;
}

void User::setUserId(string userid) {
    this -> userid = userid ;
}

void User::setPassword(string password) {
    this -> password = password ;
}

string User::getPassword() {
    return password ;
}

bool Student::authenticate(string userid, string password) {
    Student* student = StudentDBM().SelectStudent(userid) ;
    if( student == NULL ) {
        return false ;
    }
    if( student -> getPassword() == password ) {
        //cout << "looged in" << endl; 
        return true ;
    }
    return false ;
}

void Student::setNumberOfBooksBorrowed(int num_Books_Borrowed){
    this -> num_Books_Borrowed = num_Books_Borrowed ;
}

int Student::MaxBooks() {
    return 3 ;
}

string Student::StudentLogin() {
    
    string userid, password ;
    Student student ;
    
    for( int i = 0 ; i < 3 ; i++ ){
        cout << "-----------------------------------" << endl ;
        cout << "           LOGIN WINDOW            " << endl ;
        cout << "-----------------------------------" << endl ;
        
        cout << "[Input] Enter UserID Option: " ;
        cin >> userid ;
        cin.clear(); 
        cin.ignore(10000, '\n');
        
        cout << "[Input] Enter Password Option: " ;
        cin >> password ;
        cin.clear(); 
        cin.ignore(10000, '\n');
        
        student.setUserId(userid) ;
        student.setPassword(password) ;

        if ( student.authenticate(userid, password) ) {
            cout << "Login Successful!" << endl ;
            return userid ;
        }
        
        else {
            cout << "Login Failed!" << endl ;
            if( i == 2 ) {
                cout << "Maximum attempts reached!" << endl ;
                return "" ;
            }
        }
    }
}

void Student::ReturnRequest() {
    cout << "-----------------------------------" << endl ;
    cout << "          RETURN A BOOK           " << endl ;
    cout << "-----------------------------------" << endl ;
    Books().DisplayBorrowedBooks(userid) ;

    if( this -> getNumberOfBooksBorrowed() == 0 ) return ;

    cout << "[Input] Enter ISBN of book to be returned: " ;
    string bookid ;
    cin >> bookid ;
    cin.clear();
    cin.ignore(10000, '\n');

    Books *bookcheck = BooksDBM().SelectBooks(bookid) ; 

    if( bookcheck == nullptr ) {
        cout << "No Book with provided BookID/ISBN available for you to return." << endl ;
        return ;
    }
    if( bookcheck -> getUser() != userid ) {
        cout <<  "No Book with provided BookID/ISBN available for you to return." << endl ;
        return ;
    }
        
    time_t now = time(0) ;
    tm *ltm2 = localtime(&now);
    string today = to_string(ltm2->tm_mday) + "-" + to_string(1 + ltm2->tm_mon) + "-" + to_string(1900 + ltm2->tm_year) ;

    Account* acc = AccountDBM().SelectAccount(userid, bookid, "CUR") ;
    if (acc == nullptr) {
        cout << "No current borrowing record found for this book." << endl;
        return;
    }

    int days = DaysDiff(bookcheck -> showDueDate(), today) ;
    if( days > 0 ) {
        float fine = bookcheck->CalculateFine(days) ;
        cout << "Book is returned " << days << " days late!" << endl ;
        cout << "Fine to be paid: Rs. " << fine << endl ;
        cout << "-----------------------------------" << endl ;
        if(!confirm()) return ;
        this -> setDues(this -> getDues() + fine) ;
        this -> setNumberOfBooksBorrowed(this -> getNumberOfBooksBorrowed() - 1) ;
        StudentDBM().UpdateStudent(this) ;
        bookcheck -> setUser("") ;
        bookcheck -> setBorrowDate("") ;
        bookcheck -> setDueDate("") ;
        bookcheck -> setstatus("Available");
        acc -> setReturnDate(today) ;
        acc -> setHistoryType("PREV") ;
        AccountDBM().UpdateAccount(acc) ;
        BooksDBM().UpdateBooks(bookcheck) ;
        cout << "Book returned successfully!" << endl ;
        cout << "May you have a pleasant day.. :) " << endl ;
    } else {
        cout << "-----------------------------------" << endl ;
        if(!confirm()) return ;
        this -> setNumberOfBooksBorrowed(this -> getNumberOfBooksBorrowed() - 1) ;
        StudentDBM().UpdateStudent(this) ;
        bookcheck -> setUser("") ;
        bookcheck -> setBorrowDate("") ;
        bookcheck -> setDueDate("") ;
        bookcheck -> setstatus("Available");
        acc -> setReturnDate(today) ;
        acc -> setHistoryType("PREV") ;
        AccountDBM().UpdateAccount(acc) ;
        BooksDBM().UpdateBooks(bookcheck) ;
        cout << "Book returned successfully!" << endl ;
        cout << "May you have a pleasant day.. :) " << endl ;
    }        
}


void Student::clearDues() {
    cout << "-----------------------------------" << endl ;
    cout << "            CLEAR DUES             " << endl ;
    cout << "-----------------------------------" << endl ;
    cout << "[NOTE] Your Current Dues to be paid: Rs. " << this -> getDues() << endl ;
    cout << "-----------------------------------" << endl ;
    if( this -> getDues() == 0 ) {
        cout << "No Dues to be paid!" << endl ;
        return ;
    }
    cout << "[Input] How much would you like to pay? (Rs.): " ;
    string temp ;
    cin >> temp ;
    cin.clear();
    cin.ignore(10000, '\n');

    if(!isDecimal(temp)) return ;
    int pay = stoi(temp) ;

    if( pay > this -> getDues() ) {
        cout << "Invalid input! Amount more than Dues." << endl ;
        cout << "Payment Cancelled!" << endl ;
        return ;
    }
    if( pay < 0 ) {
        cout << "Invalid input! Amount can not be negative" << endl ;
        cout << "Payment Cancelled!" << endl ;
        return ;
    }
    if(!confirm()) return ;
    this -> setDues(this -> getDues() - pay) ;
    StudentDBM().UpdateStudent(this) ;
    cout << "Payment Successful!" << endl ;
    cout << "May you have a pleasant day.. :) " << endl ;
}
