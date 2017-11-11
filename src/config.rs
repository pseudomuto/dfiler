use std::collections::BTreeMap;
use std::fs::File;
use std::io::BufReader;
use std::io::prelude::*;
use std::path::PathBuf;

use errors::*;
use serde_yaml;

/// The `Config` struct holds information loaded from a dfiler.yml file.
#[derive(Debug, Deserialize)]
pub struct Config {
    /// The set of symlinks to be created
    pub symlinks: BTreeMap<String, String>,
}

impl Config {
    /// Parses a `Config` object from the supplied YAML string.
    ///
    /// # Examples
    ///
    /// ```
    /// # extern crate dfiler;
    /// let config = dfiler::Config::from_yaml(r#"
    /// symlinks:
    ///   bin: _
    ///   agignore: .agignore
    /// "#);
    /// ```
    ///
    /// # Errors
    ///
    /// Will return `Err(Error)` when parsing the YAML fails
    pub fn from_yaml(yaml: &str) -> Result<Self> {
        serde_yaml::from_str(yaml).chain_err(|| "Unable to parse config file")
    }

    /// Parses a `Config` object from the supplied file.
    ///
    /// # Errors
    ///
    /// Will return `Err(Error)` when parsing the YAML fails
    pub fn from_yaml_file(path: &PathBuf) -> Result<Self> {
        let file = File::open(path).chain_err(|| "Unable to read config file")?;
        let mut buf_reader = BufReader::new(file);
        let mut contents = String::new();

        buf_reader
            .read_to_string(&mut contents)
            .chain_err(|| "Unable to read config file")?;

        Config::from_yaml(&contents)
    }
}

#[cfg(test)]
mod test {
    use super::Config;
    use std::path::Path;

    #[test]
    fn from_yaml_loads_symlinks() {
        let config = Config::from_yaml(include_str!("../fixture/source/dfiler.yml")).unwrap();
        assert_eq!(false, config.symlinks.is_empty());

        assert_eq!("_", config.symlinks["bin"]);
        assert_eq!(".agignore", config.symlinks["agignore"]);
    }

    #[test]
    fn from_yaml_file_loads_symlinks() {
        let path = Path::new(env!("CARGO_MANIFEST_DIR")).join("fixture/source/dfiler.yml");
        let config = Config::from_yaml_file(&path).unwrap();
        assert_eq!(false, config.symlinks.is_empty());

        assert_eq!("_", config.symlinks["bin"]);
        assert_eq!(".agignore", config.symlinks["agignore"]);
    }
}
