<?hh // strict

if(defined('BASE_PATH'))
{
  require_once BASE_PATH.'/Rime/ActionView/load.hh';
}
else
{
  require_once '../ActionView/load.hh';
}

require_once 'Exception/Exception.hh';
require_once 'Exception/UndefinedProperty.hh';
require_once 'Implementation/iAbstractController.hh';
require_once 'Controller/BaseController.hh';
require_once 'Render/Renderer.hh';