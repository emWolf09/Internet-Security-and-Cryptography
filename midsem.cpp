//Mahesh nagarwal
//ID 2015KUCP1043
//g++ midsem.cpp


#include<iostream>
#include<math.h>
using namespace std;

int p_bit[64] ={0};
string ct="";
string encrypted_text="";
int iv[64] = {1,0,1,0,1,0,1,0,
                          1,0,1,0,1,0,1,0,
                          1,0,1,0,1,0,1,0,
                          1,0,1,0,1,0,1,0,
                          1,0,1,0,1,0,1,0,
                          1,0,1,0,1,0,1,0,
                          1,0,1,0,1,0,1,0,
                          1,0,1,0,1,0,1,0,};
int key = 4;


/////
void converttobinary(string p)
{
  int ch=0;
  for(int j=0;j<p.length();j++)
    {
      char c = p[j];
      int bits[8], i;

      for(i = 0; i < 8; i++)
    	   bits[i] = ((1<<i) & c) != 0 ? 1:0;

      for(i = 7; i >= 0; i--)
       	p_bit[7-i+ch]=bits[i];

      ch+=8;

    }
}


void converttobinary_forIV(string p)
{
  int ch=0;
  for(int j=0;j<p.length();j++)
    {
      char c = p[j];
      int bits[8], i;

      for(i = 0; i < 8; i++)
    	   bits[i] = ((1<<i) & c) != 0 ? 1:0;

      for(i = 7; i >= 0; i--)
       	iv[7-i+ch]=bits[i];

      ch+=8;

    }
}



void get_text_bits(string p)
{
  converttobinary(p);
}


void perform_xor()
{
  for(int i=0;i<64;i++)
    {
      p_bit[i] = p_bit[i]^iv[i];
    }
}
//convert binarytostring
void converttostring()
{
  int binary[8],rem,base=2,dec;
  int c=0;
  for(int j=0;j<8;j++)
    {
      for(int k=0;k<8;k++)
        binary[k] = p_bit[k+c];

      int i=7;
      while(i>=0)
       {
         rem = binary[i];
         dec+=rem*pow(base,7-i);
         i--;
       }
       char ch=(char)dec;
       //cout<<ch<<"\t";
       ct+=ch;
       c+=8;
    }
}

void perform_encryption()
{
  for(int i=0;i<8;i++)
    {
      char ch = ct[i];
      ct[i]=(char)(4+(int)ch);
    }

}

int main()
{
    string pt = "welcome to cryptography and network security";
    string pt1 = "maheshna";
    int l = pt.length();
    cout<<"input string length is "<<l<<endl;
    if(l%8!=0)
        {
            //padding
            while(pt.length()%8!=0)
              {
                pt+="x";
              }

        }
        //cout<<pt<<endl;


    for(int j=0;j<pt.length();)
        {
          string p;
            for(int i=0;i<8;i++)
              {
                 p +=pt[i+j];

              }
              //cout<<p<<endl;
          //change the string into 64 bit
          get_text_bits(p);

          //printing the bits of text
          /*for(int i=0;i<64;i++)
            {
              cout<<p_bit[i]<<"\t";
              if((i+1)%8==0){
                //cout<<endl<<"i is"<<i+1;
                cout<<endl;
              }
            }
            cout<<endl;
            */
          //perform xor on text bits and initial_vector bits
          perform_xor();
          /*
          //printing the bits of text
          for(int i=0;i<64;i++)
            {
              cout<<p_bit[i]<<"\t";
              if((i+1)%8==0){
                //cout<<endl<<"i is"<<i+1;
                cout<<endl;
              }
            }
            */
          //convert into string from text bits
          converttostring();
          //cout<<"xor output in string is "<<ct<<endl;
          //cout<<"size of ct is "<<ct.length()<<endl;

          //perform encryption
          perform_encryption();
          //cout<<"chiper text output after encryption is "<<ct<<endl;
          //cout<<"size of ct is "<<ct.length()<<endl;


          encrypted_text+=ct;

          //update initial_vector
          converttobinary_forIV(ct);
          ct="";

          //add encrypted text into ct
          j+=8;

        }
        cout<<"encrypted_text is "<<encrypted_text<<endl;
        cout<<"length of encrypted_text is "<<encrypted_text.length()<<endl;
}
