#include<iostream>
#include<vector>
using namespace std;
int main(){
    int numberofCoursestakenbyStudent, i; double totalCredithours=0, totalGrades=0, GPA=0;
    cout<<"Enter the number of courses you are enrolled in: ";
    cin>>numberofCoursestakenbyStudent;
    vector<double> gradesofStudent(numberofCoursestakenbyStudent);
    vector<double> creditsofStudent(numberofCoursestakenbyStudent);

    for(i=0;i<numberofCoursestakenbyStudent;i++){
        cout<<"Enter the grade of course "<<i+1<<": ";
        cin>>gradesofStudent[i];
        cout<<"Enter credit hours of course "<<i+1<<": ";
        cin>>creditsofStudent[i];
        totalCredithours=totalCredithours+creditsofStudent[i];
        totalGrades=totalGrades+(gradesofStudent[i]*creditsofStudent[i]);
    }
    if(totalCredithours>0){
        GPA=totalGrades/totalCredithours;
    }
    cout<<"GPA of every course seperately: "<<endl;
    for(i=0;i<numberofCoursestakenbyStudent;i++){
        cout<<"Grade of course "<<i+1<<" is "<<gradesofStudent[i]<<endl;
        cout<<"Credit hours of course "<<i+1<<" is "<<creditsofStudent[i]<<endl;
    }
    cout<<"CGPA of student is: "<<GPA<<endl;
    cout<<"Overall GPA of student is: "<<GPA<<endl;
    return 0;
}