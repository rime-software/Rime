<?hh // strict

namespace Rime\ActionSupport\Helpers;

abstract class RimeDecorator
{
  protected mixed $model;
  
  protected function __construct(mixed $model)
  {
    $this->model = $model;
  }
  
  public static function decorate(mixed $object, $namespaced = true): mixed
  {
    if(is_object($object))
    {
      $reflection = new \ReflectionClass(get_class($object));
      if($namespaced)
      {
        $className = '\\Application\\Decorators\\'.( $reflection->getShortName() ).'Decorator';
      }
      else
      {
        $className = '\\'.$reflection->getShortName().'Decorator';
      }
      return (new $className($object));
    }
  }

  public function __call($method,$args=array()): mixed
  {
    if( method_exists($this->model,$method) )
    {
      return call_user_func_array(array($this->model,$method), $args);
    }
    return call_user_func_array(array($this,$method), $args);    
  }
  
  public function __set(string $name, mixed $value)
  {
    if(property_exists($this->model,$name))
    {
      $this->model->$name = $value;
    }
    else
    {
      $this->$name = $value;
    }
  }
  
  public function __get(string $name)
  {
    if(property_exists($this->model,$name))
    {
      return $this->model->$name;
    }
    else
    {
      return $this->$name;
    }
  }
  
}