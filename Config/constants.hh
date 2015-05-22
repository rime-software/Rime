<?hh // strict

/*
 * Minimum HHVM version required to run Rime
 * 380 translates to 3.8.0 (-dev if using a nightly build)
 * Run the dependencyTest in Test/dependencies/dependencyTest.hh to verify your HHVM version
 * ex: hhvm /usr/bin/phpunit --testsuite dependencies
 */
define('HHVM_MIN_VERSION',380);

/*
 * Base Path relative to public_html/index.hh
 * BASE_PATH provides the fundamental basis to autoloading classes
 * used in the Rime namespace as well as user-defined controllers, models,
 * and views.
 */
define('BASE_PATH',dirname(dirname(__FILE__)));