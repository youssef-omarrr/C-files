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

/*
// 'doc' is the document
struct paragraph* para = &doc.data[i];

// 'doc' is the document, 'i' is the paragraph index, 'j' is the sentence index
struct sentence* sent = &doc.data[i].data[j];

// 'doc' is the document, 'i' is the paragraph index, 'j' is the sentence index, 'k' is the word index
struct word* wrd = &doc.data[i].data[j].data[k];

char* word_data = doc.data[i].data[j].data[k].data;

*/

struct document get_document(char *text) {
    struct document docu;
    docu.data = (struct paragraph *)malloc(MAX_PARAGRAPHS * sizeof(struct paragraph));
    
    // Initialize paragraphs
    for (int i = 0; i < MAX_PARAGRAPHS; i++) {
        docu.data[i].data = NULL;
        docu.data[i].sentence_count = 0;
    }

    char current_word[MAX_CHARACTERS]; // Temporary storage for current word
    int char_i = 0, word_i = 0, sent_i = 0, para_i = 0;

    for (int i = 0; i < strlen(text); i++) {

        if (text[i] == ' ' || text[i] == '.' || text[i] == '\n') {

            if (char_i > 0) { // Word is complete
                current_word[char_i] = '\0';

                // Ensure space for a new sentence in the current paragraph
                if (docu.data[para_i].data == NULL) {
                    docu.data[para_i].data = (struct sentence *)calloc(1, sizeof(struct sentence));
                    docu.data[para_i].sentence_count = 1;
                    sent_i = 0;
                } else {
                    docu.data[para_i].data = (struct sentence *)realloc(docu.data[para_i].data, (sent_i + 1) * sizeof(struct sentence));
                }

                // Ensure space for a new word in the current sentence
                if (docu.data[para_i].data[sent_i].data == NULL) {
                    docu.data[para_i].data[sent_i].data = (struct word *)calloc(1, sizeof(struct word));
                    docu.data[para_i].data[sent_i].word_count = 1;
                    word_i = 0;
                } else {
                    docu.data[para_i].data[sent_i].data = (struct word *)realloc(docu.data[para_i].data[sent_i].data, (word_i + 1) * sizeof(struct word));
                    docu.data[para_i].data[sent_i].word_count++;
                }

                // Allocate memory for the word and copy it
                docu.data[para_i].data[sent_i].data[word_i].data = (char *)malloc((char_i + 1) * sizeof(char));
                strcpy(docu.data[para_i].data[sent_i].data[word_i].data, current_word);

                // Increment word index and reset temporary word counter
                word_i++;
                char_i = 0;
            }

            // Handle sentence end ('.')
            if (text[i] == '.') {
                sent_i++;
                word_i = 0; // Reset word index for the new sentence
                docu.data[para_i].sentence_count = sent_i;
            }

            // Handle paragraph end ('\n')
            if (text[i] == '\n') {
                para_i++;
                sent_i = 0; // Reset sentence index for the new paragraph
                
            }
        } 
        else {
            // Add characters to the current word
            current_word[char_i++] = text[i];
        }
    }
    
    docu.paragraph_count = para_i+1;
    
    return docu;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    // Ensure that paragraph, sentence, and word indices are within bounds
    if (n > 0 && n <= Doc.paragraph_count && 
        m > 0 && m <= Doc.data[n - 1].sentence_count &&
        k > 0 && k <= Doc.data[n - 1].data[m - 1].word_count) {
        return Doc.data[n - 1].data[m - 1].data[k - 1];
    }
    
    // Return an empty word in case of invalid input
    struct word empty_word = { NULL };
    return empty_word;
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) {
    // Ensure that paragraph and sentence indices are within bounds
    if (m > 0 && m <= Doc.paragraph_count &&
        k > 0 && k <= Doc.data[m - 1].sentence_count) {
        return Doc.data[m - 1].data[k - 1];
    }
    
    // Return an empty sentence in case of invalid input
    struct sentence empty_sentence = { NULL, 0 };
    return empty_sentence;
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    // Ensure that paragraph index is within bounds
    if (k > 0 && k <= Doc.paragraph_count) {
        return Doc.data[k - 1];
    }
    
    // Return an empty paragraph in case of invalid input
    struct paragraph empty_paragraph = { NULL, 0 };
    return empty_paragraph;
}


void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}