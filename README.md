# Smart Attendance System
**Kathmandu University — ENGG 102 | Year I / Semester II**  
Department of Computer Science and Engineering

A real-time facial recognition attendance system built in C++ using OpenCV and Qt.

---

## Team Members
| Name | Roll No. |
|---|---|
| Aaryan Khatri | 43 |
| Shashwot Karki | 36 |
| Subhechha Ghimire | 26 |
| Dilasha Dulal | 18 |
| Prachika Dhaubhadel | 14 |

---

## Before You Clone

You need to install 4 things on your machine before cloning this repo.  
Follow the section for **your operating system** below.

---

## 🪟 Windows Setup

### 1. Install CMake
- Download the **Windows x64 Installer** from https://cmake.org/download/
- During install, select **"Add CMake to the system PATH for all users"**
- Verify: open Command Prompt and run `cmake --version`

### 2. Install Visual Studio 2022 (C++ Compiler)
- Download **Visual Studio Community 2022** (free) from https://visualstudio.microsoft.com/vs/community/
- During install, select the **"Desktop development with C++"** workload only
- This gives you the MSVC compiler that Qt requires on Windows

### 3. Install Qt
- Download the Qt Online Installer from https://www.qt.io/download-qt-installer
- You will need to create a free Qt account
- When selecting components, expand **Qt 6.7.x** and check:
  - ✅ MSVC 2019 64-bit
- Note the install path — default is `C:\Qt\6.7.0\msvc2019_64\`

### 4. Install OpenCV
- Go to https://github.com/opencv/opencv/releases
- Download the latest `opencv-4.x.x-windows.exe`
- Run it — it will ask where to extract. Use `C:\opencv\`
- The important folder inside is `C:\opencv\build\`

### 5. Install SQLite (no installer needed)
- Go to https://www.sqlite.org/download.html
- Under **Source Code**, download `sqlite-amalgamation-xxxxxxx.zip`
- Extract it. You will get two files: `sqlite3.h` and `sqlite3.c`
- Create a folder called `sqlite/` inside the project after cloning and put both files there (see folder structure below)

---

## 🍎 macOS Setup

### 1. Install Homebrew (if you don't have it)
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### 2. Install everything in one command
```bash
brew install cmake qt opencv sqlite
```
This will take 10–20 minutes. Let it finish completely.

### 3. Add Qt to your PATH
```bash
echo 'export PATH="/opt/homebrew/opt/qt/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc
```
> **Intel Mac?** Replace `/opt/homebrew` with `/usr/local` in the line above.

Verify Qt is found:
```bash
qmake --version
```
You should see a Qt version number printed.

---

## Cloning the Repo

Once all installations above are done:

```bash
git clone https://github.com/YOUR_USERNAME/SmartAttendanceSystem.git
cd SmartAttendanceSystem
```

---

## Folder Structure After Cloning

```
SmartAttendanceSystem/
├── CMakeLists.txt
├── README.md
├── sqlite/                  ← CREATE THIS FOLDER (Windows users only)
│   ├── sqlite3.h            ← paste files downloaded from sqlite.org here
│   └── sqlite3.c
├── src/
│   └── main.cpp
└── tests/
    └── webcam_test.cpp
```

> macOS users: SQLite is installed by Homebrew so you do **not** need the `sqlite/` folder.

---

## Building the Project

### Windows
Open the **Developer Command Prompt for VS 2022** (search for it in the Start menu — this is different from regular Command Prompt).

```cmd
cd SmartAttendanceSystem
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH="C:\Qt\6.7.0\msvc2019_64" -DOpenCV_DIR="C:\opencv\build"
cmake --build . --config Release
```

> If your Qt or OpenCV are installed in different folders, adjust the paths accordingly.

### macOS
```bash
cd SmartAttendanceSystem
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH="$(brew --prefix qt)"
cmake --build .
```

---

## Testing Your Setup

### Step 1 — Test OpenCV + Webcam

**Windows:**
```cmd
cmake --build . --target webcam_test --config Release
.\Release\webcam_test.exe
```

**macOS:**
```bash
cmake --build . --target webcam_test
./webcam_test
```

✅ You should see your **webcam feed** open in a window. Press **Q** to close it.  
If this works, OpenCV is installed correctly.

---

### Step 2 — Test Qt Window

**Windows:**
```cmd
.\Release\SmartAttendanceSystem.exe
```

**macOS:**
```bash
./SmartAttendanceSystem
```

✅ You should see a small window that says **"Qt is working!"**  
If this works, everything is set up correctly and you're ready to develop.

---

## Common Errors

**"Qt not found" during cmake (Windows)**  
Double-check the path. Open File Explorer and confirm that this folder exists:  
`C:\Qt\6.7.0\msvc2019_64\lib\cmake\Qt6\`  
Use its parent in `-DCMAKE_PREFIX_PATH`.

**App crashes immediately on Windows**  
Qt DLLs are missing. Run this once:
```cmd
C:\Qt\6.7.0\msvc2019_64\bin\windeployqt.exe .\Release\SmartAttendanceSystem.exe
```

**"opencv_face module not found"**  
This is expected for now. Open `CMakeLists.txt` and comment out the `face` line:
```cmake
# face   ← comment this out for now
```
We will add it later when we reach the face recognition module.

**"Permission denied" running the app (macOS)**
```bash
chmod +x ./SmartAttendanceSystem
./SmartAttendanceSystem
```

**Webcam not opening**  
- Make sure no other app (Zoom, Teams, etc.) is using the camera
- Try changing `cv::VideoCapture cap(0)` to `cap(1)` in `webcam_test.cpp` if you have multiple cameras

---

## Tech Stack

| Purpose | Tool |
|---|---|
| Language | C++17 |
| Computer Vision | OpenCV 4.x |
| GUI Framework | Qt 6 |
| Database | SQLite 3 |
| Build System | CMake |
| Version Control | Git + GitHub |

---

## Need Help?

If you hit an error not listed above, paste the **full error message** into the group chat. Don't just say "it doesn't work" — the exact error text is what helps fix it.
