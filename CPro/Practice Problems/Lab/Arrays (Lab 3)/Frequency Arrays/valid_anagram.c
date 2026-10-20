#include <stdbool.h>
#include <string.h>

bool isAnagram(char* s, char* t) {
    size_t len = strlen(s);

    int f1[26];
    int f2[26];

    for (size_t i = 0; i < len; i++) {
        f1[s[i] - 97]++;
        f2[t[i] - 97]++;
    }

    for (int i = 0; i < 26; i++) {
        if (f1[i] != f2[i]) return false;
    }
    
    return true;
}