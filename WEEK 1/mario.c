#include <cs50.h>
#include <stdio.h>
int main(void) 
{
    int height,i=1,temp=0;
    int space,count;
    do
    {
        height = get_int("Enter Height : ");
    }
    while( (height<0) || (height>20) );    
    count=height;

  for( ; i<=height ; ++i, space=0,temp=0,count-=1)
  {
      while(space!=count)
        { printf(" "); space++; } //print spaces as per needed 
      while(temp!=i)
        { printf("#"); temp++; }  //print left side pyramid 
    
      printf("  ");  //print two spaces in between pyramid
    
      temp=0;  //set temp to 0 for print right side pyramid
    
      while(temp!=i)
        {  printf("#");  temp++; } //print right side pyramid
     printf("\n"); //new line 
  }
}
