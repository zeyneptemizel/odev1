
//ZEYNEP TEMİZEL
//1306190045
//21.12.2019
// Development Environment: CODEBLOCK IDE






#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int size(char *);
int createNodeList(char [], char *, int, int);
int isContains(char [], int, char);
int findIndex(char [], int, char);
void findPaths(int **, int , char [], int, char *, int, int);
int findMaxSize(char *);

int main(int argc, char** argv){
	char nodeList[20], *word, from;
	int  N, maxSize, i, j, inputSize, wordSize=0, **pathList, fromIndex, startIndex = 0;

    if (argc == 1){
		printf("please entry a parameter");
		return 0;
	} else if (argc > 2){
		printf("please entry just one parameter");
		return 0;
	}
	inputSize = size(argv[1]);
	maxSize = findMaxSize(argv[1]);
	word = calloc(maxSize,sizeof(char));
	int temp = maxSize;
	printf("\nmax = %d \n", maxSize);
	 while(temp!=0){
        temp = temp/10;
        startIndex ++;
	 }

	N = createNodeList(argv[1], nodeList, inputSize, startIndex);

	pathList = (int**)malloc(N*sizeof(int*));
    for(i=0;i<N;i++)
        pathList[i] = calloc(N,sizeof(int));

	printf("%s", nodeList);
	printf("\nN = %d\n", N);

	i = startIndex;
	while(i<inputSize){
		from = argv[1][i];
		fromIndex = findIndex(nodeList, N, from);
		j = i+1;
		while(j<inputSize && argv[1][j]!='1'){
			pathList[fromIndex][findIndex(nodeList, N, argv[1][j])] = 1;
			j++;
		}
		j++;
		i= j;
	}

	printf("\nPath Matrix \n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%d", pathList[i][j]);
		}
		printf("\n");
	}
	word[0] = nodeList[0];
	wordSize++;
	printf("%s \n", word);
	findPaths(pathList, N, nodeList, maxSize, word, wordSize, 0);
	return 0;
}

int createNodeList(char input[], char *nodeList, int inputSize, int startIndex){
	int N = 0, i;

	for(i = startIndex; i<inputSize+1; i++){
		if( (input[i] != '1') && (!isContains(nodeList, N, input[i])) ){
			nodeList[N] = input[i];
			N++;
		}
	}
	N--;
	return N;
}

int isContains(char nodeList[], int N, char c){
	int i;
	for(i = 0; i<N; i++){
		if(nodeList[i] == c) return 1;
	}
	return 0;
}

int findIndex(char nodeList[], int N, char c){
	int i;
	for(i = 0; i<N; i++){
		if(nodeList[i] == c) return i;
	}
	return -1;
}

void findPaths(int **pathList, int N, char nodeList[], int maxSize, char word[], int wordSize, int index){
	int i , tempWordSize = wordSize;
	char *tempWord = (char*)calloc(maxSize,sizeof(char));
	strcpy(tempWord,word);
	for(i=0;i<N;i++){
        if(i != index){
            if((pathList[index][i]) && (wordSize < maxSize)){
            word[wordSize] = nodeList[i];
            wordSize ++;
            printf("%s\n", word);
			findPaths(pathList, N, nodeList, maxSize, word, wordSize, i);
			strcpy(word, tempWord);
			wordSize = tempWordSize;
            }
        }
	}
}

void resetWord(char *word, int size){
	int i;
	for(i = 0;i<size;i++){
		word[i] = ' ';
	}
}

int findMaxSize(char *ptr){
    int i = 0, value = 0, basamak = 10;
    value = ptr[i] - '0';
    i++;
    while(isdigit(ptr[i])){
        value = value*basamak;
        value += ptr[i] - '0';
        i++;
    }

    return value;
}

int size(char *ptr){
    int offset = 0;
    int count = 0;
    while (*(ptr + offset) != '\0'){
        ++count;
        ++offset;
    }
    return count;
}

