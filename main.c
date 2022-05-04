#include <stdio.h>
#include "twitter_create.h"

int main() {
    printf("part1\n");
    twitter twitter_system;
    create_twitter_system(&twitter_system);
    printf("part2\n");
    printf("\n%d users in t_s.n_u\n", twitter_system.num_users);

    for(int i =0; i < twitter_system.num_users; i++){
        user usr = twitter_system.users[i];
        printf("User: %s; Followers: %d; Following: %d\n",usr.username, usr.num_followers, usr.num_followers);
    }
    printf("part4\n");


}
