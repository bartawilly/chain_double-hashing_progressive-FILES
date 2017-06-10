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
char  pk [ 50];
short offset;
};
void show_index_file(){
fstream f;
   int cont =0;
     f.open("index.txt",ios::binary | ios::in  );
     index b;
     f.seekg(0,ios::beg);
     for(int i=0 ;i<100 ;i++){
        for(int j=0 ;j<3;j++){
 f.read((char*) &b,sizeof(index));
cout<<b.pk<<b.offset<<endl;
cont ++;
        }
        f.seekg(1,ios::cur);

    }

f.close();
cout << cont;


}
void build_index_and_student(){
     fstream ff;
    ff.open("index.txt",ios::binary | ios::out |ios::trunc);
ff.close();
 ff.open("student.txt",ios::binary | ios::out |ios::trunc);
 ff.close();
  index bmla ;
     for(int i=0 ;i<sizeof(bmla.pk);i++){

        bmla.pk[i]='\0';
     bmla.pk[0]='#';


      }


    bmla.offset=-1;
    fstream f;
    f.open("index.txt",ios::binary | ios::out |ios::app);
    for(int i=0 ;i<100 ;i++){
        for(int j=0 ;j<3;j++){


       f.write((char*) &bmla,sizeof(index));
        }
        f<<endl;

    }
    f.close();

}
short h1(char k []);
void add_student(){
    student s;
    index sdex;
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
//cout<<sdex.offset<<endl;
file.write((char*) &s,sizeof(student));
file.close();
strcpy(sdex.pk,s.Name);
short hashh=h1(s.Name);
//*((2*sizeof(index))+1);
//cout<<hashh<<endl<<endl;
//cout<<seek<<endl;
fstream f;
index tg;
 f.open("index.txt",ios::in |ios::out |ios::binary);

short hashstop=hashh;
f.seekg(0,ios::end);
short endd=f.tellp();
while(1){
short seek=(hashh-1)*((3*sizeof(index))+1);
     f.seekg(seek,ios::beg);
f.read((char*)&tg,sizeof(tg));
if(tg.offset==-1 ||tg.offset==-5){
    f.seekg(seek,ios::beg);
    f.write((char*)&sdex,sizeof(index));
    break;
}
else if(tg.offset!=-1 && tg.offset!=-5){
     f.seekg(seek+sizeof(index),ios::beg);
    f.read((char*)&tg,sizeof(tg));
    if(tg.offset==-1 || tg.offset==-5){
    f.seekg(seek+sizeof(index),ios::beg);
    f.write((char*)&sdex,sizeof(index));
    break;
    }
    else if(tg.offset!=-1 && tg.offset!=-5){
 //cout<<seek;
//hashh=hashh+h2(sdex.pk);
//cout<<hashh<<endl;
  //cout<<seek;
   f.seekg(seek+2*sizeof(index),ios::beg);
    f.read((char*)&tg,sizeof(tg));
     if(tg.offset==-1 || tg.offset==-5){
    f.seekg(seek+2*sizeof(index),ios::beg);
    f.write((char*)&sdex,sizeof(index));
    break;
    }
    else if(tg.offset!=-1 && tg.offset!=-5){
            hashh=hashh+1;
    }
}

}
if(seek>endd){
hashh=hashh%100;
f.close();
f.open("index.txt",ios::in |ios::out |ios::binary);
}

if(hashh==hashstop){
    cout<<"no place to write your student"<<endl;
    break;
}

}
f.close();
}



short h1(char k []){
    return ((int)k[0]*(int)k[1])%100;

}



void show(char name []){
short hashh=h1(name);
//*((2*sizeof(index))+1);
//cout<<seek<<endl;
fstream f;
index tg;
f.open("index.txt",ios::in |ios::out |ios::binary);


short hashstop=hashh;

 f.seekg(0,ios::end);
short endd=f.tellp();


while(1){
        short seek=(hashh-1)*((3*sizeof(index))+1);
        f.seekg(seek,ios::beg);
f.read((char*)&tg,sizeof(tg));
//cout<<tg.offset<<endl;
if((tg.offset!=-1 && tg.offset!=-5)&& !strcmp(tg.pk,name)){
    f.seekg(seek,ios::beg);
    f.read((char*)&tg,sizeof(index));
      student s;
    fstream file;
file.open("student.txt",ios::in | ios::binary);
file.seekg(tg.offset,ios::beg);
file.read((char*)&s,sizeof(s));
cout<<s.Name<<'|'<<s.GPA<<'|'<<s.Address<<'|'<<s.Mobile<<'|'<<s.Department<<'|'<<endl;

    break;
    }
    else if((tg.offset==-1|| tg.offset==-5)|| strcmp(tg.pk,name)){
        f.seekg(seek+sizeof(index),ios::beg);
         f.read((char*)&tg,sizeof(index));
        if((tg.offset!=-1 && tg.offset!=-5)&& !strcmp(tg.pk,name)){
    f.seekg(seek+sizeof(index),ios::beg);
    f.read((char*)&tg,sizeof(index));
      student s;
    fstream file;
file.open("student.txt",ios::in | ios::binary);
file.seekg(tg.offset,ios::beg);
file.read((char*)&s,sizeof(s));
cout<<s.Name<<'|'<<s.GPA<<'|'<<s.Address<<'|'<<s.Mobile<<'|'<<s.Department<<'|'<<endl;

    break;
    }
    else if((tg.offset==-1 || tg.offset==-5)|| strcmp(tg.pk,name)){
       //  hashh=hashh+h2(name);
               f.seekg(seek+2*sizeof(index),ios::beg);
         f.read((char*)&tg,sizeof(index));
if((tg.offset!=-1 && tg.offset!=-5)&& !strcmp(tg.pk,name)){
    f.seekg(seek+2*sizeof(index),ios::beg);
    f.read((char*)&tg,sizeof(index));
      student s;
    fstream file;
file.open("student.txt",ios::in | ios::binary);
file.seekg(tg.offset,ios::beg);
file.read((char*)&s,sizeof(s));
cout<<s.Name<<'|'<<s.GPA<<'|'<<s.Address<<'|'<<s.Mobile<<'|'<<s.Department<<'|'<<endl;

    break;
    }
        else if((tg.offset==-1 || tg.offset==-5)|| strcmp(tg.pk,name)){
            hashh=hashh+1;
        }
    }
    }
    if(seek>endd){
   hashh=hashh%100;
f.close();
f.open("index.txt",ios::in |ios::out |ios::binary);
}
if(hashh==hashstop){
    cout<<"this student is not founded !!"<<endl;
    break;
}


}
f.close();
}
void delete_student(char name []){
short hashh=h1(name);
//*((2*sizeof(index))+1);
//cout<<seek<<endl;
fstream f;
index tg;
f.open("index.txt",ios::in |ios::out |ios::binary);


short hashstop=hashh;

 f.seekg(0,ios::end);
short endd=f.tellp();


while(1){
        short seek=(hashh-1)*((3*sizeof(index))+1);
        f.seekg(seek,ios::beg);
f.read((char*)&tg,sizeof(tg));
//cout<<tg.offset<<endl;
if(tg.offset!=-1&& !strcmp(tg.pk,name)){
    f.seekg(seek,ios::beg);
    f.read((char*)&tg,sizeof(index));
    short sek=tg.offset;
    f.seekg(seek,ios::beg);
    tg.offset=-5;
      f.write((char*)&tg,sizeof(index));
      student s;
    fstream file;
file.open("student.txt",ios::in | ios::binary);
file.seekg(sek,ios::beg);
file.read((char*)&s,sizeof(s));
cout<<s.Name<<'|'<<s.GPA<<'|'<<s.Address<<'|'<<s.Mobile<<'|'<<s.Department<<'|'<<endl;
cout<<"DELETED!!!"<<endl;

    break;
    }
    else if(tg.offset==-1 || strcmp(tg.pk,name)){
        f.seekg(seek+sizeof(index),ios::beg);
         f.read((char*)&tg,sizeof(index));
        if(tg.offset!=-1&& !strcmp(tg.pk,name)){
    f.seekg(seek+sizeof(index),ios::beg);
    f.read((char*)&tg,sizeof(index));
    short sekk=tg.offset;
     f.seekg(seek+sizeof(index),ios::beg);
     tg.offset=-5;
    f.write((char*)&tg,sizeof(index));
      student s;
    fstream file;
file.open("student.txt",ios::in | ios::binary);
file.seekg(sekk,ios::beg);
file.read((char*)&s,sizeof(s));
cout<<s.Name<<'|'<<s.GPA<<'|'<<s.Address<<'|'<<s.Mobile<<'|'<<s.Department<<'|'<<endl;
cout<<"DELETED!!!"<<endl;

    break;
    }
    else if(tg.offset==-1 || strcmp(tg.pk,name)){
     //    hashh=hashh+h2(name);
     f.seekg(seek+2*sizeof(index),ios::beg);
         f.read((char*)&tg,sizeof(index));
 if(tg.offset!=-1&& !strcmp(tg.pk,name)){
    f.seekg(seek+2*sizeof(index),ios::beg);
    f.read((char*)&tg,sizeof(index));
    short sekk=tg.offset;
     f.seekg(seek+2*sizeof(index),ios::beg);
     tg.offset=-5;
    f.write((char*)&tg,sizeof(index));
      student s;
    fstream file;
file.open("student.txt",ios::in | ios::binary);
file.seekg(sekk,ios::beg);
file.read((char*)&s,sizeof(s));
cout<<s.Name<<'|'<<s.GPA<<'|'<<s.Address<<'|'<<s.Mobile<<'|'<<s.Department<<'|'<<endl;
cout<<"DELETED!!!"<<endl;

    break;
    }
     else if(tg.offset==-1 || strcmp(tg.pk,name)){
         hashh=hashh+1;
     }
    }
    }
    if(seek>endd){
   hashh=hashh%100;
f.close();
f.open("index.txt",ios::in |ios::out |ios::binary);
}
if(hashh==hashstop){
    cout<<"student that you want delete him/her is not founded !!"<<endl;
    break;
}


}
f.close();

}
int main()
{
 //build_index_and_student();
   show_index_file();

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
