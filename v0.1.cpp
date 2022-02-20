#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include<time.h>

using namespace std;

struct student
{
    string name;
    string surname;
    vector<float> homework_grades;
    float exam_grade;
};

vector<student> stud;

int final_choice;

void FillArr();
void printArr();
void calculateFinal();

float final = 0;

int main()
{
    FillArr();
    printArr();
    return 0;
}

void FillArr()
{
    string choice;

    int count;

    cout<<"Iveskite studentu skaiciu: ";
    cin>>count;

    for(int i = 0; i < count; i++)
    {
        stud.push_back(student());

        cout<<"Iveskite mokinio varda: ";
        cin>>stud[i].name;

        cout<<"Iveskite mokinio Pavarde: ";
        cin>>stud[i].surname;
    }

    cout<<"Ar mokinio ivertinimus generuoti atsitiktinai? (y/n)";

    int pazimys;

    while(true)
    {
        cin>>choice;

        if(choice == "n")
        {
            for(int i = 0; i<count; i++)
            {
                int grade;
                cout<<"iveskite "<<stud[i].name<<" egzamino pazymi: ";
                cin>>stud[i].exam_grade;
                cout<<"iveskite "<<stud[i].name<<" namu darbu pazymi: ";
                cin>>grade;
                stud[i].homework_grades.push_back(grade);
                while(true)
                {
                    cout<<"Ar norite ivesti dar balu? (y/n) ";
                    cin>>choice;
                    if(choice == "y")
                    {
                        cout<<"iveskite "<<stud[i].name<<"  namu darbu pazymi: ";
                        cin>>grade;
                        stud[i].homework_grades.push_back(grade);                 
                    }
                    else
                    {
                        break;
                    }
                }            
            }
        }
        else if(choice == "y")
        {
            int grade;
            srand(time(NULL));
            for(int i = 0; i < count; i++)
            {
                stud[i].exam_grade = rand() % 10 + 1;
                for(int j = 0; j < rand()%10+1; j++)
                {   
                    grade = rand() % 10 + 1;
                    stud[i].homework_grades.push_back(grade);
                }               
            }
            break;
        }
        else
        {
            cout<<"Bloga ivestis, bandyti is naujo (y/n): ";
        }
    }
}

void calculateFinal(int i)
{
    int num = i;
    float sum = 0;

    for(int j=0; j<stud[num].homework_grades.size(); j++)
    {
        sum+=stud[num].homework_grades[j];
    }

    if(final_choice == 2)
    {
        final = 0.4 * sum / stud[num].homework_grades.size() + 0.6 * stud[num].exam_grade;
    }

    else if(final_choice == 1)
    {
        final = 0.5*(sum / stud[num].homework_grades.size() + stud[num].exam_grade);
    }
}

void printArr()
{  
    int count = 2;

    while(true)
    {
        cout<<"Skaiciuoti naudojant mediana(1) ar formule(2)? ";
        cin>>final_choice;
        if(!cin.fail())
            break;
        else
            cout<<"Bloga Ivestis";
    }
    


    cout<<"Pavarde"<<setw(10)<<"Vardas"<<setw(44)<<"Galutinis (Vid.) / Galutinis (Med.)"<<endl;
    cout<<"--------------------------------------------------------------"<<endl;
    
    for(int i = 0; i < count; i++)
    {
        cout<<setw(11)<<left<<stud[i].name<<setw(15)<<left<<stud[i].surname;
        calculateFinal(i);
        if(final_choice == 2)
        {
            cout<<setw(19)<<left<<setprecision(2)<<fixed<<final<<setw(19)<<left<<"xx.yy";      
        }
        else if(final_choice == 1)
        {
            cout<<setw(19)<<left<<"xx.yy"<<setw(19)<<left<<setprecision(2)<<fixed<<final;   
        }
        final = 0;
        cout<<endl;
    }
}
