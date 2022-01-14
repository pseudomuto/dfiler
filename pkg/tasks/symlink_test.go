package tasks_test

import (
	"errors"
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
	s.fs.EXPECT().Remove("link").Return(nil)
	s.Require().NoError(s.task.Undo())

	s.fs.EXPECT().Remove("link").Return(errors.New("Boom"))
	s.Require().EqualError(s.task.Undo(), "Boom")
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

// func TestSymlink(t *testing.T) {
// dir := t.TempDir()

// t.Run("String", func(t *testing.T) {
// target := filepath.Join("testdata", "target.txt")
// link := filepath.Join(dir, t.Name())
// slink := NewSymlink(target, link, false)

// target, _ = filepath.Abs(target)
// link, _ = filepath.Abs(link)
// require.Equal(t, fmt.Sprintf("Symlink %s to %s", link, target), slink.String())
// })

// t.Run("IsDone", func(t *testing.T) {
// target := filepath.Join("testdata", "target.txt")
// link := filepath.Join(dir, t.Name())
// slink := NewSymlink(target, link, false)
// require.False(t, slink.IsDone())

// require.NoError(t, os.MkdirAll(filepath.Dir(link), os.ModePerm))
// require.NoError(t, os.Symlink(target, link))
// require.True(t, slink.IsDone())
// })

// t.Run("Do", func(t *testing.T) {
// target := filepath.Join("testdata", "target.txt")
// link := filepath.Join(dir, t.Name())
// slink := NewSymlink(target, link, false)

// require.NoError(t, slink.Do())
// require.True(t, slink.IsDone())

// // without force, error
// require.Error(t, slink.Do())

// // force will create it no matter what
// slink = NewSymlink(target, link, true)
// require.NoError(t, slink.Do())
// })

// t.Run("Undo", func(t *testing.T) {
// target := filepath.Join("testdata", "target.txt")
// link := filepath.Join(dir, t.Name())
// slink := NewSymlink(target, link, false)

// // can't undo what  hasn't been done
// require.Error(t, slink.Undo())

// require.NoError(t, slink.Do())
// require.NoError(t, slink.Undo())
// require.False(t, slink.IsDone())
// })
// }
