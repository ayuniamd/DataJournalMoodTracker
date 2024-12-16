#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date {
    int day;
    int month;
    int year;
};

// Struct for Journal Entry registration
struct journalEntry {
    char entryTitle[100];
    char thought[20];
    char summary[100];
    char remarks[100];
    struct Date date;
    struct journalEntry* next;
};

// Struct for Mood Track Entry registration
struct moodTrackEntry {
    char moodType[10];
    char remarks[100];
    struct Date date;
    struct moodTrackEntry* next;
};

// Function for main menu
void displayMenu() {
    printf("============================================\n");
    printf("\n   Daily Journal and Mood Tracker System\n");
    printf("\n============================================\n");
    printf("1. Enter Journal\n");
    printf("2. Enter Mood Tracker\n");
    printf("3. Exit\n");
    printf("\n======================================\n");
}

// Function for edit menu
void displayEditMenu() {
    printf("\n============================================\n");
    printf("\n           Edit Journal System\n");
    printf("\n============================================\n");
    printf("1. Add Journal Entry\n");
    printf("2. Update Journal Entry\n");
    printf("3. Delete Journal Entry\n");
    printf("4. Search Journal Entry by Title\n");
    printf("5. Sort Journal Entry\n");
    printf("6. Display all Journal Entries\n");
    printf("7. Back to Main Menu\n");
    printf("\n======================================\n");
}

// Function for mood tracking menu
void displayMoodMenu() {
    printf("\n============================================\n");
    printf("\n           Mood Tracking System\n");
    printf("\n============================================\n");
    printf("1. Add Mood Entry\n"); //push
    printf("2. Delete Mood Entry\n"); //pop
    printf("3. Update Mood Track Entry\n");
    printf("4. Delete Mood Track Entry\n");
    printf("5. Display all Mood Track Entries\n");
    printf("6. Back to Main Menu\n");
    printf("\n======================================\n");
}

// Function to display moods
void displayMoodOptions() {
    printf("\nMood Options:\n");
    printf("1. Extremely Happy\n");
    printf("2. Happy\n");
    printf("3. Somewhat Happy\n");
    printf("4. Neutral\n");
    printf("5. Somewhat Sad\n");
    printf("6. Sad\n");
    printf("7. Very Sad\n");

}

// Function to clear the input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to create a new journal entry
struct journalEntry* createJournalEntry() {
    struct journalEntry* newJournal = (struct journalEntry*)malloc(sizeof(struct journalEntry));
    if (!newJournal) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    printf("\nJournal Entry Title: ");
    fgets(newJournal->entryTitle, sizeof(newJournal->entryTitle), stdin);
    newJournal->entryTitle[strcspn(newJournal->entryTitle, "\n")] = '\0';

    printf("\nDate (DD MM YYYY): ");
    scanf("%d %d %d", &newJournal->date.day, &newJournal->date.month, &newJournal->date.year);
    clearInputBuffer();

    printf("\nDaily thoughts: ");
    fgets(newJournal->thought, sizeof(newJournal->thought), stdin);
    newJournal->thought[strcspn(newJournal->thought, "\n")] = '\0';

    printf("\nSummary of the day: ");
    fgets(newJournal->summary, sizeof(newJournal->summary), stdin);
    newJournal->summary[strcspn(newJournal->summary, "\n")] = '\0';

    printf("\nRemarks: ");
    fgets(newJournal->remarks, sizeof(newJournal->remarks), stdin);
    newJournal->remarks[strcspn(newJournal->remarks, "\n")] = '\0';

    newJournal->next = NULL;
    return newJournal;
}

// Function to create a new mood track entry
struct moodTrackEntry* createMoodTrackEntry() {
    struct moodTrackEntry* newMoodTrack = (struct moodTrackEntry*)malloc(sizeof(struct moodTrackEntry));
    if (!newMoodTrack) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    printf("\nDate (DD MM YYYY): ");
    scanf("%d %d %d", &newMoodTrack->date.day, &newMoodTrack->date.month, &newMoodTrack->date.year);
    clearInputBuffer();

    int check = 0;

    while (check == 0) {
        int moodChoice;

        displayMoodOptions();
        printf("\nChoose Mood Option (1-7): ");
        scanf("%d", &moodChoice);
        clearInputBuffer();

        switch (moodChoice) {
            case 1:
                strcpy(newMoodTrack->moodType, "Extremely Happy");
                check = 1;
                break;
            case 2:
                strcpy(newMoodTrack->moodType, "Happy");
                check = 1;
                break;
            case 3:
                strcpy(newMoodTrack->moodType, "Somewhat Happy");
                check = 1;
                break;
            case 4:
                strcpy(newMoodTrack->moodType, "Neutral");
                check = 1;
                break;
            case 5:
                strcpy(newMoodTrack->moodType, "Somewhat Sad");
                check = 1;
                break;
            case 6:
                strcpy(newMoodTrack->moodType, "Sad");
                check = 1;
                break;
            case 7:
                strcpy(newMoodTrack->moodType, "Very Sad");
                check = 1;
                break;
            default:
                printf("Invalid choice. Please choose between 1-7.\n");
                break;
        }
    }

    printf("\nRemarks: ");
    fgets(newMoodTrack->remarks, sizeof(newMoodTrack->remarks), stdin);
    newMoodTrack->remarks[strcspn(newMoodTrack->remarks, "\n")] = '\0';

    newMoodTrack->next = NULL;
    return newMoodTrack;
}

// Function to push a new mood track entry onto the stack
void pushMoodTrackEntry(struct moodTrackEntry** head) {
    struct moodTrackEntry* newMoodTrack = createMoodTrackEntry();
    if (!newMoodTrack) return;

    newMoodTrack->next = *head;
    *head = newMoodTrack;

    printf("\nMood Track Entry added successfully!\n");
}

// Function to pop the top mood track entry from the stack
void popMoodTrackEntry(struct moodTrackEntry** head) {
    if (*head == NULL) {
        printf("\nNo mood entries to pop.\n");
        return;
    }

    struct moodTrackEntry* temp = *head;
    *head = (*head)->next;
    printf("Popped mood entry dated '%02d/%02d/%04d'.\n", temp->date.day, temp->date.month, temp->date.year);
    free(temp);
}

// Function to display all journal entries
void displayAllJournalEntries(struct journalEntry* head) {
    if (head == NULL) {
        printf("\nNo journal entries to display.\n");
        return;
    }

    struct journalEntry* current = head;
    int entryNumber = 1;

    printf("\n\n======================================\n");
    printf("\n\tAll Journal Entries\n");
    printf("\n======================================\n");

    while (current != NULL) {
        printf("Entry %d\n", entryNumber);
        printf("Entry Title       : %s\n", current->entryTitle);
        printf("Date              : %02d/%02d/%04d\n", current->date.day, current->date.month, current->date.year);
        printf("Thought           : %s\n", current->thought);
        printf("Summary of the day: %s\n", current->summary);
        printf("Remarks           : %s\n", current->remarks);
        printf("\n======================================\n");

        current = current->next;
        entryNumber++;
    }
}

// Function to display all mood track entries
void displayAllMoodTrackEntries(struct moodTrackEntry* head) {
    if (head == NULL) {
        printf("\nNo mood track entries to display.\n");
        return;
    }

    struct moodTrackEntry* current = head;
    int entryNumber = 1;

    printf("\n\n======================================\n");
    printf("\n\tAll Mood Track Entries\n");
    printf("\n======================================\n");

    while (current != NULL) {
        printf("Entry %d\n", entryNumber);
        printf("Date              : %02d/%02d/%04d\n", current->date.day, current->date.month, current->date.year);
        printf("Mood Type         : %s\n", current->moodType);
        printf("Remarks           : %s\n", current->remarks);
        printf("\n======================================\n");

        current = current->next;
        entryNumber++;
    }
}

// Function to delete a journal entry by date
void deleteJournalEntryByDate(struct journalEntry** head, int day, int month, int year) {
    if (*head == NULL) {
        printf("\nNo journal entries to delete.\n");
        return;
    }

    struct journalEntry* temp = *head;
    struct journalEntry* prev = NULL;

    while (temp != NULL && (temp->date.day != day || temp->date.month != month || temp->date.year != year)) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("No journal entry found for the given date.\n");
        return;
    }

    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Journal entry for date %02d/%02d/%04d deleted successfully!\n", day, month, year);
}

// Function to delete a mood track entry by date
void deleteMoodTrackEntryByDate(struct moodTrackEntry** head, int day, int month, int year) {
    if (*head == NULL) {
        printf("\nNo mood track entries to delete.\n");
        return;
    }

    struct moodTrackEntry* temp = *head;
    struct moodTrackEntry* prev = NULL;

    while (temp != NULL && (temp->date.day != day || temp->date.month != month || temp->date.year != year)) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("No mood track entry found for the given date.\n");
        return;
    }

    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Mood track entry for date %02d/%02d/%04d deleted successfully!\n", day, month, year);
}

// Function to update a journal entry by title
void updateJournalEntry(struct journalEntry* head) {
    if (head == NULL) {
        printf("\nNo journal entries to update.\n");
        return;
    }

    char title[100];
    printf("Enter the title of the journal entry to update: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    struct journalEntry* current = head;
    while (current != NULL && strcmp(current->entryTitle, title) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("No journal entry found with the title '%s'.\n", title);
        return;
    }

    printf("\nUpdating Journal Entry: %s\n", current->entryTitle);

    printf("\nNew Daily thoughts: ");
    fgets(current->thought, sizeof(current->thought), stdin);
    current->thought[strcspn(current->thought, "\n")] = '\0';


    printf("\nNew Summary of the day: ");
    fgets(current->summary, sizeof(current->summary), stdin);
    current->summary[strcspn(current->summary, "\n")] = '\0';

    printf("\nNew Remarks: ");
    fgets(current->remarks, sizeof(current->remarks), stdin);
    current->remarks[strcspn(current->remarks, "\n")] = '\0';

    printf("Journal entry updated successfully!\n");
}

// Function to update a mood track entry by date
void updateMoodTrackEntry(struct moodTrackEntry* head) {
    if (head == NULL) {
        printf("\nNo mood track entries to update.\n");
        return;
    }

    int day, month, year;
    printf("Enter the date of the mood track entry to update (DD MM YYYY): ");
    scanf("%d %d %d", &day, &month, &year);
    clearInputBuffer();

    struct moodTrackEntry* current = head;
    while (current != NULL && (current->date.day != day || current->date.month != month || current->date.year != year)) {
        current = current->next;
    }

    if (current == NULL) {
        printf("No mood track entry found for the date '%02d/%02d/%04d'.\n", day, month, year);
        return;
    }

    printf("\nUpdating Mood Track Entry for date: %02d/%02d/%04d\n", day, month, year);

    int check = 0;

    while (check == 0) {
        int moodChoice;

        displayMoodOptions();
        printf("\nChoose New Mood Option (1-7): ");
        scanf("%d", &moodChoice);
        clearInputBuffer();

        switch (moodChoice) {
            case 1:
                strcpy(current->moodType, "Extremely Happy");
                check = 1;
                break;
            case 2:
                strcpy(current->moodType, "Happy");
                check = 1;
                break;
            case 3:
                strcpy(current->moodType, "Somewhat Happy");
                check = 1;
                break;
            case 4:
                strcpy(current->moodType, "Neutral");
                check = 1;
                break;
            case 5:
                strcpy(current->moodType, "Somewhat Sad");
                check = 1;
                break;
            case 6:
                strcpy(current->moodType, "Sad");
                check = 1;
                break;
            case 7:
                strcpy(current->moodType, "Very Sad");
                check = 1;
                break;
            default:
                printf("Invalid choice. Please choose between 1-7.\n");
                break;
        }
    }

    printf("\nNew Remarks: ");
    fgets(current->remarks, sizeof(current->remarks), stdin);
    current->remarks[strcspn(current->remarks, "\n")] = '\0';

    printf("Mood track entry updated successfully!\n");
}


// Function to search for a journal entry by title
void searchJournalEntryByTitle(struct journalEntry* head) {
    if (head == NULL) {
        printf("\nNo journal entries to search.\n");
        return;
    }

    char title[100];
    printf("Enter the title of the journal entry to search: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    struct journalEntry* current = head;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->entryTitle, title) == 0) {
            printf("\nJournal Entry Found:\n");
            printf("Entry Title       : %s\n", current->entryTitle);
            printf("Date              : %02d/%02d/%04d\n", current->date.day, current->date.month, current->date.year);
            printf("Thought           : %s\n", current->thought);
            printf("Summary of the day: %s\n", current->summary);
            printf("Remarks           : %s\n", current->remarks);
            printf("\n======================================\n");
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No journal entry found with the title '%s'.\n", title);
    }
}

// Function to sort journal entries by date
void sortJournalEntriesByDate(struct journalEntry** head) {
    if (*head == NULL) {
        printf("\nNo journal entries to sort.\n");
        return;
    }

    struct journalEntry* sorted = NULL;
    struct journalEntry* current = *head;

    while (current != NULL) {
        struct journalEntry* next = current->next;

        if (sorted == NULL || (sorted->date.year > current->date.year ||
            (sorted->date.year == current->date.year && sorted->date.month > current->date.month) ||
            (sorted->date.year == current->date.year && sorted->date.month == current->date.month && sorted->date.day > current->date.day))) {
            current->next = sorted;
            sorted = current;
        } else {
            struct journalEntry* temp = sorted;
            while (temp->next != NULL &&
                   (temp->next->date.year < current->date.year ||
                    (temp->next->date.year == current->date.year && temp->next->date.month < current->date.month) ||
                    (temp->next->date.year == current->date.year && temp->next->date.month == current->date.month && temp->next->date.day < current->date.day))) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    *head = sorted;
    printf("Journal entries sorted by date successfully!\n");
}

// Function to sort journal entries by title
void sortJournalEntriesByTitle(struct journalEntry** head) {
    if (*head == NULL) {
        printf("\nNo journal entries to sort.\n");
        return;
    }

    struct journalEntry* sorted = NULL;
    struct journalEntry* current = *head;

    while (current != NULL) {
        struct journalEntry* next = current->next;

        if (sorted == NULL || strcmp(sorted->entryTitle, current->entryTitle) > 0) {
            current->next = sorted;
            sorted = current;
        } else {
            struct journalEntry* temp = sorted;
            while (temp->next != NULL && strcmp(temp->next->entryTitle, current->entryTitle) < 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    *head = sorted;
    printf("Journal entries sorted by title successfully!\n");
}

int main() {
    struct journalEntry* journalHead = NULL;
    struct moodTrackEntry* moodTrackHead = NULL;

    int mainChoice;

    do {
        displayMenu();
        printf("\nChoose an option (1-3): ");
        scanf("%d", &mainChoice);
        clearInputBuffer();

        switch (mainChoice) {
            case 1:
                {
                    int editChoice;
                    do {
                        displayEditMenu();
                        printf("\nChoose an option (1-7): ");
                        scanf("%d", &editChoice);
                        clearInputBuffer();

                        switch (editChoice) {
                            case 1:
                                {
                                    struct journalEntry* newJournal = createJournalEntry();
                                    if (!newJournal) break;

                                    newJournal->next = journalHead;
                                    journalHead = newJournal;
                                    printf("\nJournal entry added successfully!\n");
                                }
                                break;

                            case 2:
                                updateJournalEntry(journalHead);
                                break;

                            case 3:
                                {
                                    int day, month, year;
                                    printf("Enter the date of the journal entry to delete (DD MM YYYY): ");
                                    scanf("%d %d %d", &day, &month, &year);
                                    clearInputBuffer();
                                    deleteJournalEntryByDate(&journalHead, day, month, year);
                                }
                                break;

                            case 4:
                                searchJournalEntryByTitle(journalHead);
                                break;

                            case 5:
                                {
                                    int sortChoice;
                                    printf("\n1. Sort by Date\n2. Sort by Title\nChoose an option (1-2): ");
                                    scanf("%d", &sortChoice);
                                    clearInputBuffer();

                                    if (sortChoice == 1) {
                                        sortJournalEntriesByDate(&journalHead);
                                    } else if (sortChoice == 2) {
                                        sortJournalEntriesByTitle(&journalHead);
                                    } else {
                                        printf("Invalid choice. Please choose between 1-2.\n");
                                    }
                                }
                                break;

                            case 6:
                                displayAllJournalEntries(journalHead);
                                break;

                            case 7:
                                printf("Returning to Main Menu...\n");
                                break;

                            default:
                                printf("Invalid choice. Please choose between 1-7.\n");
                                break;
                        }
                    } while (editChoice != 7);
                }
                break;

            case 2:
                {
                    int moodChoice;
                    do {
                        displayMoodMenu();
                        printf("\nChoose an option (1-6): ");
                        scanf("%d", &moodChoice);
                        clearInputBuffer();

                        switch (moodChoice) {
                            case 1:
                                pushMoodTrackEntry(&moodTrackHead);
                                break;

                            case 2:
                                popMoodTrackEntry(&moodTrackHead);
                                break;

                            case 3:
                                updateMoodTrackEntry(moodTrackHead);
                                break;

                            case 4:
                                {
                                    int day, month, year;
                                    printf("Enter the date of the mood track entry to delete (DD MM YYYY): ");
                                    scanf("%d %d %d", &day, &month, &year);
                                    clearInputBuffer();
                                    deleteMoodTrackEntryByDate(&moodTrackHead, day, month, year);
                                }
                                break;

                            case 5:
                                displayAllMoodTrackEntries(moodTrackHead);
                                break;

                            case 6:
                                printf("Returning to Main Menu...\n");
                                break;

                            default:
                                printf("Invalid choice. Please choose between 1-6.\n");
                                break;
                        }
                    } while (moodChoice != 6);
                }
                break;

            case 3:
                printf("Exiting the program...\n");
                break;

            default:
                printf("Invalid choice. Please choose between 1-3.\n");
                break;
        }
    } while (mainChoice != 3);

    return 0;
}
