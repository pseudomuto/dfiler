package tasks_test

import (
	"errors"
	"testing"

	. "github.com/pseudomuto/dfiler/pkg/tasks"
	"github.com/stretchr/testify/require"
)

func TestTaskListDo(t *testing.T) {
	tests := []struct {
		name  string
		tasks []Task
		err   error
		done  bool
	}{
		{
			name: "Do all tasks",
			tasks: []Task{
				&testTask{},
				&testTask{},
				&testTask{},
			},
			done: true,
		},
		{
			name: "Only pending tasks",
			tasks: []Task{
				&testTask{},
				// if do were called, this would go "Boom"
				&testTask{do: errors.New("Boom"), done: true},
				&testTask{},
			},
			done: true,
		},
		{
			name: "task errors",
			tasks: []Task{
				&testTask{do: errors.New("Boom")},
				&testTask{},
			},
			err:  errors.New("Boom"),
			done: false,
		},
	}

	for _, tt := range tests {
		list := TaskList{Name: tt.name, Tasks: tt.tasks}
		require.Equal(t, tt.err, list.Do(), tt.name)
		require.Equal(t, tt.done, list.IsDone(), tt.name)
	}
}

func TestTaskListUndo(t *testing.T) {
	tests := []struct {
		name  string
		tasks []Task
		err   error
		done  bool
	}{
		{
			name: "Undo all tasks",
			tasks: []Task{
				&testTask{done: true},
				&testTask{done: true},
				&testTask{done: true},
			},
			done: false,
		},
		{
			name: "task errors",
			tasks: []Task{
				&testTask{undo: errors.New("Boom"), done: true},
				&testTask{done: true},
			},
			err:  errors.New("Boom"),
			done: true,
		},
	}

	for _, tt := range tests {
		list := TaskList{Name: tt.name, Tasks: tt.tasks}
		require.Equal(t, tt.err, list.Undo(), tt.name)
		require.Equal(t, tt.done, list.IsDone(), tt.name)
	}
}

func TestTaskListIsDone(t *testing.T) {
	tests := []struct {
		name   string
		tasks  []Task
		result bool
	}{
		{
			name: "all pending",
			tasks: []Task{
				&testTask{},
				&testTask{},
				&testTask{},
			},
		},
		{
			name: "some pending",
			tasks: []Task{
				&testTask{done: true},
				&testTask{},
				&testTask{done: true},
			},
		},
		{
			name: "some pending",
			tasks: []Task{
				&testTask{done: true},
				&testTask{done: true},
				&testTask{done: true},
			},
			result: true,
		},
	}

	for _, tt := range tests {
		list := TaskList{Name: tt.name, Tasks: tt.tasks}
		require.Equal(t, tt.result, list.IsDone())
	}
}

func TestTaskListPendingTasks(t *testing.T) {
	list := TaskList{
		Name: "test list",
		Tasks: []Task{
			&testTask{done: true},
			&testTask{},
			&testTask{done: true},
		},
	}

	require.Len(t, list.PendingTasks(), 1)
}

func TestTaskListCompletedTasks(t *testing.T) {
	list := TaskList{
		Name: "test list",
		Tasks: []Task{
			&testTask{done: true},
			&testTask{},
			&testTask{done: true},
		},
	}

	require.Len(t, list.CompletedTasks(), 2)
}

type testTask struct {
	do   error
	undo error
	done bool
}

func (tt *testTask) IsDone() bool   { return tt.done }
func (tt *testTask) String() string { return "TestTask" }

func (tt *testTask) Do() error {
	if tt.do == nil {
		tt.done = true
	}

	return tt.do
}

func (tt *testTask) Undo() error {
	if tt.undo == nil {
		tt.done = false
	}

	return tt.undo
}
