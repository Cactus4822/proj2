#include "twitter_functions.h"


void helpfunc(); // Function to print list of commands
tweet twt;
twitter twitter_system;
user usr; // Declares usr variable to be used down below
int main() {

    create_twitter_system(&twitter_system);
    //printf("\n%d users in t_s.n_u\n", twitter_system.num_users);

    int turn=0, i, next=0; // "turn" to check whose turn it is, "i" just iterator, "next" to check if next user turn
    char opt[10]; // User option
    // Strings to compare to check user command
    char newsfeed[12] = "/newsfeed";
    char follow[10] = "/follow";
    char tweet[10] = "/tweet";
    char delete[10] = "/delete";
    char help[10] = "/help";
    char endturn[10] = "/endturn";
    char end[10] = "/end";

    while(turn != -1){ // While loop to encapsulate user rotations until program is terminated
        printf("\n%d human(s) using Twitter.\n\n", twitter_system.num_users);
        for(i=0; i < twitter_system.num_users; i++){ // Iterates and prints all users
            usr = twitter_system.users[i];
            printf("User: %s; Followers: %d; Following: %d\n",usr.username, usr.num_followers, usr.num_following);
        }
        printf("\n%d tweet(s) posted.\n", twitter_system.num_tweets);
        if(turn > twitter_system.num_users-1)
            turn = 0;
        usr = twitter_system.users[turn]; // Person in control
        printf("\n%s is in control.\nSelect an operation:\n", usr.username);
        helpfunc(); // Function to display commands

        next = 0;
        while(next == 0){ // Allows user to continue entering commands until they pass control or end the program
            printf("Select an operation (/help for help):\n");
            fgets(opt, 12, stdin);
            if(opt[strlen(opt) -1] == '\n'){
                opt[strlen(opt) -1] = '\0';
            }
            printf("Entered command: %s.\n", opt);
            if(strcmp(opt, tweet) == 0){
                printf("[Tweet]\n");
                postTweet(&twitter_system, &twt, &usr);
            }
            else if(strcmp(opt, follow) == 0){
                printf("[Follow]\n");
                followFunc(&usr, &twitter_system);
                fgets(opt, 12, stdin);
                if(opt[strlen(opt) -1] == '\n'){
                    opt[strlen(opt) -1] = '\0';
                }
            }
            else if(strcmp(opt, newsfeed) == 0){
                printf("[Newsfeed]\n");
            }
            else if(strcmp(opt, delete) == 0){
                printf("Are you sure you want to delete your account?\n");
                printf("Note: This is irreversible. Please enter 'Confirm' to confirm.\n");
                fgets(opt, 12, stdin);
                if(opt[strlen(opt) -1] == '\n'){
                    opt[strlen(opt) -1] = '\0';
                }
                if(strcasecmp(opt, "confirm") == 0){
                    deleteFunc(&usr, &twitter_system, &twt);
                    if(twitter_system.num_users < 1){
                        printf("There are no more users.\nShutting down Twitter...\n");
                        turn = -2;
                    }
                    next = 1;
                }
                else{
                    printf("Delete canceled.\n");
                }
            }
            else if(strcmp(opt, help) == 0){
                printf("[Help]\n");
                helpfunc();
            }
            else if(strcmp(opt, endturn) == 0){
                printf("[Turn ended]\n");
                next = 1;
            }
            else if(strcmp(opt, end) == 0){
                printf("[End]\n");
                turn = -2;
                next = 1;
            }
            else{
                printf("Invalid command.\n");
                helpfunc();
            }
        }
        turn++;
    }
//    printList(&twitter_system);
    return 0;
}

void helpfunc(){
    printf("/tweet to post a tweet\n");
    printf("/newsfeed to show user feed\n");
    printf("/follow to follow/unfollow a user\n");
    printf("/delete to delete your account\n");
    printf("/endturn to end your turn and move to the next user\n");
    printf("/end to terminate the program\n");
    printf("/help to show this message again.\n\n");
    printf("%d", twt.id);
    printf("%d", twitter_system.num_tweets);
}