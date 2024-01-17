#include <iostream> 
#include <fstream> 
#include <string> 
 
using namespace std; 
class Student 
{ 
private: 
    string FullName; 
    string ID; 
    float CGPA; 
    
public: 
    Student (string fn="", string i="", float g=0.0); 
    void add_stu(); 
}; 
Student:: Student(string fn, string i, float g): FullName(fn), ID(i),  CGPA(g){}  
 
void Student:: add_stu() 
{ 
    cout<< "Add student"<<endl; 
    int n; 
    ofstream myfile("Student profile list.txt",ios ::binary); 
 
    if (myfile.is_open()) 
    { 
    cout<< "File will be saved in Student profile list"<<endl; 
    cout<< "How many students will you be adding"<<endl; 
    cin>> n; 
 
    cin.ignore(); 
for(int i=0; i<n;i++) 
{ 
    cout<< "Enter fullname of student "<<i+1<<" : "<<endl; 
   getline(cin, FullName); 
    cout<< "Enter ID of student "<< i+1<<" : "<<endl; 
   getline(cin, ID); 
   cout<< "Enter CGPA of student"<< i+1<<" : "<<endl; 
   cin>>CGPA;
   cin.ignore();
 
            myfile.write(reinterpret_cast<const char*>(&FullName[0]), sizeof(char) * FullName.size()); 
            myfile.write(reinterpret_cast<const char*>(&ID[0]), sizeof(char) * ID.size()); 
            myfile.write(reinterpret_cast<const char*>(&CGPA), sizeof(float)); 
 
   cout<< "File saved successfully"<<endl; 
} 
myfile.close(); 
} 
else  
cout<< "Error opening file"<<endl; 
} 
int main() 
{ 
    Student student1; 
 
    student1.add_stu(); 
 
    return 0; 
}