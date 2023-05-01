//
// Created by Legion on 5/1/2023.
//

#ifndef YELLOW_BELT_CPP_TASKTRACKER_H
#define YELLOW_BELT_CPP_TASKTRACKER_H

#include <iostream>
#include <map>
#include <iostream>
#include <sstream>
#include <vector>

enum class TaskStatus {
    NEW,
    IN_PROGRESS,
    TESTING,
    DONE
};

using TasksInfo = std::map<TaskStatus, int>;

std::ostream& operator <<(std::ostream& out, const TaskStatus& status) {
    std::string statusName;
    switch (status) {
        case TaskStatus::NEW:
            statusName = "\"NEW\"";
            break;
        case TaskStatus::IN_PROGRESS:
            statusName = "\"IN_PROGRESS\"";
            break;
        case TaskStatus::TESTING:
            statusName = "\"TESTING\"";
            break;
        case TaskStatus::DONE:
            statusName = "\"DONE\"";
            break;
    }
    return out << statusName;
}

class TeamTasks {
public:

    const TasksInfo& GetPersonTasksInfo(const std::string& person) const{
        return tasks_per_person.at(person);
    }

    void AddNewTask(const std::string& person){
        if (tasks_per_person.count(person) == 0) {
            tasks_per_person[person][TaskStatus::NEW] = 0;
        }
        tasks_per_person[person][TaskStatus::NEW]++;
    }

    std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(
            const std::string& person, int task_count){

        TasksInfo updated_tasks;
        TasksInfo untouched_tasks;
        if (tasks_per_person.count(person) == 0)
            return tie(updated_tasks, untouched_tasks);
        int tasks_to_update = std::min(this->get_unfinished_tasks_count(person), task_count);

        int new_count = tasks_per_person.at(person).at(TaskStatus::NEW);
        int in_progress_count = tasks_per_person.at(person)[TaskStatus::IN_PROGRESS];
        int testing_count = tasks_per_person.at(person)[TaskStatus::TESTING];
        int done_count = tasks_per_person.at(person)[TaskStatus::DONE];

        int new_to_in_progress = std::min(new_count, tasks_to_update);
        task_count -= new_to_in_progress;

        int in_progress_to_testing = std::min(in_progress_count, task_count);

        task_count -= in_progress_to_testing;
        int testing_to_done = std::min(testing_count, task_count);

        int left_new_count = new_count - new_to_in_progress;
        tasks_per_person[person][TaskStatus::NEW] = left_new_count;
        erase_if_empty(person, TaskStatus::NEW);

        if (left_new_count > 0 && new_to_in_progress != 0)
            untouched_tasks[TaskStatus::NEW] = left_new_count;
        if (new_to_in_progress != 0)
            updated_tasks[TaskStatus::IN_PROGRESS] = new_to_in_progress;

        int left_in_progress_count = in_progress_count - in_progress_to_testing;
        tasks_per_person[person][TaskStatus::IN_PROGRESS] = left_in_progress_count + new_to_in_progress;
        erase_if_empty(person, TaskStatus::IN_PROGRESS);

        if (left_in_progress_count > 0)
            untouched_tasks[TaskStatus::IN_PROGRESS] = left_in_progress_count;
        if (in_progress_to_testing != 0)
            updated_tasks[TaskStatus::TESTING] = in_progress_to_testing;

        int left_in_testing_count = testing_count - testing_to_done;
        tasks_per_person[person][TaskStatus::TESTING] = left_in_testing_count + in_progress_to_testing;
        tasks_per_person[person][TaskStatus::DONE] = done_count + testing_to_done;
        erase_if_empty(person, TaskStatus::TESTING);
        erase_if_empty(person, TaskStatus::DONE);
        if (left_in_testing_count > 0)
            untouched_tasks[TaskStatus::TESTING] = left_in_testing_count;

        if (testing_to_done != 0) {
            updated_tasks[TaskStatus::DONE] = testing_to_done;
        }
        return tie(updated_tasks, untouched_tasks);
    }

    void Set (std::string p, TasksInfo info) {
        tasks_per_person[p] = info;
    }
private:

    std::map<std::string, TasksInfo> tasks_per_person;

    int get_unfinished_tasks_count(const std::string& person) {
        if(tasks_per_person.count(person) == 0)
            return 0;

        int new_count = tasks_per_person.at(person)[TaskStatus::NEW];
        int in_progress_count = tasks_per_person.at(person)[TaskStatus::IN_PROGRESS];
        int testing_count = tasks_per_person.at(person)[TaskStatus::TESTING];
        return new_count + in_progress_count + testing_count;
    }
    void erase_if_empty(const std::string& person, TaskStatus status){
        if(tasks_per_person.at(person)[status] == 0)
            tasks_per_person.at(person).erase(status);
    }
};

template <typename Collection>
std::string Join(const Collection& c, const std::string& d) {
    std::stringstream ss;
    bool isFirst = true;
    for (const auto& i : c) {
        if(!isFirst) {
            ss << d;
        }
        isFirst = false;
        ss << i;
    }
    return ss.str();
}
template <typename F, typename S>
std::ostream& operator <<(std::ostream& out, const std::pair<F,S>& p) {
    return out << p.first << ": " << p.second;
}
template <typename K, typename V>
std::ostream& operator <<(std::ostream& out, const std::map<K,V>& m){
    return out << '{' << Join(m, ", ") << '}';
}
template <typename T>
std::ostream& operator <<(std::ostream& out, const std::vector<T>& v) {
    return out << '['  << Join(v, ", ") << ']';
}


void PrintTasksInfo(TasksInfo tasks_info) {
    std::cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
         ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
         ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
         ", " << tasks_info[TaskStatus::DONE] << " tasks are done\n";
}

void test(){
    TasksInfo info{
            {TaskStatus::NEW,10},
            {TaskStatus::IN_PROGRESS,10},
            {TaskStatus::TESTING,10},
            {TaskStatus::DONE,10}
    };

    TeamTasks tasks;

    tasks.Set("anna", info);

    while (std::cin) {
        std::string command, person;
        int num;
        std::cin >> command >> person;
        if (command == "add") {
            std::cin >> num;
            while (num--)
                tasks.AddNewTask(person);
            std::cout << "[]" << std::endl;
        } else if (command == "perform") {
            std::cin >> num;
            TasksInfo updated_tasks, untouched_tasks;
            tie(updated_tasks, untouched_tasks) =
                    tasks.PerformPersonTasks(person, num);
            std::cout << std::vector<TasksInfo>{updated_tasks, untouched_tasks} << std::endl;
        } else if (command == "get_info") {
            std::cout << tasks.GetPersonTasksInfo(person) << std::endl;
        } else if (command.size() && command[0] != '#') {
            throw std::invalid_argument("wrong command: " + command);
        }
    }
}

#endif //YELLOW_BELT_CPP_TASKTRACKER_H
