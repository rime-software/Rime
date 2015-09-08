<?hh
  
  define('BASE_PATH',dirname(dirname(__FILE__)));
  
  require_once 'Config/autoload.hh';
  require_once 'Rime/ActionController/bootstrap.hh';
  require_once 'Rime/ActionDispatch/bootstrap.hh';
  require_once 'Rime/ActionView/bootstrap.hh';
  require_once 'Rime/ActiveSupport/bootstrap.hh';
  require_once 'Rime/System/bootstrap.hh';
  
  #require_once 'Rime/ActiveRecord/autoload.php';
  #require_once 'Rime/ActiveRecord/test/helpers/config.php';