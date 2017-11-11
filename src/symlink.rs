use std::fmt;
use std::fs;
use std::os::unix::fs as nix_fs;
use std::path::PathBuf;

use errors::*;

pub struct Symlink {
    pub source: PathBuf,
    pub target: PathBuf,
}

impl fmt::Display for Symlink {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{} -> {}", self.source.display(), self.target.display())
    }
}

impl Symlink {
    pub fn new(source: PathBuf, target: PathBuf) -> Result<Self> {
        if source.is_relative() {
            return Err("`source` must be an absolute path".into());
        }

        if target.is_relative() {
            return Err("`target` must be an absolute path".into());
        }

        Ok(Symlink { source, target })
    }

    pub fn exists(&self) -> bool {
        if !(self.source.exists() && self.target.exists()) {
            return false;
        }

        fs::read_link(self.target.to_str().unwrap())
            .and_then(|path| {
                let parent = self.target.parent().unwrap().to_path_buf();

                expand_path(&path, &parent)
                    .and_then(|path| Ok(path == self.source))
                    .or_else(|_| Ok(false))
            })
            .unwrap_or(false)
    }

    pub fn create(&self) -> Result<()> {
        create_symlink(&self.source, &self.target)
    }
}

fn expand_path(path: &PathBuf, base_path: &PathBuf) -> Result<PathBuf> {
    if path.is_absolute() {
        return Ok(path.clone());
    }

    fs::canonicalize(base_path.join(path)).chain_err(|| "Unable to canonicalize path")
}

fn create_symlink(source: &PathBuf, target: &PathBuf) -> Result<()> {
    nix_fs::symlink(source, target).chain_err(|| "Error creating symlink")
}

#[cfg(test)]
mod test {
    use super::Symlink;
    use std::fs;
    use std::path::Path;
    use std::path::PathBuf;

    fn relative_path(path: &str) -> PathBuf {
        Path::new(env!("CARGO_MANIFEST_DIR")).join(path)
    }

    #[test]
    fn new_when_paths_are_absolute() {
        assert!(Symlink::new(PathBuf::from("/dotfiles"), PathBuf::from("/")).is_ok());
    }

    #[test]
    fn new_when_paths_not_absolute() {
        assert!(Symlink::new(PathBuf::from("./"), PathBuf::from("/")).is_err());
        assert!(Symlink::new(PathBuf::from("/"), PathBuf::from("./")).is_err());
    }

    #[test]
    fn exists_when_source_and_target_exist() {
        let link = Symlink::new(
            relative_path("fixture/source/agignore"),
            relative_path("fixture/target/.agignore"),
        ).unwrap();

        assert!(link.exists());
    }

    #[test]
    fn exists_when_source_and_or_target_dont_exist() {
        let mut link = Symlink::new(
            fs::canonicalize("./").unwrap(),
            fs::canonicalize("../").unwrap(),
        ).unwrap();

        link.source = PathBuf::from("./this_aint_real");
        assert_eq!(false, link.exists());

        link.source = PathBuf::from("/");
        link.target = PathBuf::from("./this_aint_real");
        assert_eq!(false, link.exists());

        link.source = PathBuf::from("./this_aint_real");
        link.target = PathBuf::from("./this_also_aint_real");
        assert_eq!(false, link.exists());
    }

    #[test]
    fn exists_when_target_exists_but_points_to_the_wrong_source() {
        let link = Symlink::new(
            relative_path("fixture/source/agignore"),
            relative_path("fixture/target/bin"),
        ).unwrap();

        // false, since it's pointing to the wrong place it should be updated
        assert_eq!(false, link.exists());
    }

    #[test]
    fn create_creates_the_symlink() {
        fs::remove_dir_all(relative_path("tmp/create")).ok();
        fs::create_dir_all(relative_path("tmp/create")).expect("Couldn't create tmp dir");

        let link = Symlink::new(
            relative_path("fixture/source/agignore"),
            relative_path("tmp/create/agignore"),
        ).unwrap();

        assert_eq!(false, link.exists());
        assert!(link.create().is_ok());
        assert!(link.exists());
    }
}
