<?hh // strict

namespace Rime\ActionController\Controller;

abstract class BaseController implements \Rime\ActionController\Implementation\iAbstractController
{
  public ?\Rime\ActionView\Render\View $view;
  protected Map<Mixed> $data = Map {};
  protected \Rime\ActionController\Render\Renderer $renderer;
  
  public function __construct()
  {
    $this->renderer = new \Rime\ActionController\Render\Renderer; 
    $this->view = null; 
  }
  
  public function respondTo(callable $lambda): void
  {
    call_user_func($lambda, $this->getRenderer());
  }
  
  public function canRespondTo($type = '.html'): boolean
  {
    $type = str_replace('.', '', $type);
    return $this->renderer->$type ? true : false;
  }
  
  public function getData(): Map<Mixed>
  {
    return $this->data;
  }
  
  public function &getRenderer(): \Rime\ActionController\Render\Renderer
  {
    return $this->renderer;
  }

  public function __call(string $method, array $arguments): mixed
  {
    if(is_null($this->view))
    {
      $this->view = (new \Rime\ActionView\Factory\ViewFactory)->newInstance();
    }
    $this->view->$method($arguments[0] ? $arguments : false);
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