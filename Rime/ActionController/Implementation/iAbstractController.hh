<?hh // strict

namespace Rime\ActionController\Implementation;

interface iAbstractController
{
  public \Rime\ActionView\View\View $view;
  protected Map<Mixed> $data;
  protected \Rime\ActionController\Render\Renderer $renderer;
  
  public function __construct();
  public function respondTo(callable $lambda): void;
  public function getData(): Map<Mixed>;
  public function __set(string $name, Mixed $value): void;
  public function __get(string $name): Mixed;
}