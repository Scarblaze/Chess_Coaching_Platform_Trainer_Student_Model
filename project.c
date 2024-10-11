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

struct progress{
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

// Function to Initialize the student DB

void Initialize_student_DB(struct student_attribute students[], int size)
{
    for(int i=0; i<size; i++)
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
        for(int j = 0; j < 12; j++)
        {
            students[i].data.ratings[j] = 0;
        }
    }
}

// Fucntion to insert update student records

int insert_update_student(struct student_attribute student_DB[], int size, char stud_name[], float stud_elo_rating, char goals[], char slot[], char style[], int assigned_train_id, char performance[], struct progress info)
{

    // Check if corresponding data exists for student

    int status = SUCCESS;
    int i=0,j,found=0,free_loc;
    while(i<size && !found)
    {
        if((strcmp(student_DB[i].student_name, stud_name) == 0) && (student_DB[i].student_elo_rating == stud_elo_rating))
        {
            found = 1;
        }
        else
        {
            i++;
        }
    }

    // Update student data

    if(found)
    {
        // strcpy(student_DB[i].student_name, stud_name);
        // student_DB[i].student_elo_rating = stud_elo_rating;

        //Check once!
    }
    else
    {
        j = 0, free_loc = 0;
        while(j<size && free_loc == 0)
        {
            if(student_DB[j].student_name == '\0' && student_DB[j].student_elo_rating == 0)
            {
                free_loc = 1;
            }
            else
            {
                j++;
            }
        }

        // If free location found insert the student data

        if(free_loc)
        {
            strcpy(student_DB[j].student_name, stud_name);
            student_DB[j].student_elo_rating =  stud_elo_rating;
            strcpy(student_DB[j].learn_goals, goals);
            strcpy(student_DB[j].time_slot, slot);
            strcpy(student_DB[j].preferred_coaching_style, style);
            student_DB[j].assigned_trainer_id = assigned_train_id;
            strcpy(student_DB[j].performance_data, performance);
            student_DB[j].data.games_won = info.games_won;
            student_DB[j].data.puzzles_solved = info.puzzles_solved;
            for(int k = 0; k < 12; k++)
            {
                student_DB[j].data.ratings[k] = info.ratings[k];
            }
        }

        else
        {
            status = FAILURE;
        }
    }
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

    // Intializing DB vales to zero.

    Initialize_student_DB(student_DB, STUD_DB_SIZE);

    // Asking number of student records and taking input.

    printf("How many student records you want to enter: ");
    scanf("%d",&stud_records);

    for(int i=0; i < stud_records; i++)
    {
        scanf("%s",stud_name);
        scanf("%f",&stud_elo_rating);
        scanf("%s",goals);
        scanf("%s",slot);
        scanf("%s",style);
        scanf("%s",assigned_train_id);
        scanf("%s",performance);
        scanf("%s",&info.games_won);
        scanf("%s",&info.puzzles_solved);
        for(int j=0; j<12; j++)
        {
            scanf("%s",&info.ratings[j]);
        }
        
        int status = insert_update_student(student_DB, STUD_DB_SIZE, stud_name, stud_elo_rating, goals, slot, style, assigned_train_id, performance, info);
    }
}
