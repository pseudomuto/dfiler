package tasks

// Task describes a unit of work
type Task interface {
	Do() error
	Undo() error
	IsDone() bool
	String() string
}

// TaskList describes a group of related tasks.
type TaskList struct {
	Name  string
	Tasks []Task
}

// Do runs Do on all pending tasks.
func (tl *TaskList) Do() error {
	for _, task := range tl.PendingTasks() {
		if err := task.Do(); err != nil {
			return err
		}
	}

	return nil
}

// Undo runs Undo on all tasks in the list.
func (tl *TaskList) Undo() error {
	for _, task := range tl.Tasks {
		if err := task.Undo(); err != nil {
			return err
		}
	}

	return nil
}

// IsDone returns true if there are no pending tasks.
func (tl *TaskList) IsDone() bool {
	return len(tl.PendingTasks()) == 0
}

// String returns the name of this list.
func (tl *TaskList) String() string {
	return tl.Name
}

// PendingTasks returns only tasks where IsDone returns false
func (tl *TaskList) PendingTasks() []Task {
	tasks := []Task{}
	for _, t := range tl.Tasks {
		if t.IsDone() {
			continue
		}

		tasks = append(tasks, t)
	}

	return tasks
}
