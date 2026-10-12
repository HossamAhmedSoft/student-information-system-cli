# University Student Information System (SIS) — C++ CLI

A high-performance, object-oriented Academic Enterprise Management CLI written in **modern C++**, engineered for university operations with role-based access control (Admin, Professor, Student), course scheduling, attendance tracking, automated GPA calculations, and file persistence.

---

## Key Features

- **Role-Based Portals:**
  - **Student Portal:** View enrolled courses, review academic grades, calculate semester & cumulative GPA, view attendance records, and inspect fee statement balances.
  - **Professor Portal:** Manage assigned courses, take student attendance, record grades (Midterm, Final, Coursework), and view course enrollments.
  - **Administrator Portal:** Full administrative management across Students, Faculty, Courses, Departments, Lecture Halls, Laboratories, and Financial Accounts.
- **Academic Computation Engine:** Credit-weighted GPA computation, grade letter mappings (A+, A, B, C, D, F), and graduation progress checking.
- **Robust Validation:** Strict format validators for Student IDs, email addresses, phone numbers, course codes, and numeric ranges.
- **Persistent Data Store:** Delimited file-based persistence for cross-session data storage.
- **Interactive Terminal UI:** Formatted ANSI tables, aligned data grids, breadcrumb menus, and colored status indicators.

---

## System Architecture

```
SISCLI/
├── include/
│   ├── Config.h                  # System constants and global configurations
│   ├── Models/                   # Domain Entity Definitions
│   │   ├── User.h / Admin.h      # Core authentication entities
│   │   ├── Student.h             # Student profile, academic standing, major
│   │   ├── Professor.h           # Academic staff credentials and department
│   │   ├── Course.h              # Course code, credit hours, prerequisites
│   │   ├── Department.h          # University departments and faculties
│   │   ├── Grade.h               # Letter grades, raw marks, weights
│   │   ├── Attendance.h          # Attendance logs, dates, statuses
│   │   ├── Fee.h                 # Financial charges, payments, balance
│   │   ├── Schedule.h            # Time slots, lecture halls, labs
│   │   └── Equipment.h           # Laboratory assets and inventory
│   ├── Services/                 # Business Operations & Persistence
│   │   ├── AuthService.h         # User session management and credential verification
│   │   ├── DataService.h         # CRUD operations across entities
│   │   └── FileHandler.h         # File serialization and parsing
│   └── Utils/                    # UI Utilities and Calculators
│       ├── ConsoleUI.h           # Formatted headers, dividers, tables
│       ├── GradeCalculator.h     # Weighted GPA calculation logic
│       └── Validators.h          # Input sanitization and format rules
├── data/                         # Local database files
│   └── users.dat                 # Seed authentication records
├── main.cpp                      # Application entry point & interactive menus
├── SISCLI.sln                    # Visual Studio Solution
└── SISCLI.vcxproj                # MSBuild Project Definition
```

---

## Default Demonstration Credentials

For testing and demonstration, pre-seeded accounts are available in `data/users.dat`:

| Role | Username | Password | Access Level |
| :--- | :--- | :--- | :--- |
| **System Admin** | `admin` | `admin123` | Full system governance, all portals |

---

## Building and Running

### Option 1: Microsoft Visual Studio (Recommended on Windows)
1. Open `SISCLI.sln` in **Visual Studio 2022** (or newer).
2. Set configuration to `Release` and architecture to `x64`.
3. Press `Ctrl + Shift + B` to build the solution.
4. Run via `Ctrl + F5` or execute `x64\Release\SISCLI.exe`.

### Option 2: Command Line (MSVC / Developer PowerShell)
```cmd
msbuild SISCLI.sln /p:Configuration=Release /p:Platform=x64
.\x64\Release\SISCLI.exe
```

### Option 3: Clang++ / G++ (Cross-Platform)
```bash
g++ -std=c++17 -I./include main.cpp -o sis_cli
./sis_cli
```

---

## Code Quality & Engineering Highlights
- Strict separation of concerns adhering to the **Model-View-Service** architectural pattern.
- Memory safe modern C++ using standard library containers (`std::vector`, `std::string`, `std::unique_ptr`).
- Strongly typed domain models reflecting real-world university registrar workflows.

---

## License
MIT License. Developed for software engineering and academic systems demonstrations.
