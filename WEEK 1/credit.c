#include<cs50.h>
#include<stdio.h>

string check_type(long long int);
bool checksum(long long int);
int main(void){
    string str;
    long long int card_number;
    do
    {
        card_number=get_long("Card Number : ");  //check card number is positive and >0
    }
    while(card_number<=0);

    if (checksum(card_number))  //check card number validity using Luhn’s Algorithm
        printf("%s\n",check_type(card_number));  //check type of card like. master,visa,AMEX
    else 
        printf("INVALID\n");
}

//Luhn’s Algorithm CHECKSUM
bool checksum(long long int number)
{
    int length=0,hold,even_mul;
    long long int temp;
    bool odd=1;
    int sum_odd=0,sum_even=0;
    temp=number;
    while(temp != 0)  //find length of card number
    {
        temp /= 10;
        length++; 
    }

    if(length <=12||length>=17)  //reject card number based on length
    {
        return 0;
    }
    else
    {
         while(number != 0)  
         {
            hold = number % 10;  //get last digit of card number
            if(odd) //check is digit odd or even? and do operation
            {
                sum_odd += hold;  //simply add odd number 
                odd = 0;
            }
            else
            {
                even_mul = hold * 2;  //even number * 2 and seperate digit and add eg. 6*2=12 (1+2) 
                while (even_mul != 0)
                {
                    sum_even += even_mul % 10;
                    even_mul /= 10;
                }
                odd = 1;
            }
         number /= 10; //delete the last digit which get before
        }
    }
    if((sum_odd + sum_even)%10) //if mod of (odd+even = 0) return true else false
        return 0;
    else
        return 1;
}

//Check type of card 
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
