//
// Created by Lili on 30/03/2022.
//

#include <stdio.h>
#include <string.h>
#include "twitter_create.h"

void create_twitter_system(twitter * twitter_system){

    twitter_system->num_users = 0;
    twitter_system->firstUser = NULL;
    twitter_system->lastUser = NULL;

    twitter_system->num_tweets = 0;
    twitter_system->firstTweet = NULL;
    twitter_system->lastTweet = NULL;

    int num_users; // Number of users ygm

    printf("Enter number of users: \n"); // Gets number of users
    scanf("%d", &num_users);
    getchar();
    twitter_system->num_users = num_users;
    while (num_users < 1){ // Makes sure there's at least one user
        printf("Error: Need at least 1 user.\n");
        printf("Enter number of users: \n");
        scanf("%d", &num_users);
    }
    printf("%d users.\n", num_users); // Just to double-check

    user users[num_users]; // Users Array
    tweet news_feed[MAX_TWEETS];

    printf("Username of first user:");
    fgets(users[0].username, USR_LENGTH, stdin);
    users[0].num_followers = 0;
    users[0].num_following = 0;

    for (int i=1;i<num_users;i++){
        printf("\nUsername of next user:");
        fgets(users[i].username, USR_LENGTH, stdin);
        users[i].num_followers = 0;
        users[i].num_following = 0;
    }

}