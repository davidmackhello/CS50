/**
 * myswitch.c
 *
 * provides user advice based on how they are feeling
 * 
 */

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // ask for user's mood
    printf("On a scale from 1 to 5, how are you feeling today?: ");
    int n = GetInt();
    
    // judge result
    switch (n)
    {
        case 1:
            printf("Stop being so hard on yourself. You currently can't see how much better off you are than you think. Try to take a walk or a nap, or call home, anything to pull you out of your current state.\n");
            break;
            
        case 2:
            printf("Try to read a book, watch a movie, or do something enriching. Avoid the internet. Engaging with something meaningful will make you feel more productive and satisfied.\n");
            break;
            
        case 3:
            printf("Neutral, eh? Have you eaten? Have you had enough water? Maybe go for a jog.\n");
            break;
            
        case 4:
            printf("You know what, you deserve to feel good! Be content with how you feel, and don't waste your time questioning it.\n");
            break;
            
        case 5:
            printf("Great news! Now is the time to do some good work. Sit down and write, play some music, or otherwise create something. God knows where these times come from, but they are certainly worth cherishing.\n");
            break;
            
        default:
            printf("Invalid choice.\n");
            break;
    }
}