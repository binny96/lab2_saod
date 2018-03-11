#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <QFile>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <QLineEdit>
#include <QMessageBox>
#include <QTextStream>

#define n 10000

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

}


//простое
void SimpleSort(char *name)
{
    int a1, a2, k, i, j, kol;
    FILE *f, *f1, *f2;
    kol = 0;
    if ((f = fopen(name,"r")) == NULL)
        printf("\nИсходный файл не может быть прочитан...");
    else
    {
        while ( !feof(f) )
        {
            fscanf(f,"%d",&a1);
            kol++;
        }
        fclose(f);
    }
    k = 1;
    while ( k < kol )
    {
        f = fopen(name,"r");
        f1 = fopen("Simple1","w");
        f2 = fopen("Simple2","w");
        if (!feof(f))
            fscanf(f,"%d",&a1);
        while (!feof(f))
        {
            for ( i = 0; i < k && !feof(f) ; i++ )
            {
                fprintf(f1,"%d ",a1);
                fscanf(f,"%d",&a1);
            }
            for ( j = 0; j < k && !feof(f) ; j++ )
            {
                fprintf(f2,"%d ",a1);
                fscanf(f,"%d",&a1);
            }
        }
        fclose(f2);
        fclose(f1);
        fclose(f);
        f = fopen(name,"w");
        f1 = fopen("Simple1","r");
        f2 = fopen("Simple2","r");
        if (!feof(f1))
            fscanf(f1,"%d",&a1);
        if (!feof(f2))
            fscanf(f2,"%d",&a2);
        while (!feof(f1) && !feof(f2))
        {
            i = 0;
            j = 0;
            while (i < k && j < k && !feof(f1) && !feof(f2))
            {
                if ( a1 < a2 )
                {
                    fprintf(f,"%d ",a1);
                    fscanf(f1,"%d",&a1);
                    i++;
                }
                else
                {
                    fprintf(f,"%d ",a2);
                    fscanf(f2,"%d",&a2);
                    j++;
                }
            }
            while (i < k && !feof(f1))
            {
                fprintf(f,"%d ",a1);
                fscanf(f1,"%d",&a1);
                i++;
            }
            while (j < k && !feof(f2))
            {
                fprintf(f,"%d ",a2);
                fscanf(f2,"%d",&a2);
                j++;
            }
        }
        while (!feof(f1))
        {
            fprintf(f,"%d ",a1);
            fscanf(f1,"%d",&a1);
        }
        while ( !feof(f2) )
        {
            fprintf(f,"%d ",a2);
            fscanf(f2,"%d",&a2);
        }
        fclose(f2);
        fclose(f1);
        fclose(f);
        k *= 2;
    }
    remove("Simple1");
    remove("Simple2");
}

bool End_Range(FILE * f)
{
    int tmp;
    tmp = fgetc(f);
    tmp = fgetc(f);
    if (tmp != '\'')
        fseek(f,-2,1);
    else
        fseek(f,1,1);
    return tmp == '\'' ? true : false;
}

//естественное
void NaturalSort(char *name)
{
    int s1, s2, a1, a2, mark;
    FILE *f, *f1, *f2;
    s1 = s2 = 1;
    while (s1 > 0 && s2 > 0)
    {
        mark = 1;
        s1 = 0;
        s2 = 0;
        f = fopen(name,"r");
        f1 = fopen("Natural1","w");
        f2 = fopen("Natural2","w");
        fscanf(f,"%d",&a1);
        if (!feof(f))
        {
            fprintf(f1,"%d ",a1);
        }
        if (!feof(f))
            fscanf(f,"%d",&a2);
        while (!feof(f))
        {
            if (a2 < a1)
            {
                switch (mark)
                {
                case 1:
                    {
                        fprintf(f1,"' ");
                        mark = 2;
                        s1++;
                        break;
                    }
                case 2:
                    {
                        fprintf(f2,"' ");
                        mark = 1;
                        s2++;
                        break;
                    }
                }
            }
            if (mark == 1)
            {
                fprintf(f1,"%d ",a2);
                s1++;
            }
            else
            {
                fprintf(f2,"%d ",a2);
                s2++;
            }
            a1 = a2;
            fscanf(f,"%d",&a2);
        }
        if (s2 > 0 && mark == 2)
        {
            fprintf(f2,"'");
        }
        if (s1 > 0 && mark == 1)
        {
            fprintf(f1,"'");
        }
        fclose(f2);
        fclose(f1);
        fclose(f);
        f = fopen(name,"w");
        f1 = fopen("Natural1","r");
        f2 = fopen("Natural2","r");
        if (!feof(f1))
            fscanf(f1,"%d",&a1);
        if (!feof(f2))
            fscanf(f2,"%d",&a2);
        bool file1, file2;
        while (!feof(f1) && !feof(f2))
        {
            file1 = file2 = false;
            while (!file1 && !file2)
            {
                if ( a1 <= a2 )
                {
                    fprintf(f,"%d ",a1);
                    file1 = End_Range(f1);
                    fscanf(f1,"%d",&a1);
                }
                else
                {
                    fprintf(f,"%d ",a2);
                    file2 = End_Range(f2);
                    fscanf(f2,"%d",&a2);
                }
            }
            while (!file1)
            {
                fprintf(f,"%d ",a1);
                file1 = End_Range(f1);
                fscanf(f1,"%d",&a1);
            }
            while (!file2)
            {
                fprintf(f,"%d ",a2);
                file2 = End_Range(f2);
                fscanf(f2,"%d",&a2);
            }
        }
        file1 = file2 = false;
        while (!file1 && !feof(f1))
        {
            fprintf(f,"%d ",a1);
            file1 = End_Range(f1);
            fscanf(f1,"%d",&a1);
        }
        while (!file2 && !feof(f2))
        {
            fprintf(f,"%d ",a2);
            file2 = End_Range(f2);
            fscanf(f2,"%d",&a2);
        }
        fclose(f2);
        fclose(f1);
        fclose(f);
    }
    remove("Natural1");
    remove("Natural2");
}


void MainWindow::on_pushButton_clicked()
{
    if (ui->radioButton->isChecked())
    {
        QFile file("C:/Qt/2010.05/qt/lab2saod-build-desktop/f1.txt");
        if (!file.open(QIODevice::ReadOnly))
            QMessageBox::information(0, "info", file.errorString());
        QTextStream in(&file);
        ui->textBrowser->setText((in.readAll()));
    }
    if (ui->radioButton_2->isChecked())
    {
        QFile file("C:/Qt/2010.05/qt/lab2saod-build-desktop/f2.txt");
        if (!file.open(QIODevice::ReadOnly))
            QMessageBox::information(0, "info", file.errorString());
        QTextStream in(&file);
        ui->textBrowser->setText((in.readAll()));
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if (ui->radioButton->isChecked())
    {
        clock_t start = clock();
        SimpleSort ("f1.txt");
        clock_t end = clock();
        double smTime = double(end - start) / CLOCKS_PER_SEC;
        QFile file("C:/Qt/2010.05/qt/lab2saod-build-desktop/f1.txt");
        if (!file.open(QIODevice::ReadOnly))
            QMessageBox::information(0, "info", file.errorString());
        QTextStream in(&file);
        ui->textBrowser_2->setText((in.readAll()));
        ui->textBrowser_3->setText("File: f1.txt\nSort type: simple merger\nData type: number\nNumber of elements: " +
                                   QString::number(n) + " \nTime of sort: " + QString::number(smTime, 'f', 5));
    }
    if (ui->radioButton_2->isChecked())
    {
        clock_t start_1 = clock();
        NaturalSort("f2.txt");
        clock_t end_1 = clock();
        double nmTime = double(end_1 - start_1) / CLOCKS_PER_SEC;
        QFile file("C:/Qt/2010.05/qt/lab2saod-build-desktop/f2.txt");
        if (!file.open(QIODevice::ReadOnly))
            QMessageBox::information(0, "info", file.errorString());
        QTextStream in(&file);
        ui->textBrowser_2->setText((in.readAll()));
        ui->textBrowser_3->setText("File: f2.txt\nSort type: natural merger\nData type: number\nNumber of elements: " +
                                   QString::number(n) + " \nTime of sort: " + QString::number(nmTime, 'f', 5));
    }
}
