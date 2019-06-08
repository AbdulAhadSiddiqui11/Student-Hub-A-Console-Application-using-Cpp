
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include <iomanip>
#include <ctime>
using namespace std;
class Login
{
private:
    char username[20],password[20],branch[20],pno[20],email[30];
public:
    Login();
    int  log_in();
    bool regester();
    void display();
    void delete_user();
    void main_menu();
    void sub_menu1();
    void sub_menu2();
    void update_data_user();
    void update_data_admin();
    void search_user();
    void read_news();
    void write_news();
    void schedule();
    void impt_con();
    void write_reviews();
    void read_reviews();
}; 
Login l1,l2;
void clear_screen();
Login::Login()
{
    strcpy(username,"no data");
    strcpy(password,"no data");
    strcpy(branch,"no data");
    strcpy(pno,"no data");
    strcpy(email,"no data");
}

int Login::log_in()
{
    char user[20],pass[20];
    cout<<"Username : ";
    cin>>user;
    cout<<"\nPassword : ";
    cin>>pass;
    clear_screen();
    if(!(strcmp(user,"admin")) && !(strcmp(pass,"admin101") ))
        return 2;
    else
    {
    ifstream fin;
    fin.open("user_data.dat", ios::in|ios::binary);
    fin.read((char *)this, sizeof(*this));
        while(!fin.eof())
        {
            if(!(strcmp(user,username)) && !(strcmp(pass,password) ))
              return 1;
           fin.read((char *)this, sizeof(*this));
        }
    }
    return 10;
}

bool Login::regester()
{   int err;
    cout<<"Username    : ";
    cin>>username;
    cout<<"\nPassword  : ";
    cin>>password;
    cout<<"\nBranch    : ";
    cin>>branch;
    cout<<"\nPhone No. : ";
    cin>>pno;
    cout<<"\nEmail     : ";
    cin>>email;
    try
    {
        if(!(strcmp(username,"no data")) || !(strcmp(password,"no data") ))
            throw err;
        else
        {
            ofstream fout;
            fout.open("user_data.dat",ios::app|ios::binary);
            fout.write((char *)this, sizeof(*this));
            fout.close();
            clear_screen();
            return true;
        }
    }
    catch(int e)
    {
        cout<<"Username or password cannot be blank"<<endl;
            return false;
    }
}
void Login::display()
{
    int ctr =1;
    cout<<"Currently registered users are: \n\n";
    ifstream display;
    display.open("user_data.dat", ios::in|ios::binary);
    display.read((char *)this, sizeof(*this));
        while(!display.eof())
        {
            cout<<"\nName      : "<<username;
            cout<<"\nBranch    : "<<branch;
            cout<<"\nPhone No. : "<<pno;
            cout<<"\nEmail     : "<<email<<endl<<endl;
            display.read((char *)this, sizeof(*this));
            ctr++;
        }
    cout<<"Total registered users : ";
    cout << "\033[1;31m"<<ctr<<"\033[0m\n\n";
    display.close();
}

void Login::delete_user()
{
    char user[20];
    cout<<"Enter the user to be deleted"<<endl;
    cin>>user;
    ifstream fin;
    ofstream fout;
    fin.open("user_data.dat", ios::in|ios::binary);
    fout.open("temp.dat",ios::out|ios::binary);
    fin.read((char *)this, sizeof(*this));
    while(!fin.eof())
        {
            if(strcmp(user,username))
              fout.write((char *)this, sizeof(*this));
          fin.read((char *)this, sizeof(*this));
        }

    fin.close();
    fout.close();
    remove("user_data.dat");
    rename("temp.dat","user_data.dat");
    cout<<"User : "<<user<<" deleted successfully"<<endl;
}

void Login::main_menu()
{
    int ch;
    int log;
    do
    {
    cout << "\033[1;31mW E L C O M E   T O   S T U D E N T - H U B\033[0m\n";
    cout << "\033[1;37m";
    cout<<"============================================\n";
    cout<<"Enter your choice"<<endl;
    cout<<"1.SIGN UP"<<endl;
    cout<<"2.LOGIN"<<endl;
    cout<<"3.EXIT"<<endl;
    cout<<"=============================================\n";
    cout<<"\033[0m\n";
    cin>>ch;
            switch(ch)
            {
                case 1:{
                            if(l1.regester())
                            cout<<"Registration successful - you may now login!"<<endl;
                            cout << "\033[1;33mWELCOME TO THE COMMUNITY!\033[0m\n";
                            cout<<"Press any key to continue..."<<endl;
                             cin.ignore();
                            cin.get();
                            clear_screen();
                            break;
                       }
                case 2:{
                            log=l1.log_in();
                           if(log==1)
                            l1.sub_menu1();
                           else if(log==2)
                            l1.sub_menu2();
                            else
                            {
                                cout << "\033[1;31mInvalid username or password\033[0m\n";
                                cout << "\033[1;33mNOTE: Usernames and passwords are case-sensitive\033[0m\n";
                                cout<<"Press any key to continue..."<<endl;
                                cin.ignore();
                                cin.get();
                                clear_screen();
                            }
                            break;
                        }

                case 3: break;
              default: cout<<"Invalid option\n";
                        break;
               }
          }while(ch!=3);
}

void Login::sub_menu2()
{
    int ch;
    do
    {
    cout<<"======================================\n";
    cout<<"WELCOME ";
    cout << "\033[1;31mADMIN\033[0m\n\n";
    cout<<"Enter your choice"<<endl;
    cout<<"1.Display all users"<<endl;
    cout<<"2.Delete a user"<<endl;
    cout<<"3.Update a user\'s data"<<endl;
    cout<<"4.Read reviews from users"<<endl;
    cout<<"5.logout"<<endl;
    cout<<"=======================================\n";
    cin>>ch;
    switch(ch)
            {
                case 1:{
                            l2.display();
                            cout<<"Press any key to continue..."<<endl;
                            cin.ignore();
                             cin.get();
                            clear_screen();
                            break;
                       }
                case 2:{
                            l2.delete_user();
                            cin.ignore();
                            cin.get();
                             cout<<"Press any key to continue..."<<endl;
                            clear_screen();
                            break;
                        }

                case 3: {
                            l2.update_data_admin();
                            cout<<"Press any key to continue..."<<endl;
                            cin.ignore();
                            cin.get();
                            clear_screen();
                            break;
                        }
                case 4: {
                            cout << "\033[1;31mTHESE ARE THE REVIEWS FROM THE ACTIVE USERS\033[0m\n";
                            l1.read_reviews();
                            cout<<"Press any key to continue..."<<endl;
                             cin.ignore();
                            cin.get();
                            clear_screen();
                            break;
                        }
                case 5: {
                            cout<<"Logged out successfully"<<endl;
                             cout<<"Press any key to continue..."<<endl;
                               cin.ignore();
                            cin.get();
                            clear_screen();
                            break;
                        }
              default: cout<<"Invalid option\n";
                        break;

            }
     }while(ch!=5);
}

void Login::sub_menu1()
{
    int ch;
   do
    {
    cout<<"==============================================\n";
    cout<<"WELCOME ";
    cout << "\033[1;31m"<<username <<"\033[0m\n\n";
    cout<<"Enter your choice"<<endl;
    cout<<"1.See what\'s hapenning around you?!"<<endl;
    cout<<"2.Write news"<<endl;
    cout<<"3.Semester schedule"<<endl;
    cout<<"4.Important Contacts"<<endl;
    cout<<"5.Update Your Profile"<<endl;
    cout<<"6.Search friends"<<endl;
    cout<<"7.Give us your review"<<endl;
    cout<<"8.logout"<<endl;
    cout<<"===============================================\n";
    cin>>ch;
    switch(ch)
    {
    case 1:
        {   clear_screen();
             cout << "\033[1;31mHERE ARE THE LATEST HAPPENINGS FROM AROUND THE CAMPUS\033[0m\n";
            l1.read_news();
            cout<<"THAT\'S ALL FOLKS\n";
            cout<<"Press any key to continue..."<<endl;
                            cin.ignore();
                            cin.get();
                            clear_screen();
                            break;
        }
    case 2:
        {
            clear_screen();
             cout << "\033[1;31mGot something to share with all your college mates?\nFrom academics to fun events anything can be posted here in this section\033[0m\n";
            l1.write_news();
            cout<<"Press any key to continue..."<<endl;
                           cin.ignore();
                            cin.get();
                            clear_screen();
                            break;
        }
    case 3:
        {   clear_screen();
            cout << "\033[1;31mHERE\'S THE ACADEMIC CALANDER FOR THE CURRENT SEMESTER\033[0m\n";
            l1.schedule();
            cout<<"Press any key to continue..."<<endl;
                            cin.ignore();
                            cin.get();
                            clear_screen();
                            break;
        }
    case 4: 
        {
            clear_screen();
            cout << "\033[1;31mTHESE CONTACTS MAY COME IN HANDY\033[0m\n";
          l1.impt_con();
          cout<<"Press any key to continue..."<<endl;
                            cin.ignore();
                            cin.get();
                            clear_screen();
                            break;       
        }

        
    case 5:
        {
                            l1.update_data_user();
                            cout<<"Press any key to continue..."<<endl;
                            cin.ignore();
                            cin.get();
                            clear_screen();
                            break;
        }
    case 6:
        {
                            l2.search_user();
                            cout<<"Press any key to continue..."<<endl;
                            cin.ignore();
                            cin.get();
                            clear_screen();
                            break;
         }

    case 7:
        {
            clear_screen();
             cout << "\033[1;33mTell us about this app... loved it?, hated it? , want some features to be added? any feedback is much appericiated!\033[0m\n";
            l1.write_reviews();
            cout << "\033[1;33mThanks for the feedback and for being an active community member!\033[0m\n";
            cout<<"Press any key to continue..."<<endl;
                           cin.ignore();
                            cin.get();
                            clear_screen();
                            break;
        }

    case 8: 
        {
                            cout<<"Logged out successfully! ";
                            cout << "\033[1;33mSayonara ;)\033[0m\n";
                            cout<<"Press any key to continue..."<<endl;
                            cin.ignore();
                            cin.get();
                            clear_screen();
                            break;
         }
              default: cout<<"Invalid option\n";
                        break;
    }

      }while(ch!=8);

}

void Login ::read_news()
{
         string in;
    ifstream f2;
    f2.open("newsfile.txt",ios::in);
    while(getline(f2,in))
    {
        cout<<in<<endl;
        cout<<"\n";
    }
    f2.close();
}

void Login::write_news()
{
         char info[1000];
        string usernews;
        srand(time(NULL));
        int random;
        random= (rand()%7)+30; 
    ofstream f1;
    f1.open("newsfile.txt",ios::app);

    cout<<"Say something..."<<endl;
    cin.ignore();
    cin.getline(info,100);
    usernews = l1.username;
    f1<<"\033[1;"<<random<<"m"<<usernews<<"\033[0m"<<" : "<<info;
    f1<<"\n";
    f1.close();

}

void Login::schedule()
{

    string day1,day2,day3,day4,day5,day6,day7,day8,day9,day10,day11,day12,d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12;
    cout<<" schedule for SEM-III \n\n";
    ifstream show;
        show.open("schedulefile.txt");
         while(show>>day1>>d1>>day2>>d2>>day3>>d3>>day4>>d4>>day5>>d5>>day6>>d6>>day7>>d7>>day8>>d8>>day9>>d9>>day10>>d10>>day11>>d11>>day12>>d12)

         {


    cout << "|" << day1 << setw(20)<<"   |   " <<setw(5)<< d1 << setw(5)<<"   |"<<endl;
    cout << "|" << day2 << setw(20)<<"   |   " <<setw(5)<< d2 << setw(5)<<"   |"<<endl;
    cout << "|" << day3 << setw(20)<<"   |   " <<setw(5)<< d3 << setw(5)<<"   |"<<endl;
    cout << "|" << day4 << setw(20)<<"   |   " <<setw(5)<< d4 << setw(5)<<"   |"<<endl;
    cout << "|" << day5 << setw(20)<<"   |   " <<setw(5)<< d5 << setw(5)<<"   |"<<endl;
    cout << "|" << day6 << setw(20)<<"   |   " <<setw(5)<< d6 << setw(5)<<"   |"<<endl;
    cout << "|" << day7 << setw(20)<<"   |   " <<setw(5)<< d7 << setw(5)<<"   |"<<endl;
    cout << "|" << day8 << setw(20)<<"   |   " <<setw(5)<< d8 << setw(5)<<"   |"<<endl;
    cout << "|" << day9 << setw(20)<<"   |   " <<setw(5)<< d9 << setw(5)<<"   |"<<endl;
    cout << "|" << day10 << setw(20)<<"   |   " <<setw(5)<< d10 << setw(5)<<"   |"<<endl;
    cout << "|" << day11 << setw(20)<<"   |   " <<setw(5)<< d11 << setw(5)<<"   |"<<endl;
    cout << "|" << day12 << setw(20)<<"   |   " <<setw(5)<< d12 << setw(5)<<"   |"<<endl;

    cin.get();
         }

}

void Login::impt_con()
{
      ifstream f2;
      string in;
      f2.open("contact.txt",ios::in);
       while(   getline(f2,in))
    {
        cout<<in<<endl;
        cout<<"\n";
    }
    f2.close();
}

void Login::write_reviews()
    {
       char review[1000];
        string usereview;
        srand(time(NULL));
        int random;
        random= (rand()%7)+30; 
    ofstream f1;
    f1.open("reviews.txt",ios::app);

    cout<<"Say something..."<<endl;
    cin.ignore();
    cin.getline(review,100);
    usereview = l1.username;
    f1<<"\033[1;"<<random<<"m"<<usereview<<"\033[0m"<<" : "<<review;
    f1<<"\n";
    f1.close();

    }

    void Login ::read_reviews()
{
         string in;
    ifstream f2;
    f2.open("reviews.txt",ios::in);
    while(getline(f2,in))
    {
        cout<<in<<endl;
        cout<<"\n";
    }
    f2.close();
}


void Login::update_data_admin()
{
    char user[20];
    cout<<"Enter a user to be updated"<<endl;
    cin>>user;
    fstream file;
    file.open("user_data.dat", ios::in|ios::out|ios::ate|ios::binary);
    file.seekg(0);
    file.read((char *)this , sizeof(*this));
        while(!file.eof())
        {
            if(!(strcmp(user,username)))
            {
                cout<<"Enter new info."<<endl;
                cout<<"Username    : ";
                cin>>username;
                cout<<"\nPassword  : ";
                cin>>password;
                cout<<"\nBranch    : ";
                cin>>branch;
                cout<<"\nPhone No. : ";
                cin>>pno;
                cout<<"\nEmail     : ";
                cin>>email;
                file.seekp(-sizeof(*this),ios::cur);
                file.write((char *)this , sizeof(*this));
            }
         file.read((char *)this , sizeof(*this));
        }
    cout<<"User data updated successfully"<<endl;
    file.close();
}

void Login::update_data_user()
{
    char user[20];
    strcpy(user,username);
    fstream file;
    file.open("user_data.dat", ios::in|ios::out|ios::ate|ios::binary);
    file.seekg(0);
    file.read((char *)this , sizeof(*this));
        while(!file.eof())
        {
            if(!(strcmp(user,username)))
            {
                cout<<"Enter new credentials"<<endl;
                cout<<"\nNew Password  : ";
                cin>>password;
                cout<<"\nBranch    : ";
                cin>>branch;
                cout<<"\nPhone No. : ";
                cin>>pno;
                cout<<"\nEmail     : ";
                cin>>email;
                file.seekp(-sizeof(*this),ios::cur);
                file.write((char *)this , sizeof(*this));
            }
         file.read((char *)this , sizeof(*this));
        }
    cout << "\033[1;31mYour\'e all set! Your profile has been updated\033[0m\n";
    file.close();
}

void Login::search_user()
{
    int counter=0;
    char user[20];
    cout << "\033[1;31mLooking for someone?\033[0m\n";
    cout<<"Enter the username to be searched"<<endl;
    cin>>user;
    ifstream fin;
    fin.open("user_data.dat", ios::in|ios::binary);
    fin.read((char *)this , sizeof(*this));
        while(!fin.eof())
        {
            if(!(strcmp(user,username)))
            {
                cout<<"User : "<<username<<" found!"<<endl<<endl;
                cout<<"\nName      : "<<username;
                cout<<"\nBranch    : "<<branch;
                cout<<"\nPhone No. : "<<pno;
                cout<<"\nEmail     : "<<email<<endl<<endl;
                counter++;
            }
          fin.read((char *)this , sizeof(*this));
        }
    if(counter==0)
    cout<<"Sorry we couldn\'t find anyone with the username - "<<user<<"!\n";
    fin.close();
}

int main()
{
    l1.main_menu();
    return 101;
}


void clear_screen()
{
    for(int i=0 ; i<27 ;i++)
        cout<<endl;
}