#include<iostream>
#include<math.h>
#include <stdlib.h>
#include<stdio.h>

using namespace std;
//declaring matrix to global to use in various functions
float encrypt[3][1], decrypt[3][1],ct[3][1];
float a[3][3]={{6,24,1},{13,16,10},{20,17,15}}, c[3][3]={{6,24,1},{13,16,10},{20,17,15}}; //out key matrix
float b[3][3], mes[3][1]; //b is for inverse of key mes is for storing plain text into matrix form


string msg,ctext="",decrypt_text;
//to store given inputs length
int length_global=0;

//functions to be used
void getstarted(int);    //provides option to the user and take key and plain text as input form user
void inverse();        //finds inverse of key matrix
void encryption1();
void decryption1();

int main() {

    int choice;
    cout<<"\nENTER 0. msg is greater than length 3 \nENTER 1. msg is less than or equal length 3\n";
    cin>>choice;
    if(choice==1)
    {
      getstarted(choice);
      encryption1();
      decryption1();
    }
    else if(choice==0)
    {getstarted(choice);
    encryption1();
    decryption1();
    }

}

void getstarted(int choice) {
    int i, j,ch;

    cout<<"Enter 1.If you want to give your own key matrix that is inversible \nEnter 2. IF you you dont want to enter key matrix\n";
    cin>>ch;
    if(ch==1)
    {
      cout<<"enter key matrix:\n";
      for(i = 0; i < 3; i++)
          for(j = 0; j < 3; j++) {
              scanf("%f", &a[i][j]);
              c[i][j] = a[i][j];
          }
    }

    else if(ch==2)
    {
      cout<<"\nWe are using our own inbuilt key matrix(that is inversible):\n";
      for(int i=0;i<3;i++)
        {
          for(int j=0;j<3;j++)
            {
                cout<<a[i][j]<<"\t";
            }
            cout<<endl;
        }
    }

    if(choice==0)
    {
      cout<<"\nEnter a  letter string which have length of multiple of 3 otherwise we will add 'x' character at last it and encrypt it\n: ";
      cin>>msg;
      //making the msg to multiple of 3
      while(msg.length()%3!=0)
      {
        msg = msg + 'x';
      }
      cout<<"\nmassage after addig x at last if length is smaller than 3 is :="<<msg<<endl;
    }

    else if(choice ==1)
    {
      cout<<"\nenter a string of length 3 or less than 3 only\n";
      cin>>msg;
      length_global =msg.length();
      if(length_global>3)
        {
          cout<<"string should be less or equal 3 only\n";
          exit(-1);
        }
      while(msg.length()%3!=0)
      {
            msg = msg + 'x';
      }
      for(i = 0; i < 3; i++)
          {
            mes[i][0] = msg[i] - 97;
            //cout<<mes[i][0]<<endl;
          }
      cout<<"\nmassage after addig x at last if length is smaller than 3 is :="<<msg<<endl;
    }
    //to equal the length
    decrypt_text = msg;

}



void encryption1() {
    int i, j, k;
    int n = msg.length()/3;
    int flag=0;
    cout<<"\nEncrypted string is: ";
    while(n>0)
    {
      //getting mes matrix for 3 characters
      for(i = 0; i < 3&&flag<msg.length(); i++,flag++)
          {
            mes[i][0] = msg[flag] - 97;
            //cout<<mes[i][0]<<endl;
          }
          for(i = 0; i < 3; i++)
              for(j = 0; j < 1; j++)
                  for(k = 0; k < 3; k++)
                      encrypt[i][j] = encrypt[i][j] + a[i][k] * mes[k][j];


          for(i = 0; i < 3; i++)
              {
                cout<<(char)(fmod(encrypt[i][0], 26) + 97);
                ctext= ctext+(char)(fmod(encrypt[i][0], 26) + 97);
              }

          n--;


    }
    cout<<endl;

}

void decryption1() {
    int i, j, k;

    inverse();
    int n=msg.length()/3,flag=0;
    cout<<"\nDecrypted string is: ";
    while(n>0)
    {
      //getting mes matrix for 3 characters
      for(i = 0; i < 3&&flag<msg.length(); i++,flag++)
          {
            mes[i][0] = msg[flag] - 97;
            //cout<<mes[i][0]<<endl;
          }
          for(i = 0; i < 3; i++)
              for(j = 0; j < 1; j++)
                  for(k = 0; k < 3; k++)
                      encrypt[i][j] = encrypt[i][j] + a[i][k] * mes[k][j];

      for(i = 0; i < 3; i++)
          for(j = 0; j < 1; j++)
              for(k = 0; k < 3; k++)
                  decrypt[i][j] = decrypt[i][j] + b[i][k] * encrypt[i][0];
    /*  for(i = 0; i < 3; i++)
         cout<<(char)(fmod(decrypt[i][0], 26) + 97);*/
      n--;
    }
    for(int i=0;i<msg.length();i++)
    if(decrypt_text[i]!='x')cout<<decrypt_text[i];

    cout<<"\n";
}

//we will store inverse of key in matrix b
void inverse() {
    int i, j, k;
    float p, q;

    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++) {
            if(i == j)
                b[i][j]=1;
            else
                b[i][j]=0;
        }

    for(k = 0; k < 3; k++) {
        for(i = 0; i < 3; i++) {
            p = c[i][k];
            q = c[k][k];

            for(j = 0; j < 3; j++) {
                if(i != k) {
                    c[i][j] = c[i][j]*q - p*c[k][j];
                    b[i][j] = b[i][j]*q - p*b[k][j];
                }
            }
        }
    }
    for(i = 0; i < 3; i++)
       for(j = 0; j < 3; j++)
           b[i][j] = b[i][j] / c[i][i];

   cout<<"\n\nInverse Matrix is:\n";
   for(i = 0; i < 3; i++) {
       for(j = 0; j < 3; j++)
           cout<<b[i][j]<<" ";

       cout<<"\n";
   }
}
