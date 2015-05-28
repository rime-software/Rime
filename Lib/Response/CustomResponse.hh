<?hh // strict

namespace Lib\Response;

use \Rime\ActionController\Implementation as iController;

class CustomResponse
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