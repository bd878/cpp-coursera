#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <unordered_map>
#include <tuple>
#include <set>

using namespace std;

// Перечислимый тип для статуса задачи
// enum class TaskStatus {
//   NEW,          // новая
//   IN_PROGRESS,  // в разработке
//   TESTING,      // на тестировании
//   DONE          // завершена
// };

TaskStatus Next(TaskStatus status) {
  return static_cast<TaskStatus>(static_cast<int>(status) + 1);
}

// Объявляем тип-синоним для map<TaskStatus, int>,
// // позволяющего хранить количество задач каждого статуса
// using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
private:
  unordered_map<string, TasksInfo> stats;

  void RemoveEmptyTasks(TasksInfo& tasks) {
    for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = Next(status)) {
      if (tasks[status] == 0) {
        tasks.erase(status);
      }
    }

    if (tasks[TaskStatus::DONE] == 0) {
      tasks.erase(TaskStatus::DONE);
    }
  }
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const {
    return stats.at(person);
  }

  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person) {
    stats[person][TaskStatus::NEW]++;
  }
  
  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
    TasksInfo person_tasks = stats[person];

    TasksInfo undone_tasks, performed_tasks;
    for (
      TaskStatus status = TaskStatus::NEW;
      status != TaskStatus::DONE && task_count > 0;
      status = Next(status)
    ) {
      undone_tasks[status] = min(person_tasks[status], task_count);
      performed_tasks[Next(status)] = undone_tasks[status];
      task_count -= person_tasks[status];
    }

    TasksInfo untouched_tasks;
    for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = Next(status)) {
      untouched_tasks[status] = person_tasks[status] - undone_tasks[status];
      stats[person][status] -= undone_tasks[status];
      stats[person][Next(status)] += performed_tasks[Next(status)];
    }

    RemoveEmptyTasks(stats[person]);
    RemoveEmptyTasks(untouched_tasks);
    RemoveEmptyTasks(performed_tasks);

    return {performed_tasks, untouched_tasks};
  }
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
// void PrintTasksInfo(TasksInfo tasks_info) {
//   cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
//       ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
//       ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
//       ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
// }

// int main() {
//   TeamTasks tasks;
//   tasks.AddNewTask("Ilia");
//   for (int i = 0; i < 3; ++i) {
//     tasks.AddNewTask("Ivan");
//   }
//   cout << "Ilia's tasks: ";
//   PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
//   cout << "Ivan's tasks: ";
//   PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  
//   TasksInfo updated_tasks, untouched_tasks;
  
//   tie(updated_tasks, untouched_tasks) =
//       tasks.PerformPersonTasks("Ivan", 2);
//   cout << "Updated Ivan's tasks: ";
//   PrintTasksInfo(updated_tasks);
//   cout << "Untouched Ivan's tasks: ";
//   PrintTasksInfo(untouched_tasks);
  
//   tie(updated_tasks, untouched_tasks) =
//       tasks.PerformPersonTasks("Ivan", 2);
//   cout << "Updated Ivan's tasks: ";
//   PrintTasksInfo(updated_tasks);
//   cout << "Untouched Ivan's tasks: ";
//   PrintTasksInfo(untouched_tasks);

//   return 0;
// }