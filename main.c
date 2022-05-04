#include <stdio.h>
#include "twitter_create.h"
#include "twitter_follow.h"
#include "twitter_tweet.h"

int main() {
    twitter twitter_system;
    create_twitter_system(&twitter_system);
    printf("\n%d users in t_s.n_u\n", twitter_system.num_users);

    int turn=0, i;
    user usr = twitter_system.users[i];

    for(i=0; i < twitter_system.num_users; i++){
        printf("User: %s; Followers: %d; Following: %d\n",usr.username, usr.num_followers, usr.num_followers);
    }

    i=0;
    while (turn != -1){
        if (i < twitter_system.num_users){
            i = 0;
        }
        printf("%s is in control. Select an operation:\n", usr.username);

    }


}
