package tasks_test

import (
	"errors"
	"testing"

	. "github.com/pseudomuto/dfiler/pkg/tasks"
	"github.com/stretchr/testify/require"
)

func TestRunTaskList(t *testing.T) {
	tests := []struct {
		name    string
		tasks   TaskList
		opts    *testOptions
		wantErr error
	}{
		{
			name: "no tasks",
			opts: newTestOptions(1, 0, 0, nil, nil, false),
		},
		{
			name: "some tasks",
			tasks: TaskList{
				Tasks: []Task{
					&testTask{done: true},
					&testTask{},
					&testTask{done: true},
				},
			},
			opts: newTestOptions(0, 1, 1, nil, nil, false),
		},
		{
			name: "some tasks to undo",
			tasks: TaskList{
				Tasks: []Task{
					&testTask{done: true},
					&testTask{},
					&testTask{done: true},
				},
			},
			opts: newTestOptions(0, 2, 2, nil, nil, true),
		},
		{
			name: "before errors",
			tasks: TaskList{
				Tasks: []Task{&testTask{}},
			},
			opts:    newTestOptions(0, 1, 0, errors.New("BeforeBoom"), nil, false),
			wantErr: errors.New("BeforeBoom"),
		},
		{
			name: "after errors",
			tasks: TaskList{
				Tasks: []Task{&testTask{}},
			},
			opts:    newTestOptions(0, 1, 1, nil, errors.New("AfterBoom"), false),
			wantErr: errors.New("AfterBoom"),
		},
		{
			name: "do errors",
			tasks: TaskList{
				Tasks: []Task{&testTask{do: errors.New("DoBoom")}},
			},
			opts:    newTestOptions(0, 1, 1, nil, nil, false),
			wantErr: errors.New("DoBoom"),
		},
		{
			name: "undo errors",
			tasks: TaskList{
				Tasks: []Task{&testTask{done: true, undo: errors.New("UndoBoom")}},
			},
			opts:    newTestOptions(0, 1, 1, nil, nil, true),
			wantErr: errors.New("UndoBoom"),
		},
	}

	for _, tt := range tests {
		require.Equal(t, tt.wantErr, RunTaskList(&tt.tasks, tt.opts.runOpts), tt.name)

		require.Equal(t, tt.opts.emptyCount, tt.opts.expEmptyCount, tt.name)
		require.Equal(t, tt.opts.beforeCount, tt.opts.expBeforeCount, tt.name)
		require.Equal(t, tt.opts.afterCount, tt.opts.expAfterCount, tt.name)
	}
}

type testOptions struct {
	emptyCount     int
	expEmptyCount  int
	beforeCount    int
	beforeErr      error
	expBeforeCount int
	afterCount     int
	afterErr       error
	expAfterCount  int
	runOpts        RunOptions
}

func newTestOptions(ec, bc, ac int, be error, ae error, undo bool) *testOptions {
	opts := &testOptions{
		expEmptyCount:  ec,
		expBeforeCount: bc,
		expAfterCount:  ac,
		beforeErr:      be,
		afterErr:       ae,
	}

	opts.runOpts = RunOptions{
		Undo:    undo,
		NoTasks: func() { opts.emptyCount++ },
		Before: func(t Task) error {
			opts.beforeCount++
			return opts.beforeErr
		},
		After: func(t Task, err error) error {
			opts.afterCount++
			if err != nil {
				return err
			}

			return opts.afterErr
		},
	}

	return opts
}
