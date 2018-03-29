#include <iostream>
#include<stdlib.h>
#include<bits/stdc++.h>
using namespace std;
class mcc{
  public:
    int key;
   //constructor
    mcc(int k)
    {
      if(k==-1)key = 3;else key = k;
      cout<<"key will be used is "<<key<<endl;
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
                  s1[i]=(((s[i] - 'a') + key) % 26) + 'a';
                  cout<<s1[i]<<endl;
                }
                //for upper case characters
                else if(s[i]>='A'&&s[i]<='Z')
                  {
                    s1[i]=(((s[i] - 'A') + key) % 26) + 'A';
                  }
                else s1[i] = s[i]; 
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
  int k=-1;
  string input;
  cout<<"enter the string to be encrypted : ";
  getline(cin,input);
  cout<<"enter the  key Other wise we will use default key as 3 :\n";
  cin>>k;
  //making a object
  mcc x(k);
  string ct  = x.encrytpion(input);
  cout<<"returned ct is :"<<ct<<endl;
  string dt = x.decryption(ct);
  cout<<"decr text is : "<<dt<<endl;

  return 0;
}
