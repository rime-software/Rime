<?hh // strict

namespace Rime\ActionController\Implementation;

interface iAbstractController
{
  protected Map<Mixed> $data;
  
  public function getData(): Map<Mixed>;
  public function __set(string $name, Mixed $value): void;
  public function __get(string $name): Mixed;
}