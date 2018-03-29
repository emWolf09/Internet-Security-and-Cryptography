#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
using namespace std;

int a [] = {2  , 3  ,  5  ,  7  , 11  , 13  , 17  , 19  , 23  , 29  , 31  , 37  , 41  , 43  , 47  , 53  , 59  , 61  , 67  , 71,
    73, 79, 83, 89, 97 , 101 , 103 ,   107   , 109   , 113 , 127  ,  131  ,  137  ,  139  ,  149  ,  151  ,  157  ,  163  ,  167 , 173 ,
    179 ,   181  ,  191   , 193  ,  197  ,  199  ,  211 ,   223  ,  227 ,   229 ,    233  ,  239 ,   241  ,  251  ,  257  ,  263  ,
    269 ,   271  ,  277  ,  281 ,    283  ,  293 ,   307  ,  311  ,  313  ,  317  ,  331  ,  337  ,  347  ,  349 ,    353  ,  359  ,
    367  ,  373  ,  379  ,  383  ,  389  ,  397  ,  401  ,  409 ,  419  ,  421 ,   431  ,  433  ,  439  ,  443  ,  449  ,  457   ,
    461  ,  463 ,    467  ,  479 ,   487  ,  491  ,  499  ,  503  ,  509  ,  521  ,  523  ,  541 ,    547  ,  557  ,  563  ,  569  ,
    571  , 577  ,  587   , 593  ,  599  ,  601 ,    607  ,  613 ,   617  ,  619  ,  631  ,  641  ,  643   , 647  ,  653  ,  659 ,
    661  ,  673  ,  677  ,  683  ,  691  ,  701  ,  709  ,  719  ,  727  ,  733 ,    739  ,  743 ,   751  ,  757  ,  761  ,  769  ,
    773  ,  787  ,  797   , 809 ,    811  ,  821  ,  823  ,  827  ,  829  ,  839  ,  853  ,  857  ,  859   , 863 ,    877  ,  881  ,
    883  ,  887  ,  907  ,  911  ,  919  ,  929  ,  937  ,  941 ,    947  ,  953 ,   967  ,  971  ,  977  ,  983  ,  991  ,  997
    };
    unsigned long int power(unsigned long int x,unsigned long int y,unsigned long int p)
{
    unsigned long int res = 1;      // Initialize result

    x = x % p;  // Update x if it is more than or
                // equal to p

    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;

        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
  }
     unsigned long int gcd(unsigned long int a,unsigned long int b)
    {
        if (a == 0)
          return b;
        return gcd(b%a, a);
    }

    int main()
    {
      unsigned long int p,q;

      srand(time(NULL));

      p = a[rand()%168];
      cout<<"P is "<<p<<endl;
      q =  a[rand()%168];
      cout<<"\nq is "<<q<<endl;
    //p=3;q=7;
      unsigned long int n = p*q;
      unsigned long int e = 2;
      unsigned long int phi = (p-1)*(q-1);
      cout<<"\nphi is "<<phi;
      while (e<phi) {

        if(gcd(e,phi)==1)
          break;
        else e++;
      }
      std::cout << "\ne is " <<e<< '\n';
       int k = rand()%10+2;
       k=0;
       unsigned long int d;
      //cout<<"\nk is "<<k;
      for(k=0;;k++){
        if((1+(k*phi))%e == 0){
           d  = (1+(k*phi))/e;
           break;
        }
      }

      //cout<<"d is "<<d;
      //cout<<"\nmod is"<<(int)(d*e)%(int)phi<<endl;
      //unsigned long int  d=2;
      cout<<"\nd is: "<<d<<endl;
      string msg;
      cout<<"\nEnter the string msg:";
      cin>>msg;
      for(int i=0;i<msg.length();i++)
        {
          unsigned long int ch;
          cout<<"ascii value of "<<msg[i]<<"  "<<(int)msg[i]<<"\t";
          ch = power(msg[i],e,n);
          unsigned long int ch1 = power(ch,d,n);

          cout<<"chiper encrypted value for character  "<<msg[i]<<" is"<<"\t"<<ch<<"  decrypted ascii value  is  "<<ch1<<endl;
        }

      return 0;
    }
