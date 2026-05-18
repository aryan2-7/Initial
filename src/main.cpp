/**
 * main.cpp
 * ────────
 * Entry point for the Smart Attendance System.
 * For now this just opens a blank Qt window to confirm
 * Qt is installed and linked correctly.
 *
 * Place this file in:  src/main.cpp
 */

#include <QApplication>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Simple placeholder window
    QWidget window;
    window.setWindowTitle("Smart Attendance System");
    window.setMinimumSize(400, 200);

    QVBoxLayout *layout = new QVBoxLayout(&window);
    QLabel *label = new QLabel("Qt is working!\nReplace this with the real UI.");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    window.show();

    return app.exec();
}
