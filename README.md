

# Library Management System

C++ implementation submitted for **CS253 – Software Development and Operations (Spring 2025)** under the guidance of **Prof. Indranil Saha**. 
The program emulates day-to-day operations of a small library: borrowing / returning books, fine calculation, stock management and multi-role authentication (Student / Faculty / Librarian).

## 1. Setup

| Step | Command |
| :-- | :-- |
| Clone repository | `git clone https://github.com/<your-username>/Library-Management-System-CS253.git` |
| Build (C++17) | `g++ -std=c++17 LMS_main.cpp` |
| Run | `./a.exe` |

> **Windows vs Linux:** the code clears the console with `system("cls")`. On Unix-like systems replace it with `system("clear")`.

## 2.  Project Layout

```
.
├── LMS_DB/              ← CSV “database”
│   ├── books.csv
│   ├── students.csv
│   ├── faculty.csv
│   ├── Librarian.csv
│   └── account.csv
├── Library.cpp          ← Presentation layer (menus & reports)
├── Books.cpp            ← Book domain logic
├── Students.cpp
├── Faculty.cpp
├── Librarian.cpp
├── Account.cpp
├── LMS_DB_manager.cpp   ← Lightweight DAO layer
├── LMS_model.hpp        ← Class / struct declarations
└── LMS_main.cpp         ← `main()` + helpers
```


### 2.1  CSV Schema

| File | Columns (in order) |
| :-- | :-- |
| `books.csv` | ISBN, Title, Author, Publisher, Year, Status, UserIdRented, BorrowDate, DueDate |
| `students.csv` | UserId, Password, Name, Dues, OverdueBooks, BooksBorrowed |
| `faculty.csv` | UserId, Password, Name, OverdueBooks, BooksBorrowed |
| `Librarian.csv` | UserId, Password, Name |
| `account.csv` | UserId, HistoryType(CUR/PREV), ISBN, BorrowDate, DueDate, ReturnDate |

## 3. Core Classes (see `LMS_model.hpp`)

### 3.1  Domain

* **User** – base for Student, Faculty, Librarian
Attributes: `userid`, `password`, `name`
* **Student / Faculty**
Extra: dues / record counts, borrowing limits, login \& authentication helpers, fine settlement.
* **Librarian**
Full CRUD over users and non-borrowed books.
* **Books**
ISBN, title, author, publisher, year, status (`Available`, `Reserved`, `Borrowed`), daily fine; methods to borrow, return, compute fines/dues.
* **Account**
Historical record for every borrow/return (current vs past).
* **Library**
Read-only dashboards (all books, available list, reserved list, borrowed list, user lists).


### 3.2  Database Managers (-DBM)

Each DBM keeps an in-memory `std::vector` of objects, loads it from the corresponding CSV at construction and writes back on destruction.

```
StudentDBM   FacultyDBM   LibrarianDBM   BooksDBM   AccountDBM
```

Typical operations: `Add*`, `Delete*`, `Update*`, `Select*`, `List*`.

## 4.  Program Flow

1. `main()` shows a **Login Menu** (Student / Faculty / Librarian).
2. Successful login drops the user into a role-specific **command window**:
    - **Student / Faculty** – view \& borrow books, return, pay dues, history.
    - **Librarian** – stock management, user management, global reports.
3. CSV files are updated transparently on every CRUD mutation.

## 5. Running Example (initial seed)

### 5.1  Users

| Role | Count | Example UserIDs |
| :-- | :-- | :-- |
| Students | 5 | `s_220097`, `s_220098`, … |
| Faculty | 3 | `f_fac1`, `f_fac2`, … |
| Librarians | 1 | `lib1` |

### 5.2  Books (excerpt)

| ISBN | Title | Status | Borrower |
| :-- | :-- | :-- | :-- |
| 9780131103627 | The C Programming Language | Borrowed | s_220097 |
| 9780262033848 | Introduction to Algorithms | Available | — |
| 9780134685991 | Effective Modern C++ | Reserved | — |

*(Edit the CSVs to change the seed or start from scratch.)*

## 6.  Design \& Assumptions

* A **borrowed** book cannot be deleted or edited by the librarian.
* Deleting a user **auto-returns** all books linked to that user.
* Reserved books are for in-library reading only; only librarians may toggle `Reserved ⇄ Available`.
* **Borrow limits**
    * Student – 3 books
    * Faculty  – 5 books
* **Fine policy** – ₹10/day past due date (configurable via `Books::fine`).
* Dates are stored as `dd-mm-yyyy` strings; helper functions convert \& compute day differences.
* Max login attempts: 3 per session.


## 7.  Portability

The code is **platform-independent** except for console clearing:

```cpp
// Windows
system("cls");
// Linux / macOS
system("clear");
```

No external libraries beyond the C++17 STL are required.

## 8.  Author

- **Akash Verma**  
- IIT Kanpur  
- 220097



Happy borrowing!

<div style="text-align: center">⁂</div>

[^1]: Library.cpp

[^2]: README.md

[^3]: Students.cpp

[^4]: Account.cpp

[^5]: Books.cpp

[^6]: Faculty.cpp

[^7]: Librarian.cpp

[^8]: LMS_DB_manager.cpp

[^9]: LMS_main.cpp

[^10]: LMS_model.hpp

