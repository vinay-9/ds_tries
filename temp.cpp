#include<bits/stdc++.h>

using namespace std;
int main (){
    string tp= "vinay,lord ganeshas name";
                 int pos = tp.find(",");
                string word= tp.substr(0, pos);
                string meaning = tp.substr(pos+1, tp.length());
                cout<< "word "<< word << " meaning "<< meaning<< endl;
}