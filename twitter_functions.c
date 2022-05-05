#include <stdlib.h>
#include "twitter_functions.h"



int id = 0;

void postTweet( twitter * twtr){
    if( twtr->num_tweets > MAX_TWEETS){
        printf("You have reached the max Tweet limit.\n");
        return;
    }
    tweet *link = (struct tweet*) malloc(sizeof(struct tweet));
    printf("What's happening?\n");
    fgets(link->msg, TWEET_LENGTH, stdin);
    if (strchr(link->msg, '\n') == NULL) {
        printf("Error: Your tweet is too long. Please try again:\n");
        fflush(stdin);
    }
    link->id = twtr->tweets_created;
    link->nextTweet = NULL;
    if (twtr->num_tweets != 0) {
        twtr->lastTweet->nextTweet = link;
        twtr->lastTweet = link;
    } else {
        twtr->firstTweet = twtr->lastTweet = link;
    }
    twtr->num_tweets++;
    twtr->tweets_created++;
}
/*void printList(twitter * twtr) {
    tweet *ptr = twtr->firstTweet;
    printf("\n[ ");
    //start from the beginning
    while(ptr != NULL) {
        printf("(%d,%s) ",ptr->id,ptr->msg);
        ptr = ptr->nextTweet;
    }

    printf(" ]");
}*/

int followFunc(user * usr, twitter * twitter_system){
    int valid = 0;
    char opt[10];
    char target[USR_LENGTH];
    char edit[10] = "/edit";
    char follow[10] = "/follow";
    char unfollow[10] = "/unfollow";
    char leave[10] = "/leave";

    printf("Hello %s!\n\n", usr->username);
    printf("Your Stats\n--------\n");
    printf("%d following\n", usr->num_following);
    for(int i=0;i<usr->num_following;i++){
        printf("%s; ", usr->following[i]);
    }
    printf("%d followers\n", usr->num_followers);
    for(int i=0;i<usr->num_followers;i++){
        printf("%s; ", usr->followers[i]);
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

        if(strcmp(target, usr->username) == 0){
            printf("You cannot target yourself.\n");
        }
        else if(strcmp(opt, follow) == 0){
            printf("[Follow user]\n");
            valid = 1;
            for(int i=0;i<usr->num_following;i++) {
                if (strcmp(&usr->following[i], target) == 0) {
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
                        strcpy(&usr->following[usr->num_following], target);
                        usr->num_following++;
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
            for(int i=0;i<usr->num_following;i++) {
                if (strcmp(&usr->following[i], target) == 0) {
                    printf("You are already following %s.\n", target);
                    valid = 0;
                }
            }
            if(valid == 1){
                for(int i=0;i<twitter_system->num_users;i++){
                    if(strcmp(twitter_system->users[i].username, target) == 0){
                        strcpy(&usr->following[usr->num_following], target);
                        usr->num_following++;
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

int delete(twitter * twtr, char usernamedel[USR_LENGTH]) {
    printf("Type in your username to confirm you want to delete your account:");
    fgets(usernamedel, USR_LENGTH, stdin);
    user *current = twtr->firstUser;
    user *previous = NULL;

    if (twtr->firstUser == NULL) {
        return NULL;
    }

    while (current->username != usernamedel) {
        if (current->nextUser == NULL) {
            return NULL;
        } else {
            previous = current;
            current = current->nextUser;
        }
    }

    if(current == twtr->firstUser) {
        twtr->firstUser = twtr->firstUser->nextUser;
    } else {
        previous->nextUser = current->nextUser;
    }
    return current;
}