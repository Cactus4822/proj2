//
// Created by Lili on 30/03/2022.
//

#ifndef ASSIGNMENT2_TWITTER_CREATE_H
#define ASSIGNMENT2_TWITTER_CREATE_H

#endif //ASSIGNMENT2_TWITTER_CREATE_H

#define TWEET_LENGTH 270
#define USR_LENGHT 100
#define MAX_FOLLOWERS 30
#define MAX_FOLLOWING 30
#define MAX_TWEETS 100
#define MAX_USERS 100

typedef struct tweet{
    int id;
    char msg[TWEET_LENGTH];
    char user[USR_LENGHT];

}tweet;

typedef struct user{
    char username[USR_LENGHT];
    char followers[MAX_FOLLOWERS];
    int num_followers;
    char following[MAX_FOLLOWING];
    int num_following;
}user;

typedef struct twitter{
    tweet news_feed[MAX_TWEETS];
    user users[MAX_USERS];
    int num_tweets;
    int num_users;
} twitter;

void create_twitter_system(twitter * twitter_system);