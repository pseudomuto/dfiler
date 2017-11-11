use std::fmt;
use std::result;
use std::str::FromStr;

use config::Config;
use context::Context;
use errors::*;
use symlink::Symlink;

static PLACEHOLDER: &'static str = "_";

/// A enumeration representing the commands that can be run.
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum Command {
    /// The symlinks command is used to create symlinks for dotfiles, etc.
    Symlinks,
}

impl fmt::Display for Command {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        fmt::Debug::fmt(self, f)
    }
}

impl FromStr for Command {
    type Err = &'static str;

    fn from_str(s: &str) -> result::Result<Self, Self::Err> {
        match s.to_lowercase().as_ref() {
            "symlinks" => Ok(Command::Symlinks),
            _ => Err("not a valid command"),
        }
    }
}

impl Command {
    /// Executes the command
    pub fn execute(self, ctx: &Context, config: &Config) -> Result<()> {
        match self {
            Command::Symlinks => create_symlinks(ctx, config),
        }
    }
}

fn create_symlinks(ctx: &Context, config: &Config) -> Result<()> {
    for (source, target) in &config.symlinks {
        let mut link = Symlink::new(ctx.source_path.join(source), ctx.target_path.join(target))?;

        if target == PLACEHOLDER {
            link.target = ctx.target_path.join(source);
        }

        if !link.exists() {
            link.create()?;
        }
    }

    Ok(())
}

#[cfg(test)]
mod test {
    use super::Command;

    #[test]
    fn command_display_and_debug() {
        assert_eq!("Found Symlinks", format!("Found {}", Command::Symlinks));
        assert_eq!("Found Symlinks", format!("Found {:?}", Command::Symlinks));
    }

    #[test]
    fn command_from_string() {
        let positive = vec!["symlinks", "symLinks", "SYMLINKS"];
        let negative = vec![" symlinks", "unknown"];

        for test in &positive {
            assert_eq!(Ok(Command::Symlinks), test.parse());
        }

        for test in &negative {
            // type hint necessary for error type
            assert!(test.parse::<Command>().is_err());
        }
    }
}
