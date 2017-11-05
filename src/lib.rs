#![deny(missing_docs)]

//! A tool for managing dotfiles and packages for 'nix systems.
//!
//! dfiler makes it easy to ensure your dotfiles and software packages are testable, and
//! reproduceable on your Linux and OSX machines.
//!
//! TODO: Talk about how it works, and how to configure it.

extern crate clap;
#[macro_use]
extern crate error_chain;

use clap::{App, Arg, ArgMatches};

mod commands;
pub use commands::Command;

mod context;
pub use context::Context;

/// Library specific errors.
///
/// This uses the error-chain crate to wrap errors and expose custom `Error`, `ErrorKind`,
/// `ResultExt`, and `Result` types.
pub mod errors {
    error_chain!{}
}

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
        .arg_from_usage("-l, --symlinks-only, 'only handle symlinks'")
        .arg_from_usage("-n, --dry-run, 'See what would happen, but don\'t run anything'")
        .get_matches_from(args)
}
