


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "spell.h"


#define DICTIONARY "wordlist.txt"
#define TESTDICT "test_worlist.txt"

int _test_01();
int _test_02();
void log_msg(char* msg);
void log_msg_i1(char* msg, int i1);
void log_err(char* msg);

int main(int argc, char** argv)
{
    int ret = 0;
    int ec;
    
    ec = _test_01();
    ec = _test_02();
    ret = 1;

EXIT_RET:
    return ret;
}



int _test_01()
{
    int ret = 0;
    int ec;
    hashmap_t hashtable[HASH_SIZE];
    FILE* fd;
    char* mspell[MAX_MISSPELLED];

    memset(mspell, 0, sizeof(char*)*MAX_MISSPELLED);
    
    log_msg("---- Test 01 ------------------");
    log_msg("Loading dictionary...");
    ec = load_dictionary(DICTIONARY, hashtable);
    if(!ec)
    {
        ret = -1;
        log_err("Failed to load dictionary!");
        goto EXIT_RET;
    }

    log_msg("-- Loading test file 'test1'...");
    fd = fopen("test1.txt", "rb");
    if(!fd)
    {
        ret = -2;
        log_err("Failed to open test file.");
        goto EXIT_RET;
    }

    ec = check_words(fd, hashtable, mspell);
    log_msg_i1("%d invalid words found", ec);

    fclose(fd);
    
    log_msg("-- Loading test file 'tolower'...");
    fd = fopen("tolower.txt", "rb");
    if(!fd)
    {
        ret = -2;
        log_err("Failed to open test file.");
        goto EXIT_RET;
    }

    ec = check_words(fd, hashtable, mspell);
    log_msg_i1("%d invalid words found", ec);

    fclose(fd);

EXIT_RET:
    return ret;
}
int _test_02()
{
    int ret = 0;
    int ec;
    hashmap_t hashtable[HASH_SIZE];
    
    log_msg("---- Test 02 ----------------");
    log_msg("Loading dictionary...");
    ec = load_dictionary(DICTIONARY, hashtable);
    if(!ec)
    {
        ret = -1;
        log_err("Failed to load dictionary!");
        goto EXIT_RET;
    }

    log_msg("Testing words...");
    if(!check_word("test", hashtable)) log_err("'test' err");
    if(!check_word("Test", hashtable)) log_err("'Test' err");
    if(!check_word("tesT", hashtable)) log_err("'tesT' err");
    if(!check_word("tESt", hashtable)) log_err("'tESt' err");
    if(!check_word("!@#$%^&*()test!@#$%^&*()", hashtable)) log_err("'!@#$%^&*()test!@#$%^&*()' err");
    if(check_word("te.st", hashtable)) log_err("'te.st' err");
    if(check_word("ith", hashtable)) log_err("'ith' err");
    

EXIT_RET:
    return ret;
}

void log_msg(char* msg)
{
    fprintf(stdout, msg); fprintf(stdout, "\n");
}
void log_msg_i1(char* msg, int i1)
{
    fprintf(stdout, msg, i1); fprintf(stdout, "\n");
}

void log_err(char* msg)
{
    fprintf(stdout, msg); fprintf(stdout, "\n");
}