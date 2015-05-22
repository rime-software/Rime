<?hh // strict

namespace Rime\ActionDispatch\Dispatcher\Factory;

class RouterFactory
{
  public function newInstance()
  {
    $router = new \Rime\ActionDispatch\Dispatcher\Route\Router(
      new \Rime\ActionDispatch\Dispatcher\Route\RouteCollection(
          new \Rime\ActionDispatch\Dispatcher\Factory\RouteFactory()
        ),
        new \Rime\ActionDispatch\Dispatcher\Route\RouteGenerator());
    return $router;
  }

}