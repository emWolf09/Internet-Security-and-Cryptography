#include<iostream>
#include<math.h>
#include <stdlib.h>
#include<stdio.h>

using namespace std;

class playfair{
  public:
    string key,pt,ct;
    char m[5][5];
    int count[256]={0};int k;
    //constructor
    playfair(string k,string pt)
      {
        key = k;
        this->pt =pt;
        this->k=0;
        ct="";
        for(int i=0;i<5;i++)for(int j=0;j<5;j++)m[i][j]='a';
      }
    void print_matrix()
        {
            for(int i=0;i<5;i++)
              {
                for(int j=0;j<5;j++)
                cout<<m[i][j]<<"\t";
                cout<<endl;
              }
              cout<<endl;
        }
    void print_count()
    {
      for(int i=0;i<255;i++)
        {
          char ch=i;
          cout<<"for ch = "<<ch<<" count[i] is "<<count[i]<<"\n";
        }
    }

    void fill_matrix()
      {
        //fill all the charaters of key into matrix
        for(int i=0;i<key.length();i++)
          {
            int r=k/5,c=k%5;
            //check whether it is already present in matrix
            if(count[key[i]]==0)
              {
                //special case when key is i or j
                if(key[i]=='i'||key[i]=='j')
                  {
                    //check whether it is already filled in matrix
                    if(count['i']==1||count['j']==1)
                      continue;
                    else if(count['i']==0&&count['j']==0)
                      {
                        count['i']++;count['j']++;
                        m[r][c]='i';
                        k++;
                        continue;
                      }
                  }
                count[key[i]]++;
                m[r][c]=key[i];
                k++;

              }
            else if(count[i]==1)
              continue;
          }

        //fill rest of the elements of the matrix by remaining charaters of alphabet
        for(char ch='a';ch>='a'&&ch<='z'&&k<25;ch++)
          {
            int r=k/5,c=k%5;
            if(count[ch]==0)
              {
                m[r][c]=ch;
                count[ch]++;
                k++;
              }
          }
      }

    int findInMatrix(char ch)
      {

              //
      }

    void get_ct()
    {
      //making line divisble by 2
      padding:
      if(pt.length()%2!=0)
        {
          pt+='x';
          goto padding;
        }
      // before removing repeating char
        //cout<<endl<<pt<<endl;
      //removing repeating charaters by replacing with x
      for(int i=0;i<pt.length();)
        {
          if(pt[i]==pt[i+1])
            {
              pt[i+1]='x';
              i+=2;
            }
          else if(pt[i]!=pt[i+1])
            {
              i+=2;
            }
        }
      //cout<<endl<<pt<<endl;
      //start encryption
      for(int i=0;i<pt.length();)
        {
          char ch1=pt[i],ch2=pt[i+1],ct1,ct2;
          int r1,r2,c1,c2;
          //find location of i and i+1 charaters into matrix
          for(int i1=0;i1<5;i1++)
            for(int i2=0;i2<5;i2++)
              {
                if(ch1==m[i1][i2]){r1=i1;c1=i2;}
                else if(ch2==m[i1][i2]){r2=i1;c2=i2;}
              }

          //if both are in same row
          if(r1==r2){
              ct1 = m[r1][(c1+1)%5];
              ct2 = m[r2][(c2+1)%5];
              ct+=toupper(ct1);
              ct+=toupper(ct2);
          }
        else if(c1==c2)
          {
            ct1 = m[(r1+1)%5][c1];
            ct2 = m[(r2+1)%5][c2];
            ct+=toupper(ct1);
            ct+=toupper(ct2);

          }
        else if(r1!=r2&&c1!=c2)
          {
            ct1 = m[r1][c2];
            ct2 = m[r2][c1];
            ct+=toupper(ct1);
            ct+=toupper(ct2);

          }



          i+=2;
        }
        cout<<"\nchiper text is :"<<ct<<endl;
    }
};

int main()
{
  string key,pt;
  cout<<"enter the key without spaces only containing alphabet :";
  cin>>key;
  cout<<"\nenter the plaintext without spaces only containing alphabet :";
  cin>>pt;
  playfair p(key,pt);
  //p.print_matrix();
  //cout<<endl;
  p.fill_matrix();
  p.get_ct();
  //p.print_matrix();
  cout<<endl;
}
