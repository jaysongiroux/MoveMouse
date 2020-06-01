#include <QApplication>
#include <QLabel>
#include <QWidget>

int main(int argc, char *argv[ ])
{

QApplication app(argc, argv);
QLabel hello("<center>Welcome to my first Qt program</center>");
hello.setWindowTitle("My First Qt Program");
hello.resize(400, 400);
hello.show();
return app.exec();

}
