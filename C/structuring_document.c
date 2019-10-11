#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};

void add_paragraph(struct document* doc, struct paragraph* par){
    if(doc->data == NULL){
        doc->data = (struct paragraph*)malloc(sizeof(struct paragraph));
        doc->paragraph_count = 0;
    }
    doc->data = (struct paragraph*)realloc(doc->data, sizeof(struct paragraph) * ++doc->paragraph_count);
    doc->data[doc->paragraph_count-1] = *par;
    par->data = NULL;
}

void add_sentence(struct paragraph* par, struct sentence* sen){
    // Check empty, if so, re-init data and count
    if(par->data == NULL){
        par->data = (struct sentence*)malloc(sizeof(struct sentence));
        par->sentence_count = 0;
    }

    //Reallocate memory - make space for new sentence
    par->data = (struct sentence*)realloc(par->data, sizeof(struct sentence) * ++par->sentence_count);

    // Copy sentence into paragraph
    par->data[par->sentence_count-1] = *sen;

    // Clear the original sentence struct so we can re-use it
    sen->data = NULL;
}


// Gonna practice using dot operators for sentence and word structs
void add_word(struct sentence* sen, struct word* wrd){
    // Check empty, if so, re-init data and count
    if((*sen).data == NULL){
        (*sen).data = (struct word*)malloc(sizeof(struct word));
        (*sen).word_count = 0;
    }

    // Reallocate memory - make space for new word
    int newSize = sizeof(struct word) * ++(*sen).word_count;
    (*sen).data = (struct word*)realloc((*sen).data, newSize);

    // Copy word into sentence (setting one struct equal to another is a copy operation)
    (*sen).data[(*sen).word_count-1] = *wrd;

    // Clear the struct word that was passed in, so we can re-use it
    // Doesn't affect the word we just put into sentence, cause that was a Copy
    // DON'T free the array, cause it's in the sentence now. Just clear pointer
    (*wrd).data = NULL;
    //printf("Size:%d Last word: %s\n", newSize, (*sen).data[(*sen).word_count-1]);
}

void add_char(struct word* wrd, char c){
    // Persistent static int for keeping track of word size after every add_char call
    static int wordsize = 0;

    // Check empty
    if((*wrd).data == NULL){
        (*wrd).data = (char*) malloc(sizeof(char));
        wordsize = 0;
    }
    // Reallocate memory - make space for new char, +1 for the null char
    (*wrd).data = (char*) realloc((*wrd).data, sizeof(char)*(++wordsize)+1);

    // Insert the new char
    (*wrd).data[wordsize-1] = c;

    // Terminate the string
    (*wrd).data[wordsize] = 0;
}

struct document get_document(char* text) {

    struct document doc;
    struct paragraph par;
    struct sentence sen;
    struct word wrd;

    doc.data = NULL;
    par.data = NULL;
    sen.data = NULL;
    wrd.data = NULL;

    for(int i = 0; i<=strlen(text);i++)
    {
        switch(text[i]){
            case '\0':
            case '\n':
                add_paragraph(&doc,&par);
                break;

            case '.':
                add_word(&sen,&wrd);
                add_sentence(&par,&sen);
                break;
      
            case ' ':
                add_word(&sen,&wrd);
                break;
            default:
                add_char(&wrd, text[i]);
                break;
        }
    }
    return doc;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    return Doc.data[n-1].data[m-1].data[k-1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    return Doc.data[m-1].data[k-1];
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    return Doc.data[k-1];
}

