use std::fs;
use std::path::PathBuf;

use errors::*;

/// The Context struct contains details about the current run, like source/target paths, and
/// whether or not this is a dry run.
pub struct Context {
    /// The source path containing the dfiler.yml and source files
    pub source_path: PathBuf,
    /// The target path to create symlinks in
    pub target_path: PathBuf,
    /// Whether or not this is a dry run (won't apply any changes)
    pub dry_run: bool,
}

impl Context {
    /// Creates a new context object for an invocation.
    ///
    /// # Examples
    ///
    /// ```
    /// # extern crate dfiler;
    /// let ctx = dfiler::Context::new("./", "../", true).unwrap();
    /// ```
    pub fn new(source_path: &str, target_path: &str, dry_run: bool) -> Result<Self> {
        let context = Context {
            source_path: fs::canonicalize(source_path).chain_err(|| "Source path doesn't exist")?,
            target_path: fs::canonicalize(target_path).chain_err(|| "Target path doesn't exist")?,
            dry_run,
        };

        Ok(context)
    }
}

#[cfg(test)]
mod test {
    use super::Context;

    #[test]
    fn new() {
        // both directories exist
        assert!(Context::new("./", "../", true).is_ok());

        // source dir doesn't exist
        assert!(Context::new("./nothere", "../", true).is_err());

        // target dir doesn't exist
        assert!(Context::new("./", "./nothere", true).is_err());
    }
}
