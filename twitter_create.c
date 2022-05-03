//
// Created by Lili on 30/03/2022.
//

#include <stdio.h>
#include <string.h>
#include "twitter_create.h"

void create_twitter_system(twitter * twitter_system){

    int num_users;

    printf("Enter number of users: \n");
    scanf("%d", &num_users);
    while (num_users < 1){
        printf("Error: Need at least 1 user.\n");
        printf("Enter number of users: \n");
        scanf("%d", &num_users);
    }
    printf("%d users.\n", num_users);

    user users[num_users];
    tweet news_feed[MAX_TWEETS];


    for (int i=0; i<num_users;i++){
        printf("Username of next user (Press Enter to end): ");
    }

}