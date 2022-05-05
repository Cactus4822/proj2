
#include "twitter_functions.h"

void postTweet(tweet * twt);

void postTweet(tweet * twt){
    twitter * twtr;
    printf("What's happening?\n");
    fgets(twt->msg, TWEET_LENGTH, stdin);
    twt->id++;
    //twtr->num_tweets++;
}

int followFunc(user usr, twitter * twitter_system){
    int valid = 0;
    char opt[10];
    char target[USR_LENGTH];
    char edit[10] = "/edit";
    char follow[10] = "/follow";
    char unfollow[10] = "/unfollow";
    char leave[10] = "/leave";

    printf("Hello %s!\n\n", usr.username);
    printf("Your Stats\n--------\n");
    printf("%d following\n", usr.num_following);
    for(int i=0;i<usr.num_following;i++){
        printf("%s; ", usr.following[i]);
    }
    printf("%d followers\n", usr.num_followers);
    for(int i=0;i<usr.num_followers;i++){
        printf("%s; ", usr.followers[i]);
    }

    while(valid == 0){
        printf("What would you like to do?\n");
        printf("/edit to manage followers and following,\n/leave to return to the main menu.\n");
        scanf("%s", &opt);
        if(strcmp(opt, leave) == 0){
            printf("Leaving...\n");
            return 0;
        }
        else if(strcmp(opt, edit) == 0){
            printf("Entering...\n");
        }
        printf("Input /follow <username> or /unfollow <username>\n");
        scanf("%s %s", &opt, &target);
        printf("opt is %s. target is %s.\n", opt, target);

        if(strcmp(target, usr.username) == 0){
            printf("You cannot target yourself.\n");
        }
        else if(strcmp(opt, follow) == 0){
            printf("[Follow user]\n");
            valid = 1;
            for(int i=0;i<usr.num_following;i++) {
                if (strcmp(&usr.following[i], target) == 0) {
                    printf("You are already following %s.\n", target);
                    valid = 0;
                }
            }
            if(valid == 1){
                valid = 0;
                //printf("Looking for %s...\n", target);
                for(int i=0;i<twitter_system->num_users;i++) {
                    //printf("We see %s.\n", twitter_system->users[i].username);
                    if (strcmp(twitter_system->users[i].username, target) == 0) {
                        strcpy(&usr.following[usr.num_following], target);
                        usr.num_following++;
                        printf("You are now following %s.\n", target);
                        valid = 1;
                    }
                }
                if(valid == 0){
                    printf("There is no user named %s.\n", target);
                }
            }
        }
        else if(strcmp(opt, unfollow) == 0){
            printf("[Unfollow user]");
            valid = 1;
            for(int i=0;i<usr.num_following;i++) {
                if (strcmp(&usr.following[i], target) == 0) {
                    printf("You are already following %s.\n", target);
                    valid = 0;
                }
            }
            if(valid == 1){
                for(int i=0;i<twitter_system->num_users;i++){
                    if(strcmp(twitter_system->users[i].username, target) == 0){
                        strcpy(&usr.following[usr.num_following], target);
                        usr.num_following++;
                        printf("You are now following %s.\n", target);
                    }
                    else{
                        printf("There is no user named %s.\n");
                        valid = 0;
                    }
                }
            }
        }
        else{
            printf("Invalid command.\n");
            scanf("%s %s", &opt, &target);
        }
    }
}