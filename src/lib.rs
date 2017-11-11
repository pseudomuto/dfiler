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
#[macro_use]
extern crate log;
#[macro_use]
extern crate serde_derive;
extern crate serde_yaml;

use std::env;

use clap::{App, AppSettings, Arg};

mod commands;
pub use commands::Command;

mod config;
pub use config::Config;

mod context;
pub use context::Context;

mod symlink;

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
/// if let Err(error) = dfiler::run(env::args().skip(1).collect()) {
///     println!("Got an error: {}", error);
/// }
/// ```
pub fn run(args: Vec<String>) -> errors::Result<()> {
    let default_source = env::current_dir().unwrap().to_str().unwrap().to_owned();
    let default_target = env::home_dir().unwrap().to_str().unwrap().to_owned();

    let matches = new_app(&default_source, &default_target).get_matches_from(args);
    let context = Context::new(
        matches.value_of("source").unwrap(), // unwrap is safe due to default
        matches.value_of("target").unwrap(), // unwrap is safe due to default
        matches.is_present("dry-run"),
    )?;

    let config = Config::from_yaml_file(&context.source_path.join("dfiler.yml"))?;

    // TODO: you know...all the things...which commands, etc.
    Command::Symlinks
        .execute(&context, &config)
        .unwrap_or_else(|e| error!("{}", e));

    Ok(())
}

fn new_app<'a, 'b>(default_source: &'a str, default_target: &'a str) -> App<'a, 'b> {
    App::new("dfiler")
        .version(env!("CARGO_PKG_VERSION"))
        .author(env!("CARGO_PKG_AUTHORS"))
        .about(env!("CARGO_PKG_DESCRIPTION"))
        .setting(AppSettings::GlobalVersion)
        .setting(AppSettings::NoBinaryName)
        .setting(AppSettings::UnifiedHelpMessage)
        .arg(
            Arg::with_name("source")
                .short("s")
                .long("source")
                .help("The source directory")
                .value_name("DIR")
                .takes_value(true)
                .default_value(default_source),
        )
        .arg(
            Arg::with_name("target")
                .short("t")
                .long("target")
                .help("The target directory")
                .value_name("DIR")
                .takes_value(true)
                .default_value(default_target),
        )
        .arg_from_usage("-n, --dry-run... 'See what would happen, but don\'t run anything'")
        .arg_from_usage("-l, --symlinks-only... 'only handle symlinks'")
}
