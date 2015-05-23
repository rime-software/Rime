<?hh // strict

namespace Application\Hooks;

use \Rime\ActionController\Implementation as iController;

class ResponseHook
{
  private iController\iAbstractController $controller;
  
  public function __construct($controller)
  {
    $this->controller = $controller;
  }
  
  public function atom()
  {
    die('Not Yet Implemented');
  }
  
}