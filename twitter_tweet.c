//
// Created by ninja on 5/4/2022.
//

#include "twitter_tweet.h"
#include "twitter_create.h"

void postTweet(tweet * twt);

void postTweet(tweet * twt){
    printf("What's happening?");
    fgets(twt->msg, TWEET_LENGTH, stdin);
    twt->id++;
}
