#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXCARDS 50

struct Flashcard //flashcard has a q and an ans
{
    char question[100];
    char answer[100];
};

struct Score //storing player names and marks scored during quiz
{
    char name[50];
    int marks;
};

struct Flashcard cards[MAXCARDS] = //giving values fr first 10
{
    {"capital of Japan","tokyo"},
    {"Largest planet","Jupiter"},
    {"Inventor of light bulb","Thomas Edison"},
    {"Symbol of Gold","Au"},
    {"Fastest land animal","Cheetah"},
    {"Author of Harry Potter","J.K. Rowling"},
    {"Largest ocean","Pacific Ocean"},
    {"National animal of India","Bengal Tiger"},
    {"Red planet","Mars"},
    {"Father of Indian Constitution","Dr. B.R. Ambedkar"}
};

int cardCount =10;//saying only first 10 cards have been made
struct Score scores[20];//struct ka array ie array of data type struct score
int scoreCount=0;//counting plkayer score

void clearInput() //to help cleat any buffer(usually \n as it skips next line of code) as we are using fgets
{
    int c;
    while ((c =getchar())!='\n'&& c !=EOF);//eof=end of file
}

void viewCards() //to printr all catrds
{
    for (int i =0; i <cardCount; i++)
    {
        printf("%d) %s - %s\n",i+1,cards[i].question,cards[i].answer);
    }
}

void addCard() //add cards if no of cards is below 50
{
    if (cardCount >=MAXCARDS) 
    {
        printf("card limit reached\n");
        return;
    }
    printf("enter question: ");
    fgets(cards[cardCount].question,100,stdin);
    cards[cardCount].question[strcspn(cards[cardCount].question,"\n")] ='\0';//find new line and replace w \0

    printf("enter answer: ");
    fgets(cards[cardCount].answer, 100, stdin);
    cards[cardCount].answer[strcspn(cards[cardCount].answer, "\n")] = '\0';

    cardCount++;//increase card count
    printf("cards added\n");
}

void searchCard() 
{
    char word[100];
    printf("enter word to search: ");
    fgets(word,100,stdin);
    word[strcspn(word,"\n")] = '\0';

    for (int i=0;i<cardCount;i++) 
    {
        if (strstr(cards[i].question, word))//searches for str2 in str1
        {
            printf("%d) %s - %s\n", i + 1,cards[i].question,cards[i].answer);//if word is present in any flashcard it will print it
        }
    }
}

void quiz() 
{
    if (cardCount==0)
    {
        printf("no cards to quiz\n");
        return;
    }

    char player[50];
    printf("Enter player name: ");
    fgets(player, 50, stdin);
    player[strcspn(player, "\n")] = '\0';

    srand(time(NULL));//seeding srand to get random numbers every round
    int score =0;

    for (int i=0;i<5;i++) 
    {

        int index = rand() %cardCount;// to get number bw 0 and count-1
        char ans[100];

        printf("\nQ%d: %s\n",i+1,cards[index].question);
        printf("Your answer: ");
        fgets(ans, 100, stdin);
        ans[strcspn(ans, "\n")] = '\0';

        if (strcasecmp(ans,cards[index].answer) == 0) //ignores case
        {
            printf("correct\n");
            score++;
        }
        else 
        {
            printf("wrong");
        }
    }

    printf("\n%s scored %d/5\n",player,score);

    strcpy(scores[scoreCount].name,player);//storing user input
    scores[scoreCount].marks=score;
    scoreCount++;
}

void viewScores() //view scores of ppl that have played and have been stored 
{
    for (int i=0;i <scoreCount;i++)
    {
        printf("%d) %s - %d/5\n",i+1,scores[i].name,scores[i].marks);
    }
}

int main() 
{
    int choice;
    while (1) {
        printf("\n===== FLASHCARD APP =====\n");
        printf("1. view flashcards\n");
        printf("2. add flashcard\n");
        printf("3. search flashcard\n");
        printf("4. quiz mode\n");
        printf("5. view scores\n");
        printf("6. exit\n");
        printf("enter choice: ");
        scanf("%d", &choice);
        clearInput();//remove unnesceassy buffer characters like \n and etc

        switch (choice) {
            case 1: viewCards(); break;
            case 2: addCard(); break;
            case 3: searchCard(); break;
            case 4: quiz(); break;
            case 5: viewScores(); break;
            case 6: printf("bye thanks\n"); return 0;
            default: printf("invalid\n");
        }
    }
}
