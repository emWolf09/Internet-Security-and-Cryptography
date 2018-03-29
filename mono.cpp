#include <iostream>
#include<unordered_map>

using namespace std;

class mono{
  public:
    unordered_map <char,char > map;
    mono()
      {
        //std::unordered_map<char,char> map1
        map=
                      {
												  {'a','t'},
												  {'b','s'},
                          {'c','r'},
                          {'d','q'},
                          {'e','m'},
                          {'f','n'},
                          {'g','o'},
                          {'h','p'},
                          {'i','l'},
                          {'j','k'},
                          {'k','j'},
                          {'l','i'},
                          {'m','e'},
                          {'n','f'},
                          {'o','g'},
                          {'p','h'},
                          {'q','a'},
                          {'r','b'},
                          {'s','c'},
                          {'t','d'},
                          {'u','z'},
                          {'v','y'},
                          {'w','x'},
                          {'x','w'},
                          {'y','u'},
												  {'z','v'}
  	  	  	  	  	  };
      }
      void printmap()
        {
          cout<<"map is : \n";
          for(char x = 'a';x<='z';x++)
            {
              cout<<x<<"= "<<map[x]<<endl;
            }
        }
      string encryption(string s)
      {
        for(int i=0;i<s.length();i++)
      	   {
      	       if(s[i]!=' ')
      	        {
                    if(s[i]>='a'&&s[i]<='z')
      	            s[i] = map[s[i]];
      	        }
      	   }
           return s;
      }
      string decryption(string s)
      {
        for(int i=0;i<s.length();i++)
      	   {
      	       if(s[i]!=' ')
      	        {
                    if(s[i]>='a'&&s[i]<='z')
                      {
                        char ch ='a';
                        while (ch<='z') {
                          /* code */
                          if(map[ch]==s[i])
                            {
                              s[i]=ch;
                              break;
                            }
                          ch++;
                        }
                      }

      	        }
      	   }
           return s;
      }

};

int main(int argc, char const *argv[]) {
    mono x;string input;
    x.printmap();
    cout<<endl<<endl;
    cout<<"enter the input :";
    getline (cin,input);
    if(input.length() == 0){
      cout<<"empty string\n";
      exit(-1);
    }
    input = x.encryption(input);
    cout<<"encryption returns chiper text is : "<<input<<endl;
    input = x.decryption(input);
    cout<<"decryption returns plain text : "<<input<<endl;
  return 0;
}
