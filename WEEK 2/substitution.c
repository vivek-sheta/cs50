#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>

string encryption(string,string,string); //function for encryption

int main(int argc, string argv[])
{
	if(argc!=2) 
	{
		printf("Usage : %s key \n",argv[0]);  //print usage of ./file
		return 1;
	}
  else if (strlen(argv[1]) != 26)  //terminate program if key length != 26
	{
		printf("Usage : %s key \n",argv[0]);
		return 1;
	}
  else if (strlen(argv[1]) == 26)  // if key length 26 check all char is different and not contain numbers or other char
	{
		for(int i=0 ;i < strlen(argv[1]) ;i++)
		{
			for(int j=i+1; j < strlen(argv[1]) ;j++)
			  {
				if (argv[1][j] == argv[1][i] || (!isalpha(argv[1][j])) )
				{
					printf("key repeated or number in key\n");
					return 1;
				}
			  }
		}

	}

	string plaintext,ciphertext;
	plaintext = get_string("plaintext: ");
	ciphertext = plaintext;

	printf("ciphertext: %s\n", encryption(plaintext,ciphertext,argv[1])); 
}

string encryption(string pt,string ct ,string key)
{
	int repeat;
	for(repeat=0; repeat < strlen(pt) ; repeat++)
	{
			if (isupper(pt[repeat]))
				ct[repeat] = toupper(key[pt[repeat]-'A']);
			else if (islower(pt[repeat]))
			    ct[repeat] = tolower(key[pt[repeat]-'a']);
			else ct[repeat] = pt[repeat];
	}
	ct[repeat] = '\0';
	return ct;
}
