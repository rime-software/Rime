<?hh // strict

namespace Application\Controllers;

class indexController extends \Rime\ActionController\Controller\BaseController
{
  public function index($name)
  {
    $this->greeting = "See me in Application/Views/index/index.hh!";
    
    $this->respondTo( ($format) ==> {
      $format->json = true;
      $format->xml = true;
      $format->html = 'index.index';
    });
  }
}