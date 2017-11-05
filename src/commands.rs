use std::fmt;
use std::str::FromStr;

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

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        match s.to_lowercase().as_ref() {
            "symlinks" => Ok(Command::Symlinks),
            _ => Err("not a valid command"),
        }
    }
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
