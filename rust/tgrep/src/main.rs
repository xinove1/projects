use std::env;
use std::process;
use tgrep::Config;

fn main() {
    let config = Config::build(env::args()).unwrap_or_else(|err| {
        eprintln!("{}", err);
        process::exit(1);
    });

    if let Err(err) = tgrep::run(config) {
        eprintln!("{}", err);
        process::exit(1);
    }
}
