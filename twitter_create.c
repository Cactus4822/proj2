//
// Created by Lili on 30/03/2022.
//

#include <stdio.h>
#include <string.h>
#include "twitter_create.h"

void create_twitter_system(twitter * twitter_system){

    int num_users; // Number of users ygm

    printf("Enter number of users: \n"); // Gets number of users
    scanf("%d", &num_users);
    while (num_users < 1){ // Makes sure there's at least one user
        printf("Error: Need at least 1 user.\n");
        printf("Enter number of users: \n");
        scanf("%d", &num_users);
    }
    printf("%d users.\n", num_users); // Just to doublecheck

    user users[num_users]; // For creating user structs
    tweet news_feed[MAX_TWEETS];
    int num_tweets = 0;

    printf("Username of first user: ");
    fgets(users[0].username, USR_LENGTH)
    users[0].num_followers = 0;
    users[0].num_following = 0;

    for (int i=1;i<num_users;i++){
        printf("Username of next user (Press Enter to end): ");
        fgets(user)
    }

}