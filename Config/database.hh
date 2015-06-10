<?hh //strict
  
  require_once BASE_PATH.'/Rime/ActiveRecord/autoload.php';
  
  ActiveRecord\Config::initialize(function($cfg)
  {
       $cfg->set_model_directory(MODEL_PATH);
       $cfg->set_connections(array(
          'development' => 'mysql://user:mypass@myhost/my_db'));
  });