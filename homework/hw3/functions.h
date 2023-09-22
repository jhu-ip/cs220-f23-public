#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>

#define MAX_WORD_SIZE 32

/** Function to read data from file pointer into words array.
 *  @param fp the filepointer to search words file.
 *  @param words is the 2D character array of words
 *  @param size is the expected number of words in the file.
 *  @return 0 if no issues, 1 if there are issues.
 */
int read_file(FILE *fp, char words[][MAX_WORD_SIZE + 1], int size);

/** Match function to check whether regex matches a word.
 * @param regex, is a null terminated char array of the regex
 * @param word is the null terminated char array of word to match to
 * @param restriction is the restriction size for the tilde operator
 * @return 1 if it is a match, else 0 if it's not a match.
 */
int match(const char *regex, const char *word, int restriction);

// Feel free to add more helper functions! Make sure they are well commented.
// If you do change the match function, note that it is called by the functions
// in test_functions.c so make sure to change the call to match there accordingly.

#endif // FUNCTIONS_H
