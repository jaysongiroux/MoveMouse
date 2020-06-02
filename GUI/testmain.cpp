#include <QApplication>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>

int main(int argc, char *argv[ ])
{
    QApplication app(argc, argv);
    QWidget *window = new QWidget;
    // QPushButton *button1 = new QPushButton("One");
    // QPushButton *button2 = new QPushButton("Two");
    // QPushButton *button3 = new QPushButton("Three");
    // QPushButton *button4 = new QPushButton("Four");
    // QPushButton *button5 = new QPushButton("Five");

    // QVBoxLayout *layout = new QVBoxLayout;
    // layout->addWidget(button1);
    // layout->addWidget(button2);
    // layout->addWidget(button3);
    // layout->addWidget(button4);
    // layout->addWidget(button5);

    // window->setLayout(layout);
    // window->show();
    // return app.exec(); 
    QLabel *title = new QLabel("JARVIS Configuration");
    QLabel *opt_label = new QLabel("Optimization: ");
    QCheckBox *PointCloud = new QCheckBox("Enable Point Cloud?");

    QHBoxLayout *mainContainer = new QHBoxLayout;
    QVBoxLayout *options = new QVBoxLayout;

    options->addWidget(title);
    options->addWidget(opt_label);
    options->addWidget(PointCloud);


    mainContainer->addLayout(options);
    window->setLayout(mainContainer);
    window->show();
    return app.exec();

    // jarvis.setWindowTitle("JARVIS");
    // jarvis.resize(800, 400);
    // jarvis.show();
    // return app.exec();



}
