<?hh // strict
  
namespace Rime\ActionController\Filter;  

class FilterFactory
{
  public static function newInstance(string $type, string $namespace): \Rime\ActionController\Filter\iFilter
  {
    $class = $namespace.$type.'Filter';
    return new $class();
  }
}