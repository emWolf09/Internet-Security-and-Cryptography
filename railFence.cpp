#include <iostream>
using namespace std;
string decryptRailFence(string cipher, int key);
int main()
{
    //cout << "Hello World!" << endl;
    string pt;
    int key;
    cout<<"enter the plain text :";
    getline(cin,pt);
    cout<<"\nenter the key :";
	  cin>>key;
    cout<<endl;

    //cin>>pt;

    cout<<"matrix  :\n";
    int l = pt.length();
    char t[key][l];
    for(int i=0;i<key;i++){
        for(int j=0;j<l;j++)
        {   t[i][j]='-';
            cout<<t[i][j]<<"\t";
        }
        cout<<endl;
    }

    int i=0,j=0;
    bool dir_to_down = false;
    //t[0][0]=pt[0];
    for(int k=0;k<l;k++){
        if(i==0||i==key-1)dir_to_down = !dir_to_down;

        t[i][j++] = pt[k];
        dir_to_down?i++:i--;
    }

    cout<<endl<<endl;
    cout<<"matrix after enter the pt:\n";
    for(int i=0;i<key;i++){
        for(int j=0;j<l;j++)
        {   //t[i][j]='\n';
            cout<<t[i][j]<<"\t";
        }
        cout<<endl;
    }


	string ct;
	for (int i=0; i < key; i++)
		for (int j=0; j <l; j++)
			if (t[i][j]!='-')
				ct.push_back(t[i][j]);

	cout<<endl<<"the chiper text is :"<<ct<<endl;

	string decryptString = decryptRailFence(ct,key);
	cout<<"\n decrypted text is :"<<decryptString;
    return 0;
}


string decryptRailFence(string cipher, int key)
{

    char rail[key][cipher.length()];
    for (int i=0; i < key; i++)
        for (int j=0; j < cipher.length(); j++)
            rail[i][j] = '\n';

    bool dir_down;

    int row = 0, col = 0;


    for (int i=0; i < cipher.length(); i++)
    {

        if (row == 0)
            dir_down = true;
        if (row == key-1)
            dir_down = false;

        rail[row][col++] = '*';
        dir_down?row++ : row--;
    }
    int index = 0;
    for (int i=0; i<key; i++)
        for (int j=0; j<cipher.length(); j++)
            if (rail[i][j] == '*' && index<cipher.length())
                rail[i][j] = cipher[index++];

    string result;
     row = 0, col = 0;
    for (int i=0; i< cipher.length(); i++)
    {

        if (row == 0)
            dir_down = true;
        if (row == key-1)
            dir_down = false;

        if (rail[row][col] != '*')
            result.push_back(rail[row][col++]);

        // find the next row using direction flag
        dir_down?row++: row--;
    }
    return result;
}
