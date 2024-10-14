#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_LEN 100
#define GOALS 50
#define SLOT 25
#define STYLE 25
#define PERFORMANCE 50
#define STUD_DB_SIZE 500
#define SUCCESS 1
#define FAILURE 0
#define TRAIN_DB_SIZE 250

struct progress
{
    int games_won;
    int puzzles_solved;
    int ratings[12];
};

struct student_attribute
{
    char student_name[NAME_LEN];
    float student_elo_rating;
    char learn_goals[GOALS];
    char time_slot[SLOT];
    char preferred_coaching_style[STYLE];
    int assigned_trainer_id;
    char performance_data[PERFORMANCE];
    struct progress data;
};

struct trainer_attribute
{
    int trainer_id;
    char trainer_name[NAME_LEN];
    float trainer_elo_rating;
    char coaching_style[STYLE];
    char free_time_slot[SLOT];
    int experience_level;
    float qualify_elo;
    int max_students;
};

// Function to initialize the trainer DB

void Initialize_trainer_DB(struct trainer_attribute trainers[], int size_trainers)
{
    for (int i = 0; i < size_trainers; i++)
    {
        trainers[i].trainer_id = 0;
        trainers[i].trainer_name[0] = '\0';
        trainers[i].trainer_elo_rating = 0.0;
        trainers[i].coaching_style[0] = '\0';
        trainers[i].free_time_slot[0] = '\0';
        trainers[i].experience_level = 0;
        trainers[i].qualify_elo = 0.0;
        trainers[i].max_students = 0;
    }
}

// Function to Initialize the student DB

void Initialize_student_DB(struct student_attribute students[], int size)
{
    for (int i = 0; i < size; i++)
    {
        students[i].student_name[0] = '\0';
        students[i].student_elo_rating = 0;
        students[i].learn_goals[0] = '\0';
        students[i].time_slot[0] = '\0';
        students[i].preferred_coaching_style[0] = '\0';
        students[i].assigned_trainer_id = 0;
        students[i].performance_data[0] = '\0';

        // check how to handle struct within struct!

        students[i].data.games_won = 0;
        students[i].data.puzzles_solved = 0;
        for (int j = 0; j < 12; j++)
        {
            students[i].data.ratings[j] = 0;
        }
    }
}

// Function to insert update trainer records

int insert_update_trainer(struct trainer_attribute trainer_DB[], int size, int train_id, char train_name[], float train_elo_rating, char coach_style[], char slot[], int experience, float qualify, int max)
{

    // Check if corresponding data exists for trainer

    int status = SUCCESS;
    int i = 0, j, found = 0, free_loc;
    while (i < size && !found)
    {
        if ((trainer_DB[i].trainer_id == train_id))
        {
            found = 1;
        }
        else
        {
            i++;
        }
    }

    // Update trainer data

    if (found)
    {
        trainer_DB[i].trainer_elo_rating = train_elo_rating;
        strcpy(trainer_DB[i].coaching_style, coach_style);
        strcpy(trainer_DB[i].free_time_slot, slot);
        trainer_DB[i].experience_level = experience;
        trainer_DB[i].qualify_elo = qualify;
        trainer_DB[i].max_students = max;
    }
    else
    {
        j = 0, free_loc = 0;
        while (j < size && free_loc == 0)
        {
            if (trainer_DB[j].trainer_name == '\0' && trainer_DB[j].trainer_id == 0)
            {
                free_loc = 1;
            }
            else
            {
                j++;
            }
        }

        // If free location found insert the trainer data

        if (free_loc)
        {
            trainer_DB[i].trainer_id = train_id;
            strcpy(trainer_DB[i].trainer_name, train_name);
            trainer_DB[i].trainer_elo_rating = train_elo_rating;
            strcpy(trainer_DB[i].coaching_style, coach_style);
            strcpy(trainer_DB[i].free_time_slot, slot);
            trainer_DB[i].experience_level = experience;
            trainer_DB[i].qualify_elo = qualify;
            trainer_DB[i].max_students = max;
        }

        else
        {
            status = FAILURE;
        }
    }
    return status;
}

// Fucntion to insert update student records

int insert_update_student(struct student_attribute student_DB[], int size, char stud_name[], float stud_elo_rating, char goals[], char slot[], char style[], int assigned_train_id, char performance[], struct progress info)
{

    // Check if corresponding data exists for student

    int status = SUCCESS;
    int i = 0, j, found = 0, free_loc;
    while (i < size && !found)
    {
        if ((strcmp(student_DB[i].student_name, stud_name) == 0) && (student_DB[i].student_elo_rating == stud_elo_rating))
        {
            found = 1;
        }
        else
        {
            i++;
        }
    }

    // Update student data

    if (found)
    {
        // strcpy(student_DB[i].student_name, stud_name);
        // student_DB[i].student_elo_rating = stud_elo_rating;

        // Check once!
    }
    else
    {
        j = 0, free_loc = 0;
        while (j < size && free_loc == 0)
        {
            if (student_DB[j].student_name == '\0' && student_DB[j].student_elo_rating == 0)
            {
                free_loc = 1;
            }
            else
            {
                j++;
            }
        }

        // If free location found insert the student data

        if (free_loc)
        {
            strcpy(student_DB[j].student_name, stud_name);
            student_DB[j].student_elo_rating = stud_elo_rating;
            strcpy(student_DB[j].learn_goals, goals);
            strcpy(student_DB[j].time_slot, slot);
            strcpy(student_DB[j].preferred_coaching_style, style);
            student_DB[j].assigned_trainer_id = assigned_train_id;
            strcpy(student_DB[j].performance_data, performance);
            student_DB[j].data.games_won = info.games_won;
            student_DB[j].data.puzzles_solved = info.puzzles_solved;
            for (int k = 0; k < 12; k++)
            {
                student_DB[j].data.ratings[k] = info.ratings[k];
            }
        }
        else
        {
            status = FAILURE;
        }
    }
    return status;
}

// Deleting student record function

int delete_student_record(struct student_attribute student_DB[], int size, char stud_name[], float stud_elo_rating)
{
    int status = SUCCESS;
    int i = 0, found = 0;
    while (i < size && !found)
    {
        if ((strcmp(student_DB[i].student_name, stud_name)) == 0 && (student_DB[i].student_elo_rating == stud_elo_rating))
        {
            found = 1;
        }
        else
        {
            i++;
        }
    }
    if (found)
    {
        student_DB[i].student_name[0] = '\0';
        student_DB[i].student_elo_rating = 0;
        student_DB[i].learn_goals[0] = '\0';
        student_DB[i].time_slot[0] = '\0';
        student_DB[i].preferred_coaching_style[0] = '\0';
        student_DB[i].assigned_trainer_id = 0;
        student_DB[i].performance_data[0] = '\0';
        student_DB[i].data.games_won = 0;
        student_DB[i].data.puzzles_solved = 0;
        for (int j = 0; j < 12; j++)
        {
            student_DB[i].data.ratings[j] = 0;
        }
    }
    else
    {
        status = FAILURE;
    }
    return status;
}

// Delete trainer record

int delete_trainer_record(struct trainer_attribute trainer_DB[], int size, char train_name[], int train_id)
{
    int status = SUCCESS;
    int i = 0, found = 0;
    while (i < size && !found)
    {
        if (trainer_DB[i].trainer_id == train_id)
        {
            found = 1;
        }
        else
        {
            i++;
        }
    }

    if (found)
    {
        trainer_DB[i].trainer_id = 0;
        trainer_DB[i].trainer_name[0] = '\0';
        trainer_DB[i].trainer_elo_rating = 0.0;
        trainer_DB[i].coaching_style[0] = '\0';
        trainer_DB[i].free_time_slot[0] = '\0';
        trainer_DB[i].experience_level = 0;
        trainer_DB[i].qualify_elo = 0.0;
        trainer_DB[i].max_students = 0;
    }
    else
    {
        status = FAILURE;
    }
    return status;
}

// Function to sort students based on elo_rating

void sort_students_elo_rating(struct student_attribute student_DB[], struct student_attribute temp[], int size)
{
    merge_sort(student_DB, temp, 0, size - 1);
}

// Merge Sort Function for student_Database

void merge_self(struct student_attribute student_DB[], struct student_attribute temp[], int low, int mid, int high)
{
    int i, j, k;
    i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high)
    {
        if (student_DB[i].student_elo_rating == student_DB[j].student_elo_rating)
        {
            if (student_DB[i].data.games_won > student_DB[j].data.games_won)
            {
                temp[k] = student_DB[i];
                k++;
                i++;
            }
            else
            {
                temp[k] = student_DB[j];
                j++;
                k++;
            }
        }
        else
        {
            if (student_DB[i].student_elo_rating > student_DB[j].student_elo_rating)
            {
                temp[k] = student_DB[i];
                i++;
                k++;
            }
            else
            {
                temp[k] = student_DB[j];
                j++;
                k++;
            }
        }

        while (i <= mid)
        {
            temp[k] = student_DB[i];
            i++;
            k++;
        }

        while (j <= high)
        {
            temp[k] = student_DB[j];
            j++;
            k++;
        }

        i = low;
        while (i <= high)
        {
            student_DB[i] = temp[i];
            i++;
        }
    }
}

void merge_sort(struct student_attribute student_DB[], struct student_attribute temp[], int low, int high)
{
    int mid;
    if (low < high)
    {
        mid = low + (high - low) / 2;
        merge_sort(student_DB, temp, low, mid);
        merge_sort(student_DB, temp, mid + 1, high);
        merge_self(student_DB, temp, low, mid, high);
    }
}

// Students Sort function for decreasing gains

void mergeSelf_decreasing_gains(struct student_attribute student_DB[], int l, int m, int n, struct student_attribute temp[])
{
    int i, j, k;
    i = l;
    j = m + 1;
    k = l;

    while ((i <= m) && (j <= n))
    {
        if ((student_DB[i].data.ratings[11] - student_DB[i].data.ratings[0]) > (student_DB[j].data.ratings[11] - student_DB[j].data.ratings[0]))
        {
            temp[k++] = student_DB[i++];
        }
        else
        {
            temp[k++] = student_DB[j++];
        }
    }

    if (i <= m)
    {
        while (i <= m)
        {
            temp[k++] = student_DB[i++];
        }
    }
    else
    {
        while (j <= n)
        {
            temp[k++] = student_DB[j++];
        }
    }

    for (i = l; i <= n; i++)
    {
        student_DB[i] = temp[i];
    }
}

void mergeSort_decreasing_gains(struct student_attribute student_DB[], struct student_attribute temp[], int lo, int hi)
{
    int mid;
    if (lo < hi)
    {
        mid = (lo + hi) / 2;
        mergeSort_decreasing_gains(student_DB, temp, lo, mid);
        mergeSort_decreasing_gains(student_DB, temp, mid + 1, hi);
        mergeSelf_decreasing_gains(student_DB, lo, mid, hi, temp);
    }
}

int successive_increase(struct student_attribute student_DB[], int stud_records, struct student_attribute list[])
{

    int cnt = 0;
    int flag = 0;
    for (int i = 0; i < stud_records; i++)
    {
        for (int j = 1; j < 12 && flag == 0; i++)
        {
            if (student_DB[i].data.ratings[j] < student_DB[i].data.ratings[j - 1])
            {
                flag = 1;
            }
        }
        if (flag == 0)
        {
            cnt++;

            // Check strcpy order is reverse !!!

            strcpy(student_DB[i].student_name, list[i].student_name);
            student_DB[i].student_elo_rating = list[i].student_elo_rating;
            strcpy(student_DB[i].learn_goals, list[i].learn_goals);
            strcpy(student_DB[i].time_slot, list[i].time_slot);
            strcpy(student_DB[i].preferred_coaching_style, list[i].preferred_coaching_style);
            student_DB[i].assigned_trainer_id = list[i].assigned_trainer_id;
            strcpy(student_DB[i].performance_data, list[i].performance_data);
        }
    }
    return cnt;
}

void main()
{
    // student info variables

    char stud_name[NAME_LEN];
    float stud_elo_rating;
    char goals[GOALS];
    char slot[SLOT];
    char style[STYLE];
    int assigned_train_id, stud_records;
    char performance[PERFORMANCE];
    struct progress info;
    int status;

    struct student_attribute student_DB[STUD_DB_SIZE];
    int status1, status2;

    // trainer info variables
    int train_id;
    char train_name[NAME_LEN];
    float train_elo_rating;
    char coach_style[STYLE];
    char train_slot[SLOT];
    int experience;
    float qualify;
    int max, train_records, status3, status4;
    struct trainer_attribute trainer_DB[TRAIN_DB_SIZE];

    // Intializing DB vales to zero.

    Initialize_student_DB(student_DB, STUD_DB_SIZE);
    Initialize_trainer_DB(trainer_DB, TRAIN_DB_SIZE);

    // Asking number of student records and taking input.

    printf("How many student records you want to enter: ");
    scanf("%d", &stud_records);

    for (int i = 0; i < stud_records; i++)
    {
        scanf("%s", stud_name);
        scanf("%f", &stud_elo_rating);
        scanf("%s", goals);
        scanf("%s", slot);
        scanf("%s", style);
        scanf("%s", assigned_train_id);
        scanf("%s", performance);
        scanf("%s", &info.games_won);
        scanf("%s", &info.puzzles_solved);
        for (int j = 0; j < 12; j++)
        {
            scanf("%s", &info.ratings[j]);
        }

        status1 = insert_update_student(student_DB, STUD_DB_SIZE, stud_name, stud_elo_rating, goals, slot, style, assigned_train_id, performance, info);

        if (!status1)
        {
            printf("Database overload! Come next time\n");
        }
        else
        {
            printf("Student data updated successfully\n");
        }
    }

    printf("How many trainer records do you want to enter? ");
    scanf("%d", &train_records);

    for (int i = 0; i < train_records; i++)
    {
        scanf("%d", train_id);
        scanf("%s", train_name);
        scanf("%f", train_elo_rating);
        scanf("%s", coach_style);
        scanf("%f", train_slot);
        scanf("%d", experience);
        scanf("%f", qualify);
        scanf("%d", max);

        status3 = insert_update_trainer(trainer_DB, TRAIN_DB_SIZE, train_id, train_name, train_elo_rating, coach_style, train_slot, experience, qualify, max);

        if (!status3)
        {
            printf("Database is full! Apply next time\n");
        }
        else
        {
            printf("Trainer data updated successfully\n");
        }
    }

    // To delete a student record
    int flag;
    printf("Do you want to delete any student: enter 1 for YES and 0 for NO");
    scanf("%d", &flag);

    if (flag)
    {
        printf("Enter the student name to be deleted; ");
        scanf("%s", &stud_name);
        printf("Enter the elo rating of student: ");
        scanf("%f", &stud_elo_rating);
        int status2 = delete_student_record(student_DB, stud_records, stud_name, stud_elo_rating);

        if (status2)
        {
            printf("Student Record deleted successfully!\n");
        }
        else
        {
            printf("No student record of given name exists!\n");
        }
    }

    // To delete a trainer record
    int temp;
    printf("Do you want to delete a trainer record?: enter 1 for yes and 0 for No ");
    scanf("%d", &temp);

    if (temp)
    {
        printf("Enter trainer name to be deleted: ");
        scanf("%s", &train_name);
        printf("enter trainer ID: ");
        scanf("%d", train_id);

        status4 = delete_trainer_record(trainer_DB, train_records, train_name, train_id);

        if (status4)
        {
            printf("Trainer record deleted successfully\n");
        }
        else
        {
            printf("No trainer record found\n");
        }
    }

    // Ensure that stud_records is updated accoring to insert and delete functions.

    // Function call to sort student based on elo_rating.

    struct student_attribute temp[stud_records];
    sort_students_elo_rating(student_DB, stud_records);

    // answer to question 12

    struct student_attribute list[stud_records];

    Initialize_student_DB(list, stud_records);

    int size_succesive = successive_increase(student_DB, stud_records, list);


    // same temp used, check once !!

    struct student_attribute temp[stud_records];

    mergeSort_decreasing_gains(list, temp, 0, size_succesive - 1);
}
