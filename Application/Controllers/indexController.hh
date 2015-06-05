<?hh // strict

namespace Application\Controllers;

class indexController extends \Rime\ActionController\Controller\BaseController
{
  public function index($format)
  {
    $this->greeting = "Hello World!";
    $this->format = $format;
    
    $this->respondTo( ($format) ==> {
      $format->json = true;
      $format->xml = true;
      $format->html = 'index.index';
    });
  }
}