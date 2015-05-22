<?hh // strict

namespace Rime\ActionController\Controller;

abstract class BaseController implements \Rime\ActionController\Implementation\iAbstractController
{
  protected Map<Mixed> $data = Map {};
  
  public function getData(): Map<Mixed>
  {
    return $this->data;
  }
  
  public function __set(string $name, Mixed $value): void
  {
    $this->data[$name] = $value;
  }
  
  public function __get(string $name): Mixed
  {
    if( $this->data->contains($name) )
      return $this->data->get($name);
    else
      throw new \Rime\ActionController\Exception\UndefinedProperty;
  }
}