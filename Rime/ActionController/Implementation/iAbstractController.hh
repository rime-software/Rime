<?hh // strict

namespace Rime\ActionController\Implementation;

interface iAbstractController
{
  protected Map<Mixed> $data;
  
  public function getData(): Map<Mixed>;
}