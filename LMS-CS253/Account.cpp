#include "LMS_Model.hpp"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std ;

Account::Account(){
    userid = "" ;
    history_type = "" ;
    ISBN = "" ;
    borrow_date = "" ;
    due_date = "" ; 
    return_date = "" ;
}

Account::Account(string userid, string history_type, string ISBN, string borrow_date, string due_date, string return_date) {
    this->userid = userid ;
    this->history_type = history_type ;
    this->ISBN = ISBN ;
    this->borrow_date = borrow_date ;
    this->due_date = due_date ;
    this->return_date = return_date ;
}

void Account::setUserID(string userid) {
    this->userid = userid ;
}

void Account::setHistoryType(string history_type) {
    this->history_type = history_type ;
}

void Account::setISBN(string ISBN) {
    this->ISBN = ISBN ;
}

void Account::setBorrowDate(string borrow_date) {
    this->borrow_date = borrow_date ;
}

void Account::setDueDate(string due_date) {
    this->due_date = due_date ;
}

void Account::setReturnDate(string return_date) {
    this->return_date = return_date ;
}

string Account::getUserID() {
    return userid ;
}

string Account::getHistoryType() {
    return history_type ;
}

string Account::getISBN() {
    return ISBN ;
}

string Account::getBorrowDate() {
    return borrow_date ;
}

string Account::getDueDate() {
    return due_date ;
}

string Account::getReturnDate() {
    return return_date ;
}

void Account::DisplayCurHistory(string userid) {
    vector<Account*> AccountList = AccountDBM().ListAccounts() ;
    cout << "-----------------------------------" << endl ;
    cout << "        CURRENT HISTORY            " << endl ;
    cout << "-----------------------------------" << endl ;
    cout <<  endl ;
    for( int i = 0 ; i < AccountList.size() ; i++ ) {
        if(AccountList[i] -> getUserID() == userid && AccountList[i] -> getReturnDate() == "") {
            cout << "UserID: " << AccountList[i] -> getUserID() << endl ;
            cout << "BooksID: " << AccountList[i] -> getISBN() << endl ;
            cout << "Borrow Date: " << AccountList[i] -> getBorrowDate() << endl ;
            cout << "Due Date: " << AccountList[i] -> getDueDate() << endl ;
            cout << endl ;
        }
    }
    cout << "-----------------------------------" << endl ;
}

void Account::DisplayPrevHistory(string userid) {
    vector<Account*> AccountList = AccountDBM().ListAccounts() ;
    cout << "-----------------------------------" << endl ;
    cout << "        PREVIOUS HISTORY           " << endl ;
    cout << "-----------------------------------" << endl ;
    cout <<  endl ;
    for( int i = 0 ; i < AccountList.size() ; i++ ) {
        if(AccountList[i] -> getUserID() == userid && AccountList[i] -> getReturnDate() != "") {
            cout << "UserID: " << AccountList[i] -> getUserID() << endl ;
            cout << "BooksID: " << AccountList[i] -> getISBN() << endl ;
            cout << "Borrow Date: " << AccountList[i] -> getBorrowDate() << endl ;
            cout << "Due Date: " << AccountList[i] -> getDueDate() << endl ;
            cout << "Return Date: " << AccountList[i] -> getReturnDate() << endl ;
            cout << endl ;
        }
    }
    cout << "-----------------------------------" << endl ;
}