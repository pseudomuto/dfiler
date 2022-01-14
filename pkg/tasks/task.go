package tasks

// TaskList describes a group of related tasks.
type TaskList struct {
	Name  string
	Tasks []Task
}

// Task describes a unit of work
type Task interface {
	Do() error
	Undo() error
	IsDone() bool
	String() string
}
