<?hh // strict

namespace Rime\ActionView\Registry;

class TemplateRegistry
{

  protected $map;
  
  public function __construct($map = array())
  {
    foreach ($map as $name => $spec) 
    {
      $this->set($name, $spec);
    }
  }
  
  public function set($name, $spec): void
  {
    if (is_string($spec)) 
    {
      $__FILE__ = $spec;
      $spec = function ($__VARS__ = array()) use ($__FILE__) 
      {
        extract($__VARS__, EXTR_SKIP);
    
        if(!file_exists($__FILE__))
        {
          throw new \Rime\ActionView\Exception\TemplateNotFound('Unable to load view: '.$__FILE__);
        }
    
        require $__FILE__;
      };
    }
    $this->map[$name] = $spec;
  }
  
  public function has($name): boolean
  {
    return isset($this->map[$name]);
  }
  
  public function get($name): mixed
  {
    if(isset($this->map[$name]))
    {
      return $this->map[$name];
    }
    throw new \Rime\ActionView\Exception\TemplateNotFound($name);
  }
}