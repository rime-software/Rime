<?hh // strict

namespace Application\Controllers;

class indexController extends \Rime\ActionController\Controller\BaseController
{
  public function index()
  {
    echo "hello world!";
  }
}