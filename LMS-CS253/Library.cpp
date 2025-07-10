#include "LMS_Model.hpp"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std ;

void Library::DisplayAllBooks(){
    vector<Books*> BooksList = BooksDBM().ListBooks() ;
    cout << "-----------------------------------" << endl ;
    cout << "          ALL BOOKS                 " << endl ;
    cout << "-----------------------------------" << endl ;
    cout <<  endl ;
    for( int i = 0 ; i < BooksList.size() ; i++ ) {
        cout << "BooksID: " << BooksList[i] -> getISBN() << endl ;
        cout << "Title: " << BooksList[i] -> gettitle() << endl ;
        cout << "Author: " << BooksList[i] -> getauthor() << endl ;
        cout << "Publisher: " << BooksList[i] -> getpublisher() << endl ;
        cout << "Year: " << BooksList[i] -> getyear() << endl ;
        cout << "Status: " << BooksList[i] -> getStatus() << endl ;
        cout << "Borrow Date: " << BooksList[i] -> showBorrowDate() << endl ;
        cout << "Due Date: " << BooksList[i] -> showDueDate() << endl ;
        cout << endl ;
    }
    cout << "-----------------------------------" << endl ;
}
bool Library::DisplayAvailableBooks() {
    int flag = 0 ;
    vector<Books*> BooksList = BooksDBM().ListBooks() ;
    cout << "-----------------------------------" << endl ;
    cout << "          BOOKS AVAILABLE          " << endl ;
    cout << "-----------------------------------" << endl ;
    cout <<  endl ;
    for( int i = 0 ; i < BooksList.size() ; i++ ) {
        if( BooksList[i] -> isAvailable() ) {
            flag ++ ;
            cout << "BooksID: " << BooksList[i] -> getISBN() << endl ;
            cout << "Title: " << BooksList[i] -> gettitle() << endl ;
            cout << "Author: " << BooksList[i] -> getauthor() << endl ;
            cout << "Publisher: " << BooksList[i] -> getpublisher() << endl ;
            cout << endl ;
        }
    }
    if( flag == 0 ) {
        cout << "No Books available for Borrowing!" << endl ;
        cout << endl ;
    }
    cout << "-----------------------------------" << endl ;
    return flag ; 
}

void Library::DisplaAllreservedbooks() {
    vector<Books*> BooksList = BooksDBM().ListBooks() ;
    cout << "-----------------------------------" << endl ;
    cout << "          RESERVED BOOKS            " << endl ;
    cout << "-----------------------------------" << endl ;
    cout <<  endl ;
    for( int i = 0 ; i < BooksList.size() ; i++ ) {
        if( BooksList[i] -> getStatus() == "Reserved" ) {
            cout << "BooksID: " << BooksList[i] -> getISBN() << endl ;
            cout << "Title: " << BooksList[i] -> gettitle() << endl ;
            cout << "Author: " << BooksList[i] -> getauthor() << endl ;
            cout << "Publisher: " << BooksList[i] -> getpublisher() << endl ;
            cout << "Year: " << BooksList[i] -> getyear() << endl ;
            cout << "Status: " << BooksList[i] -> getStatus() << endl ;
            cout << "Borrow Date: " << BooksList[i] -> showBorrowDate() << endl ;
            cout << "Due Date: " << BooksList[i] -> showDueDate() << endl ;
            cout << endl ;
        }
    }
    cout << "-----------------------------------" << endl ;
}


void Library::DisplayAllBorrowedBooks() {
    int flag = 0 ;
    vector<Books*> BooksList = BooksDBM().ListBooks() ;
    cout << "-----------------------------------" << endl ;
    cout << "        ALL BORROWED BOOKS         " << endl ;
    cout << "-----------------------------------" << endl ;
    cout <<  endl ;
    for( int i = 0 ; i < BooksList.size() ; i++ ) {
        if(BooksList[i] -> isAvailable() == false) {
            flag ++ ;
            cout << "BooksID: " << BooksList[i] -> getISBN() << endl ;
            cout << "Title: " << BooksList[i] -> gettitle() << endl ;
            cout << "Author: " << BooksList[i] -> getauthor() << endl ;
            cout << "Publisher: " << BooksList[i] -> getpublisher() << endl ;
            cout << endl ;
        }
    }
    if( flag == 0 ) {
        cout << "No Book is Borrowed!" << endl ;
        cout << endl ;
    }
    cout << "-----------------------------------" << endl ;
}


void Library::DisplayAllStudents() {
    vector<Student*> StudentsList = StudentDBM().ListStudents() ;
    cout << "-----------------------------------" << endl ;
    cout << "          ALL STUDENTS              " << endl ;
    cout << "-----------------------------------" << endl ;
    cout <<  endl ;
    for( int i = 0 ; i < StudentsList.size() ; i++ ) {
        cout << "UserID: " << StudentsList[i] -> getUserId() << endl ;
        cout << "Name: " << StudentsList[i] -> getName() << endl ;
        cout << "Dues: " << StudentsList[i] -> getDues() << endl ;
        cout << "Number of Books Borrowed: " << StudentsList[i] -> getNumberOfBooksBorrowed() << endl ;
        cout << "Number of Overdue Books: " << StudentsList[i] -> getNumberOfOverDueBooks() << endl ;
        cout << endl ;
    }
    cout << "-----------------------------------" << endl ;
}

void Library::DisplayAllFacultys() {
    vector<Faculty*> FacultyList = FacultyDBM().ListFacultys() ;
    cout << "-----------------------------------" << endl ;
    cout << "          ALL FACULTY               " << endl ;
    cout << "-----------------------------------" << endl ;
    cout <<  endl ;
    for( int i = 0 ; i < FacultyList.size() ; i++ ) {
        cout << "UserID: " << FacultyList[i] -> getUserId() << endl ;
        cout << "Name: " << FacultyList[i] -> getName() << endl ;
        cout << "Number of Books Borrowed: " << FacultyList[i] -> getNumberOfBooksBorrowed() << endl ;
        cout << "Number of Overdue Books: " << FacultyList[i] -> getNumberOfOverDueBooks() << endl ;
        cout << endl ;
    }
    cout << "-----------------------------------" << endl ;
}

void Library::DisplayAllLibrarians() {
    vector<Librarian*> LibrarianList = LibrarianDBM().ListLibrarians() ;
    cout << "-----------------------------------" << endl ;
    cout << "          ALL LIBRARIANS            " << endl ;
    cout << "-----------------------------------" << endl ;
    cout <<  endl ;
    for( int i = 0 ; i < LibrarianList.size() ; i++ ) {
        cout << "UserID: " << LibrarianList[i] -> getUserId() << endl ;
        cout << "Name: " << LibrarianList[i] -> getName() << endl ;
        cout << endl ;
    }
    cout << "-----------------------------------" << endl ;
}


