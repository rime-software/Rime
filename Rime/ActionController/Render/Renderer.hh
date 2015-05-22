<?hh // strict

namespace Rime\ActionController\Render;

class Renderer
{
  protected Map<Mixed> $data;
  
  public function __construct($formats = Map { 
    ".html" => false,
    ".xml"  => false,
    ".json" => false 
  })
  {
    $this->data = $formats;
  }
  
  public function getData(): Map<Mixed>
  {
    return $this->data;
  }
  
  public function __set(string $name, Mixed $value): void
  {
    $this->data['.'.$name] = $value;
  }
  
  public function __get(string $name): Mixed
  {
    if( $this->data->contains('.'.$name) )
      return $this->data->get('.'.$name);
    else
      return false;
  }
}