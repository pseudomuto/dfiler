extern crate dfiler;

use std::fs;
use std::panic;
use std::path::Path;

fn setup() {
    fs::remove_dir_all("./tmp").unwrap_or_else(|why| println!("! {:?}", why.kind()));
    fs::create_dir_all("./tmp/symlinks").unwrap_or_else(|why| println!("! {:?}", why.kind()));
}

fn teardown() {}

#[test]
fn creates_symlinks_for_files_and_directories() {
    run_test(|| {
        invoke(vec![
            "dfiler",
            "-s",
            "fixture/source",
            "-t",
            "tmp/symlinks",
            "--symlinks-only",
        ]);

        assert!(Path::new("tmp/symlinks/bin/yo").exists());
        assert!(Path::new("tmp/symlinks/.agignore").exists());
    })
}

fn invoke(args: Vec<&str>) {
    let values = args.into_iter().map(String::from).collect();
    dfiler::run(values).expect("Something went wrong");
}

fn run_test<T>(test: T) -> ()
where
    T: FnOnce() -> () + panic::UnwindSafe,
{
    setup();

    let result = panic::catch_unwind(|| test());
    teardown();

    assert!(result.is_ok())
}
