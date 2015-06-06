<?hh // strict

namespace Rime\ActionDispatch\Session\Factory;

class SessionFactory
{
  public function newInstance(array $cookies, $delete_cookie = null): \Rime\ActionDispatch\Session\User\Session
  {
    $phpfunc = new \Rime\ActionDispatch\Session\User\Phpfunc;
    return new \Rime\ActionDispatch\Session\User\Session(
      new \Rime\ActionDispatch\Session\Factory\SegmentFactory,
      new \Rime\ActionDispatch\Session\Factory\CsrfTokenFactory(new \Rime\ActionDispatch\Session\Random\Randval($phpfunc)),
      $phpfunc,
      $cookies,
      $delete_cookie
    );
  }
}
