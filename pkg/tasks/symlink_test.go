package tasks_test

import (
	"errors"
	"fmt"
	"testing"

	"github.com/golang/mock/gomock"
	. "github.com/pseudomuto/dfiler/pkg/tasks"
	"github.com/stretchr/testify/suite"
)

type symlinkSuite struct {
	suite.Suite
	ctrl *gomock.Controller
	fs   *MockFS
	task Task
}

func TestSymlink(t *testing.T) {
	suite.Run(t, new(symlinkSuite))
}

func (s *symlinkSuite) SetupTest() {
	s.ctrl = gomock.NewController(s.T())
	s.fs = NewMockFS(s.ctrl)
	s.task = NewSymlink(s.fs, "target", "link", false)
}

func (s *symlinkSuite) TearDownTest() {
	s.ctrl.Finish()
}

func (s *symlinkSuite) TestNewSymlinkDir() {
	files := []string{
		".config",
		"file1.txt",
		"sub/file2.txt",
	}
	s.fs.EXPECT().Files("target").Return(files, nil)

	list, err := NewSymlinkDir(s.fs, "target", "link", false)
	s.Require().NoError(err)
	s.Require().Len(list.Tasks, len(files))

	for i, file := range files {
		s.Require().Equal(
			fmt.Sprintf("Symlink link/%s to target/%s", file, file),
			list.Tasks[i].String(),
		)
	}
}

func (s *symlinkSuite) TestString() {
	s.Require().Equal("Symlink link to target", s.task.String())
}

func (s *symlinkSuite) TestDo() {
	s.fs.EXPECT().Symlink("target", "link", false).Return(nil)
	s.Require().NoError(s.task.Do())

	s.fs.EXPECT().Symlink("target", "link", false).Return(nil)
	s.Require().NoError(s.task.Do())

	s.fs.EXPECT().Symlink("target", "link", true).Return(errors.New("Boom"))
	s.Require().EqualError(NewSymlink(s.fs, "target", "link", true).Do(), "Boom")
}

func (s *symlinkSuite) TestUndo() {
	s.fs.EXPECT().Abs("target").Return("target")
	s.fs.EXPECT().SymlinkTarget("link").Return("target", nil)
	s.fs.EXPECT().Remove("link").Return(nil)
	s.Require().NoError(s.task.Undo())

	// exists, but points to another file
	s.T().Run("wrong link target", func(t *testing.T) {
		s.fs.EXPECT().Abs("target").Return("/other/target")
		s.fs.EXPECT().SymlinkTarget("link").Return("target", nil)
		s.Require().NoError(s.task.Undo()) // no call to remove
	})

	s.T().Run("error removing file", func(t *testing.T) {
		s.fs.EXPECT().Abs("target").Return("target")
		s.fs.EXPECT().SymlinkTarget("link").Return("target", nil)
		s.fs.EXPECT().Remove("link").Return(errors.New("Boom"))
		s.Require().EqualError(s.task.Undo(), "Boom")
	})
}

func (s *symlinkSuite) TestIsDone() {
	s.fs.EXPECT().Abs("target").Return("target")
	s.fs.EXPECT().SymlinkTarget("link").Return("target", nil)
	s.Require().True(s.task.IsDone())

	s.fs.EXPECT().Abs("target").Return("/other/target")
	s.fs.EXPECT().SymlinkTarget("link").Return("target", nil)
	s.Require().False(s.task.IsDone())

	s.fs.EXPECT().SymlinkTarget("link").Return("", errors.New("Boom"))
	s.Require().False(s.task.IsDone())
}
