<?hh // strict

namespace Rime\ActionView\View;

abstract class BaseView
{
  
  private $data;
  private $content;
  private $layout;
  private $view;
  private $section;
  private $capture;
  private \Rime\ActionView\Registry\TemplateRegistry $template_registry;
  private \Rime\ActionView\Registry\TemplateRegistry $view_registry;
  private \Rime\ActionView\Registry\TemplateRegistry $layout_registry;
  
  public function __construct(\Rime\ActionView\Registry\TemplateRegistry $view_registry, \Rime\ActionView\Registry\TemplateRegistry $layout_registry) 
  {
    $this->data = (object) array();
    $this->view_registry = $view_registry;
    $this->layout_registry = $layout_registry;
  }


  public function __get($key): mixed
  {
    return $this->data->$key;
  }
  
  
  public function __set($key, $val): void
  {
    $this->data->$key = $val;
  }
  
  
  public function __isset($key): mixed
  {
    return isset($this->data->$key);
  }
  
  
  public function __unset($key): void
  {
    unset($this->data->$key);
  }
      
  public function setData($data): void
  {
    $this->data = (object) $data;
  }
  
  public function addData($data): void
  {
    foreach ($data as $key => $val) 
    {
        $this->data->$key = $val;
    }
  }
  
  public function getData(): mixed
  {
    return $this->data;
  }
    
  protected function setContent($content): void
  {
    $this->content = $content;
  }
  
  protected function getContent(): mixed
  {
    return $this->content;
  }
  
  public function setLayout($layout): void
  {
    $this->layout = $layout;
  }
  
  public function getLayout(): mixed
  {
    return $this->layout;
  }

  protected function hasSection($name): boolean
  {
    return isset($this->section[$name]);
  }
  
  protected function setSection( $name, $body): void
  {
    $this->section[$name] = $body;
  }
  
  protected function getSection($name): mixed
  {
    return $this->section[$name];
  }
  
  protected function beginSection($name): void
  {
    $this->capture[] = $name;
    ob_start();
  }
  
  protected function endSection(): void
  {
    $body = ob_get_clean();
    $name = array_pop($this->capture);
    $this->setSection($name, $body);
  }
     
  public function getLayoutRegistry(): \Rime\ActionView\Registry\TemplateRegistry
  {
    return $this->layout_registry;
  }
  
  public function setView($view): void
  {
    $this->view = $view;
  }
  
  public function getView(): mixed
  {
    return $this->view;
  }
  
  public function getViewRegistry(): \Rime\ActionView\Registry\TemplateRegistry
  {
    return $this->view_registry;
  }
  
  
  protected function setTemplateRegistry(\Rime\ActionView\Registry\TemplateRegistry $template_registry): void
  {
    $this->template_registry = $template_registry;
  }
  
  protected function getTemplate($name): mixed
  {
    $tmpl = $this->template_registry->get($name);
    return $tmpl->bindTo($this, get_class($this));
  }
}