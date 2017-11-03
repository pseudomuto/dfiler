#![deny(missing_docs)]

//! A tool for managing dotfiles and packages for 'nix systems.
//!
//! dfiler makes it easy to ensure your dotfiles and software packages are testable, and
//! reproduceable on your Linux and OSX machines.
//!
//! TODO: Talk about how it works, and how to configure it.

extern crate clap;

use clap::{App, AppSettings, ArgMatches};

/// Parses the command line args and returns an appropriate `clap::ArgMatches` object.
///
/// # Examples
///
/// ```no_run
/// # extern crate dfiler;
/// let matches = dfiler::run();
/// // do something with the matches...
/// ```
pub fn run<'a>() -> ArgMatches<'a>{
    App::new("dfiler")
        .setting(AppSettings::SubcommandRequiredElseHelp)
        .version(env!("CARGO_PKG_VERSION"))
        .author(env!("CARGO_PKG_AUTHORS"))
        .about(env!("CARGO_PKG_DESCRIPTION"))
        .get_matches()
}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}
