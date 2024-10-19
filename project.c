#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_LEN 100
#define GOALS 50
#define SLOT 5
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

int insert_update_trainer(struct trainer_attribute trainer_DB[], int size, int train_id, char train_name[], float train_elo_rating, char coach_style[], int slot[], int experience, float qualify, int max)
{
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
        j = 0, free_loc = 0;
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

// Fucntion to insert update student records

int insert_update_student(struct student_attribute student_DB[], int size, char stud_name[], float stud_elo_rating, char goals[], int slot[], char style[], int assigned_train_id, char performance[], struct progress info)
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
        strcpy(student_DB[i].learn_goals, goals);
        for (int k = 0; k < SLOT; k++)
        {
            student_DB[i].time_slot[k] = slot[k];
        }
        strcpy(student_DB[i].preferred_coaching_style, style);

        // Check once assigned trainer id!

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
        j = 0, free_loc = 0;
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

            // Check once assigned trainer_id
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

// Delete trainer record

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

// Function to sort students based on elo_rating

void merge_self_stud_elo(struct student_attribute student_DB[], struct student_attribute temp[], int low, int mid, int high) {
    int i = low, j = mid + 1, k = low;

    while (i <= mid && j <= high) {
        if (student_DB[i].student_elo_rating == student_DB[j].student_elo_rating) {
            if (student_DB[i].data.games_won > student_DB[j].data.games_won) {
                temp[k] = student_DB[i];
                i++;
            } else {
                temp[k] = student_DB[j];
                j++;
            }
        } else {
            if (student_DB[i].student_elo_rating > student_DB[j].student_elo_rating) {
                temp[k] = student_DB[i];
                i++;
            } else {
                temp[k] = student_DB[j];
                j++;
            }
        }
        k++;
    }

    while (i <= mid) {
        temp[k] = student_DB[i];
        i++;
        k++;
    }

    while (j <= high) {
        temp[k] = student_DB[j];
        j++;
        k++;
    }

    for (i = low; i <= high; i++) {
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

int successive_increase(struct student_attribute student_DB[], int stud_records, struct student_attribute list[])
{
    int cnt = 0;
    int m=0;
    for (int i = 0; i < stud_records; i++)
    {
        int flag = 0;
        for (int j = 1; j < 12&&flag==0; j++)
        {
            if (student_DB[i].data.ratings[j] < student_DB[i].data.ratings[j - 1])
            {
                flag = 1; 
            }
        }
        if (!flag)
        {
            cnt++;
            list[m++] = student_DB[i];
        }
    }
    return cnt;
}

void match_pairs(int count[], struct student_attribute students[], struct trainer_attribute trainers[],int stud_records, int train_records)
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



void average_elo(struct trainer_attribute trainer_DB[], struct student_attribute student_DB[], int stud_records, int train_records, float average[])
{
    float sum = 0;
    int cnt = 0;
    for (int i = 0; i < train_records; i++)
    {
        for (int j = 0; j < stud_records; j++)
        {
            if (trainer_DB[i].trainer_id == student_DB[j].assigned_trainer_id)
            {
                sum = sum + student_DB[j].student_elo_rating;
                cnt++;
            }
        }
        average[i] = sum / (float)cnt;
    }
}

void merge_self_popularity(struct trainer_attribute trainer_DB[], int l, int m, int n, struct trainer_attribute temp[], float average[], int count[])
{
    int i, j, k;
    i = l;
    j = m + 1;
    k = l;
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
        }
        else
        {
            temp[k++] = trainer_DB[j++];
        }
    }

    if (i <= m)
    {
        while (i <= m)
        {
            temp[k++] = trainer_DB[i++];
        }
    }
    else
    {
        while (j <= n)
        {
            temp[k++] = trainer_DB[j++];
        }
    }

    for (i = l; i <= n; i++)
    {
        trainer_DB[i] = temp[i];
    }
}

void mergeSort_popularity(struct trainer_attribute trainer_DB[], struct trainer_attribute temp[], int lo, int hi, float average[], int count[])
{
    int mid;
    if (lo < hi)
    {
        mid = lo + (hi - lo) / 2;
        mergeSort_popularity(trainer_DB, temp, lo, mid, average, count);
        mergeSort_popularity(trainer_DB, temp, mid + 1, hi, average, count);
        merge_self_popularity(trainer_DB, lo, mid, hi, temp, average, count);
    }
}

void most_popular_trainer(struct trainer_attribute trainer_DB[], int train_records, int lo, int hi, float average[], int count[])
{
    struct trainer_attribute temp[train_records];
    mergeSort_popularity(trainer_DB, temp, 0, train_records - 1, average, count);
    printf("Most popular trainer: %s\nTrainer ID: %d", trainer_DB[0].trainer_name, trainer_DB[0].trainer_id);
}

void print_stud(struct student_attribute s[], int size)
{
    for(int i=0; i<size; i++)
    {
        if(s[i].student_name[0] != '\0' && s[i].student_elo_rating != 0)
        {
            printf("Name: %s\n", s[i].student_name);
            printf("ELO: %f\n",s[i].student_elo_rating);
            printf("Learning Goals: %s\n",s[i].learn_goals);
            for (int j = 0; j < SLOT; j++)
            {
                printf("Slot %d: %d\n",j+1,s[i].time_slot[j]);
            }
            printf("style: %s\n",s[i].preferred_coaching_style);
            printf("trainer_id: %d\n",s[i].assigned_trainer_id);
            printf("performance: %s\n",s[i].performance_data);
            printf("Games Won: %d\n",s[i].data.games_won);
            printf("Puzzles Solved :%d\n",s[i].data.puzzles_solved);
            for(int k=0; k<12;k++)
            {
                printf("Ratings %d: %d\n",k+1,s[i].data.ratings[k]);
            }
        }
        
    }
}

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

void main()
{
    // student info variables

    char stud_name[NAME_LEN];
    float stud_elo_rating;
    char goals[GOALS];
    int slot[SLOT];
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
    int train_slot[SLOT];
    int experience;
    float qualify;
    int max, train_records, status3, status4;
    struct trainer_attribute trainer_DB[TRAIN_DB_SIZE];

    // Intializing DB vales to zero.

    Initialize_student_DB(student_DB, STUD_DB_SIZE);
    Initialize_trainer_DB(trainer_DB, TRAIN_DB_SIZE);

    int user_input;

    int exit = 0;

    int count[TRAIN_DB_SIZE];
    float average[TRAIN_DB_SIZE];

    struct student_attribute list[STUD_DB_SIZE];

    Initialize_student_DB(list, stud_records);
    do
    {
        printf("Functions to perform: \n");
        printf("1.Insert or Update a Student \n 2. Insert or Update a Trainer \n 3. Delete a student \n 4. Delete a Trainer \n 5.List of students a trainer is teaching \n 6. Display students based on decreasing ELO Rating \n 7. Display most popular trainer \n 8. Display strongest Trainer \n 9. Assign Trainer based on matching criteria \n 10. Display students with decreasing ELO Rating gains \n 11. Display Student Database \n 12. Display Trainer Database \n 13. Exit \n");
        printf("Enter the function number you want to perform: ");
        scanf("%d",&user_input);
        switch(user_input)
        {
            case 1:
                printf("How many student records you want to enter: ");
                scanf("%d", &stud_records);

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
                        printf("slot %d: ",k+1);
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
                        printf("Month %d: ",j+1);
                        scanf("%d", &info.ratings[j]);
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

                break;

            case 2: 
                printf("How many trainer records do you want to enter? ");
                scanf("%d", &train_records);

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

                break;
            
            case 3:
                printf("Enter the student name to be deleted; ");
                scanf("%s", &stud_name);
                printf("Enter the elo rating of student: ");
                scanf("%f", &stud_elo_rating);
                int status2 = delete_student_record(student_DB, STUD_DB_SIZE, stud_name, stud_elo_rating);

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

                status4 = delete_trainer_record(trainer_DB, TRAIN_DB_SIZE, train_id);

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

            case 6: 
                struct student_attribute temp1[STUD_DB_SIZE];
                sort_students_elo_rating(student_DB, temp1, STUD_DB_SIZE);
                print_stud(student_DB, stud_records);
                break;

            case 7: 
                struct trainer_attribute temp3[TRAIN_DB_SIZE];
                most_popular_trainer(trainer_DB, TRAIN_DB_SIZE, 0, train_records - 1, average, count);
                mergeSort_popularity(trainer_DB, temp3, 0, train_records - 1, average, count);
                break;
                print_trainers(trainer_DB, TRAIN_DB_SIZE);

            case 8:
                average_elo(trainer_DB, student_DB, STUD_DB_SIZE, TRAIN_DB_SIZE, average);
                print_trainers(trainer_DB, TRAIN_DB_SIZE);

            case 9:
                match_pairs(count, student_DB, trainer_DB, STUD_DB_SIZE, TRAIN_DB_SIZE);
                print_stud(student_DB, stud_records);
                break;

            case 10:
                int size_succesive = successive_increase(student_DB, STUD_DB_SIZE, list);
                struct student_attribute temp2[STUD_DB_SIZE];
                mergeSort_decreasing_gains(list, temp2, 0, size_succesive-1);
                print_stud(student_DB, STUD_DB_SIZE);
                break;

            case 11:
                print_stud(student_DB, STUD_DB_SIZE);
                break;

            case 12:
                print_trainers(trainer_DB, TRAIN_DB_SIZE);
                break;

            case 13:
                exit = 1;
                break;

            default:
                printf("Enter appropriate number for function!");
        }
    }while(exit == 0);
    

    // Asking number of student records and taking input.

    

    

    // To delete a student record

    // To delete a trainer record
    
    // Ensure that stud_records is updated accoring to insert and delete functions.

    // Function call to sort student based on elo_rating.

    

    // answer to question 12

    

    

    
    //print_stud(list, size_succesive)

};
