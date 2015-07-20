<?hh // strict

namespace Rime\ActionController\Controller;

abstract class BaseController implements \Rime\ActionController\Implementation\iAbstractController
{
  public ?\Rime\ActionView\Render\View $view = null;
  public \Rime\ActionController\Render\Renderer $renderer;
  protected Map<Mixed> $data = Map {};
  
  public static array<string> $before_filter = array();
  
  public function __construct(){}
  
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
    if(is_null($this->renderer))
    {
      $this->renderer = new \Rime\ActionController\Render\Renderer;
    }
    return $this->renderer;
  }
  
  public function loadViewRegistries(): ?\Rime\ActionView\Render\View
  {
    if(is_null($this->view))
    {
      $Rime = \Rime\System\Framework\Rime::getInstance();
      $this->view = (new \Rime\ActionView\Factory\ViewFactory)->newInstance();
      $this->view->setRegistries(
        new \Rime\ActionView\Registry\TemplateRegistry($Rime->viewMap),
        new \Rime\ActionView\Registry\TemplateRegistry($Rime->templateMap)
      );
    }
    return $this->view;
  }
  
  public function render(string $name, array $data = array()): ?string
  {
    if(is_null($this->view))
    {
      $this->loadViewRegistries();
    }
    $this->view->setView($name);
    echo $this->view->__invoke($data);
  }
  
  public function filter(string $action, string $type = 'Before', $namespace = '\\Rime\\ActionController\\Filter\\'): void
  {
    $filter_data = null;
    switch($type)
    {
      case 'Before':
        $filter_data = $this::$before_filter;
        break;
      default:
        
    }
    $results = \Rime\ActionController\Filter\FilterFactory::newInstance($type,$namespace)->filter(
      $action, $filter_data
    );
    
    $this->execute_filter_actions($results);
    
  }
  
  protected function redirect_to(string $url, bool $replace = true, $redirect_code = 301, string $content_type = 'text/html'): void
  {
    header('Content-Type: '.$content_type);
    header('Location: '.$url, $replace, $redirect_code);
  }
  
  private function execute_filter_actions(array<string> $actions): mixed
  {
    foreach($actions as $action)
    {
      $this->$action();
    }
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