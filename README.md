# Library management syatem
This repository contains my submission for the C++ Assignment for the course CS253 : Software Development and Operations, Spring 2025 under the guidance of Prof. Indranil Saha.

## Setup Instructions
go to LMS_main.cpp file


Run the code below to compile the files and create an executable file.
```
g++ -std=c++17 LMS_main.cpp
```
Run the created executable file by running below code.
```
./a.exe
```


## Portability 

- The code was written in Windows operating system. Few functionalities can cause issue in other operating systems, like to clear terminal screen in Linux, replace `system("cls")` has to be changed to `system("clear")`.

## Project Structure
The repository is organised as : 
- `LMS_DB` Folder : This folder acts as the database and contains 5 comma separated values files to store information.
  - `students.csv` : This file contains information about students. It contains 6 different columns namely `UserId`, `Password`, `Name`,  `Dues` , `Number of overdue books` and `Number of books borrowed`.
  - `faculty.csv` : This file contains information about facultys. It contains 5 different columns namely `UserId`, `Password`, `Name`, `Dues` and `Number Of books borrowed`.
  - `Librarian..csv` : This file contains information about Librarian. It contains  different columns namely `UserId`, `Password` and `Name`.
  - `Books.csv` : This file contains information about customers. It contains 9 different columns namely `ISBN`, `Title`, `Author`,`Publisher`, `yearofpublishing`,`Status`, `UserIdRented`,`BorrowDate` and `Due_Date`.



## Assumptions and Design 

- A Book borrowed by a User can not be deleted or updated by Manager.
- If Manager deletes a User, Books rented by him are returned back.
- Reserved Book : A book with a "reserved" status is meant to be read only within the library premises and cannot be borrowed.  Additionally, only the librarian has the authority to change its status between "available" and "reserved."
- If a user is deleted then its all history is also deleted .
- student can not borrow a book if he has overdue on some book


## Author
- Akash Verma
- IIT Kanpur
- 220097




