#include "twitter_functions.h"


void helpFunc(); // Function to print list of commands
tweet twt;
twitter twitter_system;
user usr; // Declares usr variable to be used down below
int main() {

    create_twitter_system(&twitter_system); // Creates Twitter
    //printf("\n%d users in t_s.n_u\n", twitter_system.num_users);

    int turn=0, i, next; // "turn" to check whose turn it is, "i" just iterator, "next" to check if next user turn
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
        printf("\n%d human(s) using Twitter.\n\n", twitter_system.num_users); // Tracks number of users
        for(i=0; i < twitter_system.num_users; i++){ // Iterates and prints all users
            usr = twitter_system.users[i];
            printf("User: %s; Followers: %d; Following: %d\n",usr.username, usr.num_followers, usr.num_following);
        }
        printf("\n%d tweet(s) posted.\n", twitter_system.num_tweets); // Tracks number of tweets
        if(turn > twitter_system.num_users-1) // resets control back to first user after last user's turn
            turn = 0;
        usr = twitter_system.users[turn]; // Person in control
        helpFunc(); // Function to display commands

        next = 0;
        while(next == 0){ // Allows user to continue entering commands until they pass control or end the program
            printf("\n%s is in control.\nSelect an operation:\n", usr.username);
            fgets(opt, 12, stdin); // Gets user input
            if(opt[strlen(opt) -1] == '\n'){ // Changes newline at end of fgets to null terminator
                opt[strlen(opt) -1] = '\0';
            }
            printf("Entered command: %s.\n", opt); // Was for troubleshooting but kinda helps user too
            //Compares user input to the available commands
            if(strcmp(opt, tweet) == 0){ // Tweet command
                printf("[Tweet]\n");
                postTweet(&twitter_system, &twt, &usr);
            }
            else if(strcmp(opt, follow) == 0){ // Follow command
                printf("[Follow]\n");
                followFunc(&usr, &twitter_system);
                fgets(opt, 12, stdin);
                if(opt[strlen(opt) -1] == '\n'){ // QOL, not needed but it prevents a false error
                    opt[strlen(opt) -1] = '\0';
                }
            }
            else if(strcmp(opt, newsfeed) == 0){ // Newsfeed command
                printf("[Newsfeed]\n");
            }
            else if(strcmp(opt, delete) == 0){
                printf("Are you sure you want to delete your account?\n"); // Doublechecks to emulate real system
                printf("Note: This is irreversible. Please enter 'Confirm' to confirm.\n");
                fgets(opt, 12, stdin);
                if(opt[strlen(opt) -1] == '\n'){
                    opt[strlen(opt) -1] = '\0';
                }
                if(strcasecmp(opt, "confirm") == 0){ // tested to see if I can forego the variables, now I know
                    deleteFunc(&usr, &twitter_system, &twt);
                    if(twitter_system.num_users < 1){ // If the last user is deleted, automatically shut down program
                        printf("There are no more users.\nShutting down Twitter...\n");
                        turn = -2;
                    }
                    next = 1;
                    turn--;
                }
                else{
                    printf("Delete canceled.\n");
                }
            }
            else if(strcmp(opt, help) == 0){ // Help command
                printf("[Help]\n");
                helpFunc();
            }
            else if(strcmp(opt, endturn) == 0){ // Passes control to next user
                printf("[Turn ended]\n");
                next = 1;
            }
            else if(strcmp(opt, end) == 0){ // Ends Twitter by exiting the loops to return 0.
                printf("[End]\n");
                turn = -2;
                next = 1;
            }
            else{ // If invalid command, remind the user of the available commands
                printf("Invalid command.\n");
                helpFunc();
            }
        }
        turn++; // Next user's turn
    }
//    printList(&twitter_system);
    return 0;
}

void helpFunc(){ // Help function, displays all commands
    printf("/tweet to post a tweet\n");
    printf("/newsfeed to show user feed\n");
    printf("/follow to follow/unfollow a user\n");
    printf("/delete to delete your account\n");
    printf("/endturn to end your turn and move to the next user\n");
    printf("/end to terminate the program\n");
    printf("/help to show this message again.\n\n");
    printf("%d", twt.id); // Debugging printf
    printf("%d", twitter_system.num_tweets);
}