#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

int main(void)
{
    int letter=0, word=1, sentence=0, grade;
    string paragraph;
    float i, L, S;
    paragraph = get_string("Text : ");

    for(int track=0, n=strlen(paragraph) ; track < n ; track++)
    {
        if (isalpha(paragraph[track]))
            letter++;   //count letters
        if (paragraph[track] == '.' || paragraph[track] == '?' || paragraph[track] == '!' || paragraph[track] == ':')
            sentence++;   //count sentences
        if (paragraph[track] == ' ')
        {
            if (isalpha(paragraph[track+1]))
                word++;  //count words
        }
    }

    i = 0.0588 * ( 100 * (float)letter / (float)word ) - 0.296 * ( 100 *(float)sentence / (float)word ) - 15.8; //calculate grade
    grade = round(i);

    if (grade > 0 && grade <= 16)
        printf("Grade %d\n",grade);
    else if(grade > 16){
        printf("Grade 16+\n");
    else
        printf("Before Grade 1\n");
}
