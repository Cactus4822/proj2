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

int followFunc(user *usr, twitter * twitter_system){ // Function to Follow/Unfollow Users
    int valid = 0; // Checks validity of entered command
    int j=0, k=0; // Holds pos of user in twitter_system->users[], k counter
    char opt[10]; // User option
    char target[USR_LENGTH]; // Target is the user they want to "interact" with
    // Strings to compare against user command
    char edit[10] = "/edit";
    char follow[10] = "/follow";
    char unfollow[10] = "/unfollow";
    char leave[10] = "/leave";

    while(strcmp(twitter_system->users[j].username, usr->username) != 0){ // Finds pos of current user (for continuity)
        j++;
    }

    // Stats to show
    printf("\nHello %s!\n\n", twitter_system->users[j].username);
    printf("Your Stats\n--------\n");
    printf("%d following\n", twitter_system->users[j].num_following);
    for(int i=0;i<twitter_system->users[j].num_following;i++){
        printf("%s; ", &twitter_system->users[j].following[i]);
    }
    printf("\n%d followers\n", twitter_system->users[j].num_followers);
    for(int i=0;i<twitter_system->users[j].num_followers;i++){
        printf("%s; ", &twitter_system->users[j].followers[i]);
    }


    while(valid == 0){ // "Infinite" loop, goes until command leave
        printf("\nWhat would you like to do?\n");
        while((strcmp(opt, leave) != 0) && (strcmp(opt, edit) != 0)){
            printf("%s to manage followers and following,\n%s to return to the main menu.\n", edit, leave);
            scanf("%s", &opt);
            if(strcmp(opt, leave) == 0){
                printf("Leaving...\n");
                return 0;
            }
            else if(strcmp(opt, edit) == 0){
                printf("Entering...\n");
            }
            else{
                printf("Invalid option.\n\n");
            }
        }
        printf("Input %s <username> or %s <username>\n", follow, unfollow); // Gets command and target of command
        scanf("%s %s", &opt, &target);
        printf("opt is %s. target is %s.\n", opt, target);

        if(strcmp(target, twitter_system->users[j].username) == 0){
            printf("You cannot target yourself.\n");
        }
        else if(strcmp(opt, follow) == 0){ // Following a user
            //printf("[Follow user]\n");
            valid = 1;
            for(int i=0;i<twitter_system->users[j].num_following;i++){ // Checks if they're already followed
                if (strcmp(twitter_system->users[j].following[i], target) == 0){
                    printf("You are already following %s.\n", target);
                    valid = 0;
                }
            }
            if(valid == 1){
                k=0;
                while(((strcmp(twitter_system->users[k].username, target)) != 0) && (k < twitter_system->num_users)){
                    k++; // Finds the position of the user they want to follow
                }
                //printf("k is %d, num users is %d\n", k, twitter_system->num_users);
                if(k+1>twitter_system->num_users){ // If the user isn't found
                    printf("There is no user named %s.\n", target);
                }
                else{ // Follow the user and become one of their followers
                    //printf("twitter_system->users[k].username is confirmed %s\n", twitter_system->users[k].username);
                    strcpy(twitter_system->users[j].following[twitter_system->users[j].num_following++], twitter_system->users[k].username); // User is following
                    strcpy(twitter_system->users[k].followers[twitter_system->users[k].num_followers++], twitter_system->users[j].username); // Adds user as follower
                    printf("You are now following %s\n", twitter_system->users[k].username);
                }
                valid = 0;
            }
        }
        else if(strcmp(opt, unfollow) == 0){ // Unfollow a user
            //printf("[Unfollow user]");
            valid = 1;
            while((strcmp(twitter_system->users[j].following[k], target) != 0) && k < twitter_system->users[j].num_following){
                k++; // Makes sure you're following the user you're trying to unfollow
            }
            //printf("k is %d\ntwitter_system->users[j].num_following is %d\n", k, twitter_system->users[j].num_following);
            if(k+1>twitter_system->users[j].num_following){
                printf("You are not following %s.", target);
                valid = 0;
            }
            if(valid == 1){
                if(k+1 == twitter_system->users[j].num_following){ //If they're at the end of the list anyway, decrementing the num_followers effectively removes it
                    twitter_system->users[j].num_following--;
                    printf("%s unfollowed.\n", target);
                }
                else{ // Replaces the followed user with the last followed user and decrements number of following by one, effectively removing it.
                    //printf("twitter_system->users[j].following[k] is %s.\n", &twitter_system->users[j].following[k]);
                    //printf("twitter_system->users[j].following[twitter_system->users[j].num_following -1] is %s.\n", twitter_system->users[j].following[twitter_system->users[j].num_following -1]);
                    strcpy(twitter_system->users[j].following[k], twitter_system->users[j].following[twitter_system->users[j].num_following -1]);
                    //printf("twitter_system->users[j].following[k] is now %s.\n", &twitter_system->users[j].following[k]);
                    twitter_system->users[j].num_following--;
                    printf("%s unfollowed.\n", target);
                }
                valid = 0;
            }
        }
        else{
            printf("Invalid command.\n");
        }
    }
}

int deleteFunc(user *usr, twitter * twitter_system, tweet * tp) {
    int j=0;
    while(strcmp(twitter_system->users[j].username, usr->username) != 0){ // Finds pos of user (for tracking)
        j++;
    }
    printf("\nGoodbye, %s.\n\n", twitter_system->users[j].username);
    printf("%d tweet(s) total.\n", twitter_system->num_tweets);
    printf("tp id is %d", &tp->id);

    twitter_system->num_users--;
    return 0;
}