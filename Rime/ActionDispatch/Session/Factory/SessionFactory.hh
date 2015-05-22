<?hh // strict

namespace Rime\ActionDispatch\Session\Factory;

class SessionFactory
{
  public function newInstance(array $cookies, $delete_cookie = null): Session
  {
    $phpfunc = new Phpfunc;
    return new Session(
      new SegmentFactory,
      new CsrfTokenFactory(new Randval($phpfunc)),
      $phpfunc,
      $cookies,
      $delete_cookie
    );
  }
}
