<?hh // strict

namespace Application\Controllers;

class indexController extends \Rime\ActionController\Controller\BaseController
{
  public function index()
  {
    $this->respondTo( ($format) ==> {
      $format->json = true;
    });
  }
}