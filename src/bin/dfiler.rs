extern crate dfiler;

use std::env;

fn main() {
    let matches = dfiler::run(env::args().skip(1).collect());

    if let Some(_) = matches.subcommand_matches("run") {
        println!("You hit up the run command");
    }
}
