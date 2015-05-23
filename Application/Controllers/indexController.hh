<?hh // strict

namespace Application\Controllers;

class indexController extends \Rime\ActionController\Controller\BaseController
{
  public function index()
  {
    $this->greeting = "Hello World!";

    $this->respondTo( ($format) ==> {
      $format->json = true;
      $format->xml = true;
      $format->html = 'index.index';
    });
  }
}