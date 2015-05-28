<?hh // strict

namespace Rime\ActionView\Factory;

class ViewFactory
{
  public function newInstance()
  {
    return new \Rime\ActionView\Render\View(
      new \Rime\ActionView\Registry\TemplateRegistry,
      new \Rime\ActionView\Registry\TemplateRegistry
    );
  }
}