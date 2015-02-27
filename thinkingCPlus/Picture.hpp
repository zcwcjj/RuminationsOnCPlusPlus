#include<iostream>
using namespace std;
class P_Node;
class Picture {
  friend ostream& operator<<(ostream&,const Picture &);
  friend Picture frame(const Picture&);
  friend Picture operator&(const Picture&, const Picture&);
  friend Picture operator|(const Picture&, const Picture&);
  friend Picture reframe(const Picture&,char c, char s, char t);
  //增加以下4个友元是为了干什么
  friend class String_Pic;
  friend class Frame_Pic;
  friend class Vcat_Pic;
  friend class Hcat_Pic;

public:
  Picture();
  Picture(const char * const *, int);
  Picture(const Picture &);
  ~Picture();
  //不声明成为友元
  Picture& operator=( const Picture&);
private:
  Picture(P_Node *);
  P_Node * p;
  int height() const;
  int width() const;
  void display(ostream &,int,int)const;
  
};

//负责析构，引用技术
class P_Node{
  friend class Picture;
  
  friend Picture reframe(const Picture &,char,char,char);
  virtual Picture reframe(char ,char,char)=0;
protected:
  P_Node();
  virtual ~P_Node();
  virtual int height() const = 0;
  virtual int width() const = 0;
  virtual void display(ostream &,int ,int) const = 0;
  
  int max(int x,int y)const;
  static void pad(ostream&, int , int);
  int use;
};


class String_Pic: public P_Node{
  friend class Picture;

  String_Pic(const char * const *,int);
  ~String_Pic();
  int height() const;
  int width()const ;
  void display(ostream&,int ,int )const;
  Picture reframe(char,char,char);
  char **data;
  int size;
  
  //static void pad(ostream&,int,int);
};

class Frame_Pic: public P_Node{
  //does here need friend class Picture?
  friend class Picture;
  //frame 函数在Picture 和 Frame_Pic 中出现了2次
  friend Picture frame(const Picture &);
  //friend Picture reframe(Picture &,char,char,char);
  Picture reframe(char,char,char);
  Frame_Pic(const Picture &,char ='+',char='|',char ='-');
  int height() const;
  int width()const ;
  void display(ostream&,int ,int )const;
  Picture p;
 char corner,sideborder,topborder;
};

class Vcat_Pic: public P_Node{
  friend Picture operator&(const Picture &,const Picture &);
  friend class Picutre;

  Vcat_Pic(const Picture &,const Picture &);
  int height() const;
  int width()const ;
  void display(ostream&,int ,int )const;  
  Picture reframe(char,char,char);
  Picture top, bottom;
 
};

class Hcat_Pic: public P_Node{
  friend Picture operator |(const Picture &,const Picture &);
  friend class Picture;

  Hcat_Pic(const Picture &,const Picture &);
  int height() const;
  int width()const ;
  void display(ostream&,int ,int )const;
  Picture reframe(char,char,char);  
  Picture left,right;
};

