#include <iostream>
#include <vector>
#include <string>
#include <fstream>


using namespace std;

struct student
{
    string name = "name-Error";
    string subject = "subject-Error";
    int n = 0;
    int arr[30];
    int average = 0;
};

struct subject
{
    string name = "ERROR";
    int n = 0;
};

void my_sort(vector<subject>& subjects);


int main()
{
    student students[50];
    ifstream duom("Duomenys.txt");
    ofstream rez("Rezultatai.txt");
    int n;
    duom >> n;
    for (int i = 0; i < n; i++)
    {
        duom >> students[i].name >> students[i].subject >> students[i].n;
        for (int j = 0; j < students[i].n; j++)
        {
            duom >> students[i].arr[j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        int temp = 0;
        for (int j = 0; j < students[i].n; j++)
        {
            temp+= students[i].arr[j];
        }
        students[i].average = temp / students[i].n;
    }

    vector<subject> subjects;

    for (int i = 0; i < n; i++) // filter/count subjects that students voted for and account for not-inmortant student ansvers (avg<9)
    {
        if (students[i].average >= 9)
        {
            bool temp = 1;
            for (int j = 0; j < subjects.size(); j++)
            {
                if (subjects[j].name==students[i].subject)  
                {
                    subjects[j].n++;
                    temp = 0;
                }
            }
            if (temp)
            {
                subject x;
                x.name = students[i].subject;
                x.n++;
                subjects.push_back(x);
            }
        }
    }

    if (subjects.size() == 0) { rez << "Neatitinka vidurkis"; return 0; }

    my_sort(subjects);

    for (int i = 0; i < subjects.size(); i++)
    {
        rez << subjects[i].name << ' ' << subjects[i].n << '\n';
        for (int j = 0; j < n; j++)
        {
            if (students[j].subject == subjects[i].name && students[j].average >= 9)
            {
                rez << students[j].name << '\n';
            }
        }
    }

    duom.close();
    rez.close();
    return 0;
}

void my_sort(vector<subject>& subjects)
{
    for (int i = 0; i < subjects.size(); i++)
    {
        for (int j = i; j < subjects.size(); j++)
        {
            if (subjects[i].n == subjects[j].n)
            {
                if (subjects[i].name > subjects[j].name)
                {
                    swap(subjects[i], subjects[j]);
                }
            }
            else if(subjects[i].n < subjects[j].n)
            {
                swap(subjects[i], subjects[j]);
            }
        }
    }
}
