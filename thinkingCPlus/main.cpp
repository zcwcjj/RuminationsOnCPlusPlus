#include<iostream>
#include"Picture.hpp"
using namespace std;
int main(int argc,char ** argv)
{
  
  char * a[]={"Paris","is not","the same as usual"};
char *b[]={"god","bless me","avoid","of illness!"};    
  Picture p1(a,sizeof(a)/4);
  // cout<<frame(p1)<<endl;
  Picture p6(b,sizeof(b)/4);
  Picture p7=frame(p6);
  Picture p2(p1);
  // cout<<p6<<endl;
  Picture p3=frame(p1);
  Picture p4=p3|p1;
  Picture p5; 
  //  cout<<p3<<endl;;
 
 p5=p6&p6&p1&p2&p3|p4;
  cout<<frame(p5)<<endl;  
  cout<<reframe(frame(p5),'*','*','*')<<endl;
 p5=p1|p2&p7;
 // cout<<frame(p5)<<endl;
}
