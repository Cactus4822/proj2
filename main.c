#include <stdio.h>
#include "twitter_create.h"


int main() {

    twitter twitter_system;
    create_twitter_system(&twitter_system);

    for(int i =0; i < twitter_system.num_users; i++){
        user usr = twitter_system.users[i];
        printf("User: %s; Followers: %d; Following: %d\n",usr.username, usr.num_followers, usr.num_followers );
    }



}
