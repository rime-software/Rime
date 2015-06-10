<?hh // strict
  
require_once 'constants.hh';
require_once 'autoload.hh';

if(USE_ACTIVE_RECORD)
  require_once 'database.hh';
  
require_once 'routes.hh';

require_once 'templateRegistry.hh';
require_once 'viewRegistry.hh';
  