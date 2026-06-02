#include <iostream>
#include <string>
#include <unordered_map>
#include <sqlite3.h>
// #include <windows.h>
#include <vector>
// #include <nlohman>
using namespace std;


//"seect * from students where" + var

// void add_field(string& subjects) {
//     string new_field;
//     cout<< "Input new field: ";
//     cin >> new_field;
//     subjects += " " + new_field;


// }

void execute(sqlite3* db, const char* sql)
{
    char* errMsg = 0;

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    
}

int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    for (int i = 0; i < argc; i++)
    {
        cout << azColName[i] << ": "
             << (argv[i] ? argv[i] : "NULL")
             << endl;
    }

    cout << "-------------------\n";

    return 0;
}
    enum MainMenu {
        TABLES = 1,
        STUDENTS,
        GRADES,
        SEARCH,
        SORT,
        STATS,
        EXIT = 0
    };

unordered_map<string, MainMenu> commands = {
    {"exit", EXIT},
    {"tables", TABLES},
    {"students", STUDENTS},
    {"grades", GRADES},
    {"search", SEARCH},
    {"sort", SORT},
    {"stats", STATS}
};


void show_main_menu();
void show_table_menu();
void show_student_menu();
void show_grades_menu();
void show_find_menu();
void show_sort_menu();
void show_statics_menu();
void open_submenu(MainMenu cmd, sqlite3* db);

void pause() {
    cout << "\ncontinue...";
    cin.ignore();
    cin.get();
}


void select(string table_name) {
    string sql = "SELECT * FROM table_name";
}
//"INSERT INTO students (name, age, score) values ('Andriy', 21, 7.5)"
void insert() {
    string sql = "INSERT INTO students (";

    string name_field = "name";
    string age_field = "age";
    string score_field = "score";

    string name;
    int age;
    double score;
    cin >>name;
    cin >>age;
    cin >>score;


}



void create_students(sqlite3* db){
    string sql = "CREATE TABLE IF NOT EXISTS students (Id INTEGER PRIMARY KEY AUTOINCREMENT, Surname TEXT, Name Text);";
    const char* sql_request = sql.c_str();
    execute(db, sql_request);
}
void create_subjects(sqlite3* db){
    string sql = "CREATE TABLE IF NOT EXISTS subjects (Id INTEGER PRIMARY KEY AUTOINCREMENT, Subject TEXT);";
    const char* sql_request = sql.c_str();
    execute(db, sql_request);
}
void create_grades(sqlite3* db){
    string sql =
        "CREATE TABLE grades ("
        "Id integer PRIMARY KEY AUTOINCREMENT, "
        "score integer CHECK (score >= 1 AND score <= 12), "
        "student_id INTEGER, "
        "subject_id INTEGER, "
        "FOREIGN KEY (student_id) REFERENCES students(id), "
        "FOREIGN KEY (subject_id) REFERENCES subjects(id)"
        ");";
         const char* sql_request = sql.c_str();
        execute(db, sql_request);
}

void show_table(sqlite3* db){
    string table_name;
    cout<<"Enter table name: ";
    cin>>table_name;
    string sql = "Select * from " + table_name + ";";
    int rc = sqlite3_exec(db, sql.c_str(), callback, 0, 0);
}

void add_student(sqlite3* db){
    string surname;
    string name;
    cout<<"Enter surname: ";
    cin>>surname;
    cout<<"Enter name: ";
    cin>>name;
    string sql =
    "INSERT INTO students (surname, name) VALUES ('" +
    surname + "', '" +
    name + "');";
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, 0);
}
void add_subject(sqlite3* db){
    string subject;
    string sql = "Insert into subjects (subject) Values ('" + subject + "');" ;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, 0);
}
void add_grade(sqlite3* db){
    int score;
    int student_id;
    int subject_id;
    cout<<"Enter grade: ";
    cin>>score;
    cout<<"Enter student id: ";
    cin>>student_id;
    cout<<"Enter subject id: ";
    cin>>subject_id;

    string sql = "Insert into grades (score, student_id, subject_id) Values ('" +
        to_string(score) + ", " +
        to_string(student_id) + ", " +
        to_string(subject_id) + ");";

    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, 0);
}


int main()
{
    sqlite3* db;

    int rc = sqlite3_open("school.db", &db);

    if (rc)
    {
        cerr << "Cannot open DB\n";
        return 1;
    }

    string input;
    MainMenu cmd;
    bool switcher = true;
    create_students(db);
    create_subjects(db);
    create_grades(db);
    while (switcher) {
        show_main_menu();
        printf("Input: ");
        cin >> input;
        cmd = commands[input];
            if (cmd == 0) {
                break;
            }
        open_submenu(cmd, db);

        pause();
        // system("cls");
        system("clear"); 
    }

    return 0;
}

void show_main_menu() {
    printf("Main menu\n");
    printf("1. tables\n");
    printf("2. students\n");
    printf("3. grades\n");
    printf("4. search\n");
    printf("5. sort\n");
    printf("6. stats\n");
    printf("0. exit\n");
}
void show_table_menu(sqlite3* db) {
    printf("Table menu\n");
    printf("1. Show tables (show)\n");
    printf("2. Show tables structure (show_structure)\n");
    printf("0. Exit tables (exit)\n");

    string input;
    cin >> input;
    if (input == "show") {
        show_table(db);
    }
    else if (input == "show_structure") {

    }
    else if (input == "exit") {

    }


}


void show_student_menu(sqlite3* db) {
    printf("Student menu\n");
    //insert
    //"INSERT INTO students (field1, field2, ...) VALUES (......) "
    printf("1. Add student (add)\n");
    //delete
    printf("2. Delete student (delete)\n");
    //update
    printf("3. Update student (update)\n");
    //select
    //"SELECT * FROM students"
    printf("4. Show all student (show_all)\n");
    //select
    //"SELECT * FROM students WHERE ID=${value}"
    printf("5. Show student by ID (show_by_id)\n");

    printf("0. Exit student table (exit)\n");

    string input;
    cin >> input;
    if (input == "add") {
        add_student(db);
    }
    else if (input == "delete") {

    }
    else if (input == "update") {

    }
    else if (input == "show_all") {

    }
    else if (input == "show_by_id") {

    }
    else if (input == "exit") {

    }
}
void show_grades_menu(sqlite3* db) {
    printf("Grades menu\n");
    //insert
    printf("1. Add grade (add_grade)\n");
    //update
    printf("2. Change grade (change_grade)\n");
    //delete
    printf("3. Delete grade (delete_grade)\n");
    //select
    // ???
    printf("4. Show student grades (show_stud)\n");
    //select
    // ???
    printf("5. Show class grades (show_class_grade)\n");
    //select
    printf("6. Avarage student grade (ave_st_gr)\n");
    //select
    printf("7. Avarage class grade (ave_class_gr)\n");
    printf("0. Exit grades (exit)\n");

    string input;
    cin >> input;
    if (input == "add_grade")
    {

    }
    else if (input == "change_grade")
    {

    }
    else if (input == "delete_grade")
    {

    }
    else if (input == "show_stud")
    {

    }
    else if (input == "show_class_grade")
    {

    }
    else if (input == "ave_st_gr")
    {

    }
    else if (input == "ave_class_gr")
    {

    }
    else if (input == "exit")
    {

    }
}
void show_find_menu(sqlite3* db) {
    printf("Find menu\n");
    //select
    printf("1. Find student by surname (find_surname)\n");
    //select
    printf("2. Find student by ID (find_id)\n");
    //select
    printf("3. Find students by class_group (find_group)\n");
    //select
    printf("4. Find studetns by avarage grade (find_average)\n");
    //select
    printf("5. Find honor students (find_honor)\n");
    //select
    printf("6. Find dumbass (find_dumbass)\n");
    //select
    printf("7. Find without marks (find_without_marks)\n");
    //select
    printf("8. Find your options (find_by_option)\n");
    printf("0. Exit\n");

    string input;
    cin >> input;
    if (input == "find_surname") {

    }
    else if (input == "find_id") {

    }
    else if (input == "find_group") {

    }
    else if (input == "find_average") {

    }
    else if (input == "find_honor") {

    }
    else if (input == "find_dumbass") {

    }
    else if (input == "find_without_marks") {

    }
    else if (input == "find_by_option") {

    }
    else if (input == "exit") {

    }
}

void show_sort_menu(sqlite3* db) {
    printf("Sort menu\n");
    //select
    printf("1. Sort student by surname (sort_by_sur)\n");
    //select
    printf("2. Sort student by name (sort_by_name)\n");
    //select
    printf("3. Sort students by age (sort_by_age)\n");
    //select
    printf("4. Sort studetns by avarage mark (sort_by_avemark)\n");
    //select
    printf("5. Sort studetns by skipped days (by_skipped_days)\n");
    //select
    printf("6. Sort with your options (by_option)\n");
    printf("0. Exit\n");

    string input;
    cin >> input;
    if (input == "sort_by_sur") {

    }
    else if (input == "sort_by_name") {

    }
    else if (input == "sort_by_age") {

    }
    else if (input == "sort_by_avemark") {

    }
    else if (input == "by_skipped_days") {

    }
    else if (input == "by_option") {

    }
    else if (input == "exit") {

    }
}

void show_statics_menu(sqlite3* db) {
    printf("Statistic menu\n");
    //select
    printf("1. Show general class statics (general)\n");
    //select
    printf("2. Show avarage marks by subjects (stud_ave_marks)\n");
    //select
    printf("3. Show honor students (good_stud)\n");
    //select
    printf("4. Show dumbass (dumbuss)\n");
    //select
    printf("5. Show number of studetns (number_studs)\n");
    //select
    printf("6. Show attendance (attend)\n");
    //select
    printf("7. Show stats with your options (your_options)\n");
    printf("0. Exit (exit)\n");

    string input;
    cin >> input;
    if (input == "general") {

    }
    else if (input == "stud_ave_marks") {

    }
    else if (input == "good_stud") {

    }
    else if (input == "dumbuss") {

    }
    else if (input == "number_studs") {

    }
    else if (input == "attend") {

    }
    else if (input == "your_options") {

    }
    else if (input == "exit") {

    }

}




void open_submenu(MainMenu cmd, sqlite3* db) {
    switch(cmd) {
        case TABLES:
            show_table_menu(db);
            break;
        case STUDENTS:
            show_student_menu(db);
            break;
        case GRADES:
            show_grades_menu(db);
            break;
        case SEARCH:
            show_find_menu(db);
            break;
        case SORT:
            show_sort_menu(db);
            break;
        case STATS:
            show_statics_menu(db);
            break;
    }
}


// string subjects;
// while (true) {
//     int a = 0;
//     add_field( subjects);
//     cout<<"Add another more fields?\n"<<"Push 1 to keep editing table or 0 to stop: ";
//     cin>>a;
//     if (a == 0) {
//         break;
//     }
// }
// cout<< subjects<<endl;