#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

enum TaskStatus
{
    toDo,
    inProgress,
    done
};

class Task
{
public:
    Task(const std::string &name) : name(name), status(TaskStatus::toDo) {}

    void complete()
    {
        status = TaskStatus::done;
    }

    void uncomplete()
    {
        status = TaskStatus::toDo;
    }

    void startProgress()
    {
        status = TaskStatus::inProgress;
    }

    const std::string &getName() const
    {
        return name;
    }

    TaskStatus getStatus() const
    {
        return status;
    }

private:
    std::string name;
    TaskStatus status;
};

class ToDoList
{
public:
    void addTask(const Task &task)
    {
        tasks.push_back(task);
    }

    void removeTask(const std::string &taskName)
    {
        tasks.erase(std::remove_if(tasks.begin(), tasks.end(),
                                   [taskName](const Task &task)
                                   { return task.getName() == taskName; }),
                    tasks.end());
    }

    Task *getTask(const std::string &taskName)
    {
        for (auto &task : tasks)
        {
            if (task.getName() == taskName)
            {
                return &task;
            }
        }
        return nullptr;
    }

    void completeTask(const std::string &taskName)
    {
        Task *task = getTask(taskName);
        if (task)
        {
            task->complete();
        }
    }

    void uncompleteTask(const std::string &taskName)
    {
        Task *task = getTask(taskName);
        if (task)
        {
            task->uncomplete();
        }
    }

    void startProgress(const std::string &taskName)
    {
        Task *task = getTask(taskName);
        if (task)
        {
            task->startProgress();
        }
    }

    const std::vector<Task> &getTasks() const
    {
        return tasks;
    }

private:
    std::vector<Task> tasks;
};

void runTests()
{
    ToDoList todo;

    Task task1("Task 1");
    Task task2("Task 2");

    todo.addTask(task1);
    todo.addTask(task2);

    assert(todo.getTasks().size() == 2);

    todo.startProgress("Task 1");
    assert(todo.getTask("Task 1")->getStatus() == TaskStatus::inProgress);

    todo.completeTask("Task 1");
    assert(todo.getTask("Task 1")->getStatus() == TaskStatus::done);

    todo.uncompleteTask("Task 1");
    assert(todo.getTask("Task 1")->getStatus() == TaskStatus::toDo);

    todo.removeTask("Task 1");
    assert(todo.getTasks().size() == 1);
}

int main()
{
    runTests();
    std::cout << "All tests completed successfully!" << std::endl;
    return 0;
}
