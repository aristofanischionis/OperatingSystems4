#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "Headerfiles/tree.h"
#include "Headerfiles/functions.h"
#include "Headerfiles/list.h"
#include "Headerfiles/traverse.h"
#include "Headerfiles/inotifyCode.h"

int main(int argc, char const *argv[]) {

    if(argc < 3){
        perror("Not enough arguments provided\n");
    	exit(EXIT_FAILURE);
    }

    char *sourceFilename = malloc(strlen(argv[1])+1);
    strcpy(sourceFilename, argv[1]);
    char *backupFilename = malloc(strlen(argv[2])+1);
    strcpy(backupFilename, argv[2]);

    Data sourceData, backupData;
    strcpy(sourceData.name, sourceFilename);
    strcpy(backupData.name, backupFilename);
    strcpy(sourceData.path, sourceFilename);
    strcpy(backupData.path, backupFilename);

    List *sourceINodes = initializeList();
    List *backupINodes = initializeList();

    Tree *sourceTree = initializeTree(sourceData);
    Tree *backupTree = initializeTree(backupData);

    // make backup folder if it doesn't exist
    makeBackup(sourceFilename, backupFilename);
    // make copies of filenames so that they don't change when passed in functions
    char *sourceByValue = malloc(strlen(sourceFilename)+1);
    strcpy(sourceByValue, sourceFilename);
    char *backupByValue = malloc(strlen(backupFilename)+1);
    strcpy(backupByValue, backupFilename);
    readDirectory(sourceByValue, &sourceINodes, sourceTree->root);
    readDirectory(backupByValue, &backupINodes, backupTree->root);
    
    traverseTrees(&sourceTree, &backupTree, &sourceINodes, &backupINodes);

    // Print structures
    printf("\n\nSource Tree:\n");
    printTree(sourceTree);
    printf("\n");
    printf("Backup Tree:\n");
    printTree(backupTree);
    printf("\n");
    printf("Source iNodes:\n");
    printINodes(sourceINodes);
    printf("\n");
    printf("Backup iNodes:\n");
    printINodes(backupINodes);

    inotifyCode(sourceFilename, backupFilename, sourceINodes, backupINodes, &sourceTree, &backupTree);

    // Free allocated memory
    deleteNode(sourceTree, sourceTree->root);
    deleteNode(backupTree, backupTree->root);
    deleteList(&sourceINodes);
    deleteList(&backupINodes);
    free(sourceFilename);
    free(backupFilename);
    free(sourceTree->root);
    free(backupTree->root);
    free(sourceTree);
    free(backupTree);

    return 0;
}
