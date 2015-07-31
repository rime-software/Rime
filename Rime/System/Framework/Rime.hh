<?hh // strict

namespace Rime\System\Framework;

class Rime extends \Rime\System\Implementation\Singleton
{
  
  private Map $attachments = Map{};
  
  public static function filter_get(string $key, $filter_type = false): mixed
  {
    return filter_input(INPUT_GET, $key, $filter_type ? $filter_type : FILTER_DEFAULT);  
  }

  public static function filter_post(string $key, $filter_type = false): mixed
  {
    return filter_input(INPUT_POST, $key, $filter_type ? $filter_type : FILTER_DEFAULT);  
  }
  
  public function attach(Mixed $element, string $alias): void
  {
    $this->attachments[$alias] = $element;
  }
  
  public function __get(string $element): Mixed
  {
    if($this->attachments->contains($element))
      return $this->attachments->get($element);
    return null;
  }
  
}
