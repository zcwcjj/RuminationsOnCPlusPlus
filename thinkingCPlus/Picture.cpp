#include<iostream>
#include"Picture.hpp"
#include<string.h>
using namespace std;
//class P_Node;
//class Picture {
//每次打印一行，此处宽度设为0
ostream& operator<<(ostream& os,const Picture & picture)
{
  int ht = picture.height();
  for (int i=0; i<ht; ++i)
    {
      picture.display(os, i, picture.width());
      os<<endl;
    }
  return os;
}

Picture reframe(const Picture & pic,char c,char s,char t)
{
  return pic.p->reframe(c,s,t);
}

Picture  frame(const Picture& pic)
{
  Frame_Pic *p=new Frame_Pic(pic);
  return Picture(p);
}

Picture operator&(const Picture& p1, const Picture& p2)
{
  return new Vcat_Pic(p1,p2);
}

Picture operator|(const Picture& p1, const Picture&p2)
{
  return new Hcat_Pic(p1,p2);
}
Picture:: Picture()
{
  p = NULL;    
}

Picture::Picture(P_Node * p_node)
{
  p=p_node;
}
Picture::Picture(const char * const *str, int n)
{
   p=new String_Pic(str, n);
    //  p->use=1;
}

Picture:: Picture(const Picture &orig)
{
  orig.p->use++;
  p=orig.p;  
}

Picture:: ~Picture()
{
 // cout<<"delete:Picture!\n";
    if (--p->use == 0)
      delete p; 
};

  //不声明成为友元
Picture& Picture:: operator=( const Picture& orig)
{
    //无需判断是否自我赋值，因为++ --已经达到效果,不会删除自身
    //if(this !=orig) return *this;

  
      
      orig.p->use++;
      if(p != NULL)
	{
	  if(--p->use == 0) delete p;
	}
      this->p = orig.p;

  return *this;
}

int Picture::height()const
{
  return p->height();
}

int Picture::width()const
{
  return p->width();
}

void Picture::display(ostream& o, int x, int y)const
{
  p->display(o,x,y);
}

/*-----------------------------------------------------------------------
 */
P_Node:: P_Node() :use(1){};
P_Node:: ~P_Node(){};
int P_Node::max(int x,int y)const
{
  return x > y ? x:y;
}

void P_Node::pad(ostream &os,int x,int y)
{
  for(int i=x; i<y; ++i) os<<" ";
}

String_Pic::String_Pic(const char * const * str,int n)
{
  data = new char*[n];
  size = n;
  for(int i=0; i<n ;++i)
    {
      //此处+1因为最后一个结尾符号'\n'不计算在内
      data[i]=new char[strlen(str[i])+1];
      strcpy(data[i],str[i]);
    }
}

String_Pic::~String_Pic()
{
  // cout<<"delete!"<<endl;
  for(int i=0; i<size; ++i)
    {
      delete[] data[i];
    }
  delete[] data;
}

int String_Pic::height()const
{
  return size;
}

int String_Pic::width()const
{
  int w=0;
  for (int i=0; i<size; ++i)
    {
      w=max(strlen(data[i]),w);
    };
  return w;
}

//输入行号与宽度，打印该行,不足部分用空格补
void String_Pic::display(ostream &os,int row, int width)const
{
  int start =0;
  if(row >=0 && row <height())
    {
      os<<data[row];
      start = strlen(data[row]);
    }
  pad(os,start,width);
}

Picture String_Pic::reframe(char c,char s,char t)
{
  //因为Picture(P_Node*)没有对use++;
  use++;
  return this;
}
//------------------------------------------------------------
Frame_Pic::Frame_Pic(const Picture& pic,char c,char s,char t)
{
  p=pic;
  corner=c;
  sideborder=s;
  topborder=t;
}
int Frame_Pic::height() const
{
  return p.height()+2;
}
int Frame_Pic::width() const
{
  return p.width()+2;
}

void Frame_Pic::display(ostream &os,int row, int wd)const
{
   if ( row<0 || row >=height() )
     { pad(os,0,wd); }
   else
     {
       if(row==0 || row == height()-1)
	 {
	   os <<corner;
	   for (int i=1; i<width()-1; ++i) os<<topborder;
	   os<<corner;
	 }
       else 
	 {
	   os<<sideborder;
	   p.display(os,row-1,p.width());
	   os<<sideborder;
	 }
	pad(os,width(),wd);	  
     }
   
 }
Picture Frame_Pic::reframe(char c,char s,char t)
{
  //递归
  return new Frame_Pic(::reframe(p,c,s,t),c,s,t);
} 
//-----------------------------------------------------------
Vcat_Pic::Vcat_Pic(const Picture &p1, const Picture &p2)
{
  top = p1;
  bottom = p2;
}

int Vcat_Pic::height()const
{
  return top.height()+bottom.height();
}

int Vcat_Pic::width()const
{
  return max(top.width(),bottom.width());
}
void Vcat_Pic::display(ostream &os, int row,int wd)const
{
  if (row >=0 && row < top.height())
    top.display(os,row,wd);
  else if (  row<top.height()+bottom.height())
    bottom.display(os, row-top.height(), wd);
  else 
    {
      pad(os,0,wd);
    }

}
Picture Vcat_Pic::reframe(char c,char s,char t)
{
  //此处use++ 没有是因为采用了new操作符.
  return new Vcat_Pic(::reframe(top,c,s,t),::reframe(bottom,c,s,t));
}
//-------------------------------------------------------
Hcat_Pic::Hcat_Pic(const Picture &p1,const Picture &p2)
{
  left = p1;
  right = p2;
}
int Hcat_Pic::height()const
{
  return max(left.height(),right.height());
}
int Hcat_Pic::width()const
{
  return left.width()+right.width();
}

void Hcat_Pic::display(ostream& os, int row,int wd)const
{
  left.display(os,row,left.width());
  right.display(os,row,right.width());
  pad(os,width(),wd);
}
Picture Hcat_Pic::reframe(char c,char s, char t)
{
  return new Hcat_Pic(::reframe(left,c,s,t), ::reframe(right,c,s,t));
}
