//
// Created by thepu on 05/05/2022.
//

#ifndef PROJ2_TWITTER_FUNCTIONS_H
#define PROJ2_TWITTER_FUNCTIONS_H

#endif //PROJ2_TWITTER_FUNCTIONS_H

#include "twitter_create.h"

void postTweet(twitter * twtr, tweet * link, user * usr);

int followFunc(user *usr, twitter * twitter_system);

//void printList(twitter * twtr);

int deleteFunc(user *usr, twitter * twitter_system, tweet * tweetr);

void newsFeed(twitter * twtr, tweet * link, user * usr, int index);