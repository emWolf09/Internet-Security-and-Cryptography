#include<iostream>
#include <math.h>
using namespace std;
/*-----------------------------------------------------------------
to execute  use following command
  g++ dec_final.cpp
  ./a.out
--------------*/
/*------------------------------------data global-------------------------------------------------------------------------------------------------------------------*/
//plainText
string plainText,chiperText="";
//key
int key[64]=
{
  0,0,1,1,0,1,0,0,
  0,0,1,0,1,1,0,1,
  1,0,1,1,0,1,0,1,
  1,0,1,0,1,0,0,0,
  0,0,0,1,1,1,0,1,
  1,1,0,1,1,0,1,1,
  1,0,0,1,0,0,0,0,
  0,0,0,0,0,1,0,0
};

//pc-1 table
int pc_1[56]=
{
  57, 49, 41, 33, 25, 17,  9,
   1, 58, 50, 42, 34, 26, 18,
  10,  2, 59, 51, 43, 35, 27,
  19, 11,  3, 60, 52, 44, 36,

  63, 55, 47, 39, 31, 23, 15,
   7, 62, 54, 46, 38, 30, 22,
  14,  6, 61, 53, 45, 37, 29,
  21, 13,  5, 28, 20, 12,  4
};

//CD table
int cd[56]={0};

//number of circular shift round no. wise
int lcs[16]={1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

//pc2 table 6*8
int pc_2[48] =
{
  14, 17, 11, 24,  1,  5,
   3, 28, 15,  6, 21, 10,
  23, 19, 12,  4, 26,  8,
  16,  7, 27, 20, 13,  2,

  41, 52, 31, 37, 47, 55,
  30, 40, 51, 45, 33, 48,
  44, 49, 39, 56, 34, 53,
  46, 42, 50, 36, 29, 32
};

//subkey(48 bit 6*6) output of pc-2 table on lcs performed cd table
int subkey[48]={0};

//taken input
int block_input[64]={0};
//block after permutation
int block_Ipermuted[64]={0};

//initial permutation box
int ip_box[64] =
{
            58,    50,   42,    34,    26,   18,    10,    2,
            60,    52,   44,    36,    28,   20,    12,    4,
            62,    54,   46,    38,    30,   22,    14,    6,
            64,    56,   48,    40,    32,   24,    16,    8,
            57,    49,   41,    33,    25,   17,     9,    1,
            59,    51,   43,    35,    27,   19,    11,    3,
            61,    53,   45,    37,    29,   21,    13,    5,
            63,    55,   47,    39,    31,   23,    15,    7
};

//e table to be used on the 2nd half of the input block
int e_table[48] =
{
  32,  1,  2,  3,  4,  5,
   4,  5,  6,  7,  8,  9,
   8,  9, 10, 11, 12, 13,
  12, 13, 14, 15, 16, 17,

  16, 17, 18, 19, 20, 21,
  20, 21, 22, 23, 24, 25,
  24, 25, 26, 27, 28, 29,
  28, 29, 30, 31, 32, 1
};

//output of e_table
int e_table_output[48]={0};

//xor output
int xor_output[48]={0};

/*------s-boxes ------------*/


//3d array for s-boxe
int s[8][4][16]=
{
  {
    {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
    {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
    {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
    {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
  },
  {
                     {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
                     {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
                     {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
                     {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
  },
  {
                      {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
                      {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
                      {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
                      {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
  },
  {
                     {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
                     {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
                     {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
                     {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
  },
  {
                   {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
                   {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
                   {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
                   {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
 },
 {
                    {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
                    {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
                    {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
                    {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
 },
 {
                   {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
                   {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
                   {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
                   {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
 },
 {
                    {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
                    {1,15,13,8,10,3,7,4,12,5,6,11,10,14,9,2},
                    {7,11,4,1,9,12,14,2,0,6,10,10,15,3,5,8},
                    {2,1,14,7,4,10,8,13,15,12,9,9,3,5,6,11}
 },
};

//output OF s box 32 bit
int s_box_output[32]={0};

//last permutation
int final_permutation[32]=
{
   16,7,20,21,
   29,12,28,17,
   1,15,23,26,
   5,18,31,10,
   2,8,24,14,
   32,27,3,9,
   19,13,30,6,
   22,11,4,25
};

//final permutation output
int final_permutation_output[32]={0};

//matrix to store rotated final_permutation_output
int rotated_final_permutation_output[32]={0};

//store final xor operation output
int xor_final_output[32]={0};
/*-------------------------------------------------------------------------functions--------------------------------------------------------------------------------------*/
//convert string to binary
void converttobinary()
{
  int ch=0;
  for(int j=0;j<plainText.length();j++)
    {
      char c = plainText[j];
      int bits[8], i;

      for(i = 0; i < 8; i++)
    	   bits[i] = ((1<<i) & c) != 0 ? 1:0;

      for(i = 7; i >= 0; i--)
       		block_input[7-i+ch]=bits[i];

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
        binary[k] = block_Ipermuted[k+c];

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


//print block input block and initial permutated block
void print_block_function(int choice)
    {
        //choice is 1 for input block
        //2 for frst time permutated block
          if(choice==1)
            {
              int c=0;
              for(int i=0;i<64;i++)
                {
                  cout<<block_input[i]<<"\t";
                  c++;
                  if(c==8)
                    {
                      c=0;
                      cout<<endl;
                    }
                }
            }
            else if(choice==2)
              {
                int c=0;
                for(int i=0;i<64;i++)
                  {
                    cout<<block_Ipermuted[i]<<"\t";
                    c++;
                    if(c==8)
                      {
                        c=0;
                        cout<<endl;
                      }
                  }
              }
    }

//apply initial permutation on input block
void ip_on_input_block()
{
  for(int i=0;i<64;i++)
    {
      block_Ipermuted[i]= block_input[ip_box[i]-1];
    }
}

//print cd table
void print_cd_table()
{
  int c=0;
  for(int i=0;i<56;i++)
    {

      cout<<cd[i]<<"\t";
      c++;
      if(c==7){c=0;cout<<endl;}
    }
}
//functio to fill cd table from pc-1 table
void get_cd_table_from_pc1()
{
  for(int j=0;j<56;j++)
    {
          cd[j] = key[pc_1[j]-1];
    }
}

//left shift circular operation on cd table where round number (0 to 15) is passed
void lcs_operation(int round_no)
{
  int t=lcs[round_no-1];//later make t = lcs[round_no];
  while(t>0)
    {
      int temp = cd[0];
      for(int i=0;i<28;i++)
        {
          cd[i] = cd[i+1];
        }
      cd[28] = temp;
      temp = cd[28];
      for(int i=28;i<55;i++)
        {
          cd[i] = cd[i+1];
        }
      cd[55] = temp;

      t--;
    }
}

//get subkey by performing pc-2 table on shifted cd table
void get_subkey()
{
  for(int i=0;i<48;i++)
  {
    subkey[i] = cd[pc_2[i]-1];
  }
}

//print subkey
void print_subkey()
{
  int c=0;
  for(int i=0;i<48;i++)
    {

      cout<<subkey[i]<<"\t";
      c++;
      if(c==6){c=0;cout<<endl;}
    }
}

//get e_table_outpot
void get_e_table_output()
{

  for(int i=0;i<48;i++)
    {
      e_table_output[i] = block_Ipermuted[e_table[i]-1+32];
    }
}
//print the e_table_outpot
void print_e_table_output()
{
  int c=0;
  for(int i=0;i<48;i++)
    {
      cout<<e_table_output[i]<<"\t";
      c++;
      if(c==6){c=0;cout<<endl;}
    }
}

//xor on two bits
int xor_of(int x1,int x2)
{
  if(x1==x2)return 0;
  else if(x1!=x2)return 1;
}
//perform xor operation on e_table_output and subkey
void get_xor_output()
{
  for(int i=0;i<48;i++)
    {
      xor_output[i] = xor_of(e_table_output[i],subkey[i]);
    }
}

//
void convertDectoBin(int value,int *result_bits,int n)
{
  for(int i=0;i<n;i++)
    {
      result_bits[n-1-i]= (value%2);
      value/=2;
    }
}
//perform s box on 6 bits to each row of output of the xor_output[]
void perform_s_box()
{
  int bits[6]={0};
  int count =1,c1=0,c2=0;
  while(count<=8)
    {
      //get bits from the xor_output array
      for(int i=0;i<6;i++)
        {
          bits[i] = xor_output[i+c1];
        }
      //find row and colom
      int row = bits[5]*1+bits[0]*2;
      int colom = bits[1]*2*2*2 + bits[2]*2*2 + bits[3]*2 + bits[4]*1;
      //cout<<"\nfor count ="<<count<<" row and colom is :"<<row<<" "<<colom<<endl;
      //get value from s box

      int dec_val = s[count-1][row][colom];
      //cout<<"\ndec value is"<<dec_val<<endl;
      //change it to binary and save into result output
      int result_bits[4]={0};
      convertDectoBin(dec_val,result_bits,4);

      /*cout<<"\n result_bits for "<<count<<" is :";
      for(int i=0;i<4;i++)
      {
        cout<<result_bits[i]<<"\t";
      }*/

      for(int i=0;i<4;i++)
        {
          s_box_output[i+c2] = result_bits[i];
        }
        c1+=6;
        c2+=4;

        count++;
    }
}

//get output from from final permutation
void get_final_permutation_output()
{
  for(int i=0;i<32;i++)
    {
      final_permutation_output[i]=s_box_output[final_permutation[i]-1];
    }
}

//rotate final_permutation_output
void get_rotation_on_final_permutation_output()
{
  int x=28,colom =0,c=0;
  for(int i=0;i<32;i++)
    {
      rotated_final_permutation_output[i] = final_permutation_output[x-((i-colom)*4)];
      c++;
      if(c==8)
        {
          c=0;
          x+=1;
          colom+=8;
        }
    }
}

//perform xor operation on rotated_final_permutation_output and 1st half of input
//store the result into xor_final_output[32]
void perform_xor_final()
{
  for(int i=0;i<32;i++)
    {
      xor_final_output[i] = xor_of(rotated_final_permutation_output[i],block_Ipermuted[i]);
    }
}
/*--------------------------------------main fucntion-----------------------------------------------------------------------------------------------------------------------------*/


//final main fucntion
int main()
{
  //take input from user
  cout<<"enter the plain text of size 8 only :";

  getline(cin,plainText);
  if(plainText.length()!=8){cout<<"\nenter only string of 8 character\n ";return 0;}
  converttobinary();
  //print_block_function(1);

  //perform initial permutation
  ip_on_input_block();
/*  cout<<"\n before kuch bhi \n";
  print_block_function(2);*/
  cout<<endl;
  //generate cd table
  get_cd_table_from_pc1();

  //start round machine j+1 is round
  for(int j=0;j<16;j++)
    {
      //generate key
        //perform shifting according to round on cd table and make changes into cd table only
        lcs_operation(j+1);
        //perform pc2 and get subkey
        get_subkey();

      //perform e_table on 2nd half of the input of the round
      get_e_table_output();

      //perform xor operation on e_table_output and subkey ans store into xor_output
      get_xor_output();

      //apply s_box on xor_output and store into s_box_output
      perform_s_box();

      //get last permutation on s box output and store into final_permutation_output
      get_final_permutation_output();

      //perform rotation on final_permutation_output and store into rotated_final_permutation_output
      get_rotation_on_final_permutation_output();

      //copy it into 2nd half of the input of round that is block_Ipermuted[]
      for(int i=32;i<64;i++)
        {
          block_Ipermuted[i] = rotated_final_permutation_output[i-32];
        }

        //perform xor operation on rotated_final_permutation_output and 1st half of input
        //store the result into xor_final_output[32]
        perform_xor_final();

        //copy it into 1st half of the input of the round that is block_Ipermuted
        for(int i=0;i<32;i++)
          {
            block_Ipermuted[i] = xor_final_output[i];
          }

        /*//print the output of each round
        cout<<"\noutput of round : "<<(j+1)<<"is :\n";
        print_block_function(2);*/
    }


    binartTostring();
    cout<<"\nchipe text length is :"<<chiperText.length()<<endl;
  cout<<"chiper text is :"<<chiperText<<endl;

    return 0;
}
