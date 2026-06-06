# Hospital Remake

![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Qt](https://img.shields.io/badge/Qt-Widgets-41CD52?style=for-the-badge&logo=qt&logoColor=white)
![SQLite](https://img.shields.io/badge/SQLite-Database-003B57?style=for-the-badge&logo=sqlite&logoColor=white)
![Python](https://img.shields.io/badge/Python-Dashboard_Server-3776AB?style=for-the-badge&logo=python&logoColor=white)

Hospital Remake is a Qt/C++ hospital management desktop application backed by SQLite databases. It manages doctors, nurses, patients, diseases, admin accounts, staff assignment, patient state tracking, and a small live web dashboard that exposes exported patient data through a Python HTTP server.

The project is built around a desktop control panel, but it also includes a Chernobyl/Pripyat themed browser dashboard for monitoring the exported patient registry.

## Contents

- [Features](#features)
- [Application Flow](#application-flow)
- [Database Design](#database-design)
- [Web Dashboard](#web-dashboard)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Build And Run](#build-and-run)
- [Configuration](#configuration)
- [Notes And Current Limitations](#notes-and-current-limitations)
- [Why did I create this](#why-did-i-create-this)

## Features

### Authentication

- Admin login using an ID and password stored in `hospital/databases/admin.db`.
- Admin registration with a unique numeric ID, password confirmation, and Gmail validation.
- Password recovery through Gmail SMTP.
- Basic SQL injection text detection for login fields.
- Suspicious login attempts are appended to `hospital/reports.txt`.

### Database Import

- The app requires a hospital SQLite database to be imported before login.
- Database import uses Native File Dialog and accepts `.db` files.
- The imported database is validated by checking that SQLite can read its metadata.
- After a successful import, the app starts exporting patient data for the web dashboard.

### Doctor Management

- Add doctors with name, age, sex, level, and months-left fields.
- Initialize each doctor's nurse count automatically.
- List doctors in a table view.
- Search doctors by ID.
- Modify doctor records.
- Delete doctors after choosing another doctor to inherit supervised nurses.
- Track how many nurses are assigned to each doctor.

### Nurse Management

- Add nurses with name, age, sex, and supervising doctor ID.
- Validate that the supervising doctor exists before adding a nurse.
- Initialize patient, cured, and dead counters automatically.
- List nurses in a table view.
- Search nurses by ID.
- Modify nurse records.
- Delete nurses after choosing another nurse to inherit assigned patients.
- Track patient, cured, and dead counts per nurse.

### Patient Management

- Add patients with name, age, sex, disease ID, state, payment, and assigned nurse ID.
- Validate that the assigned nurse exists.
- Validate that the disease ID exists.
- List patients in a table view.
- Search patients by ID.
- Modify patient records.
- Delete patients with a final state selection: cured or dead.
- Update the assigned nurse's cured/dead counters when a patient is removed.

### Live Data Export

- The C++ app refreshes dashboard data every 5 seconds with a `QTimer`.
- Patient records are exported into `hospital/data.json`.
- Exported data includes the patient list, total patient count, critical patient count, deceased count, and dashboard stats placeholders.

### Web Dashboard

- `hospital/website.py` starts a local HTTP server on port `8000`.
- `/` serves `hospital/index.html`.
- `/patients` serves the current `hospital/data.json` as JSON.
- The browser page polls `/patients` every 10 seconds.
- The dashboard displays total patients, dead patients, total payment, male/female patient counts, a patient table, and a live/offline status indicator.

## Application Flow

1. Start the Qt desktop application.
2. Import a valid hospital database with the pull/import database button.
3. Log in with an admin account or register a new one.
4. Use the main menu to manage doctors, nurses, and patients.
5. Run the Python dashboard server from the `hospital` folder.
6. Open `http://localhost:8000` to view the exported patient registry.

## Database Design

The project uses two SQLite databases.

### Main Hospital Database

Path:

```text
hospital/databases/database.db
```

Bundled row counts at the time this README was written:

| Table | Rows |
| --- | ---: |
| `doctors` | 1 |
| `nurses` | 5 |
| `patients` | 6 |
| `diseases` | 1 |

#### `doctors`

| Column | Type | Description |
| --- | --- | --- |
| `id` | INTEGER | Primary key |
| `name` | TEXT | Doctor name |
| `age` | INTEGER | Doctor age |
| `sex` | TEXT | Doctor sex |
| `level` | TEXT | Doctor rank/level |
| `months_left` | INTEGER | Remaining months value used by the app |
| `nurses_count` | INTEGER | Number of supervised nurses |

#### `nurses`

| Column | Type | Description |
| --- | --- | --- |
| `id` | INTEGER | Primary key |
| `name` | TEXT | Nurse name |
| `age` | INTEGER | Nurse age |
| `sex` | TEXT | Nurse sex |
| `supervisor` | INTEGER | Doctor ID supervising this nurse |
| `patients_count` | INTEGER | Number of assigned patients |
| `cured` | INTEGER | Count of cured patients |
| `dead` | INTEGER | Count of deceased patients |

Foreign key:

```text
nurses.supervisor -> doctors.id
```

#### `patients`

| Column | Type | Description |
| --- | --- | --- |
| `id` | INTEGER | Primary key |
| `name` | TEXT | Patient name |
| `age` | INTEGER | Patient age |
| `sex` | TEXT | Patient sex |
| `disease` | INTEGER | Disease ID |
| `state` | TEXT | Patient state, such as stable or critical |
| `payment` | INTEGER | Payment amount/value |
| `nurse` | INTEGER | Assigned nurse ID |

Foreign keys:

```text
patients.nurse -> nurses.id
patients.disease -> diseases.id
```

#### `diseases`

| Column | Type | Description |
| --- | --- | --- |
| `id` | INTEGER | Primary key |
| `name` | TEXT | Disease name |
| `desc` | TEXT | Disease description |

### Admin Database

Path:

```text
hospital/databases/admin.db
```

Bundled row count at the time this README was written:

| Table | Rows |
| --- | ---: |
| `admin` | 5 |

#### `admin`

| Column | Type | Description |
| --- | --- | --- |
| `id` | INTEGER | Admin ID |
| `passwd` | TEXT | Admin password |
| `gmail` | TEXT | Admin Gmail address |

The primary key is composed of:

```text
id, gmail
```

## Web Dashboard

The dashboard is made of:

| File | Purpose |
| --- | --- |
| `hospital/index.html` | Browser UI for the patient registry |
| `hospital/website.py` | Local HTTP server |
| `hospital/data.json` | Exported data generated by the Qt app |
| `hospital/server.cpp` | C++ exporter that builds the JSON payload |

Run it from inside the `hospital` directory:

```bash
cd hospital
python3 website.py
```

Then open:

```text
http://localhost:8000
```

The `/patients` endpoint returns the JSON payload used by the dashboard:

```text
http://localhost:8000/patients
```

## Project Structure

```text
hospital-remake/
|-- .gitattributes
|-- readme.md
`-- hospital/
    |-- CMakeLists.txt
    |-- main.cpp
    |-- mainwindow.cpp
    |-- mainwindow.h
    |-- mainwindow.ui
    |-- classes.h
    |-- database.cpp
    |-- database.h
    |-- externals.cpp
    |-- externals.h
    |-- server.cpp
    |-- server.h
    |-- smtp.cpp
    |-- smtp.h
    |-- website.py
    |-- index.html
    |-- data.json
    |-- reports.txt
    |-- m.env
    |-- databases/
    |   |-- admin.db
    |   `-- database.db
    `-- nlohmann/
        `-- json.hpp
```

## Requirements

### C++ Desktop App

- CMake 3.16 or newer
- C++17 compiler
- Qt 5 or Qt 6 with Widgets and Network
- SQLite3 development package
- GTK 3 development package
- PkgConfig
- Native File Dialog library/header
- `nlohmann/json.hpp`

### Python Dashboard

- Python 3
- No external Python packages are required.

## Build And Run

From the Qt/CMake project folder:

```bash
cd hospital
cmake -S . -B build
cmake --build build
./build/hospital
```

If you use Qt Creator, open `hospital/CMakeLists.txt`, configure a kit, and run the `hospital` target.

## Configuration

### Gmail SMTP Password

The SMTP helper reads a Gmail app password/API key from:

```text
hospital/m.env
```

Expected format:

```env
API_KEY=your_gmail_app_password_here
```

The sender address is currently defined in `hospital/smtp.h`.

### GitHub Language Stats

The repository includes:

```gitattributes
/hospital/nlohmann/** linguist-vendored
```

This tells GitHub Linguist to treat the bundled `nlohmann` library as vendored code so it does not distort the language breakdown.

## Notes And Current Limitations

- Some paths in the C++ source are absolute paths pointing to `/home/bro/my-creations/hospital-remake/...`.
- The app expects the admin database at `hospital/databases/admin.db`.
- The main hospital database is selected through the desktop import flow.
- The web dashboard expects `website.py`, `index.html`, and `data.json` to be in the same working directory.
- The exported dashboard stats currently include placeholder ward/radiation labels from `server.cpp`.
- Passwords are stored as plain text in the admin SQLite database.
- The project is currently Linux-oriented because of the GTK/NFD setup and local absolute paths.

## Why did I create this

Qt is well known for professional apps developement so i had to learn it , my first project in it so i know it's a bit simple but 
i planned more complex project in the future.repo closed in 6 juin 2026
