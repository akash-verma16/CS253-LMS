#include "LMS_Model.hpp"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std ;

Librarian::Librarian() {
    userid = "" ;
    password = "" ;
    name = "" ;
}

Librarian::Librarian(string userid, string password, string name) {
    this -> userid = userid ;
    this -> password = password ;
    this -> name = name ;
}

bool Librarian::authenticate(string userid, string password) {
    Librarian* library = LibrarianDBM().SelectLibrarian(userid) ;
    if( library == NULL ) {
        return false ;
    }
    if( library -> getPassword() == password ) {
        return true ;
    }
    return false ;
}

string Librarian::LibrarianLogin() {
    
    string userid, password ;
    Librarian librarian ;
    
    for( int i = 0 ; i < 3 ; i++ ){
        std::cout << "-----------------------------------" << endl ;
        std::cout << "           LOGIN WINDOW            " << endl ;
        std::cout << "-----------------------------------" << endl ;
        
        std::cout << "[Input] Enter UserID Option: " ;
        std::getline(cin , userid) ; 
        
        std::cout << "[Input] Enter Password Option: " ;
        std::getline(cin , password) ; 
        
        librarian.setUserId(userid) ;
        librarian.setPassword(password) ;

        if ( librarian.authenticate(userid, password) ) {
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

void Librarian::AddUser( int user_type ) {
    string userid, password, name, final_name ;
    std::cout << "-----------------------------------" << endl ;
    std::cout << "             ADD USER              " << endl ;
    std::cout << "-----------------------------------" << endl ;
    if (user_type == 0 ) std::cout << "Adding Student!" << endl ;
    else if (user_type == 1 ) std::cout << "Adding Faculty!" << endl ;
    else if (user_type == 2 ) std::cout << "Adding Librarian!" << endl ;
    
    if(user_type == 0) std::cout << "NOTE : Prefix the user id with s_" << endl;
    else if(user_type == 1) std::cout << "NOTE: Prefix the user id with f_"  << endl;
    
    std::cout << "[Input] Enter UserID: " ;
    std::getline(cin , userid) ;

    std::cout << "[Input] Enter Password: " ;
    std::getline(cin , password) ; 

    std::cout << "[Input] Enter Name: " ;
    std::getline(std::cin, final_name);

    if(user_type == 0){
        Student* student = new Student(userid, password, final_name) ;
        StudentDBM().AddStudent(student) ;
    }
    else if(user_type == 1){
        Faculty* faculty = new Faculty(userid, password, final_name) ;
        FacultyDBM().AddFaculty(faculty) ;
    }
    else if(user_type == 2){
        Librarian* librarian = new Librarian(userid, password, final_name) ;
        LibrarianDBM().AddLibrarian(librarian) ;
    }
}

void Librarian::DeleteUser( int user_type ) {
    string userid ;
    std::cout << "-----------------------------------" << endl ;
    std::cout << "            DELETE USER            " << endl ;
    std::cout << "-----------------------------------" << endl ;
    if (user_type == 0 ) std::cout << "Deleting Student!" << endl ;
    else if (user_type == 1 ) std::cout << "Deleting Faculty!" << endl ;
    else if (user_type == 2 ) std::cout << "Deleting Librarian!" << endl ;
    std::cout << "[Input] Enter UserID: " ;
    std::getline(cin , userid) ; 

    if( userid == this->getUserId() ){
       std:: cout << "Cannot delete yourself!" << endl ;
        return ;
    }

    BooksDBM().DeleteBooksUserID(userid) ;

    if (user_type == 0 ) StudentDBM().DeleteStudent(userid) , AccountDBM().DeleteAccount(userid) ;
    else if (user_type == 1 ) FacultyDBM().DeleteFaculty(userid) , AccountDBM().DeleteAccount(userid) ;
    else if (user_type == 2 ) LibrarianDBM().DeleteLibrarian(userid) , AccountDBM().DeleteAccount(userid) ;
    
}

void Librarian::UpdateUser( int user_type ) {
    string userid, password, name , temp , temp1 , temp2 , final_name ;
    int dues , num_books_borrowed , num_overdue_books ;
    
    std::cout << "-----------------------------------" << endl ;
    std::cout << "          UPDATE USER              " << endl ;
    std::cout << "-----------------------------------" << endl ;
    if (user_type == 0 ) std::cout << "Updating Student!" << endl ;
    else if (user_type == 1 ) std::cout << "Updating Faculty!" << endl ;
    else if (user_type == 2 ) std::cout << "Updating Librarian!" << endl ;
    std::cout << "[Input] Enter UserID: " ;
    std::getline(cin , userid) ; 
    
    if( user_type == 0 && StudentDBM().SelectStudent(userid) == NULL ) {
        std::cout << "UserID does not exist!" << endl ;
        return ;
    }
    if( user_type == 1 && FacultyDBM().SelectFaculty(userid) == NULL ) {
        std::cout << "UserID does not exist!" << endl ;
        return ;
    }
    if( user_type == 2 && LibrarianDBM().SelectLibrarian(userid) == NULL) {
        std::cout << "UserID does not exist!" << endl ;
        return ;
    }


    std::cout << "-----------------------------------" << endl ;
    std::cout << "      CURRENT USER DETAILS         " << endl ;
    std::cout << "-----------------------------------" << endl ;
    if( user_type == 0 ) {
        Student* student = StudentDBM().SelectStudent(userid) ;
        std::cout << "UserID: " << student -> getUserId() << endl ;
        std::cout << "Password: " << student -> getPassword() << endl ;
        std::cout << "Name: " << student -> getName() << endl ;
        
        std::cout << "Dues: " << student -> getDues() << endl ;
        std::cout << "Number of Books Borrowed: " << student -> getNumberOfBooksBorrowed() << endl ;
        std::cout << "Number of Overdue Books: " << student -> getNumberOfOverDueBooks() << endl ;
    }
    else if( user_type == 1 ) {
        Faculty* faculty = FacultyDBM().SelectFaculty(userid) ;
        std::cout << "UserID: " << faculty -> getUserId() << endl ;
        std::cout << "Password: " << faculty -> getPassword() << endl ;
        std::cout << "Name: " << faculty -> getName() << endl;
        std::cout << "Number of Books Borrowed: " <<faculty -> getNumberOfBooksBorrowed() << endl ;
        std::cout << "Number of Overdue Books: " << faculty -> getNumberOfOverDueBooks() << endl ;
    }
    else if( user_type == 2 ) {
        Librarian* librarian = LibrarianDBM().SelectLibrarian(userid) ;
        std::cout << "UserID: " << librarian -> getUserId() << endl ;
        std::cout << "Password: " << librarian -> getPassword() << endl ;
        std::cout << "Name: " << librarian -> getName() << endl ;
    }
    std::cout << "-----------------------------------" << endl ;
    std::cout << "[Input] Enter New Password: " ;
    std::getline(cin , password) ; 
    
    std::cout << "[Input] Enter New Name: " ;
    std::getline(std::cin, final_name);
    
    if(user_type == 0 || user_type == 1){
        if(user_type == 0){
        std::cout << "[Input] Enter New Dues/fines(total): " ;
        std::getline(cin , temp) ; 
        
        if(!isDecimal(temp)) return ;
        if(temp == "") {
            std::cout << "Invalid Data!" << endl ;
            return ;
        }
        dues = stoi(temp) ;
        if(dues < 0) {
            std::cout << "Invalid Data!" << endl ;
            return ;
            }
        }

        std::cout << "[Input] Enter new Number of Books Borrowed: " ;
        std::getline(cin , temp1) ; 
        
        if(!isNumber(temp1)) return ;
        if(temp1 == "") {
            std::cout << "Invalid Data!" << endl ;
            return ;
        }
        num_books_borrowed = stoi(temp1) ;
        if(num_books_borrowed < 0) {
            std::cout << "Invalid Data!" << endl ;
            return ;
        }

        std::cout << "[Input] Enter new Number of Overdue Books: " ;
        std:: getline(cin , temp2) ;
        if(temp2 == "") {
            std::cout << "Invalid Data!" << endl ;
            return ;
        }
        
        if(!isNumber(temp2)) return ;
        num_overdue_books = stoi(temp2) ;

        if(num_overdue_books < 0 || num_overdue_books > num_books_borrowed) {
            std::cout << "Invalid Data : overdue books can't be less than 0 or more than no. of borrowed books!" << endl ;
            return ;
        }
    }
    if( user_type == 0 ){
        Student* student = new Student(userid, password, final_name, dues, num_overdue_books, num_books_borrowed) ;
        StudentDBM().UpdateStudent(student) ;
        std::cout << "Student Updated!" << endl ;
    }
    else if( user_type == 1 ){
        Faculty* faculty = new Faculty(userid, password, final_name, num_overdue_books, num_books_borrowed) ;
        FacultyDBM().UpdateFaculty(faculty) ;
        std::cout << "Faculty Updated!" << endl ;
    }
    else if( user_type == 2 ){
        Librarian* librarian = new Librarian(userid, password, final_name) ;
        LibrarianDBM().UpdateLibrarian(librarian) ;
        std::cout << "Librarian Updated!" << endl ;
    }   
}

void Librarian::AddBooks() {
    string ISBN,title , author,  publisher , year , status  ; 
    int book_year ;
    std::cout << "-----------------------------------" << endl ;
    std::cout << "             ADD BOOK               " << endl ;
    std::cout << "-----------------------------------" << endl ;
    std::cout << "[Input] Enter ISBN : " ;
    std::getline(cin , ISBN) ; 
    
    std::cout << "[Input] Enter book title: " ;
    std::getline(cin , title) ; 

    std::cout << "[Input] Enter author name: " ;
    std::getline(cin , author)  ;
    
    std::cout << "[Input] Enter publisher name: " ;
    std::getline(cin , author) ; 
    
    std::cout << "[Input] Enter year of publishing: " ;
    std::getline(cin , year) ; 
    if(!isNumber(year)) return ;
    if(year == "") {
        std::cout << "Invalid Condition!" << endl ;
        return ;
    }
     book_year = stoi(year) ;
    if(book_year < 0) {
        std::cout << "Invalid Condition!" << endl ;
        return ;
    }
    
    std::cout << "[Input] Enter Status [Avialable / Reserved]: " ;
    std::getline(cin , status) ; 
    if(status != "Available" && status != "Reserved" ) {
        std::cout << "Invalid Status!" << endl ;
        return ;
    }
    
    Books* book = new Books(ISBN,  title , author, publisher, book_year , status );
    BooksDBM().AddBooks(book) ;
}

void Librarian::DeleteBooks() {
    string ISBN ;
    std::cout << "-----------------------------------" << endl ;
    std::cout << "            DELETE BOOK             " << endl ;
    std::cout << "-----------------------------------" << endl ;
    std::cout << "[Input] Enter BOOKID /ISBN: " ;
    std::getline(cin , ISBN ) ;

    if( BooksDBM().SelectBooks(ISBN) != NULL && BooksDBM().SelectBooks(ISBN) -> getUser() != "") {
        std::cout << "Borrowed Book can not be deleted!" << endl ;
        return ;
    }        
    BooksDBM().DeleteBooks(ISBN) ;
}

void Librarian::UpdateBooks() {

    string ISBN,title , author,  publisher , year , status  ; 
    int book_year ;
    cout << "-----------------------------------" << endl ;
    cout << "            UPDATE BOOK             " << endl ;
    cout << "-----------------------------------" << endl ;
    cout << "[Input] Enter BOOKID/ISBN: " ;
    getline(cin , ISBN) ; 
    
    if( BooksDBM().SelectBooks(ISBN) == NULL ) {
        cout << "Book ID / ISBN  does not exist!" << endl ;
        return ;
    }
    if( BooksDBM().SelectBooks(ISBN) -> getUser() != "" ) {
        cout << "Borrowed book can not be updated!" << endl ;
        return ;
    }   
    cout << "-----------------------------------" << endl ;
    cout << "       CURRENT BOOK DETAILS         " << endl ;
    cout << "-----------------------------------" << endl ;
    Books* book = BooksDBM().SelectBooks(ISBN) ;
    cout << "ISBN: " << book -> getISBN() << endl ;
    cout << "title: " << book -> gettitle() << endl ;
    cout << "author: " << book -> getauthor() << endl ;
    cout << "publisher: " << book -> getpublisher() << endl ;
    cout << "year: " << book -> getyear() << endl ;
    cout << "status: " << book -> getStatus() << endl ;
    cout << "borrow_date: " << book -> showBorrowDate() << endl ; 
    cout << "due_date: " << book -> showDueDate() << endl ; 
    
    cout << "-----------------------------------" << endl ;
    cout << "[Input] Enter New title : " ;
    getline(cin , title) ; 
    
    cout << "[Input] Enter New author : " ;
    getline(cin , author) ; 
    
    std::cout << "[Input] Enter New publisher name: " ;
     std::getline(cin , publisher) ; 

    std::cout << "[Input] Enter New year of publishing: " ;
    std::getline(cin , year) ;
    if(!isNumber(year)) return ;
    if(year == "") {
        std::cout << "Invalid Condition!" << endl ;
        return ;    
    }
     book_year = stoi(year) ;
    if(book_year < 0) {
        std::cout << "Invalid Condition!" << endl ;
        return ;
    }

    std::cout << "[Input] Enter New Status [Avialable / Reserved]: " ;
    std::getline(cin , status) ; 
    if(status != "Available" && status != "Reserved" ) {
        std::cout << "Invalid Status!" << endl ;
        return ;
    }
    Books* newbook = new Books(ISBN,  title , author, publisher, book_year , status );
    BooksDBM().UpdateBooks(newbook) ;
    cout << "Book Updated!" << endl ;
}

