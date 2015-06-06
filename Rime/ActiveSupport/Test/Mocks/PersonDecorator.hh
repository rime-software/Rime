<?hh // strict

class PersonDecorator extends \Rime\ActionSupport\Helpers\RimeDecorator
{
  public $age;
  
  public function changeName(string $name): void
  {
    $this->name = $name;
  }

}