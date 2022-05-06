//
// Created by Lili on 30/03/2022.
//

#include <stdio.h>
#include <string.h>
#include "twitter_create.h"

void create_twitter_system(twitter * twitter_system){

    twitter_system->tweets_created = 0;

    twitter_system->num_users = 0;
    twitter_system->firstUser = NULL;
    twitter_system->lastUser = NULL;

    twitter_system->num_tweets = 0;
    twitter_system->firstTweet = NULL;
    twitter_system->lastTweet = NULL;

    int orig=0; // Original username

    printf("Enter number of users: \n"); // Gets number of users
    scanf("%d", &twitter_system->num_users);
    getchar();
    //twitter_system->num_users = num_users;
    while (twitter_system->num_users < 1){ // Makes sure there's at least one user
        printf("Error: Need at least 1 user.\n");
        printf("Enter number of users: \n");
        scanf("%d", &twitter_system->num_users);
    }
    //printf("%d users.\n", twitter_system->num_users); // Just to double-check

    //user users[twitter_system->num_users]; // Users Array
    twitter_system->users[twitter_system->num_users];
    tweet news_feed[MAX_TWEETS];

    printf("Username of first user:");
    /*
    fgets(users[0].username, USR_LENGTH, stdin);
    if (users[i].username[strlen(users[i].username) -1] == "\Process finished with exit code -1073741819 (0xC0000005)n")
     users[i].username[strlen(users[i].username) -1] = "\0";
    users[0].num_followers = 0;
    users[0].num_following = 0;
     */
    //user *firstUser;
    fgets(twitter_system->users[0].username, USR_LENGTH, stdin);
    if (twitter_system->users[0].username[strlen(twitter_system->users[0].username) -1] == '\n')
        twitter_system->users[0].username[strlen(twitter_system->users[0].username) -1] = '\0';
    twitter_system->users[0].num_followers = 0;
    twitter_system->users[0].num_following = 0;

    //twitter_system->firstUser = twitter_system->lastUser = firstUser;
    //user *currUser;
    for (int i=1;i<twitter_system->num_users;i++) {
        printf("\nUsername of next user:");
        puts("called 2");
        /*
        fgets(users[i].username, USR_LENGTH, stdin);
        if (users[i].username[strlen(users[i].username) -1] == "\n")
         users[i].username[strlen(users[i].username) -1] = "\0";
        users[i].num_followers = 0;
        users[i].num_following = 0;
         */
        fgets(twitter_system->users[i].username, USR_LENGTH, stdin);
        if (twitter_system->users[i].username[strlen(twitter_system->users[i].username) - 1] == '\n')
            twitter_system->users[i].username[strlen(twitter_system->users[i].username) - 1] = '\0';
        orig = 0;
        while (orig == 0) {
            orig = 1;
            for (int j=0;j<i;j++){
                 if(strcasecmp(twitter_system->users[j].username, twitter_system->users[i].username) == 0){
                     orig = 0;
                 }
             }
            if (orig == 0) {
                printf("Username taken. Please try a different username.\n");
                fgets(twitter_system->users[i].username, USR_LENGTH, stdin);
                if (twitter_system->users[i].username[strlen(twitter_system->users[i].username) - 1] == '\n')
                    twitter_system->users[i].username[strlen(twitter_system->users[i].username) - 1] = '\0';
            }
        }

        twitter_system->users[i].num_followers = 0;
        twitter_system->users[i].num_following = 0;

        //twitter_system->lastUser->nextUser = currUser;
        //twitter_system->lastUser = currUser;
    }
}