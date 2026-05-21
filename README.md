# Smart Attendance System
**Kathmandu University — ENGG 102 | Year I / Semester II**  
Department of Computer Science and Engineering

A real-time facial recognition attendance system built in C++ using OpenCV and Qt.

---

## Team Members
| Name | Roll No. |
|---|---|
| Aryan Khatri | 43 |
| Shashwot Karki | 36 |
| Subhechha Ghimire | 26 |
| Dilasha Dulal | 18 |
| Prachika Dhaubhadel | 14 |

---

## Before You Clone

You need to install 4 things on your machine before cloning this repo.

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

## Cloning the Repo

Once all installations above are done, open the **Developer Command Prompt for VS 2022** (search for it in the Start menu) or you can use Powershell / cmd and run:

```cmd
git clone https://github.com/aryan2-7/Initial.git
cd Initial
```

---

## Folder Structure After Cloning

```
Initial/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── sqlite/                  ← CREATE THIS FOLDER yourself
│   ├── sqlite3.h            ← paste the two files from sqlite.org here
│   └── sqlite3.c
├── src/
│   └── main.cpp
└── tests/
    └── webcam_test.cpp
```

> The `sqlite/` folder is not in the repo — you create it yourself and paste the two files you downloaded in Step 5.
> Only windows uses need to make this file, macOS is too cool for all this

---

## Building the Project

Open the **Developer Command Prompt for VS 2022** (not regular Command Prompt).

```cmd
cd Initial
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH="C:\Qt\6.7.0\msvc2019_64" -DOpenCV_DIR="C:\opencv\build"
cmake --build . --config Release
```

> If your Qt or OpenCV were installed in different folders, adjust the paths in the command above accordingly.

---

## Testing Your Setup

### Step 1 — Test OpenCV + Webcam

```cmd
cmake --build . --target webcam_test --config Release
.\Release\webcam_test.exe
```

✅ You should see your **webcam feed** open in a window. Press **Q** to close it.  
If this works, OpenCV is installed and linked correctly.

---

### Step 2 — Test the Qt Window

```cmd
.\Release\SmartAttendanceSystem.exe
```

✅ You should see a small window that says **"Qt is working!"**  
If both steps pass, your setup is complete and you are ready to develop.

---

## Common Errors

**"Qt not found" during cmake**  
Double-check the path. Open File Explorer and confirm this folder exists:  
`C:\Qt\6.7.0\msvc2019_64\lib\cmake\Qt6\`  
Use its parent folder in `-DCMAKE_PREFIX_PATH`.

**App opens then immediately crashes**  
Qt DLLs are missing next to the .exe. Run this once:
```cmd
C:\Qt\6.7.0\msvc2019_64\bin\windeployqt.exe .\Release\SmartAttendanceSystem.exe
```
Then try running the app again.

**"opencv_face module not found"**  
This is expected for now. Open `CMakeLists.txt` and comment out the `face` line:
```cmake
# face   ← comment this out for now
```
We will add it later when we reach the face recognition module.

**Webcam not opening**  
- Make sure no other app (Zoom, Teams, etc.) is using the camera
- Try changing `cv::VideoCapture cap(0)` to `cap(1)` in `tests/webcam_test.cpp` if you have multiple cameras

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

If you hit an error not listed above, paste the **full error message** into the group chat.  
Aryan the Great will help you our or js ask an AI lowkey
