#include <stdio.h>
#define NAME_LEN 100
#define GOALS 50
#define SLOT 25
#define STYLE 25
#define PERFORMANCE 50

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
    char coaching_style[STYLE];
    int given_trainer_id;
    char performance_data[PERFORMANCE];
    struct progress data;
};

struct trainer_attribute
{
    int id;
    char trainer_name[NAME_LEN];
    float trainer_elo_rating;
    char coaching_style[STYLE];
    char time_slot[SLOT];
    int experience_level;
    float qualify_elo;
    int max_students;
};

