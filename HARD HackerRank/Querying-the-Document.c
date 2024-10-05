#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

//init structs
typedef struct word{
    //a word is an array of letters
    char* letter;
}word;

typedef struct sent{
    //a sentence is an array of words
    word* word;
    int word_count;
} sent;

typedef struct para{
    //a paragraph is an array of sentences
    sent* sent;
    int sent_count;
}para;

typedef struct docu{
    //a document is an array of paragraphes
    para* para;
    int para_count;
}docu;

//init arrays
word word1;
sent sent1;
para para1;
docu docu1;


word kth_word_in_mth_sentence_of_nth_paragraph(docu document, int k, 
int m, int n) {
    return document.para[n].sent[m].word[k];
}

sent kth_sentence_in_mth_paragraph(docu document, int k, int m) { 
    return document.para[m].sent[k];
}

para kth_paragraph(docu document, int k) {
    return document.para[k];
}

docu get_document(char* text) {
    //allocate memory for the document
    docu1.para = malloc(MAX_PARAGRAPHS*sizeof(para));
    
    //init current word (acts as temp)
    char current_word [MAX_CHARACTERS];
    
    //init index of each object
    int char_i =0, word_i =0, sent_i=0, para_i=0;
    
    for (int i=0; i< strlen(text); i++){
        //we will start from the end to the beginning
        if (text[i] == ' ' || text[i] == '.' || text[i] == '\n'){
            //start with space ' ' condition if the word_len is more than zero
            if (char_i>0){//this means there is a word
                //finish the word
                current_word[char_i] = '\0';
                
                //store the word (+1 for the '\0')
                word1.letter = malloc((char_i+1)*sizeof(char));
                strcpy (word1.letter, current_word);
                
                //store word in sentence in the correct index
                //realloc it to equal the number of words
                sent1.word = realloc(sent1.word, (word_i+1)*sizeof(word));
                sent1.word[word_i] = word1;
                
                //increment the word index and reset temp word counter
                word_i++;
                char_i = 0;
            }
            
            //end of the sentence
            if (text[i] == '.'){
                //realloc paragraph to include new sentence
                para1.sent = realloc(para1.sent, (sent_i+1)*sizeof(sent));
                
                //add sentence to paragraph and inc sentence index
                para1.sent[sent_i] = sent1;
                sent_i++;
                
                //reset sentence to be empty for the new one
                sent1.word = NULL;
                word_i = 0;
            }
            
            //end of paragraph
            if (text[i] == '\n'){
                //realloc document to include new paragraph
                docu1.para = realloc(docu1.para, (para_i+1)*sizeof(para));
                
                //add paragraph to document and inc paragraph index
                docu1.para[para_i] = para1;
                para_i++;
                
                //reset paragraph to be empty for new one
                para1.sent = NULL;
                sent_i = 0;
            }
        }
        
        //in the middle of a word
        else{
            current_word[char_i] = text[i];
            char_i++;
        }
    }
    
    return docu1;  // Return document structure
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

    char* returnDoc = (char*)malloc((strlen(doc) + 1) * sizeof(char));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence, int word_count) {
    for (int i = 0; i < word_count; i++) {
        printf("%s", sentence[i]);
        if (i != word_count - 1)
            printf(" ");
    }
}

void print_paragraph(char*** paragraph, int sent_count, int* word_counts) {
    for (int i = 0; i < sent_count; i++) {
        print_sentence(paragraph[i], word_counts[i]);
        printf(".");
    }
}

int main() {
    char* text = get_input_text();
    docu document = get_document(text);  // Now returns docu struct
    
    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3) {
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            
            word w = kth_word_in_mth_sentence_of_nth_paragraph(document, k - 1, m - 1, n - 1);
            print_word(w.letter);  // Correct word output
        } else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            
            sent s = kth_sentence_in_mth_paragraph(document, k - 1, m - 1);
            char** sentence = malloc(s.word_count * sizeof(char*));
            for (int i = 0; i < s.word_count; i++) {
                sentence[i] = s.word[i].letter;
            }
            print_sentence(sentence, s.word_count);
            free(sentence);
        } else if (type == 1) {
            int k;
            scanf("%d", &k);
            
            para p = kth_paragraph(document, k - 1);
            char*** paragraph = malloc(p.sent_count * sizeof(char**));
            int* word_counts = malloc(p.sent_count * sizeof(int));
            for (int i = 0; i < p.sent_count; i++) {
                paragraph[i] = malloc(p.sent[i].word_count * sizeof(char*));
                word_counts[i] = p.sent[i].word_count;
                for (int j = 0; j < p.sent[i].word_count; j++) {
                    paragraph[i][j] = p.sent[i].word[j].letter;
                }
            }
            print_paragraph(paragraph, p.sent_count, word_counts);
            
            for (int i = 0; i < p.sent_count; i++) {
                free(paragraph[i]);
            }
            free(paragraph);
            free(word_counts);
        }

        printf("\n");
    }
    
    free(text);
    return 0;
}