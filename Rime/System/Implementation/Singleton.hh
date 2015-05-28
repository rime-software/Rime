<?hh // strict

namespace Rime\System\Implementation;

abstract class Singleton
{
  private static $instance;

  public static function getInstance(): mixed
  {
    if (!isset(self::$instance)) 
    {
      self::$instance = new (get_called_class());
    }
    return self::$instance;
  }
    
}