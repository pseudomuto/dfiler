#![deny(missing_docs)]

//! A tool for managing dotfiles and packages for 'nix systems.
//!
//! dfiler makes it easy to ensure your dotfiles and software packages are testable, and
//! reproduceable on your Linux and OSX machines.
//!
//! TODO: Talk about how it works, and how to configure it.

extern crate clap;

use clap::{App, Arg, ArgMatches};

/// Parses the command line args and returns an appropriate `clap::ArgMatches` object.
///
/// # Examples
///
/// ```no_run
/// # extern crate dfiler;
/// use std::env;
///
/// let matches = dfiler::run(env::args().skip(1).collect());
/// // do something with the matches...
/// ```
pub fn run<'a>(args: Vec<String>) -> ArgMatches<'a> {
    App::new("dfiler")
        .version(env!("CARGO_PKG_VERSION"))
        .author(env!("CARGO_PKG_AUTHORS"))
        .about(env!("CARGO_PKG_DESCRIPTION"))
        .arg(
            Arg::with_name("source")
                .short("s")
                .long("source")
                .help("The source directory")
                .value_name("DIR")
                .takes_value(true)
                .default_value("./"),
        )
        .arg(
            Arg::with_name("target")
                .short("t")
                .long("target")
                .help("The target directory")
                .value_name("DIR")
                .takes_value(true)
                .default_value("$HOME"),
        )
        .arg(Arg::with_name("packages-only").help("Only run packages task"))
        .arg(Arg::with_name("symlinks-only").help("Only run symlinks task"))
        .arg(Arg::with_name("dry-run").help("Don't run tasks, just show what would be done"))
        .get_matches_from(args)
}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}
