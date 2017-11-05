extern crate dfiler;

use std::env;

fn main() {
    dfiler::run(env::args().skip(1).collect());
}
