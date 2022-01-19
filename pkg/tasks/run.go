package tasks

type RunOptions struct {
	DryRun  bool
	Undo    bool
	Before  func(t Task) error
	After   func(t Task, err error) error
	NoTasks func()
}

func RunTaskList(tl *TaskList, opts RunOptions) error {
	tasks := tl.PendingTasks()
	if opts.Undo {
		tasks = tl.CompletedTasks()
	}

	if len(tasks) == 0 {
		if opts.NoTasks != nil {
			opts.NoTasks()
		}

		return nil
	}

	for _, t := range tasks {
		if err := runTask(t, &opts); err != nil {
			return err
		}
	}

	return nil
}

func runTask(t Task, opts *RunOptions) error {
	if opts.Before != nil {
		if err := opts.Before(t); err != nil {
			return err
		}
	}

	fn := t.Do
	if opts.Undo {
		fn = t.Undo
	}

	var err error
	if !opts.DryRun {
		err = fn()
	}

	if opts.After != nil {
		if err := opts.After(t, err); err != nil {
			return err
		}
	}

	return nil
}
