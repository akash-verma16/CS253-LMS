#include "LMS_DB_manager.cpp"
#include "Students.cpp"
#include "Faculty.cpp"
#include "Books.cpp"
#include "Librarian.cpp"
#include "Account.cpp"
#include "LMS_Model.hpp"
#include "Library.cpp"
#include <ctime>
#include <fstream>
#include <iostream>
using namespace std ;

// A function to count the number of leap years to show correct number of days between two given dates
int countLeapYears(Date d) { 
    int years = d.y; 
    if (d.m <= 2) 
        years--;  
    return (years/4)  - (years/100) + (years/400) ; 
}

// A function to check if the input is a valid decimal number.. used to validate user input
bool isDecimal(string temp) {
    int flag = 0 ;
    for ( int i = 0 ; i < temp.length() ; i++ ) {
        if ( isdigit(temp[i]) == false && temp[i] != '.' ) {
            cout << "Invalid input!" << endl ;
            cout << "Process Cancelled!" << endl ;
            return false ;
        }
        if ( temp[i] == '.' ) {
            flag ++ ;
            if(flag>1) {
                cout << "Invalid input!" << endl ;
                cout << "Process Cancelled!" << endl ;
                return false;
            }
        }
    }
    return true ;
}

// A function to check if the input is a valid number.. used to validate user input
bool isNumber(string temp) {
    for ( int i = 0 ; i < temp.length() ; i++ ) {
        if ( isdigit(temp[i]) == false ) {
            cout << "Invalid input!" << endl ;
            cout << "Process Cancelled!" << endl ;
            return false ;
        }
    }
    return true ;
}

// Next two function acts an interface between the program and the database

// It reads data from a file and returns a vector of strings depending on number of columns
vector<string> readFromFile(string filename, int columns) {
    fstream file ;
    file.open(filename, ios::in) ;
    if( file.is_open() ) {
        string line ;
        vector<string> data ;
        int flag = 0 ;
        while( getline(file, line, ',') ) {
            data.push_back(line) ;
            flag ++ ;
            if(flag == columns){
                getline(file, line) ;
                flag = 0 ;
            }
        }
        file.close() ;
        return data ;
    }
    else {
        cout << "Error: File not found!" << endl ;
        return {} ;
    }
}

// This function all acts as an interface between the program and the database... writing a vector of strings to a file
void writeToFile(string filename, vector<string> data, int columns) {
    fstream file ;
    file.open(filename, ios::out) ;
    if( file.is_open() ) {
        for(int i = 0; i < data.size(); i++) {
            file << data[i] ;
            if( (i+1) % columns == 0 ) {
                file << "," << endl ;
            }
            else {
                file << "," ;
            }
        }
        file.close() ;
    }
    else {
        cout << "Error: File not found!" << endl ;
    }
}

// To calculate the number of days between two given dates  
// Used in the customer menu to calculate the number of days between the due date and today's date
int DaysDiff(string due_date, string today) { 
    int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    Date dt1, dt2 ; stringstream ss(due_date) ;
    string temp ; getline(ss, temp, '-') ; dt1.d = stoi(temp) ;
    getline(ss, temp, '-') ; dt1.m = stoi(temp) ;
    getline(ss, temp, '-') ; dt1.y = stoi(temp) ;
    stringstream ss2(today) ;
    getline(ss2, temp, '-') ; dt2.d = stoi(temp) ;
    getline(ss2, temp, '-') ; dt2.m = stoi(temp) ;
    getline(ss2, temp, '-') ; dt2.y = stoi(temp) ;
    long int n1 = dt1.y * 365 + dt1.d; 
    for (int i = 0; i < dt1.m - 1; i++) n1 += monthDays[i]; 
    n1 += countLeapYears(dt1); 
    long int n2 = dt2.y * 365 + dt2.d; 
    for (int i = 0; i < dt2.m - 1; i++) n2 += monthDays[i];
    n2 += countLeapYears(dt2); 
    return (n2 - n1); 
}

// A function to ask user to confirm his/her action
bool confirm() {
    cout << "[Input] Confirm ? (Y/N): " ;
    char confirm ;
    cin >> confirm ;
    cin.clear();
    cin.ignore(10000, '\n');
    if( confirm == 'N' || confirm == 'n' ) {
        cout << "Process Cancelled!" << endl ;
        return false ;
    }
    else if( confirm != 'Y' && confirm != 'y' ) {
        cout << "Invalid input!" << endl ;
        cout << "Process Cancelled!" << endl ;
        return false ;
    }
    return true ;
}

void Student_Menu() {
    string userid  = Student().StudentLogin() ;
    if( userid == "" ) return ;
    int option = 0 ;
    while( option != 8 ) {   
        Student* student = StudentDBM().SelectStudent(userid) ;    
        cout << "--------------------------------------" << endl ;
        cout << "            STUDENT WINDOW            " << endl ;
        cout << "--------------------------------------" << endl ;
        cout << "||  1 - VIEW BORROWED BOOKS         ||" << endl ;
        cout << "||  2 - BORROW A BOOK               ||" << endl ;
        cout << "||  3 - RETURN A BOOK               ||" << endl ;
        cout << "||  4 - CLEAR DUES                  ||" << endl ;
        cout << "||  5 - VIEW ALL AVAILABLE BOOKS    ||" << endl ;
        cout << "||  6 - VIEW PAST BORROWINGS        ||" << endl ;
        cout << "||  7 - VIEW RESERVED BOOKS         ||" << endl ;
        cout << "||  8 - LOGOUT                      ||" << endl ;
        cout << "--------------------------------------" << endl ;
        cout << "[Input] Enter Option: " ;
        cin >> option ;
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        if( option == 1 ) Books().DisplayBorrowedBooks(userid) ;
        else if ( option == 2 ) {
            if( Library().DisplayAvailableBooks() == 0 ) continue ;
            if( student->getDues() > 0 ){
                cout << "You have unpaid dues. First pay dues then only you can borrow"  << endl ; 
                continue ;
            }
            if( student->MaxBooks() == student->getNumberOfBooksBorrowed()  ) {
                cout << "You have reached the maximum borrowing limit!" << endl ;
                continue ;
            }

            
            if(true){
                vector<Account*> AccountList = AccountDBM().ListAccounts() ;

                time_t now = time(0) ;
                tm *ltm2 = localtime(&now);
                string today = to_string(ltm2->tm_mday) + "-" + to_string(1 + ltm2->tm_mon) + "-" + to_string(1900 + ltm2->tm_year) ;
    
                bool hasoverdue = false ;
                for( int i = 0 ; i < AccountList.size() ; i++ ) {
                    if(AccountList[i] -> getUserID() == userid ) {
                        int days = DaysDiff(AccountList[i] -> getDueDate() , today) ;
                        //cout << userid << " " << days << endl ;
                        if( days > 0 ) {
                            hasoverdue = true ;
                            break ;
                         }
                    }
                 }
    
                if( hasoverdue ) {
                    cout << "You have overdue book(s) ." << endl ;
                    cout << "You cannot borrow any more books until you return those overdue book(s)." << endl ;
                    continue ;
                }
            }


            
            string ISBN ;
            cout << "-----------------------------------" << endl ;
            cout << "            BORROW A BOOK          " << endl ;
            cout << "-----------------------------------" << endl ;
            cout << "[Input] Enter ISBN from above available books: " ;
            cin >> ISBN ;
            cin.clear(); 
            cin.ignore(10000, '\n');
            Books *bookcheck = BooksDBM().SelectBooks(ISBN) ; 
            if( bookcheck == nullptr ) {
                cout << "No book with provided BookID/ISBN available for rent." << endl ;
                continue ;
            }
            if( (bookcheck -> isAvailable()) == false ) {
                cout << "Book already borrowed!" << endl ;
                continue ;
            }
            bookcheck -> BorrowBooks(userid,0,ISBN) ;
        }
        else if( option == 3 ) student->ReturnRequest() ;
        else if( option == 4 ) student->clearDues() ;
        else if( option == 5 ) Library().DisplayAvailableBooks() ;
        else if( option == 6 ) Account().DisplayPrevHistory(userid) ;
        else if( option == 7 ) Library().DisplaAllreservedbooks() ;
        else if( option == 8 ) cout << "Logging out" << endl ;
        else cout << "Invalid input!" << endl ;
    }
}

void Faculty_menu(){
    string userid  = Faculty().FacultyLogin() ;
    if( userid == "" ) return ;
    int option = 0 ;
    while( option != 7 ) {   
        Faculty* faculty = FacultyDBM().SelectFaculty(userid) ;    
        cout << "--------------------------------------" << endl ;
        cout << "            FACULTY WINDOW            " << endl ;
        cout << "--------------------------------------" << endl ;
        cout << "||  1 - VIEW BORROWED BOOKS         ||" << endl ;
        cout << "||  2 - BORROW A BOOK               ||" << endl ;
        cout << "||  3 - RETURN A BOOK               ||" << endl ;
        //cout << "||  4 - CLEAR DUES                  ||" << endl ;
        cout << "||  4 - VIEW ALL AVAILABLE BOOKS    ||" << endl ;
        cout << "||  5 - VIEW PAST BORROWINGS        ||" << endl ;
        cout << "||  6 - VIEW ALL RESERVED BOOKS     ||" << endl ;
        cout << "||  7 - LOGOUT                      ||" << endl ;
        cout << "--------------------------------------" << endl ;
        cout << "[Input] Enter Option: " ;
        cin >> option ;
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        if( option == 1 ) Books().DisplayBorrowedBooks(userid) ;
        else if ( option == 2 ) {
            if( Library().DisplayAvailableBooks() == 0 ) continue ;
            if( faculty->MaxBooks() == faculty->getNumberOfBooksBorrowed()  ) {
                cout << "You have reached the maximum borrowing limit!" << endl ;
                continue ;
            }  

            if(true){
                vector<Account*> AccountList = AccountDBM().ListAccounts() ;

                time_t now = time(0) ;
                tm *ltm2 = localtime(&now);
                string today = to_string(ltm2->tm_mday) + "-" + to_string(1 + ltm2->tm_mon) + "-" + to_string(1900 + ltm2->tm_year) ;
    
                bool hasoverdue = false ;
                for( int i = 0 ; i < AccountList.size() ; i++ ) {
                    if(AccountList[i] -> getUserID() == userid ) {
                        int days = DaysDiff(AccountList[i] -> getDueDate() , today) ;
                        //cout << userid << " " << days << endl ;
                        if( days > 60 ) {
                            hasoverdue = true ;
                            break ;
                         }
                    }
                 }
    
                if( hasoverdue ) {
                    cout << "You have overdue book(s) for more than 60 days." << endl ;
                    cout << "You cannot borrow any more books until you return those overdue book(s)." << endl ;
                    continue ;
                }
            } 

            
            string ISBN ;
            cout << "-----------------------------------" << endl ;
            cout << "            BORROW A BOOK          " << endl ;
            cout << "-----------------------------------" << endl ;
            cout << "[Input] Enter ISBN from above available books: " ;
            cin >> ISBN ;
            cin.clear(); 
            cin.ignore(10000, '\n');
            Books *bookcheck = BooksDBM().SelectBooks(ISBN) ; 
            if( bookcheck == nullptr ) {
                cout <<  "No book with provided BookID/ISBN available for rent." << endl ;
                continue ;
            }
            if( !(bookcheck -> isAvailable() )) {
                cout << "Book already borrowed!" << endl ;
                continue ;
            }
            bookcheck -> BorrowBooks(userid,1 ,ISBN) ;
        }
        else if( option == 3 ) faculty->ReturnRequest() ;
        //else if( option == 4 ) faculty->clearDues() ;
        else if( option == 4 ) Library().DisplayAvailableBooks() ;
        else if ( option == 5 ) Account().DisplayPrevHistory(userid) ;
        else if( option == 6 ) Library().DisplaAllreservedbooks() ;
        else if( option == 7 ) cout << "Logging out" << endl ;
        else cout << "Invalid input!" << endl ;
    }
} 

void Librarian_Menu() {
    string userid  = Librarian().LibrarianLogin() ;
    if( userid == "" ) return ;
    int option = 0 ;
    while( option != 21 ) {  
        // CODE : func to see all reserverd books in all three of users
        Librarian* librarian = LibrarianDBM().SelectLibrarian(userid) ;      
        cout << "----------------------------------------------" << endl ;
        cout << "               LIBRARIAN WINDOW               " << endl ;
        cout << "----------------------------------------------" << endl ;
        cout << "||  1 - DISPLAY AVAILABLE BOOKS             ||" << endl ;
        cout << "||  2 - DISPLAY ALL BORROWED BOOKS          ||" << endl ;
        cout << "||  3 - DISPLAY ALL STUDENTS                ||" << endl ;
        cout << "||  4 - DISPLAY ALL FACULTYS                ||" << endl ;
        cout << "||  5 - ADD STUDENT                         ||" << endl ;
        cout << "||  6 - DELETE STUDENT                      ||" << endl ;
        cout << "||  7 - UPDATE STUDENT                      ||" << endl ;
        cout << "||  8 - ADD FACULTY                         ||" << endl ;
        cout << "||  9 - DELETE FACULTY                      ||" << endl ;
        cout << "|| 10 - UPDATE FACULTY                      ||" << endl ;
        cout << "|| 11 - ADD LIBRARIAN                       ||" << endl ;
        cout << "|| 12 - DELETE LIBRARIAN                    ||" << endl ;
        cout << "|| 13 - UPDATE LIBRARIAN                    ||" << endl ;
        cout << "|| 14 - ADD BOOK                            ||" << endl ;
        cout << "|| 15 - DELETE BOOK                         ||" << endl ;
        cout << "|| 16 - UPDATE BOOK                         ||" << endl ;
        cout << "|| 17 - VIEW CURRENT BORROWINGS (ANY USER)  ||" << endl ;
        cout << "|| 18 - VIEW PAST BORROWINGS (ANY USER)     ||" << endl ;
        cout << "|| 19 - DISPLAY ALL RESERVED BOOKS          ||" << endl ;
        cout << "|| 20 - DISPLAY BOOKS IN LIB                ||" << endl ;
        cout << "|| 21 - LOGOUT                              ||" << endl ;
        cout << "----------------------------------------------" << endl ;
        cout << "[Input] Enter Option: " ;
        cin >> option ;
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        if( option == 1 ) Library().DisplayAvailableBooks() ;
        else if( option == 2 ) Library().DisplayAllBorrowedBooks() ;
        else if( option == 3 ) Library().DisplayAllStudents() ;
        else if( option == 4 ) Library().DisplayAllFacultys() ;
        else if( option == 5 ) librarian->AddUser(0) ;
        else if( option == 6 ) librarian->DeleteUser(0) ;
        else if( option == 7 ) librarian->UpdateUser(0) ;
        else if( option == 8 ) librarian->AddUser(1) ;
        else if( option == 9 ) librarian->DeleteUser(1) ;
        else if( option == 10 ) librarian->UpdateUser(1) ;
        else if( option == 11 ) librarian->AddUser(2) ;
        else if( option == 12 ) librarian->DeleteUser(2) ;
        else if( option == 13 ) librarian->UpdateUser(2) ;
        else if( option == 14 ) librarian->AddBooks() ;
        else if( option == 15 ) librarian->DeleteBooks() ;
        else if( option == 16 ) librarian->UpdateBooks() ;
        else if( option == 17 ) {
            cout << "Enter UserID: " ;
            string userid ;
            cin >> userid ;
            Account().DisplayCurHistory(userid) ;
        }
        else if( option == 18 ){
            cout << "Enter UserID: " ;
            string userid ;
            cin >> userid ;
            Account().DisplayPrevHistory(userid) ;
        }
        else if( option == 19 ) Library().DisplaAllreservedbooks() ;
        else if( option == 20 ) Library().DisplayAllBooks() ;
        else if( option == 21 ){
            cout << "Logging out!" << endl ;
            return ;
        }
        else cout << "Invalid Option!" << endl ;
    }
}

// First Screen to display.. options to login as a customer, employee or manager
void LoginMenu() {
    int option = 0 ;
    while ( option != 4 ) {
        system("cls") ;
        cout << "=====================================" << endl ;
        cout << "||                                 ||" << endl ;
        cout << "||       LIB MANAGEMENT SYSTEM     ||" << endl ;
        cout << "||                                 ||" << endl ;
        cout << "=====================================" << endl ;
        cout << "-------------------------------------" << endl ;
        cout << "           LOGIN OPTIONS             " << endl ;
        cout << "-------------------------------------" << endl ;
        cout << "||   1 - STUDENT                   ||" << endl ;
        cout << "||   2 - FACULTY                   ||" << endl ;
        cout << "||   3 - LIBRARIAN                 ||" << endl ;
        cout << "||   4 - EXIT                      ||" << endl ;
        cout << "-------------------------------------" << endl ;
        cout << "[Input] Enter Login Option: ";	
        cin >> option;
        cin.clear(); 
        cin.ignore(10000, '\n');

        if ( option == 1 ) {
            system("cls") ;
            Student_Menu() ;
        }
        else if( option == 2 ) {
            system("cls") ;
            Faculty_menu() ;
        }
        else if( option == 3 ) {
            system("cls") ;
            Librarian_Menu() ;
        }
        else if( option == 4 ) {
            cout << "Exiting" << endl ;
            cout << "Thank you for visiting you favourite Library!" << endl ;
        }
        else {
            cout << "Invalid option!" << endl ;
        }
    }
}

int main(){
    LoginMenu() ;
    return 0 ; 
}