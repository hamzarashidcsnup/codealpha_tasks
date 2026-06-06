#include<iostream>
#include<string>
using namespace std;
class Library{
    private:
            int book_id[5] = {1,2,3,4,5};
            string title[5] = {"OOP","DLD","DBMS","CALCULUS","EXPO WRITING"};
            int book_availablity[5] = {1,1,1,1,1}; //1 means available, 0 means borrowed
    public:
            void displayBooks(){
                int displaychoice;
                cout<<"Enter 1 if you want to see info of all books.\nEnter 2 if you want to see info of a specific book."<<endl;
                cin>>displaychoice;
                if(displaychoice==1){
                    cout<<"Info about all the books is as follows: "<<endl;
                    for(int i=0;i<5;i++){
                        cout<<"Book"<<i+1<<": Title: "<<title[i]<<endl;
                        if(book_availablity[i]==1){
                            cout<<"Available"<<endl;
                        }
                        else{
                            cout<<"Not available"<<endl;
                        }
                    }
                }
                else if (displaychoice==2){
                    int bookchoice;
                    cout<<"Enter the ID of the book you want to see info of: ";
                    cin>>bookchoice;
                    cout<<"The information of Book "<<bookchoice<<" is given below:\nBook ID: "<<bookchoice-1<<", Book Title: "<<title[bookchoice-1]<<endl;
                    if(book_availablity[bookchoice-1]==1){
                        cout<<"Book is available"<<endl;
                    }
                    else{
                        cout<<"Book is not available"<<endl;
                    }
                }
            }
            void borrowBook(){
                int IDofBooktobeBorrowed;
                cout<<"Enter the ID of the book that you want to borrow: ";
                cin>>IDofBooktobeBorrowed;
                if(book_availablity[IDofBooktobeBorrowed-1] == 1){
                    book_availablity[IDofBooktobeBorrowed-1] = 0;
                    cout<<"Book successfully borrowed\n";
                }
                else
                    cout<<"Book not available\n";
            }
            void returnBook(){
                int IDofBooktobeReturned;
                cout<<"Enter the ID of the book that you want to return: ";
                cin>>IDofBooktobeReturned;
                book_availablity[IDofBooktobeReturned-1] = 1;
                cout<<"Book successfully returned\n";
            }
};
int main(){
    Library Libraryobj;
    int choice=0;
    while(choice != 4){
    cout<<"Welcome to the menu of Library Management System.\n•To display all the books in Library with their information, enter 1.\n•To Borrow a book from the Library, enter 2.\n•To return a book to Library, Enter 3.\n•To exit from the main menu, press 4.\n ";
    cin>>choice;
    if(cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n');
        cout<<"Invalid input, please enter a valid choice(1-4)";
        continue;
    }
    switch(choice){
        case 1:
                Libraryobj.displayBooks();
                break;
        case 2:
                Libraryobj.borrowBook();
                break;
        case 3:
                Libraryobj.returnBook();
                break;
        case 4:
                cout<<"Thank you for visiting.";
                break;
        default:
                cout<<"invalid choice, please enter a valid choice(1-4)";
        }
    }
    return 0;
}
