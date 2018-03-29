#include <iostream>
#include<stdlib.h>
#include<bits/stdc++.h>
using namespace std;


class mcc{
  public:
    int key;
    //default constructor
    mcc()
    {
      //s = s1;
      key = 3;
    }//parameter constructor
    mcc(int k)
    {
      key = k;
    }
    string encrytpion(string s)
    {
      string s1=s;
      for(int i=0;i<s.length();i++)
        {
          if(s[i]!=' ')
            {
              //for lower case characters
              if(s[i]>='a'&&s[i]<='z')
                {
                  if(s[i]>'w')
                    {
                      if(s[i]=='x')s1[i] = 'a';
                      else if(s[i]=='y')s1[i]='b';
                      else if(s[i]=='z')s1[i]='c';

                    }

                    else {s1[i] = (char)(s[i]+key);//cout<<(char)(s[i]+key)<<endl;
                    }
                }
                //for upper case characters
                if(s[i]>='A'&&s[i]<='Z')
                  {
                    if(s[i]>'W')
                      {
                        if(s[i]=='X')s1[i] = 'A';
                        else if(s[i]=='Y')s1[i]='B';
                        else if(s[i]=='Z')s1[i]='C';

                      }

                      else {s1[i] = (char)(s[i]+key);//cout<<(char)(s[i]+key)<<endl;
                      }
                  }
                }
                else s1[i] = ' ';
            }




          return s1;
    }

  string decryption(string s)
    {
      string s1=s;
        for(int i=0;i<s.length();i++)
          {
            //skip spaces
            if(s[i]!=' ')
              {
                if(s[i]>='a'&&s[i]<='z')
                  {
                    s1[i] = s[i]-key;
                      if(s1[i]<'a')s1[i] = s1[i]+'z'-'a'+1;

                  }
                else if(s[i]>='A'&&s[i]<='z')
                  {
                    s1[i] = s[i]-key;
                      if(s1[i]<'A')s1[i] = s1[i]+'Z'-'A'+1;
                  }
              }
              else s1[i] = ' ';

          }


          return s1;
    }
};


int main()
{
  string input;
  cout<<"enter the string to be encrypted : ";
  getline(cin,input);
  mcc x;
  string ct  = x.encrytpion(input);
  cout<<"returned ct is :"<<ct<<endl;
  string dt = x.decryption(ct);
  cout<<"decr text is : "<<dt<<endl;
  return 0;
}
