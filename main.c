#include <stdio.h>
#include <string.h>
#include "twitter_create.h"
#include "twitter_follow.h"
#include "twitter_tweet.h"

void helpfunc(); // Function to print list of commands

int main() {
    twitter twitter_system;
    create_twitter_system(&twitter_system);
    //printf("\n%d users in t_s.n_u\n", twitter_system.num_users);

    int turn=0, i, valid=0;
    user usr;
    char opt[10];
    char feed[10] = "/feed";
    char follow[10] = "/follow";
    char tweet[10] = "/tweet";
    char help[10] = "/help";
    char pass[10] = "/pass";
    char end[10] = "/end";

    for(i=0; i < twitter_system.num_users; i++){
        usr = twitter_system.users[i];
        printf("User: %s; Followers: %d; Following: %d\n",usr.username, usr.num_followers, usr.num_followers);
    }

    while(turn != -1){
        if(turn > twitter_system.num_users-1)
            turn = 0;
        usr = twitter_system.users[turn];
        //printf("Turn %d\n", turn);
        printf("%s is in control.\nSelect an operation:\n", usr.username);
        helpfunc();
        valid = 0;
        while(valid == 0){
            fgets(opt, 10, stdin);
            if(opt[strlen(opt) -1] == '\n'){
                opt[strlen(opt) -1] = '\0';
            }
            printf("Entered command: %s.\n", opt);
            valid = 1;
            if(strcmp(opt, feed) == 0){
                printf("[Feed]\n");
            }
            else if(strcmp(opt, follow) == 0){
                printf("[Follow]\n");
            }
            else if(strcmp(opt, tweet) == 0){
                printf("[Tweet]\n");
            }
            else if(strcmp(opt, help) == 0){
                printf("[Help]\n");
                helpfunc();
                valid = 0;
            }
            else if(strcmp(opt, pass) == 0){
                printf("[Pass]\n");
            }
            else if(strcmp(opt, end) == 0){
                printf("[End]\n");
                turn = -2;
            }
            else{
                printf("Invalid command.\n");
                valid = 0;
                helpfunc();
            }
        }
        turn++;
    }

    return 0;
}

void helpfunc(){
    printf("/feed to show user feed\n");
    printf("/follow to follow/unfollow\n");
    printf("/tweet to post a tweet\n\n");
    printf("/pass to pass control\n");
    printf("/end to terminate the program\n");
    printf("/help to show this message again.\n");
}