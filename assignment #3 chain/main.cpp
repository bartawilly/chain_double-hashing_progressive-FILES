#include <iostream>
#include<fstream>
#include <cstring>
using namespace std;
struct student{
 char  Name [ 50]; //max len = 50
  char GPA [5]; //max len =3
 char Address [ 50]; //max len=50
 char  Mobile [ 11];
 char  Department [3];
};
struct index{
short offset;
char  pk [ 50];
short next ;
};
void initialize(){
    fstream f;
    f.open("overflow.txt",ios::binary | ios::out |ios::trunc);
 f.close();
 f.open("student.txt",ios::binary | ios::out |ios::trunc);
 f.close();
 fstream ff;
   ff.open("chain.txt",ios::in |ios::out| ios::binary);
    index k;
    k.offset=-1;
    k.next=-1;

for(int i=0 ;i<sizeof(k.pk);i++){
k.pk[i]='\0';
k.pk[0]='#';
     }
        for(int j=0 ;j<100;j++){
ff.write((char*) &k,sizeof(index));
       }
ff.close();

}
short h1(char k []){
    return ((int)k[0]*(int)k[1])%100;

}
void add_student(){
     student s;
    index sdex,sdex1;
    cin.ignore();
cout<<"Student Name:";

cin.getline(s.Name,50);

cout<<"Student DEP:";

cin.getline(s.Department,3);

cout<<"Student GPA :";
cin.getline(s.GPA,5);

cout<<"Student Address:";
cin.getline(s.Address,50);
cout<<"Student Mobile:";
cin.getline(s.Mobile,11);
fstream file;
file.open("student.txt",ios::out | ios::app | ios::binary);
file.seekg(0,ios::end);
sdex.offset=file.tellp();
file.write((char*) &s,sizeof(student));
file.close();
strcpy(sdex.pk,s.Name);
sdex.next=-1;
short hashh=h1(s.Name);
//cout<<hashh<<endl;
fstream f;
index tg;
 f.open("chain.txt",ios::in |ios::out |ios::binary);
//f.seekg(0,ios::end);
//short endd=f.tellp();
short seek=(hashh)*sizeof(index);
     f.seekg(seek,ios::beg);
f.read((char*)&tg,sizeof(tg));
if(tg.offset==-1 ){
    f.seekg(seek,ios::beg);
    f.write((char*)&sdex,sizeof(index));
   f.close();
    return;
}
if(tg.offset==-5 ){
    f.seekg(seek,ios::beg);
    sdex.next=tg.next;

    f.write((char*)&sdex,sizeof(index));
   f.close();
    return;
}
 if(tg.next==-1 ){
fstream ff;
ff.open("overflow.txt",ios::out |ios::in|ios::binary);
ff.seekg(0,ios::end);
short x=ff.tellp()/sizeof(index);
 ff.write((char*)&sdex,sizeof(index));
 f.seekg(seek,ios::beg);
 tg.next=x;
 f.seekg(seek,ios::beg);
 f.write((char*)&tg,sizeof(tg));
  f.close();
 ff.close();
return;
 }

short blabla;
short sk;
while(tg.next!=-1){
    if(tg.offset==-5)break;
        fstream ff;
ff.open("overflow.txt",ios::out |ios::in|ios::binary);
        blabla=tg.next;
ff.seekg(blabla*sizeof(index),ios::beg);
sk=ff.tellp()/sizeof(index);

ff.read((char*)&tg,sizeof(tg));
ff.close();
}


if(tg.next==-1 &&tg.offset!=-5){
 fstream ff;
ff.open("overflow.txt",ios::out |ios::in|ios::binary);
ff.seekg(0,ios::end);
int y =ff.tellp()/sizeof(index);
ff.write((char*)&sdex,sizeof(index));
ff.seekg(blabla*sizeof(index),ios::beg);
ff.read((char*)&tg,sizeof(index));
tg.next=y;
ff.seekg(blabla*sizeof(index),ios::beg);
ff.write((char*)&tg,sizeof(index));
f.close();
ff.close();

return;

}
else if(tg.offset==-5){
    sdex.next=tg.next;
    fstream ff;
ff.open("overflow.txt",ios::out |ios::in|ios::binary);
ff.seekg(sk*sizeof(index),ios::beg);
ff.write((char*)&sdex,sizeof(index));
ff.close();
return;

}
}





void show(char name []){
    //strcmp(temp.pk,name)
short hashh=h1(name);
index temp;
fstream chain;
chain.open("chain.txt",ios::in |ios::out|ios::binary);
chain.seekg(hashh*sizeof(index),ios::beg);
chain.read((char*)&temp,sizeof(index));
if(temp.offset==-1 ){
    cout<<"there's no student name like this !!!"<<endl;
    return;
}

if(temp.next==-1 && strcmp(temp.pk,name)){
     cout<<"there's no student name like this !!!"<<endl;
    return;
}
if((temp.next==-1||temp.next!=-1) && temp.offset==-5&&!strcmp(temp.pk,name)){
     cout<<"there's no student name like this !!!"<<endl;
    return;
}

if(temp.next==-1 &&temp.offset!=-5 &&!strcmp(temp.pk,name)){
        student s;
    fstream file;
    file.open("student.txt",ios::in|ios::binary);
    file.seekg(temp.offset,ios::beg);
    file.read((char*)&s,sizeof(student));
    file.close();
cout<<s.Name<<'|'<<s.GPA<<'|'<<s.Address<<'|'<<s.Mobile<<'|'<<s.Department<<'|'<<endl;
return;
}
if(temp.next!=-1 && temp.offset!=-5 && !strcmp(temp.pk,name)){
        student s;
    fstream file;
    file.open("student.txt",ios::in|ios::binary);
    file.seekg(temp.offset,ios::beg);
    file.read((char*)&s,sizeof(student));
    file.close();
cout<<s.Name<<'|'<<s.GPA<<'|'<<s.Address<<'|'<<s.Mobile<<'|'<<s.Department<<'|'<<endl;
return;
}

 short blabla;
 if(temp.next!=-1&& strcmp(temp.pk,name)){
while(temp.next!=-1&&strcmp(temp.pk,name)){
        fstream ff;
ff.open("overflow.txt",ios::out |ios::in|ios::binary);
        blabla=temp.next;
ff.seekg(blabla*sizeof(index),ios::beg);
ff.read((char*)&temp,sizeof(index));
ff.close();
} if(!strcmp(temp.pk,name)&&temp.offset!=-5){
 fstream ff;
ff.open("overflow.txt",ios::out |ios::in|ios::binary);
ff.seekg(blabla*sizeof(index),ios::beg);
ff.read((char*)&temp,sizeof(index));
student s;
    fstream file;
    file.open("student.txt",ios::in|ios::binary);
    file.seekg(temp.offset,ios::beg);
    file.read((char*)&s,sizeof(student));
    file.close();
cout<<s.Name<<'|'<<s.GPA<<'|'<<s.Address<<'|'<<s.Mobile<<'|'<<s.Department<<'|'<<endl;
}
else if (strcmp(temp.pk,name)||temp.offset==-5){
     cout<<"there's no student name like this !!!"<<endl;
}
 }

chain.close();
}
void delete_student(char name []){
  short hashh=h1(name);
index temp;
fstream chain;
chain.open("chain.txt",ios::in |ios::out|ios::binary);
chain.seekg(hashh*sizeof(index),ios::beg);
chain.read((char*)&temp,sizeof(index));
if(temp.offset==-1){
    cout<<"there's no student name like this !!!"<<endl;
    return;
}
if(temp.next==-1 && strcmp(temp.pk,name)){
     cout<<"there's no student name like this !!!"<<endl;
    return;
}
else if(temp.next==-1 && !strcmp(temp.pk,name)){
        student s;
    fstream file;
    file.open("student.txt",ios::in|ios::binary);
    file.seekg(temp.offset,ios::beg);
    file.read((char*)&s,sizeof(student));
    file.close();

cout<<s.Name<<'|'<<s.GPA<<'|'<<s.Address<<'|'<<s.Mobile<<'|'<<s.Department<<'|'<<endl;
chain.seekg(hashh*sizeof(index),ios::beg);
    chain.read((char*)&temp,sizeof(index));
    temp.offset=-5;
    chain.seekg(hashh*sizeof(index),ios::beg);
chain.write((char*)&temp,sizeof(index));
      cout<<"deleted"<<endl;
      return;
}
else if(temp.next!=-1 && !strcmp(temp.pk,name)){
        student s;
    fstream file;
    file.open("student.txt",ios::in|ios::binary);
    file.seekg(temp.offset,ios::beg);
    file.read((char*)&s,sizeof(student));
    file.close();
cout<<s.Name<<'|'<<s.GPA<<'|'<<s.Address<<'|'<<s.Mobile<<'|'<<s.Department<<'|'<<endl;
chain.seekg(hashh*sizeof(index),ios::beg);
    chain.read((char*)&temp,sizeof(index));
    temp.offset=-5;
    chain.seekg(hashh*sizeof(index),ios::beg);
chain.write((char*)&temp,sizeof(index));
      cout<<"deleted"<<endl;
      return;
}
 short blabla;
 if(temp.next!=-1&&strcmp(temp.pk,name)){
while(temp.next!=-1&&strcmp(temp.pk,name)){
        fstream ff;
ff.open("overflow.txt",ios::out |ios::in|ios::binary);
        blabla=temp.next;
ff.seekg(blabla*sizeof(index),ios::beg);
ff.read((char*)&temp,sizeof(index));
ff.close();
} if(!strcmp(temp.pk,name)){
 fstream ff;
ff.open("overflow.txt",ios::out |ios::in|ios::binary);
ff.seekg(blabla*sizeof(index),ios::beg);
ff.read((char*)&temp,sizeof(index));
student s;
    fstream file;
    file.open("student.txt",ios::in|ios::binary);
    file.seekg(temp.offset,ios::beg);
    file.read((char*)&s,sizeof(student));
    file.close();
cout<<s.Name<<'|'<<s.GPA<<'|'<<s.Address<<'|'<<s.Mobile<<'|'<<s.Department<<'|'<<endl;
ff.seekg(blabla*sizeof(index),ios::beg);
    ff.read((char*)&temp,sizeof(index));
    temp.offset=-5;
    ff.seekg(blabla*sizeof(index),ios::beg);
ff.write((char*)&temp,sizeof(index));
      cout<<"deleted"<<endl;
      ff.close();
      return;
}
else if (strcmp(temp.pk,name)){
     cout<<"there's no student name like this !!!"<<endl;
     return;
}
 }

chain.close();
}
int main()
{
 //initialize();
    while (1){
        cout<<endl<<endl;
            cout<<"Enter 1 to add student"<<endl<<"Enter 2 to search for student by his/her name"<<endl<<"Enter 3 to delete student"<<endl<<"Enter 4 to exit"<<endl;
    int x;
    cout<<"enter your choice : ";
    cin>>x;

   if(x==1){
    add_student();
   }
   else if(x==2){
student s;
 cin.ignore();
cout<<"Student you want Name:";

cin.getline(s.Name,50);
show(s.Name);}
else if(x==3){
    student ss;
 cin.ignore();
cout<<"Student you want to delete Name:";

cin.getline(ss.Name,50);
delete_student(ss.Name);
}
else {break;}
}
    return 0;
}
