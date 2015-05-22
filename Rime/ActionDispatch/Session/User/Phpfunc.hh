<?hh // strict

namespace Rime\ActionDispatch\Session\User;


class Phpfunc
{
  public function __call(string $func, array $args): mixed
  {
    return call_user_func_array($func, $args);
  }
}
