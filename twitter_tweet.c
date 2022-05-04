//
// Created by ninja on 5/4/2022.
//

#include "twitter_tweet.h"

void postTweet(tweet * twt);

void postTweet(tweet * twt){
    twitter * twtr;
    printf("What's happening?\n");
    fgets(twt->msg, TWEET_LENGTH, stdin);
    twt->id++;
    //twtr->num_tweets++;
}
