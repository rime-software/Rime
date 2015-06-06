<?hh // strict

class Person
{
  public string $name;
  public string $status = "Married";
  
  public function __construct(string $name)
  {
    $this->name = $name;
  }
  
  public function getName(): string
  {
    return $this->name;
  }
}