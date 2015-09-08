<?hh // strict

class PersonDecorator extends \Rime\ActiveSupport\Helpers\RimeDecorator
{
  public $age;
  
  public function changeName(string $name): void
  {
    $this->name = $name;
  }

}