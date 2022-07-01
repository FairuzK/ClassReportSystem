#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

class student{
    char name[30];
    int rollno;
    char grade;
    int english,math,science,language,computerSkills;
    double average;

public:
    void getdata();
    void showdata() const;
    void calculate();
    int retrollno() const;
};

void student::calculate(){
    average=(math+english+science+language+computerSkills)/5.0;
    if(average>=80) grade='A';
    else if(average>=70) grade='B';
    else if(average>=60) grade='C';
    else if(average>=50) grade='E';
    else grade='F';
}
void student::getdata(){
    cout<<"\tEnter Student Roll Number: ";
    cin>>rollno;
    cout<<"\tEnter Student Name: ";
    cin.ignore();
    cin.getline(name,30);
    cout<<"\tEnter Math Marks: ";
    cin>>math;
    cout<<"\tEnter English Marks: ";
    cin>>english;
    cout<<"\tEnter Science Marks: ";
    cin>>science;
    cout<<"\tEnter Computer Marks: ";
    cin>>computerSkills;
    cout<<"\tEnter Language Marks: ";
    cin>>language;
    calculate();
    system("cls");
}
void student::showdata()const {
    cout<<"\n\tStudent Name: "<<name;
    cout<<"\n\tRoll Number: "<<rollno;
    cout<<"\n\tEnglish: "<<english;
    cout<<"\n\tScience: "<<science;
    cout<<"\n\tMathematics: "<<math;
    cout<<"\n\tLanguage: "<<language;
    cout<<"\n\tComputer Skills: "<<computerSkills;
    cout<<"\n\n\tAverage Marks: "<<average<<"  Grade: "<<grade;
}
int student::retrollno() const
{
    return rollno;
}

void create_student();
void display_record(int);
void display_all();
void delete_student(int);
void change_student(int);

int main()
{
    char ch;
    cout<<setprecision(2);
    int num;

    do{
    system("cls");
    cout<<"\n\n\t\tMENU";
    cout<<"\n\t\t 1) Create a Student";
    cout<<"\n\t\t 2) Search for a Student";
    cout<<"\n\t\t 3) Display all Students";
    cout<<"\n\t\t 4) Delete a Student";
    cout<<"\n\t\t 5) Modify a Student Record";
    cout<<"\n\t\t 6) Exit";
    cout<<"\n\n\t\t Select one between (1 /2 /3 /4 /5 /6):   ";
    cin>>ch;
    system("cls");

    switch(ch){
    case '1':
        cout<<"\n\t\tEnter Student Details\n";
        create_student();
        break;
    case '2':
        cout<<"\n\t\tEnter Student Roll Number:";
        cin>>num;
        display_record(num);
        break;
    case '3':
        cout<<"\t\t==ALL STUDENT RECORDS==\n\n";
        display_all();
        break;
    case '4':
        cout<<"Enter Student Roll Number: ";
        cin>>num;
        delete_student(num);
        break;
    case '5':
        cout<<"Insert the Student Number: ";
        cin>>num;
        change_student(num);
        break;
    case '6':
        cout<<"Exiting Program....";
        exit(0);
        break;}

    }while(ch!='6');{ return 0;}
}
student obj;
//Creating a student...
void create_student(){
    fstream ofile;
    ofile.open("student.dat",ios::binary|ios::app |ios::in |ios::out );
    obj.getdata();
    ofile.write(reinterpret_cast <char *> (&obj),sizeof(student));
    ofile.close();
     cout<<"Student is successfully Registered";
    cin.ignore();
    cin.get();
}

//Displaying all student Records

void display_all(){
    ifstream rfile;
    rfile.open("student.dat",ios::binary | ios::in |ios::out);
    if(!rfile){
        cout<<"No Records Found, Press Any key to Exit";
        cin.ignore();
        cin.get();
    }
    cout<<"\n\t===== Displaying All Records ======\n\n";
    while(rfile.read(reinterpret_cast <char *>(&obj),sizeof(student))){
        obj.showdata();
        cout<<"\n\n\t================================\n";
    }
    rfile.close();
    cin.ignore();
    cin.get();
}

//Displaying a specific Record
void display_record(int num){
    fstream infile;
    infile.open("student.dat",ios::in |ios::out);
    if(!infile){
        cout<<"Records Not Found, Press any Key to Exit";
        cin.ignore();
        cin.get();
    }
    bool flag=false;
    while(infile.read(reinterpret_cast<char *>(&obj),sizeof(student))){
        if(num==obj.retrollno()){
            obj.showdata();
            flag =true;
        }
        infile.close();
        if(flag==false){
            cout<<"\nRecord Not Found";
            cin.ignore();
            cin.get();
        }
    }
}

//Modifying Student Record
void change_student(int n){
    fstream mfile;
    mfile.open("student.dat",ios::binary|ios::in|ios::out);
    bool found =false;
    if(!mfile){
        cout<<"\n\nRecord not Found, Press any key to Exit";
        cin.ignore();
        cin.get();
    }
    while(!mfile.eof() && found==false){
        if(obj.retrollno()==n){
            obj.showdata();
            cout<<"\nEnter new Details";
            obj.getdata();
            int pos=(-1)*static_cast<int>(sizeof(obj));
            mfile.seekp(pos,ios::cur);
            mfile.write(reinterpret_cast<char *>(&obj),sizeof(student));
            cout<<"\n\nRecord Updated";
            found=true;
        }
    }
    mfile.close();
    found=false;
    cout<<"\n\nRecord not Found";
    cin.ignore();
    cin.get();
}
void delete_student(int num)
{
    fstream ifile;
    ifile.open("student.dat",ios::binary);
    if(!ifile){
        cout<<"Record not Found,Press any key to Exit";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream ofile;
    ofile.open("temp.dat",ios::out);
    ifile.seekg(0,ios::beg);
    while(ifile.read(reinterpret_cast<char *>(&obj),sizeof(student))){
        if(obj.retrollno()!=num)
        {
            ofile.write(reinterpret_cast<char *> (&obj),sizeof(student));
        }
    }
    ofile.close();
    ifile.close();
    remove("student.dat");
    rename("temp.dat","student.dat");
    cout<<"\n\n\tStudent Record Deleted ...";
    cin.ignore();
    cin.get();
}


