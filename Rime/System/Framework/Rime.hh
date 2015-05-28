<?hh // strict

namespace Rime\System\Framework;

class Rime extends \Rime\System\Implementation\Singleton
{
  
  private Map $attachments = Map{};
  
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