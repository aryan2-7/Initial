# Smart Attendance System — Windows Setup Guide

> **For:** Year I / Semester II Computer Engineering Project  
> **Dept:** Computer Science and Engineering, Kathmandu University  

---


#Read through each part once before installations as some programs need to be added to path, so follow this precicely



## Prerequisites Overview

| Tool | Purpose |
|---|---|
| CMake | Build system (works cross-platform) |
| Visual Studio 2022 | C++ compiler (MSVC) |
| Qt 6 | GUI framework |
| OpenCV | Computer vision / face detection |
| SQLite | Database (bundled directly in project) |

---

## Step 1 — Install CMake

Download and install from: https://cmake.org/download/

Choose the **Windows x64 Installer** (`.msi` file). During installation, select **"Add CMake to the system PATH"** when asked.

Verify it worked — open **Command Prompt** and run:

```cmd
cmake --version
```

---

## Step 2 — Install a C++ Compiler (Visual Studio)

Qt on Windows requires MSVC (Microsoft's compiler). Download **Visual Studio Community 2022** (free):

https://visualstudio.microsoft.com/vs/community/

During installation, select the workload **"Desktop development with C++"** — that's the only one you need.

---

## Step 3 — Install Qt

Go to: https://www.qt.io/download-qt-installer

Download the **Qt Online Installer**. You'll need to create a free Qt account.

During installation:
- Select **Qt 6.7** (or the latest Qt 6.x available)
- Under it, check **MSVC 2019 64-bit** (works with VS 2022 too)
- Also check **Qt 5 Compatibility Module** just in case

Remember where Qt gets installed — the default is usually:

```
C:\Qt\6.7.0\msvc2019_64\
```

---

## Step 4 — Install OpenCV

Download the prebuilt Windows release from:
https://github.com/opencv/opencv/releases

Look for the latest `opencv-4.x.x-windows.exe` file. Run it — it's a self-extracting archive. Extract it somewhere simple like:

```
C:\opencv\
```

Inside you'll find `C:\opencv\build\` — that's the important folder.

---

## Step 5 — Install SQLite

SQLite on Windows is easiest as a bundled file (no installer needed).

Go to: https://www.sqlite.org/download.html

Download **"sqlite-amalgamation-xxxxxxx.zip"** under the *Source Code* section. Extract it and copy these two files into your project:

```
SmartAttendanceSystem/
└── sqlite/
    ├── sqlite3.h
    └── sqlite3.c
```

> The `CMakeLists.txt` already handles this automatically — no extra configuration needed.

---

## Step 6 — Set up your Project Folder

Make sure your project looks like this before continuing:

```
SmartAttendanceSystem/
├── CMakeLists.txt
├── sqlite/
│   ├── sqlite3.h
│   └── sqlite3.c
├── src/
│   └── main.cpp
└── tests/
    └── webcam_test.cpp
```

---

## Step 7 — Open the Project in VS Code

Install the following VS Code extensions:
- **C/C++** (by Microsoft)
- **CMake Tools** (by Microsoft)

Then open your project folder in VS Code. When it opens, CMake Tools will ask **"Select a Kit"** — choose **Visual Studio Community 2022 Release - amd64**.

---

## Step 8 — Build via Command Prompt

Open the **"Developer Command Prompt for VS 2022"** (search for it in the Start menu — it's different from regular Command Prompt; it sets up the MSVC compiler automatically).

Navigate to your project and build:

```cmd
cd SmartAttendanceSystem
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH="C:\Qt\6.7.0\msvc2019_64" -DOpenCV_DIR="C:\opencv\build"
cmake --build . --config Release
```

> **Note:** Adjust the paths if your Qt or OpenCV are installed in different locations.

---

## Step 9 — Run the Webcam Test First

```cmd
cmake --build . --target webcam_test --config Release
.\Release\webcam_test.exe
```

You should see your webcam feed pop up in a window. Press **Q** to close it.

If this works, OpenCV is installed correctly.

---

## Step 10 — Run the Main Qt App

```cmd
.\Release\SmartAttendanceSystem.exe
```

You should see a small window saying **"Qt is working!"**

If you see this, Qt is installed and linked correctly. You're ready to start development.

---

## Troubleshooting

### "Qt not found" during cmake
Double-check the path. Open File Explorer and confirm that this folder exists:
```
C:\Qt\6.7.0\msvc2019_64\lib\cmake\Qt6\
```
Use the parent path in `-DCMAKE_PREFIX_PATH`. If your version number differs, adjust accordingly.

### App opens then immediately crashes
Qt DLLs are missing next to the `.exe`. Run this to copy them automatically:
```cmd
C:\Qt\6.7.0\msvc2019_64\bin\windeployqt.exe .\Release\SmartAttendanceSystem.exe
```
Then try running the app again.

### "opencv_face module not found"
This is expected until you install `opencv_contrib`. For now, comment out `face` in `CMakeLists.txt`:
```cmake
find_package(OpenCV REQUIRED COMPONENTS
    core
    imgproc
    highgui
    videoio
    objdetect
    # face   <- comment this out for now
)
```

### "Permission denied" or antivirus blocking the build
Windows Defender sometimes blocks newly compiled `.exe` files. Add your `build/` folder to the Windows Defender exclusion list:
**Settings → Windows Security → Virus & threat protection → Exclusions → Add folder**

---

## Quick Reference — Useful Commands

| Action | Command |
|---|---|
| Configure the project | `cmake .. -DCMAKE_PREFIX_PATH="C:\Qt\6.7.0\msvc2019_64" -DOpenCV_DIR="C:\opencv\build"` |
| Build everything | `cmake --build . --config Release` |
| Build webcam test only | `cmake --build . --target webcam_test --config Release` |
| Run webcam test | `.\Release\webcam_test.exe` |
| Run main app | `.\Release\SmartAttendanceSystem.exe` |
| Copy Qt DLLs | `C:\Qt\6.7.0\msvc2019_64\bin\windeployqt.exe .\Release\SmartAttendanceSystem.exe` |
