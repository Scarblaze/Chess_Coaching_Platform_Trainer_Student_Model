// Vinit More - BT23CSE083
// Jayesh Patil - BT23CSE078
// Batch - R4

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_LEN 100
#define GOALS 20
#define SLOT 5
#define STYLE 20
#define PERFORMANCE 20
#define STUD_DB_SIZE 100
#define SUCCESS 1
#define FAILURE 0
#define TRAIN_DB_SIZE 30

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
    int time_slot[SLOT];
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
    int free_time_slot[SLOT];
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
        for (int j = 0; j < SLOT; j++)
        {
            trainers[i].free_time_slot[j] = 0;
        }
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
        students[i].student_elo_rating = 0.0;
        students[i].learn_goals[0] = '\0';
        for (int j = 0; j < SLOT; j++)
        {
            students[i].time_slot[j] = 0;
        }
        students[i].preferred_coaching_style[0] = '\0';
        students[i].assigned_trainer_id = 0;
        students[i].performance_data[0] = '\0';
        students[i].data.games_won = 0;
        students[i].data.puzzles_solved = 0;
        for (int j = 0; j < 12; j++)
        {
            students[i].data.ratings[j] = 0;
        }
    }
}

// Function to insert update trainer records

int insert_update_trainer(struct trainer_attribute trainer_DB[], int size, int train_id, char train_name[], float train_elo_rating, char coach_style[], int slot[], int experience, float qualify, int max)
{
    int status = SUCCESS;
    int i = 20, j, found = 0, free_loc;
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

    if (found)
    {
        trainer_DB[i].trainer_elo_rating = train_elo_rating;
        strcpy(trainer_DB[i].coaching_style, coach_style);
        for (int k = 0; k < SLOT; k++)
        {
            trainer_DB[i].free_time_slot[k] = slot[k];
        }
        trainer_DB[i].experience_level = experience;
        trainer_DB[i].qualify_elo = qualify;
        trainer_DB[i].max_students = max;
    }
    else
    {
        j = 20, free_loc = 0;
        while (j < size && free_loc == 0)
        {
            if (trainer_DB[j].trainer_id == 0)
            {
                free_loc = 1;
            }
            else
            {
                j++;
            }
        }

        if (free_loc)
        {
            trainer_DB[j].trainer_id = train_id;
            strcpy(trainer_DB[j].trainer_name, train_name);
            trainer_DB[j].trainer_elo_rating = train_elo_rating;
            strcpy(trainer_DB[j].coaching_style, coach_style);
            for (int k = 0; k < SLOT; k++)
            {
                trainer_DB[j].free_time_slot[k] = slot[k];
            }
            trainer_DB[j].experience_level = experience;
            trainer_DB[j].qualify_elo = qualify;
            trainer_DB[j].max_students = max;
        }
        else
        {
            status = FAILURE;
        }
    }
    return status;
}

// Function to insert update student records

int insert_update_student(struct student_attribute student_DB[], int size, char stud_name[], float stud_elo_rating, char goals[], int slot[], char style[], int assigned_train_id, char performance[], struct progress info)
{

    // Checking if corresponding data exists for student

    int status = SUCCESS;
    int i = 20, j, found = 0, free_loc;
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

    // Update student data if found

    if (found)
    {
        strcpy(student_DB[i].learn_goals, goals);
        for (int k = 0; k < SLOT; k++)
        {
            student_DB[i].time_slot[k] = slot[k];
        }
        strcpy(student_DB[i].preferred_coaching_style, style);
        student_DB[i].assigned_trainer_id = assigned_train_id;
        strcpy(student_DB[i].performance_data, performance);
        student_DB[i].data.games_won = info.games_won;
        student_DB[i].data.puzzles_solved = info.puzzles_solved;
        for (int k = 0; k < 12; k++)
        {
            student_DB[i].data.ratings[k] = info.ratings[k];
        }
    }
    else
    {
        j = 20, free_loc = 0;
        while (j < size && free_loc == 0)
        {
            if (student_DB[j].student_name[0] == '\0' && student_DB[j].student_elo_rating == 0)
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
            for (int k = 0; k < SLOT; k++)
            {
                student_DB[j].time_slot[k] = slot[k];
            }
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
        for (int k = 0; k < SLOT; k++)
        {
            student_DB[i].time_slot[k] = 0;
        }
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

// Delete trainer record function

int delete_trainer_record(struct trainer_attribute trainer_DB[], int size, int train_id)
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
        for (int k = 0; k < SLOT; k++)
        {
            trainer_DB[i].free_time_slot[k] = 0;
        }
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

// Function to sort students based on elo_rating using merge_sort

void merge_self_stud_elo(struct student_attribute student_DB[], struct student_attribute temp[], int low, int mid, int high)
{
    int i = low, j = mid + 1, k = low;

    while (i <= mid && j <= high)
    {
        if (student_DB[i].student_elo_rating == student_DB[j].student_elo_rating)
        {
            if (student_DB[i].data.games_won > student_DB[j].data.games_won)
            {
                temp[k] = student_DB[i];
                i++;
            }
            else
            {
                temp[k] = student_DB[j];
                j++;
            }
        }
        else
        {
            if (student_DB[i].student_elo_rating > student_DB[j].student_elo_rating)
            {
                temp[k] = student_DB[i];
                i++;
            }
            else
            {
                temp[k] = student_DB[j];
                j++;
            }
        }
        k++;
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

    for (i = low; i <= high; i++)
    {
        student_DB[i] = temp[i];
    }
}

void merge_sort_stud_elo(struct student_attribute student_DB[], struct student_attribute temp[], int low, int high)
{
    int mid;
    if (low < high)
    {
        mid = low + (high - low) / 2;
        merge_sort_stud_elo(student_DB, temp, low, mid);
        merge_sort_stud_elo(student_DB, temp, mid + 1, high);
        merge_self_stud_elo(student_DB, temp, low, mid, high);
    }
}

void sort_students_elo_rating(struct student_attribute student_DB[], struct student_attribute temp[], int size)
{
    merge_sort_stud_elo(student_DB, temp, 0, size - 1);
}


// Students Sort function for decreasing gains

void mergeSelf_decreasing_gains(struct student_attribute student_DB[], int l, int m, int n, struct student_attribute temp[])
{
    int i = l, j = m + 1, k = l;

    while (i <= m && j <= n)
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

    while (i <= m)
    {
        temp[k++] = student_DB[i++];
    }

    while (j <= n)
    {
        temp[k++] = student_DB[j++];
    }

    for (i = l; i <= n; i++)
    {
        student_DB[i] = temp[i];
    }
}
void mergeSort_decreasing_gains(struct student_attribute student_DB[], struct student_attribute temp[], int lo, int hi)
{
    if (lo < hi)
    {
        int mid = (lo + hi) / 2;
        mergeSort_decreasing_gains(student_DB, temp, lo, mid);
        mergeSort_decreasing_gains(student_DB, temp, mid + 1, hi);
        mergeSelf_decreasing_gains(student_DB, lo, mid, hi, temp);
    }
}

// Function for checking student elo_rating increases every month or not 

int successive_increase(struct student_attribute student_DB[], int stud_records, struct student_attribute list[])
{
    int cnt = 0;
    int m = 0;
    for (int i = 0; i < stud_records; i++)
    {
        int flag = 0;
        for (int j = 1; j < 12 && flag == 0; j++)
        {
            if (student_DB[i].data.ratings[j] < student_DB[i].data.ratings[j - 1])
            {
                flag = 1;
            }
        }
        if (flag == 0)
        {
            cnt++;
            list[m++] = student_DB[i];
        }
    }
    return cnt;       // returns the number of students for whom elo_rating increases every month
}

// Matching Algorithm Function for assigning trainer to students

void match_pairs(int count[], struct student_attribute students[], struct trainer_attribute trainers[], int stud_records, int train_records)
{
    for (int i = 0; i < train_records; i++)
    {
        count[i] = 0;
    }

    for (int i = 0; i < stud_records; i++)
    {
        int best_match = -1;
        for (int j = 0; j < train_records; j++)
        {
            if (count[j] < trainers[j].max_students)
            {
                int time_match = 0;
                for (int k = 0; k < SLOT && !time_match; k++)
                {
                    for (int m = 0; m < SLOT && !time_match; m++)
                    {
                        if (students[i].time_slot[k] == trainers[j].free_time_slot[m])
                        {
                            time_match = 1;
                        }
                    }
                }
                if (time_match)
                {
                    if (strcmp(students[i].preferred_coaching_style, trainers[j].coaching_style) == 0)
                    {
                        if (students[i].student_elo_rating >= trainers[j].qualify_elo)
                        {
                            best_match = j;
                            break;
                        }
                        else if (best_match == -1 || trainers[j].qualify_elo < trainers[best_match].qualify_elo)
                        {
                            best_match = j;
                        }
                    }
                    else if (best_match == -1)
                    {
                        best_match = j;
                    }
                }
            }
        }
        if (best_match != -1)
        {
            students[i].assigned_trainer_id = trainers[best_match].trainer_id;
            count[best_match]++;
        }
    }
}

// Function to calculate the average elo_rating of students assigned to a trainer

void average_elo(struct trainer_attribute trainer_DB[], struct student_attribute student_DB[], int stud_records, int train_records, float average[])
{
    for (int i = 0; i < train_records; i++)
    {
        float sum = 0;
        int cnt = 0;
        for (int j = 0; j < stud_records; j++)
        {
            if (trainer_DB[i].trainer_id == student_DB[j].assigned_trainer_id)
            {
                sum += student_DB[j].student_elo_rating;
                cnt++;
            }
        }
        if (cnt != 0)
            average[i] = sum / (float)cnt;
        else
            average[i] = 0;
    }
}

// Function to find most popular trainer using merge_sort

void merge_self_popularity(struct trainer_attribute trainer_DB[], int l, int m, int n, struct trainer_attribute temp[], float average[], int count[])
{
    int i = l, j = m + 1, k = l;

    while ((i <= m) && (j <= n))
    {
        if (count[i] > count[j])
        {
            temp[k++] = trainer_DB[i++];
        }
        else if (count[i] == count[j])
        {
            if (average[i] > average[j])
            {
                temp[k++] = trainer_DB[i++];
            }
            else if (average[i] == average[j])
            {

                if (strcmp(trainer_DB[i].trainer_name, trainer_DB[j].trainer_name) < 0)
                {
                    temp[k++] = trainer_DB[i++];
                }
                else
                {
                    temp[k++] = trainer_DB[j++];
                }
            }
            else
            {
                temp[k++] = trainer_DB[j++];
            }
        }
        else
        {
            temp[k++] = trainer_DB[j++];
        }
    }

    while (i <= m)
    {
        temp[k++] = trainer_DB[i++];
    }

    while (j <= n)
    {
        temp[k++] = trainer_DB[j++];
    }

    for (i = l; i <= n; i++)
    {
        trainer_DB[i] = temp[i];
    }
}

void mergeSort_popularity(struct trainer_attribute trainer_DB[], struct trainer_attribute temp[], int lo, int hi, float average[], int count[])
{
    if (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        mergeSort_popularity(trainer_DB, temp, lo, mid, average, count);
        mergeSort_popularity(trainer_DB, temp, mid + 1, hi, average, count);
        merge_self_popularity(trainer_DB, lo, mid, hi, temp, average, count);
    }
}

// Function to find most popular trainer

void most_popular_trainer(struct trainer_attribute trainer_DB[], int train_records, int lo, int hi, float average[], int count[])
{
    struct trainer_attribute temp[train_records];
    mergeSort_popularity(trainer_DB, temp, 0, train_records - 1, average, count);
    printf("Most popular trainer: %s\nTrainer ID: %d\n", trainer_DB[0].trainer_name, trainer_DB[0].trainer_id);
}

// Function to list students assigned to particular trainer

void student_trainer_list(struct student_attribute student_DB[], struct trainer_attribute trainer_DB[], int size_stud, int size_train)
{
    for (int i = 0; i < size_train; i++)
    {
        printf("Students of trainer %s, Trainer ID %d:\n", trainer_DB[i].trainer_name, trainer_DB[i].trainer_id);
        for (int j = 0; j < size_stud; j++)
        {
            if (trainer_DB[i].trainer_id == student_DB[j].assigned_trainer_id)
            {
                printf("%s\n", student_DB[j].student_name);
            }
        }
    }
}

// Function to print Student data

void print_stud(struct student_attribute s[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (s[i].student_name[0] != '\0' && s[i].student_elo_rating != 0)
        {
            printf("Name: %s\n", s[i].student_name);
            printf("ELO: %f\n", s[i].student_elo_rating);
            printf("Learning Goals: %s\n", s[i].learn_goals);
            for (int j = 0; j < SLOT; j++)
            {
                printf("Slot %d: %d\n", j + 1, s[i].time_slot[j]);
            }
            printf("style: %s\n", s[i].preferred_coaching_style);
            printf("trainer_id: %d\n", s[i].assigned_trainer_id);
            printf("performance: %s\n", s[i].performance_data);
            printf("Games Won: %d\n", s[i].data.games_won);
            printf("Puzzles Solved :%d\n", s[i].data.puzzles_solved);
            for (int k = 0; k < 12; k++)
            {
                printf("Ratings %d: %d\n", k + 1, s[i].data.ratings[k]);
            }
            printf("\n");
        }
    }
}

// Function to print trainer data

void print_trainers(struct trainer_attribute t[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (t[i].trainer_id != 0)
        {
            printf("ID: %d\n", t[i].trainer_id);
            printf("Name: %s\n", t[i].trainer_name);
            printf("ELO Rating: %f\n", t[i].trainer_elo_rating);
            printf("Style: %s\n", t[i].coaching_style);
            printf("Free time slots: ");
            for (int j = 0; j < SLOT; j++)
            {
                printf("%d ", t[i].free_time_slot[j]);
            }
            printf("\n");
            printf("Experience: %d\n", t[i].experience_level);
            printf("Qualifying Elo: %f\n", t[i].qualify_elo);
            printf("Max students: %d\n", t[i].max_students);
            printf("\n");
        }
    }
}

// Hardcoded student data

void hardcode1(struct student_attribute record1[])
{

    // 1. Alex
    strcpy(record1[0].student_name, "Alex");
    record1[0].student_elo_rating = 1350.5;
    strcpy(record1[0].learn_goals, "Tactics");
    record1[0].time_slot[0] = 5;
    record1[0].time_slot[1] = 3;
    record1[0].time_slot[2] = 8;
    record1[0].time_slot[3] = 6;
    record1[0].time_slot[4] = 9;
    strcpy(record1[0].preferred_coaching_style, "Aggressive");
    record1[0].assigned_trainer_id = 0;
    strcpy(record1[0].performance_data, "Endgame");
    record1[0].data.games_won = 20;
    record1[0].data.puzzles_solved = 80;
    int alex_student_elo_ratings[] = {1340, 1350, 1360, 1345, 1340, 1355, 1360, 1365, 1370, 1375, 1380, 1390};
    for (int j = 0; j < 12; j++)
        record1[0].data.ratings[j] = alex_student_elo_ratings[j];

    // 2. Sam
    strcpy(record1[1].student_name, "Sam");
    record1[1].student_elo_rating = 1800.0;
    strcpy(record1[1].learn_goals, "Endgame");
    record1[1].time_slot[0] = 7;
    record1[1].time_slot[1] = 9;
    record1[1].time_slot[2] = 2;
    record1[1].time_slot[3] = 5;
    record1[1].time_slot[4] = 4;
    strcpy(record1[1].preferred_coaching_style, "Defensive");
    record1[1].assigned_trainer_id = 0;
    strcpy(record1[1].performance_data, "Opening");
    record1[1].data.games_won = 30;
    record1[1].data.puzzles_solved = 90;
    int sam_student_elo_ratings[] = {1800, 1810, 1820, 1815, 1810, 1825, 1830, 1835, 1840, 1850, 1855, 1860};
    for (int j = 0; j < 12; j++)
        record1[1].data.ratings[j] = sam_student_elo_ratings[j];

    // 3. Chris
    strcpy(record1[2].student_name, "Chris");
    record1[2].student_elo_rating = 1600.0;
    strcpy(record1[2].learn_goals, "Middlegame");
    record1[2].time_slot[0] = 4;
    record1[2].time_slot[1] = 2;
    record1[2].time_slot[2] = 10;
    record1[2].time_slot[3] = 3;
    record1[2].time_slot[4] = 8;
    strcpy(record1[2].preferred_coaching_style, "Positional");
    record1[2].assigned_trainer_id = 0;
    strcpy(record1[2].performance_data, "Transitions");
    record1[2].data.games_won = 25;
    record1[2].data.puzzles_solved = 70;
    int chris_student_elo_ratings[] = {1600, 1610, 1605, 1620, 1615, 1630, 1625, 1640, 1635, 1650, 1645, 1660};
    for (int j = 0; j < 12; j++)
        record1[2].data.ratings[j] = chris_student_elo_ratings[j];

    // 4. Jamie
    strcpy(record1[3].student_name, "Jamie");
    record1[3].student_elo_rating = 1750.5;
    strcpy(record1[3].learn_goals, "Calculation");
    record1[3].time_slot[0] = 6;
    record1[3].time_slot[1] = 8;
    record1[3].time_slot[2] = 4;
    record1[3].time_slot[3] = 10;
    record1[3].time_slot[4] = 1;
    strcpy(record1[3].preferred_coaching_style, "Defensive");
    record1[3].assigned_trainer_id = 0;
    strcpy(record1[3].performance_data, "Tactics");
    record1[3].data.games_won = 35;
    record1[3].data.puzzles_solved = 100;
    int jamie1_student_elo_ratings[] = {1750, 1760, 1770, 1765, 1775, 1780, 1770, 1785, 1790, 1795, 1800, 1810};
    for (int j = 0; j < 12; j++)
        record1[3].data.ratings[j] = jamie1_student_elo_ratings[j];

    // 5. Taylor
    strcpy(record1[4].student_name, "Taylor");
    record1[4].student_elo_rating = 1400.0;
    strcpy(record1[4].learn_goals, "Openings");
    record1[4].time_slot[0] = 3;
    record1[4].time_slot[1] = 10;
    record1[4].time_slot[2] = 5;
    record1[4].time_slot[3] = 7;
    record1[4].time_slot[4] = 9;
    strcpy(record1[4].preferred_coaching_style, "Aggressive");
    record1[4].assigned_trainer_id = 0;
    strcpy(record1[4].performance_data, "Opening Theory");
    record1[4].data.games_won = 15;
    record1[4].data.puzzles_solved = 60;
    int taylor_student_elo_ratings[] = {1400, 1405, 1410, 1420, 1415, 1425, 1430, 1435, 1440, 1445, 1450, 1455};
    for (int j = 0; j < 12; j++)
        record1[4].data.ratings[j] = taylor_student_elo_ratings[j];

    // 6. Jordan
    strcpy(record1[5].student_name, "Jordan");
    record1[5].student_elo_rating = 1650.0;
    strcpy(record1[5].learn_goals, "Defense");
    record1[5].time_slot[0] = 2;
    record1[5].time_slot[1] = 5;
    record1[5].time_slot[2] = 7;
    record1[5].time_slot[3] = 9;
    record1[5].time_slot[4] = 6;
    strcpy(record1[5].preferred_coaching_style, "Defensive");
    record1[5].assigned_trainer_id = 0;
    strcpy(record1[5].performance_data, "Attacking");
    record1[5].data.games_won = 22;
    record1[5].data.puzzles_solved = 75;
    int jordan1_student_elo_ratings[] = {1650, 1660, 1670, 1675, 1665, 1680, 1670, 1685, 1690, 1700, 1710, 1720};
    for (int j = 0; j < 12; j++)
        record1[5].data.ratings[j] = jordan1_student_elo_ratings[j];

    // 7. Morgan
    strcpy(record1[6].student_name, "Morgan");
    record1[6].student_elo_rating = 1550.5;
    strcpy(record1[6].learn_goals, "Tactics");
    record1[6].time_slot[0] = 5;
    record1[6].time_slot[1] = 6;
    record1[6].time_slot[2] = 2;
    record1[6].time_slot[3] = 1;
    record1[6].time_slot[4] = 9;
    strcpy(record1[6].preferred_coaching_style, "Aggressive");
    record1[6].assigned_trainer_id = 0;
    strcpy(record1[6].performance_data, "Endgames");
    record1[6].data.games_won = 20;
    record1[6].data.puzzles_solved = 60;
    int morgan_student_elo_ratings[] = {1550, 1560, 1570, 1565, 1555, 1575, 1580, 1590, 1600, 1605, 1610, 1620};
    for (int j = 0; j < 12; j++)
        record1[6].data.ratings[j] = morgan_student_elo_ratings[j];

    // 8. Riley
    strcpy(record1[7].student_name, "Riley");
    record1[7].student_elo_rating = 1500.0;
    strcpy(record1[7].learn_goals, "Attacking");
    record1[7].time_slot[0] = 10;
    record1[7].time_slot[1] = 7;
    record1[7].time_slot[2] = 3;
    record1[7].time_slot[3] = 4;
    record1[7].time_slot[4] = 8;
    strcpy(record1[7].preferred_coaching_style, "Aggressive");
    record1[7].assigned_trainer_id = 0;
    strcpy(record1[7].performance_data, "Positional Play");
    record1[7].data.games_won = 30;
    record1[7].data.puzzles_solved = 80;
    int riley_student_elo_ratings[] = {1500, 1510, 1520, 1515, 1505, 1525, 1530, 1540, 1550, 1560, 1570, 1580};
    for (int j = 0; j < 12; j++)
        record1[7].data.ratings[j] = riley_student_elo_ratings[j];

    // Add more students (9 to 19) similarly...

    // (Previous records for students 0 to 8)

    // 9. Alex
    strcpy(record1[8].student_name, "Alex");
    record1[8].student_elo_rating = 1400.5;
    strcpy(record1[8].learn_goals, "Tactics");
    record1[8].time_slot[0] = 3;
    record1[8].time_slot[1] = 8;
    record1[8].time_slot[2] = 5;
    record1[8].time_slot[3] = 10;
    record1[8].time_slot[4] = 6;
    strcpy(record1[8].preferred_coaching_style, "Aggressive");
    record1[8].assigned_trainer_id = 0;
    strcpy(record1[8].performance_data, "Endgame");
    record1[8].data.games_won = 18;
    record1[8].data.puzzles_solved = 85;
    int alex2_student_elo_ratings[] = {1400, 1410, 1405, 1415, 1410, 1420, 1430, 1435, 1440, 1445, 1450, 1455};
    for (int j = 0; j < 12; j++)
        record1[8].data.ratings[j] = alex2_student_elo_ratings[j];

    // 10. Taylor
    strcpy(record1[9].student_name, "Taylor");
    record1[9].student_elo_rating = 1900.0;
    strcpy(record1[9].learn_goals, "Strategy");
    record1[9].time_slot[0] = 1;
    record1[9].time_slot[1] = 9;
    record1[9].time_slot[2] = 7;
    record1[9].time_slot[3] = 4;
    record1[9].time_slot[4] = 2;
    strcpy(record1[9].preferred_coaching_style, "Defensive");
    record1[9].assigned_trainer_id = 0;
    strcpy(record1[9].performance_data, "Tactics");
    record1[9].data.games_won = 40;
    record1[9].data.puzzles_solved = 95;
    int taylor1_student_elo_ratings[] = {1900, 1905, 1910, 1920, 1915, 1925, 1930, 1935, 1940, 1950, 1955, 1960};
    for (int j = 0; j < 12; j++)
        record1[9].data.ratings[j] = taylor1_student_elo_ratings[j];

    // 11. Casey
    strcpy(record1[10].student_name, "Casey");
    record1[10].student_elo_rating = 1750.5;
    strcpy(record1[10].learn_goals, "Endgame");
    record1[10].time_slot[0] = 6;
    record1[10].time_slot[1] = 8;
    record1[10].time_slot[2] = 10;
    record1[10].time_slot[3] = 1;
    record1[10].time_slot[4] = 3;
    strcpy(record1[10].preferred_coaching_style, "Aggressive");
    record1[10].assigned_trainer_id = 0;
    strcpy(record1[10].performance_data, "Strategy");
    record1[10].data.games_won = 45;
    record1[10].data.puzzles_solved = 99;
    int casey_student_elo_ratings[] = {1750, 1760, 1770, 1765, 1780, 1785, 1790, 1795, 1800, 1805, 1810, 1820};
    for (int j = 0; j < 12; j++)
        record1[10].data.ratings[j] = casey_student_elo_ratings[j];

    // 12. Jordan
    strcpy(record1[11].student_name, "Jordan");
    record1[11].student_elo_rating = 1650.0;
    strcpy(record1[11].learn_goals, "Defense");
    record1[11].time_slot[0] = 3;
    record1[11].time_slot[1] = 2;
    record1[11].time_slot[2] = 8;
    record1[11].time_slot[3] = 4;
    record1[11].time_slot[4] = 9;
    strcpy(record1[11].preferred_coaching_style, "Defensive");
    record1[11].assigned_trainer_id = 0;
    strcpy(record1[11].performance_data, "Calculation");
    record1[11].data.games_won = 25;
    record1[11].data.puzzles_solved = 90;
    int jordan_student_elo_ratings[] = {1650, 1665, 1675, 1680, 1670, 1690, 1700, 1705, 1710, 1715, 1720, 1730};
    for (int j = 0; j < 12; j++)
        record1[11].data.ratings[j] = jordan_student_elo_ratings[j];

    // 13. Kim
    strcpy(record1[12].student_name, "Kim");
    record1[12].student_elo_rating = 1580.5;
    strcpy(record1[12].learn_goals, "Middlegame");
    record1[12].time_slot[0] = 9;
    record1[12].time_slot[1] = 1;
    record1[12].time_slot[2] = 3;
    record1[12].time_slot[3] = 5;
    record1[12].time_slot[4] = 7;
    strcpy(record1[12].preferred_coaching_style, "Aggressive");
    record1[12].assigned_trainer_id = 0;
    strcpy(record1[12].performance_data, "Opening");
    record1[12].data.games_won = 20;
    record1[12].data.puzzles_solved = 80;
    int kim_student_elo_ratings[] = {1580, 1590, 1600, 1605, 1610, 1620, 1625, 1630, 1640, 1650, 1660, 1665};
    for (int j = 0; j < 12; j++)
        record1[12].data.ratings[j] = kim_student_elo_ratings[j];

    // 14. Taylor
    strcpy(record1[13].student_name, "Taylor");
    record1[13].student_elo_rating = 1450.0;
    strcpy(record1[13].learn_goals, "Analysis");
    record1[13].time_slot[0] = 2;
    record1[13].time_slot[1] = 6;
    record1[13].time_slot[2] = 8;
    record1[13].time_slot[3] = 4;
    record1[13].time_slot[4] = 3;
    strcpy(record1[13].preferred_coaching_style, "Defensive");
    record1[13].assigned_trainer_id = 0;
    strcpy(record1[13].performance_data, "Endgame");
    record1[13].data.games_won = 15;
    record1[13].data.puzzles_solved = 70;
    int taylor2_student_elo_ratings_2[] = {1450, 1460, 1470, 1480, 1485, 1490, 1495, 1500, 1505, 1510, 1520, 1525};
    for (int j = 0; j < 12; j++)
        record1[13].data.ratings[j] = taylor2_student_elo_ratings_2[j];

    // 15. Morgan
    strcpy(record1[14].student_name, "Morgan");
    record1[14].student_elo_rating = 1300.0;
    strcpy(record1[14].learn_goals, "Endgame");
    record1[14].time_slot[0] = 7;
    record1[14].time_slot[1] = 2;
    record1[14].time_slot[2] = 5;
    record1[14].time_slot[3] = 6;
    record1[14].time_slot[4] = 1;
    strcpy(record1[14].preferred_coaching_style, "Aggressive");
    record1[14].assigned_trainer_id = 0;
    strcpy(record1[14].performance_data, "Middlegame");
    record1[14].data.games_won = 12;
    record1[14].data.puzzles_solved = 65;
    int morgan_student_elo_ratings_2[] = {1300, 1310, 1320, 1330, 1340, 1350, 1360, 1370, 1380, 1390, 1400, 1405};
    for (int j = 0; j < 12; j++)
        record1[14].data.ratings[j] = morgan_student_elo_ratings_2[j];

    // 16. Jamie
    strcpy(record1[15].student_name, "Jamie");
    record1[15].student_elo_rating = 1505.0;
    strcpy(record1[15].learn_goals, "Calculation");
    record1[15].time_slot[0] = 4;
    record1[15].time_slot[1] = 8;
    record1[15].time_slot[2] = 1;
    record1[15].time_slot[3] = 5;
    record1[15].time_slot[4] = 3;
    strcpy(record1[15].preferred_coaching_style, "Defensive");
    record1[15].assigned_trainer_id = 0;
    strcpy(record1[15].performance_data, "Tactics");
    record1[15].data.games_won = 27;
    record1[15].data.puzzles_solved = 88;
    int jamie_student_elo_ratings[] = {1505, 1515, 1520, 1525, 1530, 1540, 1550, 1555, 1560, 1570, 1580, 1590};
    for (int j = 0; j < 12; j++)
        record1[15].data.ratings[j] = jamie_student_elo_ratings[j];

    // 17. Avery
    strcpy(record1[16].student_name, "Avery");
    record1[16].student_elo_rating = 1250.0;
    strcpy(record1[16].learn_goals, "Techniques");
    record1[16].time_slot[0] = 10;
    record1[16].time_slot[1] = 1;
    record1[16].time_slot[2] = 3;
    record1[16].time_slot[3] = 6;
    record1[16].time_slot[4] = 2;
    strcpy(record1[16].preferred_coaching_style, "Aggressive");
    record1[16].assigned_trainer_id = 0;
    strcpy(record1[16].performance_data, "Endgame");
    record1[16].data.games_won = 10;
    record1[16].data.puzzles_solved = 60;
    int avery_student_elo_ratings[] = {1250, 1260, 1270, 1280, 1290, 1300, 1310, 1320, 1330, 1340, 1350, 1355};
    for (int j = 0; j < 12; j++)
        record1[16].data.ratings[j] = avery_student_elo_ratings[j];

    // 18. Riley
    strcpy(record1[17].student_name, "Riley");
    record1[17].student_elo_rating = 1905.0;
    strcpy(record1[17].learn_goals, "Study");
    record1[17].time_slot[0] = 8;
    record1[17].time_slot[1] = 10;
    record1[17].time_slot[2] = 4;
    record1[17].time_slot[3] = 6;
    record1[17].time_slot[4] = 1;
    strcpy(record1[17].preferred_coaching_style, "Defensive");
    record1[17].assigned_trainer_id = 0;
    strcpy(record1[17].performance_data, "Tactics");
    record1[17].data.games_won = 32;
    record1[17].data.puzzles_solved = 77;
    int riley2_student_elo_ratings_2[] = {1905, 1910, 1920, 1930, 1940, 1950, 1960, 1970, 1980, 1990, 2000, 2005};
    for (int j = 0; j < 12; j++)
        record1[17].data.ratings[j] = riley2_student_elo_ratings_2[j];

    // 19. Skylar
    strcpy(record1[18].student_name, "Skylar");
    record1[18].student_elo_rating = 1405.0;
    strcpy(record1[18].learn_goals, "Understanding");
    record1[18].time_slot[0] = 3;
    record1[18].time_slot[1] = 9;
    record1[18].time_slot[2] = 2;
    record1[18].time_slot[3] = 4;
    record1[18].time_slot[4] = 7;
    strcpy(record1[18].preferred_coaching_style, "Aggressive");
    record1[18].assigned_trainer_id = 0;
    strcpy(record1[18].performance_data, "Opening");
    record1[18].data.games_won = 22;
    record1[18].data.puzzles_solved = 85;
    int skylar_student_elo_ratings[] = {1405, 1410, 1420, 1430, 1440, 1450, 1460, 1470, 1480, 1490, 1500, 1510};
    for (int j = 0; j < 12; j++)
        record1[18].data.ratings[j] = skylar_student_elo_ratings[j];

    // 20. Quinn
    strcpy(record1[19].student_name, "Quinn");
    record1[19].student_elo_rating = 1305.0;
    strcpy(record1[19].learn_goals, "Focus");
    record1[19].time_slot[0] = 2;
    record1[19].time_slot[1] = 5;
    record1[19].time_slot[2] = 6;
    record1[19].time_slot[3] = 9;
    record1[19].time_slot[4] = 1;
    strcpy(record1[19].preferred_coaching_style, "Defensive");
    record1[19].assigned_trainer_id = 0;
    strcpy(record1[19].performance_data, "Positional Play");
    record1[19].data.games_won = 35;
    record1[19].data.puzzles_solved = 80;
    int quinn_student_elo_ratings[] = {1305, 1320, 1330, 1340, 1350, 1360, 1370, 1380, 1390, 1400, 1405, 1410};
    for (int j = 0; j < 12; j++)
        record1[19].data.ratings[j] = quinn_student_elo_ratings[j];
}

// Hardcoded trainer data

void hardcode2(struct trainer_attribute record2[])
{

    // 0. Trainer 1
    record2[0].trainer_id = 1;
    strcpy(record2[0].trainer_name, "Alex");
    record2[0].trainer_elo_rating = 1450.0;
    strcpy(record2[0].coaching_style, "Aggressive");
    record2[0].free_time_slot[0] = 1;
    record2[0].free_time_slot[1] = 2;
    record2[0].free_time_slot[2] = 3;
    record2[0].free_time_slot[3] = 5;
    record2[0].free_time_slot[4] = 10;
    record2[0].experience_level = 5;
    record2[0].qualify_elo = 1400.0;
    record2[0].max_students = 5;

    // 1. Trainer 2
    record2[1].trainer_id = 2;
    strcpy(record2[1].trainer_name, "Jamie");
    record2[1].trainer_elo_rating = 1600.0;
    strcpy(record2[1].coaching_style, "Defensive");
    record2[1].free_time_slot[0] = 4;
    record2[1].free_time_slot[1] = 6;
    record2[1].free_time_slot[2] = 7;
    record2[1].free_time_slot[3] = 8;
    record2[1].free_time_slot[4] = 9;
    record2[1].experience_level = 8;
    record2[1].qualify_elo = 1550.0;
    record2[1].max_students = 4;

    // 2. Trainer 3
    record2[2].trainer_id = 3;
    strcpy(record2[2].trainer_name, "Jordan");
    record2[2].trainer_elo_rating = 1700.0;
    strcpy(record2[2].coaching_style, "Aggressive");
    record2[2].free_time_slot[0] = 3;
    record2[2].free_time_slot[1] = 5;
    record2[2].free_time_slot[2] = 6;
    record2[2].free_time_slot[3] = 7;
    record2[2].free_time_slot[4] = 8;
    record2[2].experience_level = 10;
    record2[2].qualify_elo = 1600.0;
    record2[2].max_students = 6;

    // 3. Trainer 4
    record2[3].trainer_id = 4;
    strcpy(record2[3].trainer_name, "Taylor");
    record2[3].trainer_elo_rating = 1800.0;
    strcpy(record2[3].coaching_style, "Defensive");
    record2[3].free_time_slot[0] = 1;
    record2[3].free_time_slot[1] = 3;
    record2[3].free_time_slot[2] = 4;
    record2[3].free_time_slot[3] = 8;
    record2[3].free_time_slot[4] = 9;
    record2[3].experience_level = 7;
    record2[3].qualify_elo = 1650.0;
    record2[3].max_students = 3;

    // 4. Trainer 5
    record2[4].trainer_id = 5;
    strcpy(record2[4].trainer_name, "Morgan");
    record2[4].trainer_elo_rating = 1550.0;
    strcpy(record2[4].coaching_style, "Aggressive");
    record2[4].free_time_slot[0] = 2;
    record2[4].free_time_slot[1] = 6;
    record2[4].free_time_slot[2] = 8;
    record2[4].free_time_slot[3] = 5;
    record2[4].free_time_slot[4] = 7;
    record2[4].experience_level = 6;
    record2[4].qualify_elo = 1500.0;
    record2[4].max_students = 5;

    // 5. Trainer 6
    record2[5].trainer_id = 6;
    strcpy(record2[5].trainer_name, "Avery");
    record2[5].trainer_elo_rating = 1650.0;
    strcpy(record2[5].coaching_style, "Defensive");
    record2[5].free_time_slot[0] = 1;
    record2[5].free_time_slot[1] = 2;
    record2[5].free_time_slot[2] = 4;
    record2[5].free_time_slot[3] = 6;
    record2[5].free_time_slot[4] = 8;
    record2[5].experience_level = 9;
    record2[5].qualify_elo = 1550.0;
    record2[5].max_students = 6;

    // 6. Trainer 7
    record2[6].trainer_id = 7;
    strcpy(record2[6].trainer_name, "Riley");
    record2[6].trainer_elo_rating = 1900.0;
    strcpy(record2[6].coaching_style, "Aggressive");
    record2[6].free_time_slot[0] = 3;
    record2[6].free_time_slot[1] = 4;
    record2[6].free_time_slot[2] = 5;
    record2[6].free_time_slot[3] = 7;
    record2[6].free_time_slot[4] = 9;
    record2[6].experience_level = 11;
    record2[6].qualify_elo = 1800.0;
    record2[6].max_students = 7;

    // 7. Trainer 8
    record2[7].trainer_id = 8;
    strcpy(record2[7].trainer_name, "Kim");
    record2[7].trainer_elo_rating = 1720.0;
    strcpy(record2[7].coaching_style, "Defensive");
    record2[7].free_time_slot[0] = 1;
    record2[7].free_time_slot[1] = 2;
    record2[7].free_time_slot[2] = 3;
    record2[7].free_time_slot[3] = 4;
    record2[7].free_time_slot[4] = 6;
    record2[7].experience_level = 5;
    record2[7].qualify_elo = 1500.0;
    record2[7].max_students = 3;

    // 8. Trainer 9
    record2[8].trainer_id = 9;
    strcpy(record2[8].trainer_name, "Skylar");
    record2[8].trainer_elo_rating = 1750.0;
    strcpy(record2[8].coaching_style, "Aggressive");
    record2[8].free_time_slot[0] = 2;
    record2[8].free_time_slot[1] = 5;
    record2[8].free_time_slot[2] = 7;
    record2[8].free_time_slot[3] = 8;
    record2[8].free_time_slot[4] = 10;
    record2[8].experience_level = 6;
    record2[8].qualify_elo = 1600.0;
    record2[8].max_students = 5;

    // 9. Trainer 10
    record2[9].trainer_id = 10;
    strcpy(record2[9].trainer_name, "Jamie");
    record2[9].trainer_elo_rating = 1500.0;
    strcpy(record2[9].coaching_style, "Defensive");
    record2[9].free_time_slot[0] = 3;
    record2[9].free_time_slot[1] = 6;
    record2[9].free_time_slot[2] = 8;
    record2[9].free_time_slot[3] = 1;
    record2[9].free_time_slot[4] = 2;
    record2[9].experience_level = 4;
    record2[9].qualify_elo = 1450.0;
    record2[9].max_students = 6;

    // 10. Trainer 11
    record2[10].trainer_id = 11;
    strcpy(record2[10].trainer_name, "Quinn");
    record2[10].trainer_elo_rating = 1670.0;
    strcpy(record2[10].coaching_style, "Aggressive");
    record2[10].free_time_slot[0] = 4;
    record2[10].free_time_slot[1] = 5;
    record2[10].free_time_slot[2] = 8;
    record2[10].free_time_slot[3] = 9;
    record2[10].free_time_slot[4] = 10;
    record2[10].experience_level = 10;
    record2[10].qualify_elo = 1550.0;
    record2[10].max_students = 5;

    // 11. Trainer 12
    record2[11].trainer_id = 12;
    strcpy(record2[11].trainer_name, "Cameron");
    record2[11].trainer_elo_rating = 1420.0;
    strcpy(record2[11].coaching_style, "Defensive");
    record2[11].free_time_slot[0] = 1;
    record2[11].free_time_slot[1] = 2;
    record2[11].free_time_slot[2] = 3;
    record2[11].free_time_slot[3] = 5;
    record2[11].free_time_slot[4] = 6;
    record2[11].experience_level = 3;
    record2[11].qualify_elo = 1400.0;
    record2[11].max_students = 4;

    // 12. Trainer 13
    record2[12].trainer_id = 13;
    strcpy(record2[12].trainer_name, "Jesse");
    record2[12].trainer_elo_rating = 1560.0;
    strcpy(record2[12].coaching_style, "Aggressive");
    record2[12].free_time_slot[0] = 2;
    record2[12].free_time_slot[1] = 4;
    record2[12].free_time_slot[2] = 5;
    record2[12].free_time_slot[3] = 8;
    record2[12].free_time_slot[4] = 9;
    record2[12].experience_level = 7;
    record2[12].qualify_elo = 1500.0;
    record2[12].max_students = 5;

    // 13. Trainer 14
    record2[13].trainer_id = 14;
    strcpy(record2[13].trainer_name, "Casey");
    record2[13].trainer_elo_rating = 1620.0;
    strcpy(record2[13].coaching_style, "Defensive");
    record2[13].free_time_slot[0] = 1;
    record2[13].free_time_slot[1] = 3;
    record2[13].free_time_slot[2] = 4;
    record2[13].free_time_slot[3] = 6;
    record2[13].free_time_slot[4] = 10;
    record2[13].experience_level = 5;
    record2[13].qualify_elo = 1400.0;
    record2[13].max_students = 6;

    // 14. Trainer 15
    record2[14].trainer_id = 15;
    strcpy(record2[14].trainer_name, "Taylor");
    record2[14].trainer_elo_rating = 1590.0;
    strcpy(record2[14].coaching_style, "Aggressive");
    record2[14].free_time_slot[0] = 1;
    record2[14].free_time_slot[1] = 2;
    record2[14].free_time_slot[2] = 3;
    record2[14].free_time_slot[3] = 5;
    record2[14].free_time_slot[4] = 8;
    record2[14].experience_level = 8;
    record2[14].qualify_elo = 1500.0;
    record2[14].max_students = 4;

    // 15. Trainer 16
    record2[15].trainer_id = 16;
    strcpy(record2[15].trainer_name, "Jordan");
    record2[15].trainer_elo_rating = 1750.0;
    strcpy(record2[15].coaching_style, "Defensive");
    record2[15].free_time_slot[0] = 3;
    record2[15].free_time_slot[1] = 5;
    record2[15].free_time_slot[2] = 7;
    record2[15].free_time_slot[3] = 9;
    record2[15].free_time_slot[4] = 10;
    record2[15].experience_level = 9;
    record2[15].qualify_elo = 1650.0;
    record2[15].max_students = 6;

    // 16. Trainer 17
    record2[16].trainer_id = 17;
    strcpy(record2[16].trainer_name, "Morgan");
    record2[16].trainer_elo_rating = 1800.0;
    strcpy(record2[16].coaching_style, "Aggressive");
    record2[16].free_time_slot[0] = 1;
    record2[16].free_time_slot[1] = 2;
    record2[16].free_time_slot[2] = 4;
    record2[16].free_time_slot[3] = 6;
    record2[16].free_time_slot[4] = 8;
    record2[16].experience_level = 7;
    record2[16].qualify_elo = 1500.0;
    record2[16].max_students = 5;

    // 17. Trainer 18
    record2[17].trainer_id = 18;
    strcpy(record2[17].trainer_name, "Avery");
    record2[17].trainer_elo_rating = 1640.0;
    strcpy(record2[17].coaching_style, "Defensive");
    record2[17].free_time_slot[0] = 2;
    record2[17].free_time_slot[1] = 3;
    record2[17].free_time_slot[2] = 5;
    record2[17].free_time_slot[3] = 7;
    record2[17].free_time_slot[4] = 9;
    record2[17].experience_level = 5;
    record2[17].qualify_elo = 1400.0;
    record2[17].max_students = 6;

    // 18. Trainer 19
    record2[18].trainer_id = 19;
    strcpy(record2[18].trainer_name, "Riley");
    record2[18].trainer_elo_rating = 1570.0;
    strcpy(record2[18].coaching_style, "Aggressive");
    record2[18].free_time_slot[0] = 1;
    record2[18].free_time_slot[1] = 4;
    record2[18].free_time_slot[2] = 6;
    record2[18].free_time_slot[3] = 7;
    record2[18].free_time_slot[4] = 8;
    record2[18].experience_level = 6;
    record2[18].qualify_elo = 1450.0;
    record2[18].max_students = 5;

    // 19. Trainer 20
    record2[19].trainer_id = 20;
    strcpy(record2[19].trainer_name, "Taylor");
    record2[19].trainer_elo_rating = 1600.0;
    strcpy(record2[19].coaching_style, "Defensive");
    record2[19].free_time_slot[0] = 1;
    record2[19].free_time_slot[1] = 2;
    record2[19].free_time_slot[2] = 3;
    record2[19].free_time_slot[3] = 5;
    record2[19].free_time_slot[4] = 10;
    record2[19].experience_level = 8;
    record2[19].qualify_elo = 1500.0;
    record2[19].max_students = 4;
}

// Function to find strongest trainer using merge_sort

void merge_self_strongest(struct trainer_attribute trainer_DB[], int l, int m, int n, struct trainer_attribute temp5[], float average[])
{
    int i = l, j = m + 1, k = l;
    while ((i <= m) && (j <= n))
    {
        if (average[i] > average[j])
        {
            temp5[k++] = trainer_DB[i++];
        }
        else
        {
            temp5[k++] = trainer_DB[j++];
        }
    }

    while (i <= m)
    {
        temp5[k++] = trainer_DB[i++];
    }

    while (j <= n)
    {
        temp5[k++] = trainer_DB[j++];
    }

    for (i = l; i <= n; i++)
    {
        trainer_DB[i] = temp5[i];
    }
}

void merge_sort_strongest(struct trainer_attribute trainer_DB[], struct trainer_attribute temp5[], int lo, int hi, float average[])
{
    if (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        merge_sort_strongest(trainer_DB, temp5, lo, mid, average);
        merge_sort_strongest(trainer_DB, temp5, mid + 1, hi, average);
        merge_self_strongest(trainer_DB, lo, mid, hi, temp5, average);
    }
}

void strongest(struct trainer_attribute trainer_DB[], struct trainer_attribute temp5[], int lo, int hi, float average[])
{
    merge_sort_strongest(trainer_DB, temp5, lo, hi, average);
    printf("Strongest Trainer Name: %s ID: %d\n", trainer_DB[0].trainer_name, trainer_DB[0].trainer_id);
}


int main()
{
    // student info variables

    char stud_name[NAME_LEN];
    float stud_elo_rating;
    char goals[GOALS];
    int slot[SLOT];
    char style[STYLE];
    int assigned_train_id, stud_records=0;
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
    int train_slot[SLOT];
    int experience;
    float qualify;
    int max, train_records=0, status3, status4;
    struct trainer_attribute trainer_DB[TRAIN_DB_SIZE];

    // Other variables
    int user_input;
    int exit = 0;
    int count[TRAIN_DB_SIZE];
    float average[TRAIN_DB_SIZE];
    struct student_attribute list[STUD_DB_SIZE];
    struct student_attribute temp1[STUD_DB_SIZE];
    struct student_attribute temp2[STUD_DB_SIZE];
    struct trainer_attribute temp3[TRAIN_DB_SIZE];
    struct trainer_attribute temp5[TRAIN_DB_SIZE];
    int size_succesive;
    int x, y;

    // Intializing DB vales to zero.
    Initialize_student_DB(student_DB, STUD_DB_SIZE);
    Initialize_trainer_DB(trainer_DB, TRAIN_DB_SIZE);
    Initialize_student_DB(list, stud_records);

    // hardcoded values for 20 students and trainers
    hardcode1(student_DB);
    hardcode2(trainer_DB);

    do
    {
        printf("Functions to perform: \n");
        printf("1.Insert or Update a Student \n 2. Insert or Update a Trainer \n 3. Delete a student \n 4. Delete a Trainer \n 5.List of students a trainer is teaching \n 6. Display students based on decreasing ELO Rating \n 7. Display most popular trainer \n 8. Display strongest Trainer \n 9. Assign Trainer based on matching criteria \n 10. Display students with decreasing ELO Rating gains \n 11. Display Student Database \n 12. Display Trainer Database \n 13. Exit \n");
        printf("Enter the function number you want to perform: ");
        scanf("%d", &user_input);
        switch (user_input)
        {
        case 1:
            printf("How many student records you want to enter: ");
            scanf("%d", &x);
            stud_records=x;

            for (int i = 0; i < stud_records; i++)
            {
                printf("Name: ");
                scanf("%s", stud_name);
                printf("ELO: ");
                scanf("%f", &stud_elo_rating);
                printf("Goals:");
                scanf("%s", goals);
                for (int k = 0; k < SLOT; k++)
                {
                    printf("slot %d: ", k + 1);
                    scanf("%d", &slot[k]);
                }
                printf("style: ");
                scanf("%s", style);
                printf("performance: ");
                scanf("%s", performance);
                printf("Games Won: ");
                scanf("%d", &info.games_won);
                printf("Puzzles Solved: ");
                scanf("%d", &info.puzzles_solved);
                for (int j = 0; j < 12; j++)
                {
                    printf("Month %d: ", j + 1);
                    scanf("%d", &info.ratings[j]);
                }

                status1 = insert_update_student(student_DB, 20 + stud_records, stud_name, stud_elo_rating, goals, slot, style, assigned_train_id, performance, info);

                if (!status1)
                {
                    printf("Database overload! Come next time\n");
                }
                else
                {
                    printf("Student data updated successfully\n");
                }
            }

            break;

        case 2:
            printf("How many trainer records do you want to enter? ");
            scanf("%d", &y);
            train_records=y;

            for (int i = 0; i < train_records; i++)
            {
                printf("ID: ");
                scanf("%d", &train_id);
                printf("Name: ");
                scanf("%s", train_name);
                printf("ELO: ");
                scanf("%f", &train_elo_rating);
                printf("Style: ");
                scanf("%s", coach_style);
                printf("Slots: ");
                for (int k = 0; k < SLOT; k++)
                {
                    scanf("%d", &train_slot[k]);
                }
                printf("Experience: ");
                scanf("%d", &experience);
                printf("Qualify elo: ");
                scanf("%f", &qualify);
                printf("Max Students: ");
                scanf("%d", &max);

                status3 = insert_update_trainer(trainer_DB, 20 + train_records, train_id, train_name, train_elo_rating, coach_style, train_slot, experience, qualify, max);

                if (!status3)
                {
                    printf("Database is full! Apply next time\n");
                }
                else
                {
                    printf("Trainer data updated successfully\n");
                }
            }

            break;

        case 3:
            printf("Enter the student name to be deleted; ");
            scanf("%s", &stud_name);
            printf("Enter the elo rating of student: ");
            scanf("%f", &stud_elo_rating);
            int status2 = delete_student_record(student_DB, 20 + stud_records, stud_name, stud_elo_rating);

            if (status2)
            {
                printf("Student Record deleted successfully!\n");
            }
            else
            {
                printf("No student record of given name exists!\n");
            }
            break;

        case 4:
            printf("Enter trainer ID to be deleted: ");
            scanf("%d", &train_id);

            status4 = delete_trainer_record(trainer_DB, 20 + train_records, train_id);

            if (status4)
            {
                printf("Trainer record deleted successfully\n");
            }
            else
            {
                printf("No trainer record found\n");
            }
            break;

        case 5:
            printf("Student-Trainer list:\n");
            student_trainer_list(student_DB, trainer_DB, 20 + stud_records, 20 + train_records);
            break;

        case 6:

            sort_students_elo_rating(student_DB, temp1, 20 + stud_records);
            print_stud(student_DB, 20 + stud_records);
            break;

        case 7:
            average_elo(trainer_DB, student_DB, 20 + stud_records, 20 + train_records, average);
            most_popular_trainer(trainer_DB, 20 + train_records, 0, 20 + train_records - 1, average, count);
            break;

        case 8:
            average_elo(trainer_DB, student_DB, 20 + stud_records, 20 + train_records, average);
            strongest(trainer_DB, temp5, 0, 20 + train_records - 1, average);
            break;

        case 9:
            match_pairs(count, student_DB, trainer_DB, 20 + stud_records, 20 + train_records);
            print_stud(student_DB, 20 + stud_records);
            break;

        case 10:
            size_succesive = successive_increase(student_DB, 20 + stud_records, list);

            mergeSort_decreasing_gains(list, temp2, 0, size_succesive - 1);
            print_stud(list, size_succesive);
            break;

        case 11:
            print_stud(student_DB, 20 + stud_records);
            break;

        case 12:
            print_trainers(trainer_DB, 20 + train_records);
            break;

        case 13:
            exit = 1;
            break;

        default:
            printf("Enter appropriate number for function!");
        }
    } while (exit == 0);

    return 0;
}
