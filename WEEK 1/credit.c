#include<cs50.h>
#include<stdio.h>

string check_type(long long int);
bool checksum(long long int);
int main(void){
    string str;
    long long int card_number;
    do
    {
        card_number=get_long("Card Number : ");
    }while(card_number<=0);

    if(checksum(card_number))
    {
        printf("%s\n",check_type(card_number));
    }else printf("INVALID\n");
}

bool checksum(long long int number){
    int length=0,hold,even_mul;
    long long int temp;
    bool odd=1;
    int sum_odd=0,sum_even=0;
    temp=number;
    while(temp != 0)
    {
        temp /= 10;
        length++;
    }

    if(length <=12||length>=17)
    {
        return 0;
    }
    else
    {
         while(number != 0)
         {
            hold = number % 10;
            if(odd)
            {
                sum_odd += hold;
                odd = 0;
            }
            else
            {
                even_mul = hold * 2;
                while (even_mul != 0)
                {
                    sum_even += even_mul % 10;
                    even_mul /= 10;
                }
                odd = 1;
            }
         number /= 10;
        }
    }
    if((sum_odd + sum_even)%10)
        return 0;
    else
        return 1;
}


string check_type(long long int number)
{
    int length=0;
    long long int temp=number;
    while(temp != 0)
    {
        temp /= 10;
        length++;
    }

    if(length == 13 || length == 14)
    {
        if( ((number/(long long)10E10)==4) || ((number/(long long)10E11)==4))
              return "VISA";
    }
    else if(length == 15)
    {
            if(((number/(long long)10E12)==34)||((number/(long long)10E12)==37))
                return "AMEX";
            else if((number/(long long)10E13)==4)
                return "VISA";
    }
    else if(length == 16)
    {
            if((number/(long long)10E13)>=51&&(number/(long long)10E13)<=55)
                return "MASTERCARD";
            else if((number/(long long)10E14)==4)
                return "VISA";
    }
    else return "INVALID";
    return "INVALID";
}
