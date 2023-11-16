//
// Created by lolikion on 16.11.23.
//

#ifndef TITLED1_RSA_CLI_H
#define TITLED1_RSA_CLI_H
void console_app();

big_int *get_secret_key(char *target);
big_int *get_public_key(char *target);

void add_key(char *name,unsigned int len);


#endif //TITLED1_RSA_CLI_H
