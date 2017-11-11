extern crate dfiler;
extern crate simplelog;

use std::env;

use simplelog::{CombinedLogger, Config, TermLogger};

fn main() {
    let log_level = env::var("LOG_LEVEL")
        .unwrap_or("INFO".into())
        .parse()
        .unwrap();

    CombinedLogger::init(vec![TermLogger::new(log_level, Config::default()).unwrap()]).unwrap();

    if let Err(error) = dfiler::run(env::args().skip(1).collect()) {
        println!("There was an error: {}", error);
    }
}
