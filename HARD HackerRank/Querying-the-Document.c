#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

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
    //allocate memory for the document using calloc to init pointers
    char**** docu = (char****)calloc(MAX_PARAGRAPHS, sizeof(char***));
    
    //init current word (acts as temp)
    char current_word [MAX_CHARACTERS];
    
    //init index of each object
    int char_i =0, word_i =0, sent_i=0, para_i=0;
    
    for (int i=0; i<strlen(text); i++){
        //we will start from the end to the beginning
        if (text[i] == ' ' || text[i] == '.' || text[i] == '\n'){
            
            //start with space ' ' condition if the char_i is more than zero
            if (char_i>0){//this means there is a word
                //finish the word
                current_word[char_i] = '\0';
                
                // Ensure space for a new sentence in the current paragraph
                if (docu[para_i] == NULL) {
                    // Initial allocation for sentences
                    docu[para_i] = (char***)calloc(1, sizeof(char**));  
                    sent_i = 0;  // Reset sentence index
                } 
                else {
                    // Reallocate for additional sentences
                    docu[para_i] = (char***)realloc(docu[para_i], (sent_i + 1) * sizeof(char**));
                }
                
                // Ensure space for a new word in the current sentence
                if (docu[para_i][sent_i] == NULL) {
                    // Initial allocation for words
                    docu[para_i][sent_i] = (char**) calloc(1, sizeof(char*));  
                    word_i = 0; // Reset word index
                } else {
                    // Reallocate for additional words
                    docu[para_i][sent_i] = (char**) realloc(docu[para_i][sent_i], 
                    (word_i + 1) * sizeof(char*));  
                }
                
                // Allocate memory for the word itself and copy it
                docu[para_i][sent_i][word_i] = (char*) malloc((char_i + 1) * sizeof(char));
                strcpy(docu[para_i][sent_i][word_i], current_word);
                 
                //increment the word index and reset temp word counter
                word_i++;
                char_i = 0;
                }

            // Handle sentence completion ('.' means sentence end)
            if (text[i] == '.') {
                sent_i++;  // Move to the next sentence
                word_i = 0;  // Reset word index for the new sentence
            }
            
            // Handle paragraph completion ('\n' means new paragraph)
            if (text[i] == '\n') {
                para_i++;  // Move to the next paragraph
                sent_i = 0;  // Reset sentence index for the new paragraph
            }
        } 
        else {
            // Add characters to the current word
            current_word[char_i++] = text[i];
    
        }//else
    }//for
    
    return docu;
}//function

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

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main() 
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     
}
