#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <tuple>
#include <algorithm>
#include <set>

using std::vector;
using std::cout;
using std::cin;
using std::out_of_range;
using std::invalid_argument;
using std::ostream;
using std::istream;
using std::accumulate;
using std::string;
using std::map;
using std::set;
using std::count_if;
using std::unique;
using std::tuple;
using std::min;
using std::find_if;

enum class TaskStatus {
    NEW,
    IN_PROGRESS,
    TESTING,
    DONE
};

using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:

    const TasksInfo& GetPersonTasksInfo(const string& person) const{
        return tasks_per_person.at(person);
    }

    void AddNewTask(const string& person){
        tasks_per_person[person][TaskStatus::NEW]++;
    }

    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
            const string& person, int task_count){
        int tasks_to_update = min(this->get_unfinished_tasks_count(person), task_count);

        int new_count = tasks_per_person.at(person).at(TaskStatus::NEW);
        int in_progress_count = tasks_per_person.at(person)[TaskStatus::IN_PROGRESS];
        int testing_count = tasks_per_person.at(person)[TaskStatus::TESTING];
        int done_count = tasks_per_person.at(person)[TaskStatus::DONE];

        int new_to_in_progress = min(new_count, tasks_to_update);
        task_count -= new_to_in_progress;

        int in_progress_to_testing = min(in_progress_count, task_count);

        task_count -= in_progress_to_testing;
        int testing_to_done = min(testing_count, task_count);

        TasksInfo updated_tasks;
        TasksInfo untouched_tasks;

        int left_new_count = new_count - new_to_in_progress;
        tasks_per_person[person][TaskStatus::NEW] = left_new_count;
        if (left_new_count > 0 && new_to_in_progress != 0)
            untouched_tasks[TaskStatus::NEW] = left_new_count;
        if (new_to_in_progress != 0)
            updated_tasks[TaskStatus::IN_PROGRESS] = new_to_in_progress;

        int left_in_progress_count = in_progress_count - in_progress_to_testing;
        tasks_per_person[person][TaskStatus::IN_PROGRESS] = left_in_progress_count + new_to_in_progress;
        if (left_in_progress_count > 0 && in_progress_to_testing != 0)
            untouched_tasks[TaskStatus::IN_PROGRESS] = left_in_progress_count;
        if (in_progress_to_testing != 0)
            updated_tasks[TaskStatus::TESTING] = in_progress_to_testing;

        int left_in_testing_count = testing_count - testing_to_done;
        tasks_per_person[person][TaskStatus::TESTING] = left_in_testing_count + in_progress_to_testing;
        tasks_per_person[person][TaskStatus::DONE] = done_count + testing_to_done;
        if (left_in_testing_count > 0 && testing_to_done != 0)
            untouched_tasks[TaskStatus::TESTING] = left_in_testing_count;

        if (testing_to_done != 0) {
            updated_tasks[TaskStatus::DONE] = testing_to_done;
        }

        return tie(updated_tasks, untouched_tasks);
    }
private:

    map<string, TasksInfo> tasks_per_person;

    int get_unfinished_tasks_count(const string& person) {
        if(tasks_per_person.count(person) == 0)
            return 0;

        int new_count = tasks_per_person.at(person)[TaskStatus::NEW];
        int in_progress_count = tasks_per_person.at(person)[TaskStatus::IN_PROGRESS];
        int testing_count = tasks_per_person.at(person)[TaskStatus::TESTING];
        return new_count + in_progress_count + testing_count;
    }
};

void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
         ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
         ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
         ", " << tasks_info[TaskStatus::DONE] << " tasks are done\n";
}



int main() {
    /*TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));*/

    return 0;
}
