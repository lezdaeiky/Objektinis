#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <algorithm>
#include <limits>

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
float mfinal = 0;
int number_of_lines = 0;

void printArra(int number_of_lines, int nd_count);
void printArr(bool isInputing);
bool stud_sroter(student const& lhs, student const& rhs);
void ReadPrintSortFile();
void FillArr();

int main()
{
    bool choice;

    for (;;) 
    {
        cout << "Ivesti ranka(0) ar skaityti is failo(1) : ";
        if (cin >> choice) 
        {
            if(choice)
                ReadPrintSortFile();
            else
            {
                FillArr();
                printArr(true);
            }
            break;
        } 
        else 
        {
            cout << "neteisinga Ivestis" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return 0;
}

void ReadPrintSortFile()
{
    ifstream f;
    f.open ("data.txt");
    int nd_count;

    string line;

    while(getline(f, line))
        number_of_lines++;

    f.close();

    f.open("data.txt");

    while(true)
    {
        string info;
        f>>info;
        if(info!="Egz.")
        {
            nd_count++;    
        }
        else
        {
            nd_count -= 2;

            for(int k = 0; k<number_of_lines-1; k++)
            {
                stud.push_back(student());
                f >> stud[k].name >> stud[k].surname;
                int grade;
                for(int j = 0; j < nd_count; j++)
                {
                    f >> grade; stud[k].homework_grades.push_back(grade);          
                }
                f>>stud[k].exam_grade;
            }

            break;       
        }
    }

    f.close();

    sort(stud.begin(), stud.end(), &stud_sroter); 

    printArr(false);
}

void FillArr()
{
    string choice;
    int cnt;

    cout<<"Iveskite studentu skaiciu: ";
    cin>>cnt;

    for(int i = 0; i < cnt; i++)
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
            for(int i = 0; i<cnt; i++)
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
            for(int i = 0; i < cnt; i++)
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

bool stud_sroter(student const& lhs, student const& rhs) 
{
    if (lhs.name != rhs.name)
    {
            return lhs.name < rhs.name;
    }
}

void calculateFinal(int num)
{
    float sum = 0;
    int hm_size = stud[num].homework_grades.size();

    for(int i = 0; i < hm_size; i++)
    {
        sum+=stud[num].homework_grades[i];
    }

    if(final_choice == 2)
    {
        mfinal = ( sum / hm_size ) * 0.4 + (0.6 * stud[num].exam_grade);
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

void printArr(bool isInputing)
{
    if(isInputing)
        number_of_lines = stud.size() + 1;

    while(true)
    {
        cout<<"Skaiciuoti naudojant mediana(1) ar formule(2)? ";
        cin>>final_choice;
        if(!cin.fail())
            break;
        else
            cout<<"Bloga Ivestis";
    }

    cout<<"Vardas"<<setw(15)<<"Pavarde"<<setw(44)<<"Galutinis (Vid.) / Galutinis (Med.)"<<endl;
    cout<<"------------------------------------------------------------------"<<endl;

    for(int i = 0; i < number_of_lines-1; i++)
    {
        cout<<setw(14)<<left<<stud[i].name<<setw(16)<<left<<stud[i].surname;
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