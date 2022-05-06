
#include "twitter_functions.h"



int id = 0;

void postTweet( twitter * twtr, tweet * link, user * usr){
    if( twtr->num_tweets > MAX_TWEETS){
        printf("You have reached the max Tweet limit.\n");
        return;
    }
    //tweet * link;
    printf("What's happening?\n");
    int pass = 0;
    while (pass != 1) {
    fgets(link->msg, TWEET_LENGTH, stdin);
    if (strchr(link->msg, '\n') == NULL) {
        printf("Error: Your tweet is too long. Please try again:\n");
        fflush(stdin);
    } else {
        pass = 1;}
    }

    strcpy(link->user, usr->username);
    link->id = twtr->tweets_created;
    link->nextTweet = NULL;

    if (twtr->num_tweets != 0) {
        twtr->lastTweet->nextTweet = link;
        twtr->lastTweet = link;
    } else {
        twtr->firstTweet = twtr->lastTweet = link;
    }
    twtr->num_tweets++;
    twtr->tweets_created++;
}
/*void printList(twitter * twtr) {
    tweet *ptr = twtr->firstTweet;
    printf("\n[ ");
    //start from the beginning
    while(ptr != NULL) {
        printf("(%d,%s) ",ptr->id,ptr->msg);
        ptr = ptr->nextTweet;
    }

    printf(" ]");
}*/

int followFunc(user *usr, twitter * twitter_system){ // Function to Follow/Unfollow Users
    int valid = 0; // Checks validity of entered command
    int j=0, k=0, l=0, pos; // Holds pos of user in twitter_system->users[], k and l counters
    char opt[10]; // User option
    char target[USR_LENGTH]; // Target is the user they want to "interact" with
    // Strings to compare against user command
    char edit[10] = "/edit";
    char follow[10] = "/follow";
    char unfollow[10] = "/unfollow";
    char leave[10] = "/leave";

    while(strcmp(twitter_system->users[j].username, usr->username) != 0){ // Finds pos of current user (for continuity)
        j++;
    }

    // Stats to show
    printf("\nHello %s!\n\n", twitter_system->users[j].username);
    printf("Your Stats\n--------\n");
    printf("%d following\n", twitter_system->users[j].num_following);
    for(int i=0;i<twitter_system->users[j].num_following;i++){
        printf("%s; ", &twitter_system->users[j].following[i]);
    }
    printf("\n%d followers\n", twitter_system->users[j].num_followers);
    for(int i=0;i<twitter_system->users[j].num_followers;i++){
        printf("%s; ", &twitter_system->users[j].followers[i]);
    }


    while(valid == 0){ // "Infinite" loop, goes until command leave
        printf("\nWhat would you like to do?\n");
        while((strcmp(opt, leave) != 0) && (strcmp(opt, edit) != 0)){
            printf("%s to manage followers and following,\n%s to return to the main menu.\n", edit, leave);
            scanf("%s", &opt);
            if(strcmp(opt, leave) == 0){
                printf("Leaving...\n");
                return 0;
            }
            else if(strcmp(opt, edit) == 0){
                printf("Entering...\n");
            }
            else{
                printf("Invalid option.\n\n");
            }
        }
        printf("Input %s <username> or %s <username>\n", follow, unfollow); // Gets command and target of command
        scanf("%s %s", &opt, &target);
        printf("opt is %s. target is %s.\n", opt, target);

        if(strcasecmp(target, twitter_system->users[j].username) == 0){ // If user targets self
            printf("You cannot target yourself.\n");
        }
        else if(strcmp(opt, follow) == 0){ // Following a user
            valid = 1;
            for(int i=0;i<twitter_system->users[j].num_following;i++){ // Checks if they're already followed
                if (strcasecmp(twitter_system->users[j].following[i], target) == 0){
                    printf("You are already following %s.\n", target);
                    valid = 0;
                }
            }
            if(valid == 1){ // If they're already following the target, this is all skipped
                k=0;
                while(((strcasecmp(twitter_system->users[k].username, target)) != 0) && (k < twitter_system->num_users)){
                    k++; // Finds the position of the user they want to follow on the twitter_system->users[] array
                }
                if(k+1>twitter_system->num_users){ // If the user isn't found
                    printf("There is no user named %s.\n", target);
                }
                else{ // Follow the user and become one of their followers
                    strcpy(twitter_system->users[j].following[twitter_system->users[j].num_following++], twitter_system->users[k].username); // User is now following target
                    strcpy(twitter_system->users[k].followers[twitter_system->users[k].num_followers++], twitter_system->users[j].username); // Adds user as follower to target
                    printf("You are now following %s\n", twitter_system->users[k].username);
                }
                valid = 0;
            }
        }
        else if(strcmp(opt, unfollow) == 0){ // Unfollow a user
            //printf("[Unfollow user]");
            valid = 1;
            while((strcasecmp(twitter_system->users[j].following[k], target) != 0) && k < twitter_system->users[j].num_following){
                k++; // Makes sure you're following the user you're trying to unfollow
            }
            // Target is not on user's following list
            if(k+1>twitter_system->users[j].num_following){
                printf("You are not following %s.", target);
                valid = 0;
            }
            else{
                pos = k;
                k=0;
                while((strcasecmp(twitter_system->users[k].username, target) != 0) && (k < twitter_system->num_users)){ // Makes k hold the target's actual pos
                    k++;
                }
            }
            // Target is on user's following list
            if(valid == 1){
                // Removes user from target's followers list
                while(strcmp(twitter_system->users[j].username, twitter_system->users[k].followers[l]) != 0){ // Finds pos of current user on target's followers list
                    l++;
                }
                if(l+1 == twitter_system->users[k].num_followers){ // If user is at end of target's followers list
                    twitter_system->users[k].num_followers--; // Decrement target's follower number and user is gone. If new follower gets added, they'll replace the old follower (user)
                }
                else{
                    for(int i=l+1;i<twitter_system->users[k].num_followers;i++){ // Writes over previous value in array to "slide the rest down"
                        strcpy(twitter_system->users[k].followers[i-1], twitter_system->users[k].followers[i]);
                    }
                    twitter_system->users[k].num_followers--; // Decrement target's follower number and user is gone. If new follower gets added, they'll replace the old follower (user)
                }
                // Removes target from user's following list
                if(pos+1 == twitter_system->users[j].num_following){ // If the target is at the end of the user's following list
                    twitter_system->users[j].num_following--;
                    printf("%s unfollowed.\n", target);
                }
                else{ // "Slides down" user's following list to remove the target from it
                    for(int i=pos+1;i<twitter_system->users[j].num_following;i++){
                        strcpy(twitter_system->users[j].following[i-1], twitter_system->users[j].following[i]);
                    }
                    //printf("twitter_system->users[j].following[k] is now %s.\n", &twitter_system->users[j].following[k]);
                    twitter_system->users[j].num_following--;
                    printf("%s unfollowed.\n", target);
                }
                valid = 0;
            }
        }
        else{
            printf("Invalid command.\n");
        }
    }
}

int deleteFunc(user *usr, twitter * twitter_system, tweet * tp) {
    int j=0;
    while(strcmp(twitter_system->users[j].username, usr->username) != 0){ // Finds pos of user (for tracking)
        j++;
    }
    printf("\nGoodbye, %s.\n\n", twitter_system->users[j].username);
    //printf("%d tweet(s) total.\n", twitter_system->num_tweets);

    // Remove deleted user's tweets
    printf("ptr points to %s.\n", &tp);
    if (twitter_system->firstTweet == NULL){
        printf("itsnull\n");
    }
    else{
        printf("notnull\n");
    }
    for(int i=0;i<twitter_system->num_tweets;i++){
        printf("%d: %s.\n", tp->id, tp->msg);
        tp = tp->nextTweet;
    }
    //return 0;
    // Prints who is following who (for troubleshooting)
    for(int i=0;i<twitter_system->num_users;i++){
        printf("uh\n");
        printf("t_s->users[i] is %s.\n", twitter_system->users[i]);
        printf("twitter_system->users[%d].num_following is %d.\n", i, twitter_system->users[i].num_following);
        for(int k=0;k<twitter_system->users[i].num_following;k++){
            printf("%s.following[k] is %s.\n", twitter_system->users[i], twitter_system->users[i].following[k]);
        }
    }

    if(j+1 == twitter_system->num_users){
        // Unfollow everyone and make them unfollow user
        twitter_system->num_users--;
    }
    else{
        strcpy(twitter_system->users[j].username, twitter_system->users[twitter_system->num_users -1].username);
        // Unfollow everyone and make them unfollow user
        // Write over all data from last user to replace them
        twitter_system->num_users--;
    }
    return 0;
}

void newsFeed(twitter * twtr, tweet * link, user * usr, int index) {

    if (index == 1) {
        link = twtr->firstTweet;
    }

    if (link == NULL || index == 10) {
        printf("End of feed\n");
        return;
    } else {
        int found = 0;

        for (int i = 0; i < MAX_FOLLOWING; i++) {
            if (strcmp(link->user, usr->following[i]) == 0) {
                found = 1;
                break;
            }
        }
        if (found == 1 || strcmp(usr->username, link->user) == 0) {
            printf("By: %s\nTweet: %s\n", link->user, link->msg);
            index++;
        }
        newsFeed(twtr, link->nextTweet, usr, index);
    }
}

int isFollowing(user *usr, char usrB[]) {
    for (int i = 0; i < MAX_FOLLOWING; i++) {
        if(strcmp(usrB, usr->following[i]) == 0) {
            return 1;
        }
    }
    return 0;
}