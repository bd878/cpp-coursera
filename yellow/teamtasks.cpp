#include <iostream>
#include <tuple>
#include <map>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std;

class TeamTasks {
private:
  map<string, TasksInfo> tasks;
public:
  const TasksInfo& GetPersonTasksInfo(const string& person) const;
  void AddNewTask(const string& person);
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count);
};

const TasksInfo& TeamTasks::GetPersonTasksInfo(const string& person) const {
  return tasks.at(person);
}

void TeamTasks::AddNewTask(const string& person) {
  ++tasks[person][TaskStatus::NEW];
}

TaskStatus shiftStatus(TaskStatus status) {
  return static_cast<TaskStatus>(static_cast<int>(status) + 1);
}

void removeEmptyTasks(TasksInfo& tasks) {
  vector<TaskStatus> empty_statuses;
  for (const auto& [status, count] : tasks)
    if (count == 0)
      empty_statuses.push_back(status);

  for (TaskStatus status_to_erase : empty_statuses)
    tasks.erase(status_to_erase);
}

tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(const string& person, int task_count) {
  TasksInfo updated_tasks;
  TasksInfo unupdated_tasks;

  TasksInfo& person_tasks = tasks.at(person);
  for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = shiftStatus(status)) {
    int updated_count = min(task_count, person_tasks[status]);

    updated_tasks[shiftStatus(status)] = updated_count;
    unupdated_tasks[status] = person_tasks[status] - updated_count;

    task_count -= updated_count;
  }

  for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = shiftStatus(status)) {
    person_tasks[status] = unupdated_tasks[status] + updated_tasks[status];
  }

  removeEmptyTasks(updated_tasks);
  removeEmptyTasks(unupdated_tasks);
  removeEmptyTasks(person_tasks);

  return {updated_tasks, unupdated_tasks};
}