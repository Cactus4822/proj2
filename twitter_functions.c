
#include "twitter_functions.h"

void postTweet(tweet * twt);

void postTweet(tweet * twt){
    twitter * twtr;
    printf("What's happening?\n");
    fgets(twt->msg, TWEET_LENGTH, stdin);
    twt->id++;
    //twtr->num_tweets++;
}

void follow();

void follow(){
}