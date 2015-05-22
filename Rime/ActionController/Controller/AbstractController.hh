<?hh // strict

namespace Rime\ActionController\Controller;

abstract class AbstractController
{
  protected Map<Mixed> $data = Map {};
  
  public function getData(): Map<Mixed>
  {
    return $this->data;
  }
}