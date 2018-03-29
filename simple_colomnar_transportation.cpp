#include<bits/stdc++.h>
#include<iostream>
using namespace std;

int main()
{
  string key;
  cout<<"Enter the key with no repeating characters :";
  cin>>key;
  int k;
  k = key.length();

  string pt;
  cout<<"Enter the plain text :";
  cin.ignore();
  getline(cin,pt);

  //making matrix
  char m[k][k];

  //inserting in the matrix
  for(int i=0;i<k;i++)
    {
      m[0][i] = key[i];
      cout<<m[0][i]<<"\t";
    }
    cout<<endl;
    //to keep length of string pt
    int counter = 0;
  for(int i=1;i<k;i++)
    {
      for(int j=0;j<k;j++)
        {
          //check pt is not finishef
          if(counter<pt.length())
           {
             m[i][j] = pt[counter];
             cout<<m[i][j]<<"\t";
             counter++;
           }
           else {
             m[i][j] = '0';
             cout<<m[i][j]<<"\t";
           }
        }
        cout<<endl;
    }

  //getting the chiper text
  std::string ct = "";
  int key_index[k];
  int in = 0;char min ,x='a';
  for(int i=0;i<k;i++)
    {
      min ='z';
      for(int j=0;j<k;j++)
        {

          if(key[j]<=min)
          {
            if(i>0&&key[j]<=x)continue;
            min = key[j];
            in = j;
          }
        }
        x = key[in];
        //cout<<"index is ="<<in<<endl;
       //now in contains minimum remaining characters index
       for(int p=1;p<k;p++)
         {
           ct=ct+m[p][in];
         }
         ct+=" ";


    }
    cout<<"\nct is "<<ct<<endl;

    /*-----------------------------*/
    //decryption process
    char n[k][k];
    for(int i=0;i<k;i++)
      {
        n[0][i] = key[i];
        //cout<<n[0][i]<<"\t";
      }
      //cout<<endl;

    //from ct we insert the text into the metrix
   in = 0; min ;x='a';
    int count = 0; //count is for contains the info about ct index
    for(int i=0;i<k;i++)
      {
        min ='z';
        for(int j=0;j<k;j++)
          {

            if(key[j]<=min)
            {
              if(i>0&&key[j]<=x)continue;
              min = key[j];
              in = j;
            }
          }
          x = key[in];
          //cout<<"index is ="<<in<<endl;
         //now in contains minimum remaining characters index
         for(int row=1;row<k;row++)
           {
             n[row][in] = ct[count++];

           }
           //cout<<endl;
           //row++;
           count++;


      }
      //printing the decryption matrix;
      cout<<endl<<"matrix created from chiper text is "<<endl;
      for(int i=0;i<k;i++)
        {
          for(int j=0;j<k;j++)
            {
              cout<<n[i][j]<<"\t";

            }
            cout<<endl;
        }

        //getting the plaintext from decryption matrix
        string decrypt_text="";
        for(int i=1;i<k;i++)
          {
            for(int j=0;j<k;j++)
            {
              if(n[i][j]=='0')goto x;
              decrypt_text+=n[i][j];
            }
          }
          x:
          cout<<endl<<"decrypt_text is "<<decrypt_text<<endl;

  return 0;

}
