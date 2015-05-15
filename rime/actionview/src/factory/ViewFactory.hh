<?hh // strict

namespace Rime\ActionView;

class ViewFactory
{
  public function newInstance()
  {
    return new View(
      new TemplateRegistry,
      new TemplateRegistry
    );
  }
}