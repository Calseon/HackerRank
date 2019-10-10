#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

// Question: https://www.hackerrank.com/challenges/querying-the-document/problem

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
    return document[n-1][m-1][k-1];
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 
    return document[m-1][k-1];
}

char*** kth_paragraph(char**** document, int k) {
    return document[k-1];
}

char**** get_document(char* text) {
    char ****document;
    int paragraph = 1, sentence = 1, word = 1;
    document = (char****)malloc(sizeof(char***));
    document[0] = (char***)malloc(sizeof(char**));
    document[0][0] = (char**)malloc(sizeof(char*));
    
    /* ^Basically, we don't allocate new memory for words. We just
        make *word pointers to locations in text[]. We change text[]
        by inserting null terminators at the end of words
    */
    document[0][0][0] = text; 

    int i = 0;
    while(text[i] != '\0'){

        // Check ahead the next character. If it's a newline,
        // then current char is guaranteed to be a period.
        // Skip switch case for period and jump to '\n' case
        if(text[i+1]=='\n'){
            text[i] = '\0'; // Terminate the current word
            i++; // Jump ahead 1
        }
        switch(text[i]){

            case '\n':
                // Terminate the null
                //text[i] = '\0'; // redundant, can be removed

                // Move to next paragraph, and reset sentence and word
                word = 1;
                sentence = 1;
                paragraph++;

                // If next char isn't another null (happens at EOF), make room for another paragraph.
                if(text[i+1]!='\0'){
                    document = (char****)realloc(document,sizeof(char***)*paragraph);
                    document[paragraph-1] = (char***)malloc(sizeof(char**)*sentence);
                    document[paragraph-1][sentence-1] = (char**)malloc(sizeof(char*)*word);
                    document[paragraph-1][sentence-1][word-1] = &text[i+1]; 
                }
                
                break;

            case '.':
                // Terminate the current word
                text[i] = '\0';

                // Move to next sentence, and reset word count
                word = 1;
                sentence++;
                document[paragraph-1] = (char***)realloc(document[paragraph-1],sizeof(char**)*sentence);
                document[paragraph-1][sentence-1] = (char**)malloc(sizeof(char*));

                // Start next word at the next character
                document[paragraph-1][sentence-1][word-1] = &text[i+1];
                break;

            case ' ':
                // Terminate the current word
                text[i] = '\0';
                
                // Increase word count
                word++;

                // Make room for another word in sentence
                document[paragraph-1][sentence-1]=(char**)realloc(document[paragraph-1][sentence-1], sizeof(char*)*word);

                // Start next word at the next character
                document[paragraph-1][sentence-1][word-1] = text+i+1;//equivalent to &text[i+1], I just did this to prove a point
                break;
        }

        i++;
    }
    return document;
}

