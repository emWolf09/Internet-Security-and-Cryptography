#include <iostream>
#include<bitset>
#include<math.h>
typedef unsigned int INT;
using namespace std;

/*------------------------------------------------------------------- global data------------------------------------*/
string plaintext;
int pt[64]=
{
  0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,1,
  0,1,1,0,1,0,0,1,0,1,1,1,0,1,0,0,
  0,1,1,0,1,0,1,1,0,1,1,0,1,1,1,1,
  0,1,1,1,0,1,0,0,0,1,1,0,0,0,0,1

};
string chiperText="";
int ct[64] = {0};

int p[4][16] = {{0}};


int key[128] =
{
  0,1,1,0,1,1,0,1,0,1,1,0,0,0,0,1,
  0,1,1,0,1,0,0,0,0,1,1,0,0,1,0,1,
  0,1,1,1,0,0,1,1,0,1,1,0,1,0,0,0,
  0,1,1,0,1,1,1,0,0,1,1,0,0,0,0,1,
  0,1,1,0,0,1,1,1,0,1,1,0,0,0,0,1,
  0,1,1,1,0,0,1,0,0,1,1,1,0,1,1,1,
  0,1,1,0,0,0,0,1,0,1,1,0,1,1,0,0,
  0,1,1,0,1,1,0,1,0,1,1,0,0,0,0,1,
};

//subkey

int key_count =0;
int k[6][16]={{0}};

//intermeddietee result store variable
//for multiplication

int m[4][16] = {{0}};
//for multiplication

int a[4][16] = {{0}};
//for multiplication

int x[6][16] = {{0}};

//to store string format of binary of decimal
int result_bitset[16] ={0};
/***********************************************************************operation*****************************************/
void converttobinary()
{
  int ch=0;
  for(int j=0;j<plaintext.length();j++)
    {
      char c = plaintext[j];
      int bits[8], i;

      for(i = 0; i < 8; i++)
    	   bits[i] = ((1<<i) & c) != 0 ? 1:0;

      for(i = 7; i >= 0; i--)
       	pt[7-i+ch]=bits[i];

      ch+=8;

    }
}


//convert binarytostring
void binartTostring()
{
  int binary[8],rem,base=2,dec;
  int c=0;
  for(int j=0;j<8;j++)
    {
      for(int k=0;k<8;k++)
        binary[k] = ct[k+c];

      int i=7;
      while(i>=0)
       {
         rem = binary[i];
         dec+=rem*pow(base,7-i);
         i--;
       }
       char ch=(char)dec;
       //cout<<ch<<"\t";
       chiperText+=ch;
       c+=8;
    }
}
//function to perform shifting
void get_shifting()
{
  int temp;
  for(int i=0;i<25;i++)
    {
      temp = key[0];
      for(int j=0;j<127;j++)
        {
          key[j] = key[j+1];
        }
        key[127] = temp;
    }
    return;
}



//function to get key k1 to k6
void get_key()
{
  int r_count = 6-key_count;
  //get key which are not in used
  for(int i=0;i<key_count;i++)
    {
      for(int j=0;j<16;j++)
        {
          k[i][j] = key[j+i*16];
          //cout<<k[i][j]<<"\t";
        }
        //cout<<endl;
    }
    //perform shifting
    get_shifting();
   //after shifting get remainig keys
  for(int i=0;i<r_count;i++)
    {
      for(int j=0;j<16;j++)
        {
          k[i+key_count][j] = key[j+i*16];
          //cout<<k[i+key_count][j]<<"\t";
        }
        //cout<<endl;
    }
    //update key_count for next round
    key_count = 8-r_count;
    //cout<<key_count<<endl;
}

//function to get p
void get_p()
{
  for(int i=0;i<4;i++)
    {
      for(int j=0;j<16;j++)
        {
          p[i][j] = pt[j+i*16];
          //cout<<p[i][j]<<"\t";
        }
        //cout<<endl;
    }
}

//change the given 16 bit array into decimal
int get_decimal(int *a,int m)
{
  string s="";
  for(int i=0;i<16;i++)
    {
      if(*(a+m+i)==0)
      s+='0';
      else s+='1';
    }
    //cout<<"string is pi :"<<s<<endl;
  bitset<16> bitset1(s);
  INT decimal = bitset1.to_ulong();
  return decimal;
}

//change the given decimal into 16 bit binary
void get_binary(int value)
{
  bitset<16> bitset1(value);
  string s1 = bitset1.to_string();
  for(int i=0;i<s1.length();i++)
    {
      if(s1[i]=='0')
        result_bitset[i] =0;
      else result_bitset[i] =1;
    }
}


int main()
{
  cout<<"Enter the plaintext of 8 character :";
  cin>>plaintext;
  converttobinary();
  int t=8;
  get_p();
  //8 times loop
  while(t>0)
    {
      get_key();
      int p1 = get_decimal((int *)p,0);
      //cout<<endl<<"decimal value of p1 = "<<p1<<endl;
      int k1 = get_decimal((int *)k,0);
      //cout<<endl<<"decimal value of k1 = "<<k1<<endl;
      int p2 = get_decimal((int *)p,1);
      //cout<<endl<<"decimal value of p2 = "<<p2<<endl;
      int p3 = get_decimal((int *)p,2);
      //cout<<endl<<"decimal value of p3 = "<<p3<<endl;
      int p4 = get_decimal((int *)p,3);
      //cout<<endl<<"decimal value of p4 = "<<p4<<endl;
      int k2 = get_decimal((int *)p,1);
      //cout<<endl<<"decimal value of k2 = "<<k2<<endl;
      int k3 = get_decimal((int *)p,2);
      //cout<<endl<<"decimal value of k3 = "<<k3<<endl;
      int k4 = get_decimal((int *)p,3);
      //cout<<endl<<"decimal value of k4 = "<<k4<<endl;
      int k5 = get_decimal((int *)p,4);
      //cout<<endl<<"decimal value of k5 = "<<k5<<endl;
      int k6 = get_decimal((int *)p,5);
      //cout<<endl<<"decimal value of k6 = "<<k6<<endl;

      //step1  p1*k1
      int m1 = (p1*k1)%(int)(pow(2,16)+1);

      //step 2 p2+k2
      int a1 = (p2+k2)%(int)(pow(2,16));
      //step3 p3+k3

      int a2 = (p3+k3)%(int)(pow(2,16));
      //step4 p4*k4
      int m2 = (p4*k4)%(int)(pow(2,16)+1);

      //step 5
      int x1 = m1^a2;

      //step 6
      int x2 = m2^a1;

      //step 7
      int m3 = x1^k5;

      //step8
      int a3 = (x2+m3)%(int)(pow(2,16));

      //9

      int m4 = (a3*k6)%(int)(pow(2,16)+1);
      //10
      int a4 = (m3+m4)%(int)(pow(2,16));

      //11
      int x3 = m1^m4;
      //12
      int x4 = a2^m4;
      //13
      int x5 = a1^a4;
      //14
      int x6 = m2^a4;

      //if last round
      if(t==15)
        {
            x3= (x3*k1)%(int)(pow(2,16)+1);
            x4 = (m4+k2)%(int)(pow(2,16));
            x5 = (x5+k3)%(int)(pow(2,16));
            x6= (x6*k4)%(int)(pow(2,16)+1);
        }
      //get binary p[0] from x3
      get_binary(x3);
      for(int i=0;i<16;i++)
        {
          p[0][i] = result_bitset[i];
        }
      //p[1]
      get_binary(x4);
      for(int i=0;i<16;i++)
        {
          p[1][i] = result_bitset[i];
        }
      //p[2]
      get_binary(x5);
      for(int i=0;i<16;i++)
        {
          p[2][i] = result_bitset[i];
        }
      //p[3]
      get_binary(x6);
      for(int i=0;i<16;i++)
        {
          p[3][i] = result_bitset[i];
        }

      t--;

    }
     for(int i=0;i<4;i++)
       {
         for(int j=0;j<16;j++)
           {
             ct[i*16+j] = p[i][j];
             //cout<<ct[i*16+j]<<"\t";

           }
           //cout<<endl;
       }

      binartTostring();
      cout<<"\n chiperText is  8 character :"<<chiperText<<endl;



  return 0;
}
