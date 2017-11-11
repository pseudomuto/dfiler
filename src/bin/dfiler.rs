extern crate dfiler;

use std::env;

fn main() {
    if let Err(error) = dfiler::run(env::args().skip(1).collect()) {
        println!("There was an error: {}", error);
    }
}
