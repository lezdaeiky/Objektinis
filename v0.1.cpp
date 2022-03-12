#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <time.h>
#include <cstdlib>

using namespace std;

struct student
{
    string name;
    string surname;
    vector<float> homework_grades;
    float exam_grade;
};

vector<student> stud;
int count = 0;

int final_choice;

void FillArr();
void printArr();
void calculateFinal();

float mfinal = 0;

int main()
{
    FillArr();
    printArr();
    return 0;
}

void FillArr()
{
    string choice;

    cout<<"Iveskite studentu skaiciu: ";
    cin>>count;

    for(int i = 0; i < count; i++)
    {
        stud.push_back(student());

        cout<<"Iveskite mokinio ["<<i+1<<"] varda: ";
        cin>>stud[i].name;

        cout<<"Iveskite mokinio ["<<i+1<<"] Pavarde: ";
        cin>>stud[i].surname;
        cout<<endl;
    }

    cout<<"Ar mokinio ivertinimus generuoti atsitiktinai? (y/n)";

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
            break;
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
    int hm_size = stud[num].homework_grades.size();

    if(final_choice == 2)
    {
        mfinal = 0.4 * sum / hm_size + 0.6 * stud[num].exam_grade;
    }

    else if(final_choice == 1)
    {
        vector <float> arr_temp;
        arr_temp = stud[num].homework_grades;
        arr_temp.push_back(stud[num].exam_grade);

        int arr_s = arr_temp.size();

        if(arr_s % 2 == 0)
        {
            mfinal = 0.5*(arr_temp[arr_s/2 - 1]+arr_temp[arr_s/2]);
        }
        else
        {
            mfinal = (arr_temp[arr_s/2 - 0.5]);
        }
    }
}

void printArr()
{
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
            cout<<setw(19)<<left<<setprecision(2)<<fixed<<mfinal<<setw(19)<<left<<"xx.yy";
        }
        else if(final_choice == 1)
        {
            cout<<setw(19)<<left<<"xx.yy"<<setw(19)<<left<<setprecision(2)<<fixed<<mfinal;
        }
        mfinal = 0;
        cout<<endl;
    }
}
