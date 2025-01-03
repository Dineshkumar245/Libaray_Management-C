#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100 
#define MAX_USERS 50  

struct Book {
    int id; 
    char title[100]; 
    char author[100]; 
    int isIssued; 
};

struct User {
    int id; 
    char name[100]; 
    int borrowedBookId; 
};

struct Book library[MAX_BOOKS]; 
struct User users[MAX_USERS]; 
int bookCount = 0; 
int userCount = 0; 

void addBook() {
    if (bookCount >= MAX_BOOKS) { 
        printf("\nLibrary is full! Cannot add more books.\n");
        return;
    }

    struct Book newBook;
    printf("\nEnter Book ID: "); 
    scanf("%d", &newBook.id);
    getchar();
    printf("Enter Book Title: ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    strtok(newBook.title, "\n"); 
    printf("Enter Author Name: "); 
    fgets(newBook.author, sizeof(newBook.author), stdin);
    strtok(newBook.author, "\n"); 
    newBook.isIssued = 0;

    library[bookCount++] = newBook;
    printf("\nBook added successfully!\n");
}


void addUser() {
    if (userCount >= MAX_USERS) { 
        printf("\nMaximum users reached! Cannot add more users.\n");
        return;
    }

    struct User newUser;
    printf("\nEnter User ID: "); 
    scanf("%d", &newUser.id);
    getchar();
    printf("Enter User Name: ");
    fgets(newUser.name, sizeof(newUser.name), stdin);
    strtok(newUser.name, "\n");
    newUser.borrowedBookId = -1;

    users[userCount++] = newUser;
    printf("\nUser added successfully!\n");
}

void viewBooks() {
    if (bookCount == 0) {
        printf("\nNo books in the library.\n");
        return;
    }

    printf("\n%-10s %-30s %-30s %-10s\n", "Book ID", "Title", "Author", "Status");
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < bookCount; i++) { 
        printf("%-10d %-30s %-30s %-10s\n", 
               library[i].id, 
               library[i].title, 
               library[i].author, 
               library[i].isIssued ? "Issued" : "Available");
    }
}

void viewUsers() {
    if (userCount == 0) { 
        printf("\nNo users in the system.\n");
        return;
    }

    printf("\n%-10s %-30s %-20s\n", "User ID", "Name", "Borrowed Book ID");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < userCount; i++) {
        printf("%-10d %-30s %-20d\n", 
               users[i].id, 
               users[i].name, 
               users[i].borrowedBookId);
    }
}

void issueBook() {
    int userId, bookId;
    printf("\nEnter User ID: ");
    scanf("%d", &userId);
    printf("Enter Book ID: ");
    scanf("%d", &bookId);

    int userIndex = -1, bookIndex = -1;
    for (int i = 0; i < userCount; i++) { 
        if (users[i].id == userId) {
            userIndex = i;
            break;
        }
    }
    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == bookId) {
            bookIndex = i;
            break;
        }
    }

    if (userIndex == -1) { 
        printf("\nUser not found.\n");
        return;
    }
    if (bookIndex == -1) { 
        printf("\nBook not found.\n");
        return;
    }
    if (library[bookIndex].isIssued) { 
        printf("\nBook is already issued.\n");
        return;
    }
    if (users[userIndex].borrowedBookId != -1) { 
        printf("\nUser already has a book issued.\n");
        return;
    }
    if (users[userIndex].borrowedBookId == bookId) {
        printf("\nUser already has this book issued.\n");
        return; // Add this check to prevent borrowing the same book again.
    }

    library[bookIndex].isIssued = 1; 
    users[userIndex].borrowedBookId = bookId; 
    printf("\nBook issued successfully!\n");
}

void returnBook() {
    int userId;
    printf("\nEnter User ID: "); 
    scanf("%d", &userId);

    int userIndex = -1;
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == userId) {
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1) { 
        printf("\nUser not found.\n");
        return;
    }
    if (users[userIndex].borrowedBookId == -1) { 
        printf("\nUser has no borrowed book.\n");
        return;
    }

    int bookId = users[userIndex].borrowedBookId;
    for (int i = 0; i < bookCount; i++) { 
        if (library[i].id == bookId) {
            library[i].isIssued = 0;
            break;
        }
    }
    users[userIndex].borrowedBookId = -1;
    printf("\nBook returned successfully!\n");
}

void searchBook() {
    char keyword[100];
    printf("\nEnter title or author to search: "); 
    getchar();
    fgets(keyword, sizeof(keyword), stdin);
    strtok(keyword, "\n");

    printf("\n%-10s %-30s %-30s %-10s\n", "Book ID", "Title", "Author", "Status");
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < bookCount; i++) { 
        if (strstr(library[i].title, keyword) || strstr(library[i].author, keyword)) {
            printf("%-10d %-30s %-30s %-10s\n", 
                   library[i].id, 
                   library[i].title, 
                   library[i].author, 
                   library[i].isIssued ? "Issued" : "Available");
        }
    }
}

int main() {
    int choice;

    do {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n"); 
        printf("2. View All Books\n");
        printf("3. Add User\n"); 
        printf("4. View All Users\n"); 
        printf("5. Issue Book\n"); 
        printf("6. Return Book\n"); 
        printf("7. Search Book\n"); 
        printf("8. Exit\n"); 
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break; 
            case 2: viewBooks(); break; 
            case 3: addUser(); break;
            case 4: viewUsers(); break;
            case 5: issueBook(); break; 
            case 6: returnBook(); break; 
            case 7: searchBook(); break; 
            case 8: printf("\nExiting...\n"); break; 
            default: printf("\nInvalid choice. Try again.\n"); 
        }
    } while (choice != 8); 

    return 0;
}
